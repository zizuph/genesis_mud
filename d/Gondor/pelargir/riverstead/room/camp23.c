/*
 *  NCAMP_ROOM + "camp23.c"
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
    set_short("in the southwestern part of a settlement");
    set_long(&long_desc());

    sky_add_items();
    camp_add_items();
    add_camp_tells();

    add_item(({"room", "area", "surroundings", "place",
        "landscape", "settlement", "village", "camp"}), long_desc);
        
    add_item(({"tree", "trees"}), "The trees of the woodland "
        + "to the west grow very close together. It is unlikely "
        + "you could enter them here.\n");
    add_item(({"woods", "woodland", "stand"}), "A dense stand "
        + "of trees grows to the west of the settlement.\n");
        
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(NCAMP_ROOM + "camp8.c", "northeast");
    add_exit(NCAMP_ROOM + "camp24.c", "southwest");
    
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
    return "The path in this part of the settlement appears to be "
        + "leading toward the dense stand of woodland to the southwest."
        + sky_desc() 
        + " The sounds of battle rise from the village.\n";
}
