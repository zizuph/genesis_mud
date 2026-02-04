#pragma save_binary

inherit "/std/object.c";
#include <macros.h>
#include <options.h>
#include <language.h>

#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <cmdparse.h>
#include "../guild_defs.h"
#include "/d/Terel/cedric/guild/guild_funs.c"

#define MAX_STANZA_LINES 25
#define MAX_LINE_LEN     160
#define MAX_SONG_LEN     15000
#define MAX_SONG_LINES   250
#define MIN_SONG_LINES   3

#define MINSTREL_AS_MUNDANES_HEARD "_minstrel_as_mundane_songs_heard"

/*
 * The Minstrel's SongBook
 * Here the minstrel scribes the songs he or she wishes to carry though life.
 * This object contains pointers to each song the minstrel knows. There are
 * three types of songs - Mundane Songs, Ballads, and Songs of Power. Mundane
 * Songs are simply emotes, with no other effects. Ballads are more regulated
 * songs (each must be approved by the Cycle) with such musical potency
 * that a minstrel singing a Ballad is heard by all others in the game. They
 * are intended for use as a sort of guild-line. Songs of Power are basically
 * spells. The filenames stored in the Song Book are accessed by the Minstrel
 * soul commands 'sing', 'play', and 'perform'.
 */

object owner;

object
query_owner()
{
    return owner;
}

void 
set_owner(object ob)
{
    owner = ob;

    // Remove this when all members are updated
    setuid();
    seteuid(getuid());
    if (!SONGBOOK_MANAGER->load_songbook(owner->query_real_name()))
    {
        SONGBOOK_MANAGER->add_songbook(owner);
    }
}

void
create_object()
{
    set_name("songbook");
    add_name("minstrel_song_book");
    add_name("cedric_song_book");
    add_adj("song");
    set_short("Minstrel's songbook");
    set_long(BS("This small book is along with your instrument the badge "
    + "of your membership in the August Order of Minstrels. The songs of "
    + "the Minstrels are their lifeblood, and those shall you "
    + "store in this book. Every Ballad available to the Minstrels shall "
    + "be written by its own magic into this book. But choose carefully "
    + "the Mundane Songs and Songs of Power you copy into these pages, "
    + "for the number of each that may be written within is limited. As "
    + "your days in the guild increase, so shall the pages in your song "
    + "book.\n")
    + "\nYou may always type <help minstrels> for more information.\n");
    add_prop(OBJ_M_NO_DROP, BS("You needn't drop the song book of the "
    + "Minstrels.\n"));
}

public void
remove_mundane(string str)
{
    setuid();
    seteuid(getuid());

    SONGBOOK_MANAGER->remove_mundane_songs(owner, str);
}

public int
query_mundane_max()
{
    int skmax = owner->query_stat(SS_LAYMAN) / 5 + 4;
    return ((owner->query_special_title() == 0) ? skmax : max(150, skmax));
}

/*
 * Function:    int add_mundane(string str)
 * Description: Tries to add a song filename to mundane_songs. The max
 *              number of Mundanes is (guild_stat/2) + 4.
 * Arguments:   str - the filename of the song, minus the path.
 * Returns:     0 if successful, 1 if unsuccessful.
 */
int
add_mundane(string str)
{
    string *mundanes;
    int max;

    setuid();
    seteuid(getuid());

    mundanes  = SONGBOOK_MANAGER->query_mundane_songs(owner);
    max = query_mundane_max();
    if ((max != -1) && (sizeof(mundanes) >= max))
    {
        return 0;
    }

    return SONGBOOK_MANAGER->add_mundane_songs(owner, str);
}

public void
remove_power(string str)
{
    setuid();
    seteuid(getuid());

    SONGBOOK_MANAGER->remove_power_songs(owner, str);
}

public int
query_power_max()
{
    return ((owner->query_special_title() == 0) ?
            (owner->query_stat(SS_LAYMAN) / 20 + 1) : -1);
}

/*
 * Function:    int add_power(string str)
 * Description: Tries to add a song filename to power_songs. The max          
 *              number of  Songs of Power is (guild_stat/20) + 1.
 * Arguments:   str - the filename of the song, minus the path.
 * Returns:     0 if successful, 1 if unsuccessful.
 * Note:        It is the responsibility of the calling object to insure
 *              that other requirements (such as guild membership, read
 *              music skill ability, and so on) are satified! This 
 *              function only checks the number of allowed songs.
 */            
