/*
 * /d/Gondor/rohan/edoras/rooms/sleep2.c
 *
 * Modification log:
 * 4-Dec-1997, Gnadnar: General revision.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void    create_gondor();
public void    reset_room();
static object *Men = allocate(3);

/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor()
{
    set_short("sleep chamber of the Rohirrim guard");
    set_long(BSN(
	"Tidy rows of beds, each with its own chest at its foot, "+
        "fill this large chamber.  None of the beds is in use "+
        "just now."));
    add_item(({"chamber","sleep chamber","barracks","room"}),long);
    add_item(({"rows","bed","beds"}), BSN(
	"The beds, all of which are empty, are very tidy. A small "+
	"wooden chest stands at the foot of each bed."));
    add_item(({"small wooden chest","wooden chest","chest"}), BSN(
	"The chests are fairly small, and look as if they've "+
	"seen a lot of use"));
    add_item(({"stone","stones","stone floor","floor","ground"}), BSN(
	"The stone floor is clean, but worn."));
    add_item(({"boulder","boulders","wall","walls"}), BSN(
	"The walls are simply roughly hewn boulders, carefully fitted "+
	"together."));
    add_item(({"stone ceiling","ceiling"}), BSN(
	"The low ceiling is unadorned stone."));

    add_cmd_item( ({ "small wooden chest", "wooden chest", "chest",
    "small wooden chests", "wooden chests", "chests" }),
	({ "open", "unlock" }),
	BSN("All the chests are locked, and you don't seem to have the "+
	"right key."));
    add_cmd_item( ({ "small wooden chest", "wooden chest", "chest",
    "small wooden chests", "wooden chests", "chests" }),
	({ "get", "take", "pick", "push", "move", "slide" }),
	BSN("The chests are not large, but you cannot move them. "+
	"Perhaps they are bolted to the floor."));

    add_prop(ROOM_I_INSIDE,1);
    add_exit(EDORAS_DIR + "rooms/bhallway2", "north", 0, 1);
    reset_room();
}

/*
 * Function name:	reset_room
 * Description	:	clone up the guards
 */
public void
reset_room()
{
    if (clone_npcs(Men, EDORAS_DIR + "npc/rosoldier", -1.0))
    {
	Men[1]->team_join(Men[0]);
	Men[2]->team_join(Men[0]);
    }
}
