/*
 * /d/Gondor/rohan/edoras/gat_stairs.c
 *
 * Revision history:
 *
 * 2-Jan-1998, Gnadnar: general cleanup, add item detail
 */
#pragma strict_types

inherit "/d/Gondor/std/room";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

public int      stairmsg();

public void
create_gondor()
{
    set_short("Stairs");
    set_long(BSN("This narrow landing is the junction of three stone staircases. "+
        "To the east and west, stairs lead down about ten feet into guard rooms. "+
        "A third staircase leads up."));

    add_item( ({ "landing", "junction" }), long);
    add_item( ({ "stair", "stairs", "staircase", "staircases" }), BSN(
        "Narrow stone staircases lead down to the east and west guard rooms; "+
        "a third staircase leads up."));
    add_item( ({ "stone", "stones", "floor", "wall", "walls", "ceiling" }), BSN(
        "Stairs, walls and ceiling are dark grey stone."));
    add_item( ({ "east guard room", "west guard room", "guard room",
        "guard rooms" }), BSN(
        "Not much of the guard rooms can be seen from here."));

    add_exit("/d/Gondor/rohan/edoras/guard_w","west",stairmsg);
    add_exit("/d/Gondor/rohan/edoras/guard_e","east",stairmsg);
    add_exit("/d/Gondor/rohan/edoras/lookout","up",0);
    add_prop(ROOM_I_INSIDE,1);
}

/*
 * we continually get bug reports re the exits in this room being wrong.
 * maybe this will help people figure out that "east" and "west" are
 * really "down the east staircase" and "down the west staircase".
 */
public int
stairmsg()
{
    write("You descend the "+query_verb()+" staircase.\n");
    return 0;
}
