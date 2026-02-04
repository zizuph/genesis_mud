/** tower_epic.c **/
/*
 * Added a max line width of 80 for epic compsition instructions
 * to accommodate players with no limit (-1).
 * Updated by Shanoga, 11/10/2018
 */

#pragma save_binary

inherit "/std/room.c";
#include <macros.h>
#include <stdproperties.h>
#include <options.h>
#include "/d/Terel/common/terel_defs.h"
#include "/d/Terel/cedric/guild/guild_defs.h"
#include "/d/Terel/cedric/guild/guild_funs.c"

#define MORE_OBJ        "/std/board/board_more"
#define EDIT_OBJ	"/obj/edit"

#define MAX_STANZA_LINES 25
#define MAX_LINE_LEN     160
#define MAX_SONG_LEN     15000
#define MAX_SONG_LINES   250
#define MIN_SONG_LINES   3

#define EPIC_TITLE(name) ("The Epic of " + capitalize(name))


/*
 **************************************************************************** 
 * The Minstrel Guild Headquarters: Midway up the Tower
 * The Tower is the famous Library of Songs; on the second level are the
 * great Epics
 * 
 * Cedric 1/93
 */

/*
 * About Songs:  The Songs accessible in this room are Epics. Epics, 
 *               like Ballads, are heard by Minstrels the world over 
 *               whenever one is sung. Each Minstrel may write one Epic 
 *               describing his or her exploits. The title is always 
 *               'The Epic Of XXX' where XXX is the name of the composer. 
 *               Epics need not be approved by the Guildmaster and may be 
 *               changed at any time. Since they are in fact Ballads, the
 *               Epics are placed in ~cedric/guild/Ballads and have the 
 *               suffix .epic appended. The first line of every Epic follows 
 *               the pattern:

 *                             The Epic of Cedric**Cedric
 */

void
init()
{
    ::init();
    add_action("do_compose", "compose");
    add_action("do_read", "read");
    add_action("do_read", "mread");
    add_action("do_copy", "copy");
    add_action("do_say", "sing");
    add_action("do_say", "play");
    add_action("do_say", "perform");
    add_action("do_erase", "erase");
}

int
do_say(string str)
{
    if (0)
    {
	write("The room is silenced; you move your mouth but no sound "
	+ "emerges.\n");
	return 1;
    }
    return 0;
}


string    
epic_list()
{
    int scrw = this_player()->query_option(OPT_SCREEN_WIDTH);
    string str;
    string file = SONG_ROOT + "epic.titles";
    

    setuid();
    seteuid(getuid());

    if ((file_size(file) <= 0) ||
        !strlen(str = read_file(file)))
    {
        return "\tNo epic ballads\n";
    }

    return sprintf("%-#*s\n", scrw, str);
}

