#include "DSCommand.h"
#include "ReadFileVisitor.h"
#include "ReadMetadataFileVisitor.h"
#include <iostream>
#include <sstream>


using namespace std;

DSCommand::DSCommand(AbstractFileSystem* filesys) :fs(filesys) {}

int DSCommand::execute(std::string& CWD, std::string options) {

	string fullPath = CWD;
	fullPath += '/';

	//wraps into istringstream
	istringstream iss(options);

	//get filename
	string temp;
	iss >> temp;

	string filename = temp;
	//append filename to path
	fullPath += temp;
	//get next cmd argument
	iss >> temp;
	string args = temp;
	//if third cmd argument is "-d"

	string extra;

	iss >> extra;

	//if there is extra command
	if (extra.size() != 0) {
		cout << "Invalid command input" << endl;
		return notavailablecommandoption;
	}

	//if third argument is not equal to "-d"
	if (temp != filename) {
		if (temp != "-d") {
			cout << "Invalid input. example: ds <filename> [-d]" << endl;
			return notavailablecommandoption;
		}
	}

	//open the selected file
	AbstractFile* f = fs->openFile(fullPath);

	// file creation failed
	if (f == nullptr) { 
		cout << "failed to open the file" << endl;
		return directorydoesnotexist;
	}

	//create filevisitor object
	ReadFileVisitor reader;

	//for unformatted option
	if (temp == "-d") {
		//if the file is imageFile
		if (f->getName().find(".img") != string::npos) {
			vector<char> contents = f->read();
			string str(contents.begin(), contents.end());
			istringstream iss(str);
			string temp;

			while (iss >> temp) {
				cout << temp << ' '; //putting ' ' since istringstream ignores whitespaces. 
			}
			cout << '\n';
			fs->closeFile(f);
			return success;
		}
		//if the file is textFile
		else {
			f->accept(&reader);
			fs->closeFile(f);
			return success;
		}
	}
	//regular ds function without "-d"
	else {
		f->accept(&reader);
		fs->closeFile(f);
		return success;
	}
};

void DSCommand::displayInfo() {
	cout << "Displays file content" << endl;
	cout << "Usage: ds <filename> [-d]" << endl;
}