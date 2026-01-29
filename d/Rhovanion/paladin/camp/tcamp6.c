 
inherit "/std/room";
#include "campdef.h"
#include "/d/Rhovanion/defs.h"
#include "trygo.o"
 
int maxbar;
int food_left;
 
create_room()
{
  object ob;
  set_long("You are inside big tent. Usually there are many "+
           "barbarians inside.. You'd better run away quickly!\n"+
           "You notice big table in the middle of room and some "+
           "beds close to walls. \n");
  set_short("Big tent");
  add_exit(CAMPDIR+"camp7","south",0);
  add_item("table","Very dirty table with remains of food.\n");
  add_item(({"bed","beds"}),"These beds don't look very comfortable.\n");
  add_item("food","Very dirty remains of food, but maybe you can "+
           "find something consumable among them.\n");
 
  maxbar=3;
  ob=clone_object(CAMPDIR+"est");
  ob->arming(); ob->move(TO);
  ob=clone_object(CAMPDIR+"est");
  ob->arming(); ob->move(TO);
  ob=clone_object(CAMPDIR+"est");
  ob->arming(); ob->move(TO);
  food_left=1;
 
}
 
#include "resettent.o"
#include "tryfood.o"
 
 