int
do_read(mixed str)
{
    mixed songs;

    if (!str)
    {
	return 0;
    }

    str = lower_case(str);
    if (str == "index" || str=="book" || str == "epics")
    {
        say (QCTNAME(TP()) + " studies the index.\n");

	this_player()->more(epic_list());
	return 1;
    }

    if (this_player()->query_skill(SG_READ_MUSIC)<11)
    {
	notify_fail(BS("You have not advanced far enough in the skill of reading "
	+ "music to read the Epics. Why not visit the Training "
	+ "Room?\n"));
	return 0;
    }

    setuid();
    seteuid(getuid());

    songs = SONG_INDEX->parse_song("epic " + str);

    if (!songs)
    {
        notify_fail("Read what?\n");
	return 0;
    }

    if (stringp(songs))
    {
        notify_fail(songs + "\n");
        return 0;
    }

    if (sizeof(songs) > 1)
    {
        write("More than one song matches that title. Be more specific.\n");
	return 1;
    }

    write("You read \"" + SONG_INDEX->query_title(songs[0]) +
          "\", written by " + SONG_INDEX->query_author(songs[0]) + ".\n\n" +
          SONG_INDEX->query_text(songs[0]));
    return 1;

#if 0
    title_list = get_dir(BALLADDIR+"*.epic");
    if (song_file = parse_song("epic", str, ({}), ({}), title_list, ({})))
    {
	clone_object(MORE_OBJ)->more(read_file(song_file, 2));
	return 1;
    }
    if (sscanf(str, "authors %s", first) == 1)
    {
	if (query_verb() == "mread")
	{
	    clone_object(MORE_OBJ)->more(alpha_list(first));
	}
	else
	{
	    write(alpha_list(first));
	}
	return 1;
    }
    if (str == "recent" || sscanf(str, "recent %s", first) == 1)
    {
	int numsongs;
	string authorfirst = "";
	
	if (sscanf(first, "%d %s", numsongs, authorfirst) != 2)
	{
	    if (sscanf(first, "%d", numsongs) != 1)
	    {
		numsongs = 20;
	    }
	}
	if (query_verb() == "mread")
	{
	    clone_object(MORE_OBJ)->more(recent_list(numsongs, authorfirst));
	}
	else
	{
	    write(recent_list(numsongs, authorfirst));
	}
	return 1;
    }
    notify_fail(BS("Which song would you like to read? Try <read xxx> where xxx "
    +" is the number, title (in lowercase), or first word of the title.\n"));
    return 0;
#endif
    return 0;

}

int
do_copy(string str)
{
    notify_fail("You needn't copy the Epics into your song book..they are "
    + "already there!\n");
    return 0;
}

void
create_room()
{
    seteuid(getuid(this_object()));
    set_short("The Minstrels Tower");
    set_long(BS("You stand on the second level of the Minstrel's Tower, "
    + "in a alcove set aside from the rest of the Ballads. Here you "
    + "find the Epics, hallowed Ballads written by each Minstrel to "
    + "describe the exploits of his or her life. Compose here the Epic "
    + "which shall immortalize you and your deeds in song. And since "
    + "people change, and deeds accrue over the course of an adventurous "
    + "life, come back often and compose your Epic anew! As with the "
    + "Ballads, an Epic sung by one will be heard by Minstrels the world "
    + "over. As with all levels of the Tower, a magical silence "
    + "shall descend when a Minstrel begins composing, that none may disturb "
    + "the creative process.\n")+"A handsome index to the Epics.\n");
    
    add_item(({"index", "book", "handsome index"}), "This leather-bound tome "
    + "lists every Epic ever written by a Minstrel. Feel free to "
    + "<read> any Epic you please, or to " 
    + "<compose> your own.\n");
    add_exit(GUILD+"tower_ballad", "west");
    add_prop(ROOM_I_INSIDE, 1);
}

void
silence(object composer)
{
    say(BS("Your skin tingles a though a spell were being cast, yet you hear "
    + "no magic words. In fact you hear nothing at all.."), composer);
}

void
unsilence(object composer)
{
}

/*
 * Function:	done_editing
 * Description:	This function is called by /std/edit after the player gets
 * 		done editing the text of the file. We need to:
 *			- Put a tab in front of any lines which do not
 *			  begin with a # mark or a tab.
 *			- Make sure the ** is on the correct line.
 *			- Prepend with the title**author line.
 *			- Save to the appropriate file.
 */
