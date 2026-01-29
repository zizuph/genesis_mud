/* Created by Lucas */
/* Modified by Kieryn */
   

#include "/d/Emerald/eclipsia/edefs.h"
#include <stdproperties.h>
#include "/d/Emerald/defs.h"

inherit WATER_ROOM;

create_room()
{
   object chest;
   ::create_room();
   set_short("Caves around Coral Requiem");
   set_long("    You step inside the dark hole and into what seems " +
      "like a cabin of some sort. The room is turned on its side, due " +
      "to the inverted position of the ship. It doesn't seem very safe " +
      "in here, but you manage to get a firm foothold. A bed is turned " +
      "on its side, and a door has been ripped off here, " +
      "exposing the sand and coral here at the bottom of the water.\n\n");
   
   add_item(({"wreck","shipwreck","ship","wreckage"}),
      "What a horrible end for such a beautiful ship. " +
      "The hull is in two giant pieces, but other than that, " +
      "still looks the same as it did when it sailed " +
      "the open seas.\n");
   chest = clone_object("/d/Emerald/eclipsia/obj/chest");
   chest->move(TO);
   add_item(({"skeleton", "skeletons"}), "All that is left of the " +
      "crew is their mangled skeletons.\n");
   add_item("bed", "This was the bed of whoever once slept in this cabin.\n");
   add_item(({"sand", "coral", "bottom", "door", "doorway"}),
      "The doorway leads straight into the sand due to the position " +
      "of the ship.\n");
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr20", "out");
}

