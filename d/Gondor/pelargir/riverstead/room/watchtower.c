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
public int         ascend_ladder(object actor);

object             actor;

static object *Woman = allocate(2);
static object *Orc = allocate(2);

public void
create_gondor()
{
    set_short("At the base of a watchtower");
    set_long(&long_desc());

    add_item(({"room", "area", "surroundings", "place",
        "watchtower", "tower", "building"}), long_desc);
        
    add_item(({"pole", "poles"}), "The poles supporting the tower "
        + "are in fact the trunks of four great trees, doubtless "
        + "cut from the surrounding woodland.\n");
    add_item(({"board", "boards", "timber", "rough-cut timber"}),
        "At intervals up the tower, the four large poles are "
        + "braced together with boards milled from local timber.\n");
    add_item(({"ladder", "narrow ladder"}), "The ladder is not "
        + "attached to the rest of the structure, but is rather "
        + "rooted in the ground. It rises far above and appears "
        + "to lead to the platform at the top of the tower\n");
    add_item(({"platform"}), "The four large poles are topped with "
        + "a wooden platform. To get a better look, you will need "
        + "to climb the ladder.\n");
    add_item(({"ground", "floor"}), "The ground here is bare dirt.\n");
    
    add_cmd_item(({"ladder", "the ladder", "narrow ladder", "the narrow ladder"}),
            "climb", &exit_room());

    add_prop(ROOM_I_INSIDE, 1);

    defence_status = 1;

    add_exit(NCAMP_ROOM + "camp7.c", "out");

    reset_room();
}

public void
reset_room()
{
    if(defence_status)
    {
        clone_npcs(Woman, NCAMP_NPC + "ncamp_human_female", -1.0);
        return;
    }

    clone_npcs(Orc, NCAMP_NPC + "ncamp_orc", -1.0);
}

string
long_desc()
{
    return "You are standing at the base of a tall watchtower. "
        + "The tower is constructed from four large poles set in "
        + "a wide square, braced together at intervals with boards "
        + "of rough-cut timber. In the middle of the structure "
        + "there stands a narrow ladder. Perhaps you could climb "
        + "up to the top and have a peek.\n";
}

int
ascend_ladder(object actor)
{

    set_alarm(0.0, 0.0, &actor->catch_tell("You take ahold of the ladder at its "
        + "lowest rungs.\n"));
    set_alarm(0.5, 0.0, &actor->catch_tell("Although it wobbles a bit, you "
        + "decide to climb on up and have a look.\n"));

    tell_room(environment(actor), QCTNAME(actor) + " puts " + POSSESSIVE(actor)
        + " hands on the lowest rungs of the ladder.\n", 
        ({actor}));
    set_alarm(0.5, 0.0, &tell_room(environment(actor), QCTNAME(actor) +
        " decides to climb on up, despite an obvious wobble to "
        + "the ladder.\n", ({actor})));

    return 1;
}


int
exit_room()
{
    object actor = this_player();
    
    ascend_ladder(actor);
    set_alarm(1.0, 0.0, &move_climber(actor));        
    return 1;
}


int
move_climber(object actor)
{
    say(QCTNAME(actor) + " leaves up the narrow ladder.\n");
    tell_room(NCAMP_ROOM + "watchtower2", QCNAME(actor) + " arrives "
        + "climbing the narrow ladder.\n");

    actor->move_living("M", NCAMP_ROOM + "watchtower2", 1, 0);
    return 1;
}



