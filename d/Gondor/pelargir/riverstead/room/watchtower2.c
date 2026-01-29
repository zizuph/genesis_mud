/*
 *  NCAMP_ROOM + "watchtower.c"
 *
 *  A watchtower. Only newbies and wizards should ever see this place.
 *
 *  Last modified by Alto, 16 November 2002
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include <math.h>
#include "/d/Gondor/defs.h"
#include "../ncamp_defs.h"

inherit NCAMP_LIB + "ncamp_funcs.c";

public void        create_gondor();
public string      long_desc();
public int         exit_room();
public int         move_climber(object actor);
public int         jump_hole(object actor);

object             actor;

public void
create_gondor()
{
    set_short("On a ladder, halway up the tower");
    set_long(&long_desc());

    add_item(({"room", "area", "surroundings", "place",
        "watchtower", "tower", "building"}), long_desc);
        
    add_item(({"pole", "poles"}), "The poles supporting the tower "
        + "are in fact the trunks of four great trees, doubtless "
        + "cut from the surrounding woodland.\n");
    add_item(({"board", "boards", "timber", "rough-cut timber"}),
        "At intervals up the tower, the four large poles are "
        + "braced together with boards milled from local timber.\n");
    add_item(({"ladder", "narrow ladder"}), "You cannot climb any "
        + "further on this ladder, as you are already perched "
        + "precariously at its top. To get onto the platform, you "
        + "will need to jump to the hole above you.\n");
    add_item(({"platform"}), "The four large poles are topped with "
        + "a wooden platform. To get a better look, you will need "
        + "to jump to it.\n");
    add_item(({"ground", "floor"}), "The ground below you is bare dirt.\n");
    add_item(({"hole", "hole in the platform"}), "Above you is a hole "
        + "in the middle of the platform. You will need to jump to "
        + "it in order to reach the top of the tower.\n");

    add_cmd_item(({"hole", "to hole", "platform", "to the platform",
        "to the hole", "to platform"}), "jump", &exit_room());

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(NCAMP_ROOM + "watchtower.c", "down");

    reset_room();
}

string
long_desc()
{

    return "You have reached the top of the narrow ladder, but "
        + "it does not ascend all the way up to the hole in the "
        + "middle of the platform above you. The only way to reach "
        + "the platform is to jump to it. Otherwise you will need "
        + "to climb back down and give up.\n";
}

int
jump_hole(object actor)
{

    set_alarm(0.0, 0.0, &actor->catch_tell("You take a deep breath and gather your "
        + "strength.\n"));
    set_alarm(0.5, 0.0, &actor->catch_tell("With a gasp you leap into the air!\n"));

    tell_room(environment(actor), QCTNAME(actor) + " raises " + POSSESSIVE(actor)
        + " head and looks at the hole above.\n", 
        ({actor}));
    set_alarm(0.5, 0.0, &tell_room(environment(actor), QCTNAME(actor) +
        " takes a gasp of air and jumps toward the hole.\n", ({actor})));

    return 1;
}


int
exit_room()
{
    object actor = this_player();
    jump_hole(actor);
    set_alarm(1.0, 0.0, &move_climber(actor));        
    return 1;
}


int
move_climber(object actor)
{
    say(QCTNAME(actor) + " jumps through the hole onto the platform.\n");
    tell_room(NCAMP_ROOM + "platform", QCNAME(actor) + " arrives "
        + "through the hole.\n");

    TP->move_living("M", NCAMP_ROOM + "platform", 1, 0);
    return 1;
}



