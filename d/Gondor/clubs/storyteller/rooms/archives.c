/*
 * /d/Gondor/clubs/storytellers/rooms/archives.c
 * Borrowed from:
 * The Rangers' recruitment library.
 *
 * Updated 20190625 by Shanoga:  Fixed get_story_author for
                                 long or missing subtitles
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
#include "../defs.h"
#include "../obj/storybook.h"

#define PLAYER_I_WRITING_BOOK	"_player_i_writing_book"
#define LOG 			STORYT_DIR + "stories/log"

string          exa_poster();
string          exa_sign();
string          exa_desk();
string          exa_shelves();
varargs void	add_shelf(string name, string desc, mixed books);
void            add_shelf_book(string name, mixed book);
public string   process_pronouns(string line);
public void     cleanup_trash();
public string   get_story_filename(string title);
public string   get_story_author(string title);
public int      appoint(string name);
public int      unappoint(string name);
public int      get_spectacles(string str);

string *nonshelf_books = ({ });
mapping shelf_book = ([ "Romance" : ({}), "Adventure" : ({ }),
                        "History" : ({ }), "Comedy" : ({ }),
                        "Biography" : ({ }), "Tragedy" : ({ }),
                        "Miscellaneous" : ({ }) ]);

mapping shelf_desc = ([ 
        "Romance" : "The shelf labelled 'Romance' holds scrolls telling " +
                    "wonderful tales of love and romance.",
        "Adventure" : "The shelf labelled 'Adventure' holds " +
                      "scrolls telling tales of excitement and danger.",
        "History" : "The shelf labelled 'History' holds scrolls " +
                    "telling of true events of the past.",
        "Comedy" : "The shelf labelled 'Comedy' holds scrolls "+
                   "telling tales of humour and mirth.",
        "Biography" : "The shelf labelled 'Biography' holds scrolls "+
                      "telling the story of a person's life.",
        "Tragedy" : "The shelf labelled 'Tragedy' holds scrolls "+
                    "telling tales that are sad and unfortunate.",
        "Miscellaneous" : "The shelf labelled 'Miscellaneous' holds " +
                          "scrolls telling tales that don't fall into " +
                          "the other categories.",
        ]);

static int Append;

void
create_room()
{
    int is, size;
    string *shelves;
	
    set_library_name("the Storytellers' Archives");
    set_short("in the Storytellers' Archives");
    set_long("This is a small well-lit room with shelves along every " +
        "wall.  There is a doorway to the west.  There is a desk and " +
        "chairs in the center of the room and brass lamps upon the " +
        "table.  Also on the desk are several jars of ink and several "+
        "fine quills.  There is a small sign on the desk, and a "+
        "poster on the wall.\n");
	
    add_exit(STORYT_DIR + "rooms/ehallway", "west", lib_check, 0);
    add_item(({"poster", "instructions", }), exa_poster());
    add_cmd_item("sign", "read", &exa_sign());
    add_cmd_item("poster", "read", &exa_poster());

    add_item(({"desk", "small desk",}), &exa_desk());
    add_item(({ "sign", "instructions" }), &exa_sign());	
    add_item("poster", &exa_poster());
    add_item(({"table", "tables"}), "A well-worn table spotted with ink " +
        "stains.  Upon the table rest a few blank scrolls, fine quills, " + 
        "and jars of ink.\n");
    add_item(({"lamp", "lamps", "brass lamp", "brass lamps"}), "You notice " +
        "a couple brass lanterns on the table to provide ample lighting "+
        "for those wishing to write a story.\n");
    add_item(({"wall", "walls"}), "Each of the polished wooden walls " +
        "support several shelves and appear to be quite well cared for.\n");
    add_item("spectacles", "There are several pairs of spectacles on the "+
	"desk. You could probably take one if you wanted.\n");

    set_borrow_cmd("borrow");
    set_return_cmd("return");
    set_read_cmd("read");
    set_list_cmd("list");
    set_book_type("scroll");
    set_save_path(STORYT_DIR + "stories/stories");
    set_write_dir(STORYT_DIR + "stories");
    set_log_file("story_archive");
    set_up_library();

    add_item("shelves",&exa_shelves());

    add_prop(ROOM_I_INSIDE, 1);

    cleanup_trash();

    shelves = m_indexes(shelf_desc);
    for (is = 0, size = sizeof(shelves); is < size; is++)
        add_item(LOW(shelves[is]), "@@query_shelf_long|"+shelves[is]+"@@");
}

public void
cleanup_trash()
{
    string *allfiles = get_dir(STORYT_DIR + "stories/"),
           *bookfiles = ({ }), *validbooks = ({ }), *tmp;
    int i, size;

    for (i = 0, size = sizeof(allfiles); i < size; i++)
        if (allfiles[i][0..3] == "book")
            bookfiles += ({ allfiles[i] });


    for (i = 0, size = sizeof(paths); i < size; i++)
    {
        tmp = explode(paths[i], "/");
        validbooks += ({ tmp[sizeof(tmp) - 1] });
    }


    for (i = 0, size = sizeof(bookfiles); i < size; i++)
        if (member_array(bookfiles[i], validbooks) == -1)
        {
            rm(STORYT_DIR + "stories/" + bookfiles[i]);
        }
}

string
query_shelf_long(string shelf)
{
    string desc = shelf_desc[shelf];
	
    if (sizeof(shelf_book[shelf]))
        desc += " You see the following scrolls on the shelf: " +
            COMPOSITE_WORDS(sort_array(shelf_book[shelf])) + ".";
    else
        desc += " You don't see any scrolls on this shelf.";
	
    return desc + "\n";
}

string
exa_shelves()
{
    return "There are many shelves, each holding some scrolls of " +
        "information. On each shelf is a plaque stating what scrolls " +
        "it contains. " +
        "These are the shelves to choose from:\n" +
        COMPOSITE_WORDS(m_indexes(shelf_desc)) + ".\n";
}

string
exa_desk()
{
    string desc;

    desc = "It is a small, wooden desk, used by anyone who is writing " +
        "a story. Any scroll not yet moved to a shelf will remain on the " +
        "desk. There are several pairs of spectacles on the desk, as well, " +
        "should you need them for reading.\n";
	
    if (sizeof(nonshelf_books))
        desc = desc + "You see the following scrolls on the desk: " +
        COMPOSITE_WORDS(nonshelf_books)+"\n";
	
    return desc;
}

string
exa_sign()
{
    string text = "\tInstructions for writing a story\n\n"+
        "    Writing a story is different than writing a book, because\n"+
        "it must be written with the eventual presentation in mind. To\n"+
        "that end, certain characters are available to signify actions\n"+
        "by the storyteller.\n\n"+
        "\t&    denotes an action by the storyteller\n"+
        "\t=    separates actions and defines the length of pause between\n"+
        "\t        the actions\n"+
        "\tPOS  the possessive form of the storyteller (his/her)\n"+
        "\tPRO  the pronoun form of the storyteller (he/she)\n"+
        "\tOBJ  the objective form of the storyteller (him/her)\n"+
        "\tNAM  the name of the storyteller\n\n"+
        "An example of usage of &:\n"+
        "    '&clears POS throat as PRO begins the tale.' would yield\n"+
        "    'Wilhelm clears his throat as he beings the tale.'\n"+
        "Note that there is no space necessary after &, as the space\n"+
        "is automatically added unless & is followed by a ', to allow\n"+
        "for 'Wilhelm's eyes fill with tears.'\n\n"+
        "An example of usage of =:\n"+
        "    '=' will pause for a default period of three seconds\n"+
        "    '=5' will pause for a period of five seconds\n"+
        "Every pause must be followd by a new & action\n" + 
        "This is subject to reasonability checks, pauses cannot exceed\n"+
        "thirty seconds.\n\n"+
        "NOTE: Authors of inappropriate stories may find themselves in\n"+
        "\ttrouble with the powers that be.\n\n";

    this_player()->more(text, 0);
    return "";
}

string
exa_poster()
{
    return "\tWelcome to the "+query_library_name()+"!\n" +
           "\n\tThe following commands are available:\n\n" +
           "\texa shelves    - examine the different topics\n"+
           "\texa <shelf>    - examine a particular shelf\n"+
           (TP->query_wiz_level() ? 
             "\tlist [titles]  - list the available titles,\n" : "" )+
           "\tborrow <title> - borrow a scroll with the title <title>,\n" +
           "\treturn scroll  - return a scroll,\n" +
           "\tread <title>   - read a scroll without borrowing it,\n" +
           "\ttail <title>   - read the last part of a scroll without "+
             "borrowing it,\n" +
           "\twrite scroll   - write a new scroll or add to an existing "+
             "one,\n" +
           "\t\tDo NOT leave any scroll on the desk that you do not wish\n" +
           "\t\tto be removed or shelved.\n" +
           "\tmove <title> to <shelf> shelf   - move a scroll to a shelf,\n" +
           "\tremove <title> - remove an obsolete scroll.\n"+
           "\tcopy <title>   - copy a story into your storybook\n"+ 
           (TP->query_wiz_level() ? "\tappoint [name] - appoint a librarian\n"+
             "\tunappoint[name]- unappoint a librarian\n" : "")+
           "\n\tIf you would like to become a librarian, please leave a\n" +
           "\tnote on the board or mail " +
           capitalize(SECURITY->query_domain_lord("Gondor")) +
           " with any questions.\n\n";
}

int
do_list(string str)
{
    if (!this_player()->query_wiz_level())
        return 0;
	
    return ::do_list(str);
}


int
query_privs(object pl)
{
    if (pl->query_wiz_level())
        return 1;

    if (IS_STORYTELLER(pl))
        return 1;

    return 0;
}

public int
do_read(string str)
{
    if (query_privs(this_player()))
    {
        return ::do_read(str);
    }
    else
    {
        notify_fail("Only those appointed by the tellers may do that!\n");
        return 0;
    }
}

int
query_write_priv(object pl)
{
    if (query_privs(pl))
        return 1;
    return 0;
}

int
query_remove_priv(object pl)
{
    if (query_privs(pl))
        return 1;

    return 0;
}

int
query_secure_add(object pl)
{
    if (query_privs(pl))
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
    string book, shelf, *shelves;
    int i, n, size;
	
    if (!this_player()->query_wiz_level() &&
      !IS_LIBRARIAN(this_player()))
    {
        notify_fail("You are not allowed to add new scrolls to "+
            "the shelves.\n");
        return 0;
    }
	
    s = capitalize(lower_case(s));
    if (sscanf(s, "%s to %s shelf", book, shelf) < 2)
    {
        notify_fail("Move which scroll to which shelf?\n" +
            "Try: move <scroll> to <shelf> shelf.\n");
        return 0;
    }
	
    if (member_array(CAP(shelf), query_shelf()) < 0)
    {
        notify_fail("There is no shelf with the name \"" + CAP(shelf) +
            "\" in the archives!");
        return 0;
    }

    i = member_array(book, nonshelf_books);
    if (i < 0)
    {
        /* Check if it is a book in the shelves. */
        shelves = m_indexes(shelf_book);

        for (i = 0, size = sizeof(shelves); i < size; i++)
        {
            if ((n = member_array(book, shelf_book[shelves[i]])) >= 0)
            {
                shelf_book[shelves[i]] =
                    exclude_array(shelf_book[shelves[i]], n, n);
                add_shelf_book(shelf, book);

                FIX_EUID

                write("You move the scroll from the " + shelves[i] +
                    " shelf to the " + CAP(shelf) + " shelf.\n");
                say(QCTNAME(this_player()) + " moves a scroll "+
                    "from one shelf to another.\n");

                log_file(log_file, "LIBRARY: " + 
                    this_player()->query_name() + " moved the book " + 
                    book + " from shelf " + shelves[i] + " to the shelf " +
                    CAP(shelf) + " on " + ctime(time())+".\n");
                save_object(savepath);
                return 1;
            }
        }

        return lib_hook_office_not_exist();
    }

    add_shelf_book(shelf, book);
    write("You put the scroll in the " + CAP(shelf) + " shelf.\n");
    say(QCTNAME(this_player()) + " takes a scroll from the desk and puts "+
        "it in one of the shelves.\n");
	
    FIX_EUID

    log_file(log_file, "LIBRARY: " + this_player()->query_name() +
        " moved the book " + book + " to the shelf "+CAP(shelf) +
        " on "+ctime(time())+".\n");
    nonshelf_books = exclude_array(nonshelf_books, i, i);
    save_object(savepath);
    return 1;
}

