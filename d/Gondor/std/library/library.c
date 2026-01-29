/* 
 * /d/Gondor/std/library/library.c
 *
 * A std library for general purposes.
 * 
 * Aridor, 10/96
 *
 * update history:
 * Aridor 05/97: various fixes
 * Aridor 05/97: added later editing of the book (not finished yet)
 * Aridor 11/97: finished editing of an already present book
 *
 * Allows the employment of a librarian to sort the books,
 * and different levels of accessability to the library.
 *
 * Usage Example:
 * --------------
 * void
 * create_room()
 * {
 *     // Standard room setup
 *     ...
 *
 *     // Library setup
 *     set_lib_id("ranger_lib_id");
 *     set_lib_path("/d/Gondor/common/guild/library");
 *     set_default_topics((["General":0,"Rangers Private":2]));
 *     set_lib_type(4);
 *     set_search_delay(6.7);
 *     set_max_librarian_num(1);
 *     setup_library();
 * }
 *
 * void
 * init()
 * {
 *     ::init();
 *     init_library();
 * }
 *
 * void
 * leave_inv(object player, object dest);
 * {
 *     library_leave_inv(player, dest);
 *     ::leave_inv(player, dest);
 * }
 *
 */
#include "lib.h"

string *gLibrarian =({});
int gMaxLibNum = 1;

/* gTopics uses the form: <topic>:<access level>
 * The number means: 0: Everyone has access
 *                   1: Librarian only
 *                 <n>: Special group only
 */
mapping gTopics = (["New Arrivals":1,
		   "Books":0,
		   "Trash":1]);

/* gBooks uses the form: <booktitle>:({<Full title>,<shelf/topic>,<author>}) */
mapping gBooks = ([]);

string gLibPath = 0;
string gLibId   = "my_lib_id";
string gLibLong = "great library";
float  gSearchDelay = 5.0;
int gLibType = 0;

static string gOldTitle;
static string gBookToChange;
static string* gToDelete = ({});
static string* gCurrentlyBorrowed = ({});
static string gBookfile = BOOK;

#define BOOKLIST   m_indexes(gBooks)
#define TOPICLIST  m_indexes(gTopics)

/* Prototype */
nomask int catalog(string str);
nomask int check_librarian(string who);

/*
 * Function name: set_book_file
 * Description  :
 * Arguments    : string file - the file to set it to
 */
public void
set_book_file(string file)
{
    gBookfile = file;
}

/*
 * Function name: set_default_topics
 * Description  : Sets the default shelf topics
 * Arguments    : mapping tpc - the topic to set
 */
public void
set_default_topics(mapping tpc)
{
    gTopics = tpc;
    if (member_array("New Arrivals", TOPICLIST) == -1)
        gTopics += (["New Arrivals" : 1]);

    if (member_array("Trash", TOPICLIST) == -1)
        gTopics += (["Trash" : 1]);
}

/*
 * Function name: set_lib_type
 * Description  : Set the library type. The following are the options:
 *                0: allows borrowing of books
 *                1: allows writing new books
 *                2: employs a librarian
 *                4: appointed librarian
 * Arguments    : The type to set
 */
public void
set_lib_type(int id)
{
    gLibType = id;
}

/*
 * Function name: set_lib_id
 * Description  : Set a unique id for your library.
 * Arguments    : string id - the id to set
 */
public void
set_lib_id(string id)
{
    gLibId = id;
}

/*
 * Function name: set_lib_long
 * Description  : Set the name of the library
 * Arguments    : string id - the name
 */
public void
set_lib_long(string id)
{
    gLibLong = id;
}

/*
 * Function name: set_lib_path
 * Description  : Set the library's path.
 * Arguments    : string path - the pathname
 */
public void
set_lib_path(string path)
{
    if (!path || !strlen(path))
        return 0;

    if (path[strlen(path)-1..] == "/")
        gLibPath = path;
    else
        gLibPath = path + "/";
}

/*
 * Function name: set_search_delay
 * Description  : The time to delay a book search in seconds
 * Arguments    : float f - the delay
 */
public void
set_search_delay(float f)
{
    gSearchDelay = f;
}

/*
 * Function name: set_max_librarian_num
 * Description  : Set the max number of librarians possible
 * Arguments    : int i - the max
 */
public void
set_max_librarian_num(int i)
{
    gMaxLibNum = i;
}

/*
 * Function name: setup_library
 * Description  : adds the wizinfo prop and restores the saved variables
 */
