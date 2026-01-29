#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/room";
inherit "/d/Gondor/common/lib/library_office";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

string exa_plaque();

public void
create_room()
{
    set_short("in the office of the library of the Rangers");
    set_long(BSN("This dusty little chamber off the Library of the Rangers, "
      + "is where the librarians approve or deny new books that have been "
      + "submitted to the library. A bronze plaque on one wall has some "
      + "helpful words enscribed in it. A narrow doorway leads back west "
      + "into the main hall of the library."));
    add_exit(RANGER_DIR + "north/nrlibrary", "west", 0);

    add_prop(ROOM_I_INSIDE, 1);
    set_save_path(RANGER_DIR + "north/books/waiting");
    set_library(RANGER_DIR + "north/nrlibrary");
    // We have to set the library before we define these items:
    add_item(({"plaque", "bronze plaque", }), exa_plaque());
    add_cmd_item(({"plaque", "bronze plaque", }), "read", exa_plaque());

    set_log_file("guild");
    set_up_office();
}

public void 
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
        NFN("Add which book to which shelf? Try: add <book> to shelf <shelf>.");
        return 0;
    }

    if (member_array(CAP(shelf), lib->query_shelf()) < 0)
    {
        NFN("There is no shelf with the name \""+CAP(shelf)+"\" in the library!");
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

string
exa_plaque()
{
    string libname = CAP(lib->query_library_name());
    return
        "\n\t" + libname + "\n"
      + "\n\tThe following commands are available:\n\n"
      + "\tlist           - list the submitted titles,\n"
      + "\tread <title>   - read a book without borrowing it,\n"
      + "\treject <title> - reject a submission,\n"
      + "\tadd <title> to shelf <shelf> -\n"
      + "\t                 add a book to a shelf of the library.\n"
      + "\n\tTo remove old titles, go to the library.\n\n";
}
