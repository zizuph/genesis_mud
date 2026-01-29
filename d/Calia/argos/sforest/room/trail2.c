#include "../sforest.h"
#include <stdproperties.h>
inherit SFOREST + "trail";

public void
create_trail_room()
{
	set_short("a small over-grown trail");
	set_long("   Faint strands of light flicker in from high "+
	"above the canopy of converging pine and maple trees along "+
	"this over-grown trail. Loose soil and pine needles mark "+
	"the trail with leaves swept to the side giving notice to "+
	"the wilderness beyond.\n");
	
	add_item(({"up"}),
	"The canopy is in that direction.\n");
	add_item(({"down"}),
	"The ground is firm with dark soil.\n");
	add_item(({"south"}),
	"The trail continues in the direction.\n");
	add_item(({"northeast"}),
	"A small stone bridge is in the direction.\n");
	add_item(({"southwest", "east", "west", "southeast", "north", "northwest"}),
	"The wilderness is in that direction.\n");
	
	add_exit("trail3", "northeast");
	add_exit("trail1", "south");

}