public void
setup_library()
{
    seteuid(getuid(this_object()));
    restore_object(MASTER);

    this_object()->add_prop(OBJ_S_WIZINFO,
        "This is a library, derived from the standard library in Gondor. " +
        "The following options are available for wizards (apart from what " +
        "mortals can do):\n- Movebook <booktitle> to topic <topic>\n" +
        "\tto move a book from the one shelf to another shelf.\n" +
        "\tFor adding new books to the library (after using the 'blank'\n" +
        "\tcommand), use 'movebook <title> to topic <topic>'\n" +
        "\tFor throwing books into the trash use\n" +
        "\t'movebook <title> to topic trash', then\n" +
        "- Erase <booktitle>\n" +
        "\tand follow the instructions given to get rid of a book " +
        "completely.\n");
}

/*
 * Function name: hook_borrow
 * Description  : Gives the default message when the player begins a
 *                search. Redefine for your own messages.
 */
public void
hook_borrow()
{
    write("You start to search through the bookshelves, eager to find the " +
	  "book.\n");
    say(QCTNAME(this_player()) + " starts to look through the bookshelves.\n");  
}

/*
 * Function name: hook_leave_with_books
 * Description  : Gives the default messages when someone leaves
 *                with a book, based on the number of books that
 *                have been taken. Redefine this for your own messages.
 * Arguments    : object who - the borrower, int num - the number of books
 */
public void
hook_leave_with_books(object who, int num)
{
    if (num == 1)
    {
	who->catch_tell("One of the library assistants runs after you " +
            "and takes the book you didn't return.\n"); 
        tell_room(this_object(), "One of the library assistants runs after " +
            QTNAME(who) + " and returns with a book.\n", who);
    } 
    else if (num > 1) 
    {
	who->catch_tell("One of the library assistants runs after you " +
            "and takes the books you didn't return.\n"); 
	tell_room(this_object(), "One of the library assistants runs after " +
            QTNAME(who) + " and returns with some books.\n", who);
    }
}

/*
 * Function name: hook_appointed_info
 * Description  : Function called after appointing a librarian. Redefine
 *                to add any special messages or such.
 */
public void
hook_appointed_info()
{
}

/*
 * Function name: hook_librarian_requirements
 * Description  : Define the requirements for your library's 
 *                librarian here. 
 * Returns      : Return 1 if requirements met, 0 if not.
 */
public int
hook_librarian_requirements()
{
    return 1;
}

/*
 * Function name: hook_give_blank_book
 * Description  : Default message for getting a book, redefine for your own.
 * Arguments    : int state - 0: give was ok, 
 *                            1: give failed, book moved to room.
 */
public void
hook_give_blank_book(int state)
{
    say(QCTNAME(this_player()) + " takes a blank book from one of " +
        "the shelves.\n");  
    write("You take a blank book from one of the shelves.\n");

    if (state)
    {
	say("The book is too heavy for " + QTNAME(this_player()) +
            " and it falls to the ground.\n");
	write("The book is too heavy, and it falls to the ground.\n");
    }
}

/*
 * Function name: hook_find_book
 * Description  : Returns 1 if book was found, 0 if something went wrong
 *                (Player left the room, etc...)
 * Arguments    : object who - book finder
 * Returns      : See above
 */
public int
hook_find_book(object who)
{
    if (!present(who, this_object()))
        return 0;
    return 1;
}

/*
 * Function name: hook_found_book
 * Description  : Default message given when a book is found.
 *                Redefine for your own.
 * Arguments    : object who - the book finder
 */
public void
hook_found_book(object who)
{
    who->catch_tell("You finally find the book you were looking for, and " +
        "take it off the shelf.\n");
    tell_room(this_object(), QCTNAME(who) + " takes a book off a shelf.\n", 
        who);
}

/*
 * Function name: hook_book_currently_borrowed
 * Description  : Default message given when a book is already borrowed.
 *                Redefine for your own.
 * Arguments    : object who - the player searching for a book, 
 *                string str - the bookname as entered by the player 
 */
public void
hook_book_currently_borrowed(object who, string str)
{
    who->catch_tell("You can't find the book you want. Perhaps it has " +
        "been borrowed.\n");
    say(QCTNAME(who) + " comes up empty handed from " + 
        who->query_possessive() + " search for a book.\n");
}

/*
 * Function name: hook_book_not_found
 * Description  : Default message given when a book can't be found.
 *                Redefine for your own.
 * Arguments    : object who - player who is searching
 *                string str - the bookname as given by 'who'
 */
public void
hook_book_not_found(object who, string str)
{
    if (present(who, this_object()))
    {
        who->catch_tell("You could not find the book you were " +
            "looking for. Be sure to give the full title (up to any " +
            "'-' which may be present in the title).\n");
    }
}

/*
 * Function name: hook_index_fail
 * Description  : Default message given when one can't read the index.
 *                Redefine for your own message.
 */
public void
hook_index_fail()
{
    write("You can't seem to read the index.\n");
}

/*
 * Function name: hook_appoint_unappoint
 * Description  : Checks whether a librarian appointment can be
 *                made or not, defined by your unique requirements.
 *                The standard checks, such as max librarian number
 *                are done elsewhere.
 * Returns      : 1 if an appointment is allowed, 0 if not
 */
