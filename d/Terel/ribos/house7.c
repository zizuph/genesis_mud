/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * house5.c
 *
 * An old house in Ribos
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

/*
 * Function name: query_moving_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_moving_object_list()
{
    return ({RIBOS_DIR + "monster/old_man"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("An old house");
    set_long("This old house has been home to several " +
	     "generations.  All that is left now is an old man, " +
	     "determined to stand by and not let anything scare him off.  " +
	     "There are paintings hanging all around this room.  One, " +
	     "of a young boy, catches your attention.\n");

    add_item(({"painting"}), "This is a painting of a young boy.  It " +
             "depicts him in some sort of\nbirthday getup.  Below it, " +
             "you see the name of the painter, and the\ndate it was " +
             "painted.  It says 'Geordio Palanen, November 21, 1007'.\n");

    add_exit(RIBOS_DIR + "road10", "east", 0);
    reset_room();
}
