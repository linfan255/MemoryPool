#include "CourseManager.h"

void CourseManager::removeByName(const std::string& name) {
	auto it = courseList.begin();
	for(it = courseList.begin(); it != courseList.end(); ++it)
	  if(it->getName() == name)	break;
	if(it != courseList.end())	courseList.erase(it);
	else	std::cout << "connot find the course" << std::endl;
}

void CourseManager::removeById(int id) {
	auto it = courseList.begin();
	for(it = courseList.begin(); it != courseList.end(); ++it)
	  if(it->getId() == id)	break;
	if(it != courseList.end())	courseList.erase(it);
	else	std::cout << "connot find the course" << std::endl;
}

void CourseManager::printAllCourse() {
	for(auto it = courseList.begin(); it != courseList.end(); it++) {
		it->printInfo();
	}
}

void CourseManager::printCourse(const std::string& name) {
	for(auto it = courseList.begin(); it != courseList.end(); ++it) {
		if(it->getName() == name) {
			it->printInfo();
			break;
		}
	}
}

void CourseManager::printCourse(int id) {
	for(auto it = courseList.begin(); it != courseList.end(); ++it) {
		if(it->getId() == id) {
			it->printInfo();
			break;
		}
	}
}

void CourseManager::printLongNameCourse() {
	std::size_t maxLen = 0;
	for(auto it = courseList.begin(); it != courseList.end(); ++it) {
		maxLen = std::max(maxLen, (it->getName()).length());
	}

	for(auto it = courseList.begin(); it != courseList.end(); ++it) {
		if((it->getName()).length() == maxLen) {
			it->printInfo();
		}
	}
}

