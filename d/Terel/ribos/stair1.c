/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * stair1.c
 *
 * Staircase to Ribos
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("An ancient Staircase");
    set_long("You are on an ancient staircase, carved carefully " +
	     "into this shaft eons ago.\n");

    add_item(({"stair", "stairs", "staircase"}), "It looks like " +
             "it has seen a great deal of use over the years\n");

    add_exit(RIBOS_DIR + "cave_entrance", "up",   0, 3);
    add_exit(RIBOS_DIR + "stair2",        "down", 0);
}
