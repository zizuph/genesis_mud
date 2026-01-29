/*
 * /std/board.c
 *
 * This is a new board, which is programwise compatible with the old.
 * However, the file format is totally different.
 * 920221 /Tintin
 *
 * Revision history:
 * /Mercade, August 9th 1994, general revision. Changed the editor to
 * the new general editor. Kicked out Gedit too.
 * /AoC Team, 6/2/1995, added newline to 'Read What?' message.
 */

/* Example of use:
 * inherit "std/board";
 *
 * void
 * create_board()
 * {
 *	set_board_name("/d/Wiz/tintin/my_bulletin");
 *	set_num_notes(10);
 *	set_anonymous(1);
 *	set_silent(0);
 *	set_show_lvl(0);
 *	set_remove_lvl(10);
 *	set_remove_str("Sorry, you can't do that");
 * }
 *
 * After setting it up this way you just need to clone it and move it to
 * the location where you want it.
 *
 * The following options can be set:
 * set_num_notes(n)	 Set max number of notes (default 30)
 * set_silent(n)	 0 = Tell room about read and examine of the board
 *			 1 = silent read & examine. (default 1)
 * set_anonymous(n)	 0 = No anonymous posts, 1 = make articles made
 *			 by invisible persons come out as written by
 *			 'Someone' (default 0)
 * set_board_name(name)	 Path to the save directory for the board (no
 *			 default, this variable MUST be set) Old notes
 *			 will be stored in a directory with the same name,
 *			 with _old appended
 * set_remove_lvl(n)	 Minimum level required to remove other players
 *			 notes (default arches++)
 * set_remove_str(str)	 The string to send to the player if a remove
 *			 failed. (default 'Only an Archwizard can remove
 *			 other peoples notes')
 * set_err_log(str)	 Name of the log to where error messages should
 *			 go. (default 'BOARDS', but you MUST change it
 *			 since only /obj and /room objects can write to
 *			 this file)
 * set_show_lvl(n)	 0 = Don't show level in note header,
 *			 1 = show level of writer in note header
 *			 (default 1)
 * set_no_report(n)	 0 = Keep the central board notified.
 *			 1 = Don't notify the central board.
 *			 This makes the board 'secret' for tools.
 *			 (default: 0)
 * set_keep_discarded(n) 0 = don't keep old notes
 *			 1 = keep old notes
 *			 (default 0)
 *
 * There are three functions you can use to restrict usage of the board.
 * These functions are:
 *
 * varargs int check_reader()
 * varargs int check_writer()
 * varargs int check_remove()
 *
 * These functions respectively restrict reading, writing and deleting
 * notes (including your own). They must return 1 to restict and return
 * 0 if manupulating the board. If you print a message to the player if
 * manipulating the board is not possible, please check whether the
 * player is present in the room or else tools may give very ugly lists.
 * The functions operate on this_player(). There are set_ functions for
 * all three access levels that allow you to set VBFC to a function to
 * check for access.
 *
 * The header format is:
 * subject (40)  0..39
 * length  ( 5) 41..45 (3 characters in breakets)
 * author  (11) 47..57
 * level   ( 4) 59..62 (2 characters in breakets)
 * date    ( 6) 64..69 (format: month day)
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <std.h>
#include <stdproperties.h>

#define BOARD_CENTRAL "/std/board/board_central"
#define MORE_OBJECT   "/std/board/board_more"
#define EDIT_OBJECT   "/std/edit"
#define MAX_NO_MREAD  100

/*
 * Gloval variables. They are not savable.
 */
static mixed   headers = ({ });
static string  board_name = "";
static string  remove_str = "Only an Archwizard can remove other peoples notes.\n";
static string  err_log = "BOARDS";
static int     keep_discarded = 0;
static int     notes = 30;
static int     silent = 1;
static int     anonymous = 0;
static int     msg_num;
static int     remove_lvl = (WIZLEV_LORD + 1);
static int     show_lvl = 1;
static int     no_report = 0;
static int     fuse = 0;
static int     loaded = 0;
static mapping writing = ([ ]);
static mixed   read_access = 0;
static mixed   write_access = 0;
static mixed   remove_access = 0;

