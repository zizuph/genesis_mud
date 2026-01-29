inherit "/std/room.c";
#include "defs.h"

create_room()
{

   set_short("The endless wastes");

   set_long("Long, majestic plains seem to roll endlessly into the "+
            "distance. Slow the hill climbs to the sky. There is "+
            "still no sign of civilization. The snow capped mountains"+
            " can clearly be seen to the west, while to the east "+
            "nothing but hills cover the area. It is getting colder.\n");
   add_item("plains", "They seem endless.\n");
   add_item("path", "It is a trade rout.\n");


   add_exit(KAT_WASTE+"w5", "east");
   add_exit(KAT_WASTE+"w3", "northwest");

   OUTSIDE;

}
