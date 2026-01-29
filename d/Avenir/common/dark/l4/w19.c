/*
w18.c is SE
w20.c is W
*/


inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"


void
create_room()
{
  set_short("northwest branch of tunnel");
  
  set_long("The wide, spacious western tunnel continues onward,"
+" here going west into a small chamber, and southeast to a fork"
+" in the passage.\n");

  AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
   "passageway"}), "Very uninteresting stone.\n"); 

  add_exit(L4 + "w20", "west", 0);
  add_exit(L4 + "w18", "southeast", 0);

  add_prop(ROOM_I_LIGHT,0);
  IN;
  
	add_npc(MON +"ogre_kid", 2, &->equip_me());
}
