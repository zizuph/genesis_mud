/* library.c
   
   contains just about everything needed to set up a library in
   a simple way.

   Created in 1992 by Gresolle@genesis, aka Kristian Wiklund 
   Modified in 1995 by Olorin@Genesis

   Modified Sep. 12th 1997, by Elessar:
        Added the function remove_book_no so that a entry with a buggy name
        that could not be fixed in any other ways could be removed
        by index number instead. Used data_edit to find the number,
        but according to Mercade, data_edit could not fix the entry.
   Modified March 20 1998 by Mercade, added the 'tail' command.

   set_library_name(name)    - set the name of the library. displayed
                               in long descr. of books & in book list
   set_borrow_cmd(cmd)       - set command used by player to borrow
                               a book. default is 'borrow'.
   set_return_cmd(cmd)       - set command used by player to return
                               a book. default is 'return'.
   set_list_cmd(cmd)         - set command used by player to list
                               the books in the library, default 'list'
   set_read_cmd(cmd)         - set command used by player to read
                               the books in the library without having
                               to borrow them. If not set, books have
                               to be borrowed. This is the default.
   set_book_type(type)       - set the type of the books.
                               (scroll, book...) default is 'book'
   set_save_path(path)       - set the path to the savefile
                               setting the path autoenables saving
                               of the library data
   set_up_library()          - set up the library, call from create_room().
   do_borrow(book)           - borrows a book to this_player()
   do_return(book)           - return book from this_player()
   do_read(book)             - read a book
   do_list()                 - list the titles in the library
   remove_book(name)         - remove the book 'name' from the library
   set_write_dir(path)       - define path to save user written books
                               in. this will automagically allow
                               bookwriting
   set_librarian_room        - set the room to administrate the library

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

#pragma save_binary

inherit "library";

void
create_room()
{
  set_short("gresolle's library");
  set_long("You are in Gresolle's beautiful library.\n");
  set_save_path("/d/Earthsea/gresolle/libsave");
  set_library_name("Gresolle's library");
  set_book_type("scroll");
  set_up_library();
  add_exit("/d/Earthsea/gresolle/workroom","west", "@@lib_check");
}

void
init()
{
    ::init();
    init_library();
}

*******************************************************
note that it is possible to use Call to alter the
library dynamically, instead of using add_book in the
room code. It would of course be wise to enable saving
if you manage the library that way...

eg. 

Call here add_book realbimap%%Map over Re Albi%%/d/Earthsea/common/gont/re/MAP%%0

adds a book called 'realbimap', description 'Map over Re Albi',
path /d/Earthsea/common/gont/re/MAP, that is a text file. Note that NO
testing of the path is performed. If you are stupid enough to add
a non-existant path, you can have the errors for free.

Call here remove_book realbimap

removes the book that was added above.
Autosaving is performed, if saving is enabled, when add_book & remove_book
are called. BTW, spaces are of course OK in the book names.

This should be all... If I have left out something, drop me a line...

****************************************************
Minor modifications by Olorin of Gondor:
- Removed inherit room.
- Removed TP, NF, TO definitions
- Moved initialization of global variables to the declaration statements.
- Removed function create_library().
- Renamed function create_room() to set_up_library().
- Removed global variable writeallow (replaced by check on writepath).
- Removed global variable saveflag (replaced by check on savepath).
- Replaced init() by init_library() to be called by room.
- use new editor /obj/edit.c

- modified for use of function variables. Oct 1995

****************************************************/
/* The code starts here. */

#pragma strict_types

inherit "/d/Gondor/common/lib/tail.c";

#include <files.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

// Definitions
// BORROWED_BOOK - prop set in player when borrowing book
#define BORROWED_BOOK		"borrowed_from_"
#define PLAYER_I_WRITING_BOOK	"_player_i_writing_book"
#define CLOCK			"/d/Gondor/common/obj/clock"
#define BOOK_OBJ                   "/std/scroll"

// Prototypes
public int      do_borrow(string s);
public int      do_list(string s);
public int      do_read(string str);
public int      do_return(string s);
public int      do_tail(string str);
public void     get_book_desc(string s);
public void     get_book_name(string s);
public int      remove_book(string name);
public int      write_book(string s);

