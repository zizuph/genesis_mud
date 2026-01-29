/*
 * /d/Gondor/rohan/edoras/rooms/sleep1.c
 *
 * Modification log:
 * 27-aug-1997, Olorin: General revision.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void    create_gondor();
public void    reset_room();
static object *Men = allocate(4);
static object Officer;

/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor()
{
    set_short("sleep chamber of the Rohirrim guard");
    set_long(BSN(
	"This chamber appears built to hold a quite number of people. " +
        "Beds line the walls and small chests stand at the foot of each. "+
        "To the south is a stone hallway."));
    add_item(({"chamber","sleep chamber","barracks","room"}),long);
    add_item(({"bed","beds"}), BSN(
        "All the beds are neatly kept and made up. At the foot of each " +
        "bed is a small wooden chest."));
    add_item(({"small wooden chest","wooden chest","chest"}), BSN(
	"The wooden chests are not very large, and show signs of hard "+
	"use."));
    add_item(({"stone","stones","stone floor","floor","ground"}), BSN(
	"The stone floor has been worn by much traffic."));
    add_item(({"boulder","boulders","wall","walls"}), BSN(
	"Large boulders, expertly fit together, form the walls "+
	"of the sleeping chamber."));
    add_item(({"stone ceiling","ceiling"}), BSN(
	"The rough stone ceiling is fairly low."));
    add_item(({"hall","hallway"}), BSN(
        "The hallway lies south of the sleeping chamber."));

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
    add_exit(EDORAS_DIR + "rooms/bhallway2", "south", 0, 1);
    reset_room();
}

/*
 * Function name:	reset_room
 * Description	:	clone up the guards
 */
public void
reset_room()
{
    if (!objectp(Officer))
    {
        Officer = clone_object(EDORAS_DIR + "npc/edoras_officer");
        Officer->arm_me();
        Officer->move(TO);
    }
    if (clone_npcs(Men, EDORAS_DIR + "npc/rosoldier", -1.0))
    {
   Men[0]->team_join(Officer);
   Men[1]->team_join(Officer);
   Men[2]->team_join(Officer);
   Men[3]->team_join(Officer);
    }
}
