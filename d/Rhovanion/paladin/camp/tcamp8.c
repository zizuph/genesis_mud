 
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
            "place obviously using to sleep and eat. "+
            "Not many items are around, you just notice couple beds "+
            "and table in the middle of room.\n");
  set_short("Small tent");
  add_exit(CAMPDIR+"camp12","east",0);
  add_item("table","Very dirty table with remains of food.\n");
  add_item(({"bed","beds"}),"These beds don't look very comfortable.\n");
  add_item("food","Very dirty remains of food, but maybe you can "+
           "find something consumable among them.\n");
 
  maxbar=1;
  food_left=1;
  ob=clone_object(CAMPDIR+"est");
  ob->arming(); ob->move(TO);
 
}
 
#include "resetcamp.o"
#include "tryfood.o"
 
 
