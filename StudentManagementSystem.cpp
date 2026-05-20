#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include <conio.h>
#include <climits>
#include "header.h"
#define FLBSTUD "student.txt"
#define FLBGRAD "grade.txt"
using namespace std;
fstream fil;



/*================================================================================*/
/* STUDENT */
class Student
{
	int title;
	char studentName[30];
	int rollNo;
	int classop1;
	char fatherName[30];
	char motherName[30];
	char address[80];
	char bloodGroup[4];
public:

	void getDetails();

	char* strTitle(int x)
	{
		static char title[8] = " ";
		if (x == 1)
			strcpy_s(title, sizeof(title), "Master");
		else if (x == 2)
			strcpy_s(title, sizeof(title), "Mr");
		else
			strcpy_s(title, sizeof(title), "Miss");
		return title;
	}

	void printDetails()
	{
		cout << "Student Name  : " << strTitle(title) << ' ' << studentName << endl;
		cout << "Roll No.      : " << rollNo << endl;
		cout << "Father's Name : " << fatherName << endl;
		cout << "Mother's Name : " << motherName << endl;
		cout << "Address       : " << address << endl;
		cout << "Blood Group   : " << bloodGroup << endl;
	}
	int retRollNo() {				//Return Roll No
		return rollNo;
	}
	char* retString(char x)
	{
		if (x == 'T')
			return strTitle(title);
		if (x == 'N')
			return studentName;
		if (x == 'F')
			return fatherName;
		if (x == 'M')
			return motherName;
		if (x == 'A')
			return address;
		if (x == 'B')
			return bloodGroup;
	}
	char* retStudentName() {		//Returns Student Name
		return retString('N');
	}
};

void Student::getDetails()
{
	CLS();
	cout << "Enter Title \n(Master = 1, Mr = 2, Miss = 3)  : ";
	do {
		title = scan();
	} while (title != 1 && title != 2 && title != 3);

	cout << "Enter Student's Name        : ";
	do {
		cin.getline(studentName, 30);
	} while (strlen(studentName) == 0);
	cout << "Enter Roll No.            : ";
	do {
		rollNo = scan();
	} while (rollNo < 1);
	cout << "Enter Father's Name         : ";
	do {
		cin.getline(fatherName, 30);
	} while (strlen(fatherName) == 0);
	cout << "Enter Mother's Name         : ";
	do {
		cin.getline(motherName, 30);
	} while (strlen(motherName) == 0);
	cout << "Enter Address             : ";
	do {
		cin.getline(address, 80);
	} while (strlen(address) == 0);

	cout << "Enter Blood Group [eg. B+]: ";
	do {
		cin.getline(bloodGroup, 4);
	} while (strlen(bloodGroup) == 0);
}

void insertStudent()
{
	CLS();
	Student obj, obj2;
	char ch;
	int v = 0;
	cout << "Enter Details for new Student :\n";
	obj.getDetails();
	fstream fl1(FLBSTUD, ios::in | ios::binary);
	ofstream fl2;
	if (!fl1)			//If file does not exist, create new file
	{
		fl2.open(FLBSTUD, ios::out | ios::binary);
		fl2.write((char*)&obj, sizeof(obj));
		fl2.close();
		cout << "Record successfully inserted !\n";
		return;
	}
	while (!fl1.eof())
	{
		fl1.read((char*)&obj2, sizeof(obj));
		if (fl1.eof())
		{
			break;
		}
		if (obj.retRollNo() == obj2.retRollNo())		//If record with same Roll No. exists, then abort insertion
		{
			cout << "Record with same Roll No. with following details already exists : \n";
			obj2.printDetails();
			cout << "Insertion Aborted !\n";
			return;
		}
		else if (_strcmpi(obj.retStudentName(), obj2.retStudentName()) == 0)
		{
			if (!v)							//Warns user that Record with same name exists
				cout << "Warning : Record with same name exists with follwing details : \n";
			obj2.printDetails();
			cout << '\n';
			v = 1;
		}
	}
	if (v)
	{
		cout << "Do you still wish to insert record (Y/N) ? ";
		do {
			cin >> ch;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				ch = 0;
			}
			ch = toupper(ch);
		} while (ch != 'Y' && ch != 'N');
		if (ch == 'N') {
			cout << "Insertion Aborted !\n";
			return;
		}
	}
	fl2.open(FLBSTUD, ios::out | ios::app | ios::binary);
	fl2.seekp(0, ios::end);
	fl2.write((char*)&obj, sizeof(obj));
	fl2.close();
	cout << "Record Inserted successfully !\n";
}



int dispStudentRecord()		//Display all Student Records
{
	CLS();
	Student obj;
	int v = 0;
	fstream fl(FLBSTUD, ios::in | ios::binary);
	if (!fl)
	{					//If file does not exist
		cout << "Empty Records !\n";
		return 0;
	}
	while (!fl.eof())
	{
		fl.read((char*)&obj, sizeof(obj));
		if (fl.eof())
			break;
		v = 1;
		obj.printDetails();
		RULE('-');
	}
	fl.close();
	if (!v)
		cout << "Empty Records !\n";
	return v;
}



int searchByRollNo(int i)
{
	CLS();
	int r;
	int found = 0;
	Student obj;
	do {
		cout << "Enter Roll No. to search for : ";
		cin >> r;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			r = 0;
		}
	} while (r < 1);
	fstream fl(FLBSTUD, ios::in | ios::binary);
	if (!fl) {					//No file exists
		cout << "No Records Found !\n";
		return 0;
	}
	while (!fl.eof())
	{
		fl.read((char*)&obj, sizeof(obj));
		if (fl.eof())
		{
			break;
		}
		if (r == obj.retRollNo())
		{
			if (!found)
				cout << "\nSearch Results : \n\n";

			obj.printDetails();
			RULE('-');
			found = 1;
		}
	}
	if (!found)
		cout << "No Records Found !\n";
	fl.close();
	return found;
}



void delStudentRecord()
{
	CLS();
	Student obj;					//Writes to new file except record to be deleted
	int f = 0;
	int r;
	char ch;
	do {
		cout << "\nEnter Roll No. to delete : ";
		cin >> r;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			r = 0;
		}
	} while (r < 1);
	fstream fl(FLBSTUD, ios::in | ios::binary);
	fstream fo("temp.dat", ios::out | ios::binary);
	while (!fl.eof())
	{
		fl.read((char*)&obj, sizeof(obj));

		if (fl.eof())
			break;

		if (r == obj.retRollNo())
		{
			cout << "Record with following info will be deleted :\n\n";
			obj.printDetails();
			cout << "Do you wish to continue ? (Y/N) : ";
			do {
				cin >> ch;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					ch = 0;
				}
				ch = toupper(ch);
			} while (ch != 'N' && ch != 'Y');

			if (ch == 'N')
			{
				cout << "Deletion Aborted !\n";
				fl.close();
				fo.close();
				remove("temp.dat");
				return;
			}
			f = 1;
			continue;
		}
		fo.write((char*)&obj, sizeof(obj));
	}
	fl.close();
	fo.close();
	remove(FLBSTUD);
	rename("temp.dat", FLBSTUD);
	if (f)
		cout << "Record Successfully Deleted !\n";
	else
		cout << "No Such Record Exists !\n";
}


