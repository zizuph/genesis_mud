/*
 * Hallway in the Union guildhall
 *  Cirion 032096
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;

#include <composite.h>

#define SEE_NORTH	({ HALL + "_n3" })
#define SEE_SOUTH	({ HALL + "_w2", HALL + "_n1" })


public string
north_view(void)
{
    object *live = get_view(SEE_NORTH);

    if (!sizeof(live))
	return "";

    return " At the end of the corridor to the north you can see "+
	COMPOSITE_LIVE(live) + ".";
}

public string
south_view(void)
{
    object *live = get_view(SEE_NORTH);

    if (!sizeof(live))
	return "";

    return " Along the corridor to the south can be seen "+
	COMPOSITE_LIVE(live) + ".";
}

public int
exit_block(void)
{
    /* See if player is anything other than the desired people */
    if (!IS_MEMBER(TP))
    {
	write("There is no obvious exit west.\n");
	return 1;
    }

    /* Return 0 to allow the player to exit */
    write("You step into the shadow of the west wall.\n");
    return 0;
}

public void
union_room(void)
{
    set_short("warm corridor");
    set_long("A stifling warmth seems to emanate from the "+
	"very walls here, making the air dry and hot. The "+
	"narrow corridor stretches back to the south from "+
	"here, and to the north it seems to end at some sort "+
	"of ledge.@@south_view@@@@north_view@@\n");

    add_item(({"floor","ground","stone"}),
	"The floor is made from banded gneiss, seemingly "+
	"melted into a smooth surface.\nIt is cold, a stark "+
	"contrast to the warmth of the walls.\n");
    add_item(({"wall","walls","limestone"}),
	"The stone of the walls is dusky granite, rough but "+
	"straight. They seem to emanate heat.\n");
    add_item(({"west wall", "west"}),
	"It is a limestone wall, draped in shadow.\n");
    add_item(({"shadow", "wall shadow" }),
	"It is dark and shifting, appearing penetrable as "+
	"shadows do, but most lack the courage to brave that "+
	"darkness and the mysteries beyond.\n");
    add_item(({"hall","corridor","east","hallway"}),
	"The corridor extends to the north, where it seems to "+
	"come out onto a sort of overhang. South is an "+
	"intersection of hallways.\n");
    add_item(({"roof","ceiling"}),
	"Splayed along the ceiling is a strange, twisted mosaic "+
	"in inverse colours.\n");
    add_item("mosaic","The mosaic along the ceiling is "+
	"made from dull stone tiles that seem to merge "+
	"and move together to form a strange image.\n");
    add_item("image", "You cannot quite make out what it is.\n");

    add_cmd_item(({"shadow", "west wall"}), "search",
	"Your fingers tell you what your eyes do not. "+
	"There is no wall to the west, only a darkness "+
	"you lack the will to penetrate, despite your "+
	"curiousity about what lies beyond.\n");
    add_cmd_item(({"ceiling","mosaic","image","roof"}),({"touch","feel"}),
	"You cannot reach.\n");
    add_cmd_item(({"wall","walls","stone","limestone"}),({"touch","feel"}),
	"The walls are warm and rough.\n");
    add_cmd_item(({"floor","ground"}),({"touch","feel"}),
	"A chill rises from the floor.\n");
    add_cmd_item(({"air","heat"}),({"feel","taste","smell"}),
	"The air feels hot and dry.\n");

    add_exit("hall_n3", "north");
    add_exit("hall_n1", "south");
    add_exit("hall_ne1", "east");
    add_exit("novlib0", "west", exit_block, 1, 1);
}
