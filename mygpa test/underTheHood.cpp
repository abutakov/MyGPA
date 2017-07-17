

#include "Header.h"
#include <iostream>
#include <iomanip>

// "<<" cout ’s stream insertion operator overload
ostream &operator<< (ostream &strm, const ClassInfo &obj)
{
	cout
		<< "|      "
		<< setw(30) << left << obj.className
		<< setw(15) << left << obj.classCode
		<< setw(10) << left << obj.creditHours << "     |\n\n";
	return strm;
}

int getInteger() {
	int answer;
	cin.clear();
	//cin.ignore(80, '\n');
	cin >> answer;

	if ((int)answer != answer) {
		string expectionString = "ERROR: That was NOT an integer! Please enter an integer. ";
		throw expectionString;
	}
	return answer;
}



void ClassInfo::setClassName(string n)
{
	className = n;
}
void ClassInfo::setClassCode(string s) 
{
	classCode = s;
}

void ClassInfo::setCreditHours(int h)
{
	if (h < 0 || h > 4)
	{
		creditHours = 0;
		
		// throw exception
	}
	else creditHours = h;
}

void printArray(ClassInfo obj[], int num) // ------------------------------------------  RECURSIVE FUNCTION
{
	static int i = 0;
	if (i == 0) {
		 cout << setw(60) << "\n=========================== Classes Left ===============================\n\n";
		cout
			<< "|       "
			<< setw(25) << left << "COURSE NAME  "
			<< setw(15) << left << "COURSE CODE    "
			<< setw(10) << left << "CREDITS   " << "         |\n\n";
	}
	if (num > 0) {

		cout << obj[i];

		i++;
		printArray(obj, num - 1);
	}
	else {
		i = 0;
		cout << setw(60) << "===================================================================\n";
	}
}
void printArrayWithGrades(ClassInfo obj[], int num) // ------------------------------------------  RECURSIVE FUNCTION
{
	static int i = 0;
	if (i == 0) {
		cout << "\n\n" << setw(60) << "\n======================= Your Transcript ============================\n\n";
		cout
			<< "|       "
			<< setw(27) << left << "COURSE NAME  "
			<< setw(12) << left << "COURSE CODE    "
			<< setw(10) << left << "CREDITS   "
			<< setw(10) << left << "GRADE   " << " |\n\n";
	}
	if (num > 0) {
		cout
			<< "|      "
			<< setw(30) << left << obj[i].className
			<< setw(15)  << obj[i].classCode
			<< setw(10) << left << obj[i].creditHours
			<< setw(9) << left << obj[i].earnedGrade << "|\n\n";
		i++;
		printArrayWithGrades(obj, num - 1);
	}
	else
	{
		i = 0;
		cout << setw(60) << "===================================================================\n";
	}
}

double calculateGPA(ClassInfo obj[], int num) 
{
	double 
		total = 0, 
		totalHours = 0;

	for (int i = 0; i < num; i++)
	{
		total += obj[i].earnedGrade * obj[i].creditHours;
		totalHours += obj[i].creditHours;
	}
	return total / totalHours;
}

double addAndCalculateGPA(ClassInfo obj1[], ClassInfo obj2[], int num1, int num2)
{
	double
		total = 0, 
		totalHours = 0;

	for (int i = 0; i < num1; i++)
	{
		total += obj1[i].earnedGrade * obj1[i].creditHours;
		totalHours += obj1[i].creditHours;
	}
	for (int i = 0; i < num2; i++)
	{
		total += obj2[i].earnedGrade * obj2[i].creditHours;
		totalHours += obj2[i].creditHours;
	}
	return total / totalHours;
}


void ClassInfo::setEarnedGrade(const char * g)
{
	if (g[0] == 'A') {
		if (g[1] == '-')
			earnedGrade = 3.7;
		else earnedGrade = 4.0;
	}
	else if (g[0] == 'B')
	{
		if (g[1] == '-')
			earnedGrade = 3.33;
		earnedGrade = 3.0;
	}
	else if (g[0] == 'C')
	{
		if (g[1] == '-')
			earnedGrade = 1.67;
		earnedGrade = 2.0;
	}

	else if (g[0] == 'C') {
		if (g[1] == '-')
			earnedGrade = 1.67;
		earnedGrade = 2.0;
	}
	else if (g[0] == 'D') {
		if (g[1] == '-')
			earnedGrade = .67;
		earnedGrade = 1.0;
	}
	else   earnedGrade = 0.0;
	
}

bool ClassInfo::isPassed() {
	if (getEarnedGrade() != 'F' || getEarnedGrade() != 'D')
		return true;
	else return false;
}

double ClassInfo::getEarnedGrade() { return earnedGrade; }

string ClassInfo::getClassCode() { return classCode; }

string ClassInfo::getClassName() { return className; }

int ClassInfo::getCreditHours() { return creditHours;  }



void Student::getStudID()
{
	const int STUD_ID_SIZE = 8;
	char studentID[STUD_ID_SIZE];
	bool isValidNum = false;

	cout << "Enter you Student ID: ";
	while (!isValidNum) {

		cin.getline(studentID, STUD_ID_SIZE);
		if (isValidID(studentID)) {
			cout << "\nThank you!";
			isValidNum = true;
		}
		else {
			cout
				<< "\n\tERROR: Invalid input."
				<< "\n\tNOTE: Student ID MUST contain 7 digits."
				<< "\n\nPlease, try again: ";
			cin.clear();
			//cin.ignore(80, '\n');
		}

		//system("pause");
	}

	cout << "\nYour Student ID: " << studentID << endl;
	
	for (int i = 0; i < STUD_ID_SIZE; i++)
		studID[i] = studentID[i];
}

bool Student::isValidID(char * id) {
	int
		counter = 0,
		i = 0;

	while (isdigit(id[i++]))
		counter++;

	switch (counter) {
	case 7: cout << "Brilliant!";
		return true;
		break;
	default:
		return false;
	}
}




char * Student::returnStudID()
{
	return studID;
}

char * getLetter()
{
	const int GRADE_SIZE = 3;
	char grade[GRADE_SIZE];

		cin.getline(grade, GRADE_SIZE);
		
			cin.clear();
			//cin.ignore(80, '\n');
		

		//system("pause");
			return grade;
}


