/*
n13.c is SW
n15.c is E
*/

inherit "/std/room";
#include "/d/Avenir/common/dark/dark.h"


void
create_room()
{
  set_short("wide, curving tunnel");
  set_long("You stand in a wide, curving section of the"
   +" seemingly-endless tunnels.  The passage makes a"
   +" sharp turn to the east, and returns southwest"
   +" to a large chamber.\n"); 

  AI(({"ceiling", "walls", "wall", "floor", "tunnel"}),
     "Very uninteresting stone.\n"); 

  add_exit(L4 + "n13","southwest");
  add_exit(L4 + "n15","east");
  
  	add_npc(MON + "rogue", 1, &->equip_me());
  BLACK;
  IN;
 
}
      
