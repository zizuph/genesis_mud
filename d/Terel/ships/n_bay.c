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
    set_short("In the Northern port of Terel");
    set_long("This is the Northern port of Terel.  There is a small village " +
	     "on the land to the east, whose buildings are either " +
	     "constructed of snow and ice or covered by it.  The coastline " +
	     "continues northward, but the icebergs only grow more numerous " +
	     "and thus makes sea travel dangerous.  The coastline continues " +
	     "southward as well.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
