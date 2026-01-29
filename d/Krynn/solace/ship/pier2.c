/* Added exit to the new pier */

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <stdproperties.h>
#include <macros.h>

inherit SOLOUTROOM;
inherit "/d/Genesis/gsl_ships/lib/pier";

#define LIVE_I_CAN_FISH      "_live_i_can_fish"

void
create_solace_room()
{
   set_short_desc("on a pier in Crystalmir Lake");
   set_extra_line("This part of the pier is much more recent than "+
       "its eastern side. It has been constructed by Genesis "+
       "ShipLines Company in order to allow young players "+
       "safely and comfortably travel to Pelargir and other "+
       "lands.\n");
   
   add_prop(ROOM_I_NO_CLEANUP,1);
   add_prop(LIVE_I_CAN_FISH, "freshwater");  

   add_exit("pier", "east");
   
   add_item("pier", "The pier is built on huge boulders. How they got here " +
    "is a mystery.\n");
   add_item(({"water","lake"}),
      "This is Crystalmir Lake, stretching out wide to the " +
      "north and south. The opposite shore to the west can barely be " +
      "seen, all you can make out are some mountains over yonder.\n");
   add_item("mountains", "They are too far away to see any details.\n");
   add_item("opposite shore","It is too far away to see any details.\n");
   add_item("boulders","They're hard rock.\n");
   add_item(({"road","track"}),
      "This is more like a track, apparently leading to the village " +
      "of Solace.\n");

    reset_room();
	add_pier_entry(MASTER_OB(TO), "Solace", "Newbline Line D");
	initialize_pier();
}
