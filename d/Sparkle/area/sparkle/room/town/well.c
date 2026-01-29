/*
 * well.c
 *
 * Copyright notice, please read.
 *
 * Copyright Chalmers Datorf|rening, 1993
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <ss_types.h>

#include "defs.h"

void
create_room()
{
    set_short("Well");
    set_long("The walls of the well are made out of roughly hewn stones, sloppy work that would make any dwarf snort with contempt. They seem to be able to provide a good hold for climbing, if they didn't look so slippery...\n" +
             "\nFar up, ah well.. perhaps three meters up, you can see a circle of light.\n");
    add_prop(ROOM_I_INSIDE, 1);
}

int
climb_up(string arg)
{
    switch (arg)
    {
    case "up":
        break;

    case "down":
        write("You're already threading water as it is... do you think you can breath the stuff as well?\n");
        break;

    default:
        NF("Exactly where do you want to climb?\n");
        return 0;
        break;
    }

    if (TP->query_skill(SS_CLIMB) > random(30))
        TP->move_living("climbs up the well", S_LOCAL_ROOM_DIR + "square");
    else
        write("You don't seem to be able to get a good hold. You slide back as soon as you put your weight on.\n");
    return 1;
}

void
init()
{
    ::init();

    add_action(climb_up, "climb");
}

