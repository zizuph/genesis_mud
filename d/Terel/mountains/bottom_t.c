/* -*- C++ -*- */
/*
 * Lucius, Jan 2018: ROOM_M_NO_TELEPORT_TO added.
 */
/*
 * bottom_t
 *
 * Goldberry 05102002
 */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({"/d/Terel/last/npc/assassin"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    set_short ("A dry cave");
    set_long ("You are standing in a small, but comfortable cave. " +
      "A small cot sits in one corner and a lamp hangs from " +
      "the ceiling. The eastern wall, through which you " +
      "entered this cave, appears to shimmer slightly.\n");

    add_item("cot","The cots looks as if it has been recently slept in.\n");

    add_item("lamp","The lamp provides the only light in this room.\n");

    add_item(({"wall","east wall","eastern wall"}),
      "The east wall looks like rock, but seems to shimmer.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_HIDE, 5);
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);

    add_exit("bottom2","east",0,1,1);

    reset_room();
}
