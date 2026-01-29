inherit "/std/room.c";
#include "defs.h"

create_room()
{

   set_short("The endless wastes");

   set_long("Long, majestic plains seem to roll endlessly into the "+
            "distance. The only symbol of civilization you notice "+
            "while walking down the hill is the well worn path under "+
            "your feet. It is fairly cold today, though not bitterly, "+
            "bone-chillingly cold, it seems some sort of protection "+
            "would be desirable.\n");
   add_item("plains", "The seem endless.\n");
   add_item("path", "It is a trade rout.\n");


   add_exit(KAT_WASTE+"w1", "east");
   add_exit("/d/Kalad/common/wild/pass/desert/carpet/carpet_leave", "west");

   OUTSIDE;

}

