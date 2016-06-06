/*
Multithreading
(c) 2016
original authors: Sean Connolly
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.
This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*	This tutorial deals with the basics of multithreading in C/C++.
*
*
*
*/
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using std::cout;
using std::endl;
using std::thread;

void basicThreading(const int numThreads);
void foo();
void mutexs();
void printStuff(int index);
void joinVSDetach();

//Thread Issues
	//Too Many Threads
	//Data Races
	//Deadlocks
		//thread a		thread b
		//lock1			lock2
		//lock2			lock1
	//Livelocks
	//highly contended Locks
	//Priority Inversion


int main(){
	//Gives an approximation of the number of threads supported
	//this is system and implementation specific
	//
	cout << std::thread::hardware_concurrency() << endl;

	getchar();
	return 0;
}

void basicThreading(int numThreads){
	//To create a thread you do it by creating an object of the thread class
		//Takes in a function to do while it runs
		//foo doesn't do anything, it is just to show syntax
	thread beginner(foo);

	//We will get to it later, but for right now, you have to join a thread when it is done being used
	//a good habit to get into is to make sure you can join the thread
	if (beginner.joinable())
		beginner.join();

	//That was a basic look at threading, now we will deal with creating multiple threads
	std::vector<thread> threads(numThreads);
	for (int i = 0; i < threads.size(); i++){
		threads[i] = thread(foo);
	}

	for (int i = 0; i < threads.size(); i++){
		if (threads[i].joinable())
			threads[i].join();
	}
}

void foo(){
	//s
}

std::mutex mtx;
int numArr[4] = { 0, 0, 0, 0 };
void mutexs(){
	//s
}

void printStuff(int index){
	//Need to lock since cout merely sends the string to the stdout buffer
	while (numArr[index] < 10) {
		mtx.lock();
		cout << "Thread " << index << ": " << numArr[index] << endl;
		mtx.unlock();

		numArr[index]++;
	}
}

void joinVSDetach(){
	//s
}