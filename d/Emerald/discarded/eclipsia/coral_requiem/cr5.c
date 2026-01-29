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
   set_long("    As you walk through the cave, you realize how " +
      "peaceful it is here under the surface. Beautiful fish swim " +
      "past and the ethereal voices of singing mermaids can be " +
      "heard while you explore this underwater paradise. The coral " +
      "shimmers all around you, and patches of green seaweed drift " +
      "in the current. The central pavillion is just to the south of " +
      "here, while the cave continues in a northeastern direction.\n\n");
   
   add_item("fish", "Fish of every color imaginable swim along " +
      "periodically in schools of their own kind.\n");
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr4", "northeast");
   add_exit(CRDIR + "bwl", "south");
}

