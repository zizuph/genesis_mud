/*
 *  WALL_FLOOR_FOUR + "s_para4.c"
 *
 *  Parapet overlooking the southern gate of Isengard.
 *
 *  Last modified by Alto, 01 October 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../../igard_defs.h"

inherit IGARD_LIB + "igard_funcs.c";

public void        create_gondor();

static object *Archer   = allocate(3);
static object *Uruk     = allocate(1);

object catapultee;

string
long_extratext()
{
    return "This section of the ring wall looks to the south, where "
    + "a great highway leads away from Isengard toward the Gap of Rohan. "
    + "As this is the highest parapet along the ring wall, there is no "
    + "higher vantage in Isengard save Orthanc itself. Directly below you "
    + "is the great southern gate, the only entrance or exit from the "
    + "fortification of Isengard. A stairwell ascends from below.\n";

}


public void
create_gondor()
{
    set_short("A parapet atop the southern ring wall");
    set_long(parapet_long_desc() + long_extratext());

    sky_add_items();
    parapet_add_items();

    add_item(({"room", "area", "surroundings", "place", "parapet",
        "stone parapet", "section", "landscape"}), 
        parapet_long_desc() + long_extratext());

    add_item(({"stairwell", "stairs", "steps", "stair"}), "The stairwell "
        + "opens in the middle of the parapet and rises in spiral fashion "
        + "to the next parapet.\n");
    add_item(({"highway", "road", "street"}), "A wide highway runs "
        + "from the distant south right up to the great southern gate "
        + "directly below. It seems well-crafted for the passage of "
        + "heavy carts and horses.\n");
    add_item(({"gap of rohan"}), "The gap is a large open area between "
        + "the Misty Mountains to the north and the White Mountains to "
        + "the south. Isengard looks down upon the Gap of Rohan much as a "
        + "majestic bird of prey watches a field for stray mice.\n");
    add_item(({"white mountain", "white mountains"}), "The White Mountains, "
        + "on the southern edge of the Gap of Rohan, can just barely be "
        + "made out to the south.\n");
    add_item(({"rohan"}), "The land of the Horse Lords lies to the "
        + "southeast. Although little of it can be seen from this section "
        + "of the wall, it is rumoured to be a seemingly endless ocean "
        + "of grass.\n");
    add_item(({"gate", "southern gate", "great southern gate", "entrance",
        "exit"}), "As it is directly below you, it is very difficult to "
        + "discern without leaning far over the ramparts. The strong wind "
        + "here renders that kind of curiosity extremely dangerous.\n");
    add_item(({"catapult", "war-engine", "large catapult"}), "A large "
        + "catapult, made of wood and rope, it is used to propel massive "
        + "boulders down upon the heads of invaders. It also looks of the "
        + "right size to fling bodies too.\n"); 

    add_parapet_tells();

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(WALL_FLOOR_FOUR + "s_para3.c",        "down");

    reset_room();
}

public void
reset_room()
{
    clone_npcs(Uruk,    IGARD_NPC + "i_quest_uruk.c",  -1.0);
    clone_npcs(Archer,  IGARD_NPC + "igard_archer",    -1.0);
}


int
push_catapult()
{
    object catapulter;
    catapultee = TP;

    catapulter = present("_igard_archer", TO);

    if (catapultee->query_npc())
    {
    return 1;
    }

    if (!ENEMY)
    {
    return 1;
    }

    if (!CAN_SEE(catapulter, catapultee))
    {
    return 1;
    }

    if(present("_igard_archer", TO))
    {
    TP->catch_tell("You are pushed against your will into a "
        + "large catapult!\n"
        + "Kicking and screaming, you are hurled violently into the "
        + "air as the great war-engine is triggered!\n");
    tell_room(environment(catapultee), QCTNAME(catapultee) + " is pushed "
        + "kicking and screaming into the large catapult! "
        + CAP(PRONOUN(catapultee)) + " is hurled violently into the "
        + "air as the great war_engine is triggered!\n", 
        ({catapultee}));

    TP->move_living("M", IGARD_ROOM + "catapult_room.c", 1, 0);

    return 1;
    }

    else
    {
    return 1;
    }
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
        set_alarm(12.0, 0.0, &push_catapult());
}



