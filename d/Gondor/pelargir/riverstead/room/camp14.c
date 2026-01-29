/*
 *  NCAMP_ROOM + "camp14.c"
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
    set_short("in the northern part of a settlement");
    set_long(&long_desc());

    sky_add_items();
    camp_add_items();
    add_camp_tells();

    add_item(({"room", "area", "surroundings", "place",
        "landscape", "settlement", "village", "camp"}), long_desc);
        
    add_item(({"huts", "burning huts"}), "Most of the huts to "
        + "the east and south are burning. To the west, most "
        + "of the huts still look sound.\n");
    add_item(({"hut", "burning hut"}), "There is a burning "
        + "hut here. It is still standing, however, so you may "
        + "be able to enter it.\n");
        
    add_prop(ROOM_I_INSIDE, 0);
    
    defence_status = 1;

    add_exit(NCAMP_ROOM + "camp15.c", "north");
    add_exit(NCAMP_ROOM + "camp18.c", "east");
    add_exit(NCAMP_ROOM + "camp13.c", "south");
    add_exit(NCAMP_ROOM + "camp7.c", "southwest");
    add_exit(NCAMP_ROOM + "camp6.c", "west");
    add_exit(NCAMP_ROOM + "hut14.c", "enter", 0, 0, 1);

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
    return "From where you are standing in the northern part of "
        + "the settlement, burning huts can be seen to the east "
        + "and south. The huts to the west still look safe."
        + sky_desc() 
        + " One hut looks particularly in danger of burning to "
        + "the ground, but it may yet be safe to enter.\n";
}
