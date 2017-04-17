#ifndef COURSEMANAGER_H
#define COURSEMANAGER_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Course.h"

class Course;
class CourseManager {
public:
	CourseManager() = default;
	CourseManager(const std::vector<Course>& courseVect):
		courseList(courseVect) {}

	//获取课程列表长度
	int getCourseNum() {return courseList.size();}

	//添加新课程
	void addCourse(const Course& course) {
		courseList.push_back(course);
	}
	void addCourse(const std::string& courseName) {
		courseList.push_back(Course(courseName));
	}

	//删除
	void removeLast() {
		courseList.pop_back();
	}
	void removeByName(const std::string &name);
	void removeById(int id);

	//打印课程列表信息
	void printAllCourse();
	void printCourse(const std::string& name);
	void printCourse(int id);
	void printLongNameCourse();
private:
	std::vector<Course> courseList;
};

#endif
