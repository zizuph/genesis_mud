
/*
 * File:     domain_libary
 * Created:  Lilith
 * Purpose:  Contains info also posted on the website
 *           This room is accessed from /d/Avenir/common/domain_office.c
 *
 */
#pragma strict_types

inherit "/std/room";
inherit "/lib/library";

#include <stdproperties.h>

#define BOOKPATH      "/d/Avenir/doc/domain_library/"

void
create_room()
{
    set_short("Library of the Sybarite Embassy");
    set_long("This is library is an embassy of Sybarus. It is a valuable "+
       "source of information to outlanders who are not familiar with "+
       "this land or its ways. The room itself is very bright and of "+
       "indeterminate size. Rows of books are suspended in the air, "+
       "their covers open and ready to read.  There is a large sign "+
       "hanging above the books.\n");

    add_prop(ROOM_I_INSIDE, 1);

   /* There, but not obvious */
    add_exit("/d/Avenir/common/domain_office", "out");

    /* Indicate that we want players to have to "borrow" a book in
     * order to read it.
     */
    set_borrow_required(0);

    /* This is the directory where approved books are saved */
    set_book_directory(BOOKPATH);
    
    /* This is the directory where books that need approval are saved */
    set_book_approval_directory(BOOKPATH +"pending/");

    /* This is the directory where books that have been denied or discarded
     * are saved.
     */
    set_book_removal_directory(BOOKPATH + "removed/");

    /* Add shelves to the library so that books can be classified under
     * different categories.  Note that for each shelf you must add a
     * subdirectory with the same name under the base directory specified
     * with set_book_directory().  For instance, we would have to add
     * two directories, /d/Avenir/union/book/novice/first/ and
     * /d/Avenir/union/book/novice/second/ for the two shelves,
     * "first" and "second", in this library.
     */
    add_book_shelf(({ "sybarus" }));

    create_library();

    /* Add a sign that gives instructions on how to use the library */
    add_item("sign", library_help());
    add_cmd_item("sign","read", library_help());
    add_item(({"bookshelves","bookshelf",}),
        "They are simply rows of books suspended in the air.\n");
    add_item(({"light",}),
        "Light seems to emanate from all around you.\n");

}


void
init()
{
    ::init();

    /* Add the library commands */
    init_library();
}

/*
 * Function name: library_admin_access
 * Description:   Limit library administration abilities to certain
 *                people.
 * Returns:       1 - this_player() has administration powers
 *                0 - this_player() does not have administration powers
 */
public int
library_admin_access()
{
    if(!this_player()->query_wiz_level())
    {
        write("Such authority does not yet lie within you.\n");
        return 0;
    }

    else
        return 1;
}

/*
 * Function name: library_write_access
 * Description:   Limit permission to write books to certain people
 * Returns:       1 - this_player() is allowed to write
 *                0 - this_player() is not allowed to write
 */
public int
library_write_access()
{

    if(!this_player()->query_wiz_level())
    {
        write("Such authority does not yet lie within you.\n");
        return 0;
    }

    else
        return 1;
}

