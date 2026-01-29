inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("A street within the drow city of Undraeth");
   set_long("A veritable kaleidoscope of stalagmites and stalactites "+
      "surround you, filling your field of view. These immense structures of "+
      "rock rise far above the ground, having been magically enhanced by the "+
      "native population into the astounding structures before you now. "+
      "The air around you is warm from the presence of numerous living beings in "+
      "the area. It is also quite stale and stagnant, due to its presence far "+
      "below the fresh air of the surface. "+
      "A large compound lies to the east, just off the street. "+
      "The street you have been journeying upon continues to the northeast "+
      "and southwest.\n");
   add_item(({"immense structures","structures","structure","rock","stalagmites","stalagmite","stalactites","stalactite"}),
      "Monumental in their size, these huge rock formations provide living "+
      "space for the many inhabitants of this city.\n");
   add_item(({"streets","street"}),"The perfectly flat and smooth "+
      "structures seem to bend and twist in many directions, a rather "+
      "chaotic road design as compared to many surface cities. Yet unlike "+
      "them, not the slightest bit of rubbish litters these streets.\n");
   add_item(({"large compound","compound"}),
      "A large collection of individual stalagmites that have been magically "+
      "fused to one another to form one grand building. Before it has "+
      "been placed a sign.\n");
   add_item("sign","Several words written in glowing faerie fire are "+
      "visible upon it.\n");
   add_cmd_item("sign","read",
      "It reads: Rooming House\n");
   add_exit(CPASS(drow/d47),"northeast");
   add_exit(CPASS(drow/shop/inn),"east","@@block",-1,-1);
   add_exit(CPASS(drow/d39),"southwest");
   set_noshow_obvious(1);
}
block()
{
   write("It would appear that the rooming house is closed, since there is "+
      "no visible entrance.\n");
   return 1;
}
