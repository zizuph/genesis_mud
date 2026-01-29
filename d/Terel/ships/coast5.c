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
    set_short("Up the coastline");
    set_long("The eastern coastline of Terel is covered in sparse trees.  " +
	     "They find it more difficult to grow when its " +
	     "this cold.  To your west, you see that the small icebergs are " +
	     "not only growing in number, but in size too.  Pray that they " +
	     "so not strike the boat.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
