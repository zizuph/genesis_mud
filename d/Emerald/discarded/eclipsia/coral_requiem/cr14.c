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
   set_long("    Brightly coloured fish swim by, playing in the " +
      "warm waters of the cave. The springs in the tunnel cause the " +
      "current to be a bit stronger. Combining the current with the " +
      "slippery floor, you find it more than a little difficult to " +
      "keep your footing. The cave heads both southeast and northwest.\n\n");
   
   add_item("fish", "Tiny fish swim around the cave, taking advantage " +
      "of the exceptionally warm waters.\n");
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr15", "southeast");
   add_exit(CRDIR + "cr13", "northwest");
}

