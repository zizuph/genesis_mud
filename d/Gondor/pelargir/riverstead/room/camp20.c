/*
 *  NCAMP_ROOM + "camp20.c"
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
    set_short("in the eastern part of a settlement");
    set_long(&long_desc());

    sky_add_items();
    camp_add_items();
    east_camp_add_items();
    add_east_camp_tells();
        
    add_prop(ROOM_I_INSIDE, 0);

    add_item(({"room", "area", "surroundings", "place",
        "landscape", "settlement", "village", "camp"}), long_desc);
    
    add_item(({"ruin", "ruins"}), "All that remains of the "
        + "huts in this part of the settlement are smoking "
        + "piles of debris.\n");
    
    defence_status = 0;

    add_exit(NCAMP_ROOM + "camp12.c", "west");
    add_exit(NCAMP_ROOM + "dock5.c", "east");

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
    return "Here in the southeastern part of the settlement "
        + "there is little to see beyond the smoking ruins "
        + "of huts that once stood along the western bank "
        + "of the river Anduin."
        + sky_desc() 
        + " You can enter the remaining parts of the settlement "
        + "to the west, or step out onto a dock on the Anduin "
        + "to the east.\n";
}
