/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ugnd1.c
 *
 * This room is underground. Mortricia 921023
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
    set_short("Underground path");
    set_long("You are standing on an underground path. The air is " +
	     "not exactly refreshing. Some lanterns on the walls " +
	     "provide enough of guidelight. There is a hole above you.\n");

    add_item(({"lanterns"}) ,"They look as if they were maintained " +
			     "regularily.\n");

    INSIDE;

    add_exit(ENCHANT_DIR + "stem1", "up", 0);
    add_exit(ENCHANT_DIR + "ugnd2", "west", 0);
}

