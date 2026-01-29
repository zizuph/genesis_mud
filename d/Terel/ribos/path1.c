/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * path1.c
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
    set_long("The further west you go, the colder it " +
	     "gets.  You are also traveling higher into the mountains " +
	     "too.  Pretty soon, if it keeps getting cooler, you may " +
	     "have to turn around and go back.\n");
   
    add_exit(RIBOS_DIR + "path2",            "west",      0);
    add_exit(RIBOS_DIR +"roads/road_30","east",0,5);
}
