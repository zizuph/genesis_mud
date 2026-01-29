/*
 *  /d/Gondor/guilds/rangers/north/stairs.c
 *
 *  A stairway in the North Hideout.
 *
 *  Coded by Elessar
 *    Modified by Alto, 17 July 2001, changed to fit revised themes
 *    No longer leads to doorway.
 *
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"
inherit RANGERS_NOR_DIR + "north_funcs.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "check_exit.c"

public string long_desc();


string
long_desc()
{
    string txt;

    if (gTstand->query_torch_is_lit())
        txt = " from which a warm flickering light plays off the walls, "
            + "floor and ceiling. ";
    else
        txt = ". ";

    return "You are in a staircase inside an old tower. Set into the west "
        + "wall is an iron torch stand" + txt + "The top of the stairs "
        + "cannot be seen through a huge pile of fallen stone and rubble "
        + "which obstructs whatever exit might once have been there. The "
        + "stairs lead only down into a torchlit corridor.\n";
}

public void
create_gondor()
{
    set_short("on a staircase inside a tower");
    set_long(&long_desc());

    north_add_items();

    add_item(({"room", "corridor", "staircase"}), &long_desc());
    add_item(({"stairs", "top"}), "The stairs look as though they have "
        + "not felt the tread of booted feet for many years. A thick "
        + "layer of dust coats the steps.\n");
    add_item(({"step", "steps"}), "They are coated with a thick layer "
        + "of dust.\n");
    add_item(({"pile", "stone", "rubble", "huge pile"}), "Upon careful "
        + "examination of the rubble, you think you see a few old bones.\n");
    add_item(({"bones", "old bones"}), "The bones probably belong to a few "
        + "dead rangers who refused to desert their post when the ceiling "
        + "over the doorway collapsed. You wonder what their names were.\n");
    add_item(({"west wall"}), "Like much of the underground hideout, the "
        + "walls are made of stone. The west wall is relatively unadorned, "
        + "save for the iron torch stand mounted upon it.\n");

    add_item(({"sentinel", "grey-cloaked sentinel"}), "You are too late! "
        + "Ranger sentinels are usually too busy with their duties to "
        + "stand around long enough to be looked at.\n");

    add_exit(RANGERS_NOR_DIR + "o_corridor", "down");

    add_prop(ROOM_I_INSIDE, 1);
    set_alarm(1.1, 0.0, &add_prop(ROOM_I_LIGHT, 0));

    restore_allowed();
    reset_room();
}

void
reset_room()
{
    set_alarm(1.0, 0.0, &north_add_torch());
}

