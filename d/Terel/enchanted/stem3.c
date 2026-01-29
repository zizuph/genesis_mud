/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * stem3.c
 *
 * This room is inside a stem. Mortricia 921023
 * Modified by Sorgum 941226
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include "enchanted.h"

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({ENCHANT_DIR + "monster/goblin"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Inside oak stem");
    set_long("You are inside an oak. Through a small hole above you " +
	     "some light falls on you.\n");

    INSIDE;
    add_exit(ENCHANT_DIR + "stem2", "down", 0);

    reset_room();
}
