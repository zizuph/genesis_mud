/*
 * /d/Gondor/common/lib/library.c
 * 
 * Master library of Gondor
 *
 * Coded following /d/Gondor/rohan/edoras/edlibrary.c by Elessar
 *
 * Created: 09-nov-1994 by Olorin
 */
#pragma save_binary

inherit "/d/Gondor/common/room";

#include <composite.h>
#include <macros.h>
#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define BOOK_DIR	(LIBRARY_DIR + "books/")

#define HE(x)		(x)->query_pronoun()
#define BSNL(s)		break_string(s + "\n", 55, "\t")

int     query_book(string title);
int     gondorwiz(object player);
string  read_poster();
string  exa_desk();

static string *default_books,
              *shelves = ({ "Legends", "Lore", "History", "Geography",
                            "Miscellaneous", }),
               librarian = "librarian",
               library_name,
               extra_line,
               book_list;
       string *books = ({ });

void    set_library_name(string str)  { library_name  = str; }
void    set_extra_line(string str)    { extra_line    = str; }

void
create_library()
{
    set_library_name("a Library in Gondor");
    set_extra_line("A doorway leads out to the street east. ");
}

nomask void
create_room()
{
    add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_I_INSIDE,1);

    add_item("shelves","@@exa_shelves");
    add_item("books","There are so many of them, you don't know where "
      + "to start!\n");

    create_library();

    set_short(CAP(library_name));

    set_long(BSN(
        "You are in a very large hall with shelves along the walls, "
      + "more shelves on the floor, and all the shelves are filled with "
      + "books of all colours, sizes and ages. At a desk in the "
      + "north-eastern corner of the room stands an aging man, probably "
      + "the "+librarian+". " + extra_line + "Your gaze stops at a "
      + "poster by the open door, which says: No talking! Further down "
      + "on the poster you see some instructions."));

    add_item("desk", exa_desk());
    add_item(({"poster", "instructions"}), read_poster());
    add_cmd_item(({"poster", "instructions"}), "read", read_poster());

    if (strlen(book_list) && (file_size(book_list + ".o") > -1))
        restore_object(book_list);
}

string
exa_shelves()
{
    return BSN("There are many shelves, each containing a different sort "
      + "of books. On each shelf is a plaque stating what kind of books "
      + "it contains.")
      + "These are the shelves to choose from:\n\n"
      + BSNL(COMPOSITE_WORDS(shelves) + ".");
}

string
exa_desk()
{
    return BSN(
        "The desk isn't, as you would think, covered with pile upon pile of "
      + "books, but absolutely clean and tidy. The reason is that this is "
      + "no ordinary library where you borrow books to take home, but more "
      + "an archive, a place of lore, where records of many a secret thing "
      + "remain enshrined. One of the reasons that the "+librarian+" is "
      + "here, is to prevent you from leaving with any of the books.");
}

void
init()
{
    ::init();
    add_action("no_say","say");
    add_action("no_say","scream");
    add_action("no_say","'",1);
    add_action("no_say","rsay");
    add_action("no_say","shout");
    add_action("no_say","grsay");
    add_action("no_say","laugh");
    add_action("no_say","sing");  
    add_action("read_book","read");
    add_action("add_book","newbook");
    add_action("remove_book","banbook");
    add_action("list_all_books","allbooks");
    add_action("check_time","time");
}

int
no_say(string str)
{
    string  vb = query_verb();

    if (vb == "say" || vb == "grsay" || vb == "rsay" ||
        explode(vb,"")[0] == "'")
        vb = "speak";
    write(BSN("You are about to open your mouth to "+vb+" when you happen "
      + "to look at the "+librarian+". His stern eyes are staring right at "
      + "you while he is pointing at the poster which reads 'NO TALKING!'")
      + "You decide to keep your mouth shut.\n");
    return 1;
}

string
read_poster()
{
    return "\n\t\t\tNO TALKING!\n\n"
      + "\tWelcome to "+library_name+"!\n\n" + BSNL(
        "Examine the shelves in this library to find which titles "
      + "are available. It is not possible to borrow any books, "
      + "but you can of course read any book that is present.") + "\n"
      + "\tJust type 'read <title>'!\n\n";
}

int
read_book(string book)
{
    object  tp = TP;

    if (!strlen(book))
        NFN0("Read what?");

    if (query_book(book) >= 0)
    {
        write("You read the book titled "+CAP(book)+".\n");
        say(QCTNAME(tp)+" reads a book "+HE(tp)+" found in the shelves.\n",tp);
        book = LOW(book);
        this_player()->more(read_file(BOOK_DIR + book + ".txt"));
        return 1;
    }
    NFN("You don't see that book here.");
    return 0;
}

string *
set_default_books(string *arr)
{
    int     i;

    default_books = arr;

    return default_books;
}

void
reset_library()
{
    books = default_books;
    write("The library has been reset.\n");
    save_object(book_list);
}

int
query_book(string title)
{
    int     n;

    if (!strlen(title))
        return -1;

    title = CAP(LOW(title));

    return member_array(title, books);
}

int
add_book(string book)
{
    object  tp = TP;

    if (!gondorwiz(TP))
        return 0;

    if (query_book(book) >= 0) 
    {
        write("The "+librarian+" says: "
          + "That book is already in our shelves, dear "
          + tp->query_name()+".\n");
        return 1;
    }
    book = CAP(LOW(book));
    books = books + ({ book });
    save_object(book_list);
    write("You put a book titled "+book+" into the shelves.\n");
    say(QCTNAME(tp)+" puts a new book into the shelves.\n",tp);
    return 1;
}

string
query_title_list()
{
    int     n;
    string  title_list;

    if (!sizeof(books))
        return "No books available.\n";

    title_list = "Currently these titles are available in "
      + library_name + ": ";

    title_list += COMPOSITE_WORDS(books);

    return BSN(title_list);
}

int
list_all_books()
{
    if (!gondorwiz(TP))
        return 0;
    write(query_title_list());
    return 1;
}

int
remove_book(string book)
{
    int     n;
    object  tp = TP;

    if (!gondorwiz(tp))
        return 0;

    if ((n = query_book(book)) < 0)
        NFN0("That book is not in the shelves!");

    book = CAP(LOW(book));

    books = exclude_array(books,n,n);
    write("You remove the book titled "+book+" from the shelves.\n");
    say(QCTNAME(tp)+" removes a book from the shelves.\n",tp);
    save_object(book_list);

    return 1;
}

int
gondorwiz(object player)
{
    if (player->query_wiz_level() &&
        SECURITY->query_wiz_dom(player->query_name()) == "Gondor")
        return 1;
    return 0;
}

string
set_book_list(string str)
{
    book_list = str;
    if (sizeof(explode(str, "/")) == 1)
        book_list = (LIBRARY_DIR + str);

    return book_list;
}

string
query_book_list()
{
    return book_list;
}

int
set_shelves(string *arr)
{
    if (!pointerp(arr))
        return 0;
    shelves = arr;
    return 1;
}

string *
query_shelves()
{
    return shelves;
}

int
set_librarian(string str)
{
    librarian = str;
}