/*================================================================================*/
//GRADING SYSTEM ------------->>SHIVAM

class Grade
{
private:
	char  name[30];
	int   rollNo;
	int   total;
	float perc;
public:
	int retRollNo()
	{
		return rollNo;
	}
	void retGrade(float marks)
	{
		if (marks < 50)
		{
			printf("Grade F");
		}
		else if (marks >= 50 && marks < 60)
		{
			printf("Grade D");
		}
		else if (marks >= 60 && marks < 70)
		{
			printf("Grade C");
		}
		else if (marks >= 70 && marks < 80)
		{
			printf("Grade B");
		}
		else if (marks >= 80 && marks < 90)
		{
			printf("Grade A");
		}
		else
		{
			printf("Grade A+");
		}
	}
	void getDetails(void);
	void putDetails(void);
};

void Grade::getDetails(void)
{
	cout << "Enter Roll No. : ";
	do {
		cin >> rollNo;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			rollNo = -1;
		}
	} while (rollNo < 1);
	cin.ignore();
	cout << "Enter Full Name: ";
	do {
		cin.getline(name, 30);
	} while (strlen(name) == 0);
	cout << "Enter Total Marks (0-500) : ";
	do {
		cin >> total;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			total = -1;
		}
	} while (total < 0 || total > 500);
	perc = (float)total / 500 * 100;
}

void Grade::putDetails(void)
{
	cout << "Student Name     : " << name << endl;
	cout << "Roll No.         : " << rollNo << endl;
	cout << "Total		 : " << total << endl;
	cout << "Percentage	 : " << perc << endl;
	retGrade(perc);
}

void insertGrade()			//Insert Grade  in File
{
	system("CLS");
	Grade obj, obj2;
	char ch;
	int v = 0;
	obj.getDetails();
	fstream gl1(FLBGRAD, ios::in | ios::binary);
	ofstream gl2;
	if (!gl1)
	{
		gl2.open(FLBGRAD, ios::out | ios::binary);
		gl2.write((char*)&obj, sizeof(obj));
		gl2.close();
		cout << "Grade successfully inserted !\n";
		return;
	}

	gl2.open(FLBGRAD, ios::out | ios::app | ios::binary);
	gl2.seekp(0, ios::end);
	gl2.write((char*)&obj, sizeof(obj));
	gl2.close();
	cout << "Grade Inserted successfully !\n";
}



int dispGrade()		//Display all Student Records
{
	system("CLS");
	Grade obj;
	int v = 0;
	fstream fl(FLBGRAD, ios::in | ios::binary);
	if (!fl)
	{					//If file does not exist
		cout << "Empty Records !\n";
		return 0;
	}
	while (!fl.eof())
	{
		fl.read((char*)&obj, sizeof(obj));
		if (fl.eof())
			break;
		v = 1;
		obj.putDetails();
		RULE('-');
	}
	fl.close();
	if (!v)
		cout << "Empty Records !\n";
	return v;
}

int searchGradeByRollNo(int i)
{
	system("CLS");
	int r;
	int found = 0;
	Grade obj;
	do {
		cout << "Enter Roll No. to search for : ";
		cin >> r;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			r = 0;
		}
	} while (r < 1);
	fstream fl(FLBGRAD, ios::in | ios::binary);
	if (!fl) {					//No file exists
		cout << "No Records Found !\n";
		return 0;
	}
	while (!fl.eof())
	{
		fl.read((char*)&obj, sizeof(obj));
		if (fl.eof())
		{
			break;
		}
		if (r == obj.retRollNo())
		{
			if (!found)
				cout << "\nSearch Results : \n\n";

			obj.putDetails();
			RULE('-');
			found = 1;
		}
	}
	if (!found)
		cout << "No Records Found !\n";
	fl.close();
	return found;
}

void delGradeRecord()
{
	CLS();
	Grade obj;
	int f = 0;
	int r;
	char ch;
	do {
		cout << "\nEnter Roll No. to delete : ";
		cin >> r;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			r = 0;
		}
	} while (r < 1);
	fstream fl(FLBGRAD, ios::in | ios::binary);
	fstream fo("temp_grade.dat", ios::out | ios::binary);
	while (!fl.eof())
	{
		fl.read((char*)&obj, sizeof(obj));

		if (fl.eof())
			break;

		if (r == obj.retRollNo())
		{
			cout << "Record with following info will be deleted :\n\n";
			obj.putDetails();
			RULE('-');
			cout << "Do you wish to continue ? (Y/N) : ";
			do {
				cin >> ch;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					ch = 0;
				}
				ch = toupper(ch);
			} while (ch != 'N' && ch != 'Y');

			if (ch == 'N')
			{
				cout << "Deletion Aborted !\n";
				fl.close();
				fo.close();
				remove("temp_grade.dat");
				return;
			}
			f = 1;
			continue;
		}
		fo.write((char*)&obj, sizeof(obj));
	}
	fl.close();
	fo.close();
	remove(FLBGRAD);
	rename("temp_grade.dat", FLBGRAD);
	if (f)
		cout << "Record Successfully Deleted !\n";
	else
		cout << "No Such Record Exists !\n";
}

/*================================================================================*/
//PLACEMENT CELL ------->>DIBYA & AMLAN

// Students details class.
class Students
{
	long roll;
	float cgpa;
	char sname[25];
public:
	void getSData();
	long sroll();
	float scgpa();
	char* ssname();
};


void Students::getSData()
{
	ofstream fout("studentList.txt", ios::app);
	string tempName;
	cin.ignore();
	cout << "\n\nEnter Name: ";
	do {
		getline(cin, tempName);
	} while (tempName.length() == 0);
	strncpy_s(sname, tempName.c_str(), 24);
	sname[24] = '\0';
	fout << sname << endl;
	do {
		cout << "\n\nEnter Roll Number: ";
		cin >> roll;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			roll = -1;
		}
	} while (roll < 1);
	fout << roll << endl;
	do {
		cout << "\n\nEnter CGPA (0.0 - 10.0): ";
		cin >> cgpa;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cgpa = -1.0f;
		}
	} while (cgpa < 0.0f || cgpa > 10.0f);
	fout << cgpa << endl;
	fout << endl << endl;
	fout.close();
}
long Students::sroll()
{
	return roll;
}

float Students::scgpa()
{
	return cgpa;
}

char* Students::ssname()
{
	return sname;
}

// class company details
class company
{
	char name[20];
	int package;
	float cgpa;
public:
	void getCData();
	friend class Students;
	char* cname();
	int cpackage();
	float ccgpa();
};

void company::getCData()
{
	ofstream fout("companyList.txt", ios::app);
	string tempName;
	cin.ignore();
	cout << "\n\nEnter the name of the company: ";
	do {
		getline(cin, tempName);
	} while (tempName.length() == 0);
	strncpy_s(name, tempName.c_str(), 19);
	name[19] = '\0';
	fout << name << endl;
	do {
		cout << "\n\nEnter the package (in LPA): ";
		cin >> package;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			package = -1;
		}
	} while (package < 0);
	fout << package << endl;
	do {
		cout << "\n\nEnter CGPA required (0.0 - 10.0): ";
		cin >> cgpa;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cgpa = -1.0f;
		}
	} while (cgpa < 0.0f || cgpa > 10.0f);
	fout << cgpa << endl;
	fout << endl << endl;
	fout.close();
}

