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
   set_long("    It is getting very dark... only the faintest of glows " +
      "can be seen radiating from the coral. The cave continues on in a " +
      "southeastern direction, and back to the northwest toward the " +
      "pavillion. The seaweed is very thick here. You notice an old, " +
      "barnacle-encrusted piece of wood sticking through the "+
      "seaweed.\n\n");
   
   add_item("wood", "The wood has something etched into it... looking " +
      "closely, you can just barely make it out:\n" +
      "\n                    K E E P    O U T\n");
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr6", "northwest");
   add_exit(CRDIR + "cr8", "southeast");
}

