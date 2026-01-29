/*
 *  IGARD_DEEP_WARG + "warg_landing.c"
 *
 *  Landing at base of stairs in warg dens.
 *
 *  Last modified by Alto, 24 November 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../../igard_defs.h"

inherit IGARD_LIB + "igard_funcs.c";
inherit IGARD_LIB + "warg_funcs.c";

public void        create_gondor();
public int         check_monster();

static object *Uruk   = allocate(4);

string
long_desc()
{
    return "You are standing in a large landing carved from the black "
    + "rock beneath the plain of Isengard. Small hatches open in the walls "
    + "to the north, southeast and southwest. The place stinks like a wet "
    + "dog, and the source of the stench appears to be somewhere behind "
    + "the hatches. A narrow stairwell leads upward into shadow.\n";
}


public void
create_gondor()
{
    set_short("A landing at the foot of the stairwell");
    set_long(long_desc());

    stairwell_add_items();
    underground_add_items();

    add_item(({"room", "area", "surroundings", "place", "landing"}), 
        long_desc());

    add_item(({"hatch", "hatches"}), "The hatches are made of wood and "
        + "are so short that you would need to stoop over almost double "
        + "to pass through. Something stinks like wet dog in the darkness "
        + "beyond them.\n");
    add_item(({"stairwell"}), "A narrow stairwell vaults up into the "
        + "shadows above.\n");
    add_item(({"north wall", "southeast wall", "southwest wall"}), "Beyond "
        + "the fact that it has a small wooden hatch built into it, the "
        + "wall is the same as all the other walls in the room.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(IGARD_DEEP_WARG   + "entry_stair7",        "up");
    add_exit(IGARD_DEEP_WARG   + "pup_den1",  "north", check_monster, 2, 0);
    add_exit(IGARD_DEEP_WARG   + "warg_den1", "southwest", check_monster, 2, 0);
    add_exit(IGARD_DEEP_WARG   + "wolf_den1", "southeast", check_monster, 2, 0);

    reset_room();
}


public void
reset_room()
{
    clone_npcs(Uruk,  IGARD_NPC + "igard_uruk",  -1.0);
}


public int
check_monster()
{
    if (TP->id("_igard_monster"))
    {
    return 1;
    }

    if (TP->query_attack() != 0)
    {
    TP->catch_tell("You start to run that direction, but quickly realise "
        + "that doing so would invite a quick death from behind.\n");
    return 1;
    }

    write("Despite the smells of urine, feces and wet dog, you decide "
        + "to venture through the hatch and into the darkness beyond.\n");
    return 0;
}

