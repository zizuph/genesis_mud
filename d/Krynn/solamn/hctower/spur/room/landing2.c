
//landing1.c
//grace aug 1994

#include "../local.h"

inherit SPURRM;

create_spur_room()
{
   
   SHORT("Second floor landing");
   LONG("You are standing on the landing of a narrow stair "+
      "leading down to the ground floor of the Knights' Spur. "+
      " The small room is well-lit and bare.\n");
   
   INSIDE;
   LIGHT;
   
   AE(ROOM + "stair2", "down", 0); 
   clone_object(SOBJ + "l2d2b")->move(TO); 
   
   AI("torch", "It burns brightly.\n");
   AI("stair", "It is steep and not well-lighted.\n");
   AI(({"shadow","shadows"}), 
      "The shadows seem to leap out at you.\n");
   
}