char* company::cname()
{
	return name;
}

int company::cpackage()
{
	return package;
}
float company::ccgpa()
{
	return cgpa;
}

// Students qualified for placement
class placement
{
	char* name;
	char* cname;
	long rollnumber;
public:
	void putPlacementData(char* Name, char* Cname, long Rollnumber);
	void getData();
};

void placement::putPlacementData(char* Name, char* Cname, long Rollnumber)
{
	name = Name;
	cname = Cname;
	rollnumber = Rollnumber;
}

void placement::getData()
{
	cout << "DETAILS";
	RULE('-');
	cout << "\nName: " << name << endl;
	cout << "Roll Number: " << rollnumber << endl;
}

/*================================================================================*/

class Library
{
public:
	char book[100], author[100], publication[100], id[20];
	float price;
	int quantity;
	void getData();
	void showData();
	void mainMenu();
	void student();
	void staff();
	int booksCategory(int);
	void modifyBooklist();
	void addBooks();
	void viewBooks(int);
	void removeBook();
	void searchBook(int);
	void issueBook();
	void returnBook();
};

//function to get details of book
void Library::getData()
{
	cin.ignore();
	cout << "\t\t\t\t\t********** ENTER BOOK DETAILS **********";
	cout << "\n\n\n\t\t\tEnter Book's Name: ";
	do {
		cin.getline(book, 100);
	} while (strlen(book) == 0);
	cout << "\n\t\t\tEnter Author's Name: ";
	do {
		cin.getline(author, 100);
	} while (strlen(author) == 0);
	cout << "\n\t\t\tEnter Publication Name: ";
	do {
		cin.getline(publication, 100);
	} while (strlen(publication) == 0);
	cout << "\n\t\t\tEnter Book's ID: ";
	do {
		cin.getline(id, 20);
	} while (strlen(id) == 0);
	do {
		cout << "\n\t\t\tEnter Book's Price: ";
		cin >> price;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			price = -1.0f;
		}
	} while (price < 0);
	do {
		cout << "\n\t\t\tEnter Book's Quantity: ";
		cin >> quantity;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			quantity = -1;
		}
	} while (quantity < 0);
}

//function to display details of book(s)
void Library::showData()
{
	cout << "\n\t\tName of the book: " << book;
	cout << "\n\n\t\tAuthor's name: " << author;
	cout << "\n\n\t\tPublication's name: " << publication;
	cout << "\n\n\t\tBook's ID: " << id;
	cout << "\n\n\t\tPrice of the book: " << price;
	cout << "\n\n\t\tNumber of books available: " << quantity << endl << endl;
}

//function to display the main menu
void Library::mainMenu()
{
	int choice;
	char ch;
	bool returnFromSub = false;

	do {
		fflush(stdin);
		CLS();
		RULE('*');
		cout << "\t\t\tLIBRARY MANAGEMENT SYSTEM";
		RULE('*');
		cout << "\t1. Student\n";
		cout << "\t2. Staff\n";
		cout << "\t0. Back To Main\n";
		do {
			cout << "\nEnter your choice : ";
			cin >> choice;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				choice = -1;
			}
		} while (choice < 0 || choice > 2);
		fflush(stdin);
		returnFromSub = false;
		switch (choice)
		{
		case 1:
			student();
			returnFromSub = true;
			break;
		case 2:
			staff();
			returnFromSub = true;
			break;
		}
		if (returnFromSub)
			break;
		if (choice)
			cin >> ch;
	} while (choice != 0);
}

//function to display options for staff
void Library::staff()
{
	CLS();
	int choice;
	RULE('*');
	cout << "\t\t\tLIBRARY MANAGEMENT SYSTEM";
	RULE('*');
	cout << "\t\t\t     STAFF SECTION";
	RULE('-');
	cout << "\t1.  View Category of Books\n";
	cout << "\t2.  Search for a Book\n";
	cout << "\t3.  Modify Booklist\n";
	cout << "\t4.  Go Back\n";
	cout << "\t5.  Exit Application\n";
	do {
		cout << "\nEnter your choice : ";
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			choice = -1;
		}
	} while (choice < 1 || choice > 5);
	fflush(stdin);
	switch (choice)
	{
	case 1:
		viewBooks(2);
		break;
	case 2:
		searchBook(2);
		break;
	case 3:
		modifyBooklist();
		break;
	case 4:
		CLS();
		mainMenu();
		return;
	case 5:
		exit(0);
	}
}

//function to display options for students
void Library::student()
{
	CLS();
	int choice;
	RULE('*');
	cout << "\t\t\tLIBRARY MANAGEMENT SYSTEM";
	RULE('*');
	cout << "\t\t\t     STUDENT SECTION";
	RULE('-');
	cout << "\t1.  View Category of Books\n";
	cout << "\t2.  Search for a Book\n";
	cout << "\t3.  Go Back\n";
	cout << "\t4.  Exit Application\n";
	do {
		cout << "\nEnter your choice : ";
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			choice = -1;
		}
	} while (choice < 1 || choice > 4);
	fflush(stdin);
	switch (choice)
	{
	case 1:
		viewBooks(1);
		break;
	case 2:
		searchBook(1);
		break;
	case 3:
		CLS();
		mainMenu();
		return;
	case 4:
		exit(0);
	}
}

//function to display a list of category of books available in the library
int Library::booksCategory(int flag)
{
	CLS();
	int choice;
	RULE('*');
	cout << "\t\t\tLIBRARY MANAGEMENT SYSTEM";
	RULE('*');
	if (flag == 1)
		cout << "\t\t\t   STUDENT SECTION";
	else
		cout << "\t\t\t     STAFF SECTION";
	RULE('-');
	cout << "\t\t\t  CATEGORY OF BOOKS";
	RULE('-');
	cout << "\t1.  School of Computer Engineering\n";
	cout << "\t2.  School of Electronics Engineering\n";
	cout << "\t3.  School of Electrical Engineering\n";
	cout << "\t4.  School of Mechanical Engineering\n";
	cout << "\t5.  School of Civil Engineering\n";
	cout << "\t6.  First Year\n";
	cout << "\t7.  Go Back\n";
	cout << "\t8.  Go to Main Menu\n";
	do {
		cout << "\nEnter your choice : ";
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			choice = -1;
		}
	} while (choice < 1 || choice > 8);
	fflush(stdin);
	switch (choice)
	{
	case 1:
		return 1;
	case 2:
		return 2;
	case 3:
		return 3;
	case 4:
		return 4;
	case 5:
		return 5;
	case 6:
		return 6;
	case 7:
		CLS();
		if (flag == 1)
			student();
		else
			staff();
		return -1;  // Indicates user wants to go back - caller should exit
	case 8:
		CLS();
		mainMenu();
		return -1;  // Indicates user wants to go back - caller should exit
	}
	return 7;
}