// Global variables
       string *names = ({ }),		// the book titles
              *paths = ({ }),
              *descrs = ({ });
static string  savepath = 0,
               log_file = "library",
               libnam = "the old and ancient Genesis library",
               borrowcmd = "borrow",
               returncmd = "return",
               readcmd = 0,
               booktype = "book",
               listcmd = "list";
static string  writepath = 0,
               nbnam,			// name of a new book
               nbdesc,			// desc of a new book
               fnam,
               librarian_room;
       int    *bflags = ({ }),
               bnr = 0;
static int     busy = 0,
               secure_add = 0;

/*
 * Function name: set_librarian_room
 * Description:   set a room for use as the librarian's office
 *		  automatically sets secure_ad
 * Arguments:	  string room: the librarian's office
 * Returns:	  0
 */
void
set_librarian_room(string room)
{
    librarian_room = room;
    secure_add = 1;
}

int query_secure_add(object pl) { return secure_add; }

/*
 * Function name: set_write_dir
 * Description:   select a path to save player written books in
 * Arguments:	  the path
 * Returns:	  1 if path exists and is set, 0 else
 */
int
set_write_dir(string s)
{
    if (!strlen(s) || file_size(s) != -2)
        return 0;

    writepath = s;
    return 1;
}

string query_write_dir() { return writepath; }

/*
 * Function name: set_log_file
 * Description:   set the file to log actions in the library
 * Arguments:	  the log file
 * Returns:	  0
 */
void
set_log_file(string s)
{
    if (strlen(s))
        log_file = s;
}

/*
 * Function name: query_remove_priv
 * Description:   Redefine this if players should be able to remove
 *		  books from the library
 * Arguments:	  pl - the player object
 * Returns:	  1 if the player can remove books, 0 else
 */
int
query_remove_priv(object pl)
{
    return 0;
}

int
lib_hook_no_remove_priv()
{
    notify_fail("You are not allowed to remove any books here!\n");
    return 0;
}

int
lib_hook_lib_empty()
{
    notify_fail("The library is currently empty.\n");
    return 0;
}

int
lib_hook_remove_fail_empty()
{
    notify_fail("But the library is empty!\n");
    return 0;
}

int
lib_hook_remove_no_name()
{
    notify_fail("There is no book with that name in the library!\n");
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
    int    j;

    if (!query_remove_priv(this_player()))
        return lib_hook_no_remove_priv();

    // empty library... cannot remove things
    if (!sizeof(names))
        return lib_hook_remove_fail_empty();

    name = capitalize(lower_case(name));

    // scan through list, find book 'name'
    if ((j = member_array(name, names)) < 0)
       return lib_hook_remove_no_name();

    seteuid(getuid());
    log_file(log_file, "LIBRARY: "+this_player()->query_name()
      + " removed the book " + names[j] + " (" + descrs[j]
      + ") on " + ctime(time()) + ".\n");
    write("You remove the "+booktype+" with the title \""+descrs[j]
      + "\" from the shelves.\n");
    say(QCTNAME(this_player()) + " removes "+LANG_ADDART(booktype)
      + " from the shelves.\n");

    names  = exclude_array(names, j, j);
    paths  = exclude_array(paths, j, j);
    descrs = exclude_array(descrs, j, j);
    bflags = exclude_array(bflags, j, j);

    // save if saving is enabled
    if (strlen(savepath))
        save_object(savepath);

    return 1;
}

public int
remove_book_no(int n)
{
    if (!query_remove_priv(this_player()))
        return lib_hook_no_remove_priv();

    if (!sizeof(names))
        return lib_hook_remove_fail_empty();

    if (n < 0)
    {
        notify_fail("Must be bigger than or equal to zero.");
        return 0;
    }

    if (sizeof(names) <= n)
        return lib_hook_remove_no_name();

    seteuid(getuid());
    log_file(log_file, "LIBRARY: "+this_player()->query_name()
      + " removed the book "+ names[n] + " (" + descrs[n]
      + ") on " + ctime(time()) + ".\n");
    write("You remove the "+booktype+" with the title \""+descrs[n]
      + "\" from the shelves.\n");

    names = exclude_array(names, n, n);
    paths = exclude_array(paths, n, n);
    descrs = exclude_array(descrs, n, n);
    bflags = exclude_array(bflags, n, n);
    if (strlen(savepath))
        save_object(savepath);

    return 1;
}


