// stair2
// grace aug 1994

#include "../local.h"
inherit SPURRM;


create_spur_room()
{
   SHORT("Northeast stairwell in the lower level of Knights' Spur");
   LONG("You are standing in the middle of the stairs which lead down " 
     +"to the first level of the Knights' Spur. This stairwell is "
      + "narrow and poorly lit.\n");
   
   INSIDE;
   LIGHT;
   
   add_exit(ROOM + "landing2","up",0);
   add_exit(ROOM + "stair1", "down",0);
   
} 
