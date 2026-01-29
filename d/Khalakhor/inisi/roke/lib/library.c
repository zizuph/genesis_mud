/*
 * library.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

/* library.c
   
   contains just about everything needed to set up a library in
   a simple way.

   Created in 1992 by Gresolle@genesis, aka Kristian Wiklund 

   set_save(i)               - enable saving of data if i is true
                               saving is turned off by default
   set_lib_name(name)	     - set the name of the library. displayed
                               in long descr. of books & in book list
   set_borrow_cmd(cmd)       - set command used by player to borrow
                               a book. default is 'borrow'.
   set_return_cmd(cmd)       - set command used by player to return
                               a book. default is 'return'.
   set_list_cmd(cmd)         - set command used by player to list
                               the books in the library, default 'list'
   set_book_type(type)       - set the type of book the books are. (?)
                               (scroll, book...) default is 'book'
   set_save_path(path)       - set the path to the savefile
                               setting the path autoenables saving
                               of the library data
   lib_exit(room,direction)  - create an exit that prevents the
                               player from leaving with a book
   create_library()          - set up the library. as create_room()
   borrow(book)              - borrows a book to this_player()
   return_it(book)           - return book from this_player()
   remove_book(name)         - remove the book 'name' from the library
   no_lib_init(flag)         - don't do add_action:s if flag = 1
                               useful if you wish to redefine the
                               user interface. 0 is default.
   set_write_dir(path)       - define path to save user written books
                               in. this will automagically allow
                               bookwriting

   add_book(name,descr,path,flag) - add a book to the library.

   name   - name of the book, used when listing the contents &
            borrowing/returning books
   descr  - a long description of the book, is displayed with 'list',
            and put on the front of the book.
   path   - the path to the file containing the book data
   flag   - if 0 clone a /std/scroll & link the text file in path to it.
            if 1 clone the object 'path' and hand it to the player

   Please send bugreports/comments/ideas etc to
   gresolle - via genesis mail system or
   d1wzm@dtek.chalmers.se via internet
  
*******************************************
Typical use of the library code:

inherit "library";

create_library()
{
  set_short("gresolle's library");
  set_long("You are in Gresolle's beautiful library.\n");
  set_save_path("/d/Roke/gresolle/libsave");
  set_lib_name("Gresolle's library");
  set_book_type("scroll");
  lib_exit("/d/Roke/gresolle/workroom","west");
}

*******************************************************
note that it is possible to use Call to alter the
library dynamically, instead of using add_book in the
room code. It would of course be wise to enable saving
if you manage the library that way...

eg. 

Call here add_book realbimap%%Map over Re Albi%%/d/Roke/common/gont/re/MAP%%0

adds a book called 'realbimap', description 'Map over Re Albi',
path /d/Roke/common/gont/re/MAP, that is a text file. Note that NO
testing of the path is performed. If you are stupid enough to add
a non-existant path, you can have the errors for free.

Call here remove_book realbimap

removes the book that was added above.
Autosaving is performed, if saving is enabled, when add_book & remove_book
are called. BTW, spaces are of course OK in the book names.

This should be all... If I have left out something, drop me a line...
****************************************************/

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>

/* 
 * globals
 */

string *names, *paths, *descrs;
static string savepath, libnam, borrowcmd, returncmd, booktype, listcmd;
static string writepath, nbnam, nbdesc, fnam, librarian_room;
int *flags, nrofbooks, bnr;
static int saveflag, noinit, writeallow, busy, secure_add;

/*
 * prototypes
 */

public void set_save(int i);

/*
 *  defines, BORROWED_BOOK - prop set in player when borrowing book 
 */

#define BORROWED_BOOK "borrowed_from_"
#define TP this_player()
#define NF notify_fail
#define TO this_object()

/* Function: set_librarian_room()
 * Description: set a room for use as the librarians office
 *              Automatically sets secure_add
 */
void
set_librarian_room(string room)
{
    librarian_room = room;
    secure_add = 1;
}

