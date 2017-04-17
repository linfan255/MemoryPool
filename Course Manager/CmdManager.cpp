#include "CmdManager.h"

void CmdManager::init() {
	const std::string cs = "c++";
	manager.addCourse(cs);
	cmdMap.insert(std::make_pair(Cmd_printHelp, "help info"));
	cmdMap.insert(std::make_pair(Cmd_printCourse, "print all course info"));
	cmdMap.insert(std::make_pair(Cmd_printCourseNum, "print the course number"));
	cmdMap.insert(std::make_pair(Cmd_printLongName, "print the course which has the longest name"));
	cmdMap.insert(std::make_pair(Cmd_removeLastCourse, "remove the last course"));
	cmdMap.insert(std::make_pair(Cmd_removeByName, "remove course by name"));
	cmdMap.insert(std::make_pair(Cmd_removeById, "remove course by id"));
	cmdMap.insert(std::make_pair(Cmd_addCourse, "add course"));
}

bool CmdManager::handleCmd(const CourseCmd cmd, int id , const std::string& courseName) {
	auto iter = cmdMap.find(cmd);
	if(iter == cmdMap.end()) {
		std::cout << "no such command" << std::endl;
		return true;
	}

	switch(cmd) {
		case Cmd_printHelp: printAllHelp();	break;
		case Cmd_printCourse: manager.printAllCourse();	break;
		case Cmd_printCourseNum:	
			std::cout << manager.getCourseNum() << std::endl;
			break;
		case Cmd_printLongName:
			manager.printLongNameCourse();
			break;
		case Cmd_removeLastCourse:
			manager.removeLast();
			break;
		case Cmd_removeByName:
			manager.removeByName(courseName);
			break;
		case Cmd_removeById:
			manager.removeById(id);
			break;
		case Cmd_addCourse:
			manager.addCourse(courseName);
			break;
		case Cmd_exit:	return false;
		default: break;
	}
}

void CmdManager::printAllHelp() const {
	for(auto it = cmdMap.begin(); it != cmdMap.end(); ++it){
		std::cout << it->first << ":" << it->second << std::endl; 
	}
}

void CmdManager::printCmdHelp(const CourseCmd cmd) const {
	auto it = cmdMap.find(cmd);
	if(it == cmdMap.end()) {
		std::cout << "sorry! please enter the legal command..." << std::endl;
	} else {
		std::cout << cmd << ":" << it->second << std::endl;
	}
}
