#include <iostream>
#include <string>
#include <vector>
#include <iomanip> //for setw
#include <fstream> //write a file
#include <unistd.h> //for sleep command

using namespace std; 
const string cClear = "\033[2J\033[1;1H";

//********Class Style**********/
class MenuItemList
{ 
  private:
    string name;
    double itemCost;
    string desc;
    char addLetter;
    char removeLetter;
    int count = 0;
  public:
    void setName(string n) { name = n; }
    void setItemCost(double iT) { itemCost  = iT; }
    void setDesc(string d) { desc = d; }
    void setAddLetter(char aL) { addLetter = aL; }
    void setRemoveLetter(char rL) { removeLetter = rL; }
    void setCount(int c) { count += c; }
    string getName() const { return name; }
    double getItemCost() const { return itemCost; }
    string getDesc() const { return desc; }
    char getAddLetter() const { return addLetter; }
    char getRemoveLetter() const { return removeLetter; }
    int getCount() const { return count; }
    //void print() { //print menu item data on demad }

};


//*******Class Style*********
//function definitions
void populateObjectMenu(vector<MenuItemList> &entireMenu)
{
  //put some default values in our Menu
  const int numItems = 7; 
  MenuItemList Item1; // Item 1 is an object
  MenuItemList Item2;
  MenuItemList Item3; 
  MenuItemList Item4;
  MenuItemList Item5;
  MenuItemList Item6;
  MenuItemList Item7;    

  entireMenu.push_back(Item1); //add to the end of list the Item1
  entireMenu.push_back(Item2); //add to the end of list the Item2
  entireMenu.push_back(Item3); //add to the end of list the Item3
  entireMenu.push_back(Item4); //add to the end of list the Item4
  entireMenu.push_back(Item5); //add to the end of list the Item5
  entireMenu.push_back(Item6); //add to the end of list the Item6
  entireMenu.push_back(Item7); //add to the end of list the Item7

  vector<string> defaultMenuNames = {"Green Tea", "Burrito", "Pasta", "Taco", "Burger", "Pizza", "Lasagna"}; 
  vector<char> defaultAddLetters = {'A', 'B', 'C', 'D', 'E', 'F', 'G'}; 
  vector<char> defaultRemoveLetters = {'a', 'b', 'c', 'd', 'e', 'f', 'g'}; 

  for(int i = 0; i < numItems; i++)
  {
    //add each item to the default list efficiently 
    entireMenu[i].setName(defaultMenuNames[i]); 
    entireMenu[i].setAddLetter(defaultAddLetters[i]); 
    entireMenu[i].setRemoveLetter(defaultRemoveLetters[i]); 
    entireMenu[i].setItemCost(3.00 + i); //set a random starter cost for each item
    entireMenu[i].setCount(0); //initialze all counts to 0
    entireMenu[i].setDesc("delicious"); //set all default desc to "delicous"
  }

    //Menu Description

    //Menu Prices

}

//*******Class Style*******
void showObjectMenu(vector<MenuItemList> &m)
{
  cout << fixed << setprecision(2);//set doubles to 2 decimal places
  cout << "**One Stop Shop**" << endl; 
  cout << "ADD  \tNAME \t COST \tREMOVE\tCOUNT\tDESC"<<endl; 
  for(int i = 0; i < m.size(); i++)
  {
    cout << m[i].getAddLetter() << ")" << setw(10) 
         << m[i].getName() << setw(5) << "$" 
         << m[i].getItemCost() << setw(5) << "(" 
         << m[i].getRemoveLetter() << ")" << setw(7) 
         << m[i].getCount() << setw(13) 
         << m[i].getDesc() 
         <<endl; 
  }

}

