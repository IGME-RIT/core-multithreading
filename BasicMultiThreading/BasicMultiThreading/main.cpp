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
*	It covers the basics of creating threads, using mutexes, and the difference between join and detach.
*	This is meant for just the basics of mutithreading.
*/

//Used:
	//http://www.drdobbs.com/tools/avoiding-classic-threading-problems/231000499
	//http://www.drdobbs.com/cpp/volatile-the-multithreaded-programmers-b/184403766
	//http://www.bogotobogo.com/cplusplus/multithreaded4_cplusplus11.php
	//http://stackoverflow.com/questions/15148057/what-does-stdthread-join-do
	//http://www.cplusplus.com/reference/thread/thread/detach/
	//https://en.wikipedia.org/wiki/Critical_section

//For Multithreading definitions:
	//http://www.bogotobogo.com/cplusplus/multithreaded.php

#include "ClassDeclarations.h"

//Before we start talking about threading,
//It is important to tackle the difference between concurrent computing and parallel computing
//parallel is where you have the threads running on different cores all running at the same instant in time
//concurrent is when you have multiple threads running on the same core,
	//but each thread is given its own small amount of time to work before it is passed to the next thread

int main(){
	//Hardware Concurrency is the number of threads that your processor can run at simultaneously
		//Gives an approximation of the number of threads supported
		//this is system and implementation specific
	unsigned int numThreads = std::thread::hardware_concurrency();
	cout << numThreads << endl;
	
#pragma region Basic Threading Intro
	BasicThreading threadsIntro;
	threadsIntro.basicThreadingExample(numThreads);
#pragma endregion

#pragma region Basic Mutex Intro
	Mutexes mutexesIntro;
	mutexesIntro.mutexExample(numThreads);
#pragma endregion

#pragma region Basic Intro on Joining VS Detaching Threads
	JoinVSDetach joinVSDetachIntro;
	joinVSDetachIntro.joinVSDetachExample();
#pragma endregion

	//basicThreading(numThreads);
	//mutexs(numThreads);

	getchar();
	return 0;
}