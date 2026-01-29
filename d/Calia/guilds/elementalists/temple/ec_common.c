/*
 * Common Room for the Elemental Guilds of Calia
 *
 * Created by Petros, April 2014
 */

#pragma strict_types

#include <stdproperties.h>
#include "defs.h"

inherit TEMPLE_ROOM_BASE;

public void load_board();

public void
create_temple_room()
{
    set_short("Temple Common Room");
    set_long("You are standing in the common room for the Elemental "
             + "Guilds of Calia. Located in the center of the room "
             + "is the common board. There doesn't appear to be any "
             + "exits in this room except back down. The walls here "
             + "are carved out of a beautiful slab of a white and "
             + "black swirled marble that you haven't seen anywhere "
             + "else in the Temple.\n\n");

    try_item( ({ "ladder", "down", "wooden ladder", "small ladder",
                    "small wooden ladder" }),
        "A small wooden ladder leads down from here back into "
        + "the Elemental Worshippers board room.\n");
    
    try_item( ({ "wall", "walls", "marble", "slab", "beautiful slab",
                    "swirled marble", "black marble", "white marble" }),
        "You do wonder where this very special marble comes from that "
        + "adorns the wall. Most likely, it must have been brought from "
        + "far away since it doesn't match much of the rest of the "
        + "crystalline Temple.\n");

    add_exit(ELEMENTALIST_TEMPLE + "ec_boardroom", "down");

    add_prop(ROOM_I_NO_STEAL, 1);
    add_prop(ROOM_I_NO_TELEPORT, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_INSIDE,1);

    load_board();
}

public void
load_board()
{
    setuid();
    seteuid(getuid());

    clone_object("/d/Genesis/obj/board")->move(this_object());
}
