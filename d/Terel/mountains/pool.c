/*
 * - pool.c
 *
 * * Lucius May 2009: Cleaned and updated for code move to Avenir domain.
 */
#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

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

    write("You wade out into the fetid pool.\n" +
	  "The water is foul and filled with slime.\n" +
	  "You find the pool rather small and cross to the other side.\n");
    say(QCTNAME(this_player()) + " steps out into the fetid water.\n");

    set_dircmd("pool");

    if (!this_player()->move_living("M", "/d/Avenir/common/dark/l1/waters"))
    {
	tell_room("/d/Avenir/common/dark/l1/waters",
	    QCTNAME(this_player()) + " steps out of the dark pool.\n",
	    ({ this_player() }));
    }

    return 1;
}

public void
init(void)
{
    ::init();
    add_action(enter, "enter");
}

public void
create_room(void)
{
    set_short("Pool");
    set_long("A pool of fetid and murky water spreads out into\n"
	     + "the darkness. The cavern is coated with a sheet of slime\n"
	     + "and moss, causing it to be quite slick. Stalagmites and\n"
	     + "stalactites fill the cavern like ancient pillars of some\n"
	     + "forgotten royal hall.\n");

    add_item(({"pool", "water"}), "It is putrid and filled with slime.\n");

    add_exit("/d/Terel/mountains/dcave", "up");
}
