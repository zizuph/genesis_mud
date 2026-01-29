/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * sea_room.c
 *
 * A generic sea room.
 */

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
    set_short("Out on the sea");
    set_long("You are now out on the sea. You don't see any trace of land.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
