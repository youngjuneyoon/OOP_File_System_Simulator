#include "CPCommand.h"
#include "ProxyFile.h"
#include "ReadFileVisitor.h"
#include "ReadMetadataFileVisitor.h"
#include <iostream>
#include <sstream>


using namespace std;

CPCommand::CPCommand(AbstractFileSystem* filesys) :fs(filesys) {}

int CPCommand::execute(std::string& CWD, std::string options) {
	string fullPath = CWD;
	fullPath += "/";

	string temp;

	istringstream iss(options);

	//original file address
	iss >> temp;
	fullPath += temp;

	//getting new location
	iss >> temp;
	string newPath;
	newPath = temp;

	//if there is more than 3 arguments.
	if (iss >> temp) {
		return notavailablecommandoption;
	}

	//open the file to be duplicated
	AbstractFile* f = fs->openFile(fullPath);

	//if the file does not exists
	if (f == nullptr) {
		fs->closeFile(f);
		cout << "File Does Not Exists" << endl;
		return filedoesnotexist;
	}

	//clone the file
	AbstractFile* copiedOne = f->clone();

	//if clone is unsuccessful
	if (copiedOne == nullptr) {
		cout << "Directory cannot be copied" << endl;
		fs->closeFile(f);
		fs->closeFile(copiedOne);
		delete copiedOne;

		return cannotcopy;
	}

	//new path with new file name
	newPath += "/";
	newPath += copiedOne->getName();

	//add copied file to the new path
	int copyProcess = fs->addFile(newPath, copiedOne);

	//if the copied file is not added
	if (copyProcess != success) {
		cout << "Fail to copy the file to the directory" << endl;

		fs->closeFile(f);
		fs->closeFile(copiedOne);
		delete copiedOne;

		return failedtoadd;
	}
	
	fs->closeFile(f);
	fs->closeFile(copiedOne);

	return success;
};

void CPCommand::displayInfo() {
	cout << "The copy command will copy a file that exists in the file system and add the copy to the file system in a different location." << endl;
	cout << "cp <file_to_copy> <full_path_to_destination>" << endl;
};