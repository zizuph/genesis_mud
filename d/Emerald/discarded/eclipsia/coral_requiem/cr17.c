/* Created by Lucas */
/* Modified by Kieryn */
   

#include "/d/Emerald/eclipsia/edefs.h"
#include <stdproperties.h>
#include "/d/Emerald/defs.h"

inherit WATER_ROOM;

create_room()
{
   ::create_room();
   set_short("Caves around Coral Requiem");
   set_long("    The lovely green seaweed greets you as you stroll " +
      "through the cave. It sways very lazily with the current of the " +
      "water. The coral shimmers with green and orange hues, " +
      "casting an unusual light on everything it shines upon. The cave " +
      "continues to the southwest here and also to the northeast, " +
      "leading toward the central court.\n\n");
   
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr16", "northeast");
   add_exit(CRDIR + "cr18", "southwest");
}

