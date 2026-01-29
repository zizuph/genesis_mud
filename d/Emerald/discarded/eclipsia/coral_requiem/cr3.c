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
   set_long("    Seaweed tickles your leg as you brush past some " +
      "of it on your way through the cave. Tiny tropical fish swim " +
      "just past your face. As you gaze at the coral around you, " +
      "you marvel at its unique beauty. A virtual kaleidoscope of " +
      "color, the coral is utterly captivating. The cave continues " +
      "to the northwest, and to the southwest toward the pavillion.\n\n");
   
   add_item("fish", "A tiny school of fish swim right in front of your " +
      "face. You don't seem to be bothering them much.\n");
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr2", "northwest");
   add_exit(CRDIR + "cr4", "southwest");
}

