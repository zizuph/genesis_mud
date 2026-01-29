inherit "/std/room.c";
#include "defs.h"

create_room()
{

   set_short("The endless wastes");

   set_long("Long, majestic plains seem to roll endlessly into the "+
            "distance. The only symbol of civilization you notice "+
            "while walking down the hill is the well worn path under "+
            "your feet. Arriving at the bottom of this hill, the path "+
            "can been seen continuing up another.\n");
   add_item("plains", "They seem endless.\n");
   add_item("path", "It is a trade rout.\n");


   add_exit(KAT_WASTE+"w3", "southeast");
   add_exit(KAT_WASTE+"w1", "west");

   OUTSIDE;

}



