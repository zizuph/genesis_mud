 
inherit "/std/room";
#include "campdef.h"
#include "/d/Rhovanion/defs.h"
#include "trygo.o"
 
int maxbar;
 
create_room()
{
  object ob;
  set_long("You are in the usually looking part of evil camp. "+
           "Usualy there are many barbarians here, who don't "+
           "like other people in his camp. Don't wonder if you "+
           "get attacked!\n"+
           "You also notice fence, blocking movement "+
           "to the north and south.\n");
  set_short("Usualy looking part of the camp");
  add_exit(CAMPDIR+"foie","east","@@trygo");
  add_exit(CAMPDIR+"gcamp1","southwest",0);
 
  maxbar=3;
  ob=clone_object(CAMPDIR+"guard");
  ob->arming(); ob->move(TO);
  ob=clone_object(CAMPDIR+"guard");
  ob->arming(); ob->move(TO);
  ob=clone_object(CAMPDIR+"guard");
  ob->arming(); ob->move(TO);
 
}
 
 
#include "/d/Rhovanion/defs.h"
#include "filter_funs.h"
 
 
void reset_room()
{
 
  object *list;
  object dummy;
  int i,friends;
 
  friends=0;
  list=FILTER_LIVE(all_inventory(TO));
  for(i=0;i<sizeof(list);i++)
    if ((list[i]->query_name()=="Barbarian")||
         (list[i]->query_name()=="Chief"))
           friends++;
  for(i=friends;i<maxbar;i++)
    {
      dummy=clone_object(CAMPDIR+"guard");
      dummy->move(TO);
    }
}
