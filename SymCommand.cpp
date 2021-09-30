#include "SymCommand.h"
#include "TextFile.h"
#include "ImageFile.h"
#include "ProxyFile.h"
#include <sstream>
#include <iostream>

using namespace std;

SymCommand::SymCommand(AbstractFileSystem* filesys) :fs(filesys) {}


int SymCommand::execute(std::string& CWD, std::string options) {
	string fullPath = CWD; // ogPath
	fullPath += "/";

	string temp;

	istringstream iss(options);

	//original file address
	iss >> temp;
	fullPath += temp;

	//getting new location
	iss >> temp;
	string newPath; // DestinationPath
	newPath = temp;

	if (iss >> temp) {
		return notavailablecommandoption;
	}

	AbstractFile* newFileTest = fs->openFile(newPath);

	//if there is no file of the name
	if (newFileTest == nullptr) {
		cout << "Invalid Path" << endl;
		fs->closeFile(newFileTest);
		return filedoesnotexist;
	}
	else {
		fs->closeFile(newFileTest);
	}

	// opening original file
	AbstractFile* f = fs->openFile(fullPath);

	//dynamic casting of the opened file
	ProxyFile* isProxy = dynamic_cast<ProxyFile*>(f);

	//if the file does not open
	if (f == nullptr) {
		cout << "File Does Not Exists" << endl;
		return filedoesnotexist;
	}

	//if it is a proxy file
	else if (isProxy != nullptr) {
		fs->closeFile(f);

		//making duplicate of the original proxy file
		AbstractFile* proxDuplicate = new ProxyFile(f);

		//path for the new duplicate file
		string proxDuplicatePath = newPath + "/" + proxDuplicate->getName();

		//add the duplicate file
		int symDuplicate = fs->addFile(proxDuplicatePath, proxDuplicate);

		if (symDuplicate != success) {
			delete proxDuplicate;
			return failedtoadd;
		}
		else {
			return success;
		}
	}
	//if its not a proxy file
	else {
		AbstractFile* ogClone = f->clone();

		if (ogClone == nullptr) {
			fs->closeFile(f);
			return cannotcopy;
		}
		//clone successful
		//delete the old txt or img file
		fs->closeFile(f);
		fs->deleteFile(fullPath);

		//making the first proxy file
		AbstractFile* proxOne = new ProxyFile(ogClone);

		//adding file to system
		int symOne = fs->addFile(fullPath, proxOne);


		if (symOne != success) {
			fs->closeFile(ogClone);
			delete ogClone; // delete ogClone because not added
			return failedtoadd;
		}
		else { // adding proxOne successful
		//duplicate proxOne to create proxTwo
			AbstractFile* proxTwo = new ProxyFile(proxOne);
			string proxTwoPath = newPath + "/" + proxTwo->getName();
			int symTwo = fs->addFile(proxTwoPath, proxTwo);
			if (symTwo != success) {
				return notavailablecommandoption;
			}
			else {
				fs->closeFile(f);
				fs->closeFile(proxOne);
				return success;

			}

		}

	}


};


void SymCommand::displayInfo() {
	cout << "sym creates a symbolic link to the file. " << endl;
	cout << "Usage: sym <filename> <new symlink path>" << endl;
};