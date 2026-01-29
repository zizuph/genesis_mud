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
    set_long("In the river under a wooden bridge.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
