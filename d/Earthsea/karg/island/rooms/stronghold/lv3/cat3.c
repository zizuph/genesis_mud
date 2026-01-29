#include "defs.h"

inherit STD_STRHOLD;

object catapult;

void create_stronghold_room()
{
 set_short("Small storage room");
 set_long("@@get_long");

 add_exit(STRHOLD_LVL3+"cor11","southwest");

 reset_room();
}

string get_long()
{
 string res="This is some kind of storage room , but it looks "+
   "surprisingly empty";

 if(catapult) return res+", except of large calapult standing "+
   "in the middle of the room.\n";
 return res+".\n";
}

void reset_catapult()
{
 if(catapult) return;

 catapult=clone_object(STRHOLD_OBJ+"catapult");
 catapult->set_cat_id(32);
 catapult->move(TO);
}

