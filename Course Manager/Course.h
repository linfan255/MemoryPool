#ifndef COURSE_H
#define COURSE_H
#include <string>
#include <iostream>

class Course
{
	friend void read(std::istream& input, Course& course);
	friend std::ostream& operator << (std::ostream &out, const Course &course);
	static int currentId;
private:
	int id;
	std::string name;
public:
	Course();
	Course(std::string name);
	Course(const Course &course);
	
	int getId() const { return id; }
	std::string getName() const { return name; }
	void setName(const std::string newName) { name = newName; }
	
	virtual void printInfo() const;
};

class ProjectCourse: public Course
{
public:
	void setTag(const std::string &newTag) {tag = newTag;}
	std::string getTag() const {return tag;}
	virtual void printInfo() const override;
private:
	std::string tag;
};
#endif
