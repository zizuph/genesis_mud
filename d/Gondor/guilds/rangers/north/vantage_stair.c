/*
 *  /d/Gondor/guilds/rangers/north/vantage_stair.c
 *
 *  A stairway in the North Hideout.
 *
 *  Coded by Alto, 18 July 2001
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
 
    return "You are are standing at the bottom of a long stairwell "
        + "somewhere beneath the ruins of Fornost. Set into the north "
        + "wall is an iron torch stand" + txt + "The stairwell looks "
        + "well-used, but also seems to have fallen somewhat into disrepair. "
        + "The stairs lead directly up from here. You may also return to the "
        + "tunnel by walking west.\n";
}

void
create_gondor()
{
    set_short("at the bottom of a long stairwell");
    set_long(&long_desc());

    north_add_items();

    add_item(({"stairs", "stairwell", "stairway"}), &long_desc());
    add_item(({"tunnel"}), "It lies to the west.\n");
    add_item(({"north wall"}), "Like much of the underground hideout, the "
        + "walls are made of stone. The west wall is unadorned save the iron "
        + "torch stand mounted upon it.\n");
    add_item(({"sentinel", "grey-cloaked sentinel"}), "You are too late! "
        + "Ranger sentinels are usually too busy with their duties to "
        + "stand around long enough to be looked at.\n");

    add_exit(RANGERS_NOR_DIR + "tunnel_e","west", &check_ranger());
    add_exit(RANGERS_NOR_DIR + "vantage1","up", &check_ranger());

    add_prop(ROOM_I_INSIDE, 1);
    set_alarm(1.1, 0.0, &add_prop(ROOM_I_LIGHT, &daylight()));

    reset_room();
}

void
reset_room()
{
    set_alarm(1.0, 0.0, &north_add_torch());
}
