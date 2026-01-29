/*
 * hall1.c
 *
 * Skippern 20(c)02
 *
 * A large hall inside a noble house.
 *
 */
#include "../../defs.h"
inherit DOL_STD + "inside";

#include <stdproperties.h>

int
closed()
{
    object tp = this_player();

    if (tp->query_wiz_level())
    {
	write("Players have to be invited down by the winemaker, but since " +
	      "you are wizard you are accepted.\n");
	return 0;
    }

    if (tp->query_prop(DOL_I_WINER_QUEST))
	return 0;

    write("For some reason you want go there without leave by the " +
	  "owner.\n");
    return 1;
}

void
create_inside()
{
    set_short("a large hall");
    set_long("This large hall seems to be the entrance and antechamber of " +
		"a large mansion, probably belonging to a rich and influential " +
		"noble of Dol Amroth. To the nortwest you see a beautiful garden " +
		"through a large open doorway. To the south and east seems " +
		"to be locked off from visitors, and might be the servants " +
		"quarters. To the west you see a portal leading to a small " +
		"lounge, and to the north a doorway leads to the main hall. " +
		"A large stairway leads to the upper floors, and hidden " +
		"under it is a narrow stair leading down to a cellar.\n");

    add_exit(DOL_HILLS + "k-13/garden1", "northwest", 0, 1);
    add_exit(DOL_HILLS + "k-13/hall2", "north", 0, 1);
    add_exit(DOL_HILLS + "k-13/hall3", "west", 0, 1);
    add_exit(DOL_HILLS + "k-13/uphall1", "up", 0, 1);
    add_exit(DOL_HILLS + "k-13/winecellar", "down", &closed(), 1);

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
}


