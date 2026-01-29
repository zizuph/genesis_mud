/*
 * bk_grove3.c
 *
 * One of the rooms in the bee keeper's grove of trees
 *
 * Zima - May 16, 98
 */
#pragma strict_types
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include <stdproperties.h>
#include "room.h"
inherit  BK_GROVEBASE;
int      berries=3;
 
void reset_room() { berries=3; }
 
public void
create_khalakhor_room()
{
   create_grove();
   set_long("   You are on a low hill amongst a sparsely-populated "+
      "grove of trees. Unusual for the surrounding area, these "+
      "trees must have been planted here by a local agrarian. " +
      "Placed neatly and evenly apart, you are standing next to "+
      "one now, while there are four others nearby. There is also "+
      "a leafy bush growing on the edge of the grove to the north.\n");
 
   add_item(({"bush","shrub"}),
      "It is a leafy shrub or bush which seems to have just popped "+
      "up on the edge of the grove where it gets both sunlight and "+
      "shade. It has a few berries on it, blue in color, though it "+
      "seems the birds have gotten most of them.\n");
   add_cmd_item(({"berry from bush","blueberry from bush"}),"pick",
      "@@pick_bb");
   add_exit(ROOM + "bk_grove5","southwest");
   add_exit(ROOM + "bk_tree3", "up", "@@do_climb", 0, 1);
   set_tree_rm(ROOM+"bk_tree3");
}
 
string pick_bb()
{
   object berry;
   if (!berries)
      return ("There aren't any ripe ones left to pick.\n");
   berry=clone_object(GOHERB+"blueberry");
   if (berry->move(TP)) berry->move(TO);
   berries--;
   tell_room(TO,QCTNAME(TP)+" picks a berry from the bush.\n",TP);
   return ("You pick a "+(berry->short())+" from the bush.\n");
}