void
done_editing(string title, string author, string fname, string text)
{
    string *lines, *regex_arr;
    string final_text;
    int previous_line_blank, blank_lines_removed, invalid_lines_removed,
        stanza_size, i, line_cnt;

    if (!strlen(text))
    {
        write("Aborting song composition.\n");
        return;
    }

    setuid();
    seteuid(getuid());

    if (strlen(text) > MAX_SONG_LEN)
    {
        write("\nSong text may contain no more than " + MAX_SONG_LEN +
              " characters. Returning to editor....\n");
        clone_object("/obj/edit")->edit(&done_editing(title, author, fname), text);
        return;
    }

    // We use this array to avoid having to allocate a new one every time
    // we want to do a regexp below.
    regex_arr = allocate(1);

    lines = explode(text, "\n");
    // Start out true so that leading blank lines get deleted
    previous_line_blank = 1;

    for (i = 0; i < sizeof(lines); i++)
    {
        regex_arr[0] = lines[i];
        // Check for blank lines.
        if (!sizeof(regexp(regex_arr, "[^ ]")))
        {
            // If we find more than one blank line in a row, eliminate all
            // but one.
            if (!previous_line_blank)
            {
                stanza_size = 0;
                lines[i] = "";
                previous_line_blank = 1;
                continue;
            }
            else
            {
                lines[i] = 0;
                blank_lines_removed++;
                previous_line_blank = 1;
                continue;
            }
        }
        else
        {
            // Check for comments
            if (lines[i][0] == '#')
            {
                continue;
            }

            // Eliminate lines which contain no alpha-numerics
            if (!sizeof(regexp(regex_arr, "[A-Za-z0-9]")))
            {
                lines[i] = 0;
                invalid_lines_removed++;
                continue;
            }
            else
            {
                if (++stanza_size > MAX_STANZA_LINES)
                {
                    write("\nA stanza exceeds maximum size (" +
                          MAX_STANZA_LINES + " lines).  Returning to " +
                          "editor....\n");
                    clone_object("/obj/edit")->edit(&done_editing(title, author, fname),
                                                    text);
                    return;
                }

                if (strlen(lines[i]) > MAX_LINE_LEN)
                {
                    write("\nLine " + (i + 1) + " exceeds maximum size (" +
                          MAX_LINE_LEN + " characters).  Returning to " +
                          "editor....\n");
                    clone_object("/obj/edit")->edit(&done_editing(title, author, fname),
                                                    text);
                    return;
                }

                previous_line_blank = 0;
                lines[i] = "\t" + lines[i];
                line_cnt++;
                continue;
            }
        }
    }

    // Reusing the lines array, as we have, and doing an implode at the
    // end should be more efficient than concatenating each line normally
    // (with the + operator)
    lines -= ({ 0 });

    if (line_cnt > MAX_SONG_LINES)
    {
        write("\nSong text may contain no more than " + MAX_SONG_LINES + 
              " lines.  Returning to editor....\n");
        clone_object("/obj/edit")->edit(&done_editing(title, author, fname), text);
        return;
    }

    if (line_cnt < 1)
    {
        write("\nSong text must contain at least one proper line. " +
              "Returning to editor....\n");
        clone_object("/obj/edit")->edit(&done_editing(title, author, fname), text);
        return;
    }

    if (lines[sizeof(lines) - 1] == "")
    {
        lines = lines[..-2];
    }

    final_text = implode(lines, "\n") + "\n";

    if (blank_lines_removed)
    {
        string msg = "Removed " + LANG_WNUM(blank_lines_removed) + 
                     " extraneous blank " +
                     ((blank_lines_removed == 1) ? "line" : "lines");
        if (invalid_lines_removed)
        {
            msg += " and " + LANG_WNUM(invalid_lines_removed) + 
                   " otherwise invalid " +
                   ((invalid_lines_removed == 1) ? "line" : "lines");
        }

        write(msg + ".\n");
    }
    else if (invalid_lines_removed)
    {
        write("Removed " + LANG_WNUM(invalid_lines_removed) + " invalid " +
              ((invalid_lines_removed == 1) ? "line" : "lines") + ".\n");
    }

    if (fname)
    {
        SONG_INDEX->replace_text(fname, final_text);
    }
    else
    {
        string song;
        song = SONG_INDEX->create_new_epic(title, author, final_text);
    }

    write(BS("Thanks for submitting an Epic! Welcome to the ranks of "
		 + "named Minstrels...\n"));
}