/*
 * Function name: set_save_path
 * Description:   set the path to the library datafile
 *		  calling this function enables saving
 * Arguments:	  s - path to save in
 * Returns:	  1 on success
 */
public int
set_save_path(string s)
{
    if (!strlen(s))
        return 0;

    savepath = s;
    return 1;
}

public string query_save_path() { return savepath; }

/*
 * Function name: set_book_type
 * Description:   selects a book type, eg "scroll" or "book"
 * Arguments:	  s - a string containing the book type
 * Returns:	  0
 */
public void
set_book_type(string s)
{
    if (strlen(s))
        booktype = s;
}

/*
 * Function name: set_list_cmd
 * Description:   set the command used to list the contents of the
 *                library
 * Arguments:	  s - the command verb to use
 * Returns:	  0
 */
public void
set_list_cmd(string s)
{
    if (strlen(s))
        listcmd = s;
}

/*
 * Function name: set_return_cmd
 * Description:   sets the command used by player to return book
 * Arguments:	  s - the command verb to use
 * Returns:	  0
 */
public void
set_return_cmd(string s)
{
    if (strlen(s))
        returncmd = s;
}

/*
 * Function name: set_borrow_cmd
 * Description:   sets the command used by player to borrow book
 * Arguments:	  s - the command verb to use
 * Returns:	  0
 */
public void
set_borrow_cmd(string s)
{
    if (strlen(s))
        borrowcmd = s;
}

/*
 * Function name: set_read_cmd
 * Description:   sets the command used by player to read a book
 *		  (without borrowing it)
 * Arguments:	  s - the command verb to use
 * Returns:	  0
 */
public void
set_read_cmd(string s)
{
    if (strlen(s))
        readcmd = s;
}

/*
 * Function name: set_library_name
 * Description:   sets the name of the library
 * Arguments:	  s - the name
 * Returns:	  0
 */
public void set_library_name(string s) { libnam = s; }
public string query_library_name() { return libnam; }

/*
 * Function name: set_up_library
 * Description:   initialize the library room, set up some defaults etc
 * Arguments:	  none
 * Returns:	  0
 */
public nomask void
set_up_library()
{
    seteuid(getuid());
    if (strlen(savepath))
        restore_object(savepath);
}

/*
 * Function name: add_book
 * Description:   add a book to the library
 * Arguments:	  name - the name of the book
 *                descr - the description of the book
 *                path - the path to either the text file or the
 *                       object file for the book
 *                flag = 0 if path points at text file,
 *                flag = 1 if path points at object file to clone.
 * Returns:	  0
 */
public void
add_book(string name, string descr, string path, int flag)
{
    int     i, tt;
    string  t;

    name = capitalize(lower_case(name));
    names += ({ name });
    paths += ({ path });
    descrs += ({ descr });
    bflags += ({ flag });

    // sort the arrays
    for (i = (sizeof(names)-1); i > 0; i--)
        if(names[i-1] > names[i])
        {
            t = names[i-1];
            names[i-1] = names[i];
            names[i] = t;

            t = paths[i-1];
            paths[i-1] = paths[i];
            paths[i] = t;

            t = descrs[i-1];
            descrs[i-1] = descrs[i];
            descrs[i] = t;

            tt = bflags[i-1];
            bflags[i-1] = bflags[i];
            bflags[i] = tt;
        }

    // at last we save if a path was set
    if (strlen(savepath))
        save_object(savepath);
}

/*
 * Function name: lib_check
 * Description:   check if a player tries to steal a book
 * Arguments:	  none
 * Returns:	  0 if no thief, 1 if he tries to walk away with a book
 */
