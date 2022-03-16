#include <iostream> // For std::cin, cout
#include <thread> // For std::thread
#ifdef CXX20
#include <semaphore> // For std::binary_semaphore / Since C++20
using semaphore = std::binary_semaphore;
#else
#include <atomic> // For std::atomic
#include <condition_variable>
#include <mutex>
class semaphore{
private:
	size_t count_;
	std::condition_variable cv;
	std::mutex mtx;
public:
	explicit semaphore( size_t count = 0 ):count_(count){}
	semaphore( const semaphore& ) = delete;
	semaphore( semaphore&& ) = delete;
	semaphore& operator=( const semaphore& ) = delete;
	semaphore& operator=( semaphore&& ) = delete;

	void release(){
		std::lock_guard<std::mutex> lock( mtx );
		count_ = 1;
		cv.notify_one();
		 //count_.notify_one();
	}
	void acquire(){
		std::unique_lock<std::mutex> lock( mtx );
		while( !count_ )
			cv.wait( lock );
		count_ = 0;
		return;
		for( ;; ){
			//auto prev = count_.exchange( 0 );
			//if( prev == 1 )
			//	break;
			cv.wait( lock, [&](){ return count_ == 0; } );
			//count_.wait( 0, std::memory_order_relaxed );
		}
	}
	bool try_acquire(){
		std::lock_guard<std::mutex> lock( mtx );
		if( count_ )
			return ( count_ = 0 ) == 0;
		return false;
		//unsigned char _Prev = count_.exchange( 0 );
		//return reinterpret_cast<const bool&>( _Prev );
	}
};
#endif
#include <vector> // For database imitation
#include <fstream> // For file io
#include <algorithm> // For std::sort

using t_entry = std::string; // Type of entry at database
using database = std::vector<t_entry>; // Imitation of database


std::ofstream fout; // Out result of working of program to file

// ** Convert t_entry to string
std::string to_string( const t_entry& e ){
	return e;
}

// ** Convert a data to t_entry
t_entry to_entry( const std::string& a ){
	return a;
}

// ** Support data type
struct tumbler{
	size_t counter{ 0 };
	semaphore mtx{ 1 };
	tumbler():counter( 0 ), mtx( 1 ){}
	inline void turnOn( semaphore& target ){
		mtx.acquire();
		if( counter == SIZE_MAX )
			throw 0;
		counter++;
		if( counter == 1 ){
			target.acquire();
		}
		mtx.release();
	}
	inline void turnOff( semaphore& target ){
		mtx.acquire();
		if( counter > 0 )
			counter--;
		if( counter == 0 ){
			target.release();
		}
		mtx.release();
	}
};

tumbler activeReaders;
semaphore dataLock( 1 );
semaphore wicket( 1 );
#if 1
semaphore outLock( 1 );
#else
struct{
	void release(){}
	void acquire(){}
}outLock;
#endif

database db;
// ** Imitation of database controller
class Manager{
private:
public:
	// Normalize entries
	inline static void sort(){
		std::sort( db.begin(), db.end() );
	}
	// Add entry to db
	inline static void add( const t_entry& entry ){
		db.push_back( entry );
	}
	// Change entry at db
	inline static void ren( size_t pos, t_entry entry ){
		if( pos < db.size() ){
			db[pos] = entry;
		}
		else{
			outLock.acquire();
			//printf_s( "Rename: Out of bounds %zu/%zu\n", pos, db.size() );
			std::cout << "Database message: changing, out of bounds " << pos << "/" << db.size() << "\n";
			fout << "Database message: changing, out of bounds " << pos << "/" << db.size() << "\n";
			outLock.release();
		}
	}
	// Remove entry from db
	inline static void rem( size_t pos ){
		if( pos < db.size() ){
			db.erase( db.begin() + pos );
		}
		else{
			outLock.acquire();
			//printf_s( "Remove: Out of bounds %zu/%zu\n", pos, db.size() );
			std::cout << "Database message: removing, out of bounds " << pos << "/" << db.size() << "\n";
			fout << "Database message: removing, out of bounds " << pos << "/" << db.size() << "\n";
			outLock.release();
		}
	}
	// Read entry from db
	inline static t_entry read( size_t pos ){
		if( pos < db.size() ){
			return db[pos];
		}
		{
			outLock.acquire();
			//printf_s( "Read: Out of bounds %zu/%zu\n", pos, db.size() );
			std::cout << "Database message: reading, out of bounds " << pos << "/" << db.size() << "\n";
			fout << "Database message: reading, out of bounds " << pos << "/" << db.size() << "\n";
			outLock.release();
		}
		return t_entry();
	}
	// Get count of elements at db
	inline static size_t getSize(){
		return db.size();
	}
};

// Function for reader thread
void read( size_t it ){
	outLock.acquire();
	std::cout << "RThread #" << it << ": started..." << "\n";
	fout << "RThread #" << it << ": started..." << "\n";
	outLock.release();

	wicket.acquire(); // Check that reader can start
	wicket.release(); //

	activeReaders.turnOn( dataLock ); // Lock data for readers
	auto sz = Manager::getSize();
	for( size_t i = 0; i < sz; i++ ){
		auto str = to_string( Manager::read( i ) );
		std::this_thread::sleep_for( std::chrono::milliseconds( it % 10 ) ); // For lag reading
		outLock.acquire();
		std::cout << "RThread #" << it << ": reads entry at " << i << ", is: " << str << "\n";
		// printf_s( "%zu: read at %zu %s\n", it, i, str.c_str() );
		fout << "RThread #" << it << ": reads entry at " << i << ", is: " << str << "\n";
		outLock.release();
	}
	activeReaders.turnOff( dataLock ); // Unlock data
}