public int
hook_appoint_unappoint()
{
    return 0;
}

/*
 * Function name: hook_can_use_library
 * Description  : Determines if one can use the library, ie if the the
 *                npc librarian is present if you have one.
 * Returns      : 1 if use is allowed, 0 if not
 */
public int
hook_can_use_library()
{
    /* put checks for library npcs here */
    return 1;
}

/*
 * Function name: hook_can_access_catalog
 * Description  : Handles special access levels, such as guild
 *                rank, membership, etc. You must define any
 *                special levels beyond 0 and 1 here yourself.
 * Arguments    : int level - 0: everyone can read
 *                            1: librarian only can read
 *                            special defined levels, eg
 *                            2: council members only
 * Returns      : ({0, "No access"}) or ({1, "Something else"})
 */
public mixed
hook_can_access_catalog(int level)
{
    /* add special access levels here */
    return ({ 0, "No access" });
}

/*
 * Function name: lex_greater
 * Description  : Compares two strings.
 * Arguments    : string a - first string
 *                string b - second string
 * Returns      : 0 if strings are equal, 1 if a is more than b, -1 otherwise
 */
private int
lex_greater(string a, string b)
{
    if (a == b)
        return 0;
    else if (a > b)
        return 1;
    else
        return -1;
}

/*
 * Function name: can_access_catalog
 * Description  : Can the player read the catalog?
 * Arguments    : int level - the topic?
 * Returns      : mixed ({ access, ret }) access - 1 can read, 0 - can't
 */
nomask mixed
can_access_catalog(int level)
{
    int access = 0;
    mixed tmp;
    string ret = "No access";

    /* free access */
    if (!level)
    {
        ret = "General Public";
        access = 1;
    }
    /* librarian only */
    else if (level == 1)
    {
        ret = "Librarian only";
        if (member_array(this_player()->query_real_name(), gLibrarian) != -1)
        {
            if (hook_librarian_requirements())
            {
                access = 1;
            }
            else
            {
                write("You do not meet the requirements to be the " +
                    "librarian. You have been unappointed.\n");
                access = 0;
                gLibrarian -= ({ this_player()->query_real_name(), 0 });
                save_object(MASTER);
            }
        }
        else
        {
            access = 0;
        }
    }
    /* add new general access levels here */
    else
    {
        tmp = hook_can_access_catalog(level);
        access = tmp[0];
        ret = tmp[1];
    }

    return ({ access, ret });
}

/*
 * Function name: library_leave_inv
 * Description  : Called from leave_inv(), removes borrowed books,
 *                calls hook_leave_with_books, and gives a message
 *                that reminds the player to finish writing their
 *                book if left with a blank book. Must be included
 *                in your library in leave_inv()
 * Arguments    : object player - player leaving, 
 *                object dest - destination
 */
nomask void
library_leave_inv(object player, object dest)
{
    int took, i, size;
    object *ob;
  
    if (!player || !living(player))
        return;
  
    ob = deep_inventory(player);
    for (i = 0, size = sizeof(ob); i < size; i++)
    {
        if (ob[i]->id(gLibId))
        {
            took++;
            gCurrentlyBorrowed -= ({ ob[i]->query_bookname() });
            ob[i]->remove_object();
        }
    }

    if (took > 0)
        hook_leave_with_books(player, took);

    if (present(gLibId + "_new", player))
        player->catch_tell("Please remember to finish writing your book.\n");
}

/*
 * Function name: index
 * Description  : Lists the available topics in the library
 * Arguments    : string str - as given by the players
 * Returns      : int
 */
nomask varargs int
index(string str)
{
    int i, size, acc;
    string *ltopics = sort_array(TOPICLIST, lex_greater);
    mixed access;

    if (str)
        return catalog(str);

    write("These Topics are available in the library:\n");
    for(i = 0, size = m_sizeof(gTopics); i < size; i++)
    {
        acc = gTopics[ltopics[i]];
        access = can_access_catalog(acc);
        /* ok to access */
	if (access[0] == 1) 
            write(sprintf("  %-25s\t%-20s\n", ltopics[i], access[1]));
    }

    write("Use 'catalog <topic>' for a list of books within the topic.\n");
    return 1;
}

/*
 * Function name: catalog
 * Description  : Lists the available topics in the library
 * Arguments    : string str - as given by the players
 * Returns      : int
 */
