/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * path2.c
 *
 * Vader
 * modified by Sorgum 950707
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
    set_short("A path");
    set_long("It is now cold enough to freeze fire.  " +
	     "Your feet are numb, and your ears feel as if they were " +
	     "forced through a meat grinder.  The path continues to " +
	     "incline further west, where large rock formations block " +
	     "a clear view of the path beyond.\n");

    add_exit(RIBOS_DIR + "path1", "east", 0);
    add_exit(RIBOS_DIR + "path3", "west", 0);
}
