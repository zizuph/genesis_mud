/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road16.c
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
    set_long("You are on a dirt road leading into town.  It " +
	     "leads east to a cave set into the rock face of the cliff.  " +
	     "To your north, you see many corn and wheat fields, and south " +
	     "there are many sheep, grazing carelessly.\n");

    add_item(({"crops", "corn", "wheat"}), "They are slowly being " +
             "invaded by grass and weeds.\n");
    
    add_item(({"sheep"}), "They munch away continuosly at the grass.\n");

    add_exit(RIBOS_DIR + "intsec2", "west", 0);
    add_exit(RIBOS_DIR + "stair5", "east", 0);
    
    clone_object(RIBOS_DIR + "obj/sign")->move(TO);
}

