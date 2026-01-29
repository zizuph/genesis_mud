/*
 * The Rangers' recruitment library.
 * This little library holds information about applicants and pupils,
 *     for officers, recruiters, instructors and mentors only to read.
 *
 * Elessar, aug 1998
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/room.c";
inherit "/d/Gondor/common/lib/new_library.c";

#include <composite.h>
#include <macros.h>
#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/lib/ranger_defs.h"
#include "/d/Gondor/common/guild/lib/punish_defs.h"
#include "/d/Gondor/common/guild/lib/titles.h"

#define BSNL(s)		break_string(s + "\n", 55, "\t")
#define PLAYER_I_WRITING_BOOK	"_player_i_writing_book"

string  exa_poster();

varargs void    add_shelf(string name, string desc, mixed books);
        void    add_shelf_book(string name, mixed book);

string *nonshelf_books = ({ });
mapping shelf_book = ([ "Applicants": ({}), ]);
mapping shelf_desc = ([ "Applicants":"The shelf labelled 'Applicants' seems to hold scrolls "
      + "about individuals who have applied to join the Rangers.",
                     ]);

static int Append;

void
create_room()
{
    int     is;
    string *shelves;

    set_library_name("the Recruitment Office");
    set_short("in the Recruitment Office");
    set_long("You are in a small, cramped room. Along the walls are shelves "+
      "stretching towards the ceiling high above. A small desk sits in the middle "+
      "of the floor, two flickering candles providing light around it. "+
      "A poster with some writing on it is hanging by the doorway. "+
      "A doorway leads out to the Hall of Recruits to the east.\n");

    add_exit(RANGER_DIR + "recruithall",    "east",  lib_check,    0);
    add_item(({"ceiling",}), "The ceiling is high above your head, and solid wood "
      + "beams are supporting it.\n");
    add_item(({"poster", "instructions", }), exa_poster());
    add_cmd_item(({"poster", "instructions", }), "read", exa_poster());
    add_item(({"desk", "small desk",}), "@@exa_desk");
    add_item(({"walls", "wall",}), "The walls are hidden behind bookshelves.\n");
    add_item(({"beam", "beams",}), "These pinewood beams are without doubt strong "
      + "enough to safely keep the ceiling aloft.\n");
    add_item(({"floor",}), "In the middle of the floor sits a small desk.\n");
    add_item(({"candle", "candles", "flickering candle", "flickering candles",}),
      "Two flickering candles of wax provide light enough for reading by the desk.\n");
    add_item("doorway", "Through the doorway you see the Hall of Recruits to the east.\n");
    set_borrow_cmd("borrow");
    set_return_cmd("return");
    set_read_cmd("read");
    set_list_cmd("list");
    set_book_type("scroll");
    set_save_path(RANGER_DIR + "gondor/rec_lib/recruit_library");
    set_write_dir(RANGER_DIR + "gondor/rec_lib");
    set_log_file("ranger_application");
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
        desc = BSN(desc + " You see the following scrolls on the shelf:")
          + BSN(COMPOSITE_WORDS(sort_array(shelf_book[shelf])) + ".");
    else
        desc = BSN(desc + " You don't see any scrolls on this shelf.");

    return desc;
}

string
exa_shelves()
{
    return BSN("There are many shelves, each holding some scrolls of "
      + "information. On each shelf is a plaque stating what scrolls "
      + "it contains.")
      + "These are the shelves to choose from:\n"
      + BSNL(COMPOSITE_WORDS(m_indexes(shelf_desc)) + ".");
}

string
exa_desk()
{
    string  desc;
    desc = "It is a small, wooden desk, used by anyone who is writing "
      + "a scroll about an applicant or a pupil. Any scroll not yet moved "
      + "to a shelf will remain on the desk.\n";
    if (sizeof(nonshelf_books))
        desc = desc + "You see the following scrolls on the desk: "
          + BSN(COMPOSITE_WORDS(nonshelf_books));
    return desc;
}

string
exa_poster()
{
    return
      "\tWelcome to the "+query_library_name()+"!\n"
      + "\n\tThe following commands are available:\n\n"
//    + "\tlist [titles]  - list the available titles,\n"
      + "\tborrow <title> - borrow a scroll with the title <title>,\n"
      + "\treturn scroll  - return a scroll,\n"
      + "\tread <title>   - read a scroll without borrowing it,\n"
      + "\ttail <title>   - read the last part of a scroll without borrowing it,\n"
      + "\twrite scroll   - write a new scroll or add to an existing one,\n"
      + "\tmove <title> to <shelf> shelf   - move a scroll to a shelf,\n"
      + "\tremove <title> - remove an obsolete scroll.\n\n";
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
    add_action("move_book_to_shelf", "move");
}

void
reset_room()
{
}

int
query_got_access_here(object pl)
{
    return ((pl->query_skill(SS_MASTER_TASK) == RECRUITER)
        || (pl->query_skill(SS_MASTER_TASK) == INSTRUCTOR)
        || (pl->query_ranger_mentor())
        || (COUNCIL->is_officer(pl->query_real_name()))
        || (SECURITY->query_wiz_dom(pl->query_name()) == "Gondor"));
}

public int
do_read(string str)
{
    if (query_got_access_here(TP))
    {
        return ::do_read(str);
    }
    else
    {
        notify_fail("You are not allowed to touch those!\n");
        return 0;
    }
}

int
query_write_priv(object pl)
{
  if (query_got_access_here(pl))
      return 1;
  return 0;
}

int
query_remove_priv(object pl)
{
    if (query_got_access_here(pl))
        return 1;
    return 0;
}

/*
 *   Wizards of Gondor, Ranger Recruiters, Mentors and Officers can
 *   add books here.
 */
