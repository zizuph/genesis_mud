/*
 *  WALL_FLOOR_ONE + "1_archroom_1b.c"
 *
 *  Room for archers in the ring wall of Isengard.
 *
 *  Last modified by Alto, 06 October 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <filter_funs.h>
#include <composite.h>
#include "/d/Gondor/defs.h"
#include "../../igard_defs.h"

inherit IGARD_LIB + "igard_funcs.c";

public void      create_gondor();
public int       scan_slot();
public int       leave_room();

object           *items;
string           adjoining, surroundings;

static object *Archer   = allocate(2);

string
long_extratext()
{
    return "There are several cross-shaped slots in the north wall and "
    + "a tapestry hangs on the east wall.\n";
}


public void
create_gondor()
{
    set_short("A cramped stone room");
    set_long(archer_room_long_desc() + long_extratext());

    wall_add_items();
    archer_room_add_items();

    add_item(({"room", "area", "surroundings", "place", "stone room"}), 
        guardrm_long_desc() + long_extratext());

    add_item(({"north wall"}), "The north wall is made from rough-hewn "
        + "black stone and is perforated by numerous cross-shaped slots.\n");
    add_item(({"east wall"}), "The east wall is mostly covered with a large "
        + "threadbare tapestry.\n");
    add_item(({"tapestry", "large tapestry", "threadbare tapestry", 
        "large threadbare tapestry"}), "The tapestry conceals something on "
        + "the wall. You will need to move it to see what is behind.\n");

    add_cmd_item(({"adjoining room", "slot", "cross-shaped slot", 
        "slots", "cross-shaped slots", "through slot", "through slots",
        "through cross-shaped slots", "through the slots"}), "peer", &scan_slot());

    add_cmd_item(({"tapestry", "large tapestry", "threadbare tapestry", 
        "large threadbare tapestry"}), "move", &leave_room());

    add_item(({"adjoining room"}), &scan_slot());

    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}


public void
reset_room()
{
    clone_npcs(Archer,  IGARD_NPC + "igard_archer",  -1.0);
}

int
scan_slot()
{
    actor = TP;

    adjoining = WALL_TUNNEL_ONE + "et_gate1.c";
    adjoining->teleledningsanka();
    surroundings = find_object(adjoining)->long();

    items = FILTER_CAN_SEE(all_inventory(find_object(adjoining)), actor);

        if (items) 
        {
            if (sizeof(FILTER_DEAD(items)))
             surroundings += CAP(COMPOSITE_DEAD(FILTER_DEAD(items))) + ".\n";
            if (sizeof(FILTER_LIVE(items)))
             surroundings += CAP(COMPOSITE_LIVE(FILTER_LIVE(items))) + ".\n";
        }

    actor->catch_tell("You peer through the cross-shaped slot and see:\n\n"
            + surroundings + "\n");
    tell_room(environment(actor), QCTNAME(actor) + " peers through the "
            + "cross-shaped slot.\n", 
            ({actor}));

    return 1;
}


int
leave_room()
{
    write("You move aside the tapestry and silently slip behind it.\n");
    say(QCTNAME(TP) + " slips silently behind the tapestry.\n");
    tell_room(WALL_TUNNEL_ONE + "et5.c", QCTNAME(TP) + " slips silently "
        + "into the room from behind the tapestry.\n");

    TP->move_living("M", WALL_TUNNEL_ONE + "et5.c", 1, 0);

    return 1;
}

