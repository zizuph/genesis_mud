/* This comment tells emacs to use c++-mode -*- C++ -*- */

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
    set_short("In the river");
    set_long("In the river just north of a tall fence. There are trees on " +
	     "both sides of the river.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
