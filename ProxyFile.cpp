#include "ProxyFile.h"
#include "AbstractFileVisitor.h"
#include <iostream>
#include <sstream>

using namespace std;

ProxyFile::ProxyFile(AbstractFile* f) {
	name = f->getName();

	ProxyFile* isProxy = dynamic_cast<ProxyFile*>(f);


	// if it is textfile or image file
	if (isProxy == nullptr) {
		//dynamically allocating linkcount int
		linkCount = new int(1);
		ogFile = f;
	}
	//if its proxyfile
	else{
		this->linkCount = isProxy->linkCount;
		//increment linkcount
		*linkCount = *linkCount + 1;
		this->ogFile = isProxy->ogFile;
	}

}; 


ProxyFile::~ProxyFile() {
	*linkCount = *linkCount - 1;
	if (*linkCount == 0) {
		//prevent memory leak
		delete ogFile;
		delete linkCount;
	}

};

vector<char> ProxyFile::read() { return ogFile->read(); };


int ProxyFile::write(vector<char> g) { return ogFile->write(g); };
int ProxyFile::append(vector<char> g) { return ogFile->append(g); }; 
unsigned int ProxyFile::getSize() { return ogFile->getSize();};
string ProxyFile::getName() { return name; };


void ProxyFile::accept(AbstractFileVisitor* fv) {
	return ogFile->accept(fv);
};


AbstractFile* ProxyFile::clone() {
	return ogFile->clone();
};


int ProxyFile::addChild(AbstractFile*) { return notacomposite; };
int ProxyFile::removeChild(std::string name) { return notacomposite; };
void ProxyFile::setParent(AbstractFile* p) { parent = p; };
AbstractFile* ProxyFile::getChild(std::string name) { return nullptr; };
AbstractFile* ProxyFile::getParent() { return parent; };