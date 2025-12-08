#include <iostream>
#include "animateText.h"
#include <string>
#include <thread>
#include <chrono>
using namespace std;

// function to output as if it was being typed
void type_text(string text)
{
	// loop through each character in the text
	for (size_t i = 0; i < text.size(); ++i)
	{
		// output one character
		// flush to make sure the output is not delayed
		// flush is mainly important here because im trying to get the text to appear at the right times
		cout << text[i] << flush;
		
		// sleep 10 milliseconds
		std::this_thread::sleep_for(std::chrono::milliseconds(40)); // use Sleep on windows
	}
}