void
lib_hook_finish_book(int sec)
{
    if (sec)
        write("You place your story in the drafts bin awaiting its "+
            "review.\n");
    else
        write("You finish your "+booktype+", leaving at the desk. " +
            "Now you should move it to one of the shelves.\n");

    say(QCTNAME(this_player())+" finishes writing a "+booktype +
        " at the desk.\n");
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

void
delete_book(string name)
{
    int j = member_array(name, names);

    if (j == -1)
	return;

    names  = exclude_array(names, j, j);
    paths  = exclude_array(paths, j, j);
    descrs = exclude_array(descrs, j, j);
    bflags = exclude_array(bflags, j, j);
    save_object(savepath);
}

/*
* Function name: remove_book
* Description:	 remove the book 'name' from the library
* Arguments:	  name - the name of the book to remove
* Returns:	  1 if success
*/
public int
remove_book(string name)
{
    int i, n, r, size;
    string *shelves;

    if ((n = member_array(name, names)) == -1)
    {
        notify_fail("There is no scroll entitled '"+name+"' to remove.\n");
        return 0;
    }

    if (get_story_author(name) != this_player()->query_name() &&
      !this_player()->query_wiz_level() && !IS_LIBRARIAN(this_player()))
    {
        write("You do not have permission to remove the scroll "+
            "entitled '"+name+"' from the archives.\n");
        return 1;
    }

    if (member_array(name, nonshelf_books) >= 0)
    {
        i = member_array(name, nonshelf_books);
        nonshelf_books = exclude_array(nonshelf_books, i, i);
        delete_book(name);
        save_object(savepath);
        log_file(log_file, "LIBRARY: " + 
            this_player()->query_name() + " removed the "+
            "book " + name + " from desk on "+ ctime(time())+".\n");
        write("You removed the scroll with the title '"+name+
            "' from the desk.\n");
        return 1;
    }

    shelves = m_indexes(shelf_book);
	
    for (i = 0, size = sizeof(shelves); i < size; i++)
    {
        if ((n = member_array(name, shelf_book[shelves[i]])) >= 0)
        {
            shelf_book[shelves[i]] = 
                exclude_array(shelf_book[shelves[i]], n, n);
            delete_book(name);
            log_file(log_file, "LIBRARY: " + this_player()->query_name() +
                " removed the " + "book " + name + " from shelves on "+
                ctime(time())+".\n");
            save_object(savepath);
            write("You removed the scroll with the title '"+name+
                "' from the shelves.\n");
            return 1;
        }
    }

    write("You see no such scroll entitled '"+name+"' to remove.\n");
    return 1;
}

/*
* Function name: get_book_name
* Description:	 input the name of the book
*				 modified to allow appending to existing books
* Arguments:	  s - the name
* Returns:	  0
*/
public void
get_book_name(string s)
{
    int bn;
    string old_file;

    if (!strlen(s))
    {
        //		lib_hook_query_name();
        //		input_to(get_book_name);
        write("You abort writing a new scroll.\n");
        busy = 0;
        return;
    }
    nbnam = capitalize(lower_case(s));

    if ((bn = member_array(nbnam, names)) >= 0)
        if (this_player()->query_wiz_level() || 
          IS_LIBRARIAN(this_player()) ||
          get_story_author(nbnam) == this_player()->query_name())
        {
            write("You take the "+booktype+" from the shelves and start " +
                "to add to it.\n");
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
    else
    {
        write("A scroll by that name already exists, but you "+
            "do not have permission to modify it.\n");
        lib_hook_query_name();
        input_to(get_book_name);
        return;
    }

    lib_hook_query_desc();
    input_to(get_book_desc);
}

/*
* Function name: done_appending
* Description:	 write the modified text of the book
* Arguments:	 str - the text
* Returns:		 0
*/
void
done_appending(string str)
{
    int bn;
    string msg;

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

    write("You finish editing the " + booktype + " and put it back " +
        "onto the shelf.\n");
    say(QCTNAME(this_player())+" finishes editing a " + booktype +
        " and returns it to the shelves.\n");

    log_file(log_file, "LIBRARY: " +
        capitalize(this_player()->query_real_name()) + " edited the book " +
        nbnam + " (" + nbdesc + ") on " + ctime(time()) + ".\n");
}

/*
 * Function name:	copy_story
 * Description	:	copy a story into the player's storybook
 * Arguments	:	string title -- the story title
 * Returns	:	1 on success, 0 on failure
 */
public int
copy_story(string title)
{
    int i, j, k, n;
    object book, tmpob;
    string *data, info, line, tmpstr, prefix;

    if (!strlen(title))
    {
	NF0("Copy what?\n");
    }
    if (!objectp(book = present(STORYBOOK_NAME, TP)))
    {
	NF0("You do not have a book into which to copy stories.\n");
    }
    if (parse_command(title, ({ book }),
	"%s 'in' / 'into' [the] %o", tmpstr, tmpob))
    {
	title = tmpstr;
    }
    if (sscanf(title, "'%s'", tmpstr))
    {
	title = tmpstr;
    }
//    tmpstr = LOW(title);
    i = member_array(title, names);
    if (i < 0)
    {
	NF0("Sorry, cannot find story with title '"+title+"'\n");
    }
    line = read_file(paths[i]);
    if (!strlen(line))
    {
	NFN0("Sorry, story '"+title+"' seems to have been expunged.");
    }
    if (book->find_story(title) >= 0)
    {
	NFN0("Sorry, you already have a story '"+title+"' in your book. "+
	    "Please erase it first.");
    }

    /* ok, walk thru the story to:
     *	    remove comments
     *	    change the EMOTE/ATMOS formats to EMOTE_PROC/ATMOS_PROC
     *		for lines that contain pronoun formats.
     *
     * use the data array for both "input" (line we're examining) and
     * "output" (line to be passed to storybook).  j is input index,
     * k is output index.
     *
     * assume first three lines are id info -- leave as is
     */
    data = explode(line, "\n");

    info = extract(data[1], 0, (strlen(data[1]) - 2));

/*
    find_living("morrigan")->catch_tell("Info: "+info+"END\n");
*/

    for (j = 3, k = 0, n = sizeof(data); j < n; ++j )
    {
        line = data[j];

        switch(line[0..0])
        {
        case BLANK:
        case NEWLINE:
        case COMMENT:
            break;
        case ALARM:
            data[++k] = line;
            break;
        case EMOTE:
            line = process_pronouns(line);
            if (sizeof(explode(line, STR_NAME)) <= 1)
            {
                prefix = EMOTE;
            }
            else
            {
                prefix = EMOTE_PROC;
            }

            if (line[1..1] != "'")
            {
                data[++k] = prefix+" "+line[1..];
            }
            else
            {
                data[++k] = prefix+line[1..];
            }
            break;

/* Remove ability to use atmospheric messages
	case ATMOS:
	    line = process_pronouns(line);
	    if (sizeof(explode(line, STR_NAME)) <= 1)
	    {
	        data[++k] = line;
	    }
	    else
	    {
	        data[++k] = ATMOS_PROC+line[1..];
	    }
	    break; */
        default:
            /* append to same line of data if current line
             * is an emote/emote_proc or atmos/atmos_proc line.
             * otherwise, ignore.
             */
            switch (data[k][0..0])
            {
            case EMOTE:
                if (sizeof(explode(line, STR_NAME)) > 1)
                {
                    /* we've found embedded names on a continuation
                     * line -- have to change type of line
                     */
                    prefix = EMOTE_PROC;
                    tmpstr = data[k][1..];
                    data[k] = "\n\t" + prefix + tmpstr;
                }
                data[k] += "\n\t"+line;
                break;
            case EMOTE_PROC:
                data[k] += "\n\t"+line;
                break;

/* Remove ability to use atmospheric messages
	    case ATMOS:
		if (sizeof(explode(line, STR_NAME)) > 1)
		{ */
		    /* we've found embedded names on a continuation
		     * line -- have to change type of line
		     */
/*		    prefix = ATMOS_PROC;
		    tmpstr = data[k][1..];
		    data[k] = prefix + tmpstr;
		}
		data[k] += " "+line;
		break;
	    case ATMOS_PROC:
	    	data[k] += " "+line;
		break; */
            }
            break;
        }
    }

    --n;
    if (k < n)
    {
	data = data[..k];
    }

    if (book->add_story(names[i], info, data) == 1)
    {
	write("Copied '"+title+"' into your book.\n");
    }
    else
    {
	write("Sorry, failed to copy '"+title+"' into your book.\n");
    }
    return 1;
} /* copy_story */

/*
 * Function name:	process_pronouns
 * Description	:	replace STR_POSSESSIVE, STR_PRONOUN and
 *			STR_OBJECTIVE with the appropriate pronoun
 * Arguments	:	string line -- the line of text to process
 * Returns	:	string -- the line with all pronoun codes
 *			processed.
 */
public string
process_pronouns(string line)
{
    object	teller = TP;
    string	*data,
		replace;
    int		i, n;

    n = sizeof(data = explode(line, STR_POSSESSIVE));
    if (n > 1)
    {
	line = implode(data, POSSESSIVE(teller));
    }
    n = sizeof(data = explode(line, STR_OBJECTIVE));
    if (n > 1)
    {
	line = implode(data, OBJECTIVE(teller));
    }
    n = sizeof(data = explode(line, STR_PRONOUN));
    if (n > 1)
    {
	line = implode(data, PRONOUN(teller));
    }
    return CAP(line);
} /* process_pronouns */

public string
get_story_filename(string title)
{
    int		i;
    string      *path;

    i = member_array(title, names);

    if (i < 0)
        return "no such story";

    /* Return only the filename, not the full path */
    path = explode(paths[i], "/");

    return path[sizeof(path) - 1];
}

public string
get_story_author(string title)
{
    int		i, j;
    string      *text, tmp, author;

    i = member_array(title, names);

    if (i < 0)
        return "no such story";

    /* Get the story */
    text = explode(read_file(paths[i]), "\n");

    /* Get the info line with the author's name */
    foreach (string line : text)
    {
        if (wildmatch("written by *", line))
            tmp = line;
    }
    if (!tmp)
        return "No Author Found";
    //tmp = text[2];
   
    /* Separate the author's name from the other data */
    text = explode(tmp, " on ");
    text = explode(text[0], " by ");
    author = text[1];

    return author;
}

public int
appoint(string name)
{
    name = CAP(LOW(name));

    if (!this_player()->query_wiz_level())
	return 0;

    if (!TELLERS->query_member(name))
    {
        write(name+" is not a story teller.\n");
	return 1;
    }

    if (TELLERS->add_librarian(name))
    {
        write("You appoint "+name+" as a librarian.\n");
	return 1;
    }

    write("Something failed with your appoint.\n");
    return 1;
}

public int
unappoint(string name)
{
    name = CAP(LOW(name));

    if (!this_player()->query_wiz_level())
	return 0;

    if (!TELLERS->query_librarian(name))
    {
        write(name+" is not a librarian.\n");
	return 1;
    }

    if (TELLERS->remove_librarian(name))
    {
        write("You unappoint "+name+" as a librarian.\n");
	return 1;
    }

    write("Something failed with your unappoint.\n");
    return 1;
}

public int
get_spectacles(string str)
{
    if (!parse_command(str, this_object(), 
	"[a] [pair] [of] 'spectacles' [from] [the] [desk]"))
	return 0;

    notify_fail("You already have a pair of spectacles.\n");
    if (present(SPECTACLES_ID, this_player()))
	return 0;

    clone_object(STORYT_DIR + "obj/spectacles")->move(this_player());
    write("You take a pair of spectacles from the desk for reading.\n");
    say(QCTNAME(this_player())+" takes a pair of spectacles from the "+
	"desk.\n");
    return 1;
}

void
init()
{
    ::init();
    init_library();
    add_action(move_book_to_shelf, "move");
    add_action(copy_story, "copy");
    add_action(appoint, "appoint");
    add_action(unappoint, "unappoint");
    add_action(get_spectacles, "get");
    add_action(get_spectacles, "take");
    add_action(get_spectacles, "pick");
}
