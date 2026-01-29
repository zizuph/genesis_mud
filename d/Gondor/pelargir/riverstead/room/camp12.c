/*
 *  NCAMP_ROOM + "camp12.c"
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
    set_short("in the southern part of a settlement");
    set_long(&long_desc());

    sky_add_items();
    camp_add_items();
    add_camp_tells();

    add_item(({"room", "area", "surroundings", "place",
        "landscape", "settlement", "village", "camp"}), long_desc);
        
    add_item(({"wall", "walls"}), "The walls of the plain "
        + "looking hut have blood splashed all over them. Whether "
        + "it is orc or human blood cannot be determined.\n");
    add_item(({"blood"}), "There is quite a bit of it splashed "
        + "around here, on the walls of the hut and all over the "
        + "ground.\n");
    add_item(({"hut", "plain hut", "plain looking hut"}),
        "A rather average looking hut, were it not for the "
        + "blood splashed all over it.\n");
    
    add_prop(ROOM_I_INSIDE, 0);
    
    defence_status = 1;

    add_exit(NCAMP_ROOM + "camp13.c", "north");
    add_exit(NCAMP_ROOM + "camp20.c", "east");
    add_exit(NCAMP_ROOM + "camp11.c", "south");
    add_exit(NCAMP_ROOM + "camp7.c", "northwest");
    add_exit(NCAMP_ROOM + "camp9.c", "west");
    add_exit(NCAMP_ROOM + "hut12.c", "enter", 0, 0, 1);

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
    return "There seems to have been some fighting here. You see "
        + "what appears to be blood splashed on the walls of "
        + "the otherwise plain looking hut nearby."
        + sky_desc() 
        + " The mud is especially sticky here. The red stains "
        + "left behind leave little question as to why.\n";
}
