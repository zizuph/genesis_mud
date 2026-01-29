// stair8
// grace sept 1994

#include "../local.h"
inherit SPURRM;

create_spur_room()
{
   SHORT("Southwest stair, level three");  
   LONG("You stand near the top of a broad stair which "
      + "connects the second and third floors of the Knights' " 
      + "Spur.\n");

   INSIDE;
   LIGHT;

    add_exit(ROOM + "landing4", "east",0);
    add_exit(ROOM + "stair7", "down",0);
     
}                
