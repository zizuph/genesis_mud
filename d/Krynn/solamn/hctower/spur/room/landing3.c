// landing3.c
// grace sept 1994
//grace aug 1994

#include "../local.h"

inherit SPURRM;

create_spur_room()
{
   
   SHORT("Landing on second floor");
   LONG("You are standing on the landing of a wide stair "+
      "which leads down to the ground floor of the Knights' "+
      "Spur, and up to the third level. "+
      " The small room is well-lit and bare.\n");
   
   INSIDE;
   LIGHT;
   
   AE(ROOM + "stair6", "west", 0);
   AE(ROOM + "passage13", "north", 0);


   
   AI("torch", "It burns brightly.\n");
   AI("stair", "It is steep and not well-lighted.\n");
   AI(({"shadow","shadows"}), 
      "The shadows seem to leap out at you.\n");
   
}