nomask int
catalog(string str)
{
    int i, size, j = 0;
    int top;
    string *btitles;
    string txt;
    mapping tmp = mkmapping(map(TOPICLIST, lower_case), TOPICLIST);

    if (!str)
        return index(str);

    str = lower_case(str);

    for(i = 0, size = m_sizeof(tmp); i < size; i++)
    {
        if (wildmatch(str + "*", m_indexes(tmp)[i]))
        {
            str = m_indexes(tmp)[i];
            break;
        }
    }

    /* No real topic */
    if (member_array(str, m_indexes(tmp)) == -1)
    {
        notify_fail("No such topic!\n");
        return 0;
    }

    top = gTopics[tmp[str]];
    /* Librarian only topic */
    if (!this_player()->query_wiz_level())
    {
        if (top == 1 && !check_librarian(this_player()->query_real_name()))
        {
            notify_fail("You are not allowed access to this topic.\n");
            return 0;
        }

        if (!hook_can_access_catalog(top))
        {
            notify_fail("You are not allowed access to this topic.\n");
            return 0;
        }
    }

    btitles = sort_array(BOOKLIST, lex_greater);
    write(tmp[str] + ":\n");
    for(i = 0, size = m_sizeof(gBooks); i < size; i++)
    {
        if (lower_case(gBooks[btitles[i]][1]) == str)
        {
	    j++;
	    write("  " + gBooks[btitles[i]][0] + "\n");
        }
    }

    txt = (j == 1 ? "is one volume" : "are " + LANG_WNUM(j) + " volumes");
    write("There " + txt + " available.\n");
    return 1;
}

/*
 * Function name: bookname
 * Description  : Removes any spaces and /'s
 * Arguments    : string str - the name of the book
 * Returns      : the lower case, no space, no / name of the book
 */
nomask string
bookname(string str)
{
    string str2;

    if (!str)
        return "";

    str2 = implode(explode(str, " "), "");
    str2 = implode(explode(str2, "/"), "") + "-extra";
    return lower_case(explode(str2, "-")[0]);
}

/*
 * Function name: blank
 * Description  : Get a blank book to write a book in
 * Returns      : 0 on failure, 1 on success
 */
nomask int
blank()
{
    object book;
    int state;

    if (!gLibType && !this_player()->query_wiz_level())
        return 0;

    if (!hook_can_use_library())
        return 0;
  
    seteuid(getuid(this_object()));
    book = clone_object(W_BOOK);
    book->add_name(gLibId + "_new");
    state = book->move(this_player());

    if (state)
        book->move(this_object(), 1);

    hook_give_blank_book(state);
    return 1;
}

/*
 * Function name: come_back
 * Description  : Called after the search delay to give a book
 *                or not to the person wanting it.
 * Arguments    : object who - the person searching for a book
 *                string str - the book they are searching for
 */
nomask void
come_back(object who, string str)
{
    object book;
    int i, size, access;
    string bname = bookname(str);
    string shortname, longname, textname;
    string *adj;
    mapping topictmp = mkmapping(map(TOPICLIST, lower_case), TOPICLIST);
    string *tmp = sort_array(BOOKLIST, lex_greater);
    
    if (!strlen(str))
    {
        hook_book_not_found(who, str);
        return;
    }

    for(i = 0, size = sizeof(tmp); i < size; i++)
    {
        if (wildmatch(bname + "*", tmp[i]))
        {
            bname = tmp[i];
            break;
        }
    }

    shortname = gLibPath + "short/" + bname;
    longname = gLibPath + "long/" + bname;
    textname = gLibPath + "book/" + bname;
    
    if (!hook_find_book(who))
        return;
    
    if (file_size(gLibPath + "short/" + bname) < 0)
    {
        hook_book_not_found(who, str);
        return;
    }

    /* This prevents people from reading books from restricted categories
     * If they are not, it tells them there is no such book :-E */
    
    /* !!! Need to get the access level from the bookname... */
    access = ACCESS_LEVEL(bname);
    if (!this_player()->query_wiz_level())
    {
        if (!(can_access_catalog(access)[0]))
        {
            hook_book_not_found(who, str);
            return 0;
        }
    }

    if (member_array(bname, gCurrentlyBorrowed) != -1)
    {
        hook_book_currently_borrowed(who, str);
        return;
    }
    
    hook_found_book(who);
    book = clone_object(gBookfile);
    book->add_name(gLibId);
    adj = explode(read_file(shortname), " ") - ({ "book" });

    for (i = sizeof(adj) - 1; i >= 0; i--)
    {
        book->set_adj(adj[i]);
    }

    book->set_name(adj[sizeof(adj) - 1]);
    book->set_short(read_file(shortname));
    book->set_long(read_file(longname));
    book->set_file(textname);
    book->set_bookname(bname, file_name(this_object()));
    book->move(who, 1);
    
    gCurrentlyBorrowed += ({ bname });
}

/*
 * Function name: borrow
 * Description  : Starts the search delay alarm to find a book
 * Arguments    : string str - the string as entered by the player
 * Returns      : 0 if unsuccessful, 1 if successful
 */
nomask int
borrow(string str)
{
    if (!hook_can_use_library())
        return 0;
    
    if (!strlen(str))
    {
        notify_fail("Borrow what?\n");
        return 0;
    }

    hook_borrow();
    set_alarm(gSearchDelay, 0.0, &come_back(this_player(), str));
    return 1;
}