//function to modify list of books
void Library::modifyBooklist()
{
	CLS();
	int choice;
	RULE('*');
	cout << "\t\t\tLIBRARY MANAGEMENT SYSTEM";
	RULE('*');
	cout << "\t\t\t  BOOKLIST MODIFICATION";
	RULE('-');
	cout << "\t1.  Add Books\n";
	cout << "\t2.  Remove Books\n";
	cout << "\t3.  Issue Book\n";
	cout << "\t4.  Return Book\n";
	cout << "\t5.  Go Back\n";
	do {
		cout << "\nEnter your choice : ";
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			choice = -1;
		}
	} while (choice < 1 || choice > 5);
	fflush(stdin);
	switch (choice)
	{
	case 1:
		addBooks();
		break;
	case 2:
		removeBook();
		break;
	case 3:
		issueBook();
		break;
	case 4:
		returnBook();
		break;
	case 5:
		CLS();
		staff();
		break;
	}
}

//function to add books
void Library::addBooks()
{
	CLS();
	int aCategory = booksCategory(2);
	if (aCategory == -1)
	{
		staff();
		return;
	}
	CLS();
	getData();
	if (aCategory == 1)
	{
		ofstream fout("csBooks.txt", ios::app);
		fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
		fout.close();
	}
	if (aCategory == 2)
	{
		ofstream fout("eceBooks.txt", ios::app);
		fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
		fout.close();
	}
	if (aCategory == 3)
	{
		ofstream fout("elecBooks.txt", ios::app);
		fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
		fout.close();
	}
	if (aCategory == 4)
	{
		ofstream fout("mechBooks.txt", ios::app);
		fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
		fout.close();
	}
	if (aCategory == 5)
	{
		ofstream fout("civilBooks.txt", ios::app);
		fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
		fout.close();
	}
	if (aCategory == 6)
	{
		ofstream fout("yearOneBooks.txt", ios::app);
		fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
		fout.close();
	}
	cout << "\n\n\t\t\tBook Added Successfully.";
	cout << "\n\n\t\t\tPress any key to continue";
	(void)_getch();
	modifyBooklist();
}

//function to view list of books
void Library::viewBooks(int flag)
{
	int serial_num = 0;
	CLS();
	int vCategory = booksCategory(flag);
	if (vCategory == -1)
	{
		if (flag == 1)
			student();
		else
			staff();
		return;
	}
	CLS();
	if (vCategory == 1)
	{
		ifstream fin("csBooks.txt", ios::in);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\t\t\t\t\t********** LIST OF BOOKS **********\n\n";
			fin.getline(book, 100);
			fin.getline(author, 100);
			fin.getline(publication, 100);
			fin >> id >> price >> quantity;
			while (1)
			{
				if (book[0] == '\0')
				{
					cout << "\n\n\t\t\t\t\t\tNO BOOK AVAILABLE";
					break;
				}
				serial_num++;
				cout << "\n\t\t\t##### " << serial_num << " #####\n";
				showData();
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
			}
		}
		fin.close();
	}
	if (vCategory == 2)
	{
		ifstream fin("eceBooks.txt", ios::in);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\t\t\t\t\t********** LIST OF BOOKS **********\n\n";
			fin.getline(book, 100);
			fin.getline(author, 100);
			fin.getline(publication, 100);
			fin >> id >> price >> quantity;
			while (1)
			{
				if (book[0] == '\0')
				{
					cout << "\n\n\t\t\t\t\t\tNO BOOK AVAILABLE";
					break;
				}
				serial_num++;
				cout << "\n\t\t\t##### " << serial_num << " #####\n";
				showData();
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
			}
		}
		fin.close();
	}
	if (vCategory == 3)
	{
		ifstream fin("elecBooks.txt", ios::in);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\t\t\t\t\t********** LIST OF BOOKS **********\n\n";
			fin.getline(book, 100);
			fin.getline(author, 100);
			fin.getline(publication, 100);
			fin >> id >> price >> quantity;
			while (1)
			{
				if (book[0] == '\0')
				{
					cout << "\n\n\t\t\t\t\t\tNO BOOK AVAILABLE";
					break;
				}
				serial_num++;
				cout << "\n\t\t\t##### " << serial_num << " #####\n";
				showData();
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
			}
		}
		fin.close();
	}
	if (vCategory == 4)
	{
		ifstream fin("mechBooks.txt", ios::in);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\t\t\t\t\t********** LIST OF BOOKS **********\n\n";
			fin.getline(book, 100);
			fin.getline(author, 100);
			fin.getline(publication, 100);
			fin >> id >> price >> quantity;
			while (1)
			{
				if (book[0] == '\0')
				{
					cout << "\n\n\t\t\t\t\t\tNO BOOK AVAILABLE";
					break;
				}
				serial_num++;
				cout << "\n\t\t\t##### " << serial_num << " #####\n";
				showData();
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
			}
		}
		fin.close();
	}
	if (vCategory == 5)
	{
		ifstream fin("civilBooks.txt", ios::in);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\t\t\t\t\t********** LIST OF BOOKS **********\n\n";
			fin.getline(book, 100);
			fin.getline(author, 100);
			fin.getline(publication, 100);
			fin >> id >> price >> quantity;
			while (1)
			{
				if (book[0] == '\0')
				{
					cout << "\n\n\t\t\t\t\t\tNO BOOK AVAILABLE";
					break;
				}
				serial_num++;
				cout << "\n\t\t\t##### " << serial_num << " #####\n";
				showData();
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
			}
		}
		fin.close();
	}
	if (vCategory == 6)
	{
		ifstream fin("yearOneBooks.txt", ios::in);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\t\t\t\t\t********** LIST OF BOOKS **********\n\n";
			fin.getline(book, 100);
			fin.getline(author, 100);
			fin.getline(publication, 100);
			fin >> id >> price >> quantity;
			while (1)
			{
				if (book[0] == '\0')
				{
					cout << "\n\n\t\t\t\t\t\tNO BOOK AVAILABLE";
					break;
				}
				serial_num++;
				cout << "\n\t\t\t##### " << serial_num << " #####\n";
				showData();
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
			}
		}
		fin.close();
	}
	cout << "\n\n\n\t\tPress any key to continue";
	(void)_getch();
	CLS();
	if (flag == 1)
		student();
	else
		staff();
}

