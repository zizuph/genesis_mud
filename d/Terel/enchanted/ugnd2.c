/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ugnd2.c
 *
 * This room is underground. Mortricia 921023
 * Modified by Sorgum 941226
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include "enchanted.h"


/*
 * Function name: query_moving_object_list
 * Description:   return list of moving objects to clone at each reset.
 */
public string*
query_moving_object_list()
{
    return ({ENCHANT_DIR + "monster/badger"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{

    ::create_room();
    set_short("Underground path");
    set_long("You are standing on an underground path. The air is " +
	     "not exactly refreshing. Some lanterns on the walls " +
	     "provide enough of guidelight.\n");

    add_item(({"lanterns"}) ,"They look as if they were maintained " +
			     "regularily.\n");

    INSIDE;
       
    add_exit(ENCHANT_DIR + "ugnd1", "east",  0);
    add_exit(ENCHANT_DIR + "ugnd3", "south", 0);

    reset_room();
}
