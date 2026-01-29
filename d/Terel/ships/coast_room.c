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
    set_long("You are now travelling the eastern coastline of the continent " +
	     "of Terel.  There is little more than an endless stretch of " +
	     "water, with an occasional small iceberg that hasn't quite " +
	     "melted yet.  The east coast is all forestland, beautiful, but " +
	     "of no particular interest.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
