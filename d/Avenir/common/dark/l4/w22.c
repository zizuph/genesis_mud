/*
w21.c is E
*/


inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"

void
create_room()
{
  set_short("old storage chamber");
  
  set_long("This chamber was apparently once used for storage.\n" +
	   "Now, however, it is totally empty save several members\n" +
	   "of local ogre family sometimes visiting here. The only\n" +
	   "way out is back to the east, through the tunnel.\n");

  AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
	 "passageway"}),
     "Very uninteresting stone.\n");    
  
  add_exit(L4 + "w21","east",0);
  
  add_prop(ROOM_I_LIGHT,0);
  IN;
  
	add_npc(MON +"ogre_kid", 2, &->equip_me());
	add_npc(MON + "ogre_mom", 1,&->equip_me());
}