/*
 * Function name: set_num_notes
 * Description  : Set the maximum number of notes on the board.
 * Arguments    : int n - the number of notes on the board. (default: 30)
 */
public void
set_num_notes(int n)
{
    if (!fuse)
    {
	notes = n;
    }
}

/*
 * Function name: set_silent
 * Description  : Set this to make the board silent. That means that
 *                bystanders are not noticed of people examining the
 *                board and reading notes.
 * Arguments    : int n - true if silent (default: true)
 */
public void
set_silent(int n)
{
    if (!fuse)
    {
	silent = (n ? 1 : 0);
    }
}

/*
 * Function name: set_anonymous
 * Description  : Set this if you allow anonymous notes to be posted.
 *                People who are invisible while posting appear in the
 *                header as 'Someone'.
 * Arguments    : int n - true if anonymous notes are allowed.
 *                        (default: false)
 */
public void
set_anonymous(int n)
{
    if (!fuse)
    {
	anonymous = (n ? 1 : 0);
    }
}

/*
 * Function name: set_no_report
 * Description  : If you set this to true, the central board master is
 *                not notified of new notes. The only thing is that
 *                wizard tools won't be able to read it.
 * Arguments    : int n - true if the central board master should not
 *                        be notified. (default: false)
 */
public void
set_no_report(int n)
{
    if (!fuse)
	no_report = (n ? 1 : 0);
}

/*
 * Function name: set_board_name
 * Description  : This function sets the path in which the notes on the
 *                board are kept.
 * Arguments    : string str - the pathname of the board, without any
 *                / in the end.
 */
public void
set_board_name(string str)
{
    if (!fuse)
    {
	board_name = str;
    }
}

/*
 * Function name: set_remove_lvl
 * Description  : With this function you can set the minimum level people
 *                must have to be able to remove other peoples notes.
 * Arguments    : int n - the minimum level (default arch++).
 */
public void
set_remove_lvl(int n)
{
    if (!fuse)
    {
	remove_lvl = n;
    }
}

/*
 * Function name: set_remove_str
 * Description  : Set the string to be printed when a player tries to
 *                remove a note while he is not allowed to do so.
 * Arguments    : string str - the message (default: Only archwizards are
 *                             allowed to remove other peoples notes.)
 */
public void
set_remove_str(string str)
{
    if (!fuse)
    {
	remove_str = str;
    }
}

/*
 * Function name: err_log
 * Description  : Set the name (without path) of the log error messages
 *                are put in when something is wrong with a board.
 * Arguments    : string str - the name of the log (no default).
 */
public void
set_err_log(string str)
{
    if (!fuse)
    {
	err_log = str;
    }
}

/*
 * Function name: set_show_lvl
 * Description  : Set this if you want the level of the people writing
 *                the notes added to the header.
 * Arguments    : int n - true if the level should be show (default: true)
 */
public void
set_show_lvl(int n)
{
    if (!fuse)
    {
	show_lvl = (n ? 1 : 0);
    }
}

/*
 * Function name: set_keep_discarded
 * Description  : Set this if you want old notes to be kept. They will be
 *                kept if in a directory with the same name as the
 *                actual notes, though with _old appended to it.
 * Arguments    : int n - true if old notes should be kept (default: false)
 */
public void
set_keep_discarded(int n)
{
    if (!fuse)
    {
	keep_discarded = (n ? 1 : 0);
    }
}

/*
 * Function name: set_fuse
 * Description  : This function is automatically called directly after the
 *                object has been created using a little alarm. After that
 *                moment, the basic board properties (ie. the set_
 *                functions) cannot be called again to ensure security.
 */
static void
set_fuse()
{
    fuse = 1;
}

/*
 * Function name: set_reader
 * Description  : Use this function to set a VBFC string to the function
 *                that tests whether this_player() is allowed to read
 *                the board. Note that the VBFC should return true if the
 *                player is NOT allowed to read the board.
 * Arguments    : string str - the intended VBFC.
 */
