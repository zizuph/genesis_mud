/*
n18.c is S
*/

inherit "/std/room";
#include "/d/Avenir/common/dark/dark.h"

create_room()
{

set_short("End of passageway");
set_long("The wide passageway comes to an abrupt end. The dust " +
   "lies heavily here, apparently undisturbed for some time.\n"); 

add_exit("/d/Avenir/common/dark/l4/n18","south",0);

add_prop(ROOM_I_LIGHT,0);
IN

AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
   "passageway"}), "Very uninteresting stone.\n");    
AI("dust", "It is thick on the floor. Your footsteps stir " +
   "it up and cloud the air.\n");

}
