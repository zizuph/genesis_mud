/*
w1.c is E
w14.c is W
*/

inherit "/std/room";
#include "/d/Avenir/common/dark/dark.h"
 
void
create_room()
{
  set_short("Low, dark tunnel");
  set_long("The darkness seems especially oppressive in this low"
+" tunnel.  The ceiling is very close, making you feel slightly"
+" claustrophobic.  The passage meets others to the east, and"
+" continues west into intense darkness.\n");

  add_exit(L4+"w14","west",0,DUST);
  AE(L4+"w1","east",0,DUST);
  
  add_item("ceiling","The ceiling is uncomfortably close.\n");
  AI("dust", "It is thick on the floor. Your footsteps stir " +
     "it up and cloud the air.\n");
  
  
  add_prop(ROOM_I_LIGHT,0);
  IN;
  add_npc(MON +"rat", 2);
  reset_room();
}



