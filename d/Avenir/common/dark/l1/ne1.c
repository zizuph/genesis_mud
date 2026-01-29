/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 */
#pragma strict_types

inherit "/std/room";
#include "../dark.h"

public void
create_room(void)
{
    set_short("Tunnel");
    set_long("This tunnel is carved from deep black rock, veined " +
	     "with lines of red carnelian and sardonyx. It seems as though " +
	     "it is of better work than the most of the area. " +
	     "A set of stairs leads down deeper into the earth.\n");

    add_item("sardonyx",
	     "A stone of multi-colors, it is semi-precious.\n");
    add_item("carnelian",
	     "A red semi-precious stone. It occurs in veins\n" +
	     "in this tunnel area.\n");

    IN; BLACK;

    add_exit(L1 + "stair4", "down");
    add_exit(L1 + "n2", "west");
}
