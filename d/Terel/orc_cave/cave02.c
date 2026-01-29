/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cave02.c
 *
 * A cave room near the entrance.
 */

#include "/d/Terel/include/Terel.h"
inherit ORC_CAVE_DIR + "cave_room";

public int do_listen(string str);

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
    ::init();
    add_action(do_listen,  "listen",  0);
}

/*
 * Function name: do_listen
 * Description:   Handle the listen action
 * Returns:       1/0
 */ 
public int
do_listen(string str)
{
    write("It sounds like a lot of bats are nearby to the east.\n");
    tell_room(ETP, QCTNAME(TP) + " listens to the east.\n", TP);
    return 1;
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long(query_long() +
	     "Everything is very quiet around here.  Faint high "+
	     "pitched sounds can be heard from the east.\n");

    DARK;
    
    add_exit(ORC_CAVE_DIR + "cave03",   "east");
    add_exit(ORC_CAVE_DIR + "entrance", "west");
}
