/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * room19s.c
 *
 * an armoury for the legion Redhawk 921027
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "corridor";

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({LOD_DIR + "weapon/short_sword"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("a armoury in the legion of darkness quarters");
    set_long("This is a armoury where the legion of darkness weapons " +
	     "and armours are kept when they don't use them, but it seems " +
	     "to be quite empty for the moment. \n");

    add_exit(LOD_DIR + "corr19", "north", 0);
    reset_room();
}
