 
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
  add_exit(CAMPDIR+"camp8","east",0);
  add_exit(CAMPDIR+"tcamp6","north","@@trygo");
  add_exit(CAMPDIR+"camp6","west","@@tyrgo");
 
  maxbar=3;
  ob=clone_object(CAMPDIR+"est");
  ob->arming(); ob->move(TO);
  ob=clone_object(CAMPDIR+"est");
  ob->arming(); ob->move(TO);
  ob=clone_object(CAMPDIR+"est");
  ob->arming(); ob->move(TO);
 
}
 
#include "resetcamp.o"
 
 