/*
 * Function name: lib_books
 * Description  : Checks if an object belongs to this library or not
 * Arguments    : object ob - the book to test
 * Returns      : 1 if it belongs, 0 if it doesn't
 */
nomask int
lib_books(object ob)
{
    return (ob->id(gLibId) || ob->id(gLibId + "_new"));
}

/*
 * Function name: returned_book
 * Description  : Removes the book from the borrowed list
 * Arguments    : string bname - the name of the book
 */
public nomask void
returned_book(string bname)
{
    gCurrentlyBorrowed -= ({ bname });
}

/*
 * Function name: my_return
 * Description  : Returns a library book
 * Arguments    : string str - as input by the player
 * Returns      : 1 on success, 0 on failure
 */
nomask int
my_return(string str)
{
    object *ob;
    int i, size;
  
    if (!strlen(str))
    {
        notify_fail("Return what?\n");
        return 0;
    }

    ob = FIND_STR_IN_OBJECT(str, this_player());
    if (!sizeof(ob))
    {
        notify_fail("Couldn't find any " + str + " around.\n");
        return 0;
    }

    ob = filter(ob, "lib_books", this_object());
    if (!sizeof(ob))
    {
        notify_fail("You can only return books from this library.\n");
        return 0;
    }

    write("You return " + COMPOSITE_DEAD(ob) + ".\n");
    say(QCTNAME(this_player()) + " returns " + QCOMPDEAD + ".\n");
  
    for (i = 0, size = sizeof(ob); i < size; i++)
    {
        if (ob[i]->id(gLibId + "_new"))
            write("Too bad you didn't choose to bstore it instead.\n");
      
        gCurrentlyBorrowed -= ({ ob[i]->query_bookname() });
        ob[i]->remove_object();
    }
  
    return 1;
}

/*
 * Function name: appoint
 * Description  : Appoint a librarian
 * Arguments    : string str - as input by the player
 * Returns      : 1 on success, 0 on failure
 */
nomask int
appoint(string str)
{
    string who;

    if (gLibType != 4)
        return 0;

    if (!hook_appoint_unappoint())
        return 0;

    if (!str)
    {
        notify_fail("Appoint who as librarian?\n");
        return 0;
    }

    if (!sscanf(lower_case(str), "%s as librarian", who))
    {
        notify_fail("Appoint who as librarian?\n");
        return 0;
    }

    if (sizeof(gLibrarian) >= gMaxLibNum)
    {
        notify_fail("There maximum number of librarians has been reached " +
            "already. You have to unappoint a present librarian first.\n");
        return 0;
    }

    gLibrarian += ({ who });
    write("You have appointed " + capitalize(who) + " as librarian.\n");
    say(QCTNAME(this_player()) + " changes the sign on the librarian's " +
        "office.\n");
    hook_appointed_info();
    save_object(MASTER);
    return 1;
}

/*
 * Function name: unappoint
 * Description  : Unappoint a librarian
 * Arguments    : string str - as input by the player
 * Returns      : 1 on success, 0 on failure
 */
nomask int
unappoint(string str)
{
    string who;

    if (gLibType != 4)
        return 0;

    if (!hook_appoint_unappoint())
        return 0;

    if (!strlen(str))
    {
        notify_fail("Unappoint who as librarian?\n");
        return 0;
    }

    if (!sscanf(lower_case(str), "%s as librarian", who))
    {
        notify_fail("Unappoint who as librarian?\n");
        return 0;
    }

    if (member_array(who, gLibrarian) == -1)
    {
        notify_fail(capitalize(who) + " is not a librarian.\n");
        return 0;
    }

    write("You have unappointed " + capitalize(who) + " as " +
        "librarian.\n");
    gLibrarian -= ({ who });
    say(QCTNAME(this_player()) + " changes the sign on the librarian's " +
        "office.\n");
    save_object(MASTER);
    return 1;
}

/*
 * Function name: retire
 * Description  : Retire as librarian
 * Arguments    : string str - as input by the player
 * Returns      : 1 on success, 0 on failure
 */
nomask int
retire(string str)
{
    if (gLibType != 2 && gLibType != 4)
        return 0;

    if (member_array(this_player()->query_real_name(), gLibrarian) == -1)
        return 0;

    if (!strlen(str) || str != "as librarian")
    {
        notify_fail("Retire as librarian?\n");
        return 0;
    }

    write("You have retired from your position as librarian.\n");
    gLibrarian -= ({ this_player()->query_real_name() });
    say(QCTNAME(this_player()) + " changes the sign on the librarian's " +
        "office.\n");
    save_object(MASTER);
    return 1;
}

