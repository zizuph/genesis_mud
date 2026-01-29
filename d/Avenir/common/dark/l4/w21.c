/*
w18.c is NE
w22.c is W
*/

inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"

void
create_room()
{
  set_short("southwest branch of western tunnel");
  set_long("You now stand in the southwest branch of the"
+" spacious western tunnel.  There is little here, save the dull"
+" stone walls and that continuing musty, underground odor."
+"  The passage enters a small room to the west, and returnes to a fork"
+" in the tunnel to the northeast. Some steps have been carved"
+" into the stone here.\n");

  AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
   "passageway"}),
     "Very uninteresting stone.\n"); 
  AI(({"steps", "stairs"}), "They lead upward, into more darkness.\n");
  add_exit(L4 + "w18", "northeast", 0);
  add_exit(L4 + "w22", "west",0);
  add_exit(L4 + "w21b", "up",0); 
  add_prop(ROOM_I_LIGHT,0);
  IN;
	add_npc(MON +"ogre_kid", 1, &->equip_me());
    add_npc(MON + "ogre_dad", 1,&->equip_me());
}
