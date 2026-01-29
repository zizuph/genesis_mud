inherit "/std/room.c";
#include "defs.h"

create_room()
{

   set_short("The endless wastes");

   set_long("Long, majestic plains seem to roll endlessly into the "+
            "distance. You have reached the crest of the hill. At "+
            "the base of the hill a large oak tree stands defiantly "+
            "in the bitter cold wind. The road runs right by it.\n");
   add_item("plains", "They seem endless.\n");
   add_item("path", "It is a trade rout.\n");


   add_exit(KAT_WASTE+"w6", "east");
   add_exit(KAT_WASTE+"w4", "west");

   OUTSIDE;

}
