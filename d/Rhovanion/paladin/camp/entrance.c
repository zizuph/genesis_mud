 
inherit "/std/room";
#include "campdef.h"
#include "/d/Rhovanion/defs.h"
 
int maxbar;
 
create_room()
{
  object ob;
  set_long("This is entrance to the evil camp.There are many "+
           "guards standing around! They definetely will "+
           "attack you! You'd better leave now, while you're "+
           "alive!\n");
  set_short("Entrance to the camp");
  add_exit(CAMPDIR+"camp1","north","@@trygo");
  add_exit(CAMPDIR+"testdis","south",0);
 
  maxbar=8;
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
#include "trygo.o"
 
 
