/*
 *  /d/Emerald/telberin/sewer/level_3/3_w.c
 *
 *  This is one of the rooms in the Telberin Sewers.
 *
 *  Copyright (c) September 2004, by Gorboth
 */
#pragma strict_types
#include "../defs.h"

inherit LEVEL_3_SEWER_CORRIDOR;


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

    add_exit("3_sw_11", "south");
    add_exit(LAIR_DIR + "necro_room", "down");
    set_no_exit_msg( ({ "north" }),
        "Sewer waters have flooded the corridor to the north.\n");
} /* create_sewer_room */

