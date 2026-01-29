/*
 *  IGARD_DEEP_PRISON + "guard_station.c"
 *
 *  Stairwell down into the prisons below Isengard.
 *
 *  Last modified by Alto, 10 November 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../../igard_defs.h"

inherit IGARD_LIB + "igard_funcs.c";
inherit IGARD_LIB + "prison_funcs.c";

public void        create_gondor();
public int         check_monster();

static object *Uruk   = allocate(4);

string
long_desc()
{
    return "You are standing in a large landing carved from the black "
    + "rock beneath the plain of Isengard. On the east side of the room, "
    + "a great wooden door lies smashed and broken on the floor. There "
    + "is a great deal of blood splashed about the area, suggesting that "
    + "a battle recently took place here. A narrow stairwell leads upward "
    + "into shadow.\n";
}


public void
create_gondor()
{
    set_short("A landing at the foot of the stairwell");
    set_long(long_desc());

    stairwell_add_items();
    prison_add_items();

    add_item(({"room", "area", "surroundings", "place", "landing"}), 
        long_desc());

    add_item(({"door", "wooden door", "great wooden door", 
        "broken door"}), "Scattered across the floor are the remains "
        + "of what once must have been a very solid door. From the "
        + "blood pooled about it, there must have been a battle fought "
        + "at the time of its breaking.\n");
    add_item(({"blood"}), "Blood seems to be everywhere in this "
        + "room. No evidence remains, however, of the many bodies that "
        + "must have been slain here.\n");
    add_item(({"stairwell"}), "A narrow stairwell vaults up into the "
        + "shadows above.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(IGARD_DEEP_PRISON + "entry_stair7",        "up");
    add_exit(IGARD_DEEP_PRISON + "lev1_hall1",  "east", check_monster, 2, 0);

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

    write("Despite the foul scent coming from the east, you venture into "
        + "the prisons of Isengard.\n");
    return 0;
}