/* Function: set_write_dir
 * Description: select a path to save player written books in
 * Arguments: path
 */
void
set_write_dir(string s)
{
    writeallow = 1;
    writepath = s;
}

/* Function:    no_lib_init
 * Description: if given 1 as argument, the init() of the libcode doesn't
 *              add any commands to the user
 * Arguments:   flag, 0 to enable add_action:s in init, 1 to disable
 */
public void
no_lib_init(int flag)
{
    noinit = flag;
}

/* Function:    remove_book
 * Description: removes the book 'book' from the library
 * Arguments:   book, the name of the book to remove
 */
public void
remove_book(string book)
{
    int i, j;


    /* empty library... cannot remove things */

    if (!nrofbooks)
    {
        TP->catch_msg("But the library is empty!\n");
        return;
    }

    /* scan through list, add all items to templist EXCEPT the book(s)
       named 'book' */

    j = -1;

    for (i = 0; i < nrofbooks; i++)
        if (names[i] == book)
            j = i;

    /* move temporary storage lists to the ordinary global ones */

    NF("There were no book in the library with that name!\n");
    if (j < 0)
        return 0;

    names = exclude_array(names, j, j);
    paths = exclude_array(paths, j, j);
    descrs = exclude_array(descrs, j, j);
    flags = exclude_array(flags, j, j);

    nrofbooks--;

    /* save if saving is enabled */

    if (saveflag)
        save_object(savepath);

}

/* Function:    set_save_path
 * Description: set the path to the library datafile
 *              calling this function enables saving
 * Arguments:   path to save in
 */
public void
set_save_path(string s)
{
    savepath = s;

    /* we enable saving of lib data when setting a savepath. if you don't
       want to save things, don't set a path! */

    set_save(1);
}

/* Function:    set_save
 * Description: select if library shall load & save a book file
 * Arguments:   true if save, false if not
 */
public void
set_save(int i)
{
    saveflag = i;
}

/* Function:    set_book_type
 * Description: selects a book type, eg "scroll" or "book"
 * Arguments:   A string containing the book type
 */
public void
set_book_type(string s)
{
    booktype = s;
}

/* Function:    set_list_cmd
 * Description: set the command used to list the contents of the library
 * Arguments:   the command to use
 */
public void
set_list_cmd(string s)
{
    listcmd = s;
}

/* Function:    set_return_cmd
 * Description: sets the command used by player to return book
 * Arguments:   the command to use
 */
public void
set_return_cmd(string s)
{
    returncmd = s;
}

/* Function:    set_borrow_cmd
 * Description: sets the command used by player to borrow book
 * Arguments:   the command to use
 */
public void
set_borrow_cmd(string s)
{
    borrowcmd = s;
}

/* Function:    set_lib_name
 * Description: sets the name of the library
 * Arguments:   libname
 */
public void
set_lib_name(string s)
{
    libnam = s;
}

/* Function:    create_library
 * Description: sets up the library
 */
public void
create_library()
{
    /* you will of course mask this one by an own function, creating
       a few cosy chairs, desks, shelves etc. */

    set_short("library");
    set_long("library\n");

}

/* Function:    create_room
 * Description: initialize the library room, set up some defaults etc
 *              will call create_library() during setup
 */
public nomask void
create_room()
{
    nrofbooks = 0;
    busy = 0;
    bnr = 0;
    set_lib_name("the old and ancient Genesis library");

    set_borrow_cmd("borrow");
    set_return_cmd("return");
    set_list_cmd("list");

    set_book_type("book");

    set_save(0);                /* no save */

    no_lib_init(0);             /* use the predefined user cmd:s */

    create_library();

/* if the user has done set_save(1) in his create_library() then we'll
   reload all data we have previously stored */

    if (saveflag)
        restore_object(savepath);
}

/* Function:    add_book
 * Description: add a book to the library
 * Arguments:   book name, book descr, book path, flag
 *              flag = 0 if book path points against text file,
 *              flag = 1 if book path points against object to clone
 */
