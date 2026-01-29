// landing4.c
// grace sept 1994

#include "../local.h"

inherit SPURRM;

create_spur_room()
{

   SHORT("Landing on third floor");
   LONG("You are standing on the landing of a wide stair "+
      "which leads down to the second floor of the Knights' "+
      "Spur.  This third floor room is well-lit with "+
      "numerous torches whose dancing flames cast shadows "+
      "upon the bare stone walls.\n");


   INSIDE;
   LIGHT;

   AE(ROOM + "stair8", "west", 0);
   AE(ROOM + "pass1l3", "north", 0);

   AI(({"torch","torches"}), "The torches burn brightly, their flames "+
      "dancing in the air, making shadowy figures on the walls.\n");
   AI("stair", "It is wide and well-lighted.\n");
   AI(({"shadow","shadows","figures","shadowy figures"}),
      "The shadows seem to leap out at you.\n");

}