int            
add_power(string str)            
{            
    string *powers;
    int max;

    setuid();
    seteuid(getuid());

    powers = SONGBOOK_MANAGER->query_power_songs(owner) || ({});
    max = query_power_max();

    if ((max != -1) && (sizeof(powers) >= max))
    {
        return 0;
    }

    return SONGBOOK_MANAGER->add_power_songs(owner, str);
}
         

/*
 * Return a formatted, tabulated list of the songs whose filenames
 * are listed in mundane_songs.
 */
string
list_mundane()
{
#ifdef ALL_MUNDANES_AVAILABLE
    int scrw = this_player()->query_option(OPT_SCREEN_WIDTH);
    string str;
    string file = SONG_ROOT + "mundane.titles";

    if (scrw == -1)
    {
        scrw = 200;
    }

    setuid();
    seteuid(getuid());

    if ((file_size(file) <= 0) ||
        !strlen(str = read_file(file)))
    {
        return "\tNo mundane songs\n";
    }

    return sprintf("%-#*s\n", scrw, str);
#else
    string *mundane;
    int scrw = this_player()->query_option(OPT_SCREEN_WIDTH);
    int i;
    string fmt, str, title;

    if (scrw == -1)
    {
        scrw = 200;
    }
    
    setuid();
    seteuid(getuid());

    mundane = SONGBOOK_MANAGER->query_mundane_songs(this_player());

    str = "";
    fmt = "%" + strlen(sizeof(mundane) + "") + "d. %s\n";
    for (i = 0; i < sizeof(mundane); i++)
    {
        title = SONG_INDEX->query_title(MUNDANE_SONGS_DIR + mundane[i]);
        if (title == 0)
        {
            title = "UNKNOWN";
        }

        str += sprintf(fmt, i + 1, title);
    }

    return sprintf("%-#*s\n", scrw, str);
#endif
}

/*
 * Return a formatted, tabulated list of the songs whose filenames
 * are listed in ballad_songs, and that end with ".song".
 */
string
list_ballad()
{
    int scrw = this_player()->query_option(OPT_SCREEN_WIDTH);
    string str;
    string file = SONG_ROOT + "ballad.titles";

    if (scrw == -1)
    {
        scrw = 200;
    }

    setuid();
    seteuid(getuid());

    if ((file_size(file) <= 0) ||
        !strlen(str = read_file(file)))
    {
        return "\tNo ballads\n";
    }

    return sprintf("%-#*s\n", scrw, str);
}

/*
 * list_epic():
 * Return a formatted, tabulated list of the songs whose filenames
 * are listed in ballad_songs, and that end with ".epic".
 */
string
list_epic()
{
    int scrw = this_player()->query_option(OPT_SCREEN_WIDTH);
    string str;
    string file = SONG_ROOT + "epic.titles";

    if (scrw == -1)
    {
        scrw = 200;
    }

    setuid();
    seteuid(getuid());

    if ((file_size(file) <= 0) ||
        !strlen(str = read_file(file)))
    {
        return "\tNo epic ballads\n";
    }

    return sprintf("%-#*s\n", scrw, str);
}

/*
 * Return a formatted, tabulated list of the songs whose filenames
 * are listed in power_songs. Note that the title of a Song of Power
 * is the same as it's filename...this implies that Songs of Power
 * all have 1-word titles..Blast, Soothe, Shield, Vibrato, etc.
 * Note also that the first line of a Power looks like:
 * /**Blast**Cedric
 */
string
list_power()
{
    string *power;
    int scrw = this_player()->query_option(OPT_SCREEN_WIDTH);
    int i;
    string fmt, str, title;

    if (scrw == -1)
    {
        scrw = 200;
    }
    
    setuid();
    seteuid(getuid());

    power = SONGBOOK_MANAGER->query_power_songs(this_player());

    str = "";
    fmt = "%" + strlen(sizeof(power) + "") + "d. %s\n";
    for (i = 0; i < sizeof(power); i++)
    {
        title = (POWER_SONGS_DIR + power[i])->query_name();
        if (title == 0)
        {
            title = "UNKNOWN";
        }

        str += sprintf(fmt, i + 1, title);
    }

    return sprintf("%-#*s\n", scrw, str);
}

