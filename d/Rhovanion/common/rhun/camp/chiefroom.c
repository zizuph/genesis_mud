inherit "/std/room";

#include <filter_funs.h>
#include "/d/Rhovanion/defs.h"
#include "campdef.h"
#include "trygo.o"
 
int maxbar;
 
void create_room()
{
   object ob;
 
   maxbar = 1;
   set_long("You've wandered in the part of the camp where the " +
	    "barbarians' leader lives.\n" + 
	    "He must be an exceptional fighter to have been made Chief. " +
	    "It might be wise for you to leave before he attacks you!\n");
   set_short("Chief's room");
   add_exit(CAMP_DIR + "foyer", "north");
 
   ob = clone_object(CAMP_DIR + "npc/estch");
   ob->arming(); 
   ob->move(TO);
}
 
 
void reset_room()
{
 
  object  *list;
  object  dummy;
  int     i, friends;
 
  friends = 0;
  list = FILTER_LIVE(all_inventory(TO));
  for(i = 0; i < sizeof(list); i++)
      if (list[i]->query_name() == "Chief")
	  friends++;
  for(i = friends; i < maxbar; i++)
  {
      dummy = clone_object(CAMP_DIR + "estch");
      dummy->move(TO);
  }
}
