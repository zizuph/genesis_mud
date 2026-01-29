/*
* This is a new board, which is programwise compatible with the old.
* However, the file format is totally different.
* 920221 /Tintin
*/

/* Example of use:
* inherit "std/board";
* 
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
*	After setting it up this way you just need to clone it and move it
*	to the location where you want it.
*
*	The following options can be set:
*	set_num_notes(n)	Set max number of notes (default 30)
*	set_silent(n)		0 = Tell room about read and examine of the 
*				board 1 = silent read & examine,
*				(default 1)
*	set_anonymous(n)	0 = No anonymous posts, 1 = make articles
*				made by invisible persons come out as written
*				by 'Someone' (default 0)
*	set_board_name(name)	Path to the save directory for the board
*				(no default, this variable MUST be set)
*                               Old notes will be stored in a directory with
*                               the same name, with _old appended
*	set_remove_lvl(n)	Minimum level required to remove other
*				players notes (default 24)
*	set_remove_str(str)	The string to send to the player if a
*				remove failed. (default 'Only an Archwizard 
*				can remove other peoples notes')
*	set_err_log(str)	Name of the log to where error messages
*				should go. (default 'BOARDS', but you
*				MUST change it since only /obj and /room
*				objects can write to this file)
*	set_show_lvl(n)		0 = Don't show level in note header,
*				1 = show level of writer in note header
*				(default 1)
*	set_no_report(n)	0 = Keep the central board notified.
*				1 = Don't notify the central board.
*				    This makes the board 'secret'.
*	set_keep_discarded(n)	Keep discarded notes.
*                               0 = don't keep old notes
*                               1 = keep old notes
*                               (default 0)
*/

inherit "/std/object";

#include <macros.h>
#include <std.h>
#include <stdproperties.h>

#define BOARD_CENTRAL "/std/board/board_central"
#define BOARD_WRITER "/std/board/msg_input"
#define GEDITOR "/std/board/bb_gedit"
#define MORE_OBJ "/std/board/board_more"

static private mixed *headers = ({ });
static private int   line, looked_at, keep_discarded = 0;
static private string board_name = "",
    remove_str = "Only an Archwizard can remove other peoples notes.\n",
    err_log = "BOARDS";
static private int notes = 30, silent = 1, anonymous = 0, show_lvl = 1,
    no_report = 0, msg_num, remove_lvl = (WIZLEV_LORD + 1), fuse = 0;

/*
 * Prototypes
 */
private void error_log(string str);
static void discard_message(string file_name);
private void mread_msg(string message);
public void load_headers();

/*
 * These functions are made for setting up the board in the file
 * inheriting it.
 */
void
set_num_notes(int n)
{
    if (!fuse)
	notes = n;
}

void	
set_silent(int n)
{ 
    if (fuse)
	return;
    silent = (n ? 1 : 0);
}

void
set_anonymous(int n)
{
    if (fuse)
	return;
    anonymous = (n ? 1 : 0); 
}

void
set_no_report(int n)
{
    if (fuse)
	return;
    no_report = (n ? 1 : 0); 
}

void
set_board_name(string str)
{
    if (fuse)
	return;
    board_name = str; 
}

void
set_remove_lvl(int n) 
{
    if (fuse)
	return;
    remove_lvl = n; 
}

void
set_remove_str(string str)
{
    if (fuse)
	return;
    remove_str = str; 
}

void
set_err_log(string str)
{
    err_log = str; 
}

void
set_show_lvl(int n) 
{
    if (fuse)
	return;
    show_lvl = (n ? 1 : 0);
}

void
set_fuse() { fuse = 1; }

varargs void
set_keep_discarded(int n) { keep_discarded = (n >= 0 ? n : -n); }


/* 
   These functions are hooks that can be replaced with custom functions
   for selecting who may read, write or remove messages in an inherited
   board.
*/
varargs int check_reader() { return 0; }
varargs int check_writer() { return 0; }
varargs int check_remove() { return 0; }

