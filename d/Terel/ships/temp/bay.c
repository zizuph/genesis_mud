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
    set_short("Out in the bay");
    set_long("You are now out in the bay. To the west you can " +
             "see wooden piers, and past those, the village of "+
             "Dabaay. To the eastm the bay opens out into a "+
             "deep blue sea.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