public nomask int
lib_check()
{
    if (this_player()->query_prop(BORROWED_BOOK+libnam))
    {
        this_player()->catch_msg(
            "The librarian won't let you pass until you return the "
          + booktype + ".\n");
        return 1;
    }
    return 0;
}

/*
 * Function name: query_write_priv
 * Description:   if the player is allowed to write books
 * Arguments:	  pl - plyaer object
 * Returns:	  1 if player is allowed to write books, 0 else
 */
int
query_write_priv(object pl)
{
    return 1;
}

/*
 * Function name: init_library
 * Description:   set up actions, to be called from init()
 * Arguments:	  none
 * Returns:	  0
 */
void
init_library()
{
    add_action(do_borrow, borrowcmd);
    if (strlen(readcmd))
        add_action(do_read, readcmd);
    add_action(do_return, returncmd);
    add_action(do_list,   listcmd);
    if (strlen(writepath) && strlen(savepath))
        add_action(write_book, "write");
    add_action(remove_book, "remove");
    add_action(do_tail, "tail");
}

int
lib_hook_no_write_priv()
{
    notify_fail("You are not entitled to write a new "+booktype+" here!\n");
    return 0;
}

int
lib_hook_busy_write()
{
    notify_fail("Someone is already writing a "+booktype+"!\n");
    return 0;
}

void
lib_hook_query_name()
{
    write("Please enter the name of your "+booktype+" (one word, no commas) : ");
}

/*
 * Function name: write_book
 * Description:   let the player write a book and add it to the library
 * Arguments:	  s - what the player wants to write, should match the
 *                book type
 * Returns:	  1 if success, 0 else
 */
public int
write_book(string s)
{
    if (s != booktype)
    {
        notify_fail("Write what?\n");
        return 0;
    }

    if (!query_write_priv(this_player()))
        return lib_hook_no_write_priv();

    if (busy)
        return lib_hook_busy_write();

    busy = 1;

    lib_hook_query_name();

    input_to(get_book_name);
    return 1;
}

void
lib_hook_query_desc()
{
    write("Please enter a short description of the "+booktype+": ");
}

void
lib_hook_book_exist()
{
    write("There is already a "+booktype+" with that name!\n");
}

/*
 * Function name: get_book_name
 * Description:   input the name of the book
 * Arguments:	  s - the name
 * Returns:	  0
 */
public void
get_book_name(string s)
{
    string	tmp1, tmp2;
    if (!strlen(s))
    {
        lib_hook_query_name();
        input_to(get_book_name);
        return;
    }
    /* look for space, tab, comma */
    if ( sscanf(s, "%s,%s", tmp1, tmp2) ||
    sscanf(s, "%s %s", tmp1, tmp2) ||
    sscanf(s, "%s	%s", tmp1, tmp2) )
    {
	write("The name may not contain spaces, tabs or commas.\n");
        lib_hook_query_name();
        input_to(get_book_name);
        return;
    }

    nbnam = capitalize(lower_case(s));

    if (member_array(nbnam, names) >= 0)
    {
        lib_hook_book_exist();
        busy = 0;
        nbnam = 0;
        return;
    }

    lib_hook_query_desc();
    input_to(get_book_desc);
}

string
lib_hook_book_intro(string s, object p)
{
    return "\n"
        + break_string(capitalize(s) + ", written by "
        + p->query_name()
        + " on " + CLOCK->query_date_s() + ".\n", 75);
}

/*
 * Function name: get_book_desc
 * Description:   input the book description
 * Arguments:	  s - the description
 * Returns:	  0
 */
public void
get_book_desc(string s)
{
    string  intro;

    if (!strlen(s))
    {
        lib_hook_query_desc();
        input_to(get_book_desc);
        return;
    }

    nbdesc = s;

    this_player()->add_prop(PLAYER_I_WRITING_BOOK, 1);

    intro = lib_hook_book_intro(s, this_player());

    setuid();
    seteuid(getuid());

    clone_object(EDITOR_OBJECT)->edit("done_writing", intro, 3);
    return;
}