public string
set_reader(string str)
{
    if (!fuse)
    {
	read_access = str;
    }
}

/*
 * Function name: check_reader
 * Description  : This function checks whether this_player() is allowed
 *                to read notes on this board. If you print an error
 *                message on failure, please check whether this_player()
 *                is in the environment of the board.
 * Returns      : int - true if the player is NOT allowed to read.
 */
varargs public int
check_reader()
{
    return (stringp(read_access) ? check_call(read_access) : read_access);
}

/*
 * Function name: set_writer
 * Description  : Use this function to set a VBFC string to the function
 *                that tests whether this_player() is allowed to write on
 *                the board. Note that the VBFC should return true if the
 *                player is NOT allowed to write on the board.
 * Arguments    : string str - the intended VBFC.
 */
public string
set_writer(string str)
{
    if (!fuse)
    {
	write_access = str;
    }
}

/*
 * Function name: check_writer
 * Description  : This function checks whether this_player() is allowed
 *                to write notes on this board. If you print an error
 *                message on failure, please check whether this_player()
 *                is in the environment of the board.
 * Returns      : int - true if the player is NOT allowed to write.
 */
varargs public int
check_writer()
{
    return (stringp(write_access) ? check_call(write_access) : write_access);
}

/*
 * Function name: set_remove
 * Description  : Use this function to set a VBFC string to the function
 *                that tests whether this_player() is allowed to remove notes
 *                from the board. Note that the VBFC should return true if
 *                the player is NOT allowed to remove notes the board.
 * Arguments    : string str - the intended VBFC.
 */
public string
set_remove(string str)
{
    if (!fuse)
    {
	read_access = str;
    }
}

/*
 * Function name: check_remove
 * Description  : This function checks whether this_player() is allowed
 *                to remove notes from this board. If you print an error
 *                message on failure, please check whether this_player()
 *                is in the environment of the board. This function works
 *                indipendant of the set_remove_lvl function.
 * Returns      : int - true if the player is NOT allowed to remove notes.
 */
varargs public int
check_remove()
{
    return (stringp(remove_access) ? check_call(remove_access) :
	remove_access);
}

/*
 * Function name: load_headers
 * Description  : Load the headers when the board is created.
 */
public void
load_headers()
{
    string *arr;
    object g;
    
    if (loaded)
    {
	return;
    }

    seteuid(getuid());

    
    arr = get_dir(board_name + "/*");
    if (!pointerp(arr))
	arr = ({});
    else
	arr -= ({ ".", ".." });

    headers = map(arr, "extract_headers", this_object()) - ({ 0 });
    msg_num = sizeof(headers);
    loaded = 1;
}

/*
 * Function name: create_object
 * Description  : Create the object. Use create_board() to set up the
 *                board yourself.
 */
nomask void
create_object()
{
    set_name("board");
    add_name("bulletinboard");
    set_adj("bulletin");
    set_short("bulletin board");

    add_prop(OBJ_I_NO_GET, "It's firmly secured to the ground.\n");

    this_object()->create_board();
    enable_reset();
    set_alarm(0.5, 0.0, "load_headers");
    set_alarm(0.5, 0.0, "set_fuse");
}

/*
 * Function name: reset_object
 * Description  : Every half hour or about, the object resets. It
 *                gives a funny message. Use reset_board() for user
 *                reset functionality.
 */
nomask void
reset_object()
{
    if (!random(5))
    {
	tell_room(environment(),
	    "A small gnome appears and secures some notes on the " +
	    "board that were loose.\nThe gnome leaves again.\n");
    }

    this_object()->reset_board();
}

/*
 * Function name: long
 * Description  : This function returns the long description on the board.
 *                If you don't have access to the board, you won't see the
 *                headers.
 * Returns      : the long description.
 */
