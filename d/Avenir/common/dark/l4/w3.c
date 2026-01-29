/*
w4.c is N
w2.c is E
*/

inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"
 

void
create_room()
{
  set_short("western tunnel");
  set_long("The western tunnel makes another turn here,"
+" going to the east and north.  There is a small niche here in the"
+" stone wall, apparently cut by skilled hands, though you can"
+" only guess as to what its purpose might be.\n");

  AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
   "passageway"}), "Very uninteresting stone.\n");

  add_exit(L4 + "w2","northwest",0);
  add_exit(L4 + "w4","south",0);

  add_item("niche","There is a small niche cut into the stone wall here.  "
+"It looks to be about the size of a small goblin or dwarf.\n");
  
  add_prop(ROOM_I_LIGHT,0);
  IN;
  
	add_npc(MON + "rat", 2);
}
