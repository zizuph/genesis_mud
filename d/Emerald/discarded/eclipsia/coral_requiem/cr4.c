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
   set_long("    Your senses are filled by this gorgeous environment. " +
      "The crystal blue water glows with the changing colors of the " +
      "surrounding coral. The floor gets a bit more slippery here, " +
      "but you manage to maintain an upright prose. Every now and " +
      "then, you step over some seaweed poking through the cracks. " +
      "The cave continues to both the southwest and northeast.\n\n");
   
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr3", "northeast");
   add_exit(CRDIR + "cr5", "southwest");
}

