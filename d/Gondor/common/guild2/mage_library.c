/* 
 *    The library of the Society of Morgul Mages in Minas Morgul 
 *    Olorin, Aug-1994
 *    Modified to use /d/Gondor/common/lib/new_library,
 *    - Olorin, Jan-1995
 *
 *    Modification log:
 *     5-Dec-1996, Olorin: Split library into mage and apprentice libraries. 
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
inherit "/d/Gondor/common/lib/new_library.c";

#include <composite.h>
#include <macros.h>
#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define BSNL(s)        break_string(s + "\n", 55, "\t")
#define BORROWED_BOOK    "borrowed_from_"

//    Prototypes
        string  exa_plaque();
varargs void    add_shelf(string name, string desc, mixed books);
        void    add_shelf_book(string name, mixed book);
public  int     nazgul_check();

//    Global variables
mapping shelf_book = ([ "Society": ({}), ]);
mapping shelf_desc = ([ "Society":"The shelf labelled 'Society' contains scrolls "
      + "about the rules and traditions of the Society of Morgul Mages.",
                     ]);

void
create_morgul_room()
{
    int     is;
    string *shelves;

    set_road(9);
    set_short_desc("in the Library of the Society of Morgul mages in Minas Morgul");
    set_extraline(
        "This is a damp cellar beneath the main hall of the library "
      + "of Minas Morgul. Here the mages of the Society "
      + "keep important documents. On one wall there is a plaque with "
      + "instructions. A doorway is leading west into the part of the "
      + "library open to apprentices, while a narrow and forbidding "
      + "doorway opens in the east wall.");  

    add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_I_INSIDE,1);
    add_exit(MAGES_DIR + "society_library", "west", check_exit,   0);
    add_exit(MAGES_DIR + "library_office",  "east", nazgul_check, 0);

    add_item(({"plaque", "instructions", }), exa_plaque());
    add_cmd_item(({"plaque", "instructions", }), "read", exa_plaque());

    set_save_path(MAGES_DIR + "books/mage_library");
    set_write_dir(MAGES_DIR + "books/mages");
    set_librarian_room(MAGES_DIR + "library_office");
    set_library_name("the Secret Library of the Society of Morgul Mages");
    set_book_type("scroll");
    set_read_cmd("read");
    set_log_file("morgul_lib");

    set_up_library();

    add_item(({"shelf", "shelves", }), VBFC_ME("exa_shelves"));

    shelves = m_indexes(shelf_desc);
    for (is = 0; is < sizeof(shelves); is++)
        add_item(LOW(shelves[is]), "@@query_shelf_long|"+shelves[is]+"@@");
}

string
query_shelf_long(string shelf)
{
    string  desc = shelf_desc[shelf];

    if (sizeof(shelf_book[shelf]))
        desc = BSN(desc + " You see the following titles:")
          + BSN(COMPOSITE_WORDS(sort_array(shelf_book[shelf])) + ".");
    else
        desc = BSN(desc);

    return desc;
}

string
exa_shelves()
{
    return BSN("There are many shelves, each containing a different sort "
      + "of books. On each shelf is a plaque stating what kind of books "
      + "it contains.")
      + "These are the shelves to choose from:\n"
      + BSNL(COMPOSITE_WORDS(sort_array(m_indexes(shelf_desc))) + ".");
}

void
init()
{
    ::init();

    init_library();
}

/*
 * Function name: mlib_check
 * Description:   check if a player tries to steal a book
 * Arguments:      none
 * Returns:      0 if no thief, 1 if he tries to walk away with a book
 */
public nomask int
mlib_check()
{
    if (this_player()->query_prop(BORROWED_BOOK+libnam))
    {
        this_player()->catch_msg(
            "A terrible dark power will not let you pass until you return the "
          + booktype + ".\n");
        return 1;
    }
    return 0;
}

public int
nazgul_check()
{
    if (mlib_check())
        return 1;

    if ((TP->query_nazgul() < 1) &&
        (SECURITY->query_wiz_dom(TP->query_name()) != "Gondor"))
    {
        write("Begone, puny mortal! Only nazgul may enter here!\n");
        return 1;
    }

    return 0;
}

int
check_exit()
{
    if (mlib_check())
        return 1;

    ::check_exit();
}

string
exa_plaque()
{
    return
        "\n\tThe following commands are available:\n\n"
      + "\tlist <shelf>   - list the titles on a shelf,\n"
      + "\tborrow <title> - borrow a scroll with the title <title>,\n"
      + "\treturn scroll  - return a scroll,\n"
      + "\tread <title>   - read a scroll without borrowing it,\n"
      + "\twrite scroll   - write a new scroll and submit it to the\n"
      + "\t                 Nazgul for addition to the library.\n"
      + "\n\tNazgul can remove old titles.\n\n";
}

int
query_write_priv(object pl)
{
    if (IS_MORGUL_MAGE(pl) ||
        SECURITY->query_wiz_dom(pl->query_name()) == "Gondor")
        return 1;
    return 0;
}

int
query_remove_priv(object pl)
{
    if ((pl->query_nazgul() < 1) &&
        (SECURITY->query_wiz_dom(pl->query_name()) != "Gondor"))
        return 0;
    return 1;
}

/*
 * No one can add books from here since the shelves can be set
 * only from the office.
 */
int
query_secure_add(object pl)
{
    return 1;
}

int
lib_hook_borrow_fail_find()
{
    notify_fail("You cannot find that "+booktype+".\n");
    return 0;
}

void
lib_hook_borrow_fail_move()
{
    write("You try to take a "+booktype+" but fail.\n"
        + "You cannot carry the "+booktype+"!\n");
    say(QCTNAME(this_player())+" tries to take a "+booktype+" but fails.\n");
}

