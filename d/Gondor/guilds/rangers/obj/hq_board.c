/* 
 * /d/Gondor/guilds/rangers/obj/hq_board.c
 * 
 * This board allows anonymous postings by company Rangers in the
 * headquarters to preserve their identity. Ideas and some code 
 * borrowed from Aridor's thief board.
 * 
 * Borrowed and modified by Gwyneth, 5 April 2002
 */
inherit "/d/Gondor/std/board";

#include "../rangers.h"
#include "/d/Gondor/defs.h"

#include <macros.h>
#include <std.h>

#define MAX_HEADER_LENGTH 41
#define AUTHORS           (RANGERS_BOARD + "authors")

/* Global variables */
private static mapping gWriting = ([]);
private mapping        gAuthors = ([]);

/* Prototypes */
public void        create_board();
public varargs int block_reader(int note = 0);
public int         block_writer();
public varargs int allow_remove(int note = 0);
public int         block_discard(string file);
public void        init();
public int         anon_note(string header);
public nomask int  anon_done_editing(string message);

public void
create_board()
{
    /* Allow editor cloning */
    seteuid(getuid());

    set_long("This is the bulletin board for the Ranger Headquarters. " +
        "Your identity will not be revealed if you are a company " +
        "Ranger. However, do not abuse this ability by being abusive " +
        "or deceptive lest you have this ability revoked.\n");

    /* The directory that the notes are stored in. */
    set_board_name(RANGERS_BOARD + "hq_board");

    /* Restore the gAuthors mapping that keeps track of anonymous posters */
    gAuthors = restore_map(AUTHORS);

    /* 50 notes on the board before it scrolls */
    set_num_notes(50);

    /* No messages about other people reading or finishing a post. */
    set_silent(1);

    /* Don't display the rank of the authors in the posts */
    set_show_lvl(0);

    /* You must be a Lord or higher to remove posts */
    set_remove_rank(WIZ_LORD);

    /* What a person without remove permissions sees. */
    set_remove_str("The note is stuck to the board.\n");
}

/* Function name: block_reader
 * Description  : Checks if someone is allowed to read the board.
 *                Checks if the player wrote the note anonymously,
 *                and lets us know who it is if it's a Lord+ reading.
 * Arguments    : int note - the note number referred to
 * Returns      : 0 if they can read, 1 if not
 */
public varargs int
block_reader(int note = 0)
{
    int in_the_know = 0;
    object reader = this_player();
    string writer, name = reader->query_real_name();


    /* Allow Lord+, guildmasters and officers of the writer's company
       to see the real name of the poster. */
    if (note && 
      (SECURITY->query_guild_is_master(RANGERS_SHORT_GUILD_NAME, name) ||
       SECURITY->query_wiz_rank(name) >= WIZ_LORD ||
       MANAGER->query_is_council(name)))
    {
        /* Get the name of the writer if anonymous */
        writer = gAuthors[query_board_name() + "/" + 
            query_headers()[note-1][1]];

        if (strlen(writer))
        {
            if (this_player()->query_wiz_level() ||
              MANAGER->query_council(name, 
                  MANAGER->query_ranger_company(writer)))
            {
                write("The real author of this note is: " + 
                    capitalize(writer) + ".\n");

                in_the_know = 1;
            }
        }
    }

    /* Rangers and wizards of Lord+ or of Gondor or GMs can read it. */
    if (RANGERS_MEMBER(reader) || in_the_know ||
      SECURITY->query_wiz_dom(name) == "Gondor")
        return 0;
    else
        return 1;
}

/* Function name: block_writer
 * Description  : Only let Rangers and wizards post.
 * Returns      : 0 if allowed, 1 if not
 */
public int
block_writer()
{
    if (RANGERS_MEMBER(this_player()) || 
      this_player()->query_wiz_level())
        return 0;
    else
        return 1;
}

/* Function name: allow_remove
 * Description  : Checks if the player wrote the note anonymously,
 *                and allows removal if so. Also allows removal by
 *                the player's officers.
 * Arguments    : int note - is a note number given?
 * Returns      : 1 - allowed to remove it, 0 - not allowed
 */
public varargs int 
allow_remove(int note = 0)
{
    string name = this_player()->query_real_name(), 
           company = MANAGER->query_ranger_company(name);

    if (note && 
      (name == gAuthors[query_board_name() + "/" + query_headers()[note-1][1]]
       || MANAGER->query_council(name, company)))
        return 1;
    else
        return 0;
}

