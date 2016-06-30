#include "ClassDeclarations.h"

static void nothing(){
}

void BasicThreading::basicThreadingExample(int numThreads){
	//To create a thread you do it by creating an object of the thread class
	//Takes in a function to do while it runs
	//foo doesn't do anything, it is just to show syntax
	thread beginner(nothing);

	//We will get to it later, but for right now, you have to join a thread when it is done being used
	//a good habit to get into is to make sure you can join the thread
	if (beginner.joinable())
		beginner.join();

	//That was a basic look at threading, now we will deal with creating multiple threads
	//I create a vector to store a variable amount of threads
	//currently it is based off the hardware concurrency
	std::vector<thread> threads(numThreads);
	for (int i = 0; i < threads.size(); i++){
		threads[i] = thread(nothing);
	}

	for (int i = 0; i < threads.size(); i++){
		if (threads[i].joinable())
			threads[i].join();
	}
}