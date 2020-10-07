#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

#include "course.hpp"

using namespace std;

string makeToCaps(string s)
{
  for(int i = 0; i < s.length(); i++)
  {
	s[i] = toupper(s[i]);
  }
  return s;
}


Course::Course(int size, string name){
	tableSize = size;
	table = new Student*[size];
	for(int i = 0; i < size; i++){
		table[size] = nullptr;
	}
	numStudents = 0;
	className = name;
	maxID = 0;
  numOfAssignments = 0;

  zero = new Student();
  zero -> firstName = "zero";
  zero -> lastName = "zero";
  zero -> id = 0;
  zero -> grade = 0;
  zero -> letter = "F";
  zero -> assignments.reserve(200);

}

Course::~Course()
{
  tableSize = 0;
  delete[] table;
  numStudents = 0;
  maxID = 0;
  className = "";
}

int Course::getHash(string word)
{
	int hashValue = 5381;
	int length = word.length();
	for (int i=0;i<length;i++)
	{
		hashValue=((hashValue<<5)+hashValue) + word[i];
	}
	hashValue %= tableSize;
	return hashValue;
}

string email(string first, string last)
{
  char g = '.';
	string f = "@idaho";
  string j = "edu";
	string e = first + last;
  e += f;
  e += g;
  e += j;
  return e;
}

void Course::addStudent(string first, string last)
{
	string hash = hashName(first,last);
	Student *tmp = new Student();
	tmp -> firstName = makeToCaps(first);
  tmp -> lastName =  makeToCaps(last);
	maxID++;
	tmp -> id = maxID;
  tmp -> email = email(first, last);
  tmp -> grade = -1;
  tmp -> letter = "Z";

  if(tmp->id%2 == 0)
  {
    tmp->tutor = true;
  }
  else
  {
    tmp->tutor = false;
  }
  tmp-> assignments.reserve(200);

  for(int i = 0; i < zero -> assignments.size(); i++)
  {
    tmp -> assignments.push_back(zero -> assignments[i]);
  }

    int pos = getHash(hash);
    tmp -> next = table[pos];
    table[pos] = tmp;

    studs[numStudents] = tmp;
    numStudents++;

    cout << "Adding: " << first << " " << last << " ID: " << tmp->id << endl;

}

float Course::calculateGrade(string first, string last){

  Student *s = findStudent(first, last);

  bool hw = false;
  int numHW = 0;
  float hwGrade = 0;

  bool test;
  int numTest = 0;
  float testGrade = 0;


  float grade = 0;

  for(int i = 0; i < s -> assignments.size(); i++){
    if( s -> assignments[i].score != -1){
      if(s -> assignments[i].category == 1){
        test = true;
        numTest++;
        testGrade += (float)s ->assignments[i].score / (float)s -> assignments[i].maxScore;
      }
      if(s -> assignments[i].category == 2){
        hw = true;
        numHW++;
        hwGrade += (float)s ->assignments[i].score / (float)s -> assignments[i].maxScore;
      }
    }

  }




  float totalWeight = 0;
  if(hw){
    hwGrade /= numHW;
    totalWeight += 0.1;
    grade += (0.1) * hwGrade;
  }
  if(test){
    testGrade /= numTest;
    totalWeight += 0.3;
    grade += (0.3) * testGrade;
  }


  grade /= totalWeight;
  if(grade >= .93){
    s -> letter = "A";
  }
  else if( grade >= .90){
    s -> letter = "A-";
  }
  else if( grade >= .83){
    s -> letter = "B";
  }
  else if( grade >= .80){
    s -> letter = "B-";
  }
  else if( grade >= .73){
    s -> letter = "C";
  }
  else if( grade >= .70){
    s -> letter = "C-";
  }
  else if(grade >= .63){
    s -> letter = "D";
  }
  else if( grade >= .60){
    s -> letter = "D-";
  }
  else {
    s -> letter = "F";
  }

  return grade;
}