public void
add_book(string name, string descr, string path, int flag)
{
    int i, tt;
    string t;

    /* the library is empty, then initialize lists with given values */


    if (!nrofbooks)
    {
        names = ({name});
        paths = ({path});
        descrs = ({descr});
        flags = ({flag});
    }
    else
        /* else link the stuff in at correct places in the lists */
    {
        names += ({name});
        paths += ({path});
        descrs += ({descr});
        flags += ({flag});

        /* sort the arrays */

        for (i = nrofbooks; i > 0; i--)
            if (names[i - 1] > names[i])
            {
                t = names[i - 1];
                names[i - 1] = names[i];
                names[i] = t;

                t = paths[i - 1];
                paths[i - 1] = paths[i];
                paths[i] = t;

                t = descrs[i - 1];
                descrs[i - 1] = descrs[i];
                descrs[i] = t;

                tt = flags[i - 1];
                flags[i - 1] = flags[i];
                flags[i] = tt;
            }
    }

    /* increase amount of books in the library */

    nrofbooks++;

    /* at last we save if saveflag is true */

    if (saveflag)
        save_object(savepath);
}

/* Function:    lib_exit
 * Description: add an exit that checks if the book has been returned
 * Arguments:   roompath, direction
 */
public void
lib_exit(string path, string direction)
{
    add_exit(path, direction, "@@libblock");
}

/* Function:    libblock
 * Description: check if a player tries to steal a book
 * Returns:     0 if no thief, 1 if he tries to walk away with a book
 */
public nomask int
libblock()
{
    if (TP->query_prop(BORROWED_BOOK + libnam))
    {
        TP->catch_msg(
            "The librarian won't let you pass until you return the " +
            booktype + ".\n");

        return 1;
    }
    return 0;
}

/* Function:     init
 * Description:  set up add_action:s
 */
void
init()
{
    ::init(); /* set up standard stuff, exits etc, then init localcmds */

    if (!noinit)
    {
        add_action("borrow", borrowcmd);
        add_action("return_it", returncmd);
        add_action("list", listcmd);
        if (writeallow && saveflag)
            add_action("write_book", "write");
    }
}

/* Function:     write_book
 * Description:  let the player write a book and add it to the library
 * Arguments:    what the player wants to write, should match the book type
 */
int
write_book(string s)
{
    notify_fail("Write what?\n");
    if (s != booktype)
        return 0;

    notify_fail("Someone is already writing a " + booktype + "!\n");
    if (busy)
        return 0;

    busy = 1;

    write("Please enter the name of your " + booktype + " (one word) : ");

    input_to("getbookname");
    return 1;
}

void
getbookname(string s)
{
    nbnam = s;

    write("Please enter a short description of the " + booktype + ": ");
    input_to("getbookdesc");
}

void
getbookdesc(string s)
{
    nbdesc = s;

    write("Enter the contents of the book (** to finish, ~q to abort):\n");

    fnam = writepath + "/book" + bnr;
    rm(fnam);
    bnr++;
    write(">");
    input_to("writebook");
}

void
writebook(string s)
{
    if (s == "**")
    {
        write_file(fnam, "\nWritten by " +
                   capitalize(this_player()->query_real_name()) +
                   ".\n");
        busy = 0;
        if (!secure_add)
        {
            write("You finish your " + booktype +
                  " and put it on one of the shelves.\n");
            add_book(nbnam, nbdesc, fnam, 0);
        }
        else
        {
            librarian_room->add_book(nbnam, nbdesc, fnam, 0);
            write("You drop your masterpiece in the librarian's mailbox.\n");
            save_object(savepath);
        }

        say(QCTNAME(this_player()) + " finishes a " + booktype +
            " and adds it to the library.\n");
        /* finish book */
    }
    else if (s == "~q")
    {
        write("You abort your writing.\n");
        say(QCTNAME(this_player()) + " stops writing and throws the " +
            booktype +
            " away.\n");
        /* abort book */
        bnr--;
        busy = 0;
        save_object(savepath);
    }
    else
    {
        write(">");
        write_file(fnam, s + "\n");
        input_to("writebook");
    }
}

