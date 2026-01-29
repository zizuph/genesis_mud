/*
 *  NCAMP_ROOM + "camp7.c"
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
        
    add_item(({"tower", "watchtower", "watch tower"}), 
        "Built entirely from wood, the large watchtower stands "
        + "several stories high. At the top is a broad platform "
        + "from which the villagers keep watch for trouble.\n");
    add_item(({"platform", "broad platform"}), "At the top "
        + "of the watchtower you see a broad platform. To reach "
        + "it, you will need to enter the tower and climb up.\n");
        
    add_prop(ROOM_I_INSIDE, 0);
    
    defence_status = 1;

    add_exit(NCAMP_ROOM + "camp6.c", "north");
    add_exit(NCAMP_ROOM + "camp14.c", "northeast");
    add_exit(NCAMP_ROOM + "camp13.c", "east");
    add_exit(NCAMP_ROOM + "camp12.c", "southeast");
    add_exit(NCAMP_ROOM + "camp9.c", "south");
    add_exit(NCAMP_ROOM + "camp8.c", "southwest");
    add_exit(NCAMP_ROOM + "camp3.c", "west");
    add_exit(NCAMP_ROOM + "camp4.c", "northwest");
    add_exit(NCAMP_ROOM + "watchtower.c", "enter", 0, 0, 1);

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
    return "This appears to be the center of the settlement. "
        + "As such, it is surrounded by dense clusters of "
        + "wooden huts and the ground is a soggy mess from "
        + "the foot traffic passing to and fro."
        + sky_desc() 
        + " A large watchtower rises high into the air here. "
        + "You could enter it and climb up for a better look "
        + "at your surroundings.\n";
}
