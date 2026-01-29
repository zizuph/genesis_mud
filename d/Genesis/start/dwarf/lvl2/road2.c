/*
 * Copyright notice, please read.
 *
 * Copyright Chalmers Datorf|rening, 1992
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

#include "../defs.h"

void
create_room()
{
    set_short("yellow brick road");
    set_long("This is the southmost part of the long yellow brick road,\n"+
             "where it joins with the dark road. Around you are high\n"+
             "mountains, and if you walk north, the road will take you\n"+
             "high up on a plateau, south, through a small rift, you\n"+
             "spot the end of the dark road.\n");

    add_exit(LVL2+"road1","north");
    add_exit("/d/Genesis/start/human/wild2/field11","south");
}
