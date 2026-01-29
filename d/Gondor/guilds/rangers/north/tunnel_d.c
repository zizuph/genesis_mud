/*
 *  /d/Gondor/guilds/rangers/north/tunnel_d.c
 *
 *  A secret tunnel in the North Hideout.
 *
 *  Coded by Alto, 16 July 2001
 *
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"

inherit RANGERS_NOR_DIR + "north_funcs.c";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "check_exit.c"

string
long_desc()
{
    string txt;

    if (gTstand->query_torch_is_lit())
        txt = " from which a warm flickering light plays off the walls, "
            + "floor and ceiling. ";
    else
        txt = ". ";
 
    return "You are in a small tunnel somewhere beneath the ruins of Fornost. "
        + "Set into the west wall is an iron torch stand" + txt + "The "
        + "tunnel is narrow and damp, with a palpable upward slope to the "
        + "south. From here you may walk directly northwest or south.\n";
}

void
create_gondor()
{
    set_short("a small tunnel");
    set_long(&long_desc());

    north_add_items();

    add_item(({"tunnel", "small tunnel"}), &long_desc());
    add_item(({"walls"}), "There are two primary walls in the room, the west "
        + "wall and the east wall.\n");
    add_item(({"west wall"}), "Like much of the underground hideout, the "
        + "walls are made of stone. The west wall is unadorned save the iron "
        + "torch stand mounted upon it.\n");
    add_item(({"east wall"}), "Like much of the underground hideout, the "
        + "walls are made of stone. The east wall is unadorned.\n");
    add_item(({"sentinel", "grey-cloaked sentinel"}), "You are too late! "
        + "Ranger sentinels are usually too busy with their duties to "
        + "stand around long enough to be looked at.\n");
    add_item(({"slope", "upward slope"}), "The tunnel inclines " + 
        "upward to the south.\n");

    add_exit(RANGERS_NOR_DIR + "tunnel_c","northwest");
    add_exit(RANGERS_NOR_DIR + "tunnel_e","south");

    add_prop(ROOM_I_INSIDE, 1);
    set_alarm(1.1, 0.0, &add_prop(ROOM_I_LIGHT, 0));

    reset_room();
}

void
reset_room()
{
    set_alarm(1.0, 0.0, &north_add_torch());
}
