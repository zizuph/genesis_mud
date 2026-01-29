/*
 *  /d/Emerald/telberin/sewer/rooms/1_ne_10.c
 *
 *  This is one of the rooms in the Telberin Sewers.
 *
 *  Copyright (c) September 2004, by Gorboth
 */
#pragma strict_types
#include "../defs.h"

inherit LEVEL_1_SEWER_CORRIDOR;


/* prototypes */
public void        create_sewer_passage_room();


/* 
 * Function name:        create_sewer_passage_room
 * Description  :        set up the room from the base file
 */
public void
create_sewer_passage_room()
{
    set_short("a temp sewer room short description");
    set_long("A temp sewer room long description.\n");

    add_exit("1_ne_9", "west");
    add_exit("1_ne_11", "east");
} /* create_sewer_room */

