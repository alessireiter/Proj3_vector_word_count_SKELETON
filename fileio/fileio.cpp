#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "../includes/constants.h"
#include "../includes/fileio.h"
#include "../includes/utilities.h"

using namespace std;
using namespace constants;


const bool COULD_OPEN_FILE = true;
const bool COULD_NOT_OPEN_FILE = false;

/*if you are debugging the file must be in the project parent directory
  in this case Project2 with the .project and .cProject files*
  returns True - file opened successfully
          False - file not opened*/
bool openFile(std::fstream& myfile, const std::string& myFileName, ios_base::openmode mode){

	myfile.open(myFileName.c_str(), mode);

	if (!myfile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	return COULD_OPEN_FILE;
}

/*iff myfile is open then close it*/
void closeFile(std::fstream& myfile){
	if (myfile.is_open()){
		myfile.close();
	}
}

/* serializes all content in entries to file outputfilename
 * check out utils for helpful type conversion functions
 * BTW serialize means the process of translating a data structure
 * into a format that can be stored in a file
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in the vector entries
 * 			SUCCESS if all data is written and outputfilename closes OK
 * */
int writetoFile(std::vector<constants::entry>  &entries, const std::string &outputfilename){
	fstream myfile;

	ios_base::openmode mode = ios_base::out;
	bool file_opened = openFile(myfile, outputfilename, mode);
	cout << file_opened << endl;
	if (!file_opened) {
		return FAIL_FILE_DID_NOT_OPEN;
	}

	if (entries.size() == 0){

		return FAIL_NO_ARRAY_DATA;
	}

	for(long unsigned int i = 0; i < entries.size(); ++i) {
		myfile << entries[i].word + " " + intToString(entries[i].number_occurences) + "\n";
	}
	closeFile(myfile);

	return SUCCESS;
}
