// Ceadha Foclair - harbour master
// Refactored, Tapakah, 08/2021

#pragma strict_types

#include "defs.h"

inherit BASE_ASHLAGH;
 
void
create_khalakhor_human ()
{
   create_villager(0,"ceadha"); //0=male
   set_monster_home(ROOM+"pierhouse");
   add_ask(({"ships","ship"}),
      "say Since the goblin raid, the only ship's been here's the "+
      "Aigne Deas from MacDunn.",1);
   add_ask(({"goblins","raid"}),
      "say Oh, just a couple gobbos causin' a ruckus in town. And they "+
      "bottle the place up like its a war! baaaa!",1);
}
 
