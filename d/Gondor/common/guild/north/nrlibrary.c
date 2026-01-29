/*
 * North Rangers Library.
 * This room will contain lots of information for the Rangers only.
 * Books of many kinds will be in this room, to read from, not take.
 * Made by Elessar, April 1992.
 *
 * Recoded to use /d/Gondor/common/lib/library.c
 * Olorin, 9-nov-1994
 */
#pragma save_binary

inherit "/d/Gondor/common/room";
inherit "/d/Gondor/common/lib/new_library";

#include <composite.h>
#include <macros.h>
#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/lib/ranger_defs.h"
#include "/d/Gondor/common/guild/lib/titles.h"

#define BSNL(s)		break_string(s + "\n", 55, "\t")

        string  exa_poster();
varargs void    add_shelf(string name, string desc, mixed books);
        void    add_shelf_book(string name, mixed book);

string *authors;

mapping shelf_book = ([ "Lore": ({}), ]);
mapping shelf_desc = ([ "Lore":"The shelf labelled 'Lore' seems to contain books about "
      + "several subjects of the Nature and life in the wilderness.",
                     ]);
#if 0
    add_shelf("archive", "On this shelf the archives of the Guild of "
      + "the Rangers of the Westlands are kept.");
    add_shelf_book("archive",
        ({"Rangers", "Book-of-Votes", "Book-of-Elections", "Charter"}));
#endif

object  scroll;

void
create_room()
{
    int     is;
    string *shelves;

    set_library_name("the Library of the Rangers of the North");
    set_short("in the Library of the Rangers of the North");
    set_long("You are in a large hall with a domed ceiling. Along "+
      "the walls are shelves, and more shelves are out on the floor, "+
      "and all the shelves are filled with books of all colours, "+
      "sizes and ages. At a desk in the south-eastern corner of the room sits "+
      "an aging man, probably the librarian. A doorway leads out to the meeting-room "+
      "south. Your glance stops at a poster by the open door, which reads: "+
    "No talking! Further down on the poster you see some instructions. "+
    "Another doorway leads east into a dusty chamber.\n");

    add_exit(RANGER_DIR + "north/meeting_room","south", "@@lib_check", 0);
    add_exit(RANGER_DIR + "north/lib_office", "east", "@@office_block", 0);

    add_item("librarian", BSN(
        "The librarian is a man of Dunadan origin, dedicated to keep "
      + "track of the books and texts in the Library of the Rangers of Gondor. "
      + "He will probably not let you leave with books."));

    add_item(({"poster", "instructions", }), exa_poster());
    add_cmd_item(({"poster", "instructions", }), "read", exa_poster());

    set_borrow_cmd("borrow");
    set_return_cmd("return");
    set_read_cmd("read");
    set_list_cmd("list");
    set_book_type("book");
    set_save_path(RANGER_DIR + "north/books/ranger_library");
    set_write_dir(RANGER_DIR + "north/books");
    set_log_file("guild");
    set_librarian_room(RANGER_DIR + "north/lib_office");
    set_up_library();

    add_item("shelves","@@exa_shelves");

    add_prop(ROOM_I_INSIDE, 1);

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
          + BSN(COMPOSITE_WORDS(shelf_book[shelf]) + ".");
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
      + BSNL(COMPOSITE_WORDS(m_indexes(shelf_desc)) + ".");
}

string
exa_poster()
{
    return
        "\n\t\t\tNO TALKING!\n\n"
      + "\tWelcome to the "+query_library_name()+"!\n"
      + "\n\tThe following commands are available:\n\n"
//    + "\tlist [titles]  - list the available titles,\n"
      + "\tborrow <title> - borrow a book with the title <title>,\n"
      + "\treturn book    - return a book,\n"
      + "\tread <title>   - read a book without borrowing it,\n"
      + "\twrite book     - write a new book and submit it to the\n"
      + "\t                 Council for addition to the library.\n"
      + "\n\tCouncil members can remove old titles.\n\n";
}

int
do_list(string str)
{
    if (!TP->query_wiz_level())
        return 0;

    return ::do_list(str);
}

void
init()
{
    ::init();
    init_library();
}

void
reset_room()
{
    if (!objectp(scroll))
    {
        scroll = clone_object(RANGER_DIR+"spells/obj/pigeon_scroll");
        scroll->move(TO);
    }
}

void
reset_library()
{
    authors = ({"thalian"});
}

int
author_exists(string author)
{
    int     n;
    if (!strlen(author))
        return 0;

    author = LOW(author);

    if (member_array(author, authors) == -1)
        return 0;
    return 1;
}

