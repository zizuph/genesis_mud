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
   set_long("    There are four more cracks in the floor here, each " +
      "offering a blast of hot water. It is almost too hot for comfort " +
      "here, but you manage to bare it. The cave opens up to the east " +
      "into a large room. Peering inside, you see a good number of merfolk " +
      "who seem to be enjoying themselves. The cave heads back to the " +
      "pavillion to the northwest.\n\n");
   
   add_item(({"cracks", "springs", "fissures", "spring", "crack"}),
      "The springs have caused a big jump in the water temperature. " +
      "Four cracks in the floor each give off a hot waterflow.\n");
   add_item("merfolk", "The merfolk to the east seem to be having a lot " +
      "of fun.\n");
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr14", "northwest");
   add_exit(CRDIR + "inn", "east");
}