int
query_secure_add(object pl)
{
    if (query_got_access_here(pl))
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

public void
add_book(string name, string descr, string path, int flag)
{
    name = CAP(LOW(name));
    if (!sizeof(nonshelf_books))
        nonshelf_books = ({ name });
    else
        nonshelf_books += ({ name });
    ::add_book(name, descr, path, flag);
}

public int
lib_hook_office_not_exist()
{
    notify_fail("You don't see that scroll anywhere.\n");
    return 0;
}

public int
move_book_to_shelf(string s)
{
    string  book,
            shelf,
           *shelves;
    int     i,
            n;

    if (!query_got_access_here(TP))
    {
        NFN("You are not allowed to do that.");
        return 0;
    }

    s = capitalize(lower_case(s));
    if (sscanf(s, "%s to %s shelf", book, shelf) < 2)
    {
        NFN("Move which scroll to which shelf?\n"
          + "Try: move <scroll> to <shelf> shelf.");
        return 0;
    }

    if (member_array(CAP(shelf), query_shelf()) < 0)
    {
        NFN("There is no shelf with the name \""+CAP(shelf)+"\" in this office!");
        return 0;
    }
    i = member_array(book, nonshelf_books);
    if (i < 0)
    {
        /* Check if it is a book in the shelves. */
        shelves = m_indexes(shelf_book);

        for (i = 0; i < sizeof(shelves); i++)
        {
            if ((n = member_array(book, shelf_book[shelves[i]])) >= 0)
            {
                shelf_book[shelves[i]] =
                  exclude_array(shelf_book[shelves[i]], n, n);
                add_shelf_book(shelf, book);
                FIX_EUID
                write("You move the scroll from the " + shelves[i] 
                  + " shelf " + "to the " + CAP(shelf) + " shelf.\n");
                say(QCTNAME(TP) + " moves a scroll from one shelf to "
                  + "another.\n");
                log_file(log_file, "LIBRARY: " + this_player()->query_name()
                  + " moved the book " + book + " from shelf " + shelves[i]
                  + " to the shelf " + CAP(shelf) + " on "
                  + ctime(time())+".\n");
                save_object(savepath);
                return 1;
            }
        }

        return lib_hook_office_not_exist();
    }
    add_shelf_book(shelf, book);
    write("You put the scroll in the " + CAP(shelf) + " shelf.\n");
    say(QCTNAME(TP) + " takes a scroll from the desk and puts it in one of "
      + "the shelves.\n");

    FIX_EUID

    log_file(log_file, "LIBRARY: " + this_player()->query_name()
      + " moved the book " + book + " to the shelf "+CAP(shelf)
      + " on "+ctime(time())+".\n");
    nonshelf_books = exclude_array(nonshelf_books, i, i);
    save_object(savepath);
    return 1;
}

void
lib_hook_finish_book(int sec)
{
    if (sec)
        write("You drop your book into the mailbox of the Council.\n");
    else
        write("You finish your "+booktype+", leaving at the desk. "
          + "Now you should move it to one of the shelves.\n");
    say(QCTNAME(this_player())+" finishes writing a "+booktype
      + " at the desk.\n");
}

public int
remove_shelf_book(string shelf, string name)
{
    int  i;

    if (!strlen(shelf) || !strlen(name))
        return 0;

    if (!shelf_book[shelf])
        return 0;

    name = CAP(LOW(name));
    if ((i = member_array(name, shelf_book[shelf])) >= 0)
    {
        shelf_book[shelf] = exclude_array(shelf_book[shelf], i, i);
        save_object(savepath);
        return 1;
    }
    return 0;
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
/*
    n = member_array(name, names);
    fnam = paths[n];
    rm(fnam);
*/

    if (member_array(name, nonshelf_books) >= 0)
    {
        i = member_array(name, nonshelf_books);
        nonshelf_books = exclude_array(nonshelf_books, i, i);
        save_object(savepath);
        return r;
    }

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
    
/*
 * Function name: get_book_name
 * Description:   input the name of the book
 *                modified to allow appending to existing books
 * Arguments:	  s - the name
 * Returns:	  0
 */
public void
get_book_name(string s)
{
    int     bn;
    string  old_file;

    if (!strlen(s))
    {
        lib_hook_query_name();
        input_to(get_book_name);
        return;
    }
    nbnam = capitalize(lower_case(s));

    if ((bn = member_array(nbnam, names)) >= 0)
    {
        write("You take the "+booktype+" from the shelves and start "
          + "to add to it.\n");
        Append = 1;
        nbdesc = descrs[bn];
        this_player()->add_prop(PLAYER_I_WRITING_BOOK, 1);
        setuid();
        seteuid(getuid());

        old_file = read_file(paths[bn]);
        clone_object(EDITOR_OBJECT)->edit("done_appending", old_file,
          sizeof(explode(old_file,"\n")));
        return;
    }

    lib_hook_query_desc();
    input_to(get_book_desc);
}
/*
 * Function name: done_appending
 * Description:   write the modified text of the book
 * Arguments:     str - the text
 * Returns:       0
 */
void
done_appending(string str)
{
    int     bn;
    string  msg;

    busy = 0;

    if (!strlen(str))
    {
        write("You abort appending to the "+booktype+".\n");
        return;
    }

    bn = member_array(nbnam, names);
    fnam = paths[bn];
    rm(fnam);
    write_file(fnam, str);

    write("You finish editing the "+booktype
          + " and put it back onto the shelf.\n");
    say(QCTNAME(this_player())+" finishes editing a "+booktype
      + " and returns it to the shelves.\n");

    log_file(log_file, "LIBRARY: "+this_player()->query_name()
      + " edited the book " + nbnam + " (" + nbdesc
      + ") on " + ctime(time()) + ".\n");
}
