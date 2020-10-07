#include <iostream>
#include <string>
#include <fstream>
#include "course.hpp"
using namespace std;

string makeCaps(string s)
{
  for(int i = 0; i < s.length(); i++)
  {
    s[i] = toupper(s[i]);
  }
  return s;
}

void printStudentMenu()
{
  cout << "===== Student Portal ====" << endl;
  cout<<"1. View Grades For All Assignments"<<endl;
  cout<<"2. View Your Final Grade"<<endl;
  cout<<"3. Request Tutoring"<<endl;
  cout<<"4. Log Out"<<endl;
  cout << "Enter your choice (1-4): ";
}

void printTeacherMenu()
{
  cout << "===== Teacher Portal ====" << endl;
  cout<<"1. Create An Assignment"<<endl;
  cout<<"2. Grade An Assignment"<<endl;
  cout<<"3. View All Student Grades For An Assignment"<<endl;
  cout<<"4. View All Assignment Grades For A Student"<<endl;
  cout<<"5. Add A Student"<<endl;
  cout<<"6. Delete A Student"<<endl;
  cout<<"7. Log Out"<<endl;
  cout << "Enter your choice (1-7): ";
}

void mainMenu()
{
  cout << endl << endl << endl;
  cout << "Welcome to the world famous University of Idaho! " << endl;
  cout << "================================================" << endl;
  cout << "1. Student" << endl;
  cout << "2. Teacher" << endl;
  cout << "3. Exit" << endl;
  cout << "Enter your choice (1-3): ";
}

void addMenu()
{
  cout << endl << endl;
  cout << "1. Add Individual student" << endl;
  cout << "2. Add Students from File" << endl;
  cout << "Enter your choice (1-2): ";
}

void assignMenu()
{
  cout << endl << endl;
  cout << "1. Add or change single grade" << endl;
  cout << "2. Import grades from file" << endl;
  cout << "Enter your choice (1-2): ";
}

