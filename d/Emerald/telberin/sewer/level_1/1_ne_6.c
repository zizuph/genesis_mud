/*
 *  /d/Emerald/telberin/sewer/rooms/1_ne_6.c
 *
 *  This is one of the rooms in the Telberin Sewers.
 *
 *  Copyright (c) September 2004, by Gorboth
 */
#pragma strict_types
#include "../defs.h"

inherit SEWER_PASSAGE_ROOM;


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

    add_exit("1_ne_5", "north");
    add_exit("1_ne_7", "east");
} /* create_sewer_room */

