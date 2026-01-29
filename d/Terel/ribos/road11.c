/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road11.c
 *
 * A road in Ribos
 *
 * Vader
 * Recoded by Sorgum 950602
 *
 *  Modified: 3 May 2003, by Bleys
 *      - fixed a typo
 *
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
    set_long("You are on a dirt road next to the bank.  " +
	     "It too looks deserted.  There are sheep grazing in the " +
	     "fields to the east.\n");

   add_item(({"fields"}), "Large patches of grass are what feed the " +
            "sheep that are grazing here.\n");

   add_item(({"bank"}), "Nobody has deposited money there lately...\n");

   add_exit(RIBOS_DIR + "road10", "north",     0);
   add_exit(RIBOS_DIR + "road14", "west",      0);
   add_exit(RIBOS_DIR + "bank",   "northwest", 0);
}

