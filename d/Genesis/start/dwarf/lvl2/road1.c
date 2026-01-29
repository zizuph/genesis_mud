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
    set_short("Yellow brick road");
    set_long("You are somewhere in the middle of the long yellow brick\n"+
             "road, that was built by skilled elves many hundred years\n"+
             "ago, but unfortunately they never finished it, since evil\n"+
             "orcs invaded their kingdom and forced them to move.\n"+
             "North of here the road continues into a huge forest, and\n"+
             "south it leads back to the dark road.\n");

    add_exit(LVL2+"forest7","north");
    add_exit(LVL2+"road2","south");
}