bool Course::isInTable(string first, string last)
{
	if(findStudent(first, last) == nullptr)
  {
		return false;
	}
	return true;
}

Student* Course::findStudent(string first, string last)
{
	string hashname = hashName(first, last);
	int i = getHash(hashname);
	Student *tmp = table[i];
	while(tmp)
  {
		if(tmp -> firstName == first && tmp -> lastName == last)
    {
			return tmp;
		}
		tmp = tmp -> next;
	}
	return nullptr;
}

int Course::findAssignment(string name)
{
  for(int i = 0; i < numOfAssignments; i++)
  {
    if(zero->assignments[i].name == name)
    {
      return i;
    }
  }
  return -1;
}

string Course::hashName(string firstName, string lastName)
{
	string hash = makeToCaps(firstName) + makeToCaps(lastName);
	return hash;
}

void Course::addAssignment(string name, int category, int maxScore) //creates an empty assignment
{
  Assignment a;
  a.name = name;
  a.category = category;
  a.maxScore = maxScore;
  a.score = -1;

  if(category == 2){
    a.weight = 0.1;
  }
  else if(category == 1){
    a.weight = 0.3;
  }

  zero->assignments.push_back(a);

  for(int i = 0; i < numStudents; i++)
  {
    studs[i]->assignments.push_back(a);
  }
  numOfAssignments++;
}

void Course::addGrades(int numAssignment, int scores[], int counter) //adds grades for one assignment for all students.
{
  if(counter != numStudents )
  {
    cout << "Number of grades in file not equal to number of students" << endl;
    return;
  }
  for(int i = 0; i < numStudents; i++)
  {
    cout << "Insert Grade for " << studs[i] -> firstName << " " << studs[i] -> lastName << ": ";
    studs[i] -> assignments[numAssignment].score = scores[i];
    cout << scores[i] << endl;
    studs[i] -> grade = calculateGrade(studs[i]->firstName, studs[i]->lastName) * 100;
  }
}

void Course::changeGrade(string first, string last, int numAssignment, int newScore) //changes a students grade for one assignment
{
  Student *s = findStudent(first, last);
  if(s == nullptr)
  {
    cout << "Student not found" << endl;
    return;
  }
  s -> assignments[numAssignment].score = newScore;

  float grade = calculateGrade(first, last);
  s -> grade = grade * 100;
}

void Course::viewAssignment(int numAssignments) //shows every student and their grades for one assignment
{
  cout << endl << endl;
  cout << "Assignment: " << zero->assignments[numAssignments].name << endl;
  cout << "Maximum Score: " << zero->assignments[numAssignments].maxScore << endl;
  for(int i = 0; i < numStudents; i++)
  {
    if(studs[i] -> assignments[numAssignments].score != -1){
       cout << studs[i]->firstName << " " << studs[i]->lastName << " " << studs[i]->id << ": ";
      cout << studs[i]->assignments[numAssignments].score << endl;
    }
    else{
       cout << studs[i]->firstName << " " << studs[i]->lastName << " " << studs[i]->id << ": Ungraded" << endl;
    }

  }
  cout << endl << endl;
}


void Course::viewStudent(string first, string last)
{
  cout << endl << endl;
	Student *s = findStudent(first, last);
	if(s == nullptr)
  {
		cout << "STUDENT NOT FOUND" << endl;
		return;
	}
	cout << s -> firstName << " " << s -> lastName << endl;
	cout << "Student Grade: " << s -> grade << endl;
	cout << "Letter Grade: " << s -> letter << endl;
	cout << "Email: " << s -> email << endl << endl;
	for(int i = 0; i < s -> assignments.size(); i++)
  {
		cout << s -> assignments[i].name << ":"<<  endl;
		if(s -> assignments[i].score != -1)
    {
			cout << s -> assignments[i].score << "/" << s -> assignments[i].maxScore << endl;
		}
		else
    {
			cout << "No grade" << endl;
		}
		cout << endl;
	}
  cout << endl << endl;
}

