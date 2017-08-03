#include <iostream>
#include <string>

using namespace std;

class ss{
	private:
		string datapath {"../data/"};
		string filename {"wnsyns.tsv"};
	public:
		double calcsensimilarity (string sentence1, string sentence2);
};
