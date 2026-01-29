/*
   w11.c is W
*/


inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"

void
create_room()
{
  set_short("large cavern");

  set_long(
  "You are standing at the east end of a large cavern.  Unlit torches "
  +"hang on the walls here. This room is nearly dust-free, showing "
  +"traces of continuous usage.\n");

  add_exit(L4 + "w11","east",0);
  
  add_prop(ROOM_I_LIGHT,0);
  IN;
  
  add_item(({"torch","torches"}),
  "Several burnt-down torches hang on the walls here.  There is nothing really interesting about them.\n");
  
  add_item( ({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
		"passageway"}),
	   "Very uninteresting stone.\n");  

	add_npc(MON + "ogre_dad", 1);
	add_npc(MON + "ogre_kid", 2);
}
