/*
 *  /d/Emerald/telberin/sewer/rooms/1_e.c
 *
 *  This is one of the rooms in the Telberin Sewers.
 *
 *  Copyright (c) September 2004, by Gorboth
 */
#pragma strict_types
#include "../defs.h"

inherit LEVEL_1_SEWER_CORRIDOR;
inherit "/d/Emerald/telberin/sewer/lib/chain_code";


/* prototypes */
public void        create_sewer_passage_room();


/* 
 * Function name:        create_sewer_passage_room
    add_exit(LEVEL_2_DIR + "2_e", "down");
 */
public void
create_sewer_passage_room()
{
    set_short("a temp sewer room short description");
    set_long("A temp sewer room long description.\n");

    add_exit("1_ne_11", "north");

    add_exit("/d/Emerald/telberin/sewer/level_2/2_e", "down");
} /* create_sewer_room */


public void
init()
{
    ::init();

    add_chain_actions();
}
