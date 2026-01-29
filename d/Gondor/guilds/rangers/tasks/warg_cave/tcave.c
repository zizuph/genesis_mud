/*
 * /d/Gondor/lebennin/wolfcave/ranger_caves/tcave.c
 *
 * Coded by Tigerlily--October 29, 2004
 * For use with ranger task #8
 * Revision history:
 * 
 */
#pragma strict_types

inherit "/std/room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"
#include "cave_defs.h"


//prototypes
string climb_wall(string str);

void
create_room()
{
    set_short("small cave");
    set_long("The cave is a dead end, and the only exit is " +
        "to the south. The walls, ceiling and floor are the same " +
        "rough rock. Debris is scattered along the floor.\n");
    add_item("walls", "The walls are rough rock. You notice that " +
        "there is something unusual about the west wall.\n");
    add_item(({"ceiling", "floor"}), "The ceiling and floor are " +
        "made from the same rough rock. You look more closely at " +
        "the walls and notice something different.\n");
    add_item(({"west wall", "rope", "frayed rope"}),
        "There is a frayed rope hanging against the west wall. It " +
        "seems to be suspended from a narrow ledge above.\n");
    add_item(({"debris", "rock floor", "floor"}), 
        "You look through the debris and find what " +
        "appear to be scattered bones and pieces of rotted flesh.\n");
    add_exit(CAVE_PATH + "rcave10", "south", 0, 0);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -1);
}

void
init()
{
    ::init();
    add_action(&climb_wall(), "climb");
}

int
climb_wall(string str)
{
    object tp = this_player();

    if (!strlen(str) && str != "wall" && str != "rope")
    {
        notify_fail("Climb what?\n");
        return 0;
    }
    write("You manage to climb the wall.\n");
    say(QCTNAME(tp) + " climbs up the wall.\n");
    tp->move_living("M", CAVE_PATH + "ledge1", 1, 0);
    say(QCTNAME(tp) + " climbs in from the cave below.\n");
    return 1;
}


