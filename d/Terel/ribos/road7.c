/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road7.c
 *
 * A road in Ribos
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
    set_short("A smooth dirt road");

    set_long("You are on a dirt road leading to the Castle of Ribos. " +
	     "This is where King Bor-El lives, and it is also rumoured that " +
	     "the great wizard Vader has his chambers somewhere " +
	     "beneath it.  To the southeast, there is the Pub.  " +
	     "It appears to be open and thriving.  Must be the " +
	     "castle guards favorite place!\n");


    add_item(({"pub"}), "It is probably one of the best guarded "      +
             "places in all of Ribos.\n");

    add_item(({"castle"}), "You can see it pretty well from here, " +
             "and you notice that it is\nnot run down, like the rest of " +
             "Ribos.\n");

    add_exit(RIBOS_DIR + "intsec4", "east",      0);
    add_exit(RIBOS_DIR + "road5",   "south",     0);
    add_exit(RIBOS_DIR + "bar",     "southeast", 0);
}

