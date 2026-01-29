/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * room19n.c
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
    return ({LOD_DIR + "armour/small_chainmail"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    set_short("a armoury in the legion of darkness quarters");
    set_long("This is a armoury where the legion of darkness weapons " +
	     "and armours are kept when they dont use them, but it seems " +
	     "to be quite empty for the moment. \n");

    add_exit(LOD_DIR + "corr19", "south", 0);
    reset_room();
}
