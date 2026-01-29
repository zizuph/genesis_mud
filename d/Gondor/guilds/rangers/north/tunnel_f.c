/*
 *  /d/Gondor/guilds/rangers/north/tunnel_f.c
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
public int         exit_room();
public int         move_ranger(object who);

string
long_desc()
{
    if (gTstand->query_torch_is_lit())
    {
    return "You are in a small tunnel somewhere beneath the ruins of Fornost. "
        + "Set into the west wall is an iron torch stand from "
        + "which a warm flickering light plays off the walls, floor and "
        + "ceiling. The tunnel comes to an abrupt end here. A small ladder "
        + "leads upward to a hatch in the ceiling.\n";
    }
    return "You are in a small tunnel somewhere beneath the ruins of Fornost. "
        + "The tunnel comes to an abrupt end here. A small ladder "
        + "leads upward to a hatch in the ceiling.\n";
}

void
create_gondor()
{
    set_short("At the end of the tunnel");
    set_long(&long_desc());

    north_add_items();

    add_item(({"tunnel", "small tunnel"}), &long_desc());
    add_item(({"walls"}), "There are two primary walls in the room, the west "
        + "wall and the east wall.\n");
    add_item(({"west wall"}), "Like much of the underground hideout, the "
        + "walls are made of stone. The west wall is unadorned save the iron "
        + "torch stand mounted upon it.\n");
    add_item(({"east wall"}), "Like much of the underground hideout, the "
        + "walls are made of stone. Mounted on the east wall is a small "
        + "ladder.\n");
    add_item(({"ladder", "small ladder", "wooden ladder"}), "A sturdy wooden "
        + "ladder is mounted against the east wall, leading up to a hatch in "
        + "ceiling. You could reach the hatch by ascending the ladder.\n");
    add_item(({"hatch", "hatch in ceiling"}), "You cannot reach it from here.\n");

    add_item(({"sentinel", "grey-cloaked sentinel"}), "You are too late! "
        + "Ranger sentinels are usually too busy with their duties to "
        + "stand around long enough to be looked at.\n");

    add_exit(RANGERS_NOR_DIR + "tunnel_e","southwest");

    add_cmd_item(({"ladder", "the ladder", "small ladder", "the small ladder"}),
            "ascend", &exit_room());

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
exit_room()
{
    object actor = TP;

    set_alarm(0.0, 0.0, &actor->catch_tell("You grasp the lower rungs and "
        + "rest your weight on the small ladder. It seems to hold.\n"));
    set_alarm(1.0, 0.0, &actor->catch_tell("You quickly ascend the small "
        + "ladder.\n"));

    tell_room(environment(actor), QCTNAME(actor) + " rests " + POSSESSIVE(TP)
        + " weight on the small ladder. It seems to hold.\n", actor);
    set_alarm(1.0, 0.0, &tell_room(environment(actor), QCTNAME(actor) +
        " quickly ascends the small ladder.\n", actor));

    set_alarm(2.0, 0.0, &move_ranger(actor));        
    return 1;
}


int
move_ranger(object who)
{
    say(QCTNAME(who) + " leaves climbing the small ladder.\n");
    tell_room(RANGERS_NOR_DIR + "exit", QCTNAME(who) + " arrives "
        + "climbing the small ladder.\n");

    who->move_living("M", RANGERS_NOR_DIR + "exit", 1, 0);
    return 1;
}

