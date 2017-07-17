
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip> // for setw() function
#include "Header.h"
using namespace std;



int main() {

	/*****************************************
	*        Student ID Validation Part      *
	*****************************************/
	Student student;
	int numOfClassesPS, numOfClassesTrnscrpt;

	

	/*****************************************
	*        Reading Program of Study        *
	*****************************************/

	ClassInfo *myClasses = nullptr;
	string line;
	int counter;

	ifstream input("programOfStudy.txt");

	if (!input.is_open()) 
	{
		cout << "Error opening the file...";
		system("pause");
		return 1;
	}
	else
	{
		
		counter = 0;
	
		// Counting number of classes in my pgogram of study 
		int i = 0;
		while (getline(input, line))
		   counter++;
		input.close();
		
		const int
			CLASS_NAME_SIZE = 30,
			CLASS_CODE_SIZE = 8;

		
		char
			className[CLASS_NAME_SIZE],
			classCode[CLASS_CODE_SIZE];
		int
			creditHours;


		numOfClassesPS = counter / 3;
		myClasses = new ClassInfo[numOfClassesPS];

		input.open("programOfStudy.txt");
		fstream progStudy("binaryProgram.dat", ios::out | ios::binary);

		// Reading file into ClassInfo Object Array
		i = 0;
		while (i < numOfClassesPS)
		{
			getline(input, line);
			myClasses[i].setClassName(line);
			strcpy(className, line.c_str());
			progStudy.write(reinterpret_cast<char *>(&className), CLASS_NAME_SIZE);

			getline(input, line);
			myClasses[i].setClassCode(line);
			strcpy(classCode, line.c_str());
			progStudy.write(reinterpret_cast<char *>(&classCode), CLASS_CODE_SIZE);

			getline(input, line);
			myClasses[i].setCreditHours(stoi(line));
			creditHours = stoi(line);
			progStudy.write(reinterpret_cast<char *>(&creditHours), sizeof(int));

			i++;
		}

		input.close();
		progStudy.close();
	
		fstream read1("binaryProgram.dat", ios::in | ios::binary);

		

		char newName[CLASS_NAME_SIZE];
		char newCode[CLASS_CODE_SIZE];
		int newInt;
		i = 0;
		while (i < numOfClassesPS)
		{
			read1.read(reinterpret_cast<char *> (&newName), CLASS_NAME_SIZE);
			read1.read(reinterpret_cast<char *> (&newCode), CLASS_CODE_SIZE);
			//newCode[4] = '\0';
			read1.read(reinterpret_cast<char *> (&newInt), sizeof(int));
			//cout << "\nClass Name: " << newName << " Class Code:  " << newCode << " Credit Hours: " << newInt << endl;
			i++;
		}
		progStudy.close();
		//system("pause");
	}

	
	/*************************************************************
	*                    Reading Transcript                      *
	*************************************************************/
    
	input.open("Transcript.txt");

	ClassInfo *myTranscript = nullptr;

	if (input.is_open())
	{
		int i = 0;
		counter = 0;
		while (getline(input, line))
			counter++;

		input.close();

		numOfClassesTrnscrpt = counter / 4;
		myTranscript = new ClassInfo[numOfClassesTrnscrpt];

		input.open("Transcript.txt");

		i = 0;
		while (i < numOfClassesTrnscrpt)
		{
			getline(input, line);
			myTranscript[i].setClassCode(line);
			getline(input, line);
			myTranscript[i].setClassName(line);
			getline(input, line);
			myTranscript[i].setEarnedGrade(line.c_str());
			getline(input, line);
			myTranscript[i].setCreditHours(stoi(line));
			i++;
		}

		input.close();
	}
	else 
	{
		cout << "\nERROR opening the file. Exiting..."; 
		return 1;
	}


		//student.getStudID();

		//system("pause");

		//student.printProgramOfStudy(myClasses, numOfClassesPS);

		//student.printProgramOfStudy(myClasses, numOfClassesPS);




		/*************************************************************
		*                           MENU                             *
		*************************************************************/
		int answer;

		while (true) {
			cout
				<< "\n***************************************************************\n"
				<< "*                          MyGPA                              *\n"
				<< "*-------------------------------------------------------------*\n"
				<< "*                                                             *\n"
				<< "*                                                             *\n"
				<< "*            1. Show Program of Study                         *\n"
				<< "*            2. Show Current Transcript                       *\n"
				<< "*            3. Show Classes Left to Take upon Graduation     *\n"
				<< "*            4. Simulate GPA upon graduation                  *\n"
				<< "*            5. Show Current GPA                              *\n"
				<< "*            6. Exit                                          *\n"
				<< "*                                                             *\n"
				<< "*                                                             *\n"
				<< "***************************************************************\n";

			cout << "Pick you option: ";
			
				answer = getInteger();
			

			ClassInfo *classesLeft = nullptr;
			int newSize; // variable that will store size of the new array
			bool hasnt;
			int currentK;
			const int GRADE_SIZE = 3;
			char grade[GRADE_SIZE];
			LinkedList<ClassInfo> list;

			switch (answer) {

			case 1:
				cout << "\n" << setw(60) << "\n======================= Your Program of Study ============================\n\n";
				cout
					<< "|       "
					<< setw(25) << left << "COURSE NAME  "
					<< setw(15) << left << "COURSE CODE    "
					<< setw(10) << left << "CREDITS   " << "         |\n\n";
				for (int i = 0; i < numOfClassesPS; i++)
				{
					list.appendNode(myClasses[i]);
				}

				list.displayList();
				
				break;

			case 2:
				printArrayWithGrades(myTranscript, numOfClassesTrnscrpt);
				cout << "\nYOUR CURRENT GPA: " << calculateGPA(myTranscript, numOfClassesTrnscrpt) << endl << endl;
				cout << setw(60) << "===================================================================\n";
				break;

			case 3:


				newSize = 0;
				// counting how many classes leftk
				for (int i = 0; i < numOfClassesPS; i++)
				{
					hasnt = true;
					for (int k = 0; k < numOfClassesTrnscrpt; k++)
					{
						if (myClasses[i].getClassCode() == myTranscript[k].getClassCode())
							hasnt = false;
					}
					if (hasnt)
						newSize++;
				}

				classesLeft = new ClassInfo[newSize];

				newSize = 0; //resetting variable

				// running through our arrays again and storing uncompleted courses
				for (int i = 0; i < numOfClassesPS; i++)
				{
					hasnt = true;

					for (int k = 0; k < numOfClassesTrnscrpt; k++)
					{
						if (myClasses[i].getClassCode() == myTranscript[k].getClassCode())
							hasnt = false;

						currentK = i;
					}
					if (hasnt)
					{
						counter++;
						classesLeft[newSize++] = myClasses[currentK];
					}
				}

				

				printArray(classesLeft, newSize);
				break;

			case 4:


				newSize = 0;
				// counting how many classes left
				for (int i = 0; i < numOfClassesPS; i++)
				{
					hasnt = true;
					for (int k = 0; k < numOfClassesTrnscrpt; k++)
					{
						if (myClasses[i].getClassCode() == myTranscript[k].getClassCode())
							hasnt = false;
					}
					if (hasnt)
						newSize++;
				}
				// dynamically allocating array for left classes
				classesLeft = new ClassInfo[newSize];

				newSize = 0; //resetting variable

							 // running through our arrays again and storing uncompleted courses
				for (int i = 0; i < numOfClassesPS; i++)
				{
					hasnt = true;

					for (int k = 0; k < numOfClassesTrnscrpt; k++)
					{
						if (myClasses[i].getClassCode() == myTranscript[k].getClassCode())
							hasnt = false;

						currentK = i;
					}
					if (hasnt)
					{
						counter++;
						classesLeft[newSize++] = myClasses[currentK];
					}
				}

				
				for (int i = 0; i < newSize-2; i++)
				{
					cout << "\nPlease Enter Letter Grade for " << classesLeft[i].getClassName() << ": ";
					if (i == 0) cin.ignore(80, '\n');;
					cin.getline(grade, GRADE_SIZE);
					classesLeft[i].setEarnedGrade(grade);
				}
				cout << "\n\n\t\tThank you!\n";
				cout << "Expected GPA Is: " << setprecision(3) << addAndCalculateGPA(myTranscript, classesLeft, numOfClassesTrnscrpt, newSize-2) << endl << endl;

				break;
				
			case 5:
				cout << endl << setw(60) << "===================================================================\n";
				cout << "\nYOUR CURRENT GPA: " << calculateGPA(myTranscript, numOfClassesTrnscrpt) << endl << endl;
				cout << setw(60) << "===================================================================\n";
				break;

			case 6:

				cout << "\n\n\t\t\tHave a Nice Day!\n";
				system("pause > NUL");
				return 0;
					
			}
			system("pause");
			system("cls");
		}

		system("pause");
		return 0;
	}