public mixed
long()
{
    int ind;
    string str = "This is a bulletin board.\n" +
	"Usage : note <headline>, remove <message number>\n" +
	"        read/mread <message number> \n";

    if (this_player()->query_wiz_level())
	str += "        store <message number> <file name>\n";

    if (!msg_num)
	return str + "The board is empty.\n";

    str += "The bulletin board contains " + msg_num +
	(msg_num == 1 ? " note" : " notes") + " :\n\n";

    if (this_object()->check_reader())
	return str;

    if (!silent && present(this_player(), environment()))
	say(QCTNAME(this_player()) + " studies the bulletin board.\n");

    ind = 0;
    while (ind < msg_num)
    {
	str += sprintf("%2d: %s\n", (ind + 1), headers[ind][0]);
	ind++;
    }
    return str;
}

int new_msg(string str);
int read_msg(string str, int mr);
int remove_msg(string str);
int store_msg(string str);

/*
 * Function name: init
 * Description  : Link the commands to the player.
 */
public void
init()
{
    ::init();

    add_action(new_msg,    "note");
    add_action(read_msg,   "read");
    add_action(read_msg,   "mread");
    add_action(remove_msg, "remove");
    add_action(store_msg,  "store");
}

/*
 * Function name: extract_headers
 * Description  : This is a map function that reads the note-file and
 *                extracts the headers of the note.
 * Arguments    : string str - the name of the note.
 * Returns      : string* - ({ header-string, note-name })
 */
public string *
extract_headers(string str)
{
    string title;

    seteuid(getuid());

    if (!stringp(title = read_file(board_name + "/" + str, 1, 1)))
	return 0;

    return ({ extract(title, 0, strlen(title) - 2), str });
}

/*
 * Function name: query_latest_note
 * Description  : Find and return the name of the last note on the board.
 * Returns      : string - the filename (without path) of the last note
 *                         on the note or 0 if no notes are on the board.
 */
public string
query_latest_note()
{
    return (msg_num ? headers[msg_num - 1][1] : 0);
}

/*
 * Function name: query_num_messages
 * Description  : Find a return the number of messages on this board.
 * Returns      : int - the number of messages on the board.
 */
public int
query_num_messages()
{
    return msg_num;
}

/*
 * Function name: query_board_name
 * Description  : Return the name (path) of the board.
 * Returns      : string - the name of the board (path-name)
 */
public string
query_board_name()
{
    return board_name;
}

/*
 * Function name: new_msg
 * Description  : Write a note.
 * Arguments    : string msg_head - the header of the header.
 * Returns      : int 1/0 - success/failure.
 */
public nomask int
new_msg(string msg_head)
{
    object tp = this_player();
    string date;

    /* Player is not allowed to write a note on this board. */
    if (this_object()->check_writer())
	return 1;

    if (!strlen(msg_head))
    {
	notify_fail("Please add a header.\n");
	return 0;
    }
    if (strlen(msg_head) > 40)
    {
	write("Message header too long. Try again.\n");
	return 1;
    }

    if (present(tp, environment()))
    {
	say(QCTNAME(tp) + " starts writing a note.\n");
    }

    /* We use an independant editor and therefore we must save the header
     * the player has typed. When the player is done editing, the header
     * will be used again to save the message.
     */
    date = (show_lvl ? sprintf("(%2d) ", tp->query_wiz_level()) : "") +
	ctime(time())[4..9];
    writing[tp] = sprintf("%-40s (___) %-11s %s",
	msg_head,
	((anonymous && tp->query_invis()) ? "someone" :
	    capitalize(tp->query_real_name())),
	date);

    seteuid(getuid());

    clone_object(EDIT_OBJECT)->edit("done_editing", "");
    return 1;
}

/*
 * Function name: error_log
 * Description  : If there is an error, this function takes care of it.
 * Arguments    : string str - the error message.
 */
private void
error_log(string str)
{
    tell_room(environment(), "Board says '" + str + "'.\n");
    log_file(err_log, "Board : " + str);
}

/*
 * Function name: discard_message
 * Description  : When there are too many notes on the board, the oldest
 *                is discarded. It is either moved or deleted.
 * Arguments    : string file - the file (without path) to save.
 */
