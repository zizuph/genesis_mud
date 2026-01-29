/*
 *  NCAMP_ROOM + "camp13.c"
 *
 *  A dirt path. Only newbies and wizards should ever see this place.
 *
 *  Last modified by Alto, 17 November 2002
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

static object *Man = allocate(2);
static object *Orc = allocate(2);

public void
create_gondor()
{
    set_short("in the central part of a settlement");
    set_long(&long_desc());

    sky_add_items();
    camp_add_items();
    add_camp_tells();

    add_item(({"room", "area", "surroundings", "place",
        "landscape", "settlement", "village", "camp"}), long_desc);
        
    add_item(({"spark", "sparks"}), "Thousands of bright sparks "
        + "waft through the air, product of the many burning "
        + "huts to the east.\n");
    add_item(({"fire", "fires"}), "Most of the huts to the east "
        + "of here are actively burning, with flames licking away "
        + "at the boards from which they were built.\n");
    add_item(({"flames"}), "Its what fires are made of. There are "
        + "many of them to the east.\n");
    add_item(({"hut", "burning hut"}), "The hut before you is on "
        + "fire, but still looks safe enough to enter.\n");
        
    add_prop(ROOM_I_INSIDE, 0);
    
    defence_status = 1;

    add_exit(NCAMP_ROOM + "camp14.c", "north");
    add_exit(NCAMP_ROOM + "camp19.c", "east");
    add_exit(NCAMP_ROOM + "camp12.c", "south");
    add_exit(NCAMP_ROOM + "camp7.c", "west");
    add_exit(NCAMP_ROOM + "hut13.c", "enter", 0, 0, 1);

    reset_room();
}

public void
reset_room()
{
    if(defence_status)
    {
    clone_npcs(Man, NCAMP_NPC + "ncamp_human_male", -1.0);
    return;
    }

    clone_npcs(Orc, NCAMP_NPC + "ncamp_orc", -1.0);
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        sky_add_items();
        start_room_tells();
    }
}

string
long_desc()
{
    return "Here in the central part of the camp, you can see that "
        + "many of the huts to the east have begun to burn to the "
        + "ground. Sparks fly high into the air as each one collapses."
        + sky_desc() 
        + " A burning hut stands nearby, although the fire is only "
        + "in the early stages, so it might still be safe to enter.\n";
}
