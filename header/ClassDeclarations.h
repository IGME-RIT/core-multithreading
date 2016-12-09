#pragma once
#include <vector>
#include <thread>
#include <mutex>
#include <iostream>

using namespace std;

class BasicThreading{
public:
	void basicThreadingExample(int numThreads);
};

class Mutexes{
public:
	void mutexExample(int numThreads);
};

class MutexConsiderations{
public:
	void considerationsExample();
};

class JoinVSDetach{
public:
	void joinVSDetachExample();
};