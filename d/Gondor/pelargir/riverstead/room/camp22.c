/*
 *  NCAMP_ROOM + "camp22.c"
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
    set_short("in the southeastern part of a settlement");
    set_long(&long_desc());

    sky_add_items();
    camp_add_items();
    east_camp_add_items();
    add_east_camp_tells();

    add_item(({"room", "area", "surroundings", "place",
        "landscape", "settlement", "village", "camp"}), long_desc);
        
    add_prop(ROOM_I_INSIDE, 0);
    
    defence_status = 0;

    add_exit(NCAMP_ROOM + "camp11.c", "northwest");
    add_exit(NCAMP_ROOM + "dock7.c", "east");

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
    return "This is the furthest southeastern extent of the small "
        + "village - or at least what remains of it. Every hut "
        + "and cottage that once stood here is now a smoking pile "
        + "of debris."
        + sky_desc() 
        + " The part of the settlement that remains standing is to "
        + "the northwest, and there is a strange looking dock to your "
        + "east.\n";
}
