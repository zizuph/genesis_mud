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
   set_long("    You immediately notice that this cave has not " +
      "been travelled in some time. Completely devoid of life, " +
      "other than the overgrown seaweed poking through the cracks, " +
      "you feel rather alone here. Around the corner to the " +
      "southeast, the cave seems much darker. The coral in this " +
      "area has either lost its reflective properties, or has been " +
      "covered over the years too greatly by seaweed, preventing " +
      "light from getting through.\n\n");
   
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr7", "southeast");
   add_exit(CRDIR + "bwl", "north");
}

