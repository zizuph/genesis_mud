#include "../sforest.h"
#include <stdproperties.h>
inherit SFOREST + "trail";

public void
create_trail_room()
{
	set_short("a small over-grown trail");
	set_long("   Pine and maple trees converge together along "+
	"this over-grown trail. Loose dirt and pine needles mark the "+
	"trail with leaves swept to the side giving notice to the "+
	"wilderness beyond.\n");
	
	add_item(({"up"}),
	"The canopy is in that direction.\n");
	add_item(({"down"}),
	"The ground is firm with dark soil.\n");
	add_item(({"north"}),
	"The trail continues in the direction.\n");
	add_item(({"southwest", "southeast", "west", "east", "northeast", "northwest"}),
	"The wilderness is in that direction.\n");
	
	add_exit("sf10", "north");
	add_exit("trail4", "south");

}
