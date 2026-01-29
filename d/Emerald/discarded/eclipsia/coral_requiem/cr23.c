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
   set_long("    The cave heads south here, and also heads " +
      "west to the pavillion. These caves feel to you as if " +
      "they have been travelled for thousands of " +
      "years, yet they still retain the brilliance of " +
      "their younger days. The coral throughout " +
      "the caves is ageless. It fades neither in luster nor beauty. " +
      "Walking through the tunnels, surrounded by coral as " +
      "old as these waters, you feel as if you are taking a stroll " +
      "through the past.\n\n");
   
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr22", "west");
   add_exit(CRDIR + "cr26", "south");
}

