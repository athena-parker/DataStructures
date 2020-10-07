/****************************************************************/
/*                   Assignment 3 Driver File                   */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "CountryNetwork.hpp"
// you may include more libraries as needed

using namespace std;

void displayMenu();

int main(int argc, char* argv[])
{
  string choice;
  string lineCountry;
  string lineMessage;
  CountryNetwork network;
  Country* prev;
  int j = 0;
  int b;
  while (choice != "8")
  {
    displayMenu();
    getline(cin, choice);
    if(choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7" || choice == "8")
    {
      b = stoi(choice);
    }
    else
    {
      b = 0;
    }
    switch(b)
    {
      case 1:
        network.loadDefaultSetup();
        network.printPath();
        cout << endl;
        break;
      case 2:
        network.printPath();
        cout << endl;
        break;
      case 3:
        cout << "Enter name of the country to receive the message:" << endl;
        getline(cin, lineCountry);
        cout << "Enter the message to send:" << endl;
        getline(cin, lineMessage);
        cout << endl;
        network.transmitMsg(lineCountry, lineMessage);
        cout << endl;
        break;
      case 4:
        //while (j == 0)
        {
          cout << "Enter a new country name:" << endl;
          getline(cin, lineCountry);
          cout << "Enter the previous country name (or First):" << endl;
          getline(cin, lineMessage);
          if(lineMessage == "First")
          {
            network.insertCountry(nullptr, lineCountry);
            network.printPath();
            break;
          }
          prev = network.searchNetwork(lineMessage);
          if(prev == nullptr)
          {
            while(prev == nullptr)
            {
              cout << "INVALID country...Please enter a VALID previous country name:" << endl;
              getline(cin, lineMessage);
              if(lineMessage == "First")
              {
                network.insertCountry(NULL, lineCountry);
                network.printPath();
                break;
              }
              prev = network.searchNetwork(lineMessage);
            }
          }
          else
          {
            network.insertCountry(prev, lineCountry);
            network.printPath();
          }
          cout << endl;
          //break;
        }
        break;
      case 5:
        cout << "Enter a country name:" << endl;
        getline(cin, lineCountry);
        network.deleteCountry(lineCountry);
        network.printPath();
        cout << endl;
        break;
      case 6:
        network.reverseEntireNetwork();
        network.printPath();
        cout << endl;
        break;
      case 7:
        network.deleteEntireNetwork();
        cout << endl;
        break;
      case 8:
        cout << "Quitting... cleaning up path: " << endl;
        network.printPath();
        network.deleteEntireNetwork();
        if(network.isEmpty())
        {
          cout << "Path cleaned" << endl;
        }
        else
        {
          cout << "Error: Path NOT cleaned" << endl;
        }
        cout << "Goodbye!" << endl;
        cout << endl;
        break;
      default:
        cout << "invalid input" << endl;
        break;
    }
  }
}

/*
 * Purpose: displays a menu with options
 */
void displayMenu()
{
    cout << endl;
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Transmit Message " << endl;
    cout << " 4. Add Country " << endl;
    cout << " 5. Delete Country " << endl;
    cout << " 6. Reverse Network" << endl;
    cout << " 7. Clear Network " << endl;
    cout << " 8. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
