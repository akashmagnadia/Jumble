//Author:Akash Magnadia
//Author: Akash Magnadia
//Jumble Program

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

/*
*  this function rearranged the characters in a string
*    so that they are sorted (according to their ASCII
*    value).
*
*  Resource:  https://en.cppreference.com/w/cpp/algorithm/sort
*
*  Note:  this function is not actually used the the program
*    in this file.  But you might find it useful... :)
*/
void ssort(std::string& s) {
	/*
	 strings are "iterable" objects and so have the begin()
	 and end() functions.  These functions (in a pretty
	 abstract way) return "iterators" which specify the
	 "beginning" and "end" of the associated object).

	 Thus, this call is asking the sort function to sort
	 the entire string s.
  */
	std::sort(s.begin(), s.end());
}

/*
*   usage:   ./freq <filename>
*
*   example:  ./freq words.txt
*
*/
int main(int argc, char* argv[])
{
	std::unordered_map<std::string, std::vector<std::string>> word2word;
	std::unordered_map<std::string, int> word2freq;
	std::ifstream file;
	std::string word;

	if (argc != 2) {
		std::cout << "usage:  ./freq <filename>\n";
		std::cout << "goodbye\n";
		return 1;
	}

	/*
  *  argv[1] is a C-string which is the filname specified
  *    by the user.  Let's try to open it.
  */

	file.open(argv[1], std::ios::in);

	if (!file.is_open()) {
		std::cout << "Error: could not open file '" <<
			argv[1] << "'\n";
		std::cout << "goodbye\n";
		return 1;
	}

	std::cout << "reading input file...\n";

	std::string sortedWord = "";
	int num_words = 0; //keeps track of how many words were inserted
	int num_classes = 0; //keeps track how many keys were made
	int size_largest_class = 0;
	std::string sortedWord_largest_class = ""; //keeps track of the largest class or key with most value first in the list

	while (file >> word) {

		sortedWord = word;
		ssort(sortedWord); //sort the word
		

		if (word2freq.count(sortedWord) == 0) { //doesn't contain word as the key value in the vector
			//first time inputting that key
			num_classes++;
			word2freq[sortedWord] = 1;
		}
		else {
			word2freq[sortedWord]++;
		}

		if (word2freq[sortedWord] > size_largest_class) { //check if sortedword has the most values
			size_largest_class = word2freq[sortedWord]; //new largest class
			sortedWord_largest_class = sortedWord; //key of that largest class
		}

		num_words++; //amount of words processed
		word2word[sortedWord].push_back(word); //add word to the key which is sorted word
	}

	std::cout <<
		"enter a word and I will tell you what I know about it\n";
	std::cout <<
		"  when you are done, type ctrl-d (ctrl-z on windows)\n\n";
	std::cout << "> ";

	while (std::cin >> word) {

		sortedWord = word;
		ssort(sortedWord); //sort the word before look for key

		if (word2freq.count(sortedWord) == 0) { //if the key is not found
			std::cout << "no anagrams found...try again" << std::endl;
		}
		else
		{
			std::cout << "English Anagrams Found: " << std::endl;
			
			for (std::pair<std::string, std::vector<std::string>> entry : word2word) {
				if (entry.first.c_str() == sortedWord) {
					for (auto p : entry.second) {
						std::cout << "   " << p << std::endl; //print value of the anagrams in the vector
					}
					break;
				}
			}
		}

		std::cout << "> ";
	}

	std::cout << "REPORT: " << std::endl << std::endl;
	std::cout << "num_words             :  " << num_words << std::endl;
	std::cout << "num_classes           :  " << num_classes << std::endl;
	std::cout << "size-of-largest-class :  " << size_largest_class << std::endl;

	std::cout << "largest-class key     :  '";
	std::cout << sortedWord_largest_class;
	std::cout << "'" << std::endl;

	std::cout << "members of largest class:" << std::endl << std::endl;
	for (std::pair<std::string, std::vector<std::string>> entry : word2word) {
		if (entry.first.c_str() == sortedWord_largest_class) { //if the largest sorted class is found
			for (auto p : entry.second) {
				std::cout << "   '" << p << "'" << std::endl; //print value of the anagrams in the vector
			}
		}
	}
}
