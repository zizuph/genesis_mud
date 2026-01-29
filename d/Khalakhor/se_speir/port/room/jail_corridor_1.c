/*
 * jail_corridor_1.c
 *
 * Corridor leading to the prison cells of Port MacDunn.
 *
 * Khail - March 30/97
 */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "room.h"
#include "/d/Khalakhor/sys/defs.h"

inherit "/d/Khalakhor/std/room";

object *guards,
       captain;

public int *
query_local_coords()
{
    return ({18,2});
}

public int *
query_global_coords()
{
    return VILLAGE_COORDS;
}

public int
block_north()
{
    if (TP->query_wiz_level())
        return 0;

    if (present("guard", TO))
    {
        write("A guard prevents you from going that way.\n");
        return 1;
    }
    return 0;
}

/*
 * Function name: reset_room
 * Description  : Resets the room, ensures guards
 *                are present.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_room()
{
    int i;

    if (!guards)
        guards = allocate(2);

    for (i = 0; i < sizeof(guards); i++)
    {
        if (!objectp(guards[i]))
        {
            guards[i] = clone_object(NPC + "guard");
            guards[i]->set_team_follower();
            guards[i]->set_team_name("garrison_team");
            guards[i]->set_autoassist();
            guards[i]->arm_me();
            guards[i]->move(TO);
        }
    }

    if (!captain)
    {
        captain = clone_object(NPC + "broghe");
        captain->set_team_leader();
        captain->set_team_name("jail_captains_team");
        captain->set_autoassist();
        captain->arm_me();
        captain->move(TO);
    }
}
   
/*
 * Function name: create_khalakhor_room
 * Description  : Turns this object into a room.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_khalakhor_room()
{
    set_short("prison corridor of Port Macdunn");
    set_long("   You are in a corridor leading to the prison " +
        "cells of Port Macdunn, to the east. It also appears " +
        "to be some sort of office for the captain of the " +
        "guard, as evident by the crude desk standing " +
        "against one wall. The smell here isn't the best, " +
        "despite a few small windows high in the walls to " +
        "let light and air in, and you suspect the cells " +
        "are filled mostly with drunks who got a bit too " +
        "rowdy.\n");

    add_item(({"desk"}),
        "The desk is pretty much just a number of old planks " +
        "fastened atop a couple crates. Evidently the captain " +
        "of the guard has little concern for appearance, or " +
        "the Lord of the village is a bit tight-fisted with " +
        "his purse.\n");
    add_item(({"window", "windows"}),
        "The windows are fairly small, just a bit larger " +
        "than a man's head. However, they've been covered " +
        "with bars, just in case they have a particularly " +
        "slippery prisoner.\n");
    add_item(({"floor", "ground"}),
        "The floor of the room is simply hard-packed " +
        "earth.\n");
    add_item(({"walls", "wall"}),
        "The walls of the room are made from various sized " +
        "pieces of hard grey stone, carefully placed together " +
        "and packed with clay.\n");
    add_item(({"roof", "ceiling"}),
        "The ceiling is constructed a bit more sturdily than " +
        "most buildings in the village, and seems to be " +
        "made from several layers of wooden planks atop " +
        "heavy rafters.\n");
    add_item(({"rafters"}),
        "The thatch of the roof is supported by a handful of " +
        "thick wooden rafters.\n");

    INSIDE;

    add_exit(ROOM + "jail_storage", "north", VBFC_ME("block_north"));
    add_exit(ROOM + "jail_corridor_2", "east");
    add_exit(ROOM + "jail", "west");

    reset_room();
}
