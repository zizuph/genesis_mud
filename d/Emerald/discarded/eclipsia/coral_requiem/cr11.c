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
   set_long("    The striking contrasts of the coral and the blue " +
      "water, along with the bright colours of the many fish that " +
      "swim by are very pleasing to the eye. Everything you look at " +
      "seems more vibrant and animated than anything you have seen " +
      "in quite some time. The cave winds on to the northeast, and " +
      "the pavillion is just to the west.\n\n");
   
   add_item("fish", "The brightly coloured fish dart around the cave.\n");
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr12", "northeast");
   add_exit(CRDIR + "bwl", "west");
}

