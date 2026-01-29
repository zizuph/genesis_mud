/*
 * Hallway in the Union guildhall
 *  Cirion 032096
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;


public void
union_room(void)
{
    set_short("wide passage");
    set_long("High walls of a strange yellow-green stone "+
	"frame this passage, arching to a domed ceiling "+
	"above. The passage opens up to a narrow "+
	"hallway to the west, and east it continues on "+
	"until it ends at a large door.\n");

    add_item("door", "It is at the east end of the passage.\n");
    add_item(({"floor","ground","basalt"}),
	"The floor is made from greyish basalt, expertly fitted "+
	"together so that no seams show.\n");
    add_item(({"seam","seams"}), "You cannot see them.\n");
    add_item(({"wall","walls"}), "The walls are made from a "+
	"smooth yellow-green stone that seems more like gemstone "+
	"than anything else. They rise up to a domed ceiling.\n");
    add_item(({"roof","ceiling"}), "The ceiling forms a solid dome "+
	"above, on which has been painted an image of a dark, "+
	"glimmering sphere.\n");
    add_item(({"image","sphere","painting"}),
	"The image above is that of a perfect sphere, blue-black and "+
	"shining with an eerie light.\n");

    add_cmd_item(({"ceiling","mosaic","image","roof"}),({"touch","feel"}),
	"You cannot reach.\n");
    add_cmd_item(({"wall","walls","stone"}),({"touch","feel"}),
	"The walls are smooth, almost silken.\n");

    add_exit("hall_n2", "west");
    add_exit("hall_ne2", "east");
}
