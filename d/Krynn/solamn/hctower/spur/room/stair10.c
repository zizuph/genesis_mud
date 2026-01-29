// stair10
// grace april 1994

#include "../local.h"
inherit SPURRM;


create_spur_room()
{
   SHORT("Tower stair, level two");  
   LONG("You stand near the third floor exit on a circular "
      + "stairwell "
      + "that connects the second and third floors of the " 
      + "Knights' Spur with the towers and battlements.\n");

   INSIDE;
   LIGHT;

   add_exit(ROOM + "stair9", "down",0);
   add_exit(ROOM + "stair11", "up",0);
     
}                
