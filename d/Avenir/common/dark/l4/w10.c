/*
w11.c is N
w9.c is E
*/

inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"



void
create_room()
{
  set_short("Clean tunnel");
  set_long(
      "The clean, smooth, well-kept tunnel makes yet another turn\n" +
      "here, now going east and north. The northern way leads\n" +
      "to a large, arched stone doorway. There appears to be a large\n" +
      "cavern beyond.\n"
	   );

  add_exit(L4 + "w9", "west", 0);
  add_exit(L4 + "w11", "north", 0);

  add_prop(ROOM_I_LIGHT,0);
  IN

  add_item("doorway",
	   "It is high and arched, crafted from solid stone.  You can see a large cavern just beyond it, to the north.\n");

  add_item (({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
   "passageway"}),
	    "Very uninteresting stone.\n");  
	add_npc(MON + "rat", 1);
	add_npc(MON + "ogre_kid", 2, &->equip_me());
}