/*
 * Function name: movebook
 * Description  : Move a book from one topic to another, or 
 *                from the input section to the library itself
 * Arguments    : string str - the name of the book as input by the player
 * Returns      : 1 on success, 0 on failure
 */ 
nomask int
movebook(string str)
{
    string thebook, newshelf, oldtopic;

    if (gLibType != 2 && gLibType != 4 && !this_player()->query_wiz_level())
        return 0;

    if (member_array(this_player()->query_real_name(), gLibrarian) == -1 && 
      !this_player()->query_wiz_level())
        return 0;

    if (!strlen(str))
    {
        notify_fail("Movebook <booktitle> to topic <newtopic>.\n");
        return 0;
    }

    if (sscanf(lower_case(str), "%s to topic %s", thebook, newshelf) != 2)
    {
        notify_fail("Movebook <booktitle> to topic <newtopic>.\n");
        return 0;
    }

    thebook = bookname(thebook);

    if (member_array(thebook, BOOKLIST) == -1)
    {
        notify_fail("No such book title found.\n");
        return 0;
    }

    if (member_array(newshelf, map(TOPICLIST, lower_case)) == -1)
    {
        notify_fail("No such Topic available.\n");
        return 0;
    }

    oldtopic = gBooks[thebook][1];
    gBooks[thebook][1] = newshelf;
    write("You move the book '" + gBooks[thebook][0] + "' from the Topic '" +
        oldtopic + "' to the Topic '" + newshelf + "'.\n");
    save_object(MASTER);
    return 1;
}

/* 
 * Function name: add_book
 * Description  : Adds a new book to the library mapping. All new 
 *                books will end up in the 'New Arrivals Section'
 * Arguments    : string descript - the description of the book
 */
nomask void
add_book(string descript)
{
    gBooks += ([bookname(descript) : ({descript,"new arrivals",
                this_player()->query_real_name()})]);
    save_object(MASTER);
}

/*
 * Function name: add_new_book
 * Description  : Handles adding a new book to the library
 * Arguments    : string blong  - the book's long description
 *                string bshort - the book's short description
 *                string bfile  - the book content
 */ 
nomask int
add_new_book(string blong, string bshort, string blist, string bfile)
{
    string str = bookname(blist);
    string tme;

    if (file_size(gLibPath + "short/" + str) != -1 ||
      file_size(gLibPath + "long/" + str) != -1 ||
      file_size(gLibPath + "book/" + str) != -1)
        return 0;

    write_file(gLibPath + "short/" + str, bshort);
    write_file(gLibPath + "long/" + str, blong);
    write_file(gLibPath + "book/" + str, bfile);
    add_book(blist);
    
    tme = ctime(time());
    write_file(gLibPath + "book_log", tme[4..15] + " " + tme[22..23] + " " +
	       this_player()->query_name() + ": " + str + "\n");
    return 1;
}

/*
 * Function name: erase_book
 * Description  : Remove a book from the library, or all books from
 *                the trash.
 * Arguments    : string descript - the book(s) to delete
 * Returns      : 1 if book(s) removed, 0 if not
 */
nomask int
erase_book(string descript)
{
    string *b;
    string *btitles = sort_array(BOOKLIST,lex_greater);
    string str = "These books were deleted from the trash:\n";
    string bname = "";
    string shortname, longname, textname;
    int i, size, j = 0;

    if (gLibType != 2 && gLibType != 4 && !this_player()->query_wiz_level())
        return 0;

    if (member_array(this_player()->query_real_name(), gLibrarian) == -1 && 
      !this_player()->query_wiz_level())
        return 0;
  
    /* Remove all books in the trash */
    if (!descript || descript == "")
    {
        write("Give a specific book title or '-all books in trash-' as " +
            "argument if you want to empty the trash.\n");
        return 1;
    }

    if (descript == "-all books in trash-")
    {
        for(i = 0, size = m_sizeof(gBooks);i < size; i++)
        {
            if (lower_case(gBooks[btitles[i]][1]) == "trash")
            {
                if (member_array(btitles[i], gToDelete) < 0)
                {
                    j--;
                    gToDelete += ({ btitles[i] });
	        }
	        else
	        {
                    j++;
                    str += btitles[i] + "\n";
                    gBooks = m_delete(gBooks, btitles[i]);

                    /* Here we remove the long-, short- and text-file 
                       for this book */
                    bname = bookname(btitles[i]);
                    shortname = gLibPath + "short/" + bname;
                    longname = gLibPath + "long/" + bname;
                    textname = gLibPath + "book/" + bname;
                    rm(longname);
                    rm(shortname);
                    rm(textname);
                }
            }
        }

        if (j > 0)
            write(str + "\n");
        else if (j < 0)
            write("Please repeat the last command to really delete the " +
                "book(s).\n");
        else
            write("Trash was empty, no books removed.\n");

        save_object(MASTER);
        return 1;
    }

    /* Remove a specific book */
    descript = bookname(descript);
    b = gBooks[lower_case(descript)];
    if (!b)
    {
        notify_fail("No such book found!\n");
        return 0;
    }
    if (b[1] != "trash")
    {
        write("Book must be in the trash before it can be removed " +
            "completely.\n");
        return 1;
    }
    if (member_array(descript, gToDelete) == -1)
    {
        gToDelete += ({ descript });
        write("Really delete this book? - To continue repeat the last " +
            "command.\n");
        return 1;
    }
    else
    {
        gBooks = m_delete(gBooks, descript);
        /* Here we remove the long-, short- and text-file for this book */
        bname = descript;
        shortname = gLibPath + "short/" + bname;
        longname = gLibPath + "long/" + bname;
        textname = gLibPath + "book/" + bname;
        rm(longname);
        rm(shortname);
        rm(textname);

        write("Book: " + descript + " was erased!\n");
        save_object(MASTER);
        return 1;
    }
}


