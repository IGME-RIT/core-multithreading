#include "../header/ClassDeclarations.h"

// A brief consideration about what to mutex
// Figuring out what to mutex can be hard, so lets talk about things to consider

// The first and main consideration is access
	// What is being accessed and where
	// If only one thread is printing to the console, then there is no reason to mutex the printf or cout statements
	// If a variable will be used by more than one thread then you probably want to mutex it
		// this is not always the case

// If you have one thread reading a variable and another thread storing in that same variable do you mutex it?
	// well, you probably don't
	// If the variable is of a basic data type and is small enough and properly aligned, reading it or storing to it is considered an Atomic Operation
		// This is architecture and compiler dependent, so be careful

// What is an Atomic Operation?

// The first thing to go over when talking about Atomic Operations is the fact that this is where we start to get into how hardware works
	// We won't go into too much detail about that, but it is important to understand a few things:
		// A cycle or instruction cycle is the process by which a computer retrieves a program instruction from its memory, determines what actions the instructions requires and carries out those actions
			// https://en.wikipedia.org/wiki/Instruction_cycle

// Atomic Vs Non-Atomic Operations
	// A Atomic operation is an operation that takes a single cycle
		// A single cycle means that no other threads can see the operation, since it is essentially done instantly
			// Essentially, there is no chance of another thread interrupting the operation
		// Example: num = 1;
			// This is a single store operation, thus making it atomic
// A non-atomic operation takes more than a single cycle
	// Example: int temp = num + 1; num = temp;
		// This first has a load operation on num. Then it stores temp into num.
		// While the individual operations are atomic, the overall operation isn't atomic
	// num++ may or may not be an atomic operation depending on the architecture of your CPU
		// This is good to understand for the future
	// For more info: http://preshing.com/20130618/atomic-vs-non-atomic-operations/
	// For more info on what operations are atomic: http://stackoverflow.com/questions/36624881/why-is-integer-assignment-on-a-naturally-aligned-variable-atomic
	// For more info on size constraints of variables: http://stackoverflow.com/questions/589575/what-does-the-c-standard-state-the-size-of-int-long-type-to-be

// Now back to the original point
	// If an operation is atomic, then there is no need to mutex it
	// This means that the below is usually a perfectly multithreaded function with no data races
		// A data race is when 2 threads are using affecting some shared data at the same time

	//Below is some example code:
	

static void threadFunction1Ver1();
static void threadFunction2Ver1();
static void threadFunction1Ver2();
static void threadFunction2Ver2();
void MutexConsiderations::considerationsExample()
{
	// Just something to show you the code
	std::thread t1(threadFunction1Ver1);
	std::thread t2(threadFunction1Ver1);

	t1.join();
	t2.join();
}

	
	int sharedInt1 = 0;
	void threadFunction1Ver1()
	{
		for(int i = 0; i < 100; i++)
		{
			sharedInt1 = rand() % 20;
		}
	}

	void threadFunction2Ver1()
	{
		printf("sharedInt = %d", sharedInt1);
	}
	

	// Lets look over the above code and talk about it
	// Is randNum, being shared between the threads?
		// No, then it doesn't need a mutex
	// Is sharedInt being shared between the threads?
		// Well, duh.
		// Does it need a mutex?
			// Well, lets look at what we are doing with it
				// Is "sharedInt = rand() % 20;" atomic?
					// For x86/x64 architecture it is guaranteed to be for a 32 bit integer
						// So, you could probably get away without mutexing this, but since depending on the CPU an int may not be guaranteed to be 32 bits we will
						// Where should the mutex go?
							// could put it around the the store statment, but then you are locking and unlocking 100 times
							// could mutex the whole loop, but then you serialize the threads(one thread goes and then another)
							// say, you don't care what value you read, you just want to print something
								// we can have it generate 100 numbers and then save the last one into the variable
									// this whole example is pretty contrived, so we will do this
									// Also,this means that you only lock and unlock the mutex once
				// Is "printf("sharedInt = %d", sharedInt);" atomic?
					// same exact considerations as above, so we could leave it unmutexed, but we won't

	// Safe version of the code:
	std::mutex mtx2;
	int sharedInt2 = 0;
	void threadFunction1Ver2()
	{
		int randNum = 0;
		// Loop through 100 times, updating a temp variable
		for(int i = 0; i < 100; i++)
		{
			randNum = rand() % 20;
		}

		mtx2.lock();
		// lock and then update the shared variable
			// probably not needed, but just in case
		sharedInt2 = randNum;
		mtx2.unlock();
	}

	void threadFunction2Ver2()
	{
		mtx2.lock();
		// Lock the print statement
			// probably not needed, but just in case
		printf("sharedInt = %d", sharedInt2);
		mtx2.unlock();
	}

	// If we know that the CPU and the architecture says an int's store and read operations are atomic then no mutexing needed
	// Also take a second and notice how we reordered everything and added a temporary variable
		// doing things like this can speed up the code enormously