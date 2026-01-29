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
   set_long("    Just outside of the central pavillion, this " +
      "coral cave curves off to the east. The cave is quite " +
      "a bit darker than the central court, but the light " +
      "which reflects off of the coral surrounding you is " +
      "easily sufficient to light the way. The coral serves " +
      "as a mirror, bouncing light through the length of the " +
      "cave. The white light is seperated by the prism-like effect " +
      "of the coral, and it is cast throughout the tunnel in a " +
      "rainbow of shimmering and constantly changing colour.\n\n");
   
   add_item("light", "The light from the central court is " +
      "reflected by the coral deep into the tunnel.\n");
   add_item("rainbow", "A band of changing colours shines " +
      "through the cave. The colours mix and move around the cave " +
      "like the colours that you would notice on the surface of a " +
      "bubble, flowing and transforming themselves as their surface changes.\n");
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "bwl", "northwest");
   add_exit(CRDIR + "cr23", "east");
}

