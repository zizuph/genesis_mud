/*
 * cadu_l.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"
#include <stdproperties.h>

inherit ROKEDIR + "lib/library";

string
read_sign()
{
    return "You must return any previously borrowed books before\n"+
        "you are allowed to borrow any new book, and you are not\n"+
        "allowed to leave the library without returning all books.\n"+
        "\nThe following commands are used:\n"+
        "borrow <book> - borrow a book\n"+
        "return book   - return a book\n"+
        "list          - list all books currently in the library\n\n";
/*
        "write book    - write a book and submit it to the library.\n"+
        "                all written books has to be accepted by\n"+
        "                Gresolle, before they appear in the library\n"+
        "                so it might take a few days before you see\n"+
        "                them after they are written.\n";
*/
}

void
create_library()
{
    set_short("library in Cadu");
    set_long("You are standing in the famous Cadu library. "+
             "All around you are high, very impressive, shelves "+
             "filled with most of the knowledge of the world. "+
             "The librarian sits behind his desk, studying you "+
             "very carefully. Above him is a small sign.\n");

    add_item("librarian", "He looks very nervous.\n");
    add_item("desk", "The desk is used by the librarian to sort returned books.\n");
    add_item("sign",
             "The sign states the procedures for borrowing books:\n\n" +
             read_sign());
    add_cmd_item("sign","read",
                 "The sign states the procedures for borrowing books:\n\n" +
                 read_sign());
  
    add_prop(OBJ_S_WIZINFO,
             "You are standing in a library using the library.c file by Gresolle.\n"+
             "It is possible to add books by doing\n"+
             "Call here add_book <name>%%<descr>%%<path>%%<type>\n"+
             "for more info please check " + ROKEDIR + "lib/library.c\n"+
             "it is also possible to remove books with\n"+
             "Call here remove_book <name>. Please don't add anything stupid\n"+
             "or offending, and don't remove anything you havn't put there\n"+
             "yourself.\n");

    set_save_path(NYREESEDIR + "libsave");
    set_lib_name("the Library of Cadu");
    lib_exit("cadu_q3", "north");

    //set_write_dir(NYREESEDIR + "books");
    //set_librarian_room("/d/Roke/gresolle/workroom");
}
