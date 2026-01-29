/*
w4.c is S
w6.c is E
*/

inherit "/std/room";
#include "/d/Avenir/common/dark/dark.h"


void
create_room()
{
  set_short("wide western tunnel");
  set_long("The western tunnel widens further here as it turns."
+" That musty cave smell is still strong, and, as you look"
+" around, it appears that the walls are cut more smoothly here.\n");

  AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
   "passageway"}), "Very uninteresting stone.\n");    

  add_exit(L4 + "w6","north",0);
  add_exit(L4 + "w4","west",0);

  add_prop(ROOM_I_LIGHT,0);
  IN;
  	add_npc(MON + "rat", 2);

}




