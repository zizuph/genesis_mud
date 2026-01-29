/* Board of the Cabal of Hiddukel Thief guild.
 *
 * Originally coded by:
 *   Aridor, ../95
 *
 * Revision history:
 *   Aridor, ../96:  Added Ringleader support for writing special
 *                   notes, and allowing removal of all notes.
 *   Aridor, 10/97:  Added anonymous posting option.
 */

#include "../guild.h"
#include <macros.h>
#include <std.h>

#define LOGFILE           "/d/Krynn/solamn/thief/guild/log/notewriter"
#define GUEST_NAME        "guest"
#define MAX_HEADER_LENGTH  41

/* Set this to 0 to disallow anonymous postings on this board. */
#define ANONYMOUS_POSTING  1


inherit "/std/board";


#if ANONYMOUS_POSTING
private static mapping my_writing = ([ ]);
private mapping authors = ([]);
#endif


void
create_board()
{
    seteuid(getuid());
    set_board_name(LOG + "board_data");
    set_short("the Cabal of Hiddukel Burglar Board");
#if ANONYMOUS_POSTING
    set_long("It is a bulletin board.\n" +
	     "Special feature is anonymous posting, usage: anote <headline>\n");
    authors = restore_map(LOGFILE);
#endif
    set_num_notes(30);
    set_silent(0);
    set_show_lvl(0);
    set_no_report(1);
    set_keep_discarded(1);
    set_remove_rank(WIZ_MAGE);
    set_remove_str("Sorry, Only a Mage or higher may remove the notes.\n");
}

varargs int
block_reader(int note = 0)
{
#if ANONYMOUS_POSTING
    string tmp;

    if (note && SECURITY->query_wiz_rank(TP->query_real_name()) >= WIZ_MAGE)
      if (tmp = authors[query_board_name() + "/" + query_headers()[note-1][1]])
	write("Real author of this note is: " + C(tmp) + ".\n");
#endif
    
    if (MEMBER(TP) || LAYMAN(TP) || TP->query_wiz_level())
      return 0;
    return 1;
}

int
block_writer()
{
    if (MEMBER(TP) || LAYMAN(TP) || TP->query_wiz_level())
      return 0;
    return 1;
}

/* We want to allow the masterthief to remove all notes from the board */
varargs int
allow_remove(int note = 0)
{
    if (TP->query_real_name() == MASTER_ROOM->query_master_thief())
      return 1;
#if ANONYMOUS_POSTING
    if (note &&
	TP->query_real_name() == authors[query_board_name() + "/" +
					 query_headers()[note-1][1]])
      return 1;
#endif
    return 0;
}

#if ANONYMOUS_POSTING

int
block_discard(string file)
{
    if (authors[query_board_name() + "/" + file])
    {
	authors = m_delete(authors, query_board_name() + "/" + file);
	save_map(authors, LOGFILE);
    }
    return 0;
}



void
init()
{
    ::init();
    ADA("anote");
}

/*
 * Function name: note
 * Description  : Write a note.
 * Arguments    : string msg_head - the header of the header.
 * Returns      : int 1/0 - success/failure.
 */
int
anote(string msg_head)
{

    if (this_player()->query_real_name() == GUEST_NAME)
    {
	write(break_string("You are a guest of " +
	    SECURITY->query_mud_name() + " and as such you cannot write on " +
	    "bulletin boards. If you want to participate in the discussion " +
	    "you should create yourself a real character. We are always " +
	    "pleased to welcome a new player to the game.", 75) + "\n");
	return 1;
    }

    /* Player is not allowed to write a note on this board. */
    if (check_writer())
    {
        notify_fail("You are not allowed to write here.\n");
	return 0;
    }

    if (!stringp(msg_head))
    {
	notify_fail("Please add a header.\n");
	return 0;
    }
    if (strlen(msg_head) > MAX_HEADER_LENGTH)
    {
	write("Message header too long. Try again.\n");
	return 1;
    }

    if (this_player()->query_wiz_level() &&
	this_player()->query_name() != "Aridor")
    {
	NF("Wizards cannot write as 'Anonymous'...\n");
	return 0;
    }

    if (present(this_player(), environment()))
    {
	say(QCTNAME(this_player()) + " starts writing a note.\n");
    }

    this_player()->add_prop(LIVE_S_EXTRA_SHORT, " is writing a note");

    /* We use an independant editor and therefore we must save the header
     * the player has typed. When the player is done editing, the header
     * will be used again to save the message. Don't you just love these
     * kinds of statments.
     */
    my_writing[this_player()] = sprintf("%-*s", MAX_HEADER_LENGTH-1,
					msg_head);

    seteuid(getuid());

    clone_object(EDITOR_OBJECT)->edit("my_done_editing", "");
    return 1;
}


/*
 * Function name: done_editing
 * Description  : When the player is done editing the note, this function
 *                will be called with the message as parameter. If all
 *                is well, we already have the header.
 * Arguments    : string message - the note typed by the player.
 * Returns      : int - 1/0 - true if the note was added.
 */
public nomask int
my_done_editing(string message)
{
    string head;

    this_player()->remove_prop(LIVE_S_EXTRA_SHORT);

    if (!strlen(message))
    {
	write("No message entered.\n");
	if (present(this_player(), environment()))
	{
	    say(QCTNAME(this_player()) + " quits writing a note.\n");
	}

	my_writing = m_delete(my_writing, this_player());
	return 0;
    }

    if (!stringp(my_writing[this_player()]))
    {
    	write("Your header has been lost! No note posted. " +
    	    "Please report this!\n");
	return 0;
    }

    head = my_writing[this_player()];
    my_writing = m_delete(my_writing, this_player());

    if (this_object()->create_note(head, "Anonymous", message))
    {
	authors += ([query_board_name() + "/" + query_latest_note():
		     this_player()->query_real_name()]);
	write("Ok.\n");
	save_map(authors, LOGFILE);
	write_file(LOGFILE,"" + query_latest_note() + " " +
		   this_player()->query_name() + "\n");
    }
    else
      write("Failed.\n");
    return 1;
}
#endif
