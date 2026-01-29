/*
 * monk_lib.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void reset_room();

object transformer;

void
create_room()
{
/*    set_short("the library of the Kaheda order");*/
    set_short("large book-smelling room");
/*
    set_long("You are in the library of the Kaheda order. Here you may\n" +
             "borrow and read any book you find in the shelves. A librarian\n" +
             "stands in one of the corners, sorting new books and puts them\n" +
             "in the shelves. A small sign is located on the wall in front of\n" +
             "you.\n");
*/
    set_long("This large dusty room smells strongly of old books.\n");

/*  
    add_prop(ROOM_M_NO_ATTACK,
         "You can not do that while on Sacred ground.\n");
    add_item("shelves", "The shelves are filled with books.\n");
    add_item("books", "There are many books here.\n");
    add_item("librarian", "The librarian is busy working with the books.\n");
    add_item("sign", "@@sign");
    add_cmd_item("sign", "read", "@@sign");
*/
    add_exit("monk_board", "west");
    add_exit("monk_lib2", "east");

    INSIDE;
    reset_room();
}

void
reset_room()
{
    if (!objectp(transformer))
    {
        transformer = clone_object(ROKEDIR + "npc/transformer");
        transformer->move(TO);
    }
}