void
lib_hook_borrow_move()
{
    write("You take a "+booktype+" from the shelves.\n");
    say(QCTNAME(this_player())+" takes a "+booktype+" from the shelves.\n");
}

/*
 *    Modified code for a library with different shelves
 */

varargs void
add_shelf(string name, string desc, mixed books)
{
    name = CAP(LOW(name));
    shelf_desc[name] = desc;
    if (stringp(books))
        books = ({ books });
    else if (!pointerp(books))
        books = ({});
    shelf_book[name] = books;
    save_object(savepath);
    add_item(LOW(name), "@@query_shelf_long|"+name+"@@");
}

void
add_shelf_book(string name, mixed book)
{
    name = CAP(LOW(name));
    if (stringp(book))
        book = ({ book });

    if (!pointerp(shelf_book[name]))
        shelf_book[name] = ({});
    shelf_book[name] += book;
    save_object(savepath);
}

public void
remove_shelf(string shelf)
{
    shelf = CAP(LOW(shelf));
    shelf_book = m_delete(shelf_book, shelf);
    shelf_desc = m_delete(shelf_desc, shelf);
    save_object(savepath);
}

string *
query_shelf()
{
    return m_indexes(shelf_desc);
}

varargs mixed
query_shelf_desc(string shelf)
{
    if (stringp(shelf))
        return shelf_desc[CAP(LOW(shelf))];
    return shelf_desc;
}

varargs mixed
query_shelf_book(string shelf)
{
    if (stringp(shelf))
        return shelf_book[CAP(LOW(shelf))];
    return shelf_book;
}

/*
 * Function name: remove_book
 * Description:   remove the book 'name' from the library
 * Arguments:      name - the name of the book to remove
 * Returns:      1 if success
 */
public int
remove_book(string name)
{
    int     i, n, r;
    string *shelves;

    if (!(r = ::remove_book(name)))
        return 0;

    name = CAP(LOW(name));
    shelves = m_indexes(shelf_book);

    for (i = 0; i < sizeof(shelves); i++)
    {
        if ((n = member_array(name, shelf_book[shelves[i]])) >= 0)
        {
            shelf_book[shelves[i]] = exclude_array(shelf_book[shelves[i]], n, n);
            save_object(savepath);
			IDLENESS->increase_activity( this_player(), TYPICAL_ACTIVITY );
            return r;
        }
    }
    return r;
}

int
lib_hook_list_fail()
{
    NFN("The is no shelf of that name in the library.");
    return 0;
}

int
lib_hook_lib_empty()
{
    NFN("That shelf is currently empty.");
    return 0;
}

/*
 * Function name: do_list
 * Description:   let the player list the contents of the library
 * Arguments:      s - argument of the command
 * Returns:      1 if success, 0 else
 */
public int
do_list(string s)
{
    int     i;
    string  txt,
           *list_names,
            shelf;

    if (!strlen(s))
        s = "titles";
    else
        s = LOW(s);

    if (s == "titles")
        list_names = names;
    else if (member_array(CAP(s), query_shelf()) >= 0)
        list_names = shelf_book[CAP(s)];
    else
        return lib_hook_list_fail();

    // catch an empty library or empty shelf
    if (!sizeof(list_names))
        return lib_hook_lib_empty();

    if (s == "titles")
        txt = "These are the "+LANG_PWORD(booktype)+" you can see "
          + "on the shelves of the " + libnam + ":\n";
    else
        txt = "These are the "+LANG_PWORD(booktype)+" you can see "
          + "on the shelf \""+CAP(s)+"\":\n";

    for (i = 0; i < sizeof(names); i++)
        if (member_array(names[i], list_names) >= 0)
            txt += sprintf("%-20s %-55s\n", names[i], descrs[i]);

    TP->more(txt);
    IDLENESS->increase_activity( this_player(), MINOR_ACTIVITY );
    return 1;
}

/*
 * Function name: move_book
 * Description:   Move book from one shelf to another.
 * Argument:      book  - the title
 *                shelf - the new shelf
 * Returns:       1/0   - failure/success
 */
public int
move_book(string book, string shelf)
{
    int     i, s;
    string *shelves;

    if (member_array(book, names) < 0)
    {
    NFN("There is no " + booktype + " " + book + " in the mage library!");
    return 0;
    }

    if (member_array(CAP(shelf), shelves = query_shelf()) < 0)
    {
    NFN("There is no shelf " + shelf + " in the mage library!");
    return 0;
    }

    for (i = 0, s = sizeof(shelves); i < s; i++)
    shelf_book[shelves[i]] -= ({ book });
    add_shelf_book(shelf, book);
    write("You move the " + booktype + " " + book +
      " to the shelf " + shelf + " in the mage library.\n");
    say(QCTNAME(TP) + " moves the " + booktype + " " + book +
    " to the shelf " + shelf + " in the mage library.\n");
    IDLENESS->increase_activity( this_player(), TYPICAL_ACTIVITY );
    return 1;
}

/*
 * Function name: do_read
 * Description  : This is a mask of the orginal function from the
 *                /d/Gondor/common/lib/new_library.c It's only purpose
 *                is to call idleness system in the case of success.
 */
public int do_read( string str )
{
    if (::do_read( str ) == 1)
    {
        IDLENESS->increase_activity( this_player(), OTHER_LIB_READ );
        return 1;
    }
    return 0;
}

public int do_borrow( string str )
{
    if (::do_borrow( str ) == 1)
    {
        IDLENESS->increase_activity( this_player(), EMOTION / 2 );
        return 1;
    }
    return 0;
}

public int do_return( string str )
{
    if (::do_return( str ) == 1)
    {
        IDLENESS->increase_activity( this_player(), EMOTION / 2 );
        return 1;
    }
    return 0;
}