/* 
 * Function name: my_create
 * Description  : Add a topic to the topics list
 * Arguments    : string str - the topic
 * Returns      : 1 if topic added, 0 if not
 */
nomask int
my_create(string str)
{
    string newtopic;
    int access;
    string *tmp;

    if (gLibType != 2 && gLibType != 4)
        return 0;

    if (member_array(this_player()->query_real_name(), gLibrarian) == -1 &&
      !this_player()->query_wiz_level())
        return 0;
  
    if (!strlen(str))
    {
        notify_fail("Create what topic?\n");
        return 0;
    }

    tmp = explode(str, " ");
    newtopic = implode(tmp[..sizeof(tmp)-2]," ");
    if (!newtopic || !strlen(newtopic))
    {
        notify_fail("Create <new topic> <access level>?\n");
        return 0;
    }

    if (sscanf(tmp[sizeof(tmp) - 1], "%d", access) != 1)
    {
        notify_fail("Create <new topic> <access level>?\n");
        return 0;
    }

    gTopics += ([newtopic : access]);
    save_object(MASTER);
    write("Topic " + capitalize(newtopic) + " created.\n");
    return 1;
}

/* 
 * Function name: uncreate
 * Description  : Remove a topic from the topics list
 * Arguments    : string str - the topic
 * Returns      : 1 if topic removed, 0 if not
 */
nomask int
uncreate(string str)
{
    int i, size;

    if (gLibType != 2 && gLibType != 4)
        return 0;

    if (member_array(this_player()->query_real_name(), gLibrarian) == -1 &&
      !this_player()->query_wiz_level())
        return 0;

    if (!strlen(str))
    {
        notify_fail("Uncreate what topic?\n");
        return 0;
    }

    if (lower_case(str) == "trash" || lower_case(str) == "new arrivals" ||
        lower_case(str) == "general")
    {
        notify_fail("You can't uncreate that topic.\n");
        return 0;
    }

    for(i = 0, size = m_sizeof(gBooks); i < size; i++)
    {
        if (gBooks[BOOKLIST[i]][1] == lower_case(str))
        {
            notify_fail("There are still books in this topic. Topic must " +
                "be empty before it can be 'uncreated'.\n");
            return 0;
        }
    }

    if (member_array(str, m_indexes(gTopics)) == -1)
    {
        notify_fail("No such topic found. Watch for upper and lower case.\n");
        return 0;
    }

    gTopics = m_delete(gTopics, str);
    save_object(MASTER);
    write("Topic " + str + " removed.\n");
    return 1;
}

/* 
 * Function name: input_new_title
 * Description  : Change the catalog entry of a book.
 *                eg. if it was misformatted
 * Arguments    : string str - the book
 */
nomask void
input_new_title(string str)
{
    string newtitle = ((str && strlen(str)) ? str : gOldTitle);
    mixed oldentry = gBooks[gBookToChange];
    string newbookname = bookname(newtitle);

    if (newbookname != bookname(gOldTitle) &&
      file_size(gLibPath + "short/" + bookname(newtitle)) != -1)
    {
        write("There is already a book with that title. Beautify failed.\n");
        return;
    }

    oldentry[0] = newtitle;
    gBooks = m_delete(gBooks, gBookToChange);
    gBooks += ([newbookname : oldentry]);

    if (gBookToChange != newbookname)
    {
        rename(gLibPath + "short/"+ gBookToChange,
            gLibPath + "short/"+ newbookname);
        rename(gLibPath + "long/" + gBookToChange,
            gLibPath + "long/" + newbookname);
        rename(gLibPath + "book/" + gBookToChange,
            gLibPath + "book/" + newbookname);
    }

    write("Catalog entry set to:\n'" + newtitle +"'\n");
    save_object(MASTER);
    
    /* Add the option to modify the short and long of the book as well. */
}

