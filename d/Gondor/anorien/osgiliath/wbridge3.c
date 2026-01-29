/*
 *	/d/Gondor/anorien/osgiliath/wbridge3.c
 *
 *	Coded by Olorin
 *
 *	Modification log:
 *	 7-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/anorien/osgiliath/osgiliath";

#include "/d/Gondor/defs.h"
#include <stdproperties.h>

public void
create_area_room()
{
    set_areadesc("bridge over the Anduin river");
    set_area("western");
    set_areaname("the ruins of Osgiliath");
    set_land("Gondor");
    set_grass("no");
    set_extraline("This stone bridge seems to have been recently rebuilt. "+
    "To the northeast the bridge reaches the islet in the Anduin, and the "+
    "central complex of the ruined Osgiliath. A stone archway allows "+
    "entry to the ruins, but the darkness beyond gives no clue on what "+
    "to expect. Southwest the bridge stretches on arched pillars across to "+
    "the west shore of the Anduin, and the west parts of Osgiliath.");
    add_item("bridge", BS(
    "The ancient bridge was smashed during a great battle. " +
    "But this must have been centuries ago. Looking closer, " +
    "the current bridge must be quite recently reconstructed, as the "+
    "stones of the foundations seem to be fresh from the quarry.\n"));
    add_item(({"ruins","archway"}),BSN("Before you to the northeast is a "+
    "gaping archway of stone allowing entry to the central parts of "+
    "Osgiliath. The city is mostly ruins, but there are still some towers "+
    "and battlements left on this islet in the Anduin."));
    add_item("towers",BS("Only a couple of towers are still standing among the "+
	  "ruins of the islet of Osgiliath. The fact that the towers were "+
	  "built by excellent craftsmen in the ancient days of Gondor's "+
          "founding, and in strong stone, seems to have played a part in "+
	  "keeping the towers standing through thousands of years.\n"));
    add_item(({"buildings","houses","halls"}),BSN("Osgiliath was built of "+
    "stone - great halls, towers and houses, all in stone. The city was "+
    "built in three separate parts - the central part on the islet in "+
    "the great river Anduin, the rest on each of the riverbanks. Not much "+
    "is left standing now, only some houses and towers, and the bridge "+
    "connecting the three parts of Osgiliath has been recently repaired."));
    add_item("islet",BSN("On the islet in the Anduin are the ruins of "+
    "central Osgiliath, where the King of Gondor once lived in great halls "+
    "and towers of stone, now mostly crumbled to the ground or into the "+
    "river. The islet is reachable from both riverbanks by bridges of stone "+
		       "that have been recently rebuilt."));
    add_item("shore",BSN("The west shore of the Anduin river is not far west, "+
    "but the east bank is further away, beyond the islet "+
    "of Central Osgiliath."));

    add_prop(ROOM_M_NO_TELEPORT, check_teleport);
    add_exit(OSG_DIR + "w1archway", "northeast", 0, 2);
    add_exit(OSG_DIR + "wbridge2",  "southwest", 0, 2);
}