static void
discard_message(string file)
{
    seteuid(getuid());

    if (keep_discarded)
    {
	if (file_size(board_name + "_old") == -1)
	    mkdir(board_name + "_old");
	rename(board_name + "/" + file,
	       board_name + "_old/" + file);
    }
    else
    {
	rm(board_name + "/" + file);
    }
}

/*
 * Function name: done_editing
 * Description  : When the player is done editing the note, this function
 *                will be called with the message as parameter. If all
 *                is well, we already have the header.
 * Arguments    : string message - the note typed by the player.
 * Returns      : int - 1/0 - true if the note was added.
 */
public int
done_editing(string message)
{
    string fname;
    string head;
    object tp = this_player();

    if (!strlen(message))
    {
	write("No message entered.\n");
	if (present(tp, environment()))
	{
	    say(QCTNAME(tp) + " quits writing a note.\n");
	}

	writing = m_delete(writing, tp);
	return 0;
    }

    if (!strlen(writing[tp]))
    {
	error_log("No header from: " +
	    capitalize(tp->query_real_name()) + ".\n");
	return 0;
    }

    while(msg_num >= notes)
    {
	discard_message(headers[0][1]);
	headers = exclude_array(headers, 0, 0);
	msg_num--;
    }

    seteuid(getuid());

    if (file_size(board_name) == -1)
    {
	mkdir(board_name);
    }

    fname = "b" + time();
    head = writing[tp][..41] + sprintf("%3d", sizeof(explode(message, "\n"))) +
	writing[tp][45..];
    writing = m_delete(writing, tp);
    write_file(board_name + "/" + fname, head + "\n" + message);
    headers += ({ ({ head, fname }) });
    msg_num++;

    if (present(tp, environment()))
    {
	say(QCTNAME(tp) + " has completed a note :\n" + head + "\n");
    }

    write("Ok.\n");

    if (!no_report)
    {
	BOARD_CENTRAL->new_note(board_name, fname, MASTER_OB(environment()));
    }

    return 1;
}

/*
 * Function name: read_msg
 * Description  : Read a message on the board
 * Arguments    : string what_msg - the message number.
 *                int    mr       - read with more if true.
 * Returns      : int 1/0 - success/failure.
 */
public varargs int
read_msg(string what_msg, int mr)
{
    int note;

    /* Player is not allowed to read. */
    if (this_object()->check_reader())
	return 1;

    if (!what_msg)
    {
	notify_fail(break_string("You read a while but as you can't decide "+
	    "exactly what to read, you don't find much of interest.\n", 75));
	return 0;
    }

    if (!sscanf(what_msg, "%d", note))
    {
	if (!sscanf(what_msg, "note %d", note))
	{
	    notify_fail("Read what?\n");
	    return 0;
	}
    }

    if (note < 1 || note > msg_num)
    {
	notify_fail("Not that many messages.\n");
	return 0;
    }

    note--;
    if (!silent && present(this_player(), environment()))
    {
	say(QCTNAME(this_player()) + " reads a note titled:\n" +
	    headers[note][0] + "\n");
    }

    seteuid(getuid());

    if (!mr)
    {
	mr = (query_verb() == "mread");
    }

    if ((atoi(headers[note][0][42..44]) > MAX_NO_MREAD) && !mr)
    {
	write("Too long note. More automatically invoked.\n");
	mr = 1;
    }

    write("You read the note:\n" + headers[note][0] + "\n\n");

    if (mr == 1)
	clone_object(MORE_OBJECT)->more(board_name + "/" + headers[note][1], 2);
    else
	cat(board_name + "/" + headers[note][1], 2);

    return 1;
}

/*
 * Function name: no_special_fellow
 * Description  : Some people can always remove messages and this is the
 *                function to check on it. If you own the board (same
 *                euid) or if the board is in your domain, you can always
 *                remove notes.
 * Returns      : int - if false he is a special fellow.
 */
