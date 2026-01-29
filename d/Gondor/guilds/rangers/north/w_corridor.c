/*
 *  /d/Gondor/guilds/rangers/north/w_corridor.c
 *
 *  A hallway in the North Hideout.
 *
 *  Coded by Elessar
 *    Modified by Alto, 15 July 2001, changed to fit revised themes
 *
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"
inherit RANGERS_NOR_DIR + "north_funcs.c";

#include <macros.h>
#include <stdproperties.h>

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

    return "You are standing in a western corridor of the underground "
        + "hideout. A large tapestry hangs on the east wall. Set into the "
        + "north corner is an iron torch stand" + txt+ "The corridor leads "
        + "to the south, where there appears to be some kind of shop, and "
        + "also opens into an interesting room to the north. Just west of "
        + "here is a room filled with mouth-watering scents.\n";
}

public void
create_gondor()
{
    set_short("a western corridor");
    set_long(&long_desc());

    north_add_items();

    add_item(({"room", "corridor", "western corridor"}), &long_desc());
    add_item(({"tapestry", "east wall"}), "On the tapestry you see a "
        + "scene from the most famous tale of the First Age. You see Luthien "
        + "dancing in the moonlight. She is in the forest of Neldoreth at the "
        + "river Esgalduin, in long lost Beleriand. Beren watches her as he "
        + "hides among the shadows.\n");
    add_item(({"north corner", "corner"}), "The north corner supports a "
        + "large iron torch stand.\n");

    add_item(({"sentinel", "grey-cloaked sentinel"}), "You are too late! "
        + "Ranger sentinels are usually too busy with their duties to "
        + "stand around long enough to be looked at.\n");

    add_exit(RANGERS_NOR_DIR + "north_train", "north");
    add_exit(RANGERS_NOR_DIR + "mess_hall", "west");
    add_exit(RANGERS_NOR_DIR + "shop", "south");

    add_prop(ROOM_I_INSIDE, 1);
    set_alarm(1.1, 0.0, &add_prop(ROOM_I_LIGHT, 0));

    reset_room();
}

void
reset_room()
{
    set_alarm(1.0, 0.0, &north_add_torch());
}

