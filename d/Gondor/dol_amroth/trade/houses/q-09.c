/* -*- Mode: C -*-
 *
 * trade/houses/q-09.c
 *
 * Skippern 20(c)01
 *
 * Harbour office in Dol Amroth.
 */
#include "../../defs.h"

inherit DOL_STD + "inside";
inherit "/d/Gondor/common/lib/new_library";

#include <composite.h>
#include <macros.h>
#include <std.h>
#include <stdproperties.h>

#define BSNL(s)         break_string(s + "\n", 55, "\t")

/* Global variables */
string *authors;
mapping shelf_book = ([ "General": ({}),
		        "Maps": ({}), ]);
mapping shelf_desc = ([ "General":"The shelf 'General' contains books " +
		      "about general topics.",
		      "Maps":"The shelf 'Maps' contains maps of various " +
		      "places.",
		      ]);
object  qmaster;

/* Prototypes */
string          exa_shelves();
string          show_map();
varargs void    add_shelf(string name, string desc, mixed books);
void            add_shelf_book(string name, mixed book);


int wizcheck()
{
    if (this_player()->query_wiz_level())
        return 0;
    write("What?\n");
    return 1;
}

void
create_inside()
{
    int     is;
    string *shelves;


    FIX_EUID;

    set_library_name("Dol Amroth Trade Office");

    set_short("small office");
    set_long("This is a small office above a warehouse. A large desk " +
	     "fills up most of the room, and on the north wall there " +
	     "is a window. Behind the desk is a large comfortable " +
	     "chair. It looks the office of somebody important. On " +
	     "the east wall there hangs some scatches, and on the " +
	     "west wall there hangs a large map. The south " +
	     "wall is occupied by a large bookshelf.\n");

    add_item( ({ "bookshelf", "shelf", "shelves" }), &exa_shelves());
    add_item("scetches", "The east wall is full of scetches showing " +
	     "everything from ships to buildings. On some of them " +
	     "corrections have been made.\n");
    add_item("map", &show_map());

    set_borrow_cmd("borrow");
    set_return_cmd("return");
    set_read_cmd("read");
    set_list_cmd("list");
    set_save_path(DOL_BASE + "/txt/library/books/");
    set_write_dir(DOL_BASE + "/txt/library/approval/");
    set_log_file("DolAmrothBooks");
    set_librarian_room(DOL_OTHER + "lib_room");
    set_up_library();
    shelves = m_indexes(shelf_desc);
    for (is = 0; is < sizeof(shelves); is++)
        add_item(LOW(shelves[is]), "@@query_shelf_long|"+shelves[is]+"@@");

    //    add_exit(DOL_OTHER + "lib_room", "addbook", &wizcheck(), 1, 1);
    clone_object(DOL_OBJ + "doors/q-09-door-office")->move(this_object());

    reset_room();
}

void
reset_room()
{
    if (!present(qmaster))
    {
	qmaster = clone_object(DOL_NPC + "harbourm");
	qmaster->move(this_object());
    }
}

string
show_map()
{
  return "Its blury.\n";
}

void
init()
{
    ::init();
    init_library();
}

string
query_shelf_long(string shelf)
{
    string  desc = shelf_desc[shelf];

    if (sizeof(shelf_book[shelf]))
        desc = BSN(desc + " You see the following titles:")
	    + BSN(COMPOSITE_WORDS(shelf_book[shelf]) + ".");
    else
        desc = BSN(desc);

    return desc;
}

string
exa_shelves()
{
    return BSN("This bookshelf is made of sturdy redwood, and there are " +
	       "many interesting books in it.\n")
      + "These are the topics you can choose from:\n"
	+ BSNL(COMPOSITE_WORDS(m_indexes(shelf_desc)) + ".");
}

int
do_list(string str)
{
    if (!TP->query_wiz_level())
        return 0;

    return ::do_list(str);
}

void
reset_library()
{
    authors = ({"thalian"});
}

int
query_write_priv(object pl)
{
    return 1;
}

int
query_remove_priv(object pl)
{
    if (SECURITY->query_wiz_dom(pl->query_name()) == "Gondor")
	return 1;
    return 0;
}

/*
 *   Noone can add books here, because the shelves are only
 *   set from the office.
 */
int
query_secure_add(object pl)
{
    return 1;
    if (SECURITY->query_wiz_dom(pl->query_name()) == "Gondor")
	return 0;
    return secure_add;
}

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

varargs mixed
query_shelf_book(string shelf)
{
    if (stringp(shelf))
        return shelf_book[CAP(LOW(shelf))];
    return shelf_book;
}

string *
query_shelf()
{
    return m_indexes(shelf_desc);
}

void
lib_hook_finish_book(int sec)
{
    if (sec)
        write("You finish your book and out it in a box marked oproval.\n");
    else
        write("You finish your "+booktype
	      + " and put it onto one of the shelves.\n");
    say(QCTNAME(this_player())+" finishes a "+booktype
	+ " and adds it to the library.\n");
}

/*
 * Function name: remove_book
 * Description:   remove the book 'name' from the library
 * Arguments:     name - the name of the book to remove
 * Returns:       1 if success
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
            shelf_book[shelves[i]] = exclude_array(shelf_book[shelves[i]], n, 
		n);
            save_object(savepath);
            return r;
        }
    }

    return r;
}

