/*
 *  /d/Gondor/guilds/rangers/north/tunnel_a.c
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

public string      long_desc();
public int         enter_hideout();

string
long_desc()
{
    string txt;

    if (gTstand->query_torch_is_lit())
        txt = " from which a warm flickering light plays off the walls, "
            + "floor and ceiling.";
    else
        txt = ". ";
 
    return "You are in a small tunnel behind the tapestry in the temple "
        + "corridor. Set into the west wall is an iron torch stand" + txt
        + " Unlike much of the underground hideout, which is old "
        + "beyond remembering, this place seems of much more recent "
        + "construction. The tunnel leads due south from here.\n";
}

void
create_gondor()
{
    set_short("a small tunnel");
    set_long(&long_desc());

    north_add_items();

    add_item(({"tunnel", "small tunnel"}), &long_desc());
    add_item(({"tapestry"}), "You see the back side of a tapestry depicting "
        + "Tulkas, the strongest of the Valar, laughing joyfully as he "
        + "fights bare-handed. You can enter the underground hideout by "
        + "lifting it.\n");
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

    add_cmd_item(({"tapestry", "up tapestry"}), "lift", &enter_hideout());
    add_cmd_item(({"tapestry", "over tapestry"}), "move", &enter_hideout());

    add_exit(RANGERS_NOR_DIR + "tunnel_b","south");

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
enter_hideout()
{
    object tp = this_player();

    write("You move aside the tapestry and silently slip into the " +
        "hideout.\n");
    say(QCTNAME(tp) + " slips silently around the tapestry.\n");
    TP->move_living("M", RANGERS_NOR_DIR + "t_corridor", 1, 0);
    tell_room(RANGERS_NOR_DIR + "t_corridor", QCTNAME(tp) + 
        " slips silently into the corridor from behind " +
        "the tapestry.\n", tp);

    return 1;
}