void
lib_hook_finish_book(int sec)
{
    if (sec)
        write("You drop your masterpiece into the librarian's mailbox.\n");
    else
        write("You finish your "+booktype
          + " and put it onto one of the shelves.\n");
    say(QCTNAME(this_player())+" finishes a "+booktype
      + " and adds it to the library.\n");
}

/*
 * Function name: done_writing
 * Description:   write the text of the book
 * Arguments:	  str - the text
 * Returns:	  0
 */
void
done_writing(string str)
{
    string  msg;

    busy = 0;

    if (!strlen(str))
    {
        write("You abort the writing of the new "+booktype+".\n");
        return;
    }

    fnam = writepath + "/book" + bnr;
    rm(fnam);
    bnr++;
    write_file(fnam, str);

    if (!query_secure_add(this_player()))
    {
        lib_hook_finish_book(0);
        add_book(nbnam, nbdesc, fnam, 0);
        log_file(log_file, "LIBRARY: "+this_player()->query_name()
          + " added the book " + nbnam + " (" + nbdesc
          + ") on " + ctime(time()) + ".\n");
        if (stringp(savepath))
            save_object(savepath);
    }
    else
    {
        seteuid(getuid());
        if (stringp(msg = librarian_room->add_book(nbnam, nbdesc, fnam, 0)))
        {
            notify_fail(msg);
            return 0;
        }
        lib_hook_finish_book(1);
        save_object(savepath);
    }
}

int
lib_hook_borrow_fail_return()
{
    notify_fail("You must first return the previous " + booktype
      + " you have borrowed!\n");
    return 0;
}

int
lib_hook_borrow_fail_empty()
{
    notify_fail("The library is currently empty!\n");
    return 0;
}

int
lib_hook_borrow_fail_find()
{
    notify_fail("The librarian couldn't find that "+booktype+".\n");
    return 0;
}

void
lib_hook_borrow_fail_move()
{
    write("The librarian tries to give you a "+booktype+" but fails.\n"
        + "The librarian says: But you cannot carry the "+booktype+"!\n");
    say(QCTNAME(this_player())+" tries to borrow a "+booktype+" but fails.\n");
}

void
lib_hook_borrow_move()
{
    write("The librarian gives you a "+booktype+".\n");
    say(QCTNAME(this_player())+" borrows a "+booktype+".\n");
}

/*
 * Function name: do_borrow
 * Description:   let the player borrow a book
 * Arguments:	  s - the name of the book to borrow
 * Returns:	  1 if success, 0 else
 */
public int
do_borrow(string s)
{
    int     j;
    object  ob;
  
    if (!strlen(s))
    {
        notify_fail("Borrow which book?\n");
        return 0;
    }

    // check if player already has a borrowed book
    if (this_player()->query_prop(BORROWED_BOOK+libnam))
        return lib_hook_borrow_fail_return();

    s = capitalize(lower_case(s));

    // check lists to see if lib is empty
    if (!sizeof(names))
        return lib_hook_borrow_fail_empty();

    // scan through the lists for the wanted book
    if ((j = member_array(s, names)) < 0)
        return lib_hook_borrow_fail_find();

    // success, clone a book and give it to player
    if (bflags[j]) // it's a clonable object we have a path to...
    {
        ob = clone_object(paths[j]);
    }
    else // we have a text file, create a scroll and set it up...
    {
        ob = clone_object(BOOK_OBJ);
        ob->set_long("A "+booktype+", "+s+", borrowed from "+libnam
          + ".\n"+"On the front is written: "+descrs[j]+".\n"
          + "You can 'read' or 'mread' it.\n");
        ob->set_short(booktype);
        ob->set_name(booktype);
        ob->add_name(s);
        ob->set_file(paths[j]);
    }

    if (ob->move(this_player()))
    {
        lib_hook_borrow_fail_move();
        ob->remove_object();
        return 1;
    }
    else
        lib_hook_borrow_move();

    // prevent the player from giving the book to someone
    ob->add_prop(OBJ_I_NO_DROP,1);

    // mark the player as having borrowed a book. note that the object ptr
    // of the book is stored in the property
    this_player()->add_prop(BORROWED_BOOK+libnam,ob);

    return 1;
}

