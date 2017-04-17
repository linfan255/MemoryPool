#include "Course.h"

int Course::currentId = 1;

Course::Course()
{
	id = currentId++;
	name = "";
}

Course::Course(std::string CourseName) {
	id = currentId++;
	name = CourseName; 
}

std::ostream &operator << (std::ostream &os, const Course& course)
{
	os << "Course: " << course.id << " : " << course.name;
	return os;
}

Course::Course(const Course& course)
{
	id = course.id;
	name = course.name;
}

void Course::printInfo() const
{
	std::cout << (*this) << std::endl;
}

void ProjectCourse::printInfo() const
{
	std::cout << (*this) << " : " << tag << std::endl;
}
