
inherit "/d/Rhovanion/lib/room";
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

create_room()
{
    set_short("Path");
    set_long("You follow a path that begins to climb up into "+
	"the mountains to the southwest. East of here, it slopes "+
	"down to meet the seaside along the Sea of Rhun's western "+
	"edge. Loose gravel is scattered on the path.\n");
	
    add_exit(RHUN_DIR+"hills/s17", "east");
    add_exit(RHUN_DIR+"hills/p2", "southwest");
    add_item(({"mountain","mountains"}), "The mountains tower in the distance. Clouds race amongst the tops"
	     + " indicating that they are quite high.\n");
    add_item("gravel", "It seems to be ordinary stone gravel.\n");
}
