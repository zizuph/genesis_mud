/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * dragon_cave.c
 *
 * This is the starting point for the dragon in Ribos
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

int opened = 0;

/*
 * Function name: query_moving_object_list
 * Description:   return list of moving_objects to clone at each reset.
 */
public string*
query_moving_object_list()
{
    return ({RIBOS_DIR + "monster/evil_thang"});
}

open_the_door()
{
    if (opened == 1)
	return;
   opened = 1;
   (RIBOS_DIR + "road15")->do_open();
   add_exit(RIBOS_DIR + "road15", "north", 0);

}

create_room()
{
   
    set_short("Cave");
    set_long("This damp, dank cave has been the prison of an evil dragon " +
	     "for several days.  The Ribos Knights lured it here and " +
	     "managed to trap it.  But it has now broken its trap, as you " +
	     "can see by the remains of an iron door around an exit to " +
	     "the north.  There are also a pile of rocks blocking a " +
	     "passage to the west.\n");

    INSIDE;
    opened = 0;
    reset_room();
}

