/*
w5.c is N
w3.c is S
*/

inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"
 

void
create_room()
{
  set_short("western tunnel");
  set_long("You are standing in a wide section of the western"
+" tunnel.  The floor of the passage is rocky, and several large"
+" stalagmites thrust up.  The tunnel continues into darkness to the"
+" north and south.\n");

  add_exit(L4 + "w3", "north", 0);
  add_exit(L4 + "w5", "east", 0);
  
  add_item(({"stalagmite","stalagmites"}),
	   "The stalagmites are like miniature mountains of rock that thrust up from the tunnel floor.\n");
  
  add_prop(ROOM_I_LIGHT,0);
  IN;
	add_npc(MON + "rat", 1);
}
