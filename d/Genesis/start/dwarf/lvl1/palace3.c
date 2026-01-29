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

object king;

void reset_room();

void
create_room()
{
    set_short("Throne room");
    set_long("You have entered the throneroom of the palace.\n"+
             "The walls are covered with huge paintings from\n"+
             "various battlefields, and at the eastern wall is\n"+
             "the huge throne of the king. The floor below you\n"+
             "is made of polished black marble, that reflects\n"+
             "the light almost like a mirror, making the room\n"+
             "look larger and even more breathtaking.\n");

    add_item("paintings", "They depict soldiers of dwarven "+
             "heritage battling orcs.\n");
    add_item("floor","You can see the image of yourself reflected by the marble.\n");

    add_item("marble", "It is very shiny.\n");
    add_item("throne","The throne is made of polished gold, that has been\n"+
             "decorated with jewels. It is an unusually large item, for the\n"+
             "dwarves anyway, and it seems almost impossible that the king\n"+
             "would be able to get up there without help.\n");

    /* here we suddenly get a nice quest!!! Help the king to get up on the
       throne! */

    seteuid(getuid(TO));

    add_exit(LVL1+"palace2","west");

    reset_room();
}

void
reset_room()
{
    if(king)
        return;

    king = clone_object(D_MON+"king");
    king->arm_me();
    king->move(TO);

    tell_room(TO,"The king steps out of the shades, screaming for his coffee.\n");
}
