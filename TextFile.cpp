/*
Author: Jon Shidal
Purpose: CSE 332 lab 5, defines the TextFile class
*/

#include "TextFile.h"
#include "AbstractFileVisitor.h"
#include<iostream>

using namespace std;

TextFile::TextFile(string n) : name(n), parent(nullptr) {}

unsigned int TextFile::getSize() {
	return contents.size();
}

string TextFile::getName() {
	return name;
}

vector<char> TextFile::read() {
	return contents;
}

void TextFile::accept(AbstractFileVisitor* fv) {
	if (fv) { fv->visit(this); }
}

AbstractFile* TextFile::clone() {
	TextFile* newOne = new TextFile(*this);
	//AbstractFile* nullpointer = nullptr;
	newOne->setParent(nullptr);

	return newOne;

}


int TextFile::write(vector<char> data) {
	contents = data;
	return success;
}

int TextFile::append(vector<char> data) {
	for (size_t i = 0; i < data.size(); ++i) {
		contents.push_back(data[i]);
	}
	return success;
}

int TextFile::addChild(AbstractFile*) {
	return notacomposite;
}

int TextFile::removeChild(string name) {
	return notacomposite;
}

AbstractFile* TextFile::getChild(std::string name) {
	return nullptr;
}

AbstractFile* TextFile::getParent() {
	return parent;
}
void TextFile::setParent(AbstractFile* p) {
	parent = p;
}