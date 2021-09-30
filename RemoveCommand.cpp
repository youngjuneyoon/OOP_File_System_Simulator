/*
Author: Jon Shidal
Purpose: CSE 332 lab 5
*/

#include "RemoveCommand.h"
#include<iostream>
#include<sstream>
#include"DirectoryFile.h"

using namespace std;

RemoveCommand::RemoveCommand(AbstractFileSystem* fileSys) : fs(fileSys) {}

// removes a file from the current working directory
int RemoveCommand::execute(std::string& CWD, std::string options) {
	string fullPath = CWD;
	fullPath += '/';

	//wraps into istringstream
	istringstream iss(options);

	//get filename
	string temp;
	iss >> temp;
	//append filename to path
	fullPath += temp;
	//get next cmd argument
	iss >> temp;
	//if third cmd argument is "-r"
	if (temp == "-r") {
		//cout << "dash R DETECTED" << endl;
		AbstractFile* f = fs->openFile(fullPath);

		//if the file is invalid
		if (f == nullptr) {
			fs->closeFile(f);
			return filedoesnotexist;
		}

		//read the contents of the file
		vector<char> contents = f->read();
		string str(contents.begin(), contents.end());

		istringstream iss(str);

		string temp;

		//till there are no files left
		while (iss >> temp) {

			AbstractFile* two = fs->openFile(fullPath + "/" + temp);
			DirectoryFile* isDir = dynamic_cast<DirectoryFile*>(two);

			if (isDir != nullptr) {
				//if size is not zero
				if (two->getSize() != 0) {
			
					fs->closeFile(f);
					fs->closeFile(two);

					//recursion happend here when opened file is directory, and is not empty
					execute(fullPath, temp+" -r");

					int loc = fullPath.find_last_of('/');

					string prevDir = fullPath.substr(0, loc);

					//if recursion reaches to the end
					if (prevDir == "root") {
						return success;
					}
				}
				//if size is bigger than 0
				else {
					fs->closeFile(two);
					int result = fs->deleteFile(fullPath + "/" + temp);

					if (result == AbstractFileSystem::fileisopen) {
						cout << "File Cannot be Deleted" << endl;
					}
				}
			}
			else {
				fs->closeFile(two);
				int result = fs->deleteFile(fullPath + "/" + temp);

				if (result == AbstractFileSystem::fileisopen) {
					cout << "File Cannot be Deleted" << endl;
				}
			}
		}


		//checks if the currently opened file's size is 0, then close the file and deletes. 
		if (f->getSize() == 0) {
			fs->closeFile(f);
			int result = fs->deleteFile(fullPath);

		}
		else {
			fs->closeFile(f);
		}

		int loc = fullPath.find_last_of('/');

		string prevDir = fullPath.substr(0, loc);

		//if recursion reached to the end. 
		if (prevDir == "root") {
			return success;
		}

		//if there is more upper directories to look at
		else {
			int loc2 = prevDir.find_last_of('/');

			string prevDir2 = prevDir.substr(0, loc2);

			string nextDir = prevDir.substr(loc2 + 1, string::npos);

			//recursion happens here. This step takes a look at upper directory. 
			execute(prevDir2, nextDir + " -r");
		}

		return success;
	}


	//regular rm (without -r)
	else {
		int result = fs->deleteFile(fullPath);
		if (result == AbstractFileSystem::filedoesnotexist) {
			cout << "File does not exist" << endl;
			return filedoesnotexist;
		}
		else if (result == AbstractFileSystem::fileisopen) {
			cout << "File is currently in use" << endl;
			return fileinuse;
		}
		return success;
	}


}
void RemoveCommand::displayInfo() {
	cout << "touch removes a file from the file system and then deletes the file" << endl;
	cout << "Usage: rm <filename>" << endl;
}