/*
 * Function name: beautify
 * Description  : Begins changing the catalog of the book
 * Arguments    : string str - the book
 * Returns      : 1 if beautified, 0 if not
 */
nomask int
beautify(string str)
{
    if (gLibType != 2 && gLibType != 4 && !this_player()->query_wiz_level())
      return 0;

    if (member_array(this_player()->query_real_name(), gLibrarian) == -1 && 
      !this_player()->query_wiz_level())
        return 0;

    if (!str)
    {
        notify_fail("Beautify what book?\n");
        return 0;
    }

    if (!gBooks[bookname(str)])
    {
        notify_fail("Beautify what book?\n");
        return 0;
    }

    gBookToChange = bookname(str);
    gOldTitle = gBooks[gBookToChange][0];
  
    write("Catalog entry is:\n'" + gOldTitle + "'\nEnter new catalog entry " +
        "(Hit Return to leave as is).\n");
    input_to(input_new_title);
    return 1;
}

/*
 * Function name: done_editing
 * Description  : Writes a file when done editing
 * Arguments    : string text - the text
 */
void
done_editing(string text)
{
    string file = this_player()->query_prop("_temp_s_editing_book");

    if (!text || text == "")
    {
        write("Aborted.\n");
        return;
    }

    if (!file)
    {
        write("Sorry, something went wrong, the book was NOT stored!\n");
        return;
    }

    write("Ok.\n");
    seteuid(getuid(this_object()));
    rm(file);
    write_file(file, text);
}

/*
 * Function name: edit
 * Description  : Deals with editing a current book
 * Arguments    : string str - the book
 * Returns      : 1 if successful, 0 if not
 */
nomask int
edit(string str)
{
    string author;
    string booktext;

    if (gLibType != 2 && gLibType != 4 && !this_player()->query_wiz_level())
        return 0;
    
    if (!str)
    {
        notify_fail("Edit what book?\n");
        return 0;
    }

    if (!gBooks[bookname(str)])
    {
        notify_fail("Edit what book?\n");
        return 0;
    }

    gBookToChange = bookname(str);

    if (sizeof(gBooks[gBookToChange]) >= 2)
        author = gBooks[gBookToChange][2];
    else
        author = this_player()->query_real_name();

    gBookToChange = gLibPath + "book/" + gBookToChange;
    this_player()->add_prop("_temp_s_editing_book", gBookToChange);

    if (author != this_player()->query_real_name() &&
      member_array(this_player()->query_real_name(), gLibrarian) == -1 &&
      !this_player()->query_wiz_level())
        return 0;

    write("Editing mode.\n");
    booktext = read_file(gBookToChange);
    clone_object(BEDIT)->edit("done_editing", booktext,
        booktext ? sizeof(explode(booktext, "\n")) : 0);
    return 1;
}

/*
 * Function name: query_librarian
 * Description  : Gives the librarians of this library
 * Returns      : string* - the librarians
 */
nomask string*
query_librarian()
{
    return gLibrarian;
}

/*
 * Function name: check_librarian
 * Description  : Checks if someone is a librarian
 * Arguments    : string who - the name to check
 * Returns      : 1 if a librarian, 0 if not
 */
nomask int
check_librarian(string who)
{
    return (member_array(lower_case(who), gLibrarian) != -1);
}

/*
 * Function name: query_lib_long
 * Description  : Gives the library long
 * Returns      : string - gLibLong
 */
nomask string
query_lib_long()
{
    return gLibLong;
}

/*
 * Function name: query_lib_type
 * Description  : Gives the type of library
 * Returns      : int - gLibType
 */
nomask int
query_lib_type()
{
    return gLibType;
}

/*
 * Function name: query_lib_path
 * Description  : Gives the library path
 * Returns      : string - gLibPath
 */
nomask string
query_lib_path()
{
    return gLibPath;
}

/*
 * Function name: query_search_delay
 * Description  : Gives the search delay when searching for books
 * Returns      : float - gSearchDelay
 */
nomask float
query_search_delay()
{
    return gSearchDelay;
}

/*
 * Function name: query_max_librarian_num
 * Description  : Gives the maximum number of librarians allowed
 * Returns      : int gMaxLibNum
 */
nomask int
query_max_librarian_num()
{
    return gMaxLibNum;
}

/*
 * Function name: init_library
 * Description  : Call this in your library's init to set up the library
 */
nomask void
init_library()
{
    add_action(index, "index");
    add_action(index, "list");
    add_action(catalog, "catalog");
    add_action(blank, "blank");
    add_action(borrow, "borrow");
    add_action(my_return, "return");
    add_action(appoint, "appoint");
    add_action(unappoint, "unappoint");
    add_action(retire, "retire");
    add_action(movebook, "movebook");
    add_action(erase_book, "erase");
    add_action(my_create, "create");
    add_action(uncreate, "uncreate");
    add_action(beautify, "beautify");
    add_action(edit, "edit");
}

