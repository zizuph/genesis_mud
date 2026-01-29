// stair7
// grace sept 1994

#include "../local.h"
inherit SPURRM;

create_spur_room()
{
   SHORT("Southwest stair, level two");  
   LONG("You stand near the bottom of a broad stair which "
      + "connects the second and third floors of the Knights' " 
      + "Spur.\n");

   INSIDE;
   LIGHT;

    add_exit(ROOM + "stair8", "up",0);
    add_exit(ROOM + "stair6", "down",0);
     
}                
