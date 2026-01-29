/*
 *  WALL_FLOOR_ONE + "1_archroom_4a.c"
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

object           *items;
string           adjoining, surroundings;

static object *Archer   = allocate(2);

string
long_extratext()
{
    return "There are several cross-shaped slots in the east wall.\n";
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

    add_item(({"east wall"}), "The east wall is made from rough-hewn "
        + "black stone and is perforated by numerous cross-shaped slots.\n");

    add_cmd_item(({"adjoining room", "slot", "cross-shaped slot", 
        "slots", "cross-shaped slots", "through slot", "through slots",
        "through cross-shaped slots", "through the slots"}), "peer", &scan_slot());

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(WALL_FLOOR_ONE  + "1_archroom_3a.c",       "north");

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

    adjoining = IGARD_WALL + "gate_tun2.c";
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



