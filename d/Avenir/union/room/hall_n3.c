/*
 * Hallway in the Union guildhall
 *  Cirion 032096
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;

#include <composite.h>

#define SEE_NORTH	({ ROOM + "overhang" })
#define SEE_SOUTH	({ HALL + "_w2", HALL + "_n1", HALL + "_n2" })
#define SEE_EAST	({ ROOM + "alcove" })
#define SEE_WEST	({ HALL + "_nw" })

public string
north_view(void)
{
    object *live = get_view(SEE_NORTH);

    if (!sizeof(live))
	return "";

    return " Standing on the ledge "+
	(sizeof(live) > 1 ? "are " : "is ") +
	COMPOSITE_LIVE(live) + ".";
}

public string
south_view(void)
{
    object *live = get_view(SEE_SOUTH);

    if (!sizeof(live))
	return "";

    return " Standing in the corridor to the south " +
	(sizeof(live) > 1 ? "are " : "is ") +
	COMPOSITE_LIVE(live) + ".";
}

public string
east_view(void)
{
    object *live = get_view(SEE_EAST);

    if (!sizeof(live))
	return ", where a large shelf can be seen.";

    return ", where "+ COMPOSITE_LIVE(live) +" can be seen.";
}

public string
west_view(void)
{
    object *live = get_view(SEE_WEST);

    if (!sizeof(live))
	return "";

    return " Standing before a tall pine door west of here "+
	(sizeof(live) > 1 ? "are " : "is ") +
	COMPOSITE_LIVE(live) + ".";
}

public void
union_room(void)
{
    set_short("stifling corridor");
    set_long("Waves of heat radiate along the corridor from "+
	"the north, where it ends in some sort of overhang. The "+
	"floor of the corridor is stark cold, a bizarre contrast "+
	"to the warmth of the air and the walls all around. The "+
	"corridor stretches back to the south, and to the east "+
	"is a small alcove formed of soft reddish stone"+
	"@@east_view@@@@north_view@@@@south_view@@@@west_view@@\n");

    add_item("door","It is at the end of the west junction.\n");
    add_item(({"floor","ground","stone"}),
	"The floor is made from banded gneiss, seemingly "+
	"melted into a smooth surface.\n");
    add_item(({"wall","walls","limestone"}),
	"The stone of the walls is dusky granite, rough but "+
	"straight. They emanating heat powerfully.\n");
    add_item(({"roof","ceiling"}),
	"It is smooth and unadorned.\n");

    add_cmd_item(({"wall","walls","stone","limstone"}),({"touch","feel"}),
	"The walls are very hot!\n");
    add_cmd_item(({"floor","ground"}),({"touch","feel"}),
	"It is cold.\n");
    add_cmd_item(({"air","heat"}),({"feel","taste","smell"}),
	"The air feels hot and dry.\n");

    add_exit("hall_n2", "south");
    add_exit("overhang", "north");
    add_exit("alcove", "east");
    add_exit("hall_nw", "west");
}
