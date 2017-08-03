#include <vector>
#include <stdio.h>
#include <fstream>
#include <map>
#include <list>
#include <set>
#include <iomanip>
#include <iostream>
#include <cfloat>
#include <sstream>
#include <sys/time.h>

#include "crf.h"
#include "common.h"

using namespace std;

class Lapos
{
    public:
    Lapos(void);
    std::map< std::string, std::vector<std::string> > posTag_exec(string sen);
/*
void crf_decode_lookahead(Sentence &s, CRF_Model &m, vector< map<string, double> > &tagp);
void read_WordNet(const string &wordnetdir);
void loadModel();
void loadFromFile(const string file_name);
void tokenize(const string &s, vector<Token> &bt, const bool  usr_upenn_tokenizer);
 */        
};
