/* Created by Lucas */
/* Modified by Kieryn */
   
#include "/d/Emerald/eclipsia/edefs.h"
#include <stdproperties.h>
#include "/d/Emerald/defs.h"

inherit WATER_ROOM;

create_room()
{
   add_item(({"ceiling", "floor", "wall", "walls", "coral"}),
      "Everything in sight is covered by the seaweed. Something " +
      "has caused most of the animal life to leave the area, allowing " +
      "the seaweed to take over.\n");
   
   ::create_room();
   set_short("Caves around Coral Requiem");
   set_long("    You are now deep within the cave. Seaweed covers " +
      "everything around you. It is darker still to the southwest. " +
      "It gets slightly less dark to the northwest, on the way back to " +
      "the central court. It is obvious that none of the merfolk have " +
      "been back here in a while.\n\n");
   
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr7", "northwest");
   add_exit(CRDIR + "cr9", "southwest");
}

