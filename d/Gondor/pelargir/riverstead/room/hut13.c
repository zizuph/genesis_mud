/*
 *  NCAMP_ROOM + "hut13.c"
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
    set_short("a small hut in the eastern parts of the settlement");
    set_long(&long_desc());

    hut_add_items();

    add_item(({"room", "area", "surroundings", "place",
        "cottage", "house", "hut", "cabin", "building"}), long_desc);
        
    add_item(({"flames", "flame"}), "Flames lick greedily at the "
        + "wood in the walls and ceiling.\n");
    add_item(({"smoke"}), "Smoke is quickly filling the room. It "
        + "is getting difficult to breathe in here.\n");
    add_item(({"spark", "sparks"}), "The burning wood pops and "
        + "crackles, sending bright orange sparks into the air. Every "
        + "now and then one lands on your skin. Ouch!.\n");

    add_prop(ROOM_I_INSIDE, 1);

    defence_status = 1;

    add_exit(NCAMP_ROOM + "camp13.c", "out");

    add_tell("Flames lick the boards of the walls.\n");
    add_tell("Smoke rolls down into the room.\n");
    add_tell("It is getting very hot in here.\n");
    add_tell("You are finding it increasingly difficult to breathe.\n");
    add_tell("Sparks shower down from the ceiling.\n");
    add_tell("A backdraft rushes in from the window.\n");
    add_tell("You smell burnt hair. It could be yours!\n");

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
    return "The most obvious thing about this hut is that it is on "
        + "fire! It is still safe to be in here, but you wonder how "
        + "long that will last.\n";
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

