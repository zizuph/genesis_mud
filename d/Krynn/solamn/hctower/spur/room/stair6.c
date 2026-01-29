// stair6
// grace sept 1994

#include "../local.h"
inherit SPURRM;

create_spur_room()
{
   SHORT("Southwest stair, halfway to level two");  
   LONG("You stand on a broad stair midway between the central " 
      + "hall on the second level of the Knights' Spur and the "
      + "first floor.\n");

   INSIDE;
   LIGHT;

    add_exit(ROOM + "stair7", "up",0);
    add_exit(ROOM + "landing3", "east",0);
    add_exit(ROOM + "stair5", "down",0);
     
}                