public void
reply_erase(string song, int reply)
{
    if (reply == 1)
    {
        if (IS_POWER(song))
        {
            remove_power(song[strlen(POWER_SONGS_DIR)..-3]);
        }
        else if (IS_MUNDANE(song))
        {
            remove_mundane(song[strlen(MUNDANE_SONGS_DIR)..]);
        }
        else
        {
        }

        write("Ok.\n");
    }
    else if (reply == -1)
    {
        write("Timeout.\n");
    }
    else if (reply == 0)
    {
        write("Ok.\n");
    }
}

int
do_erase(string str)
{
    mixed songs;
    string type;
    string title;
    object yn;

    if (!strlen(str))
    {
        return 0;
    }

    setuid();
    seteuid(getuid());

    songs = SONG_INDEX->parse_song(str);

    if (stringp(songs))
    {
        notify_fail(songs + "\n");
        return 0;
    }

    if (pointerp(songs))
    {
        if (sizeof(songs) > 1)
        {
            write("There are multiple matching songs.  Please be more specific.\n");
            return 1;
        }

        songs = songs[0];
    }

    if (!stringp(songs))
    {
        notify_fail("You know no such song.\n");
        return 0;
    }

    if (IS_BALLAD(songs))
    {
        write("You can't erase a Ballad! They are written by their own "
            + "potent magic into each Minstrel's songbook. Nor need you erase a "
            + "Ballad, for they do not affect the number of pages remaining in your "
            + "songbook.\n");
        return 1;
    }

    if (IS_EPIC(songs))
    {
        write("You can't erase an Epic! They are Ballads, each written "
            + "by its own "
            + "potent magic into every Minstrel's songbook.\n");
        return 1;
    }

    if (IS_POWER(songs))
    {
        remove_power(songs);
        type = "song of power";
    }
    else if (IS_MUNDANE(songs))
    {
        remove_mundane(songs);
        type = "mundane song";
    }
    else
    {
        write("Unable to erase song: unknown type.\n");
        return 1;
    }

    title = SONG_INDEX->query_title(songs);
    if (title)
    {
        write("You are about to erase the " + type + ", \"" + title +
              "\".  Are you sure? (Yes/No) ");
    }
    else
    {
        write("You are about to erase a " + type +
              ".  Are you sure? (Yes/No)\n");
    }

    yn = clone_object(GUILD + "obj/yes_no");
    yn->get_answer(this_player(), &reply_erase(songs), 20.0);
    return 1;

#if 0
    string type, which, is_song, songfile;
    int songnum;
    
    if (!str) return 0;
    if (sscanf(str, "%d", songnum))
    {
        if (is_song = parse_song("mundane", str, mundane_songs, ({}), ({}), ({})))
        {
            songfile=explode(is_song, "/")[sizeof(explode(is_song, "/"))-1];
            mundane_songs -= ({songfile});
            TP()->CM("You erase "+CAP_TITLE(is_song)+"from your songbook.\n");
            return 1;
        }
    }
    if (sscanf(str,"%s %s",type,which))
    {
        is_song = parse_song(type,which,mundane_songs,ballad_songs,query_epic(),power_songs);
        if (type == "power")
        {
            songfile=explode(is_song, "/")[sizeof(explode(is_song, "/"))-1];
            power_songs -= ({songfile});
            TP()->CM("You erase "+CAP_TITLE(is_song)+"from your songbook.\n");
            return 1;
        }
        if (type == "ballad")
        {
        }
        if (type == "epic")
        {
            TP()->CM("You can't erase an Epic! They are Ballads, each written "
            + "by its own "
            + "potent magic into every Minstrel's songbook.\n");
            return 1;
        }
        if (type == "mundane")
        {
            songfile=explode(is_song, "/")[sizeof(explode(is_song, "/"))-1];
            mundane_songs -= ({songfile});
            TP()->CM("You erase "+CAP_TITLE(is_song)+"from your songbook.\n");
            return 1;
        }
    }
    if (is_song=parse_song("mundane",str,mundane_songs, ({}), ({}), ({})))
    {
        songfile=explode(is_song, "/")[sizeof(explode(is_song, "/"))-1];
        mundane_songs -= ({songfile});
        TP()->CM("You erase "+CAP_TITLE(is_song)+"from your songbook.\n");
        return 1;
    }
    if (is_song=parse_song("ballad",str,({}), ballad_songs, ({}), ({})))
    {
        TP()->CM("You can't erase a Ballad! They are written by their own "
        + "potent magic into each Minstrel's songbook. Nor need you erase a "
        + "Ballad, for they do not affect the number of pages remaining in your "
        + "songbook.\n");
        return 1;
    }
    if (is_song=parse_song("epic",str,({}), ({}), query_epic(), ({})))
    {
            TP()->CM("You can't erase an Epic! They are Ballads, each written "
            + "by its own "
            + "potent magic into every Minstrel's songbook.\n");
            return 1;
        }
    if (is_song=parse_song("power", str, ({}), ({}), ({}), power_songs))
    {
        songfile=explode(is_song, "/")[sizeof(explode(is_song, "/"))-1];
        power_songs -= ({songfile});
        TP()->CM("You erase "+CAP_TITLE(is_song)+"from your songbook.\n");
        return 1;
    }
    notify_fail(BS("Erase which song? The correct syntax is:\n")
    + "        erase <type> <song>\n"
    + "where <type> is mundane, ballad, or power,  and <song> is the number, title\n"
    + "(in lowercase), or first word of the title of the song you wish to erase.\n");  
    return 0;
#endif
}

