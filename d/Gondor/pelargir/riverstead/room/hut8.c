/*
 *  NCAMP_ROOM + "hut8.c"
 *
 *  A hut. Only newbies and wizards should ever see this place.
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

static object *Woman = allocate(2);
static object *Orc = allocate(2);

public void
create_gondor()
{
    set_short("a small hut in the southeastern corner of the settlement");
    set_long(&long_desc());

    hut_add_items();

    add_item(({"room", "area", "surroundings", "place",
        "cottage", "house", "hut", "cabin", "building"}), long_desc);

    add_prop(ROOM_I_INSIDE, 1);

    defence_status = 1;

    add_exit(NCAMP_ROOM + "camp8.c", "out");

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
    return "You have entered a small hut, the dwelling in which a family "
        + "of settlers have made their home. There is not much to see, for "
        + "this family is too poor to afford many conveniences. A bed "
        + "rests in one corner of the one-room building, and a wooden "
        + "table occupies the center of the floor. The only way out appears "
        + "to be in the direction you came.\n";
}
