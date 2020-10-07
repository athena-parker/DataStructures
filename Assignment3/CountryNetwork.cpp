/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork()
{
  head = NULL;
}


/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CountryNetwork::isEmpty()
{
  if (head == NULL)
  {
    return true;
  }
  else
  {
    return false;
  }
}


/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
 void CountryNetwork::insertCountry(Country* previous, string countryName)
 {
    Country* node = new Country;
    node->name = countryName;
    // if(head == NULL)
    // {
    //   head = node;
    //   cout << "adding: " << countryName << " (HEAD)" << endl;
    // }
    if (previous == NULL)
    {
      node->next = head;
      head = node;
      cout << "adding: " << countryName << " (HEAD)" << endl;
    }
    else
    {
      node->next = previous->next;
      previous->next = node;
      cout << "adding: " << countryName << " (prev: " << previous->name << ")" << endl;
    }
 }


/*
 * Purpose: delete the country in the network with the specified name.
 * @param countryName name of the country to delete in the network
 * @return none
 */
 void CountryNetwork::deleteCountry(string countryName)
 {
   if(head == nullptr)
   {
     cout << "Country does not exist." << endl;
     return;
   }
   if (head->name == countryName)
   {
     Country* temp = head;
     head = head->next;
     delete temp;
   }
   else
   {
     Country* toDelete = searchNetwork(countryName);
     if(toDelete == nullptr)
     {
       cout << "Country does not exist." << endl;
       return;
     }
     bool found = false;
     Country* temp = head;
     while (temp != NULL && !found)
     {
       if (temp->next == toDelete)
       {
         temp->next = toDelete->next;
         delete toDelete;
         found = true;
       }
       else
       {
         temp = temp->next;
       }
     }
   }
 }


/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
 void CountryNetwork::loadDefaultSetup()
 {
   deleteEntireNetwork();
   insertCountry(NULL, "United States");
   insertCountry(head, "Canada");
   insertCountry(head->next, "Brazil");
   insertCountry(head->next->next, "India");
   insertCountry(head->next->next->next, "China");
   insertCountry(head->next->next->next->next, "Australia");
 }


/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 * @see insertCountry, deletecountry
 */
 Country* CountryNetwork::searchNetwork(string countryName)
 {
   Country* temp = head;
   Country* returnNode = NULL;
   bool found = false;
   while(!found && temp != NULL)
   {
     if(temp->name == countryName)
     {
       found = true;
       returnNode = temp;
     }
     else
     {
       temp = temp->next;
     }
   }
   return returnNode;
 }


/*
 * Purpose: deletes all countries in the network starting at the head country.
 * @param none
 * @return none
 */
 void CountryNetwork::deleteEntireNetwork()
 {
   if (head == nullptr)
   {
     return;
   }
   Country* temp = head;
   Country* n;
   while(temp != NULL)
   {
     cout << "deleting: " << temp->name << endl;
     n = temp->next;
     free(temp);
     temp = n;
   }
   head = NULL;
   cout << "Deleted network" << endl;
 }


/*
 * Purpose: Transmit a message across the network to the
 *   receiver. Msg should be stored in each country it arrives
 *   at, and should increment that country's count.
 * @param receiver name of the country to receive the message
 * @param message the message to send to the receiver
 * @return none
 */
 void CountryNetwork::transmitMsg(string receiver, string message)
 {
   if(head == NULL)
   {
     cout << "Empty list" << endl;
   }
   head->message = message;
   head->numberMessages++;
   cout << head->name << " [# messages received: " << head->numberMessages << "] received: " << head->message << endl;
   Country* temp = head->next;
   Country* p = head;
   bool done = false;
   while (p->name != receiver)
   {
     temp->message = message;
     temp->numberMessages++;
     cout << temp->name << " [# messages received: " << temp->numberMessages << "] received: " << temp->message << endl;
     temp = temp->next;
     p = p->next;
   }
 }


/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
 void CountryNetwork::printPath()
 {
   if(head == NULL)
   {
     cout << "== CURRENT PATH ==" << endl;
     cout << "nothing in path" << endl;
     cout << "===" << endl;
   }
   else
   {
     Country* temp = head;
     cout << "== CURRENT PATH ==" << endl;
     while (temp != nullptr)
     {
       cout << temp->name << " -> ";
       temp = temp->next;
     }
     cout << "NULL" << endl;
     cout << "===" << endl;
   }
 }


/*
 * Purpose: reverse the entire network t
 * @param ptr head of list
 */
 void CountryNetwork::reverseEntireNetwork()
 {
   Country* temp = head;
   Country* n = NULL;
   Country* p = NULL;
   while(temp != NULL)
   {
     n = temp->next;
     temp->next = p;
     p = temp;
     temp = n;
   }
   head = p;
 }
