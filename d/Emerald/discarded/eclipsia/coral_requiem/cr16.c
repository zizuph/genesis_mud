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
   set_long("    You don't see any merfolk in this cave, but the cave " +
      "is quite beautiful. The coral glows shades of orange and blue, " +
      "with a splash of bright green every now and then. It is a truly " +
      "fascinating addition to the atmosphere of the underwater town. " +
      "Seaweed sways as you walk past. Their long green leaves seem to "+
      "dance in the water. The pavillion is just to the east of " +
      "here, and the cave continues to the southwest.\n\n");
   
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr17", "southwest");
   add_exit(CRDIR + "bwl", "east");
}

