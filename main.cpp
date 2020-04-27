#include "Transaction.h"

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