// Called by /cmd/live/items.c when the standard read command is used
public mixed
command_read(int use_more)
{
    string text;
    
    say(QCTNAME(this_player())+" studies " + this_player()->query_possessive()
        + " song book.\n");
    text = "This songbook, which belongs to " + query_owner()->query_name() +
           " dedicated to the Muse " + query_owner()->query_muse_name() +
           ".\nIt contains the following:\n<<Mundane Songs>>\n" +
           list_mundane() + "\n<<Ballads>>\n" + list_ballad() +
           "\n<<Songs of Power>>\n" + list_power() +
           "\nAlso listed are the great Epics; in them the " +
           "story of each Minstrel's life is immortalized in song.\n";
    if (use_more || (strlen(text) > 2500))
    {
        this_player()->more(text);
    }
    else
    {
        write(text);
    }

    return 1;

}

int
do_read(string str)
{
    object ob1;
    mixed song;
    
    if (!strlen(str)) 
        return 0;
    if (str == "epics" || str == "Epics")
    {
        string list = list_epic();
        say(QCTNAME(TP())+" studies "+TP()->query_possessive()
        + " song book.\n");
        if (query_verb() == "mread" || (strlen(list) > 2500))
        {
            this_player()->more("The songbook contains the following "
                                         + "Epics:\n" + list);
        }
        else
        {
            write("The songbook contains the following "
                  + "Epics:\n" + list);
        }
        return 1;
    }
    if (str == "ballads" || str == "Ballads")
    {
        string list = list_ballad();
        say(QCTNAME(TP())+" studies "+TP()->query_possessive()
        + " song book.\n");
        if (query_verb() == "mread" || (strlen(list) > 2500))
        {
            this_player()->more("The songbook contains the following "
                                         + "Ballads:\n" + list);
        }
        else
        {
            write("The songbook contains the following "
                  + "Ballads:\n" + list);
        }
        return 1;
    }
    if (str == "mundanes" || str == "Mundanes")
    {
        string list = list_mundane();
        say(QCTNAME(TP())+" studies "+TP()->query_possessive()
        + " song book.\n");
        if (query_verb() == "mread" || (strlen(list) > 2500))
        {
            this_player()->more("The songbook contains the " +
                                "following Mundane Songs:\n" + list);
        }
        else
        {
            write("The songbook contains the following Mundane Songs:\n"
                  + list);
        }
        return 1;
    }
    if (str == "Songs of Power" || str == "songs of power" || str == "powers")
    {
        say(QCTNAME(TP())+" studies "+TP()->query_possessive()
        + " song book.\n");
        write("The songbook contains the following Songs of Power:\n"
        + list_power()+"\n");
        return 1;
    }

    setuid();
    seteuid(getuid());

    song = SONG_INDEX->parse_song(str);

    if (stringp(song))
    {
        notify_fail(song + "\n");
        return 0;
    }

    if (pointerp(song))
    {
        if (sizeof(song) > 1)
        {
            write("There are multiple matching songs.  Please specify more of " +
                  "the title or use the song number.\n");
            return 1;
        }

        song = song[0];
    }

    if (!stringp(song) || !strlen(song))
    {
        notify_fail("You know of no such song.\n");
        return 0;
    }

    if (wildmatch(POWER_SONGS_DIR + "*", song))
    {
        write(song->query_purpose());
        return 1;
    }

    this_player()->more("You read \"" + SONG_INDEX->query_title(song) +
          "\", written by " + SONG_INDEX->query_author(song) + ".\n\n" +
	  SONG_INDEX->query_text(song));
    return 1;

#if 0
    notify_fail(BS("Read what? The songbook, maybe? The Epics? Or did you mean to "
    + "read a certain song? In that case, the correct syntax would be:\n")
    + "        read <type> <song>\n"
    + "where <type> is mundane, ballad, or power,  and <song> is the number, title\n"
    + "(in lowercase), or first word of the title of the song you wish to read.\n");
#endif
}