void Course::deleteStudent(string first, string last)
{
  Student* s = findStudent(first, last);
  if(s == nullptr)
  {
    cout << "Student not found" << endl;
    return;
  }
  for(int i = 0; i < numStudents; i++)
  {
    if(studs[i] == s)
    {
      for(int j = i; j < numStudents - 1; j++)
      {
        studs[j] = studs[j+1];
      }
    }
  }
  delete s;
  numStudents--;
}

void Course::viewFinalGrade(string firstName, string lastName)
{
  cout << endl << endl;
  Student *s = findStudent(firstName, lastName);
  if (s == nullptr)
  {
    cout << "Student not found" << endl;
    return;
  }
  cout << s->firstName << " " << s->lastName << ": " << setprecision(2) << fixed << s->grade << "%" <<endl;
  cout << "Letter Grade: " << s-> letter << endl << endl;
}

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void heapify(Student* arr[], int n, int i)
{
  int largest = i;
  int l = 2*i + 1;
  int r = 2*i + 2;

  if (l < n && arr[l]->grade > arr[largest]->grade)
  {
    largest = l;
  }

  if (r < n && arr[r]->grade > arr[largest]->grade)
  {
    largest = r;
  }

  if (largest != i)
  {
    swap(arr[i], arr[largest]);
    heapify(arr, n, largest);
  }
}

void heapSort(Student* arr[], int n)
{
  for (int i = n/2-1; i>=0; i--)
  {
    heapify(arr, n, i);
  }

  for (int i = n-1; i>=0; i--)
  {
    swap(arr[0], arr[1]);
    heapify(arr, i, 0);
  }
}

float Course::nameCompare(string first, string last)
{
  for (int i=0;i<numStudents;i++)
  {
    if ((studs[i]->firstName == first) && (studs[i]->lastName == last))
    {
      return studs[i]->grade;
    }
  }
  return 0;
}

int Course::requestTutor(string first, string last)
{
  bool haveTutor = false;
  heapSort(studs, numStudents);
  nameCompare(first, last);
  for (int i=0;i<numStudents;i++)
  {
    if ((studs[i]->grade >= nameCompare(first, last)))
    {
      if (studs[i]->tutor == true)
      {
        if ((studs[i]->firstName != first) && (studs[i]->firstName != last))
          {
            cout<<"\nHere is your tutor:"<<endl;
            cout<<studs[i]->firstName<<" "<<studs[i]->lastName<<endl;
            cout<<studs[i]->email<<endl;
            cout<<"Please send "<<studs[i]->firstName<<" an email with your topic concerns as well as the time and place that you would like to meet.\n"<<endl;
            studs[i]->tutor = false;
            return 0;
          }
      }
    }
  }
  for (int i=0;i<numStudents;i++)
  {
    if ((studs[i]->grade <= nameCompare(first, last)))
    {
      if (studs[i]->tutor == true)
      {
        if ((studs[i]->firstName != first) && (studs[i]->firstName != last))
          {
            cout<<"\nHere is your tutor:"<<endl;
            cout<<studs[i]->firstName<<" "<<studs[i]->lastName<<endl;
            cout<<studs[i]->email<<endl;
            cout<<"Please send "<<studs[i]->firstName<<" an email with your topic concerns as well as the time and place that you would like to meet.\n"<<endl;
            studs[i]->tutor = false;
            return 0;
          }
      }
    }
  }
  return 0;
}

bool Course::checkID(string first, string last, int id)
{

  if(findStudent(makeToCaps(first), makeToCaps(last)) == nullptr){
    cout << "STUDENT DOES NOT EXIST" << endl;
    return false;
  }

  cout << findStudent(first, last) -> id << endl;
  if(findStudent(first, last)->id == id)
  {
    return true;
  }
  return false;
}