//function to remove books
void Library::removeBook()
{
	CLS();
	int rCategory = booksCategory(2);
	if (rCategory == -1)
	{
		staff();
		return;
	}
	CLS();
	int result = INT_MIN;
	char delBook[100];
	if (rCategory == 1)
	{
		ifstream fin("csBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\n\t\t\tEnter Books's Name: ";
			cin.ignore();
			cin.getline(delBook, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(delBook, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
			}
		}
		fout.close();
		fin.close();
		remove("csBooks.txt");
		result = rename("tempFile.txt", "csBooks.txt");
	}
	if (rCategory == 2)
	{
		ifstream fin("eceBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\n\t\t\tEnter Books's Name: ";
			cin.ignore();
			cin.getline(delBook, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(delBook, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
			}
		}
		fout.close();
		fin.close();
		remove("eceBooks.txt");
		result = rename("tempFile.txt", "eceBooks.txt");
	}
	if (rCategory == 3)
	{
		ifstream fin("elecBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\n\t\t\tEnter Books's Name: ";
			cin.ignore();
			cin.getline(delBook, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(delBook, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
			}
		}
		fout.close();
		fin.close();
		remove("elecBooks.txt");
		result = rename("tempFile.txt", "elecBooks.txt");
	}
	if (rCategory == 4)
	{
		ifstream fin("mechBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\n\t\t\tEnter Books's Name: ";
			cin.ignore();
			cin.getline(delBook, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(delBook, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
			}
		}
		fout.close();
		fin.close();
		remove("mechBooks.txt");
		result = rename("tempFile.txt", "mechBooks.txt");
	}
	if (rCategory == 5)
	{
		ifstream fin("civilBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\n\t\t\tEnter Books's Name: ";
			cin.ignore();
			cin.getline(delBook, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(delBook, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
			}
		}
		fout.close();
		fin.close();
		remove("civilBooks.txt");
		result = rename("tempFile.txt", "civilBooks.txt");
	}
	if (rCategory == 6)
	{
		ifstream fin("yearOneBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\n\t\t\tEnter Books's Name: ";
			cin.ignore();
			cin.getline(delBook, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(delBook, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
			}
		}
		fout.close();
		fin.close();
		remove("yearOneBooks.txt");
		result = rename("tempFile.txt", "yearOneBooks.txt");
	}
	if (result == 0)
		cout << "\n\n\t\t\tBook Deleted Successfully.";
	cout << "\n\n\t\t\tPress any key to continue";
	(void)_getch();
	modifyBooklist();
}

//function to search books
void Library::searchBook(int flag)
{
	CLS();
	int sCategory = booksCategory(2);
	if (sCategory == -1)
	{
		if (flag == 1)
			student();
		else
			staff();
		return;
	}
	CLS();
	int choice;
	char bookName[100], bookID[20];
	int var = 1;
	cout << "\t\t\t\t\t********** SEARCH BOOK **********\n\n";
	cout << "\t\t\t\t\t>> Choose any option\n\n";
	cout << "\t\t\t\t\t1. Search by name\n\n" << "\t\t\t\t\t2. Search by ID\n\n" << "\t\t\t\t\t3. Go Back\n\n";
	do {
		cout << "\t\t\t\t\tEnter choice: ";
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			choice = -1;
		}
	} while (choice < 1 || choice > 3);
	cout << endl << endl;
	switch (choice)
	{
	case 1:
		CLS();
		if (sCategory == 1)
		{
			ifstream fin("csBooks.txt", ios::in);
			if (!fin)
				cout << "\n\t\tFile Not Found.";
			else
			{
				cout << "\n\t\tEnter Book's Name: ";
				cin.ignore();
				cin.getline(bookName, 100);
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				while (1)
				{
					if (strcmp(bookName, book) == 0)
					{
						cout << "\n\n\t\t##### SEARCH RESULTS #####\n";
						showData();
						var++;
					}
					if (fin.eof())
						break;
					fin.getline(book, 100);
					fin.getline(author, 100);
					fin.getline(publication, 100);
					fin >> id >> price >> quantity;
				}
				fin.close();
			}
			if (var == 1)
				cout << "\n\n\t\t\tBOOK NOT FOUND";
			cout << "\n\n\n\t\tPress any key to continue";
			(void)_getch();
			if (flag == 1)
				student();
			else
				staff();
		}
		if (sCategory == 2)
		{
			ifstream fin("eceBooks.txt", ios::in);
			if (!fin)
				cout << "\n\t\tFile Not Found.";
			else
			{
				cout << "\n\t\tEnter Book's Name: ";
				cin.ignore();
				cin.getline(bookName, 100);
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				while (1)
				{
					if (strcmp(bookName, book) == 0)
					{
						cout << "\n\n\t\t##### SEARCH RESULTS #####\n";
						showData();
						var++;
					}
					if (fin.eof())
						break;
					fin.getline(book, 100);
					fin.getline(author, 100);
					fin.getline(publication, 100);
					fin >> id >> price >> quantity;
				}
				fin.close();
			}
			if (var == 1)
				cout << "\n\n\t\t\tBOOK NOT FOUND";
			cout << "\n\n\n\t\tPress any key to continue";
			(void)_getch();
			if (flag == 1)
				student();
			else
				staff();
		}
		if (sCategory == 3)
		{
			ifstream fin("elecBooks.txt", ios::in);
			if (!fin)
				cout << "\n\t\tFile Not Found.";
			else
			{
				cout << "\n\t\tEnter Book's Name: ";
				cin.ignore();
				cin.getline(bookName, 100);
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				while (1)
				{
					if (strcmp(bookName, book) == 0)
					{
						cout << "\n\n\t\t##### SEARCH RESULTS #####\n";
						showData();
						var++;
					}
					if (fin.eof())
						break;
					fin.getline(book, 100);
					fin.getline(author, 100);
					fin.getline(publication, 100);
					fin >> id >> price >> quantity;
				}
				fin.close();
			}
			if (var == 1)
				cout << "\n\n\t\t\tBOOK NOT FOUND";
			cout << "\n\n\n\t\tPress any key to continue";
			(void)_getch();
			if (flag == 1)
				student();
			else
				staff();
		}
		if (sCategory == 4)
		{
			ifstream fin("mechBooks.txt", ios::in);
			if (!fin)
				cout << "\n\t\tFile Not Found.";
			else
			{
				cout << "\n\t\tEnter Book's Name: ";
				cin.ignore();
				cin.getline(bookName, 100);
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				while (1)
				{
					if (strcmp(bookName, book) == 0)
					{
						cout << "\n\n\t\t##### SEARCH RESULTS #####\n";
						showData();
						var++;
					}
					if (fin.eof())
						break;
					fin.getline(book, 100);
					fin.getline(author, 100);
					fin.getline(publication, 100);
					fin >> id >> price >> quantity;
				}
				fin.close();
			}
			if (var == 1)
				cout << "\n\n\t\t\tBOOK NOT FOUND";
			cout << "\n\n\n\t\tPress any key to continue";
			(void)_getch();
			if (flag == 1)
				student();
			else
				staff();
		}
		if (sCategory == 5)
		{
			ifstream fin("civilBooks.txt", ios::in);
			if (!fin)
				cout << "\n\t\tFile Not Found.";
			else
			{
				cout << "\n\t\tEnter Book's Name: ";
				cin.ignore();
				cin.getline(bookName, 100);
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				while (1)
				{
					if (strcmp(bookName, book) == 0)
					{
						cout << "\n\n\t\t##### SEARCH RESULTS #####\n";
						showData();
						var++;
					}
					if (fin.eof())
						break;
					fin.getline(book, 100);
					fin.getline(author, 100);
					fin.getline(publication, 100);
					fin >> id >> price >> quantity;
				}
				fin.close();
			}
			if (var == 1)
				cout << "\n\n\t\t\tBOOK NOT FOUND";
			cout << "\n\n\n\t\tPress any key to continue";
			(void)_getch();
			if (flag == 1)
				student();
			else
				staff();
		}
		if (sCategory == 6)
		{
			ifstream fin("yearOneBooks.txt", ios::in);
			if (!fin)
				cout << "\n\t\tFile Not Found.";
			else
			{
				cout << "\n\t\tEnter Book's Name: ";
				cin.ignore();
				cin.getline(bookName, 100);
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				while (1)
				{
					if (strcmp(bookName, book) == 0)
					{
						cout << "\n\n\t\t##### SEARCH RESULTS #####\n";
						showData();
						var++;
					}
					if (fin.eof())
						break;
					fin.getline(book, 100);
					fin.getline(author, 100);
					fin.getline(publication, 100);
					fin >> id >> price >> quantity;
				}
				fin.close();
			}
			if (var == 1)
				cout << "\n\n\t\t\tBOOK NOT FOUND";
			cout << "\n\n\n\t\tPress any key to continue";
			(void)_getch();
			if (flag == 1)
				student();
			else
				staff();
		}
		break;
	case 2:
		CLS();
		if (sCategory == 1)
		{
			ifstream fin("csBooks.txt", ios::in);
			if (!fin)
				cout << "\n\t\tFile Not Found.";
			else
			{
				cout << "\n\t\tEnter Book's ID: ";
				cin.ignore();
				cin >> bookID;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				while (1)
				{
					if (strcmp(bookID, id) == 0)
					{
						cout << "\n\n\t\t##### SEARCH RESULTS #####\n";
						showData();
						var++;
					}
					if (fin.eof())
						break;
					fin.getline(book, 100);
					fin.getline(author, 100);
					fin.getline(publication, 100);
					fin >> id >> price >> quantity;
				}
				fin.close();
			}
			if (var == 1)
				cout << "\n\n\t\t\tBOOK NOT FOUND";
			cout << "\n\n\n\t\tPress any key to continue";
			(void)_getch();
			if (flag == 1)
				student();
			else
				staff();
		}
		if (sCategory == 2)
		{
			ifstream fin("eceBooks.txt", ios::in);
			if (!fin)
				cout << "\n\t\tFile Not Found.";
			else
			{
				cout << "\n\t\tEnter Book's ID: ";
				cin.ignore();
				cin >> bookID;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				while (1)
				{
					if (strcmp(bookID, id) == 0)
					{
						cout << "\n\n\t\t##### SEARCH RESULTS #####\n";
						showData();
						var++;
					}
					if (fin.eof())
						break;
					fin.getline(book, 100);
					fin.getline(author, 100);
					fin.getline(publication, 100);
					fin >> id >> price >> quantity;
				}
				fin.close();
			}
			if (var == 1)
				cout << "\n\n\t\t\tBOOK NOT FOUND";
			cout << "\n\n\n\t\tPress any key to continue";
			(void)_getch();
			if (flag == 1)
				student();
			else
				staff();
		}
		if (sCategory == 3)
		{
			ifstream fin("elecBooks.txt", ios::in);
			if (!fin)
				cout << "\n\t\tFile Not Found.";
			else
			{
				cout << "\n\t\tEnter Book's ID: ";
				cin.ignore();
				cin >> bookID;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				while (1)
				{
					if (strcmp(bookID, id) == 0)
					{
						cout << "\n\n\t\t##### SEARCH RESULTS #####\n";
						showData();
						var++;
					}
					if (fin.eof())
						break;
					fin.getline(book, 100);
					fin.getline(author, 100);
					fin.getline(publication, 100);
					fin >> id >> price >> quantity;
				}
				fin.close();
			}
			if (var == 1)
				cout << "\n\n\t\t\tBOOK NOT FOUND";
			cout << "\n\n\n\t\tPress any key to continue";
			(void)_getch();
			if (flag == 1)
				student();
			else
				staff();
		}
		if (sCategory == 4)
		{
			ifstream fin("mechBooks.txt", ios::in);
			if (!fin)
				cout << "\n\t\tFile Not Found.";
			else
			{
				cout << "\n\t\tEnter Book's ID: ";
				cin.ignore();
				cin >> bookID;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				while (1)
				{
					if (strcmp(bookID, id) == 0)
					{
						cout << "\n\n\t\t##### SEARCH RESULTS #####\n";
						showData();
						var++;
					}
					if (fin.eof())
						break;
					fin.getline(book, 100);
					fin.getline(author, 100);
					fin.getline(publication, 100);
					fin >> id >> price >> quantity;
				}
				fin.close();
			}
			if (var == 1)
				cout << "\n\n\t\t\tBOOK NOT FOUND";
			cout << "\n\n\n\t\tPress any key to continue";
			(void)_getch();
			if (flag == 1)
				student();
			else
				staff();
		}
		if (sCategory == 5)
		{
			ifstream fin("civilBooks.txt", ios::in);
			if (!fin)
				cout << "\n\t\tFile Not Found.";
			else
			{
				cout << "\n\t\tEnter Book's ID: ";
				cin.ignore();
				cin >> bookID;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				while (1)
				{
					if (strcmp(bookID, id) == 0)
					{
						cout << "\n\n\t\t##### SEARCH RESULTS #####\n";
						showData();
						var++;
					}
					if (fin.eof())
						break;
					fin.getline(book, 100);
					fin.getline(author, 100);
					fin.getline(publication, 100);
					fin >> id >> price >> quantity;
				}
				fin.close();
			}
			if (var == 1)
				cout << "\n\n\t\t\tBOOK NOT FOUND";
			cout << "\n\n\n\t\tPress any key to continue";
			(void)_getch();
			if (flag == 1)
				student();
			else
				staff();
		}
		if (sCategory == 6)
		{
			ifstream fin("yearOneBooks.txt", ios::in);
			if (!fin)
				cout << "\n\t\tFile Not Found.";
			else
			{
				cout << "\n\t\tEnter Book's ID: ";
				cin.ignore();
				cin >> bookID;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				while (1)
				{
					if (strcmp(bookID, id) == 0)
					{
						cout << "\n\n\t\t##### SEARCH RESULTS #####\n";
						showData();
						var++;
					}
					if (fin.eof())
						break;
					fin.getline(book, 100);
					fin.getline(author, 100);
					fin.getline(publication, 100);
					fin >> id >> price >> quantity;
				}
				fin.close();
			}
			if (var == 1)
				cout << "\n\n\t\t\tBOOK NOT FOUND";
			cout << "\n\n\n\t\tPress any key to continue";
			(void)_getch();
			if (flag == 1)
				student();
			else
				staff();
		}
		break;
	case 3:
		CLS();
		if (flag == 1)
			student();
		else
			staff();
		break;
	default:
		cout << "\n\t\t\t\t\tInvalid choice.\n\n";
		cout << "\n\n\t\t\t\t\tPress any key to be able to enter a valid choice\n\n";
		(void)_getch();
		CLS();
		searchBook(flag);
	}
}

//function to issue books
void Library::issueBook()
{
	CLS();
	int iCategory = booksCategory(2);
	if (iCategory == -1)
	{
		staff();
		return;
	}
	CLS();
	char bookName[100];
	int result = INT_MIN;
	if (iCategory == 1)
	{
		ifstream fin("csBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\t\tEnter Book's Name: ";
			cin.ignore();
			cin.getline(bookName, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(bookName, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
				if (strcmp(bookName, book) == 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity - 1;
			}
		}
		fout.close();
		fin.close();
		remove("csBooks.txt");
		result = rename("tempFile.txt", "csbooks.txt");
	}
	if (iCategory == 2)
	{
		ifstream fin("eceBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\t\tEnter Book's Name: ";
			cin.ignore();
			cin.getline(bookName, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(bookName, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
				if (strcmp(bookName, book) == 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity - 1;
			}
		}
		fout.close();
		fin.close();
		remove("eceBooks.txt");
		result = rename("tempFile.txt", "ecebooks.txt");
	}
	if (iCategory == 3)
	{
		ifstream fin("elecBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\t\tEnter Book's Name: ";
			cin.ignore();
			cin.getline(bookName, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(bookName, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
				if (strcmp(bookName, book) == 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity - 1;
			}
		}
		fout.close();
		fin.close();
		remove("elecBooks.txt");
		result = rename("tempFile.txt", "elecbooks.txt");
	}
	if (iCategory == 4)
	{
		ifstream fin("mechBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\t\tEnter Book's Name: ";
			cin.ignore();
			cin.getline(bookName, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(bookName, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
				if (strcmp(bookName, book) == 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity - 1;
			}
		}
		fout.close();
		fin.close();
		remove("mechBooks.txt");
		result = rename("tempFile.txt", "mechbooks.txt");
	}
	if (iCategory == 5)
	{
		ifstream fin("civilBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\t\tEnter Book's Name: ";
			cin.ignore();
			cin.getline(bookName, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(bookName, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
				if (strcmp(bookName, book) == 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity - 1;
			}
		}
		fout.close();
		fin.close();
		remove("civilBooks.txt");
		result = rename("tempFile.txt", "civilbooks.txt");
	}
	if (iCategory == 6)
	{
		ifstream fin("yearOneBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\t\tEnter Book's Name: ";
			cin.ignore();
			cin.getline(bookName, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(bookName, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
				if (strcmp(bookName, book) == 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity - 1;
			}
		}
		fout.close();
		fin.close();
		remove("yearOneBooks.txt");
		result = rename("tempFile.txt", "yearOnebooks.txt");
	}
	if (result == 0)
		cout << "\n\n\t\t\tBook Issued Successfully.";
	cout << "\n\n\t\t\tPress any key to continue";
	(void)_getch();
	modifyBooklist();
}

//funtion to return book
void Library::returnBook()
{
	CLS();
	int rtCategory = booksCategory(2);
	if (rtCategory == -1)
	{
		staff();
		return;
	}
	CLS();
	char bookName[100];
	int result = INT_MIN;
	if (rtCategory == 1)
	{
		ifstream fin("csBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\t\tEnter Book's Name: ";
			cin.ignore();
			cin.getline(bookName, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(bookName, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
				if (strcmp(bookName, book) == 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity + 1;
			}
		}
		fout.close();
		fin.close();
		remove("csBooks.txt");
		result = rename("tempFile.txt", "csbooks.txt");
	}
	if (rtCategory == 2)
	{
		ifstream fin("eceBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\t\tEnter Book's Name: ";
			cin.ignore();
			cin.getline(bookName, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(bookName, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
				if (strcmp(bookName, book) == 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity + 1;
			}
		}
		fout.close();
		fin.close();
		remove("eceBooks.txt");
		result = rename("tempFile.txt", "ecebooks.txt");
	}
	if (rtCategory == 3)
	{
		ifstream fin("elecBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\t\tEnter Book's Name: ";
			cin.ignore();
			cin.getline(bookName, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(bookName, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
				if (strcmp(bookName, book) == 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity + 1;
			}
		}
		fout.close();
		fin.close();
		remove("elecBooks.txt");
		result = rename("tempFile.txt", "elecbooks.txt");
	}
	if (rtCategory == 4)
	{
		ifstream fin("mechBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\t\tEnter Book's Name: ";
			cin.ignore();
			cin.getline(bookName, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(bookName, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
				if (strcmp(bookName, book) == 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity + 1;
			}
		}
		fout.close();
		fin.close();
		remove("mechBooks.txt");
		result = rename("tempFile.txt", "mechbooks.txt");
	}
	if (rtCategory == 5)
	{
		ifstream fin("civilBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\t\tEnter Book's Name: ";
			cin.ignore();
			cin.getline(bookName, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(bookName, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
				if (strcmp(bookName, book) == 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity + 1;
			}
		}
		fout.close();
		fin.close();
		remove("civilBooks.txt");
		result = rename("tempFile.txt", "civilbooks.txt");
	}
	if (rtCategory == 6)
	{
		ifstream fin("yearOneBooks.txt", ios::in);
		ofstream fout("tempFile.txt", ios::app);
		if (!fin)
			cout << "\n\t\tFile Not Found.";
		else
		{
			cout << "\n\t\tEnter Book's Name: ";
			cin.ignore();
			cin.getline(bookName, 100);
			while (1)
			{
				if (fin.eof())
					break;
				fin.getline(book, 100);
				fin.getline(author, 100);
				fin.getline(publication, 100);
				fin >> id >> price >> quantity;
				if (strcmp(bookName, book) != 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity;
				if (strcmp(bookName, book) == 0)
					fout << book << endl << author << endl << publication << endl << id << endl << price << endl << quantity + 1;
			}
		}
		fout.close();
		fin.close();
		remove("yearOneBooks.txt");
		result = rename("tempFile.txt", "yearOnebooks.txt");
	}
	if (result == 0)
		cout << "\n\n\t\t\tBook Return Success.";
	cout << "\n\n\t\t\tPress any key to continue";
	(void)_getch();
	modifyBooklist();
}

/*================================================================================*/

int main()
{
	int a = 1, w;
	ifstream file1;
	ofstream file2;
	Grade g1;
	char ch5;
	char ch;
	char ch1;
	int ch2;

	do {
		CLS();
		RULE("*");
		cout << "\t\t\tSTUDENT MANAGEMENT SYSTEM";
		RULE("*");
		cout << "\t1. STUDENT INFORMATION SECTION\n";
		cout << "\t2. LIBRARY MANAGEMENT SYSTEM\n";
		cout << "\t0. Exit.\n\n";
		cout << "Enter your choice : ";
		fflush(stdin);
		cin >> ch5;
		if (ch5 == '1')
		{
			fflush(stdin);
			do {
			studentMenu:
				CLS();
				RULE("*");
				cout << "\t\t\tSTUDENT INFORMATION SECTION";
				RULE("*");
				cout << "\t1. Admission Details.\n";
				cout << "\t2. Grading System.\n";
				cout << "\t3. Placement Cell.\n";
				cout << "\t0. Exit.\n\n";
				cout << "Enter your choice : ";
				fflush(stdin);
				cin >> ch1;
				if (ch1 == '1')
				{
					fflush(stdin);
					do {
						CLS();
						RULE("*");
						cout << "\t\t\tSTUDENT INFORMATION SECTION";
						RULE("*");
						cout << "\t\t\t     ADMISSION DETAILS";
						RULE('-');

						cout << "\t1.  Register Student\n";
						cout << "\t2.  Display all Records.\n";
						cout << "\t3.  Search for a Record\n";
						cout << "\t4.  Delete a Record.\n";
						cout << "\t0.  Exit.\n";
						cout << "\nEnter your choice : ";

						cin >> ch2;
						if (cin.fail()) {
							cin.clear();
							cin.ignore(INT_MAX, '\n');
							ch2 = -1;
						}
						switch (ch2)
						{
						case 1:
							insertStudent();
							break;
						case 2:
							dispStudentRecord();
							break;
						case 3:
							searchByRollNo(2);
							break;
						case 4:
							delStudentRecord();
							break;
						}

						fflush(stdin);
						if (ch2)
							cin >> ch;
					} while (ch2 != 0);
				}

				if (ch1 == '2')
				{
					fflush(stdin);
					do {
						CLS();
						RULE("*");
						cout << "\t\t\tSTUDENT INFORMATION SECTION";
						RULE("*");
						cout << "\t\t\t    	GRADING SYSTEM";
						RULE('-');

						cout << "\t1.  Upload Grades\n";
						cout << "\t2.  View All Grades\n";
						cout << "\t3.  Search Grades By Roll Number\n";
						cout << "\t4.  Delete a Grade Record\n";
						cout << "\t0.  Exit.\n";
						cout << "\nEnter your choice : ";

						cin >> w;
						if (cin.fail()) {
							cin.clear();
							cin.ignore(INT_MAX, '\n');
							w = -1;
						}
						switch (w)
						{
						case 1:
							insertGrade();
							break;
						case 2:
							dispGrade();
							break;
						case 3:
							searchGradeByRollNo(2);
							break;
						case 4:
							delGradeRecord();
							break;
						}
						fflush(stdin);
						if (w)
							cin >> ch;
					} while (w != 0);
				}
				// Dibya's Code for Main Function
				if (ch1 == '3')
				{
					fflush(stdin);
				placementMenu:
					int placementChoice;
					do {
						CLS();
						RULE("*");
						cout << "\t\t\tSTUDENT INFORMATION SECTION";
						RULE("*");
						cout << "\t\t\t    	PLACEMENT CELL";
						RULE('-');
						cout << "\t\t\t1. Add Student\n";
						cout << "\t\t\t2. Add Company\n";
						cout << "\t\t\t3. Show Eligible students\n";
						cout << "\t\t\t4. Back\n";
						do {
							cout << "\t\t\tEnter your choice: ";
							cin >> placementChoice;
							if (cin.fail()) {
								cin.clear();
								cin.ignore(INT_MAX, '\n');
								placementChoice = -1;
							}
						} while (placementChoice < 1 || placementChoice > 5);
						int n = 0, m = 0;
						company c[100];
						Students s[100];
						placement p[100];
						switch (placementChoice)
						{

						case 1:
						{
							CLS();
							do {
								cout << "Enter the number of Students who want to sit in placement (1-100): ";
								cin >> n;
								if (cin.fail()) {
									cin.clear();
									cin.ignore(INT_MAX, '\n');
									n = 0;
								}
							} while (n < 1 || n > 100);
							cin.ignore();
							cout << endl;
							RULE('-');
							cout << " \n\nEnter the Students details:- \n ";
							RULE('-');
							for (int i = 0; i < n; i++)
							{
								if (i > 0) cout << endl << endl;
								cout << "##### Student " << i + 1 << " #####" << endl;
								s[i].getSData();
							}
							cout << endl << endl;
							break;
						}
						case 2:
						{
							CLS();
							do {
								cout << "\nEnter the number of Companies (1-100): ";
								cin >> m;
								if (cin.fail()) {
									cin.clear();
									cin.ignore(INT_MAX, '\n');
									m = 0;
								}
							} while (m < 1 || m > 100);
							RULE('-');
							cout << "\n\nEnter the company details: \n";
							RULE('-');
							for (int i = 0; i < m; i++)
							{
								if (i > 0) cout << endl << endl;
								cout << "##### Company " << i + 1 << " #####" << endl;
								c[i].getCData();
							}
							break;
						}
						case 3:
						{
							char companyName[100];
							cin.ignore();
							do {
								cout << "\nEnter Company's Name: ";
								cin.getline(companyName, 100);
							} while (strlen(companyName) == 0);
							char cName[100], sName[100];
							int companyPackage;
							float companyMinCGPA, studentCGPA, studentRoll;
							int eCount = 0;
							ifstream fin("companyList.txt");
							int companyFound = 0;
							while (!(fin.eof()))
							{
								fin.getline(cName, 100);
								if (strlen(cName) == 0) {
									fin.ignore(INT_MAX, '\n');
									fin.ignore(INT_MAX, '\n');
									continue;
								}
								fin >> companyPackage >> companyMinCGPA;
								fin.ignore(1, '\n');
								fin.ignore(INT_MAX, '\n');
								fin.ignore(INT_MAX, '\n');
								if (strcmp(companyName, cName) == 0)
								{
									companyFound = 1;
									break;
								}
							}
							fin.close();
							if (!companyFound)
							{
								cout << "\n\nCompany '" << companyName << "' not found in the records!" << endl;
								break;
							}
							ifstream fin2("studentList.txt");
							while (!(fin2.eof()))
							{
								fin2.getline(sName, 100);
								if (strlen(sName) == 0) {
									fin2.ignore(INT_MAX, '\n');
									fin2.ignore(INT_MAX, '\n');
									continue;
								}
								fin2 >> studentRoll >> studentCGPA;
								fin2.ignore(1, '\n');
								fin2.ignore(INT_MAX, '\n');
								fin2.ignore(INT_MAX, '\n');
								if (studentCGPA >= companyMinCGPA)
								{
									eCount++;
									cout << endl << "##### Student " << eCount << " #####" << endl;
									cout << "\nName: " << sName << endl;
									cout << "\nRoll. No.: " << studentRoll << endl;
									cout << "\nCGPA: " << studentCGPA << endl;
								}
							}
							fin2.close();
							if (eCount == 0)
							{
								cout << "\n\nNo students found with required CGPA " << companyMinCGPA << " for company " << companyName << "." << endl;
							}
							break;
						}
						case 4:
						{
							goto studentMenu;
						}
						case 5:
						{
							exit(0);
						}
						default:
						{
							cout << "\nInvalid Choice. Please try again.";
							goto placementMenu;
						}
						}
						if (placementChoice != 4 && placementChoice != 5)
						{
							cout << "\n\nPress any key to continue...";
							(void)_getch();
						}
					} while (placementChoice != 4 && placementChoice != 5);
				}
			} while (ch1 != '0');
		}

		if (ch5 == '2')
		{
			fflush(stdin);
			CLS();
			Library lib;
			lib.mainMenu();
		}

	} while (ch5 != '0');
	CLS();
	return 0;
}
