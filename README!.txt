Documentation Author: Niko Procopi 2019

This tutorial was designed for Visual Studio 2017 / 2019
If the solution does not compile, retarget the solution
to a different version of the Windows SDK. If you do not
have any version of the Windows SDK, it can be installed
from the Visual Studio Installer Tool

Welcome to the Multithreading Tutorial!
Prerequesites: None

Multithreading allows a programmer to take full advantage of a CPU's power.
Every modern CPU has multiple threads. As of July 2019, the weakest and
cheapest line of CPUs that is currently in production is 
"Intel Atom for Internet Of Things", where each processor has at least two threads. 
That means any modern CPU can take advantage of multithreading.

As of 2017,  with C++17 introducing std::thread, multithreading has
never been easier before. If you have a long algorithm that takes 5 seconds,
you can run it 4 times, in 20 seconds, like this:

void Algorithm()
{
	// long algorithm
}

int main()
{
	Algorithm();
	Algorithm();
	Algorithm();
	Algorithm();
}

With multithreading, we can run this algorithm once on each CPU thread, all at the same time. 
Assuming we have four threads, you can run them all, and then wait until they are all done.
Rather than taking 20 seconds, this will take 6 seconds: 5 seconds for each algorithm to run
on each thread, plus 1 second to sync the threads up.

// same algorithm
void Algorithm()
{
	// long algorithm
}

int main()
{
	// here is how you start threads
	std::thread t1 = std::thread(Print);
	std::thread t2 = std::thread(Print);
	std::thread t3 = std::thread(Print);
	std::thread t4 = std::thread(Print);
	
	// check to make sure they're all done before continuing
	t1.join();
	t2.join();
	t3.join();
	t4.join();
}

If you want to take things to the next level, you can add parameters to your function, to
make each thread run the algorithm differently. For example, in games like Grand Theft Auto,
there are thousands of textures and 3D models in the game; loading each file one at a time
would take forever. They use multithreading to load multiple files at once.

// You can also pass parameters
void Algorithm(char* text)
{
	printf("%s\n", text);

	// long algorithm
}

int main()
{
	// here is how you start threads
	std::thread t1 = std::thread(Print, (char*)"Hello");
	std::thread t2 = std::thread(Print, (char*)"World");
	std::thread t3 = std::thread(Print, (char*)"Sup");
	std::thread t4 = std::thread(Print, (char*)"Hi");
	
	// check to make sure they're all done before continuing
	t1.join();
	t2.join();
	t3.join();
	t4.join();
}

