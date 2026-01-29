/*
 *  NCAMP_ROOM + "hut12.c"
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
    set_short("a small hut in the southern parts of the settlement");
    set_long(&long_desc());

    hut_add_items();

    add_item(({"room", "area", "surroundings", "place",
        "cottage", "house", "hut", "cabin", "building"}), long_desc);
        
    add_item(({"sack", "sacks", "burlap sack", "burlap sacks", "bed",
        "beds"}), "The burlap sacks are large and stuffed with something "
        + "soft, so you surmise they must function as beds for the "
        + "poor family who lives here. They are spattered with a "
        + "prodigious amount of blood.\n");
    add_item(({"blood"}), "Blood is spattered all over the cabin, "
        + "but whether it is of orc or human nature is difficult to "
        + "ascertain.\n");

    add_prop(ROOM_I_INSIDE, 1);

    defence_status = 1;

    add_exit(NCAMP_ROOM + "camp12.c", "out");

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
    return "You are inside a plain looking hut. The family who lives here "
        + "is obviously poor, as indicated by the lack of decent furniture. "
        + "Several burlap sacks apparently serve as beds. The sacks, like "
        + "most of the walls and the floor, are spattered with blood.\n";
}
