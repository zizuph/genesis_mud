/*w13.c is E
w15.c is W
*/

inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"


void
create_room()
{
  set_short("Low, dark tunnel");
  set_long("The low, dark tunnel continues both east and west"
+" here, though you can't see much through the gloom and the thick"
+" darkness.\n");

  AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
	 "passageway"}), "Very uninteresting stone.\n");
  
  
  add_exit(L4+"w13","east",0,DUST);
  add_exit(L4+"w15","west",0,DUST);
       add_npc(MON +"rat", 2);
  add_prop(ROOM_I_LIGHT,0);
  IN;
  reset_room();
}

