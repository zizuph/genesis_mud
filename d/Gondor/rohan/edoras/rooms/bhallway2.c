/*
 * /d/Gondor/rohan/edoras/rooms/bhallway2.c
 *
 * Modification log:
 * 4-Dec-1997, Gnadnar: General revision.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void	create_gondor();
public void	reset_room();
static object	*Men = allocate(2);

/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor()
{
    set_short("Rohirrim barracks");
    set_long(BSN(
	"The barracks of the Rohirrim house many of the guards. " +
        "To the north and south are sleeping chambers " +
        "for the guards, and the hallway continues west. "+
	"A weapon rack hangs on the east wall, at the end of the hallway."));
    add_item(({"barracks","room"}),long);
    add_item(({"east wall","rack","weapon rack"}), BSN(
	"The weapon rack suspended from the east wall is locked tight "+
	"to prevent the unauthorized "+
	"removal of equipment.  To the right of the rack, a black "+
        "broadsword is set into the wall."));
    add_item(({"broadsword","black broadsword"}),BSN(
	"The black broadsword looks oddly familiar."));
    add_item(({"slab","slabs","stone","stones","stone slab","stone slabs",
	"floor","ground"}), BSN(
    	"The floor is made from large stone slabs. In the middle of " +
    	"the hallway, the surface is a bit lower than close to the walls, " +
    	"probably from the daily tear and wear by heavy boots. In some " +
    	"places old stone slabs have been replaced by newer ones."));
    add_item(({"boulder","boulders","wall","walls"}), BSN(
	"The boulders that form the walls are roughly cut, "+
	"but they fit tightly together."));
    add_item(({"hallway", "corridor","hall"}),BSN(
	"The hallway leads back to the west."));
    add_item(({"stone ceiling","ceiling"}), BSN(
	"The stone ceiling is close overhead."));
    add_item(({"sleeping chamber","chamber","sleeping chambers",
	"chambers"}), BSN(
	"Sleeping chambers lie to the north and south."));

    add_cmd_item( ({ "rack", "weapon rack" }),
	({ "open", "unlock" }),
	"The rack is locked, and you do not have the proper key.\n" );
    add_cmd_item( ({ "broadsword from wall", "black broadsword from wall" }),
	({ "get", "take", "pick", "pry", "prise", "prize", "remove" }),
	"The broadsword is firmly set into the wall. You cannot budge it.\n" );

    add_prop(ROOM_I_INSIDE,1);
    add_exit(EDORAS_DIR + "rooms/bhallway", "west", 0, 1);
    add_exit(EDORAS_DIR + "rooms/sleep1", "north", 0, 1);
    add_exit(EDORAS_DIR + "rooms/sleep2", "south", 0, 1);
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
    }
}
