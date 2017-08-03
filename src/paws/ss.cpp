#include "wikinet.h"
#include "reader.h"
#include "paws/ss.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include "lapos/lapos.h"

using namespace std;

double ss::calcsensimilarity(string sentence1,string sentence2)
{
	Lapos lapos;
	vector<vector<string>> words {};
	words = reader::read(ss::datapath + ss::filename, words);
	wiki::WikiNet net {words};
    
    // 	Getting all the data needed for the function : pos tagger model , dict etc...
	std::map< std::string, std::vector<std::string> > tagssen =  lapos.posTag_exec(sentence1);
	std::map< std::string, std::vector<std::string> > tagssen2 =  lapos.posTag_exec(sentence2);
	for (auto& pair : tagssen)
	{
	
		for (auto s : pair.second)
		{
			for (auto& pair2: tagssen2)
			{
				for (auto s2 : pair2.second)
				{
					if ( pair.first == pair2.first && s2!=s)
						pair.second.push_back(s2);
				
				}
			}	

		}
	}

	tagssen.insert(tagssen2.begin(),tagssen2.end());

    //	First , tagging every sentence and then, merging the tags :(example) Sentence1= NN:Table , Sentence2= NN:Pen , Merge= NN:Table,Pen.
	 vector < vector < std::string > > all;
        for (auto const& it : tagssen)
	{
		string word1=" ";
		string word2=" ";
		bool first=true;

        // Going through the map and comparing the words in each vector in map < int , vector <std::string>>;
		for (auto const& c : it.second )
		{
			vector < std::string > similar;
			word1=word2;
			word2 = c;
			bool weight = 1;
			sv::SparseVec<bool> v1;
			sv::SparseVec<bool> v2;
			wiki::WordNode* node1 = net.getNode(word1);
			wiki::WordNode* node2 = net.getNode(word2);
			if((node1 == nullptr || node2 == nullptr) && first==false){				
			}
			else{
				if (first == false)
				{
                    // Getting the words numbers from the dict and then comparing them.
					wiki::getScore(net, v1, node1, 3,4, weight, wiki::booleanScore);
					wiki::getScore(net, v2, node2, 3, 4, weight, wiki::booleanScore);
	
					bool isfound1=false;
					bool isfound2=false;
					int where=-1;

                    // Going through the vector all.
					for (int i=0;i<all.size();i++)
					{
						for (auto& s : all[i])
						{

							if (cosSim(v1,v2) >= 0.4 )
							{
							
									if (s == word1)
									{
										isfound1=true;
										where=i;

									}
									if (s == word2)
									{
										isfound2=true;
										where=i;
									}

							}
							else
							{		
								all[i].push_back(word2);
							}
						}
					}
					if (isfound1)
					{
						all[where].push_back(word2);
					}
					if (isfound2)
					{
						all[where].push_back(word1);
					}
					if (!isfound1 && !isfound2)
					{
						similar.push_back(word2);
						similar.push_back(word1);
						all.push_back(similar);
					}	

				}
				else
				{
					first=false;
					similar.push_back(word2);
					all.push_back(similar);
				}

			
			}
		}
	}

/*					If the words are similar it adds them to a vector of similar words and if they are not
 *			        	it creates a new one with the word
 *					that the program is checking in that moment. Then adding it to a vector named 'all'.
 */

	int sen1[all.size()];
	int sen2[all.size()];
	int i=0;
	int j=0;
	int sum=0;
	int summer=0;
	sentence1 = sentence1 + " ";
	sentence2 = sentence2 + " ";
	vector <std::string> sent1;
	vector <std::string> sent2;
	string word="";
	for (auto const& c : sentence1)
	{
		if (c != ' ')
			word = word + c;
		else
		{
			sent1.push_back(word);
			word="";
		}
	}
	for (auto const& c : sentence2)
	{
		if (c != ' ')
			word = word + c;
		else
		{
			sent2.push_back(word);
			word="";
		}
	}
    
    // Creating a vector for each sentence example: Sentence=How are you , Vector=<How,are,you>
	for (auto const& v :all)
	{

		for(auto const& s : v)
		{
			for (auto const& word : sent1)
			{
				if (word == s)
				{
					sum++;
				}
			}
			for (auto const& word : sent2)
			{
				if (word==s)
				{
					summer++;
					
				}
			}
		}
		sen1[i]=sum;
		sen2[j]=summer;
		sum=0;
		summer=0;
		i++;
		j++;

	}

/*	Counting how many times the words from all are in the sentence and adding it to an array
 * 	example: all=<<What>,<is>,<the>,<weather,temperature>>,Sentence=What is the weather,Array=[1,1,1,1]
 */
	double dot = 0.0, denom_a = 0.0, denom_b = 0.0 ;
    	 for(unsigned int i = 0u; i < all.size() ; ++i) {
        dot += sen1[i] * sen2[i] ;
        denom_a += sen1[i] * sen1[i] ;
        denom_b += sen2[i] * sen2[i] ;
    }
    return (dot / (sqrt(denom_a) * sqrt(denom_b))*100);
//  Using Cosine similarity in order to get a similarity score.	(sen1 ⋅ sen2) / ||sen1|| ||sen2||  

}
