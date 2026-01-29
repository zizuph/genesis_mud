 
inherit "/std/room";
#include "campdef.h"
#include "/d/Rhovanion/defs.h"
#include "trygo.o"
 
int maxbar;
int food_left;
 
create_room()
{
  object ob;
  set_long("You are inside small tent. This tent looks like "+
            "place usually using to sleep and eat. "+
            "Not many items are around, you just notice couple beds "+
            "and table in the middle of room.\n");
  set_short("Small tent");
  add_exit(CAMPDIR+"camp23","west",0);
  add_item("table","Very dirty table with remains of food.\n");
  add_item(({"bed","beds"}),"These beds don't look very comfortable.\n");
  add_item("food","Very dirty remains of food, but maybe you can "+
           "find something consumable among them.\n");
 
  maxbar=2;
  ob=clone_object(CAMPDIR+"est");
  ob->arming(); ob->move(TO);
  ob=clone_object(CAMPDIR+"est");
  ob->arming(); ob->move(TO);
  food_left=1;
 
}
 
#include "resettent.o"
#include "tryfood.o"
 
 