/* Function:     borrow
 * Description:  hands out the book s to the player
 * Arguments:    s, the book to borrow
 */
int
borrow(string s)
{
    int i, j;
    object ob;

    /* check if player already has a borrowed book */

    NF("You must return the previous " + booktype + " you borrowed first!\n");
    if (TP->query_prop(BORROWED_BOOK + libnam))
        return 0;

    j = -1;

    /* check lists to see if lib is empty */

    NF("The library is currently empty!\n");
    if (!nrofbooks)
        return 0;

    /* scan through the lists for the wanted book */

    NF("The librarian couldn't find that " + booktype + ".\n");

    for (i = 0; i < nrofbooks; i++)
        if (lower_case(names[i]) == lower_case(s))
            j = i;

    /* if j=-1 we didn't find it in the library */

    if (j < 0)
        return 0;

    /* success, clone a book and give it to player */

    say(QCTNAME(TP) + " borrows a " + booktype + ".\n");
    write("The librarian gives you a " + booktype + ".\n");

    /* if flags[j] != 0 it's a clonable object we have a path to... */

    if (flags[j])
    {
        ob = clone_object(paths[j]);  /* clone it and give it to player */
        ob->move(TP);
    }
    else
        /* we have a text file, create a scroll and set it up... */
    {
        ob = clone_object("/std/scroll");
        ob->set_long("A " + booktype + ", " + names[j] + ", borrowed from " +
                     libnam +
                     ".\n" + "On the front is written: " + descrs[j] + ".\n" +
                     "You can 'read' or 'mread' it.\n");
        ob->set_short(booktype);
        ob->set_name(booktype);
        ob->add_name(s);
        ob->set_file(paths[j]);
        ob->move(TP);
    }

    /* prevent the player from giving the book to someone */

    ob->add_prop(OBJ_I_NO_DROP, 1);

    /* mark the player as having borrowed a book. note that the object ptr
       of the book is stored in the property */

    TP->add_prop(BORROWED_BOOK + libnam, ob);

    return 1;
}

/* Function:     return_it
 * Description:  let the player return a borrowed book
 */
public int
return_it(string s)
{

    /* first we check if the player really mean us when he typed return.
       test if s is booktype or he has an item called s. we brutally suppose
       that if he holds an item called s AND has borrowed a book he wants
       to return s and that s is a book. perhaps one could test for it,
       but what the... */

    NF("What do you want to return?\n");
    if (!strlen(s))
        return 0;

    if (s != booktype && !present(s, TP))
        return 0;

    /* test if the player really did borrow something from us */

    NF("But you havn't borrowed any " + booktype + "!\n");
    if (!(TP->query_prop(BORROWED_BOOK + libnam)))
        return 0;

    /* if he has, remove 1. the book, 2. the property */

    (TP->query_prop(BORROWED_BOOK + libnam))->remove_object();
    TP->remove_prop(BORROWED_BOOK + libnam);

    TP->catch_msg("You return the " + booktype + ".\n");
    say(QCTNAME(TP) + " returns a " + booktype + ".\n");

    return 1;
}

/* Function:     list
 * Description:  let the player list the contents of the library
 */
public int
list()
{
    int i, j;

    /* catch an empty library */

    NF("The library is empty!\n");
    if (!nrofbooks)
        return 0;

    TP->catch_msg(
                     "The " + booktype + "s you can borrow in " + libnam +
                     " are:\n");

    for (i = 0; i < nrofbooks; i++)
    {
        TP->catch_msg(names[i]);

        for (j = 0; j < (20 - strlen(names[i])); j++)
            TP->catch_msg(" ");

        TP->catch_msg(descrs[i] + "\n");
    }
    return 1;
}
