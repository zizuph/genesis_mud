/* Voice tablet. To make it easier to track mails and such
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/board";

#include <std.h>
#include <macros.h>
#include <stdproperties.h>


#define ELDERS_NOTE_NAME   "elders"
#define VOICE_NOTE_NAME    "voice"
#define MIN_HEADER_LENGTH   1
#define MAX_HEADER_LENGTH  50
#define MIN_NAME_LENGTH     2
#define MAX_NAME_LENGTH    11
#define AUTHOR_BEGIN       46
#define AUTHOR_END         56

static private mapping elder_writing = ([ ]);
public nomask int elder_note(string msg_head);

void 
create_board()
{
    set_board_name(GUILDLOG +"voice_b");
    set_num_notes(99);
    set_silent(1);
    set_show_lvl(0);
    set_keep_discarded(1);
    set_no_report(1);
    set_remove_rank(0);
    set_remove_str("You are not permitted.\n");
    remove_name("board");
    set_name("notebook");
    add_name("av_v_notebook");
    set_adj(({"voice"}));
    set_short("notebook draped in shadows");
    set_long("This is the notebook for the Voice of the Elders. "+
      "It is rather large, holding nearly a hundred pages. It "+
      "works rather a lot like a board does, and can be used "+
      "to store mails and notes to yourself.\n"
      + VBFC_ME("elder_board_msg"));
    remove_prop(OBJ_M_NO_GET);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 100);
}


/*
 * Function name: reset_board
 * Description  : Since reset_object() is nomasked, you must mask this
 *                function at reset time. Enable_reset() is already
 *                called, so you do not have to do that yourself.
 */
void
reset_board()
{
}

string
elder_board_msg()
{
    if(IS_ELDER(TP) && IS_GMASTER(TP))
	return "You may post under the name \"Elders\" with the command \"eldernote\".\n";  
    else
	return "";
}

int block_reader()
{
    object tp;
    string name;
    tp = this_player();
    name = tp->query_real_name();

    if(!MEMBER_SPHERE(TP, SPH_VOICE) && !IS_ELDER(TP) && !IS_GMASTER(TP))
    {
	if (environment(tp) == environment(TO))
	    write("You are not permitted to view this.\n");
	return 1;
    }

    return 0;
}

int block_writer()
{
    return block_reader();
}

int allow_remove()
{ 
    if (MEMBER_SPHERE(TP, SPH_VOICE))
    {
	if(present(TP, ENV(TO))) // present is for mbs support
	    write("Since you are a Voice, you may remove that page.\n");
	return 1; 
    }

    if(SECURITY->query_wiz_dom(TP->query_real_name()) == "Avenir")
	return 1;

    return 0;
}

/*
 * The following is a horrifying kludge to allow the Elders
 * of the Union to post under the name "Elders" (and allow
 * themselves to remain anonymous). All this because everything
 * in /std/board (from which most of the following code was
 * copied) is declared private nomask.
 */
void
init()
{
    ::init();

    add_action(elder_note, "eldernote");
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
    int    rank;

    /* Only the Elders and the Guildmasters may post in this form */
    if(!IS_ELDER(TP) && !IS_GMASTER(TP))
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
    rank = SECURITY->query_wiz_rank(this_player()->query_real_name());
    date = " " + ctime(time())[4..9];
    elder_writing[this_player()] = sprintf("%-*s", MAX_HEADER_LENGTH, msg_head);

    seteuid(getuid());

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
    string head;

    this_player()->remove_prop(LIVE_S_EXTRA_SHORT);

    if (!strlen(message))
    {
	write("No message entered.\n");
	if (present(this_player(), environment()))
	{
	    say(QCTNAME(this_player()) + " quits writing a note.\n");
	}

	elder_writing = m_delete(elder_writing, this_player());
	return 0;
    }

    if (!stringp(elder_writing[this_player()]))
    {
	write("Your header has been lost! No note posted. " +
	  "Please report this!\n");
	return 0;
    }


    head = elder_writing[this_player()];
    elder_writing = m_delete(elder_writing, this_player());


    /* create_note() is where we are allowed to externally add a note
     * We need to use the call_other() construction so we outselves
     * wind up being the previous_object(), not the editor object.
     * Bloody security precautions.
     */
    if(!call_other(TO, "create_note", head, ELDERS_NOTE_NAME, message))
    {
	write("Your elder note has been lost! No note posted. " +
	  "Please report this!\n");
	return 0;
    }


    write("You post the note in the name of the Shadow Elders.\n");
    return 1;

} // End horrifying kludge

//
//

void 
dust()
{
    object where = ENV(TO);
    string msg = CAP(LANG_THESHORT(TO))+" fades away.\n";

    if(living(where))
	where->catch_msg(msg);
    else
	tell_room(ENV(TO), msg);

    remove_object();
}

// Don't want wrong people getting it, but also want it to be
// able to be put in packs and such.
void 
enter_env(object to, object from)
{
    object *obs;
    int i;

    ::enter_env(to, from);

    //If dropped in a room, dust it.
    if (to->query_prop(ROOM_I_IS))
	set_alarm(1.0, 0.0, dust);

    // If wrong living gets it, dust it
    if (living(to))
    {
	if(!MEMBER_SPHERE(to, SPH_VOICE) && !IS_ELDER(to) && !IS_GMASTER(to))
	    set_alarm(1.0, 0.0, dust);            
    }

    /* Only ever one at a time in a person's inventory */ 
    obs = all_inventory(to);
    for (i = 0; i < sizeof(obs); i++)
    {
	if (obs[i]->id("av_v_notebook") && obs[i] != this_object())
	{
	    obs[i]->remove_object();
	}
    }

}

string 
query_recover()
{
    return 0;
}

string
query_auto_load()
{
    if(!IS_GMASTER(TP))
	return MASTER;
}