string
query_author_list()
{
    int     n;
    string  author_list = "";

    if (!sizeof(authors))
        return "No authors named.\n";

    while (n<sizeof(authors)-1)
    {
        author_list += CAP(authors[n])+", ";
        n++;
    }
    author_list += CAP(authors[n])+".";
    author_list = BSN("Currently these mortals which are not rangers " +
        "have access to the library of the North Rangers:") +
    BSN(author_list);

    return (author_list);
}

int
list_all_authors()
{
    if (SECURITY->query_wiz_dom(TP->query_name()) != "Gondor")
        return 0;
    write(query_author_list());
    return 1;
}
  
int
add_author(string author)
{
    if (SECURITY->query_wiz_dom(TP->query_name()) != "Gondor")
        return 0;
    author = LOW(author);

    if(author_exists(author))
    {
        write("The librarian says: That mortal already has access "
          + "to the library, dear "+ TP->query_cap_name()+".\n");
        return 1;
    }
    if(!SECURITY->finger_player(author) || SECURITY->query_wiz_level(author))
    {
        write("The librarian says: There is no mortal with that name, dear "
          + TP->query_cap_name()+".\n");
        return 1;
    }

    if(!sizeof(authors))
        authors = ({author});
    else
        authors = authors + ({author});
    if (strlen(savepath))
      save_object(savepath);
    write("You enable the mortal "+CAP(author)+" to enter the library.\n");
    return 1;
}

int
remove_author(string author)
{
    int     n;

    if (SECURITY->query_wiz_dom(TP->query_name()) != "Gondor")
        return 0;

    author = LOW(author);

    if (!author_exists(author))
    {
        write("That mortal has no access to the library!\n");
        return 1;
    }

    while (n<sizeof(authors))
    {
        if (author == authors[n]) 
        {
            authors = exclude_array(authors,n,n);
            write("You remove "+CAP(author)+" from the list of mortals "
              + "which have access to the library.\n");
            if (strlen(savepath))
              save_object(savepath);
            return 1;
        }
        n++;
    }
    write("The author didn't have access afterall.\n");
    return 1;
}

int
query_write_priv(object pl)
{
  if (IS_RANGER(pl) ||
      SECURITY->query_wiz_dom(pl->query_name()) == "Gondor")
    return 1;
  return 0;
}
int
query_remove_priv(object pl)
{
  if (SECURITY->query_wiz_dom(pl->query_name()) == "Gondor"
      || (pl->query_master_ranger() &&
	 (pl->query_skill(SS_MASTER_TASK) == HISTORIAN ||
          pl->query_skill(SS_MASTER_TASK) == SCHOLAR))
      || COUNCIL->is_officer(pl->query_real_name()))
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
#if 0
  if (SECURITY->query_wiz_dom(pl->query_name()) == "Gondor"
      || COUNCIL->is_council_member(pl->query_real_name()))
    return 0;
  return secure_add;
#endif
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

void
lib_hook_finish_book(int sec)
{
    if (sec)
        write("You drop your book into the mailbox of the Council.\n");
    else
        write("You finish your "+booktype
          + " and put it onto one of the shelves.\n");
    say(QCTNAME(this_player())+" finishes a "+booktype
      + " and adds it to the library.\n");
}

/*
 * Function name: remove_book
 * Description:   remove the book 'name' from the library
 * Arguments:	  name - the name of the book to remove
 * Returns:	  1 if success
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
            return r;
        }
    }

    return r;
}
    
int
office_block()
{
    int  mr;
    mr = TP->query_skill(SS_MASTER_TASK);
    if ((MASTER_TITLES[mr] == "Scholar"
        || MASTER_TITLES[mr] == "Historian"))
    {
        write(BSN("The librarian bows to you as you pass, saying: Greetings, "
          + "Master " + MASTER_TITLES[mr]+"! Welcome to your office!"));
        say("The librarian bows to " + QTNAME(TP) + ", saying: Greetings, "
          + "Master " + MASTER_TITLES[mr] + "! Welcome to your office!\n", TP);
        return 0;
    }
    else if (COUNCIL->is_officer(TP->query_real_name()))
    {
        write(BSN("The librarian bows to you as you pass, saying: Greetings, "
          + TP->query_ranger_title() + "!"));
        say("The librarian bows to " + QTNAME(TP) + ", saying: Greetings, "
          + TP->query_ranger_title(1) + "!\n", TP);
        return 0;
    }
    else if (TP->query_wiz_level())
    {
        write(BSN("The librarian bows to you as you pass, saying: "
          + "Greetings, wizard!"));
        say("The librarian bows to " + QTNAME(TP) + ", saying: "
          + "Greetings, wizard!\n", TP);
        return 0;
    }
    write(BSN("The librarian stops you, saying: Only those in charge of this "
      + "library may enter that office."));
    say("The librarian stops " + QTNAME(TP) + " from entering the east "
      + "doorway, saying: Only those in charge of this library may enter "
      + "that office.\n", TP);
    return 1;
}
