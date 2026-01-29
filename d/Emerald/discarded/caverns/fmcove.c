/*
 * FMCOVE.c
 * This is an exit out to the cove.
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_cave()
{
   set_short("Exit to Cove");
   set_long("   Standing just inside the caverns, you can peer "+
	    "outside to see a sandy cove with deep, blue ocean "+
	    "water lapping gently against the jagged shoreline "+
	    "rocks. The sound of the surf echos in the mouth of the "+
	    "cave. The entrance to this cave looks pretty well "+
	    "hidden from prying eyes on the outside. Deeper inside "+
	    "the caverns, the tunnels are dark and gloomy, but "+
	    "retain just enough light so that you can maneuver "+
	    "around.\n\n");

   add_item(({"cove","sandy cove","beach"}),
	    "It is a peaceful cove with a sandy beach. It's hard "+
	    "to tell what else might be out there.\n");

   add_item(({"water","ocean","sea"}),
	    "The water is calm and peacefull. It is gently lapping "+
	    "against the beach with a smooth rythmic cadence.\n");

   add_item(({"opening","entrance"}),
	    "The entrance is covered with dry grasses and other brush "+
	    "making it difficult to see in or out.\n");

   add_item(({"cave","caverns"}),
	    "The caverns are dark and gloomy.\n");

   add_exit(THIS_DIR + "main1", "north");
   add_exit(VOLCANO_DIR+"cove", "out");
   
   if (LOAD_ERR(CAVERNS_DIR + "caverns_clone_handler"))
     {
       this_player()->catch_msg("You notice something wrong that a "+
				"wizard should probably take care of.\n");
     }
}