// Function for writer thread
// it - number of thread
// type - operation type
// pos - element id
// e - a new data
void edit( size_t it, size_t type, size_t pos, const t_entry& e ){
	outLock.acquire();
	std::cout << "EThread #" << it << ": started..." << "\n";
	fout << "EThread #" << it << ": started..." << "\n";
	if( type > 2 ){
		std::cout << "EThread #" << it << ": invalid operation type " << type << "\n";
		fout << "EThread #" << it << ": invalid operation type " << type << "\n";
		return;
	}
	outLock.release();
	wicket.acquire(); // Lock readers
	dataLock.acquire(); // Lock data
	switch( type ){
		case 2:
		{
			Manager::ren( pos, e );
			outLock.acquire();
			auto str = to_string( e );
			std::cout << "EThread #" << it << ": change entry at " << pos << " to: " << str << "\n";
			//printf_s( "%zu: rename %zu %s\n", it, pos, str.c_str() );
			fout << "EThread #" << it << ": change entry at " << pos << " to: " << str << "\n";
			outLock.release();
			break;
		}
		case 1:
		{
			Manager::rem( pos );
			outLock.acquire();
			std::cout << "EThread #" << it << ": remove entry at " << pos << "\n";
			//printf_s( "%zu: remove %zu\n", it, pos );
			fout << "EThread #" << it << ": remove entry at " << pos << "\n";
			outLock.release();
			break;
		}
		case 0:
		default:
		{
			Manager::add( e );
			#if 0
			// Test section for overcharge thread work
			for( size_t i = 0; i < 20; i++ ){
				auto sz = Manager::getSize() - 1;
				//if( sz > 0 )
					//sz--;
				auto r = Manager::read( sz );
				r += std::to_string( i );
				Manager::ren( sz, r );
			}
			auto sz = Manager::getSize() - 1;
			#endif
			outLock.acquire();
			auto str = to_string( Manager::read( Manager::getSize() - 1 ) );
			std::cout << "EThread #" << it << ": adds entry: " << str << "\n";
			//printf_s( "%zu: add %s\n", it, str.c_str() );
			fout << "EThread #" << it << ": adds entry: " << str << "\n";
			outLock.release();
			break;
		}
	}
	Manager::sort();
	dataLock.release(); // Unlock data
	wicket.release(); // Unlock readers
}

bool strtosize_t( const std::string& str, size_t& val ){
	char* end;
	val = strtoull( str.c_str(), &end, 10 );
	return end == str.c_str() ? false : true;
}

int main( int argc, char* args[] ){
	size_t it = 0; // ** Counter of launched threads
	std::string cmd; // ** Command
	std::ifstream f; // ** Input file
	if( argc > 1 ){
		f.open( args[1], std::ifstream::in );
	}
	if( f.is_open() ){
		std::cout << "Input file: " << args[1] << "\n";
	}
	else{
		std::cout << "Custom input. Type \'help\' for commands list." << "\n";
	}
	if( argc > 2 ){
		fout.open( args[2], std::ofstream::out );
	}
	if( fout.is_open() ){
		std::cout << "Output file: " << args[2] << "\n";
	}
	else{
		std::cout << "No output file.\n";
	}
	std::istream& in( f.is_open() ? f : std::cin );
	std::vector<std::thread> threads; // ** Started threads
	do{
		in >> cmd;
		std::string str;
		// Add entry
		if( cmd == "add" ){
			in >> str;
			threads.push_back( std::thread( edit, it, 0ull, 0ull, to_entry( str ) ) );
		}
		// Change entry
		else if( cmd == "change" ){
			in >> str;
			size_t pos;
			std::string dat;
			in >> dat;
			if( strtosize_t( dat, pos ) ){
				threads.push_back( std::thread( edit, it, 2ull, pos, to_entry( str ) ) );
			}
			else{
				std::cout << "Data corrupted\n";
			}
		}
		// Remove entry
		else if( cmd == "remove" ){
			size_t pos;
			in >> str;
			if( strtosize_t( str, pos ) ){
				threads.push_back( std::thread( edit, it, 1ull, pos, to_entry( "" ) ) );
			}
			else{
				std::cout << "Data corrupted\n";
			}
		}
		// Launch reader
		else if( cmd == "read" ){
			threads.push_back( std::thread( read, it ) );
		}
		else if( cmd == "help" ){
			outLock.acquire();
			std::cout << "add   " << "\t<string>        \t" << "Add entry to db." << "\n";
			std::cout << "change" << "\t<string> <index>\t" << "Change entry at db at position." << "\n";
			std::cout << "remove" << "\t<index>         \t" << "Remove entry from db at position." << "\n";
			std::cout << "read  " << "\t                \t" << "Launch read-thread." << "\n";
			std::cout << "help  " << "\t                \t" << "This message." << "\n";
			std::cout << "exit  " << "\t                \t" << "Terminate program." << "\n";
			outLock.release();
		}
		it++;
	} while( cmd != "exit" && !in.eof() );
	for( auto& p : threads )
		p.join();
	return 0;
}