int
lib_hook_return_fail()
{
    notify_fail("What do you want to return?\n");
    return 0;
}

int
lib_hook_return_not_borrowed()
{
    notify_fail("But you havn't borrowed any " + booktype + "!\n");
    return 0;
}

void
lib_hook_return()
{
    this_player()->catch_msg("You return the "+booktype+".\n");
    say(QCTNAME(this_player())+" returns a "+booktype+".\n");
}

/*
 * Function name: do_return
 * Description:   let the player return a borrowed book
 * Arguments:	  s - name of the book
 * Returns:	  1 if success, 0 else
 */
public int
do_return(string s)
{
    if (!strlen(s))
        return lib_hook_return_fail();

    if (s != booktype && !present(s,this_player()))
        return lib_hook_return_fail();
 
    // test if the player really did borrow something from us
    if (!(this_player()->query_prop(BORROWED_BOOK+libnam)))
        return lib_hook_return_not_borrowed();

    // if he has, remove 1. the book, 2. the property
    (this_player()->query_prop(BORROWED_BOOK+libnam))->remove_object();
    this_player()->remove_prop(BORROWED_BOOK+libnam);

    lib_hook_return();

    return 1;
}

int
lib_hook_list_fail()
{
    notify_fail("List what? The titles in the library perhaps?\n");
    return 0;
}

/*
 * Function name: do_list
 * Description:   let the player list the contents of the library
 * Arguments:	  s - argument of the command
 * Returns:	  1 if success, 0 else
 */
public int
do_list(string s)
{
    int i, j;
    string  txt;

    if (strlen(s) && (s != "titles"))
        return lib_hook_list_fail();

    // catch an empty library
    if (!sizeof(names))
        return lib_hook_lib_empty();

    txt = "These are the "+LANG_PWORD(booktype)+" you can borrow in "
      + libnam+":\n";

    for (i = 0; i < sizeof(names); i++)
        txt += sprintf("%-20s %-55s\n", names[i], descrs[i]);

    this_player()->more(txt);
    return 1;
}

int
lib_hook_read_fail_find()
{
    notify_fail("You cannot find that "+booktype+".\n");
    return 0;
}

void
lib_hook_read(int j, object p)
{
    write("You read the "+booktype+" titled \""
      + capitalize(descrs[j])+"\".\n");
    say(QCTNAME(p)+" reads a "+booktype+" "+p->query_pronoun()
      + " found in the shelves.\n",p);
}

/*
 * Function name: do_read
 * Description:   let the player read a book (w/o having to borrow it)
 * Arguments:	  str - argument of the command
 * Returns:	  1 if success, 0 else
 */
public int
do_read(string str)
{
    int     j;
    object  tp = this_player();

    if (!strlen(str))
    {
        notify_fail("Read which book?\n");
        return 0;
    }

    str = capitalize(lower_case(str));

    // check lists to see if lib is empty
    if (!sizeof(names))
        return lib_hook_lib_empty();

    // scan through the lists for the wanted book
    if ((j = member_array(str, names)) < 0)
        return lib_hook_read_fail_find();

    lib_hook_read(j, tp);
    if (file_size(paths[j]) > 1000)
#if 0
        this_player()->more(paths[j], 1);
#else
	this_player()->more(read_file(paths[j]), 0);
#endif
    else
        cat(paths[j]);
    return 1;
}

/*
 * Function name: do_tail
 * Description  : Allow the player to tail the book without having to=
 *                borrow it.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
public int
do_tail(string str)
{
    int index;

    if (!strlen(str))
    {
        notify_fail("Tail which book?\n");
        return 0;
    }

    /* Check the lists to see whether the lib is empty. */
    if (!sizeof(names))
    {
        return lib_hook_lib_empty();
    }

    /* scan through the lists for the wanted book */
    str = capitalize(lower_case(str));
    if ((index = member_array(str, names)) < 0)
    {
        return lib_hook_read_fail_find();
    }

    lib_hook_read(index, this_player());
    tail_file(paths[index]);
    return 1;
}

string *
query_names()
{
    return names;
}
