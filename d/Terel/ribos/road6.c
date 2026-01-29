/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road6.c
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

    set_long("You are on a dirt road leading to the Castle of " +
	     "Ribos.  This is where King Bor-El lives, and it is also " +
	     "rumoured that the great wizard Vader has his chambers " +
	     "somewhere beneath it.  To your east, you can see many " +
	     "small fields where food is  grown for the citizens.  " +
	     "There are also farmhouses, but they are unreachable " +
	     "from here.  There is an abandoned house here, and it " +
	     "has been left unlocked.\n");


    add_item(({"fields"}), "Small patches of wheat and corn spread " +
            "out across the land,\nall in dire need of harvesting.  " +
            "You wonder where the farmers might be....\n");

    add_item(({"farm", "farms", "farmhouse", "farmhouses"}), 
	     "These houses are slowly being reclaimed by the weeds and tall " +
	     "grass.\n");

    add_item(({"house"}), "It looks like it was abandoned in a hurry.\n");

    add_item(({"castle"}), "You can barely see details from here.\n");

    add_exit(RIBOS_DIR + "road8",   "north", 0);
    add_exit(RIBOS_DIR + "intsec2", "south", 0);
    add_exit(RIBOS_DIR + "house6",   "west", 0);

}

