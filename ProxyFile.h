#pragma once
#include "AbstractFile.h"
#include "TextFile.h"
#include "ImageFile.h"
#include <vector>
#include <string>


class ProxyFile : public AbstractFile {
public:
	//ProxyFile(std::string n);
	ProxyFile(AbstractFile* f);
	virtual std::vector<char> read() override;
	virtual int write(std::vector<char>) override; // re-writes file
	virtual int append(std::vector<char>) override; // appends to current contents
	virtual unsigned int getSize() override;
	virtual std::string getName() override;

	virtual ~ProxyFile();

	// visitor pattern function
	virtual void accept(AbstractFileVisitor*) override;
	// clone function
	virtual AbstractFile* clone() override;
	// request function - gunny
	// (AbstractFile* ogFile) ?

	/*virtual void linkCounter() override;*/
	//// function to keep track of link counts
	//virtual int linkCount(AbstractFile* f) = 0;

protected:
	virtual int addChild(AbstractFile*) override;
	virtual int removeChild(std::string name) override;
	virtual void setParent(AbstractFile* p) override;
	virtual AbstractFile* getChild(std::string name) override;
	virtual AbstractFile* getParent() override;
	

private:
	std::vector<char> contents;
	std::string name;
	AbstractFile* parent;
	
	//Step 6
	//keeping track of link counts
	int* linkCount;
	//static int* linkCount; // pointer because to dynamically allocate address
	AbstractFile* ogFile;
};