public void
done_editing(string name, string fname, string text)
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
        clone_object("/obj/edit")->edit(&done_editing(name, fname), text);
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
                    clone_object("/obj/edit")->edit(&done_editing(name, fname),
                                                    text);
                    return;
                }

                if (strlen(lines[i]) > MAX_LINE_LEN)
                {
                    write("\nLine " + (i + 1) + " exceeds maximum size (" +
                          MAX_LINE_LEN + " characters).  Returning to " +
                          "editor....\n");
                    clone_object("/obj/edit")->edit(&done_editing(name, fname),
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
        clone_object("/obj/edit")->edit(&done_editing(name, fname), text);
        return;
    }

    if (line_cnt < 1)
    {
        write("\nSong text must contain at least one proper line. " +
              "Returning to editor....\n");
        clone_object("/obj/edit")->edit(&done_editing(name, fname), text);
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
        song = SONG_INDEX->create_new_mundane(name,
                                              capitalize(this_player()->query_real_name()),
                                              final_text);
        add_mundane(song[strlen(MUNDANE_SONGS_DIR)..]);
    }

    write("Ok.\n");
}

public varargs void
compose4(string title, string fname = 0)
{
    string default_text = 0, fmt;
    int mmax = query_mundane_max(), scrw;
    string *mundanes;

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

        default_text = read_file(fname, 2);
        if (strlen(default_text))
        {
            string *lines;
            int i;

            default_text = extract(default_text, 0, -3);
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
    else 
    {
        if ((mmax != -1) &&
            (mundanes = SONGBOOK_MANAGER->query_mundane_songs(this_player())) &&
            (sizeof(mundanes) >= mmax))
        {
            write("You have no room in your songbook to compose a new song. " +
                  "You will have to erase another mundane song first.\n");
            return;
        }
    }

    scrw = this_player()->query_option(OPT_SCREEN_WIDTH);

    if (scrw == -1)
    {
        scrw = 200;
    }

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

    compose4(name, existing_songs[selection - 1]);
}

public void compose3(string title)
{
    int mmax = query_mundane_max();
    string *mundanes_heard, *mundanes_known;
    mixed song;

    if ((mmax != -1) &&
        (mundanes_known = SONGBOOK_MANAGER->query_mundane_songs(this_player())) &&
        (sizeof(mundanes_known) >= mmax))
    {
        write("You have no room in your songbook to compose a new song. " +
              "You will have to erase another mundane song first.\n");
        return;
    }

    mundanes_heard = this_player()->query_prop(MINSTREL_AS_MUNDANES_HEARD);
    
    if (pointerp(mundanes_heard))
    {
        mixed song;
        string fname = SONG_INDEX->title_to_filename(title);
        if (pointerp(mundanes_known))
        {
            mundanes_heard -= mundanes_known;
        }
    
        song = regexp(mundanes_heard,
                      "^" + fname + "(_[0-9][0-9]*)*(\\.[^\\.]*)*$");
        if (pointerp(song))
        {
            int i;
            string lctitle = implode(map(explode(title, ""), lower_case), "");

            for (i = 0; i < sizeof(song); i++)
            {
                if (SONG_INDEX->query_lc_title(MUNDANE_SONGS_DIR + song[i]) == lctitle)
                {
                    mundanes_heard -= ({ song[i] });
                    this_player()->add_prop(MINSTREL_AS_MUNDANES_HEARD,
                                            mundanes_heard);
                    add_mundane(song[i]);

                    write("From memory, you scribe the song into your " +
                          "songbook.\n");
                    return;
                }
            }
        }
    }

    compose4(title);
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
            compose4(name, existing_songs[0]);
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
    string *existing_songs, *mundanes_heard;
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

    existing_songs = SONGBOOK_MANAGER->query_mundane_songs(this_player()) || ({});
    // Would prefer + in some places, but it doesn't seem to work.
    // <pattern><pattern>* will have to suffice
    existing_songs = map(regexp(existing_songs,
                                "^" + fname + "(_[0-9][0-9]*)*(\\.[^\\.]*)*$"),
                         &operator(+)(MUNDANE_SONGS_DIR));
    existing_songs = filter(existing_songs,
                            &operator(==)(lctitle) @ &index->query_lc_title());

    if (sizeof(existing_songs))
    {
        int songnum = sizeof(existing_songs);
        write("You already know " +
              ((songnum == 1) ? "a song" : (LANG_WNUM(songnum) + " songs")) +
              " with that title.  Do you wish to [e]dit " +
              ((songnum == 1) ? "it" : "one") + " or [c]reate a new one? " +
              "(~q to quit)\n: ");
        input_to(&edit1(input, existing_songs));
        return;
    }

    compose3(input);
}

int
do_compose(string str)
{
    string *mundanes_heard, *mundanes_known;
    if (!strlen(str) || (str != "mundane song"))
    {
        notify_fail("What do you wish to compose?  A mundane song?\n");
        return 0;
    }


    write("What is the title of your song? Titles cannot exceed 50 " +
          "characters.  Remember to use proper capitalization for song " +
          "titles.\n");

    mundanes_heard = this_player()->query_prop(MINSTREL_AS_MUNDANES_HEARD);
    if (pointerp(mundanes_heard))
    {
        mundanes_known = SONGBOOK_MANAGER->query_mundane_songs(this_player());
        if (pointerp(mundanes_known))
        {
            mundanes_heard -= mundanes_known;
        }

        if (sizeof(mundanes_heard) > 0)
        {
            int i;
            string fmt = "%" + strlen(sizeof(mundanes_heard) + "") +
                         "d. %s by %s\n";
            string txt = "\nYou can scribe the following " +
                         ((sizeof(mundanes_heard) > 1) ? "songs" : "song") +
                         " from memory:\n";
            for (i = 0; i < sizeof(mundanes_heard); i++)
            {
                txt += sprintf(fmt,
                               i + 1,
                               SONG_INDEX->query_title(MUNDANE_SONGS_DIR +
                                                       mundanes_heard[i]),
                               SONG_INDEX->query_author(MUNDANE_SONGS_DIR +
                                                        mundanes_heard[i]));
            }

            write(txt + "\n");
        }
    }

    write("Enter a song title (~q to quit)\n: ");

    input_to(compose2);
    return 1;
}

int
do_memorise(string str)
{
    string *mundanes_heard, *mundanes_known;

    mundanes_heard = this_player()->query_prop(MINSTREL_AS_MUNDANES_HEARD);
    mundanes_known = SONGBOOK_MANAGER->query_mundane_songs(this_player());

    if (!pointerp(mundanes_heard))
    {
        notify_fail("You have not been taught any mundane songs " +
            "to memorise.\n");
        return 0;
    }

    mundanes_heard -= mundanes_known;

    if (!sizeof(mundanes_heard))
    {
        notify_fail("You have not been taught any new mundane songs " +
            "to memorise.\n");
        return 0;
    }

    if (!strlen(str))
    {
        int i;
        string fmt = "%" + strlen(sizeof(mundanes_heard) + "") +
            "d. %s by %s\n";
        string txt = "\nYou can memorise the following " +
            ((sizeof(mundanes_heard) > 1) ? "songs" : "song") +
            " from memory:\n";
        for (i = 0; i < sizeof(mundanes_heard); i++)
        {
            txt += sprintf(fmt, i + 1,
                SONG_INDEX->query_title(MUNDANE_SONGS_DIR + mundanes_heard[i]),
                SONG_INDEX->query_author(MUNDANE_SONGS_DIR + mundanes_heard[i]));
        }

            write(txt + "\n");

        notify_fail("Which one of these songs you have been taught do you " +
            "wish to memorise?\n");
        return 0;
    }

    string mem_song;
    int i;

    for (i = 0; i < sizeof(mundanes_heard); i++)
    {
        if(lower_case(SONG_INDEX->query_title(MUNDANE_SONGS_DIR + 
            mundanes_heard[i])) == lower_case(str))
        mem_song = lower_case(str);
    }

    if(!strlen(mem_song))
    {
        notify_fail("You haven't been taught a mundane song " +
            "called " +str+ "?\n");
        return 0;
    }

    // write("Enter the song title you wish to memorise (~q to quit)\n: ");

    compose2(mem_song);
    return 1;
}

public void
reply_teach(object me, string myname, string song, int reply)
{
    int is_here = (me && present(me, environment(this_player()))) != 0;

    if (reply == 1)
    {
        if (!is_here)
        {
            write(capitalize(myname) + " is no longer here to teach you a " +
                  "song.\n");
        }
        else
        {
            string song_short;
            string *songs_heard, *songs_known;

            write("You accept, and " + myname + " shares " +
                me->query_possessive() + " song with you. " +
                "You can now 'memorise' it and add to your " +
                "songbook.\n");
            me->catch_tell(this_player()->query_The_name(me) +
                " accepts your offer, and you share your song " +
                "with " + this_player()->query_objective() + ".\n");

            song_short = song[strlen(MUNDANE_SONGS_DIR)..];
            songs_heard =
                this_player()->query_prop(MINSTREL_AS_MUNDANES_HEARD) || ({});
            songs_known =
                SONG_INDEX->query_mundanes_known(this_player()) || ({});
            if ((member_array(song, songs_heard) == -1) &&
                (member_array(song, songs_known) == -1))
            {
                songs_heard -= songs_known;
                this_player()->add_prop(MINSTREL_AS_MUNDANES_HEARD,
                                        ({ song_short }) + songs_heard[..98]);
            }
        }

        return;
    }
    else if (reply == -1)
    {
        write("Timeout.\n");

        if (is_here)
        {
            me->catch_tell(this_player()->query_The_name(me) + " fails " +
                           "to respond.\n");
        }

        return;
    }
    else if (reply == 0)
    {
        write("Ok.\n");
        if (is_here)
        {
            me->catch_tell(this_player()->query_The_name(me) +
                           " declines to learn the song from you.\n");
        }

        return;
    }
}

public int
do_teach(string str)
{
    string song, who;
    object *target;
    mixed songfile;

    if (!strlen(str))
    {
        notify_fail("Teach what song to whom?\n");
        return 0;
    }

    if ((sscanf(str, "%s to %s", song, who) != 2) ||
        (!(target = PARSE_THIS(who, "[the] %l"))))
    {
        notify_fail("Teach a song to whom?\n");
        return 0;
    }

    if (sizeof(target) > 1)
    {
        write("You can only teach a song to one person at a time.\n");
        return 1;
    }

    setuid();
    seteuid(getuid());

    songfile = SONG_INDEX->parse_song(song);
    if (stringp(songfile))
    {
        notify_fail(songfile + "\n");
        return 0;
    }

    if (pointerp(songfile))
    {
        if (sizeof(songfile) > 1)
        {
            write("More than one song matches that title. Please be " +
                  "more specific.\n");
            return 1;
        }

        songfile = songfile[0];
    }

    if (!stringp(songfile))
    {
        write("Unable to teach that song....\n");
        return 1;
    }

    if (!IS_MUNDANE(songfile))
    {
        write("Only mundane songs can be taught to others.\n");
        return 1;
    }

   string newtitle = "";
   string *title_words;
   int j;
   int size = sizeof(title_words = explode(explode(read_file(songfile, 1, 1),
                                               "**")[0] + " "," "));

   for (j=0;j<size;j++)
       if (j<size-1)
          newtitle+=capitalize(title_words[j])+" ";
       else
          newtitle+=capitalize(title_words[j]);

    write("You ask " + target[0]->query_the_name(this_player()) + " if " +
          target[0]->query_pronoun() + " would like to learn the song '" +
          newtitle+ "' from you.\n");
    target[0]->catch_tell(this_player()->query_The_name(target[0]) + " asks if " +
          "you would like to learn a song, \"" +
          SONG_INDEX->query_title(songfile) + "\", from " +
          this_player()->query_objective() + ". (Yes/No)\n");

     clone_object(GUILD + "obj/yes_no")->get_answer(target[0],
         &reply_teach(this_player(), this_player()->query_the_name(target[0]),
         songfile), 20.0);
     return 1;
}

string
query_auto_load()
{
    return MASTER + ":";
}

void
init()
{
    ::init();

    if (!query_owner())
    {
        set_owner(this_player());
    }

    add_action(do_read, "read");
    add_action(do_read, "mread");
    add_action(do_erase, "erase");
    add_action(do_compose, "compose");
    add_action(do_memorise, "memorise");
    add_action(do_teach, "teach");
}
