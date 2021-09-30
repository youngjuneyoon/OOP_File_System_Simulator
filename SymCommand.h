#pragma once
#include "AbstractCommand.h"


class SymCommand : public AbstractCommand{
public:
	SymCommand(AbstractFileSystem* fileSys);
	virtual int execute(std::string& CWD, std::string options) override;
	virtual void displayInfo() override;
	virtual ~SymCommand() = default;
private:
	AbstractFileSystem* fs;
};