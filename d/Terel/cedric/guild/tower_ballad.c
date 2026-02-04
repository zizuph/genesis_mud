/** tower_ballad.c **/

#pragma save_binary

inherit "/std/room.c";
#include <macros.h>
#include <stdproperties.h>
#include <options.h>
#include "/d/Terel/cedric/guild/guild_defs.h"

#define MAX_LINE_LEN     160
#define MAX_SONG_LEN     24000

/*
 **************************************************************************** 
 * The Minstrel Guild Headquarters: Midway up the Tower
 * The Tower is the famous Library of Songs; on the second level are the
 * great Ballads
 * 
 * Cedric 1/93
 */

/*
 * About Songs:  The Songs accessible in this room are Ballads. A Ballad
 *               sung by a Minstrel shall be heard by all other Minstrels 
 *               in the game.  Since ballads also write themselves 
 *               automatically into the songbooks of every Minstrel, they 
 *               serve as a sort of guild-line, accessible to the entire
 *               guild. Ballads written by players are placed in 
 *               ~cedric/guild/Submit until the Guildmaster or his appointee
 *               has a chance to review them. If accepted as Ballads, they 
 *               are placed in ~cedric/guild/Ballads and have the suffix 
 *               .song.  The first line of each song contains the 
 *               title and the author separated by '**'.  Stanzas are 
 *               separated by a blank line.  Text which is meant to comment
 *               a song but is not meant to be sung is noted with a '#'.  
 *               The last line of each song contains only the string '**'.
 *               Example:  Row, Row, Row Your Boat**Cedric
 *                         # A catchy little tune I like.     
 *                              <text of verse 1>
 *                              <text of verse 1>
 *              
 *                              <text of verse 2>
 *                              <text of verse 2>
 *
 *                         **                         
 */

