/*
 * Hallway in the Union guildhall
 *  Cirion 032096
 */
#pragma strict_types
#include "../defs.h"

#include <filter_funs.h>
#include <composite.h>

inherit BASE;

#define SEE_WEST ({ HALL + "_cross", HALL + "_w2", HALL + "_w1" })

public string
west_view(void)
{
    object *live = get_view(SEE_WEST);

    if (!sizeof(live)) 
	return "";

    return " Down the corridor to the west can be seen "+
	COMPOSITE_LIVE(live) + ".";
}

public int
go_down(void)
{
    write("The stairs turn from east to south, and you come "+
	"out onto a landing.\n");
    return 0;
}

public void
union_room(void)
{
    set_short("eastern end of corridor");
    set_long("The corridor comes to an end to the east here, "+
	"where wide stone steps descend down into a thick "+
	"gloom from which rises warm air. The walls of the "+
	"hall are smooth which limestone that gleams "+
	"with a pale light.@@west_view@@\n");

    add_item(({"floor","ground","stone","stones","swirl",
	"metal","metals"}),"The floor is covered in swirls "+
	"of dark metal and grey stone that seems to merge and "+
	"melt and never repeat itself.\nThe patterns run from "+
	"the west, and disappear abruptly at the beginning "+
	"of the marble stairs to the east.\n");
    add_item(({"wall","walls","limestone"}),"The stone of "+
	"the walls is soft and smooth, a pale white limestone "+
	"that reflects the light.\n");
    add_item(({"hall","corridor","east","hallway"}),
	"The hallway stretches off to the west, where it seems "+
	"to reach a juncture.\n");
    add_item(({"roof","ceiling"}),"The ceiling overhead is "+
	"made of the same dark granite as the floor, but "+
	"is simple and unadorned. It rises slightly in the "+
	"middle, forming a gently arch that stretches all "+
	"the way down the corridor to the east.\n");
    add_item(({"stair","stairs","staircase"}),"The stairs "+
	"are very smooth white marble veined with thin "+
	"lines of a blood red metal, like adamantine. They "+
	"lead down to the east into darkness, where it looks "+
	"like they turn.\n");

    add_cmd_item(({"breeze","wind","draft","air"}), "touch",
	"The cold air near the floor rushes down the stairs furiously.\n");
    add_cmd_item(({"wall","walls","stone","limstone"}), "touch",
	"It is smooth and soft.\n");
    add_cmd_item(({"floor","ground"}), "touch",
	"It is hard, the patterns rising out from the floor slightly.\n");

    add_exit("crossing", "west");
    add_exit("vaults", "northeast");
    add_exit("landing", "down", "@@go_down@@");
}
