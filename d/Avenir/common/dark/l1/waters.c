/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 */
#pragma strict_types

inherit "/std/room";
#include "../dark.h"

public void
create_room(void)
{
    set_short("Pool");
    set_long("Sounds echo throughout the caverns and collect "+
	"in this large grotto-cavern. A fetid pool of water reaches "+
	"out along the edges of the cavern. Slime and fungus grows "+
	"in great abundance and variety here.\n");

    add_item(({"pool", "water"}), "It is putrid and filled with slime.\n");

    IN; BLACKER;

    add_exit(L1 + "s1", "north");
}

public int
enter(string str)
{
    if ((str != "water") && (str != "pool"))
	return 0;

    if (this_player()->query_skill(SS_SWIM) < 1)
    {
	write("You do not know how to swim.\n");
	say(QCTNAME(this_player()) +
	    " goes near the water, but steps back.\n");

	return 1;
    }

    write("You wade out into the fetid pool.\n"+
	"The water is foul and filled with slime.\n"+
	"You cross the pool to the other side.\n");
    say(QCTNAME(this_player()) +
	" steps out into the fetid water.\n");

    set_dircmd("pool");

    if (!this_player()->move_living("M", "/d/Terel/mountains/pool"))
    {
	tell_room("/d/Terel/mountains/pool", QCTNAME(this_player()) +
	    " steps out from the fetid water.\n", ({ this_player() }));
    }

    return 1;
}

public void
init(void)
{
    ::init();
    add_action(enter, "enter");
}
