#ifndef CMDMANAGER_H
#define CMDMANAGER_H

#include "CourseManager.h"
#include <map>
#include <string>
#include "Cmd.h"

class CourseManager;
class CmdManager
{
private:
	CourseManager manager;
	std::map<CourseCmd, std::string> cmdMap;

public:
	CmdManager() = default;
	void init();
	void printAllHelp() const;
	void printCmdHelp(const CourseCmd cmd) const;
	bool handleCmd(const CourseCmd cmd, int id = 0, const std::string& courseName = "");
	CourseManager& getCourseManager() { return manager; }
};
#endif 