public mixed
long()
{
    int ind;
    string str = "This is a bulletin board.\n";
    str += "Usage : note/gnote <headline>, remove <message number>\n";

    if (this_player()->query_wiz_level() > WIZLEV_RETIRED)
        str += "        store <message number> <file name>\n";

    str += "        read/mread <message number> \n";
    str += "Gnote will give you an ed-like editor, mread will do 'more'.\n";
    
    if (!msg_num) 
	return str + "The board is empty.\n";
    
    str += "The bulletin board contains " + msg_num +
	(msg_num == 1 ? " note" : " notes") + " :\n\n";
    
    /* Only give the headers if you are allowed to see them.
     */
    if (check_reader())
        return str;

    if (!silent && present(this_player(), environment()))
	say(QCTNAME(this_player()) + " studies the bulletin board.\n");

    for (ind = 0; ind < msg_num; ind++)
        str += "" + (ind + 1) + ":\t" + headers[ind][0] + "\n";

    return str;
}

public void
init()
{
    ::init();
    add_action("new_msg", "note");
    add_action("new_msg", "gnote");
    add_action("read_msg", "read");
    add_action("read_msg", "mread");
    add_action("remove_msg", "remove");
    add_action("store_msg", "store");
    load_headers();
}

string *
extract_headers(string str)
{
    string title;
    title = read_file(board_name + "/" + str, 1, 1);
    return ({ extract(title, 0, strlen(title) - 2), str });
}

nomask void
reset_object()
{
    if (!random(5))
    {
	tell_room(environment(this_object()),
			      "A small gnome appears and secures some " +
			      "notes on the board that were loose.\n" +
			      "The gnome leaves again.\n");
    }
}

nomask void
create_object()
{
    ::create_object();
    
    set_name(({"board", "bulletin board", "bulletinboard" }));
    add_prop(OBJ_I_NO_GET, "It's firmly secured to the ground.\n");
    set_short("bulletin board");
    this_object()->create_board();
    set_alarm(1.0, -1.0, "set_fuse");
}

public void
load_headers()
{
    if (!looked_at)
    {
	string *arr;
	seteuid(getuid());
	looked_at = 1;
	arr = get_dir(board_name + "/*");
	arr = slice_array(arr, 2, sizeof(arr) - 1); /* get rid of . and .. */
	headers = map(arr, "extract_headers", this_object());
	msg_num = sizeof(headers);
    }
}

public string
query_latest_note()
{
    return (msg_num ? headers[msg_num - 1][1] : 0);
}

public string
query_board_name()
{
    return board_name;
}

public nomask int
new_msg(string msg_head, int gn)
{
    line = 1;
    if (check_writer())
	return 1;
    if (!msg_head)
	return 0;
    if (strlen(msg_head) > 50)
    {
	write("Message header too long. Try again.\n");
	return 1;
    }
    say(QCTNAME(this_player()) + " starts writing a note.\n");
    
    clone_object((query_verb() == "gnote" || gn == 1) ?
		 GEDITOR : BOARD_WRITER)->
	new_msg(msg_head, show_lvl, anonymous);
    return 1;
}

void
insert_message(string head, string message)
{
    string fname;

    if (msg_num >= notes)
    {
	discard_message(headers[0][1]);
	headers = exclude_array(headers, 0, 0);
	msg_num--;
    }
    if (file_size(board_name) == -1)
	mkdir(board_name);

    fname = "b" + time();
    write_file(board_name + "/" + fname,
	       head + "\n" + message);
    headers += ({ ({ head, fname }) });
    msg_num++;
    if (no_report == 0)
	BOARD_CENTRAL->new_note(board_name, fname,
			    MASTER_OB(environment(this_object())));

}

public int
read_msg(string what_msg, int mr)
{
    int note;

    if (check_reader())
	return 1;
    if (!what_msg)
    {
	notify_fail(break_string("You read a while but as you can't decide "+
		    "exactly what to read, you don't find much of "+
		    "interest.\n", 76));
	return 0;
    }
    if (!sscanf(what_msg, "%d", note))
	if (!sscanf(what_msg, "note %d", note))
	    return 0;
    if (note < 1 || note > msg_num)
    {
	write("Not that many messages.\n");
	return 1;
    }
    note--;
    if (!silent && present(this_player(), environment(this_object())))
    {
	say(QCTNAME(this_player()) + " reads a note titled '" +
	    headers[note][0] + "'.\n");
    }
    
    write("The note is titled '" + headers[note][0] + "':\n\n");
    if (query_verb() == "mread" || mr == 1)
	mread_msg(board_name + "/" + headers[note][1]);
    else
	cat(board_name + "/" + headers[note][1], 2);
    return 1;
}

