/* -*- Mode: C -*-
 *
 * lib_room
 *
 * A room to manage the library in the trade office
 *
 * Skippern 20(c)01
 */
#include "../defs.h"

inherit DOL_STD + "inside";
inherit "/d/Gondor/common/lib/library_office";

#include <macros.h>
#include <stdproperties.h>

void
create_inside()
{
    set_short("library management device");
    set_long("You are inside a library management device. It is a large " +
	     "enginge with loads of rotating wheels and knobs.\n");

    set_save_path(DOL_BASE + "txt/library/aproval");
    set_library(DOL_TRADE + "houses/q-09");
    set_log_file("DolAmrothBooks");
    set_up_office();

    add_exit(DOL_TRADE + "houses/q-09", "away", 0, 1);
}

void
init()
{
    ::init();
    init_office();
}

/*
 * Function name: add_book_to_library
 * Description:   add a book to the library
 * Arguments:     s - name of the book
 * Returns:       1 if success, 0 else
 * Modified for a library using shelves: add <book> to shelf <shelf>
 */
int
add_book_to_library(string s)
{
    string  book,
        shelf;

    s = capitalize(lower_case(s));
    if (sscanf(s, "%s to shelf %s", book, shelf) < 2)
    {
        NFN("Add which book to which shelf? Try: add <book> to shelf " +
	    "<shelf>.");
        return 0;
    }

    if (member_array(CAP(shelf), lib->query_shelf()) < 0)
    {
      NFN("There is no shelf with the name \""+CAP(shelf)+"\" in the " +
	  "library!");
      return 0;
    }

    if (!sizeof(books[book]))
      return lib_hook_office_not_exist();

    lib->add_book(book,books[book][0],books[book][1],books[book][2]);
    lib->add_shelf_book(shelf, book);
    write("You add the book to " + lib->query_library_name() + ".\n");
    seteuid(getuid(this_object()));

    log_file(log_file, "LIBRARY: " + this_player()->query_name()
	     + " added the book " + book + " (" + books[book][0]
	     + ") to the shelf "+CAP(shelf)+" on "+ctime(time())+".\n");

    books = m_delete(books,book);
    save_object(lsave);
    check_desc();
    return 1;
}

