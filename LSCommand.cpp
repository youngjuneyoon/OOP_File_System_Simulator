/*
Author: Jon Shidal
Purpose: CSE 332 lab 5
*/

#include "LSCommand.h"
#include "ReadFileVisitor.h"
#include "ReadMetadataFileVisitor.h"
#include<iostream>
#include<sstream>

using namespace std;

LSCommand::LSCommand(AbstractFileSystem * fileSys) : fs(fileSys) {}

int LSCommand::execute(std::string& CWD, std::string options) {
	AbstractFile* f = fs->openFile(CWD);
	if (f == nullptr) { // file creation failed
		cout << "failed to open directory" << endl;
		return directorydoesnotexist;
	}

	//cout << options<<"HERE!!";

	if (options == "") {
		ReadFileVisitor reader;
		f->accept(&reader);
		fs->closeFile(f);
		return success;
	}
	else if (options == "-l"){
		vector<char> contents = f->read();
		string str(contents.begin(), contents.end());

		istringstream iss(str);

		string temp;

		while (iss >> temp) {
			AbstractFile* b = fs->openFile(CWD + "/" + temp);
			ReadMetadataFileVisitor reader;
			b->accept(&reader);
			fs->closeFile(b);
		}
		fs->closeFile(f);

		return success;
	}
	else {
		fs->closeFile(f);
		return notavailablecommandoption;
	}

}
void LSCommand::displayInfo() {
	cout << "lists the contents of the current directory" << endl;
	cout << "Usage: ls" << endl;
}