private void
mread_msg(string file)
{
    clone_object(MORE_OBJ)->more(file, 2);
}

/* 
 * Some people can always remove messages
 */
int
no_special_fellow()
{
    string name, euid;
    
    name = this_player()->query_real_name();
    euid = geteuid(this_object());

    /* The board is mine */
    if (name == euid)  
	return 0;
    
    /* The board is my domains */
    if ("/secure/master"->domain_lord(euid) == name)
	return 0;

    return 1;
}
    

nomask public int
remove_msg(int what_msg)
{
    string player, title, date;
    int note;
    if (check_remove())
	return 1;
    if (!sscanf(what_msg, "%d", note)) 
	if (!sscanf(what_msg, "note %d", note))
	    return 0;
    if (note < 1 || note > msg_num)
    {
	write("That message doesn't exist.\n");
	return 1;
    }
    note--;
    if (sscanf(headers[note][0], "%s(%s,%s", title, player, date) != 3)
    {
	error_log("Header error");
	write("Board : error - header corrupt.\n");
	return 1;
    }
    if ((this_player()->query_real_name() != lower_case(player) &&
	 no_special_fellow() && 
	 this_player()->query_wiz_level() < remove_lvl) ||
	!query_ip_number(this_player()))
    {
	write(remove_str);
	if (!silent && present(this_player(), environment(this_object())))
	    say(QCTNAME(this_player()) + " failed to remove " + "a note.\n");
	return 1;
    }
    if (!silent && present(this_player(), environment(this_object())))
	say(QCTNAME(this_player()) + " removes a note titled '" +
	    headers[note][0] + "'.\n");
    discard_message(headers[note][1]);
    headers = exclude_array(headers, note, note);
    msg_num--;
    if (note == msg_num && no_report == 0)
	BOARD_CENTRAL->new_note(board_name, note > 0 ? headers[note-1][1] : 0,
				MASTER_OB(environment(this_object())));
    write("Ok.\n");
    return 1;
}

nomask static int
store_msg(string str)
{
    int ret;
    if (this_player()->query_wiz_level() <= WIZLEV_RETIRED)
    {
	write("Sorry, you can't save messages.\n");
	return 1;
    }
    if (check_reader())
	return 1;
    if (!str) 
	return 0;
    seteuid(0);
    ret = "/secure/master"->save_allow(str);
    seteuid(getuid());
    return ret;
}

nomask int
save_info(object ob, string str)
{
    int note, ret;
    string file, name;

    if (file_name(previous_object()) != "/secure/master")
	return 0;
    write("Storing...\n");
    if (sscanf(str, "%d %s", note, file) != 2)
	if (sscanf(str, "note %d %s", note, file) != 2)
	    return 0;
    if (note < 1 || note > msg_num)
    {
	write("That message doesn't exist.\n");
	return 1;
    }
    name = ob->query_real_name();
    file = "/d/" + ("secure/master"->query_wiz_dom(name)) + "/" + name +
	"/" + file + ".note";
    seteuid(getuid());
    ret = write_file(file, read_file(board_name + "/" + headers[note - 1][1]));
    seteuid(0);
    write("Ok.\n");
    return ret;
}

private void
error_log(string str)
{
    tell_room(environment(this_object()), "Board says '" + str + "'.\n");
    log_file(err_log, "Board : " + str);
    return;
}

static void
discard_message(string file)
{

    if (keep_discarded)
    {
	if (file_size(board_name + "_old") == -1)
	    mkdir(board_name + "_old");
	rename(board_name + "/" + file,
	       board_name + "_old/" + file);
    }
    else
	rm(board_name + "/" + file);
}

public mixed 
query_headers()
{
    if (check_reader())
	return ({ });

    return headers;
}
