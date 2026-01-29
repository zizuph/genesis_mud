/*
 *  /d/Emerald/telberin/sewer/level_2/2_e.c
 *
 *  This is one of the rooms in the Telberin Sewers.
 *
 *  Copyright (c) September 2004, by Gorboth
 */
#pragma strict_types
#include "../defs.h"

inherit LEVEL_2_SEWER_CORRIDOR;


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

    add_exit("2_se_1", "south");
    add_exit(LEVEL_1_DIR + "1_e", "up");
    set_no_exit_msg( ({ "north" }),
        "The sewer waters have flooded the corridor north of here.\n");
} /* create_sewer_room */

