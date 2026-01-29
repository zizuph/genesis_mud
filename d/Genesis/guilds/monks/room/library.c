/*
 * File:     library
 * Created:  Cirion
 * Purpose:  library for the Oranea Monks
 * Modification Log:
 *
 */
#pragma strict_types

#include "defs.h"
#include <math.h>
inherit ROOMBASE;
inherit "/lib/library";

// global vars
object table;
object aliya;

// function prototypes
void populate ();

/*
 * Function name: library_exit_block
 * Description:   Check to see if the player is carrying a library
 *                book.  This is meant to be used as a block function
 *                for exits from the library so that books cannot be
 *                removed.
 * Returns:       1/0 - book carried/not carried
 */
public int
library_exit_block()
{
    /* See if the player is carrying a book */
    if (::library_exit_block())
    {
        /* A book was found.  Give a warning and return 1 to block the exit */
        write("You cannot leave with a library book!\n");
        return 1;
    }

    /* No book present.  Return 0 to allow the player to exit */
    return 0;
}


string
library_table_desc()
{
    string table_desc;

    if (present (table))
        table_desc = table->describe_table ();
    else
        table_desc = " Something is very wrong with this room!";

    return table_desc;
}


void
create_room()
{
    set_short("library");
    set_long("Low bookshelves of red wood stand spaced around the "
        + "perimiter of this cool room." + NPC_DESC + " Sunlight floods in through "
        + "a large leaded-glass window in the north wall, its rays "
        + "made visible by the swirling motes of dust falling slowly "
        + "through the air."
        + VBFC_ME("library_table_desc") + "\n");

     add_exit("hall_lower_north", "east", library_exit_block);

    /* Indicate that we want players to have to "borrow" a book in
     * order to read it.
     */
    set_borrow_required(1);

    /* This is the directory where approved books are saved */
    set_book_directory(MONK_LIB + "books/");
    
    /* This is the directory where books that need approval are saved */
    set_book_approval_directory(MONK_LIB + "books/approval/");

    /* This is the directory where books that have been denied or discarded
     * are saved.
     */
    set_book_removal_directory(MONK_LIB + "books/removed/");

    /* Add shelves to the library so that books can be classified under
     * different categories.  Note that for each shelf you must add a
     * subdirectory with the same name under the base directory specified
     * with set_book_directory().  For instance, we would have to add
     * two directories, /doc/examples/library/book_dir2/general/ and
     * /doc/examples/library/book_dir2/maps/ for the two shelves,
     * "general" and "maps", in this library.
     */
    add_book_shelf(({ "general" }));

    create_library();


    /* Add a sign that gives instructions on how to use the library */
    add_item("sign", library_help());
    add_item(({"bookshelves","bookshelf","low bookshelves"}),
        "They are made of red wood and stand at "
        + "elbow-height.\n");
    add_item(({"wood","red wood"}),
        " It is a sturdy wood, perhaps oak, finished with a "
        + "reddish stain.\n");
    add_item(({"window","leaded-glass window","glass"}),
        " The glass is clear but rather thick, causing it "
        + "to distort the sunlight just enough to create "
        + "random rainbows here and there. Strips of leaded "
        + "iron hold the glass panes in place.\n");
    add_item(({"light","sunlight"}),
        "Sunlight filters through the leaded-glass window, "
        + "strongly enough to brightly illuminate the room "
        + "for reading, yet not so strong as to cause the "
        + "pages of the books to fade.\n");
    add_item(({"rainbow","rainbows","random rainbows"}),
        "You see one in the corner of your eye, but when "
        + "you turn to look, it is gone.\n");
    add_cmd_item("sign","read", library_help());


    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("east", "You enter the cool, bright library.\n");

    populate ();
}

void
populate ()
{
    table = clone_object (MONK_OBJ + "library_table");
    table->move (TO);

    aliya = m_clone_here (MONK_NPC + "aliya", 0, "", " Standing in the "
        + "corner is a stern elf, watching over the library.");
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
    // council members and authorized wizards
    if(m_query_council_member(this_player(), 1))
        return 1;
    else
    {
        /* No-one else has admin access */
        write("You do not have permission to do that.\n");
        return 0;
    }
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
    if(m_query_monk())
        return 1;

    /* We'll allow wizards to write books */
    if (this_player()->query_wiz_level())
    {
        return 1;
    }

    /* No-one else has permission to write books */
    write("Only members may author books here.\n");
    return 0;
}

/*
 * Function name: library_configure_book
 * Description:   Configure a library book.  Redefined to add a
 *                nice short description for the book based
 *                on the file name of the book.
 * Arguments:     object book           - the book object
 *                string text_filename - the file name of the book file to use
 *                string book_name     - the name of the book
 */
public void
library_configure_book(object book, string text_filename, string book_name)
{
    string *adjs = ({ "small", "red", "iron-bound", "dusty",
        "blue", "thick", "copper-bound", "old" });
    int sz, index;
    string adj, nm;

    ::library_configure_book (book, text_filename, book_name);

    sz = sizeof(adjs);
    nm = book_name;
    nm = implode(explode(nm, " "), ""); // parse out spaces: name_to_random will choke on them
    index = NAME_TO_RANDOM(nm, 43242, sz);

    // I am not confident that NAME_TO_RANDOM is reliable (I have
    // seen it return random numbers!). So I will do my own sanity
    // checking.
    if ((index >= 0) && (index < sizeof(adjs)))
        adj = adjs[index];
    else
        adj = adjs[random(sz)];

    book->add_adj(adj);
    book->set_short(adj + " book");
}

