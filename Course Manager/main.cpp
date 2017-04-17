#include <iostream>
#include <string>
#include "CmdManager.h"

using namespace std;

int main() {
	CmdManager cmdManager;
	cmdManager.init();

	cmdManager.printAllHelp();

	cout << "new command:";

	int cmd, id;
	string courseName;
	while(cin >> cmd) {
		if(cmd == 9)	break;

		if(cmd == 5 || cmd == 7) {
			cout << "please enter the course's name:";
			cin >> courseName;
			cmdManager.handleCmd((CourseCmd)cmd, 0, courseName);
		} else if(cmd == 6) {
			cout << "please enter the course's id you want to remove:";
			cin >> id;
			cmdManager.handleCmd((CourseCmd)cmd, id, "");
		} else {
			cmdManager.handleCmd((CourseCmd)cmd);
		}
		cout << "------------------------" << endl;
		cout << "New Command:";
	}		
	return 0;
}
