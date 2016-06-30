#include "ClassDeclarations.h"

static void nothing(){
}

void JoinVSDetach::joinVSDetachExample(){
	//Join
	//Makes the currently executing thread wait for another thread to finish processing
#pragma region Join
	thread joinTrial(nothing);

	//Again, checking to make sure it can still be joinned
	if (joinTrial.joinable())
		joinTrial.join();
#pragma endregion

	//Detach
	//Seperates the thread from the currently executing thread to allow them to run independently from one another
#pragma region Detach
	thread detachTrial(nothing);
	detachTrial.detach();
	//Now the thread is running seperately
	//It will run seperately until the foo function completes
	//Detaching is good if you need to run something in the background, but don't wan the main thread to wait on it
	//This means that if the main thread ends, then the detached thread's current action will be paused and the program will end
	//This can be an issue, since if this scenario happens, the thread will not cleanup,
	//meaning if there are deallocations that need to happen, they won't

#pragma endregion
}