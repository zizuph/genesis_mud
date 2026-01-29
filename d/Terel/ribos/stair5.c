/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * stair5.c
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
    set_short("An old cave");
    set_long("You are at the bottom of this vast staircase.  " +
	     "To your west, you  see a prospering town with crops " +
	     "growing and sheep grazing.  Now that you look again, " +
	     "you notice that the crops don't look so good.\n");

    add_item(({"stair", "stairs", "staircase"}),
	     "It looks as if it has seen years of use.\n");

   add_exit(RIBOS_DIR + "road16", "west", 0);
   add_exit(RIBOS_DIR + "stair4", "up",   0, 3);
}
