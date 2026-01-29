/*
 * monk_lib2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room()
{
/*    set_short("the library of the Kaheda order");*/
    set_short("A quiet, empty room");
/*
    set_long("This is the inner room of the Kaheda library. Here you " +
             "may read books written by other monks, and write one " +
             "of your own, if you like.\n" +
             "There is a sign on the wall.\n");

*/
    set_long("The faint smell of old books still lingers in this very " +
             "quiet, small, empty room.\n");

/*
    add_prop(ROOM_M_NO_ATTACK,
             "You can not do that while on Sacred ground.\n");
    add_item("shelves", "The shelves are filled with books.\n");
    add_item("books", "There are many books here.\n");
    add_item("librarian", "The librarian is busy working with the books.\n");
    add_item("sign", "@@sign");
    add_cmd_item("sign", "read", "@@sign");
*/
    add_exit("monk_lib", "west");

    INSIDE;
}
