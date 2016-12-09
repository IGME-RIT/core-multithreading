#include "../header/ClassDeclarations.h"

// A mutex is an object that is used for makong sure only 1 thread at a time has the ability to change a resource
	// It is under the std namespace
	// You do this by locking the mutex before the area of code you want to prevent multiple threads from accessing at once
		// mtx.lock();
	// You unlock the mutex after the area of code you want to prevent multiple threads from accessing at once
		// mtx.unlock

// This is an example of how to create a mutex
std::mutex mtx;
int num = 0;
static void fubar(){
	// A use of mutexes
	// Since num will be used by several threads, we mutex it so that only one thread can use it at a time
	// Also cout sends the string to a buffer called stdout, this buffer is also a resource that will be shared between mutiple threads
	mtx.lock();
	// The inside of a mutex is called a critical section
		// A critical section part of a multi-process program that may not be concurrently executed by more than one of the program's processes
			// https://en.wikipedia.org/wiki/Critical_section
	cout << "Num = " << num << endl;
	num++;
	mtx.unlock();

	// This is just one use of mutexes
	// Also, There are a lot of things to consider when using mutexes.
	// This is will be covered in another tutorial: 
}

void Mutexes::mutexExample(int numThreads){
	// You build the threads as normal
	vector<thread> threads(numThreads);
	for (unsigned int i = 0; i < threads.size(); i++){
		threads[i] = thread(fubar);
	}

	for (unsigned int i = 0; i < threads.size(); i++){
		if (threads[i].joinable())
			threads[i].join();
	}
}
