/*
 *  /d/Gondor/guilds/rangers/north/o_corridor.c
 *
 *  A hallway in the North Hideout.
 *
 *  Coded by Elessar
 *    Modified by Alto, 17 July 2001, changed to fit revised themes
 *
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"

inherit RANGERS_NOR_DIR + "north_funcs.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "check_exit.c"

public string      long_desc();


string
long_desc()
{
    string txt;

    if (gTstand->query_torch_is_lit())
        txt = " from which a warm flickering light plays off the walls, "
            + "floor and ceiling. ";
    else
        txt = ". ";

    return "You are standing in a corridor of the underground "
        + "hideout. The walls are made of stone blocks, smooth to the "
        + "touch, so skillfully set that the seams are hard to detect. "
        + "Set into the west wall is an iron torch stand" + txt
        + "To the south a stairway leads up, while to the north the "
        + "corridor ends in an arched opening.\n";
}


public void
create_gondor()
{
    set_short("a corridor in the northern headquarters");
    set_long(&long_desc());

    north_add_items();

    add_item(({"room", "corridor", "room"}), &long_desc());
    add_item(({"walls"}), "There are two primary walls in the room, the west "
        + "wall and the east wall.\n");
    add_item(({"west wall"}), "Like much of the underground hideout, the "
        + "walls are made of stone. The west wall is relatively unadorned, "
        + "save for the iron torch stand mounted upon it.\n");
    add_item(({"east wall"}), "Like much of the underground hideout, the "
        + "walls are made of stone. The east wall is entirely unadorned.\n");
    add_item(({"blocks", "stone blocks"}), "The stone blocks are smooth to "
        + "the touch and skillfully set such that the seams between them are "
        + "almost impossible to detect.\n");
    add_item(({"seam", "seams"}), "They are almost impossible to detect!\n");
    add_item(({"opening", "arched opening"}), "The arched opening leads into "
        + "a great hall.\n");
    add_item(({"stairs", "stairway", "stairwell"}), "The stairs begin at the "
        + "south end of the room.\n");

    add_item(({"sentinel", "grey-cloaked sentinel"}), "You are too late! "
        + "Ranger sentinels are usually too busy with their duties to "
        + "stand around long enough to be looked at.\n");

    add_exit(RANGERS_NOR_DIR + "great_hall", "north");
    add_exit(RANGERS_NOR_DIR + "stairs", "up");

    add_prop(ROOM_I_INSIDE, 1);
    set_alarm(1.1, 0.0, &add_prop(ROOM_I_LIGHT, 0));

    reset_room();
}


void
reset_room()
{
    set_alarm(1.0, 0.0, &north_add_torch());
}
