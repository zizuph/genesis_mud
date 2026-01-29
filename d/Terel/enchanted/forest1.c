/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * forest1.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit ENCHANT_DIR + "forest_room";

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({ENCHANT_DIR + "monster/sprite",
	     ENCHANT_DIR + "monster/sprite"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();

    add_exit(ENCHANT_DIR + "n_edge6","north",0);
    add_exit(ENCHANT_DIR + "forest3","south",0);
    reset_room();
}
