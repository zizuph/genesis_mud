/*
 * Hallway in the Union guildhall
 *  Cirion 032096
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;

#include <composite.h>

#define SEE_NORTH	({ HALL + "_n2", HALL + "_n3" })
#define SEE_SOUTH	({ HALL + "_w2" })


public string
north_view(void)
{
    object *live = get_view(SEE_NORTH);

    if (!sizeof(live))
	return "";

    return " Along the corridor to the north can be seen "+
	COMPOSITE_LIVE(live) + ".";
}

public string
south_view(void)
{
    object *live = get_view(SEE_NORTH);

    if (!sizeof(live))
	return ".";

    return ", where you see "+ COMPOSITE_LIVE(live) + ".";
}

public void
union_room(void)
{
    set_short("dark corridor");
    set_long("Narrow, high walls of dark granite rise "+
	"of to either side of this narrow corridor. Their "+
	"surface seems to emanate shadows, and the hallway "+
	"seems to get warmer to the north. To the south "+
	"is an intersection@@south_view@@@@north_view@@\n");

    add_item(({"floor","ground","stone"}),
	"The floor is made from banded gneiss, seemingly "+
	"melted into a smooth surface.\nIt is cold, a stark "+
	"contrast to the warmth of the walls.\n");
    add_item(({"wall","walls","limestone"}),
	"The stone of the walls is dusky granite, rough but "+
	"straight.\n");
    add_item(({"hall","corridor","east","hallway"}),
	"The corridor extands to the north, where it seems to "+
	"come out onto a sort of overhand. South is an intersection "+
	"of hallways.\n");
    add_item(({"roof","ceiling"}),
	"The ceiling is formed from the same gneiss as the floor.\n");

    add_cmd_item(({"wall","walls","stone","limstone"}),({"touch","feel"}),
	"The walls are warm and rough.\n");
    add_cmd_item(({"floor","ground"}),({"touch","feel"}),
	"A chill rises from the floor.\n");

    add_exit("hall_w2", "south");
    add_exit("hall_n2", "north");
}
