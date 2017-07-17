#pragma once


#ifndef HEADER_H
#define HEADER_H

#include <string>
using namespace std;

//ClassInfo classInfo;

template <class T>
class ListNode
{
public:
	T value;           // Node value
	ListNode<T> *next; // Pointer to the next node

					   // Constructor
	ListNode(T nodeValue)
	{
		value = nodeValue;
		next = nullptr;
	}
};

//*********************************************
// LinkedList class                           *
//*********************************************

template <class T>
class LinkedList
{
private:
	ListNode<T> *head;   // List head pointer

public:
	// Constructor
	LinkedList()
	{
		head = nullptr;
	}

	// Destructor
	~LinkedList();

	// Linked list operations
	void appendNode(T);
	void insertNode(T);
	void deleteNode(T);
	void displayList() const;
};


//**************************************************
// appendNode appends a node containing the value  *
// pased into newValue, to the end of the list.    *
//**************************************************

template <class T>
void LinkedList<T>::appendNode(T newValue)
{
	ListNode<T> *newNode;  // To point to a new node
	ListNode<T> *nodePtr;  // To move through the list

						   // Allocate a new node and store newValue there.
	newNode = new ListNode<T>(newValue);

	// If there are no nodes in the list
	// make newNode the first node.
	if (!head)
		head = newNode;
	else  // Otherwise, insert newNode at end.
	{
		// Initialize nodePtr to head of list.
		nodePtr = head;

		// Find the last node in the list.
		while (nodePtr->next)
			nodePtr = nodePtr->next;

		// Insert newNode as the last node.
		nodePtr->next = newNode;
	}
}

//**************************************************
// displayList shows the value stored in each node *
// of the linked list pointed to by head.          *
//**************************************************

template <class T>
void LinkedList<T>::displayList() const
{
	ListNode<T> *nodePtr;  // To move through the list

						   // Position nodePtr at the head of the list.
	nodePtr = head;

	// While nodePtr points to a node, traverse
	// the list.
	while (nodePtr)
	{
		// Display the value in this node.
		cout << nodePtr->value << endl;

		// Move to the next node.
		nodePtr = nodePtr->next;
	}
}

//**************************************************
// The insertNode function inserts a node with     *
// newValue copied to its value member.            *
//**************************************************

template <class T>
void LinkedList<T>::insertNode(T newValue)
{
	ListNode<T> *newNode;				// A new node
	ListNode<T> *nodePtr;				// To traverse the list
	ListNode<T> *previousNode = nullptr; // The previous node

										 // Allocate a new node and store newValue there.
	newNode = new ListNode<T>(newValue);

	// If there are no nodes in the list
	// make newNode the first node
	if (!head)
	{
		head = newNode;
		newNode->next = nullptr;
	}
	else  // Otherwise, insert newNode
	{
		// Position nodePtr at the head of list.
		nodePtr = head;

		// Initialize previousNode to nullptr.
		previousNode = nullptr;

		// Skip all nodes whose value is less than newValue.
		while (nodePtr != nullptr && nodePtr->value < newValue)
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		// If the new node is to be the 1st in the list,
		// insert it before all other nodes.
		if (previousNode == nullptr)
		{
			head = newNode;
			newNode->next = nodePtr;
		}
		else  // Otherwise insert after the previous node.
		{
			previousNode->next = newNode;
			newNode->next = nodePtr;
		}
	}
}

//*****************************************************
// The deleteNode function searches for a node        *
// with searchValue as its value. The node, if found, *
// is deleted from the list and from memory.          *
//*****************************************************

template <class T>
void LinkedList<T>::deleteNode(T searchValue)
{
	ListNode<T> *nodePtr;       // To traverse the list
	ListNode<T> *previousNode;  // To point to the previous node

								// If the list is empty, do nothing.
	if (!head)
		return;

	// Determine if the first node is the one.
	if (head->value == searchValue)
	{
		nodePtr = head->next;
		delete head;
		head = nodePtr;
	}
	else
	{
		// Initialize nodePtr to head of list
		nodePtr = head;

		// Skip all nodes whose value member is 
		// not equal to num.
		while (nodePtr != nullptr && nodePtr->value != searchValue)
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		// If nodePtr is not at the end of the list, 
		// link the previous node to the node after
		// nodePtr, then delete nodePtr.
		if (nodePtr)
		{
			previousNode->next = nodePtr->next;
			delete nodePtr;
		}
	}
}

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
//**************************************************

template <class T>
LinkedList<T>::~LinkedList()
{
	ListNode<T> *nodePtr;   // To traverse the list
	ListNode<T> *nextNode;  // To point to the next node

							// Position nodePtr at the head of the list.
	nodePtr = head;

	// While nodePtr is not at the end of the list...
	while (nodePtr != nullptr)
	{
		// Save a pointer to the next node.
		nextNode = nodePtr->next;

		// Delete the current node.
		delete nodePtr;

		// Position nodePtr at the next node.
		nodePtr = nextNode;
	}
}

class programOfStudy {

private:
	string name;
	int totalCredits;
	int creditsEarned;
	int creditsLeft; 
public:
	void setName(string);
	void setTotalCredits();

	//ClassInfo getClassesLeft(ClassInfo &obj1, ClassInfo &obj2);
	void printCurrentGPA();
	void print();
};

class ClassInfo : public programOfStudy {

private:
	string className;
	string classCode;
	int creditHours;
	double earnedGrade;
    bool isPass;

public:
	//ClassInfo() {}
	ClassInfo() {
		className = "";
		creditHours = 0;
		earnedGrade = 0;
		isPass = false;
	}
	
	
	//Copy Constructor
	ClassInfo(ClassInfo &obj)
	{
		className = obj.className;
		classCode = obj.classCode;
		creditHours = obj.creditHours;
	}

	void setClassCode(string);
	void setClassName(string);
	void setCreditHours(int);
	void setEarnedGrade(const char *);
	bool isPassed();

	string getClassName();
	int getCreditHours();
	double getEarnedGrade();
	string getClassCode();

	
	friend void printArray(ClassInfo [], int);
	friend void printArrayWithGrades(ClassInfo obj[], int num);
	friend double calculateGPA(ClassInfo obj[], int num);
	friend double addAndCalculateGPA(ClassInfo obj1[], ClassInfo obj2[], int num1, int num2);
	friend ostream &operator << (ostream &, const ClassInfo &);

	
	//ClassInfo operator=(const ClassInfo &);

	//friend ClassInfo programOfStudy::getClassesLeft(ClassInfo, ClassInfo);
	//friend void Student::printProgramOfStudy();
	//friend void Student::printTranscript();
};




class Student {

private:
	char studID[8];
	//int studID;
	string studentName;
	string major;
	double currentGPA;
public:
	Student() {}
	~Student() {}
	void setStudID(char *);
	void setName(string);
	void setMajor(string);
	void setGPA(double);
	void setID(char *);

	char * returnStudID();

	string getName();
	string getMajor();
	
	void getStudID();

	bool isValidID(char *);
	void print();

	

	
};

int getInteger();



#endif // !COURSEINFO_H
#pragma once
