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
    set_short("The river mouth");
    set_long("This where the river meets the bay. You see roads " +
	     "on the eastern and western river banks.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
