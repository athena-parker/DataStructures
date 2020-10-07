/****************************************************************/
/*                Producer Consumer Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "ProducerConsumer.hpp"
#include <iostream>
// you may include more libraries as needed
#include <string>
using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
    cout << "1. Producer (Produce items into the queue)" << endl;
	cout << "2. Consumer (Consume items from the queue)" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}

int main(int argc, char const *argv[])
{
	ProducerConsumer q;
	for(int i=0; i<20; i++)
	{
    q.enqueue("aaa");
	}
for(int i=0; i<10; i++)
{
    q.dequeue();
	}
for(int i=0; i<7; i++)
{
    q.enqueue("bbb");
		cout << i << endl;
	}
cout << "Queue front index: " << q.getQueueFront() << endl;
cout << "Queue back index: " << q.getQueueEnd() << endl;
cout << "Queue size: " << q.queueSize() << endl;
	// string choice;
	// int numitems = 0;
	// int i = 1;
	// int j = 1;
	// string itemi;
	// while (choice != "3")
	// {
	// 	 menu();
	// 	 cin >> choice;
	// 	 switch (stoi(choice))
	// 	 {
	// 		 case 1:
	// 				 cout << "Enter the number of items to be produced:" << endl;
	// 				 cin >> numitems;
	// 				 i = 1;
	// 				 while (i <= numitems)
	// 				 {
	// 					 cout << "Item" << i << ":" << endl;
	// 					 cin >> itemi;
	// 					 q.enqueue(itemi);
	// 					 i++;
	// 				 }
	// 				 break;
	//
	// 		 case 2:
	// 				 cout << "Enter the number of items to be consumed:" << endl;
	// 				 cin >> numitems;
	// 				 j = 1;
	// 				 while (j <= numitems)
	// 				 {
	// 					 if (q.isEmpty())
	// 					 {
	// 						 cout << "No more items to consume from queue" << endl;
	// 						 break;
	// 					 }
	// 					 cout << "Consumed: " << q.peek() << endl;
	// 					 q.dequeue();
	// 					 j++;
	// 				 }
	// 				 break;
	//
	// 		 case 3:
	// 				 cout << "Number of items in the queue:" << q.queueSize() << endl;
	// 				 break;
	//
	// 		 default:
	// 				 cout << "invalid input" << endl;
	// 				 cout << endl;
	// 	 }
	//  }
}
