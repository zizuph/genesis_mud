/*
 * Hallway in the Union guildhall
 *  Cirion 032096
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;

#include <composite.h>
#include <stdproperties.h>

#define SEE_EAST	({ ROOM + "crossing", HALL + "_e" })
#define SEE_WEST	({ HALL + "_w1" })
#define SEE_NORTH	({ HALL + "_n1", HALL + "_n2", HALL + "_n3" })
#define SEE_SOUTH	({ ROOM + "lounge" })

public string
east_view(void)
{
    object *live = get_view(SEE_EAST);

    if (!sizeof(live))
	return "";

    return " Down the hall to the east can be seen "+
	COMPOSITE_LIVE(live) + ".";
}

public string
west_view(void)
{
    object *live = get_view(SEE_WEST);

    if (!sizeof(live))
	return "";

    return " At the west end of the corridor is "+
	COMPOSITE_LIVE(live) + ".";
}

public string
north_view(void)
{
    object *live = get_view(SEE_NORTH);

    if (!sizeof(live))
	return "";

    return " Along the northern corridor you see "+
	COMPOSITE_LIVE(live) + ".";
}

public string
south_view(void)
{
    object *live = get_view(SEE_SOUTH);

    if (!sizeof(live))
	return "";

    return " In the salon to the south is "+
	COMPOSITE_LIVE(live) + ".";
}

public int
go_north(void)
{
    write("You turn down the northern corridor.\n");
    return 0;
}

public int
go_east(void)
{
    write("You walk down the long hallway to the east.\n");
    return 0;
}

public int
go_west(void)
{
    write("You walk down the hallway to the west, where it ends.\n");
    return 0;
}

public int
go_south(void)
{
    write("You step through the circular doorway.\n");
    return 0;
}

public void
union_room(void)
{
    set_short("turning in the hallway");
    set_long("The wide hallway continues east and "+
	"west, with a narrow corridor of dark granite "+
	"leading north. There is a swirl of stone and "+
	"metal covering the floor, and a soft cold "+
	"breeze seems to be passing along the ground."+
	"@@east_view@@@@west_view@@@@north_view@@@@south_view@@\n");

    add_item(({"floor","ground","stone","stones","swirl",
	"metal","metals"}),
	"The floor is covered in swirls of dark metal and grey stone "+
	"that seems to merge and melt and never repeat itself.\nThe "+
	"patterns run from east to west, to the north the corridor is "+
	"a flat dark granite.\n");
    add_item(({"wall","walls","limestone"}),
	"The stone of the walls is soft and smooth, a pale white "+
	"limestone that reflects the light.\n");
    add_item(({"hall","corridor","east","hallway"}),
	"The hallway stretches off to the east and end to the "+
	"west, running perfectly straight and wide."+
	"@@east_view@@ @@west_view@@ @@north_view@@\n");
    add_item(({"roof","ceiling"}),
	"The ceiling overhead is made of the same dark granite as the "+
	"floor, but is simple and unadorned. It rises slightly in the "+
	"middle, forming a gentle arch that stretches all the way down "+
	"the corridor to the east.\n");
    add_item(({"doorway", "circular doorway", "south", "salon"}),
      "The doorway to the south is entirely circular.@@south_view@@\n");

    add_cmd_item(({"breeze","wind","draft","air"}), "touch",
	"It seems to be blowing from west to east.\n");
    add_cmd_item(({"wall","walls","stone","limstone"}), "touch",
	"It is smooth and soft.\n");
    add_cmd_item(({"floor","ground"}), "touch",
	"It is hard, the patterns rising out from the floor slightly.\n");

    add_exit("hall_w1", "west", "@@go_west@@");
    add_exit("crossing", "east", "@@go_east@@");
    add_exit("hall_n1", "north", "@@go_north@@");
    add_exit("lounge", "south", "@@go_south@@");
}
