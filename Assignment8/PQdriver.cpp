#include "PriorityQueue.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;


void menu()
{
	cout << "============Main Menu============" << endl;
	cout << "1. Get group information from file" << endl;
	cout << "2. Add a group to Priority Queue" << endl;
  cout << "3. Show next group in the queue" << endl;
  cout << "4. Serve Next group" << endl;
  cout << "5. Serve Entire Queue" << endl;
  cout << "6. Quit" << endl;
}

int main(int argc, char const *argv[])
{
	PriorityQueue pq(stoi(argv[1]));
  int totalCookTime = 0;
  string choice;
  //for case 1
  ifstream file;
  string filename;
  string reservation;
  string resArr[3];
  int numPieces;
  string piece;
  //for case 2
  string gName;
  string gSize;
  string gTime;
	while (choice != "6")
	{
		 menu();
		 getline(cin, choice);
		 switch (stoi(choice))
		 {
			 case 1: //read from file
					 cout << "Enter filename:" << endl;
           getline(cin, filename);
           file.open(filename);
           while(getline(file, reservation))
           {
             numPieces = 0;
             stringstream ss(reservation);
             while(getline(ss, piece, ' '))
             {
               if(piece!= "")
               {
                 resArr[numPieces] = piece;
                 numPieces++;
               }
             }
             pq.enqueue(resArr[0], stoi(resArr[1]), stoi(resArr[2]));
           }
					 break;

			 case 2: //add group to queue
           if(pq.isFull())
           {
             cout << "Heap full, cannot enqueue" << endl;
             break;
           }
           else
           {
             cout << "Enter Group Name:" << endl;
             getline(cin, gName);
             cout << "Enter Group Size:" << endl;
             getline(cin, gSize);
             cout << "Enter Estimated Cooking Time:" << endl;
             getline(cin, gTime);
             pq.enqueue(gName, stoi(gSize), stoi(gTime));
           }
					 break;

       case 3: //show next group in queue
          if(pq.isEmpty())
          {
            cout << "Heap empty, nothing to peek" << endl;
            break;
          }
          else
          {
            cout << "Group Name: " << pq.peek().groupName << endl;
            cout << "Group Size: " << pq.peek().groupSize << endl;
            cout << "Group Time: " << pq.peek().cookingTime << endl;
          }
          break;

       case 4: //serve next group
          if(pq.isEmpty())
          {
            cout << "Heap empty, cannot dequeue" << endl;
            break;
          }
          else
          {
            totalCookTime += pq.peek().cookingTime;
            cout << "Group Name: " << pq.peek().groupName << " - Total Cook Time for the Group: " << totalCookTime << endl;
            pq.dequeue();
          }
          break;

       case 5: //serve entire queue
          if(pq.isEmpty())
          {
            cout << "Heap empty, cannot dequeue" << endl;
            break;
          }
          else
          {
            while(!pq.isEmpty())
            {
              totalCookTime += pq.peek().cookingTime;
              cout << "Group Name: " << pq.peek().groupName << "- Total Cook Time for the Group: " << totalCookTime << endl;
              pq.dequeue();
            }
          }
          break;

       case 6: //quit
           cout << "Goodbye!" << endl;
           break;

			 default:
					 cout << "invalid input" << endl;
					 cout << endl;
           break;
		 }
	 }
}
