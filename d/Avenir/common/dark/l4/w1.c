/*
center.c is E
w2.c is N
w 16.c is S
*/

inherit "/std/room";
#include "/d/Avenir/common/dark/dark.h"
 

void
create_room()
{
  set_short("Western tunnel");
  set_long("This is a large western tunnel that leads east to west. "
+"The musty smell of underground hangs heavily in the air.  To the "
+"south, a dark, low passage extends.\n");

  AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
   "passageway"}), "Very uninteresting stone.\n");  

  add_exit(L4 + "center","east",0);
  add_exit(L4 + "w16","south",0);
  add_exit(L4 + "w13","west",0);

	add_npc(MON + "rat", 1);
  add_prop(ROOM_I_LIGHT,0);
  IN;
  reset_room();
}
