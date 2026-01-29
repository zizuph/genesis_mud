/*
 *  The room of the library in the Houses of the Dunedain
 *  where the Lords and the Ladies of the Houses can administer
 *  the library.
 *
 *  Olorin, 20-nov-94
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/dunedain/rooms/dun_room";
inherit "/d/Gondor/common/lib/library_office";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

// Prototypes
string  do_read();

// Global variables
static  string  open_lib = (DUNEDAIN_DIR + "rooms/lib_public");

public void
create_gondor()
{
    set_short("In the Library of the House of the Dunedain");
    set_long(BSN(
        "In this room of the library in the House of the Dunedain "
      + "the Lords and the Ladies of the Houses can review works "
      + "that have been submitted for inclusion into the library. "
      + "On one wall is a plaque with instructions how to do this."));

    add_exit(DUNEDAIN_DIR + "rooms/lib_houses", "south", 0, 0);

    ceiling(1);
    walls(1);
    floor(1);

    add_item(({"plaque", "instructions", }), do_read());
    add_cmd_item(({"plaque", "instructions", }), "read", do_read());

    add_prop(ROOM_I_INSIDE, 1);

    set_save_path(DUNEDAIN_DIR + "books/submissions");
    set_library(DUNEDAIN_DIR + "rooms/lib_houses");
    set_log_file("dunedain");
    set_up_office();
}

void
init()
{
    ::init();
    init_office();
}

string
do_read()
{
    return
        "\n\tThe available commands are:\n\n"
      + "\tlist [books]\t- list the submissions,\n"
      + "\tread <title>\t- read a submitted book,\n"
      + "\treject <title>\t- reject a submitted book,\n"
      + "\tadd <title> to <private|public> library\n"
      + "                \t - add a submission to the library.\n\n";
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
            which;

    s = capitalize(lower_case(s));
    NFN("Add which book to which part of the library?\n"
      + "Try: add <book> to <public|private> library.");
    if (sscanf(s, "%s to %s library", book, which) < 2)
        return 0;

    if ((which != "public") && (which != "private"))
        return 0;

    if (!sizeof(books[book]))
        return lib_hook_office_not_exist();
  
    FIX_EUID

    if (which == "public")
        open_lib->add_book(book,books[book][0],books[book][1],books[book][2]);
    else
        lib->add_book(book,books[book][0],books[book][1],books[book][2]);
    write("You add the book to the "+which+" part of the "
      + lib->query_library_name() + ".\n");

    log_file(log_file, "LIBRARY: " + TP->query_name()
      + " added the book " + book + " (" + books[book][0]
      + ") to the "+which+" library on "+ctime(time())+".\n");

    books = m_delete(books,book);
    save_object(lsave);
    check_desc();
    return 1;
}
