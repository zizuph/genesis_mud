/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * stair.c
 *
 * Vader
 * Recoded by Sorgum 950708
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit STDROOM;

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    
    set_short("a dark spiral staircase");
    set_long("The darkness has settled around this staircase.  " +
	     "Torches on the wall above you light the path, but " +
	     "not very well.  The walls are dark and wet.\n");
 
    INSIDE;
 
    add_exit(CASTLE_DIR + "treas",    "up",   0);
    add_exit(CASTLE_DIR + "storage7", "down", 0);
}
