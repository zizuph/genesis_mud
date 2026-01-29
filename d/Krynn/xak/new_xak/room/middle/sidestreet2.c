/* 
 * Xak Tsaroth - Lower level
 * Originally coded by Percy
 * Revamped by Rastlin
 */
#pragma strict_types

#include "../../local.h"

inherit INROOM;

object gDrac;

public void
reset_xak_room()
{
    MOVE(gDrac, GET_NPC_MIDDLE);
}

public void
create_xak_room()
{
    set_short("An old deserted street");
    set_long("You are in an old ruined street of Xak Tsaroth deep " +
	     "underground in a huge cavern. The buildings has not " +
	     "collapsed, but they lean drunkenly against those opposite, " +
	     "forming a ragged archway over the street. A small building " +
	     "seems in particulary good shape to the east and an old " +
	     "metal sign hangs over the doorway.\n");

    add_exit(MIDDLE + "sidestreet1", "north");
    add_exit(MIDDLE + "sage1", "east");
    add_exit(MIDDLE + "vinetop", "south");

    add_item(({"sign", "metal sign"}), "The sign reads: 'The Sage Front.'\n");
    add_item(({"building", "buildings", "small building", "wall", "walls"}), 
	     "The buildings are mostly still standing but in a dangerous " +
	     "shape many of the walls are leaning over ready to collapse. " +
	     "However one small building to your east looks in a better " +
	     "state than most.\n");
    add_cmd_item("sign", "read", "The sign reads: 'The Sage Front.'\n");

    seteuid(getuid());

    reset_xak_room();
}