/* Function name: block_discard
 * Description  : Mask the block_discard function to delete the note
 *                and author from the mapping whenever a note is
 *                removed, either naturally scrolled or physically.
 * Arguments    : string file - the note to remove
 * Returns      : 0 always to allow discarding the note
 */
public int
block_discard(string file)
{
    if (gAuthors[query_board_name() + "/" + file])
    {
        gAuthors = m_delete(gAuthors, query_board_name() + "/" + file);
        save_map(gAuthors, AUTHORS);
    }

    return 0;
}

/* Function name: init
 * Description  : Masked to add actions to a player. Steals the 'note'
 *                action and puts some filters on it.
 */
public void
init()
{
    ::init();

    /* Override the mask command to filter out company members. */
    add_action(anon_note, "note");
}

/*
 * Function name: anon_note
 * Description  : Filter out company members from non. Company members
 *                will automatically be listed as "RoI Ranger"
 *                or "RoN Ranger" or by "RoN Capt.", etc. if an officer.
 * Arguments    : string header - the text of the header.
 * Returns      : int 1/0 - success/failure.
 */
public int
anon_note(string header)
{
    /* Simply return 0, no message. This will throw them into the 
       default note posting. */
    if (!NORTH_MEMBER(this_player()) && 
      !ITHILIEN_MEMBER(this_player()))
        return 0;

    /* Wizards shouldn't post anonymously. */
    if (this_player()->query_wiz_level())
        return 0;

    /* Player is not allowed to write a note on this board. */
    if (check_writer())
    {
        notify_fail("You are not allowed to write here.\n");
        return 0;
    }
    else if (!stringp(header))
    {
        notify_fail("Please add a header.\n");
        return 0;
    }
    else if (strlen(header) > MAX_HEADER_LENGTH)
    {
        write("Message header too long. Try again.\n");
        return 1;
    }

    this_player()->add_prop(LIVE_S_EXTRA_SHORT, " is writing a note");

    /* We use an independant editor and therefore we must save the header
     * the player has typed. When the player is done editing, the header
     * will be used again to save the message. Don't you just love these
     * kinds of statments.
     */
    gWriting[this_player()] = sprintf("%-*s", MAX_HEADER_LENGTH-1, header);

    clone_object(EDITOR_OBJECT)->edit(anon_done_editing, "");
    return 1;
}


/*
 * Function name: anon_done_editing
 * Description  : When the player is done editing the note, this function
 *                will be called with the message as parameter. If all
 *                is well, we already have the header.
 * Arguments    : string message - the note typed by the player.
 * Returns      : int - 1/0 - true if the note was added.
 */
public nomask int
anon_done_editing(string message)
{
    int rank;
    string head, name, company, post_id = "Unknown";

    this_player()->remove_prop(LIVE_S_EXTRA_SHORT);

    if (!strlen(message))
    {
        write("No message entered.\n");

        gWriting = m_delete(gWriting, this_player());
        return 0;
    }

    if (!stringp(gWriting[this_player()]))
    {
        write("Your header has been lost! No note posted. " +
            "Please make a bug report!\n");
        return 0;
    }

    head = gWriting[this_player()];
    gWriting = m_delete(gWriting, this_player());

    name = this_player()->query_real_name();
    company = MANAGER->query_ranger_company(name);
    rank = MANAGER->query_council(name, company);

    /* Resort to abbreviations to make any sense within 11 characters */
    switch(rank)
    {
    case -1:
        if (company == "ithilien")
            post_id = "RoI Ranger";
        else if (company == "north")
            post_id = "RoN Ranger";

        break;
    case 0:
        if (company == "ithilien")
            post_id = "RoI Capt.";
        else if (company == "north")
            post_id = "RoN Capt.";

        break;
    case 1:
        if (company == "ithilien")
            post_id = "RoI Lt.";
        else if (company == "north")
            post_id = "RoN Lt.";

        break;
    case 2:
        if (company == "ithilien")
            post_id = "RoI Sgt.";
        else if (company == "north")
            post_id = "RoN Sgt.";

        break;
    default:
        break;
    }

    seteuid(getuid());
    if (this_object()->create_note(head, post_id, message))
    {
        gAuthors += ([query_board_name() + "/" + query_latest_note():
            this_player()->query_real_name()]);

        write("Ok.\n");

        save_map(gAuthors, AUTHORS);

        /* Allows us to cycle the log. */
        MANAGER->rlog(AUTHORS, "" + query_latest_note() + " " +
            CAP(name) + "\n");
    }
    else
        write("Failed.\n");

    return 1;
}
