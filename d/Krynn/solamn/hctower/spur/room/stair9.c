// stair9
// grace sept 1994

#include "../local.h"
inherit SPURRM;

create_spur_room()
{
   SHORT("Tower stair, level two");  
   LONG("You stand near the bottom of a circular stairwell "
      + "that connects the second and third floors of the " 
      + "Knights' Spur with the towers and battlements.\n");

   INSIDE;
   LIGHT;

   add_exit(ROOM + "passage10", "down",0);
   add_exit(ROOM + "stair10", "up",0);        
     
}                