nomask public int
no_special_fellow()
{
    string name = this_player()->query_real_name();
    string euid = geteuid(this_object());

    /* The board is mine */
    if (name == euid)
	return 0;

    /* The board is my domains */
    if (SECURITY->domain_lord(euid) == name)
	return 0;

    return 1;
}

/*
 * Function name: remove_msg
 * Description  : Remove a note from the board.
 * Arguments    : string what_msg - the message to remove.
 * Returns      : int 1/0 - success/failure.
 */
nomask public int
remove_msg(string what_msg)
{
    string player, title, date;
    int note;

    if (!strlen(what_msg))
    {
	notify_fail("Remove which note?\n");
	return 0;
    }

    if (!sscanf(what_msg, "%d", note))
    {
	if (!sscanf(what_msg, "note %d", note))
	{
	    notify_fail("Remove what?");
	    return 0;
	}
    }
    
    /* Player is not allowed to remove the note. */
    if (this_object()->check_remove())
	return 1;

    if (note < 1 || note > msg_num)
    {
	write("That message doesn't exist.\n");
	return 1;
    }

    note--;
    player = implode(explode(headers[note][0][47..57], "") - ({ " " }), "");
    if ((this_player()->query_real_name() != lower_case(player) &&
	 no_special_fellow() &&
	 this_player()->query_wiz_level() < remove_lvl) ||
	!query_ip_number(this_player()))
    {
	write(remove_str);
	return 1;
    }

    if (present(this_player(), environment()))
    {
	say(QCTNAME(this_player()) + " removes a note:\n" +
	    headers[note][0] + "\n");
    }

    discard_message(headers[note][1]);
    headers = exclude_array(headers, note, note);
    msg_num--;
    if (note == msg_num && !no_report)
	BOARD_CENTRAL->new_note(board_name, note > 0 ? headers[note-1][1] : 0,
	    MASTER_OB(environment()));
    write("Ok.\n");
    return 1;
}

/*
 * Function name: store_msg
 * Description  : Store a message to disk. Some checks are made to see
 *                if SECURITY allows you to save it where you want it.
 * Arguments    : string str - the message to store and the filename.
 * Returns      : int 1/0 - success/failure.
 */
nomask static int
store_msg(string str)
{
    int ret;

    if (this_player()->query_wiz_level() <= WIZLEV_RETIRED)
    {
	write("Sorry, you can't save messages.\n");
	return 1;
    }

    if (this_object()->check_reader())
	return 1;
    if (!str)
    {
	notify_fail("Store what?\n");
	return 0;
    }

    seteuid(0);
    ret = SECURITY->save_allow(str);
    seteuid(getuid());

    return ret;
}

/*
 * Function name: save_info
 * Description  : This function is called by SECURITY when the save is
 *                allowed.
 * Arguments    : object ob  - the player storing.
 *                string str - the command line argument by the player.
 * Returns      : int - 1/0 success/failure.
 */
nomask public int
save_info(object ob, string str)
{
    int note;
    int ret;
    string file;
    string name = ob->query_real_name();

    if (file_name(previous_object()) != SECURITY)
	return 0;
    write("Storing...\n");
    if (sscanf(str, "%d %s", note, file) != 2)
    {
	if (sscanf(str, "note %d %s", note, file) != 2)
	{
	    notify_fail("Store what?\n");
	    return 0;
	}
    }
    if (note < 1 || note > msg_num)
    {
	write("That message doesn't exist.\n");
	return 1;
    }

    file = "/d/" + (SECURITY->query_wiz_dom(name)) + "/" + name +
	"/" + file + ".note";

    seteuid(getuid());

    ret = write_file(file, read_file(board_name + "/" + headers[note - 1][1]));

    seteuid(0);
    write("Ok.\n");
    return ret;
}

/*
 * Function name: query_headers
 * Description  : Return the headers if this_player() is allowed to see
 *                them.
 * Returns      : mixed - the headers
 *                        ({ ({ string header, string filename }) })
 */
public mixed
query_headers()
{
    if (this_object()->check_reader())
	return ({ });

    return headers;
}
