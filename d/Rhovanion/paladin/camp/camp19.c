 
inherit "/std/room";
#include "campdef.h"
#include "/d/Rhovanion/defs.h"
#include "trygo.o"
 
int maxbar;
 
create_room()
{
  object ob;
  set_long("You're standing just in the middle of the evil camp."+
           " You noticed that there are more guards here, than "+
           "elsewhere! You'd better quickly run out from here !\n");
  set_short("Middle part of the camp");
  add_exit(CAMPDIR+"camp25","south",0);
  add_exit(CAMPDIR+"camp13","north","@@trygo");
  add_exit(CAMPDIR+"camp18","west","@@trygo");
  add_exit(CAMPDIR+"camp20","east","@@trygo");
  add_exit(CAMPDIR+"wcamp2","southwest","@@trygo");
  add_exit(CAMPDIR+"gcamp1","northeast","@@trygo");
 
  maxbar=10;
  ob=clone_object(CAMPDIR+"est");
  ob->arming(); ob->move(TO);
  ob=clone_object(CAMPDIR+"est");
  ob->arming(); ob->move(TO);
  ob=clone_object(CAMPDIR+"est");
  ob->arming(); ob->move(TO);
  ob=clone_object(CAMPDIR+"est");
  ob->arming(); ob->move(TO);
  ob=clone_object(CAMPDIR+"est");
  ob->arming(); ob->move(TO);
  ob=clone_object(CAMPDIR+"est");
  ob->arming(); ob->move(TO);
  ob=clone_object(CAMPDIR+"est");
  ob->arming(); ob->move(TO);
  ob=clone_object(CAMPDIR+"est");
  ob->arming(); ob->move(TO);
  ob=clone_object(CAMPDIR+"est");
  ob->arming(); ob->move(TO);
  ob=clone_object(CAMPDIR+"est");
  ob->arming(); ob->move(TO);
 
}
 
#include "resetcamp.o"
 
 
