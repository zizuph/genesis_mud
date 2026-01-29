/*
 *  NCAMP_ROOM + "hut4.c"
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
    set_short("a small hut in the northwest corner of the settlement");
    set_long(&long_desc());

    hut_add_items();

    add_item(({"room", "area", "surroundings", "place",
        "cottage", "house", "hut", "cabin", "building"}), long_desc);

    add_item(({"table"}), "A large table made of oak. It is clean of "
        + "both food and implements.\n");
    add_item(({"cot", "cots"}), "There are three cots arranged in "
        + "various positions relative to the large stove.\n");
    add_item(({"first cot"}), "This is the largest of the three cots, "
        + "and is probably the resting place of the parents.\n");
    add_item(({"second cot"}), "A small child-sized cot.\n");
    add_item(({"third cot"}), "A small child-sized cot.\n");
    add_item(({"stove", "large stove"}), "A large wood-burning stove. "
        + "The residents of the hut use it for cooking, as well as "
        + "heating the cabin on brisk days.\n");

    add_prop(ROOM_I_INSIDE, 1);

    defence_status = 1;

    add_exit(NCAMP_ROOM + "camp4.c", "out");

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
    return "Like most of the huts in the settlement, this one has only "
        + "a single room. A table stands near the middle of the room, "
        + "no doubt used for working in addition to eating. Several "
        + "small cots rest near a large stove in the corner.\n";
}
