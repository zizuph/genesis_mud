/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * stem1.c
 *
 * This room is inside a stem. Mortricia 921023
 * Modified by Sorgum 941226
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include "enchanted.h"

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Inside oak stem");
    set_long("You are inside an oak.  There is a hole here.\n");

    INSIDE;

    add_exit(ENCHANT_DIR + "forest11", "out",  0);
    add_exit(ENCHANT_DIR + "stem2",    "up",   0);
    add_exit(ENCHANT_DIR + "ugnd1",    "down", 0);
}
