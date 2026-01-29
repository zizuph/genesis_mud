/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road13.c
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
    set_long("You are travelling a dirt road.  This " +
	     "road leads north and east.  There is a Post Office to the " +
	     "northeast, but It looks like it hasn't been used in a while.  " +
	     "There is a sign hanging crookedly by one nail over the door " +
	     "to the Post Office.\n" +
	     "A small sign was hastily constructed on the grass to your " +
	     "west reading 'Coming soon.......Ralas Magic shop!'\n");

   add_item(({"post office", "office"}), "You won't be sending any " +
            "mail from THIS Post Office...\n");

   add_exit(RIBOS_DIR + "road9",    "north",     0);
   add_exit(RIBOS_DIR + "road13",   "east",      0);
   add_exit(RIBOS_DIR + "p_office", "northeast", 0);
}

