#include "../sforest.h"
#include <stdproperties.h>
inherit SFOREST + "trail";

#define LINK ("/d/Calia/argos/nwterr/rooms/sfor13")


public void
create_trail_room()
{
	set_short("a small over-grown trail");
	set_long("   Soft strands of light shimmer in from high "+
	"above the canopy of converging pine and maple trees along "+
	"this over-grown trail. Loose dirt and pine needles mark "+
	"the trail with leaves swept to the side giving notice to "+
	"the wilderness beyond.\n");
	
	add_item(({"up"}),
	"The canopy is in that direction.\n");
	add_item(({"down"}),
	"The ground is firm with dark soil.\n");
	add_item(({"north", "southwest"}),
	"The trail continues in the direction.\n");
	add_item(({"south", "east", "west", "southeast", "northeast", "northwest"}),
	"The wilderness is in that direction.\n");

	
	add_exit("trail2", "north");
	add_exit(LINK, "southwest");

}
