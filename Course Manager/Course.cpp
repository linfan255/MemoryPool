#include "Course.h"

int Course::currentId = 1;

Course::Course()
{
	id = currentId++;
	name = "";
}

std::ostream &operator << (std::ostream &os, const Course& course)
{
	os << "Course: " << course.id << " : " << course.name;
	return os;
}

Course::Course(const Course& course)
{
	id = course.getId();
	name = course.getName();
}

void Course::printInfo() const
{
	std::cout << (*this) << std::endl;
}

void ProjectCourse::printInfo() const
{
	std::cout << (*this) << " : " << tag << std::endl;
}
