 
inherit "/std/room";
#include "campdef.h"
#include "/d/Rhovanion/defs.h"
#include "trygo.o"
 
int maxbar;
 
create_room()
{
  object ob;
  set_long("You are in a part of the camp that you find "+
           "obviously evil. "+
           "Usualy there are many barbarians here, who don't "+
           "like other people in his camp. Don't wonder if you "+
           "get attacked!\n"+
           "You also noticed big tent to the north.\n");
  set_short("Usualy looking part of the camp near some tents");
  add_exit(CAMPDIR+"camp7","east",0);
  add_exit(CAMPDIR+"tcamp5","north","@@trygo");
  add_exit(CAMPDIR+"camp5","west","@@trygo");
 
  maxbar=2;
  ob=clone_object(CAMPDIR+"est");
  ob->arming(); ob->move(TO);
  ob=clone_object(CAMPDIR+"est");
  ob->arming(); ob->move(TO);
 
}
 
#include "resetcamp.o"
 
 
