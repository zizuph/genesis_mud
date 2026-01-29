/*
w7.c is N
w9.c is W
*/


inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"


void
create_room()
{
  set_short("smooth tunnel");

  set_long("The wide, smooth tunnel makes a sharp turn here and"
   +" heads to the north and west.  The floor here has just"
   +" enough dust for some creature to have left behind "
   +" small footprints.\n");

  add_exit(L4 + "w7", "north",0);
  add_exit(L4 + "w9", "east",0);

  add_prop(ROOM_I_LIGHT,0);
  IN;

  add_item(({"footprint","footprints","dust"}),
 "You can just make out a few small-sized footprints in the dust.\n");
	add_npc(MON + "ogre_kid", 2, &->equip_me());

}