int main(int argc, char const *argv[])
{
  Course c(50, "Starch");

  c.addStudent("DHRUV", "PATEL");
  c.addStudent("ZAHRAA", "ABBASI");
  c.addStudent("ATHENA", "PARKER");

  string option1;
  string option2;
  string option3;

  string subOp1;
  string subOp2;
  string subOp3;

  string firstName;
  string lastName;
  string password;

  int num;

  int grades[200];
  int gradeCounter = 0;

  ifstream in;
  string file;
  string line;
  option1 = -1;

  while(option1 != "3")
  {
    mainMenu();
    getline(cin, option1);
    if (option1 == "1")
    {
      cout<< "Please enter your first name: " <<endl;
      getline(cin, firstName);
      cout<< "Please enter your last name: " <<endl;
      getline(cin, lastName);
      cout<<"Please enter your student ID: "<<endl;
      getline(cin, password);
      cout << endl << endl;
      cout << "Logging in... " << endl;
      if (c.checkID(makeCaps(firstName), makeCaps(lastName), stoi(password)))
      {
        cout << endl << endl << "Welcome to the Student Portal" << endl;
        option2 = -1;
        while(option2 != "4")
        {
            printStudentMenu();
            getline(cin, option2);
            if(option2 == "1") //view grades for all assignments
            {
              c.viewStudent(makeCaps(firstName), makeCaps(lastName));
            }
            else if(option2 == "2") //view final grade
            {
              c.viewFinalGrade(makeCaps(firstName), makeCaps(lastName));
            }
            else if(option2 == "3") //request tutoring
            {
              c.requestTutor(makeCaps(firstName), makeCaps(lastName));
            }
            else if(option2 == "4") //log out
            {
              cout << "goodbye" << endl;
            }
            else
            {
              cout << "Invalid Input" << endl << endl;
            }
        }
      }
      else
      {
        cout << "Login Failed" << endl << endl;
      }
    }
    else if (option1 == "2")
    {
      cout<<"Please enter your first name: "<<endl;
      getline(cin, firstName);
      cout<<"Please enter your last name: "<<endl;
      getline(cin, lastName);
      cout<<"Please enter your password: "<<endl;
      getline(cin, password);
      cout << endl << endl;
      option3 = -1;
      while(option3 != "7")
      {
          printTeacherMenu();
          getline(cin, option3);
          if(option3 == "1") //create an assignment
          {
            cout << "Enter Assignment Name: ";
            getline(cin, subOp1);
            cout << "Enter Assignment Category (1 for test, 2 for homework): ";
            getline(cin, subOp2);
            cout << "Enter Assignment Max Score: ";
            getline(cin, subOp3);
            c.addAssignment(makeCaps(subOp1), stoi(subOp2), stoi(subOp3));
          }
          else if(option3 == "2") //grade an assignment
          {
            gradeCounter = 0;
            cout << "Enter the name of the assignment: ";
            getline(cin, subOp1);
            num = c.findAssignment(makeCaps(subOp1));
            if(num == -1)
            {
              cout << "Invalid Assignment" << endl;
            }
            else
            {
              assignMenu();
              getline(cin, subOp1);
              if(subOp1 == "2")
              {
                cout << "Enter file name: " << endl;
                getline(cin, file);
                in.open(file);
                if(in.is_open()){
                  while( in >> line){
                    grades[gradeCounter] = stoi(line);
                    gradeCounter++;
                  }
                  c.addGrades(num, grades, gradeCounter);
                }
                else{
                  cout << "Invalid file name: " << endl;
                }
                in.close();
              }
              else if(subOp1 == "1")
              {
                cout << "Enter Student First Name: " << endl;
                getline(cin, firstName);
                cout << "Enter Student Last Name: " << endl;
                getline(cin, lastName);
                cout << "Enter New Score: " << endl;
                getline(cin, subOp1);
                c.changeGrade(makeCaps(firstName), makeCaps(lastName), num, stoi(subOp1));
              }
              else
              {
                cout << "Invalid Choice" << endl;
              }
            }
          }
          else if(option3 == "3") //view all student grades for assignment
          {
            cout << "Enter the name of the assignment" << endl;
            getline(cin, subOp1);
            num = c.findAssignment(makeCaps(subOp1));
            if(num == -1)
            {
              cout << "Invalid Assignment" << endl;
            }
            else
            {
              c.viewAssignment(num);
            }
          }
          else if(option3 == "4") //view all assignment grades for student
          {
            cout << "Enter Student First Name: ";
            getline(cin, firstName);
            cout << "Enter Student Last Name: ";
            getline(cin, lastName);
            if(!c.isInTable(makeCaps(firstName), makeCaps(lastName)))
            {
              cout << "Student Not Found" << endl;
            }
            else
            {
              c.viewStudent(makeCaps(firstName), makeCaps(lastName));
            }
          }
          else if(option3 == "5") //add a student
          {
            addMenu();
            getline(cin, subOp1);
            if(subOp1 == "1")
            {
              cout << "Enter Student First Name: ";
              getline(cin, firstName);
              cout << "Enter Student Last Name: ";
              getline(cin, lastName);
              c.addStudent(makeCaps(firstName), makeCaps(lastName));
            }
            else if(subOp1 == "2")
            {
              cout << "Enter file name" << endl;
              getline(cin, file);
              in.open(file);
              if(in.is_open()){
                while(getline(in, line)){
                  for(int i = 0; i < line.length(); i++){
                    if(line[i] == ' '){
                      c.addStudent(makeCaps(line.substr(0, i)), makeCaps(line.substr(i + 1)));
                    }
                  }
                }
              }
              else{
                cout << "Invalid file name" << endl;
              }
              in.close();
            }
            else
            {
              cout << "Invalid Input" << endl << endl;
            }
          }
          else if(option3 == "6") //delete a student
          {
            cout << "Enter Student First Name: ";
            getline(cin, firstName);
            cout << "Enter Student Last Name: ";
            getline(cin, lastName);
            if(!c.isInTable(makeCaps(firstName), makeCaps(lastName)))
            {
              cout << "Student Not Found" << endl;
            }
            else
            {
              c.deleteStudent(makeCaps(firstName), makeCaps(lastName));
            }
          }
          else if(option3 == "7") //log out
          {
            cout << "goodbye" << endl << endl;
          }
          else
          {
            cout << "Invalid Input" << endl << endl;
          }
        }
    }
    else if(option1 == "3"){
      cout << "Goodbye!" << endl;
    }
    else
    {
      cout << "Invalid Input" << endl << endl;
    }
    cout << endl;
  }
  return 0;
}
