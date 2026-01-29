/* The Union board
 *    Cirion, 032996
 *
 * Revisions:
 * 	??? Jul 1997: Allow Elders of the Union to post anonymously
 * 			under the name "Elders"
 *	??? Jan 2001: Changed the checks for read/write functions
 *                    to correctly check if a person is in the
 *                    environment. /Manat
 *	Lucius, Jul 2017: Re-Code.
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/board";

#include <std.h>
#include <macros.h>
#include <stdproperties.h>

#define ELDERS_NOTE_NAME   "elders"
#define VOICE_NOTE_NAME    "voice"
#define MIN_HEADER_LENGTH  10
#define MAX_HEADER_LENGTH  41

private static mapping elder_writing = ([ ]),
		       voice_writing = ([ ]);

public void
create_board()
{
    reset_euid();

    set_board_name(BOARDS+"board");
    set_num_notes(47);
    set_silent(1);
    set_show_lvl(0);
    set_keep_discarded(1);
    set_remove_str("You are not permitted.\n");
    set_no_show_composite(1);
    remove_name("board");
    set_name("tablet");
    set_long("It is a massive gneiss tablet, framed by a pool "+
	"of pale white light falling atop it. The surface is "+
	"covered in strange and almost luminous scrawlings.\n"+
	VBFC_ME("elder_board_msg"));
}

public string
elder_board_msg(void)
{
    string str = "";

    if (IS_ELDER(TP) || IS_GMASTER(TP))
    {
	str += "You may post under the name \"Elders\" with "+
	    "the command \"eldernote\".\n";  
    }

    if (MEMBER_SPHERE(TP, SPH_VOICE))
    {
	str += "You may post under the name \"Voice\" with "+
	    "the command \"voicenote\".\n";
    }
    return str;
}

public int
block_reader(void)
{
    object tp = this_player();
    string name = tp->query_real_name();

    if (!IS_MEMBER(tp) &&
	SECURITY->query_wiz_rank(name) < WIZ_MAGE &&
	SECURITY->query_wiz_dom(name) != "Avenir")
    {
	if (environment(tp) == environment(TO))
	    write("You are not permitted to view this board.\n");
	return 1;
    }

    return 0;
}

public int
block_writer(void)
{
    return block_reader();
}

public int
allow_remove(void)
{ 
    if (IS_ELDER(TP))
    {
	if (present(TP, ENV(TO))) // present is for mbs support
	    write("Since you are an Elder, you may remove the note.\n");
	return 1; 
    }

    return (SECURITY->query_wiz_dom(TP->query_real_name()) == "Avenir");
}

/*
 * Function name: elder_note
 * Description  : Write a note with the name "the Elders"
 * Arguments    : string msg_head - the header of the header.
 * Returns      : int 1/0 - success/failure.
 */
public nomask int
elder_note(string msg_head)
{
    string date;

    /* Only the Elders and the Guildmasters may post in this form */
    if (!IS_ELDER(TP) && !IS_GMASTER(TP))
	return 0;

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
    date = " " + ctime(time())[4..9];
    elder_writing[this_player()] = sprintf("%-*s", MAX_HEADER_LENGTH, msg_head);

    clone_object(EDITOR_OBJECT)->edit("done_elder_editing", "");
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
done_elder_editing(string message)
{
    this_player()->remove_prop(LIVE_S_EXTRA_SHORT);

    if (!strlen(message))
    {
	write("No message entered.\n");
	if (present(this_player(), environment()))
	    say(QCTNAME(this_player()) + " quits writing a note.\n");

	m_delkey(elder_writing, this_player());
	return 0;
    }

    string head = elder_writing[this_player()];

    if (!strlen(head))
    {
	write("Your header has been lost! No note posted. " +
	    "Please report this!\n");
	return 0;
    }

    m_delkey(elder_writing, this_player());

    /* create_note() is where we are allowed to externally add a note
     * We need to use the call_other() construction so we outselves
     * wind up being the previous_object(), not the editor object.
     * Bloody security precautions.
     */
    if (!call_other(TO, "create_note", head, ELDERS_NOTE_NAME, message))
    {
	write("Your elder note has been lost! No note posted. " +
	    "Please report this!\n");
	return 0;
    }

    write("You post the note in the name of the Shadow Elders.\n");
    LIST->add_union_message("all",
	"The Elders have written a new note upon the tablet.\n");

    return 1;
}

/*
 * Function name: voice_note
 * Description  : Write a note with the name "the Voice"
 * Arguments    : string msg_head - the header of the header.
 * Returns      : int 1/0 - success/failure.
 */
public nomask int
voice_note(string msg_head)
{
    string date;

    /* Only the Voice, Elders and the Guildmasters may post in this form */
    if (!MEMBER_SPHERE(TP, SPH_VOICE))
	return 0;

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

    if (present(this_player(), environment()))
	say(QCTNAME(this_player()) + " starts writing a note.\n");

    this_player()->add_prop(LIVE_S_EXTRA_SHORT, " is writing a note");

    /* We use an independant editor and therefore we must save the header
     * the player has typed. When the player is done editing, the header
     * will be used again to save the message. Don't you just love these
     * kinds of statments.
     */
    date = " " + ctime(time())[4..9];
    voice_writing[this_player()] = sprintf("%-*s", MAX_HEADER_LENGTH, msg_head);

    clone_object(EDITOR_OBJECT)->edit("done_voice_editing", "");
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
done_voice_editing(string message)
{
    this_player()->remove_prop(LIVE_S_EXTRA_SHORT);

    if (!strlen(message))
    {
	write("No message entered.\n");
	if (present(this_player(), environment()))
	{
	    say(QCTNAME(this_player()) + " quits writing a note.\n");
	}

	voice_writing = m_delete(voice_writing, this_player());
	return 0;
    }

    string head = voice_writing[this_player()];

    if (!strlen(head))
    {
	write("Your header has been lost! No note posted. " +
	  "Please report this!\n");
	return 0;
    }

    voice_writing = m_delete(voice_writing, this_player());

    /* create_note() is where we are allowed to externally add a note
     * We need to use the call_other() construction so we outselves
     * wind up being the previous_object(), not the editor object.
     * Bloody security precautions.
     */
    if (!call_other(TO, "create_note", head, VOICE_NOTE_NAME, message))
    {
	write("Your Voice note has been lost! No note posted. " +
	  "Please report this!\n");
	return 0;
    }

    write("You post the note in the name of the Voice.\n");
    LIST->add_union_message("all",
	"The Voice has written a new note upon the tablet.\n");

    return 1;
}

/*
 * The following is a horrifying kludge to allow the Elders
 * of the Union to post under the name "Elders" (and allow
 * themselves to remain anonymous). All this because everything
 * in /std/board (from which most of the following code was
 * copied) is declared private nomask.
 */
public void
init(void)
{
    ::init();

    add_action(elder_note, "eldernote");
    add_action(voice_note, "voicenote");
}
