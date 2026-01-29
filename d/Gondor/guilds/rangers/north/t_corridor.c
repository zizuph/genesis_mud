/*
 *  /d/Gondor/guilds/rangers/north/t_corridor.c
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

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "check_exit.c"

public string      long_desc();
public int         enter_tunnel();


string
long_desc()
{
    string txt;

    if (gTstand->query_torch_is_lit())
        txt = " from which a warm flickering light plays off the walls, "
            + "floor and ceiling. ";
    else
        txt = ". ";

    return "You are standing in the temple corridor of the underground "
        + "hideout. A marvelous tapestry hangs on the south wall. Set into "
        + "the north wall is an iron torch stand" + txt + "The corridor "
        + "leads east into the temple and opens onto a great hall "
        + "through an arched opening to the west.\n";
}

void
create_gondor()
{
    set_short("the temple corridor");
    set_long(&long_desc());

    north_add_items();

    add_item(({"room", "corridor", "temple corridor"}), &long_desc());
    add_item(({"tapestry", "south wall"}), "The tapestry depicts Tulkas, "
        + "the strongest of the Valar, laughing joyfully as he fights "
        + "bare-handed. There is something strange about this tapestry, "
        + "almost as if it were not mounted completely to the wall. You "
        + "wonder what is behind it.\n");
    add_item(({"opening", "arched opening"}), "The arched opening leads "
        + "to a great hall in the west.\n");
    add_item(({"walls"}), "There are two primary walls in the room, the "
        + "north wall and the south wall.\n");
    add_item(({"north wall"}), "Like much of the underground hideout, the "
        + "walls are made of stone. The north wall is unadorned save the "
        + "iron torch stand mounted upon it.\n");

    add_cmd_item(({"tapestry", "up tapestry"}), "lift", &enter_tunnel());
    add_cmd_item(({"tapestry", "over tapestry"}), "move", &enter_tunnel());

    add_item(({"sentinel", "grey-cloaked sentinel"}), "You are too late! "
        + "Ranger sentinels are usually too busy with their duties to "
        + "stand around long enough to be looked at.\n");

    add_exit(RANGERS_NOR_DIR + "temple", "east");
    add_exit(RANGERS_NOR_DIR + "great_hall", "west");

    add_prop(ROOM_I_INSIDE, 1);
    set_alarm(1.1, 0.0, &add_prop(ROOM_I_LIGHT, 0));

    reset_room();
}

void
reset_room()
{
    set_alarm(1.0, 0.0, &north_add_torch());
}

int
enter_tunnel()
{
    write("You move aside the tapestry and discover a small tunnel! You "
        + "silently slip behind the tapestry and into the tunnel.\n");
    say(QCTNAME(TP) + " slips silently behind the tapestry.\n");
    tell_room(RANGERS_NOR_DIR + "tunnel_a", QCTNAME(TP) + " slips silently "
        + "into the tunnel from the north.\n");

    TP->move_living("M", RANGERS_NOR_DIR + "tunnel_a", 1, 0);

    return 1;
}
