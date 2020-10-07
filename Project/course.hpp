#ifndef COURSE_HPP
#define COURSE_HPP

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Assignment
{
  int numAssignment;
  string name;
  int category;
  int maxScore;
  int score;
  float weight;
};

struct Student
{
    string firstName;
    string lastName;
    int id;
    vector <Assignment> assignments;
    float grade;
    string letter;
    Student *next;
    bool tutor;
    string email;
};



class Course
{
public:
    Course(int size, string name);
    ~Course();

    void addStudent(string firstName, string lastName);   //creates the hashname and adds the student to the hashtable
    bool isInTable(string first, string last); //used to check if we try putting duplicates

    void addAssignment(string name, int category, int maxScore); //creates an empty assignment
    void addGrades(int numAssignment, int scores[], int counter); //adds grades for one assignemt for all students.

    Student* findStudent(string first, string last); //well finds a student
    int findAssignment(string name);
    void changeGrade(string first, string last, int numAssignment, int newScore); //changes a students grade for one assignment

    void viewAssignment(int numAssignments); //shows every student and their grades.
    void viewStudent(string first, string last); //shows a student and all their grades

    void deleteStudent(string first, string last);

    void viewFinalGrade(string firstName, string lastName);

    float nameCompare(string first, string last);
    int requestTutor(string first, string last);

    bool checkID(string first, string last, int id);

    float calculateGrade(string first, string last);

    int getHash(string name);
    string hashName(string first, string last);

private:
    string className;
    Student** table;
    int tableSize;
    int numStudents;
    int maxID;
    int numOfAssignments;
    Student* studs[200];

    Student* zero;

};

#endif