/*
 ****************************************************************************
 * Name:         do_compose
 * Description:  
 *
 * Arguments:
 * Returns:
 */

int
do_compose(string str)
{
    int scrw;
    string fmt, author, title, fname, default_text;
    mixed songs;
    int i;

    setuid(); seteuid(getuid(TO()));
    if (!strlen(str) ||
        !parse_command(str, ({}), "[my] 'epic' [song] [ballad]"))
    {
	NF("Usage: 'compose epic'. Your name will be appended.\n");
	return 0;
    }

    if (!MEMBER(TP()))
    {
	write("Don't flatter yourself. Only the Minstrels may compose "
	  + "songs here.\n");
	return 1;
    }

    silence(TP());

    author = capitalize(this_player()->query_real_name());
    title = EPIC_TITLE(author);

    songs = SONG_INDEX->find_song(title, "epic");
    if (songs)
    {
        for (i = 0; i < sizeof(songs); i++)
	{
	    if (SONG_INDEX->query_title(songs[i]) == title)
	    {
	        write("You have already composed an epic ballad. Editing " +
                      "your existing song....\n\n");
                default_text = SONG_INDEX->query_text(songs[i]);
		fname = songs[i];
		break;
	    }
	}
    }

    scrw = this_player()->query_option(OPT_SCREEN_WIDTH);
    if (scrw == -1) scrw = 80;
    fmt = "- %-=" + (scrw - 2) + "s\n";
    write("Enter song text. End with '**', list with '~l', abort with '~q'.\n" +
          sprintf(fmt, "Total song length may not exceed " + MAX_SONG_LEN +
                       " characters or " + MAX_SONG_LINES + " lines.") +
          sprintf(fmt, "No single stanza may exceed " + MAX_STANZA_LINES +
                       " lines.") +
          sprintf(fmt, "No line may exceed " + MAX_LINE_LEN + " characters.") +
          sprintf(fmt, "Lines will be automatically indented.") +
          sprintf(fmt, "Separate stanzas with a single blank line.") +
          sprintf(fmt, "Text which isn't to be sung can be commented out by " +
                       "placing a # character at the left margin, before the " +
                       "text.") +
          sprintf(fmt, "Please give credit to the original artist, if any!"));

    clone_object("/obj/edit")->edit(&done_editing(title, author, fname), default_text);

    unsilence(TP());
    
    return 1;
}

public void
reply_erase(string song, int reply)
{
    if (reply == 0)
    {
        write("Ok.\n");
    }
    else if (reply == 1)
    {
        setuid();
        seteuid(getuid());
	SONG_INDEX->remove_epic(song);
        write("Your epic ballad has been removed from the index.\n");
    }
    else
    {
        write("Timeout.  Please try again if you wish to erase your epic ballad.\n");
    }
}

public int
do_erase(string str)
{
    string title;
    mixed songs;
    int i;

    if (!strlen(str))
    {
        notify_fail("Erase what?  Your epic ballad?\n");
        return 0;
    }

    if (!parse_command(str, ({}), "[my] [the] 'epic' [ballad] [song] [from] [the] [index] [book]"))
    {
        notify_fail("Erase what?  Your epic ballad?\n");
        return 0;
    }

    title = EPIC_TITLE(this_player()->query_real_name());

    setuid();
    seteuid(getuid());

    songs = SONG_INDEX->find_song(title, "epic");
    if (songs)
    {
        for (i = 0; i < sizeof(songs); i++)
	{
	    if (SONG_INDEX->query_title(songs[i]) == title)
	    {
   	        write("Are you sure you wish to erase your epic ballad? (Yes/No)\n");
		clone_object(MINSTREL_OBJ + "yes_no")->get_answer(this_player(),
								 &reply_erase(songs[i]),
								 30.0);
		return 1;
	    }
	}
    }

    write("You don't seem to have an epic ballad listed in the index.\n");
    return 1;
}