void acceptObjectOrder(vector<MenuItemList> &m)
{
  char option = '\0';// the user-selected menu item
  double subtotal = 0.0; 
  double taxRate = 0.0825;
  double tax = 0.0;
  double tip = 0.0;
  double total = 0.0;
  double sumTotal = 0.0;
  double tipTip = 0.0;
  int inputTip;

  char payment;
  double cash;
  double change = 0.0;
  char printReciept;

  do
  {
    cout << "\nPlease choose an item (x to Exit): ";
    cin >> option; 

    for(int i=0; i < m.size(); i++)
    {
      if(option == m[i].getAddLetter())
      {
        cout << "\nMenu Item " << m[i].getAddLetter() << " selected."; 
        m[i].setCount(1); //increment the count by 1
        cout << "\033[2J\033[1;1H"; //clear screen 
        cout << "\n1 UP on " << m[i].getName() << endl;
        subtotal += m[i].getItemCost(); //increment the subtotal by the cost of the item 
        showObjectMenu(m); //show the updated menu
        cout << "\nSubtotal: $" << subtotal << endl;  
      }
      else if(option == m[i].getRemoveLetter())
      {
        cout << "\nRemove Item " << m[i].getRemoveLetter() << " selected."; 
        if(m[i].getCount() > 0) //subtract if and only if the count is > 0
        {
          m[i].setCount(-1); //decrement the count by 1
          cout << "\033[2J\033[1;1H"; //clear screen 
          cout << "\n1 DOWN on " << m[i].getName() << endl;
          subtotal -= m[i].getItemCost(); //decrement the subtotal by the cost of the item
          showObjectMenu(m); //show the updated menu
          cout << "\nSubtotal: $" << subtotal << endl;  
        }
        else //the the user why you blocked item removal 
        {
            
            cout << "\nItem count must be > 0 to remove: " << m[i].getName() << endl;
        }
      }
      else if(
                option != m[i].getAddLetter() && 
                option != m[i].getRemoveLetter() &&
                option != 'x' &&
                option != 'X' 
            ) //test for all of my valid inputs
            {
              if(i == 0)
              {
                cout << "\nInvalid input (" << option << "). Please try again." << endl; 
              }  
            }
    }
  }while(option != 'x' && option != 'X'); 
  cout << "\nThank you for placing your order." << endl; 
  sleep(3);
  cout << "\nYour Subtotal for today is: " << "$" << subtotal << endl;
  sleep(3);

  cout << "\n\nWhat percentage would you like to tip?\n(A 20% tip is suggested): ";
      cin >> inputTip;
      sleep(2);

  tax = subtotal * taxRate;
  total = (subtotal + tax);

  tipTip = (inputTip * (0.010));
  tip = (subtotal * tipTip); 
  sumTotal = total + tip;
  
    cout << "\nSubtotal = $" << subtotal;
    sleep(1);
    cout << "\nTax 0.0825 = $" << tax;
    sleep(1);
    cout << "\nTotal = $" << total;
    sleep(1);
    
    cout << "\n\n" << inputTip << "% Tip = $" << tip;
    sleep(1);
    cout << "\nTotal w/Tip = $" << sumTotal;
    sleep(2);

  cout << "\n\nWhat payment method would you like to use? "<< endl;
  sleep(1);
  cout << "(A) Cash or  (B) Card: " <<endl;
  cin >> payment;

  if(payment == 'a' || payment == 'A')
  {

    cout << "\nPayment Due: $" << sumTotal << endl;
    sleep(1);
    cout << "\nPlease enter the amount of cash: ";
    cin >> cash;
    change = cash - sumTotal;

    cout << "\nPayment = $" << cash;
    sleep(1);
    cout << "\nChange Due = $" << change;
    sleep(1);
    //cout << "\nItems Sold = " << m[i].getCount();
    //sleep(1);


  }

  else if(payment == 'b' || payment == 'B')
  {

    cout << "\nPlease swipe card" << endl;
    sleep(2);
    cout << "\nPayment being processed" << endl;
    sleep(4);
    cout << "\nTransaction was succesful" << endl;
    sleep(1);
    cout << "\nWould you like a recipt? <Y/N> " << endl;
    cin >> printReciept;

    if( printReciept == 'y' || printReciept == 'Y')
    {
    
    cout << "\nPrinting recipt" << endl;

    string color = ""; 
    string reset = "\x1b[0m";

    cout << color << "\n__________________________\n" << reset;

    color = "\x1b[40;1m";

    cout << color << "\nSubtotal = $" << subtotal << reset;
    sleep(1);

    color = "\x1b[40;1m";

    cout << color << "\nTax 0.0825 = $" << tax << reset;
    sleep(1);

    color = "\x1b[40;1m";

    cout << color << "\nTotal = $" << total << reset;
    sleep(1);
    
    color = "\x1b[40;1m";

    cout << color << "\n\n" << inputTip << "% Tip = $" << tip << reset;
    sleep(1);

    color = "\x1b[40;1m";

    cout << color << "\nTotal w/Tip = $" << sumTotal << reset;
    sleep(2);

    color = "\x1b[40;1m";

    cout << color <<"\nPayment = $" << cash << reset;
    sleep(1);

    color = "\x1b[40;1m"; //Green Block (40)

    cout << color << "\nChange Due = $" << change << reset;
    sleep(1);
   
    color = "\x1b[91;1m"; // Green

    cout << color << "\nThank You for your business have a nice day" << endl;

    cout << color << "\n__________________________\n" << reset;
    }

    if( printReciept == 'n' || printReciept == 'N')

    {
        cout << "\nThank You for your business have a nice day" << endl;
    }
  }

      string color = ""; 
      string reset = "\x1b[0m";

    color = "\x1b[91;1m"; //red
    for(int i = 0; i < 50; i++) { cout << color << "_" << reset; }
    cout << endl; 
  fstream reciept;
  reciept.open("reciept.txt",ios::out);

  reciept << fixed << setprecision(2);
  for(int i=0; i < m.size(); i++)
{

  reciept << color << "\n__________________________\n" << reset;
  reciept << color << "\n**One Stop Shop**" << endl;
  reciept << fixed << setprecision(2);
  for(int i=0; i < m.size(); i++)
  reciept << m[i].getCount() 
          << " - "
          << m[i].getName()
          << " - $"
          << m[i].getItemCost()
          << endl;

    reciept << "\nSubtotal = $" << subtotal;
    sleep(1);
    reciept << "\nTax 0.0825 = $" << tax;
    sleep(1);
    reciept << "\nTotal = $" << total;
    sleep(1);
    
    reciept << "\n\n" << inputTip << "% Tip = $" << tip;
    sleep(1);
    reciept << "\nTotal w/Tip = $" << sumTotal;
    sleep(2);

    reciept << "\nPayment = $" << cash;
    sleep(1);
    reciept << "\nChange Due = $" << change;
    sleep(1);

    reciept << "\nThank You for your business have a nice day" << endl;

    reciept << color << "\n__________________________\n" << reset;

  reciept.close();

  
}
}

void printTextReciept(vector<MenuItemList> &m)
{
   cout << "\033[2J\033[1;1H"; //clear screen 
}

  /*fstream html;
  html.open("reciept.html",ios::out);

  html << "<html><head><title>cool</title></head>";
  html << "<body style=\"background-color:#000000;color:#FFFFFF;\">";
  html << "<h1>" << m[0].getName() << "</h1>"<< endl;
  html << "</body></html>";

  html.close();
  */

int main() 
{


//********Class Style**********/

  vector<MenuItemList> objectMenu;

  populateObjectMenu(objectMenu); //put some default values in the menu

  showObjectMenu(objectMenu); //show the initial menu on screen 

  acceptObjectOrder(objectMenu);//solve and call acceptObjectOrder void function here


  printTextReciept(objectMenu);

  return 0; 
}