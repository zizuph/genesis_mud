/*
 * Hallway in the Union guildhall
 *  Cirion 032096
 * Revisions:
 *    Lilith, May 2022: added Sair wall
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;
inherit "/d/Avenir/inherit/sair_wall";

public void
union_room(void)
{
    set_short("passage");
    set_long("To the north, a stark white room opens up, "+
	"the light from it shining into the passage and "+
	"making the verdant greenish wall sparkle with "+
	"a bright lustre. The passage continues west, and "+
	"east where it ends at a door.\n");

    add_item("door", "It is at the east end of the passage.\n");
    add_item(({"floor","ground","basalt"}),
	"The floor is made from greyish basalt, expertly fitted "+
	"together so that no seams show.\n");
    add_item(({"seam","seams"}), "You cannot see them.\n");
    add_item(({"wall","walls"}), "The walls are made from "+
	"a smooth yellow-green stone that seems more like "+
	"gemstone than anything else.\n");
    add_item(({"roof","ceiling"}),
	"It is flat and unadorned.\n");

    set_sair_dest(({"/d/Avenir/common/dark/l2/add/t36", 
	                "/d/Avenir/common/outpost/cave2", 
					"/d/Avenir/common/port/port2",
					"/d/Avenir/common/dark/l4/center"}));
    add_sair_wall();
//    add_cmd_item(({"wall","walls","stone"}),({"touch","feel"}),
//	"The walls are smooth, almost silken.\n");

    add_exit("hall_ne3", "east");
    add_exit("hall_ne1", "west");
    add_exit("white", "north");
}

public void
init()
{
    ::init();
    sair_init();  
}