void
init()
{
    ::init();
    add_action("do_compose", "compose");
    add_action("do_read", "read");
    add_action("do_read", "mread");
    add_action("do_copy", "copy");
    add_action("do_say", "say");
    add_action("do_say", "shout");
    add_action("do_say", "'", 1);
    add_action("do_say", "sing");
    add_action("do_say", "play");
    add_action("do_say", "perform");

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
ballad_list()
{
    int scrw = this_player()->query_option(OPT_SCREEN_WIDTH);
    string str;
    string file = SONG_ROOT + "ballad.titles";

    setuid();
    seteuid(getuid());

    if ((file_size(file) <= 0) ||
        !strlen(str = read_file(file)))
    {
        return "\tNo ballads\n";
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
    if (str == "index" || str=="book" || str == "ballads")
    {
        say (QCTNAME(TP()) + " studies the index.\n");

	this_player()->more(ballad_list());
	return 1;
    }

    if (this_player()->query_skill(SG_READ_MUSIC)<11)
    {
	notify_fail("You have not advanced far enough in the skill of reading "
	+ "music to read the ballads. Why not visit the Training "
	+ "Room?\n");
	return 0;
    }

    setuid();
    seteuid(getuid());

    songs = SONG_INDEX->parse_song("ballad " + str);

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

    this_player()->more("You read \"" + SONG_INDEX->query_title(songs[0]) +
          "\", written by " + SONG_INDEX->query_author(songs[0]) + ".\n\n" +
          SONG_INDEX->query_text(songs[0]));
    return 1;
}

int
do_copy(string str)
{
    notify_fail("You needn't copy the Ballads into your song book..they are "
    + "already there!\n");
    return 0;
}

void
create_room()
{
    seteuid(getuid(TO()));
    
    set_short("The Minstrels Tower");
    set_long("You stand on the second level of the Minstrel's Tower. " 
    + "Within the Tower is located the famous Library of Songs. Here, "
    + "halfway up the Tower, are catalogued the Ballads. These are songs "
    + "of such musical potency that when one Minstrel performs a Ballad "
    + "all the guild shall hear it. In addition, the Ballads automagically "
    + "write themselves into each Minstrel's song book, so there is no need "
    + "to copy these.  The Minstrels are known to use the Ballads as a form "
    + "of communication over great distances. Due to the great power of "
    + "these songs, each Ballad a Minstrel composes must be approved by "
    + "the Guildmaster or his Assistant. When you compose a song here, it "
    + "shall be submitted to the master; if approved, the song shall be "
    + "added to the Library. As with all levels of the Tower, a magical "
    + "silence shall descend when a Minstrel begins composing, that none "
    + "may disturb the creative process.\nA small alcove is set aside "
    + "in the eastern portion of the room.\nA handsome index to the "
    + "Ballads.\n");
    
    add_item(({"index", "book", "handsome index"}), "This leather-bound tome "
	     + "lists every Ballad ever written by a Minstrel. Feel free to "
	     + "<read> any song you please.\n");
    
    add_exit(GUILD+"tower_power", "up");
    add_exit(GUILD+"tower_mundane", "down");
    add_exit(GUILD+"tower_epic", "east");
    add_prop(ROOM_I_INSIDE, 1);
}

void
silence(object composer)
{
    say("Your skin tingles a though a spell were being cast, yet you hear "
	+ "no magic words. In fact you hear nothing at all..", composer);
}

void
unsilence(object composer)
{
}

public void
done_commenting(string title, string fname, string text, string comments)
{
    if (fname)
    {
        SONG_INDEX->submit_ballad_edits(fname, text, comments);
        write("Thank you for updating the ballad. The Cycle will review " +
              "your edits and accept them or reject them.\n");
    }
    else
    {
        string song;
        song = SONG_INDEX->create_new_ballad(title,
                                             capitalize(this_player()->query_real_name()),
                                             text, comments);
        write("Thanks for your submission! The Cycle will review " +
	      "your song and decide whether it is worthy to be " +
	      "deemed a Ballad.\n");

    }
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
done_editing(string title, string fname, string text)
{
    string *lines, *regex_arr;
    string final_text;
    int previous_line_blank, blank_lines_removed, i, line_cnt;

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
        clone_object("/obj/edit")->edit(&done_editing(title, fname), text);
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

            if (strlen(lines[i]) > MAX_LINE_LEN)
            {
                write("\nLine " + (i + 1) + " exceeds maximum size (" +
                      MAX_LINE_LEN + " characters).  Returning to " +
                      "editor....\n");
                clone_object("/obj/edit")->edit(&done_editing(title, fname),
                                                text);
                return;
            }
	    
            previous_line_blank = 0;
            lines[i] = "\t" + lines[i];
            line_cnt++;
	    continue;
        }
    }

    // Reusing the lines array, as we have, and doing an implode at the
    // end should be more efficient than concatenating each line normally
    // (with the + operator)
    lines -= ({ 0 });

    if (line_cnt < 1)
    {
        write("\nSong text must contain at least one proper line. " +
              "Returning to editor....\n");
        clone_object("/obj/edit")->edit(&done_editing(title, fname), text);
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
        write(msg + ".\n");
    }

    write("\nPlease add any comments or messages you wish to send to the " +
          "Cycle. If you editing an existing ballad, note what changes " +
          "you have made and why.\nEnd with '**', list with '~l', abort " +
          "with '~q'.\n");
    clone_object("/obj/edit")->edit(&done_commenting(title, fname, final_text));
}

public varargs void
compose3(string title, string fname = 0)
{
    string default_text = 0, fmt;
    int scrw;

    setuid();
    seteuid(getuid());

    if (strlen(fname))
    {
        string author = lower_case(SONG_INDEX->query_author(fname));
        if (author != this_player()->query_real_name())
        {
            write("You are not the author of that song; you may not edit " +
                  "it.\n");
            return;
        }

        default_text = SONG_INDEX->query_text(fname);
        if (strlen(default_text))
        {
            string *lines;
            int i;

            lines = explode(default_text, "\n");
            for (i = 0; i < sizeof(lines); i++)
            {
                if (strlen(lines[i]) && (lines[i][0] == '\t'))
                {
                    lines[i] = lines[i][1..];
                }
            }

            default_text = implode(lines, "\n");
        }
    }

    scrw = this_player()->query_option(OPT_SCREEN_WIDTH);
    fmt = "- %-=" + (scrw - 2) + "s\n";
    write("Enter song text. End with '**', list with '~l', abort with '~q'.\n" +
          sprintf(fmt, "Lines will be automatically indented.") +
          sprintf(fmt, "Separate stanzas with a single blank line.") +
          sprintf(fmt, "Text which isn't to be sung can be commented out by " +
                       "placing a # character at the left margin, before the " +
                       "text.") +
          sprintf(fmt, "Please give credit to the original artist, if any!") +
          "\nIMPORTANT! Once submitted, a ballad will be reviewed by the " +
          "Minstrel Cycle before being accepted. The song may not be edited " +
          "while it is in this review period; it may only be edited once it " +
          "has been accepted. Edited songs must again be reviewed by the " +
          "Cycle.\n");

    clone_object("/obj/edit")->edit(&done_editing(title, fname), default_text);

}

public void
edit2(string name, string *existing_songs, string input)
{
    int selection;

    if (input == "~q")
    {
        write("Aborting song composition.\n");
        return;
    }

    if (!strlen(input) || !sscanf(input, "%d", selection))
    {
        write("Enter a song number. (~q to quit)\n: ");
        input_to(&edit2(name, existing_songs));
        return;
    }

    if ((selection < 1) || (selection > sizeof(existing_songs)))
    {
        write("Please enter a song number in the range 1 to " +
              sizeof(existing_songs) + ". (~q to quit)\n: ");
        input_to(&edit2(name, existing_songs));
        return;
    }

    compose3(name, existing_songs[selection - 1]);
}

public void
edit1(string name, string *existing_songs, string input)
{
    if (input == "~q")
    {
        write("Aborting song composition.\n");
        return;
    }

    if ((input == "c") || (input == "create"))
    {
        compose3(name);
        return;
    }
    else if ((input == "e") || (input == "edit"))
    {
        if (sizeof(existing_songs) > 1)
        {
            int i;
            string fmt = "\t%" + strlen(sizeof(existing_songs) + "") +
                         "d. %s by %s\n";
            write("There is more than one existing song with that title. " +
                  "Select which one you would like to edit:\n");

            setuid();
            seteuid(getuid());

            for (i = 0; i < sizeof(existing_songs); i++)
            {
                write(sprintf(fmt, i + 1,
                                   SONG_INDEX->query_title(existing_songs[i]),
                                   SONG_INDEX->query_author(existing_songs[i])));
            }

            write("\nEnter a song number. (~q to quit)\n: ");
            input_to(&edit2(name, existing_songs));
            return;
        }
        else
        {
            compose3(name, existing_songs[0]);
            return;
        }
    }
    else
    {
        write("You can choose to \"edit\" an existing file, \"create\" a new " +
              "one, or \"~q\" to quit.\n: ");
        input_to(&edit1(name, existing_songs));
    }
}

public void
compose2(string input)
{
    string fname, index = SONG_INDEX, lctitle;
    string *existing_songs, *ballads_heard;
    int i;

    if (!strlen(input) || (input == "~q"))
    {
        write("Aborting song composition.\n");
        return;
    }

    if (strlen(input) > 50)
    {
        write("Song titles may not exceed 50 characters.  Enter a shorter " +
              "title. (~q to quit)\n: ");
        input_to(compose2);
        return;
    }

    setuid();
    seteuid(getuid());

    fname = index->title_to_filename(input);

    lctitle = implode(map(explode(input, ""), lower_case), "");

    existing_songs = SONG_INDEX->find_song(input, "ballad");
    if (existing_songs)
    {
        existing_songs = filter(existing_songs,
                                &operator(==)(lctitle) @ &index->query_lc_title());
    }

    if (existing_songs && (sizeof(existing_songs) > 0))
    {
        int songnum = sizeof(existing_songs);
        write(((songnum == 1) ? "There is already a ballad" :
              "There are already " + LANG_WNUM(songnum) + " ballads") +
              " with that title.  Do you wish to [e]dit " +
              ((songnum == 1) ? "it" : "one") + " or [c]reate a new one? " +
              "(~q to quit)\n: ");
        input_to(&edit1(input, existing_songs));
        return;
    }

    compose3(input);
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
    if (!strlen(str) ||
        !parse_command(str, ({}), "[a] 'song' / 'ballad' [song]"))
    {
	notify_fail("Usage: 'compose ballad'.\n");
	return 0;
    }

    if (!MEMBER(this_player()))
    {
	write("Don't flatter yourself. Only the Minstrels may compose "
	  + "songs here.\n");
	return 1;
    }

    write("What is the title of your song? Titles cannot exceed 50 " +
          "characters.  Remember to use proper capitalization for song " +
          "titles.\n");

    write("Enter a song title (~q to quit)\n: ");

    input_to(compose2);

    return 1;
}
