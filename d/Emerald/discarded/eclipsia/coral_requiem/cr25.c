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
   set_long("    Walking through the cave, you take special notice " +
      "of the coral all around you. Shimmering and " +
      "pearlescent, it is like nothing you have ever seen. " +
      "Just ahead to the northwest, the cave opens up into " +
      "a larger room. Merfolk swim in and out of the opening, " +
      "taking care of what business they might have there. " +
      "Occasionally, you can hear the mermaids singing back " +
      "through the cave.\n\n");
   
   add_item("merfolk", "The elegant merfolk drift in and out " +
      "of the opening regularly, attending to their business.\n");
   add_item("opening", "The opening leads into a large room " +
      "which seems to be bustling with activity.\n");
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr24", "south");
   add_exit(CRDIR + "post", "northwest");
}

