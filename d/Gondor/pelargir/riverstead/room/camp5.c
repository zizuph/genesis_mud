/*
 *  NCAMP_ROOM + "camp5.c"
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
                
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(NCAMP_ROOM + "camp15.c", "east");
    add_exit(NCAMP_ROOM + "camp6.c", "south");
    add_exit(NCAMP_ROOM + "camp4.c", "southwest");
    add_exit(NCAMP_ROOM + "hut5.c", "enter", 0, 0, 1);
    
    defence_status = 1;

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
    return "You have reached the northern boundary of the small "
        + "farming settlement. Almost all of the huts lie to the "
        + "south, but one stands nearby with its door thrown "
        + "open."
        + sky_desc() 
        + " The sounds of battle can be heard from the southeast. "
        + "There is also a considerable amount of smoke drifting "
        + "into the area from within the settlement.\n";
}
