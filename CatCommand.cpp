#include <iostream>
#include <sstream>
#include "CatCommand.h"
#include "ReadFileVisitor.h"
#include "ReadMetadataFileVisitor.h"

using namespace std;

CatCommand::CatCommand(AbstractFileSystem* fileSys) : fs(fileSys) {}

int CatCommand::execute(std::string& CWD, std::string options) {
	string fullPath = CWD;
	fullPath += '/';

	//wraps into istringstream
	istringstream iss(options);
	string args; 
	string filename;
	string extra;

	//get filename
	string temp;
	iss >> temp;
	filename = temp;
	//append filename to path
	fullPath += temp;
	//get next cmd argument
	iss >> temp;
	args = temp;
	//if third cmd argument is "-a"
	
	//if there are extra invalid input
	iss >> extra;

	if (extra.size() != 0) {
		cout << "Invalid command input" << endl;
		return notavailablecommandoption;
	}

	if (temp == "-a") {
		// displaying the contents of the file (bytes, not the formatted output)
		AbstractFile* f = fs->openFile(fullPath);

		if (f == nullptr) {
			cout << "File does not exist," << endl;
			cout << "Enter existing file name" << endl;
			return filedoesnotexist;
		} 
		else {
		if (f->getName().find(".txt") != string::npos) {
			vector<char> contents = f->read();
			string str(contents.begin(), contents.end());
			cout << fullPath << '\n';
			cout << str << '\n';

			string temp;  // temporarily stores inputs

			string temp2;

			cout << "Enter data you would like to append to the existing file. Enter :wq to save the file and exit, enter :q to exit without saving" << endl;

			while (1) {
				string input;
				getline(cin, input);
				temp = input;
				temp += '\n';

				if (input == ":wq") {
					vector<char> inputContents(temp2.begin(), temp2.end());
					f->append(inputContents);
					vector<char> saved = f->read();
					string savedStr(saved.begin(), saved.end());

					fs->closeFile(f); // WITHOUT THIS, EXITS IMMEDIEATLY
					return success;
				}
				else if (input == ":q")
				{	
					// SHOULD BE WITHOUT SAVING
					fs->closeFile(f); // WITHOUT THIS, EXITS IMMEDIEATLY
					return success;
				}
				else {
					temp2 += temp;
				}
			}
			return success;
		}else if (f->getName().find(".img") != string::npos) {
			cout << "Img file cannot be appended" << endl;
			fs->closeFile(f);
			return notavailablecommandoption;
		}
		else {
			cout << "Only Text file can be appended" << endl;
			fs->closeFile(f);
			return notavailablecommandoption;
		}
		return success;
		}
		
	}

	// cat without -a
	else if (filename == args){

		AbstractFile* f = fs->openFile(fullPath);

		if (f == nullptr) {
			cout << "File does not exist," << endl;
			cout << "Enter existing file name" << endl;
			return filedoesnotexist;
		}

		string temp;  // temporarily stores inputs

		if (f->getName().find(".img") != string::npos) {
			vector<char> contents = f->read();
			string str(contents.begin(), contents.end());
			cout << fullPath << '\n';
			cout << "Enter data you would like to append to the existing file. Enter :wq to overwrite, enter :q to exit without saving" << endl;

			while (1) {
				string input;
				getline(cin, input);

				if (input == ":wq") {
					
					if (temp.empty() == true) {
						f->write(contents);

						fs->closeFile(f);
						return success;
					}
					vector<char> inputContents;
					for (size_t i = 0; i < temp.size(); i++)
					{
						inputContents.push_back(temp[i]);
					}

					f->write(inputContents); // overwrite

					fs->closeFile(f);
					return success;
				}
				else if (input == ":q") {

					fs->closeFile(f);
					return success;
				}
				else {
					temp += input;
				}

			}

		}
		else if(f->getName().find(".txt") != string::npos) {
			vector<char> contents = f->read();
			string str(contents.begin(), contents.end());
			cout << fullPath << '\n';
			cout << "Enter data you would like to append to the existing file. Enter :wq to overwrite, enter :q to exit without saving" << endl;

			while (1) {
				string input;
				getline(cin, input);
			
				if (input == ":wq") {
					vector<char> inputContents(temp.begin(), temp.end());
					f->write(inputContents); // overwrite
					fs->closeFile(f);
					return success;
				}
				else if (input == ":q") {
					fs->closeFile(f);
					return success;
				}
				else {
					temp += input;
					temp += '\n';
				}
			}
		}

		else {
			cout << "Only Text file and Image file can be edited" << endl;
			fs->closeFile(f);
			return notavailablecommandoption;
		}

		return success;
	}
	else {
		cout << "Command Format: cat <filename> [-a]" << endl;
		return notavailablecommandoption;
	}

}

void CatCommand::displayInfo() {
	cout << "appends to files or overwrites files" << endl;
	cout << "Usage: cat <filename> [-a]" << endl;
	cout << "Enter: wq to save the file and exit, enter :q to exit without saving" << endl;
}