#include "paws/ss.h"
#include <iostream>
#include <string>
 
using namespace std;

int main (int argc, char ** argv)
{
	ss ss;
	cout << ss.calcsensimilarity("I love you","I hate you") << endl;
}
