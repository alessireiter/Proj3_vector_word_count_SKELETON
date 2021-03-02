#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include "../includes/constants.h"
#include "../includes/array_functions.h"
#include "../includes/utilities.h"

/*============================================================================
 * The following are declarations for functions that I will test
 * Please provide the definitions in the
 * included cpp file, do not erase the stuff I put in there please
 * DO NOT MODIFY THIS FILE, I WILL USE MY OWN COPY
/============================================================================*/

using namespace std;
using namespace constants;

namespace KP {
const bool COULD_OPEN_FILE = true;
const bool COULD_NOT_OPEN_FILE = false;

//remove all elements from vector that tracks words and their occurrences
void clear(std::vector<constants::entry>  &entries){
	entries.clear();
}

//return how many unique words are in the vector
int getSize(std::vector<constants::entry>  &entries){
	return entries.size();
}

//get word at location i iff i<size(see above function), otherwise return the last word
//(this is lazy, should throw an exception instead)
std::string getWordAt(std::vector<constants::entry>  &entries, int i){
	if ((long unsigned int) i < entries.size()) {
		return entries.at(i).word;
	}
	return entries.back().word;
}

//get number_occurences at location i iff i<size(see above function), otherwise return the last number_occurences
//(this is lazy, should throw an exception instead)
int getNumbOccurAt(std::vector<constants::entry>  &entries,int i){
	if ((long unsigned int)i < entries.size()) {
			return entries.at(i).number_occurences;
		}
		return entries.back().number_occurences;
}

/*loop through the entire file, one line at a time
 * call processLine on each line from the file
 * returns false: myfstream is not open
 *         true: otherwise*/
bool processFile(std::vector<constants::entry>  &entries,std::fstream &myfstream){
	string line = "";
	if (myfstream.is_open()){
		while(getline(myfstream, line)){
			processLine(entries, line);
		}
		return COULD_OPEN_FILE;
	}
	return COULD_NOT_OPEN_FILE;
}

/*take 1 line and extract all the tokens from it
feed each token to processToken for recording*/
void processLine(std::vector<constants::entry>  &entries,std::string &myLine){
	stringstream ss(myLine);
	string tempToken;

	while(getline(ss, tempToken, constants::CHAR_TO_SEARCH_FOR)) {
		processToken(entries, tempToken);
	}
}

/*NOTE: first call strip_unwanted_chars from utilities to get rid of rubbish chars in the token
 * if the token is an empty string after this then return since we are not tracking empty strings
 *
 * Keep track of how many times each token seen, in other words look thru the entries vector that
 * holds entry structs to see if there is a struct that has entry.word==token,
 * if so increment entry.number_occurences, otherwise create a new entry struct for the token,
 * set entry.number_occurences=1 and add it to the entries vector*/
void processToken(std::vector<constants::entry>  &entries,std::string &token){

	if (!strip_unwanted_chars(token)){
		return;
	}

	for(long unsigned int var=0; var < entries.size(); ++var){

		if (entries[var].word == token || entries[var].word_uppercase == token) {
			entries[var].number_occurences += 1;
			return;
		}
	}

	struct constants::entry new_word;
		new_word.word = token;
		toUpper(token);
		new_word.word_uppercase = token;
		new_word.number_occurences = 1;
		entries.push_back(new_word);
}

bool compareAscending(const entry &x, const entry &y) {
	string x_word_upper = x.word;
	toUpper(x_word_upper);

	string y_word_upper = y.word;
	toUpper(y_word_upper);

	return x_word_upper < y_word_upper;
}
bool compareDescending(const entry &x, const entry &y) {
	string x_word_upper = x.word;
		toUpper(x_word_upper);

		string y_word_upper = y.word;
		toUpper(y_word_upper);

		return x_word_upper > y_word_upper;
}
bool compareOccurrences(const entry &x, const entry &y) {
	return x.number_occurences > y.number_occurences;
}

/*
 * Sort entries based on so enum value.
 * Please provide a solution that sorts according to the enum
 * The presence of the enum implies a switch statement based on its value
 * See the course lectures and demo projects for how to sort a vector of structs
 */
void sort(std::vector<constants::entry>  &entries, constants::sortOrder so){
	switch (so) {

	case NONE:
		break;
	case ASCENDING:
		sort(entries.begin(), entries.end(), compareAscending);
		break;
	case DESCENDING:
		sort(entries.begin(), entries.end(), compareDescending);
		break;
	case NUMBER_OCCURRENCES:
		sort(entries.begin(), entries.end(), compareOccurrences);
		break;
	default:
		return;
	}
}
}
