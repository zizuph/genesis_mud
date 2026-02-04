#pragma no_clone
#pragma no_shadow
#pragma no_inherit

#include "guild_defs.h"

#define BASE_FILENAME_LENGTH 30

// If you change the length of the extension, be sure to update SONG_EXT_LEN
#define SONG_EXT      ".song"
#define SONG_EXT_LEN  5

#define SONG_DATA_TITLE  0
#define SONG_DATA_AUTHOR 1

// Each entry must be of uniform size to allow the fastest access when
// they're read.  We allow extra spaces beyond the declared base
// filename length.  This extra space allows for the unique identifier
// that is added to otherwise duplicate filenames, the file extension,
// and also for a newline.
#define INDEX_ENTRY_SIZE (BASE_FILENAME_LENGTH + 4 + SONG_EXT_LEN)

string *song_indexes;

public void update_songs();
public string pad(string str);
public string unpad(string str);
public string capitalize_title(string str);
public varargs void batch_generate_titles(string type, string *arr, int pos);
static varargs void batch_format_titles(string type, string *arr, int pos, string lines);

public void
create()
{
    setuid();
    seteuid(getuid());

    update_songs();
}

public void
update_songs()
{
    song_indexes = get_dir(SONG_ROOT + "*.index");
}

public string *
query_ignored_title_words()
{
    return ({ "a", "an", "the" });
}

public string
switch_letter(string letter)
{
    int c = letter[0];
    if (((c >= 'A') && (c <= 'Z')) ||
        ((c >= 'a') && (c <= 'z')) ||
        ((c >= '0') && (c <= '9')))
    {
        return letter;
    }

    switch (c)
    {
        case ' ':
            return "_";
        default:
            return "";
    }

    return "";
}

public string
title_to_filename(string title)
{
    string *letters;
    string *title_words;

    // First, remove extra space and then words which we don't want
    title_words = explode(title, " ") - ({ "" });
    title_words -= query_ignored_title_words();

    // Split each word into letters and reassign them as necessary
    title_words = map(title_words, &implode(, "") @
                                   &map(, switch_letter) @
                                   &explode(, ""));

    // Remove any words which got completely eliminated by the letter
    // reassignment (all letters reassigned to "") and then put the
    // words back together.
    title = implode(title_words - ({ "" }), switch_letter(" "));

    // Chop the title if it exceeds maximum length
    title = title[..BASE_FILENAME_LENGTH - 1];

    return title;
}

/*
 * Function name: find_song
 * Description:   Get the file path of a song, given a title, possibly a
 *                partial title.
 * Arguments:     1. (string) The (partial) title of the song
 *                2. (string) The type of song.  If unspecified, all types are
 *                            checked.
 * Returns:       An array of matching song files, or 0 if none are found.
 *                Matches will not include songs of different types: if matching
 *                songs are found of one type, searching ends there, and no
 *                other types are checked.
 */
public varargs mixed
find_song(mixed song, string type = 0)
{
    if (intp(song))
    {
        if (song == -1)
        {
            int i;
	    mixed next_song;
            string *songs = ({});
            while ((next_song = find_song(i++, type)) != 0)
            {
                songs += (string *)next_song;
            }

            return (sizeof(songs) ? songs : 0);
        }
        else if (song >= 0)
        {
            int i;
            string entry;
            string index;
            int position = ((int)song - 1) * INDEX_ENTRY_SIZE;
    
            if (type == 0)
            {
                for (i = 0; i < sizeof(song_indexes); i++)
                {
                    index = SONG_ROOT + song_indexes[i];
                    entry = read_bytes(index,
                                       position,
                                       position + INDEX_ENTRY_SIZE - 1);
                    if (strlen(entry))
                    {
                        break;
                    }
                }
            }
            else
            {
                index = SONG_ROOT + type + ".index";
                entry = read_bytes(index,
                                   position,
                                   INDEX_ENTRY_SIZE - 1);
            }
    
            if (strlen(entry))
            {
                entry = unpad(entry);
                return ({ index[..-7] + "/" + entry });
            }
        }

        return 0;
    }
    else if (stringp(song))
    {
        string fname = title_to_filename(song) + "*" + SONG_EXT;
        string *songs;
        int i;

        /* Using get_dir() might not be any faster than a binary search on the
         * index file (which would involve reading the whole file into memory or
         * file access operations for reading of smaller chunks). It does
         * greatly simplify the code, though.  Until I've had a chance to look
         * at the implementation of get_dir() and concluded that it's not
         * worth using, I'll keep it.
         */
        if (strlen(type))
        {
            songs = get_dir(SONG_ROOT + type + "/" + fname);
            return (sizeof(songs) ?
                map(songs, &operator(+)(SONG_ROOT + type + "/")) : 0);
        }
        else
        {
            string dir;
            for (i = 0; i < sizeof(song_indexes); i++)
            {
                dir = SONG_ROOT + song_indexes[i][..-7] + "/";
                songs = get_dir(dir + fname);
    
                if (sizeof(songs))
                {
                    return map(songs, &operator(+)(dir));
                }
            }
    
            return 0;
        }
    }

    return 0;
}

public mixed
find_song_in_list(mixed song, string *list)
{
    if (intp(song))
    {
        return ((song > sizeof(list)) ? 0 : ({ list[song - 1] }));
    }
    else if (stringp(song))
    {
        string fname = title_to_filename(song);
        list = regexp(list, "^(.*/)*" + fname + ".\\" +
            implode(explode(SONG_EXT, ""), "\\")) + "$";
    
        return (sizeof(list) ? list : 0);
    }

    return 0;
}

public void
generate_index(string song_selector, string index)
{
    string *songs = get_dir(song_selector);
    string index_str;

    // Assumes get_dir() returns the list properly sorted.  Bad idea?
    index_str = implode(map(songs, pad), "");
    write_file(index, index_str);
}

public void
generate_title_lists(string type)
{
    batch_generate_titles(type);
}

public varargs void
batch_generate_titles(string type, string *arr = 0, int pos = 0)
{
    string song_file, title, blah;
    string index = SONG_ROOT + type + ".index";
    string dir = SONG_ROOT + type + "/";
    int stop;

    if (!pointerp(arr))
    {
        int size = file_size(index);
    
        if (size <= 0)
        {
            return;
        }
    
        size /= INDEX_ENTRY_SIZE;
        arr = allocate(size);
    }

    stop = pos + 100;
    for (; (pos < stop) && (pos < sizeof(arr)); pos++)
    {
        song_file = read_bytes(index, pos * INDEX_ENTRY_SIZE, INDEX_ENTRY_SIZE);
        song_file = unpad(song_file);
        sscanf(read_file(dir + song_file, 1, 1), "%s**%s", title, blah);
        if (!strlen(title))
        {
            title = "???";
        }
        else
        {
            title = capitalize_title(title);
        }

        //arr[pos] = sprintf("%3d. %-34s", pos + 1, title);
        arr[pos] = title;
    }

    if (pos >= stop)
    {
        set_alarm(1.0, 0.0, &batch_generate_titles(type, arr, pos));
        return;
    }

    batch_format_titles(type, arr, 0);
}

static varargs void
batch_format_titles(string type, string *arr, int pos, string lines = "")
{
    int stop;
    string fmt;
    string formatted_str;

    if (pos >= sizeof(arr))
    {
        rm(SONG_ROOT + type + ".titles");
        write_file(SONG_ROOT + type + ".titles", lines);
        write("Done\n");
        return;
    }

    stop = pos + 100;

    fmt = "%" + strlen(sizeof(arr) + "") + "d. %-=30s\n";

    for (; (pos < stop) && (pos < sizeof(arr)); pos++)
    {
        formatted_str = sprintf(fmt, pos + 1, arr[pos]);
        lines += formatted_str;
    }

    set_alarm(1.0, 0.0, &batch_format_titles(type, arr, pos, lines));
}

/*
static void
batch_write_title_lists(string type, string *lines, int pos)
{
    int stop;
    int mid;
    string line;

    stop = pos + 100;
    mid = (sizeof(lines) + 1) / 2;

    for (; (pos < stop) && (pos < sizeof(lines)); pos++)
    {
        write_file(SONG_ROOT + type + ".titles1.tmp", lines[pos] + "\n");
        if (pos < mid)
        {
            line = ((strlen(lines[pos]) < 35) ?
                   sprintf("%-35s", lines[pos]) : lines[pos]);

            if ((pos + mid) < sizeof(lines))
            {
                line += " " + lines[pos + mid];
            }

            write_file(SONG_ROOT + type + ".titles2.tmp", line + "\n");
        }
    }

    if (pos >= stop)
    {
        set_alarm(1.0, 0.0, &batch_write_title_lists(type, lines, pos));
        return;
    }
}

static void batch_write_title_lists(string type, string *arr, int pos = 0)
{
    int mid = (sizeof(arr) + 1) / 2;
    int stop = pos + 100;

    for (; (pos < stop) && (pos < sizeof(arr)); pos++)
    {
        write_file(SONG_ROOT + type + ".titles1.tmp",
                   sprintf("%3d. %-s\n", pos + 1, arr[pos]));

        if (pos < mid)
        {
            write_file(SONG_ROOT + type + ".titles2.tmp",
                       sprintf("%3d. %-=33s %3d. %-=33s\n",
                               pos + 1,
                               arr[pos],
                               pos + mid + 1,
                               arr[pos + mid]));
        }
    }

    if (pos >= stop)
    {
        set_alarm(1.0, 0.0, &batch_write_title_lists(type, arr, pos));
        return;
    }

    rename(SONG_ROOT + type + ".titles1.tmp", SONG_ROOT + type + ".titles1");
    rename(SONG_ROOT + type + ".titles2.tmp", SONG_ROOT + type + ".titles2");
    write("Done.\n");
}
*/

#if 0
public void
batch_rename_songs(string *song_files, string output_dir)
{
    string song_file;
    string title, author, text;
    string fname;
    int i, version = 2;
    string *batch = song_files[..24];
    song_files = song_files[25..];

    for (i = 0; i < sizeof(batch); i++)
    {
        if (file_size(output_dir) == -1)
        {
            mkdir(output_dir);
        }

        song_file = batch[i];
        sscanf(read_file(song_file), "%s**%s\n%s", title, author, text);
        fname = title_to_filename(title);

        if (file_size(output_dir + fname) > 0)
        {
            while (file_size(output_dir + fname + "-" + version) > 0)
            {
                version++;
            }

            fname += "-" + version;
        }

        write(title + " to " + output_dir + fname + "\n");
        write_file(output_dir + fname,
                   title + "**" + author + "\n" + text);
    }

    if (sizeof(song_files) > 0)
    {
        set_alarm(1.0, 0.0, &batch_rename_songs(song_files, output_dir));
    }

    update_songs();
}

/*
 * Function name: rename_songs
 * Description:   Transfers song files from the old naming system to the new.
 * Arguments:     1. (string) The songs to transfer, should be a valid pathname
 *                            for get_dir()
 *                2. (string) The type of song (ballad, mundane, etc.) This
 *                            will be used to determine the directory where
 *                            the transferred songs are stored.
 */
public void rename_songs(string song_selection, string type)
{
    string *songs;
    string song_dir;

    song_dir = implode(explode(song_selection + "/", "/")[..-2], "/") + "/";
    songs = get_dir(song_selection);
    songs = map(songs, &operator(+)(song_dir));
    set_alarm(1.0, 0.0, &batch_rename_songs(songs, SONG_ROOT + type + "/"));
}
#endif

public string
pad(string str)
{
    return sprintf("%-" + (INDEX_ENTRY_SIZE - 1) + "s\n", str);
}

public string
unpad(string str)
{
    string padding;
    sscanf(str, "%s %s", str, padding);
    return str;
}

public string
capitalize_title(string title)
{
    string *lcwords =
        ({ "a", "an", "the", "of", "and", "or", "for", "by", "from", });
    string *words = explode(title, " ");
    int i;

    words[0] = capitalize(words[0]);
    for (i = 1; i < sizeof(words); i++)
    {
        if (member_array(words[i], lcwords) != -1)
        {
            continue;
        }

        words[i] = capitalize(words[i]);
    }

    return implode(words, " ");
}

public mixed
parse_song(string str)
{
    string type, which;
    int num;
    mixed songfile;
    mixed song_id;

    if ((sscanf(str, "%s %s", type, which) != 2) ||
        ((type != "mundane") &&
         (type != "epic") &&
         (type != "ballad") &&
         (type != "power")))
    {
        which = str;
        type = 0;
    }

    if (sscanf(which, "%d", num))
    {
        if (!strlen(type))
        {
            return "You must specify a song type with a song number.";
        }
    }
    else
    {
        num = -1;
    }

    if (!type || (type == "power"))
    {
        string *power = SONGBOOK_MANAGER->query_power_songs(this_player()) || ({});

        if (num != -1)
        {
            if (sizeof(power) >= num)
            {
	        songfile = power[num - 1];
            }
            else if (type == "power")
            {
                return "You don't know that many songs of power.";
            }
            // else it's an unspecified song type, and we keep going to check
            // for other song types which match.

        }
        else
        {
            switch (which)
            {
                case "pax":
                    songfile = "peace";
                    break;
                case "vibrato":
                    songfile = "blast";
                    break;
                case "bravuro":
                    songfile = "brave";
                    break;
                case "lux":
                    songfile = "lux";
                    break;
                case "soothe":
                    songfile = "soothe";
                    break;
                case "refresh":
                    songfile = "refresh";
                    break;
            }
        }
         
        if (!strlen(songfile))
        {
            if (type == "power")
            {
                return "There is no such song of power, \"" + which + "\".";
            }
            // else it's an unspecified song type, and we keep going to check
            // for other song types which match.
        }
        else if (member_array(songfile, power) == -1)
        {
            if (type == "power")
            {
                return "You know no such song of power, \"" + which + "\".";
            }
            // else it's an unspecified song type, and we keep going to check
            // for other song types which match.

            songfile = 0;
        }
        else
        {
            return ({ POWER_SONGS_DIR + songfile + ".c" });
        }
    }

    if (num == -1)
    {
        song_id = which;
    }
    else
    {
        song_id = num;
    }

    if (!type || (type == "mundane"))
    {
        string *mundane = SONGBOOK_MANAGER->query_mundane_songs(this_player()) || ({});

        songfile = find_song_in_list(song_id, mundane);
	if (pointerp(songfile) && (sizeof(songfile) > 0))
	{
  	    return map(songfile, &operator(+)(MUNDANE_SONGS_DIR));
	}
	else if (type == "mundane")
	{
            return "You know no such mundane song, \"" + which + "\".";
	}
    }

    if (type)
    {
        songfile = find_song(song_id, type);
    }
    else
    {
        songfile = find_song(song_id, "ballad") || find_song(song_id, "epic");
    }

    if (!songfile)
    {
        // Doing the title search is not cheap, so I hate to have to
        // do a second one.  There is a possibility, though, that a
        // title exists that happens to have a song type as its first
        // word ("Epic of Shiva", for instance).  In such a case, the
        // word will be mistaken for the song type and the title will
        // be incorrect ("of Shiva").  We try to catch such cases here.
        // Unfortunately, I can't think of any simple, natural syntax
        // (apart from possibly asking song titles to be in quotes)
        // that would make it easier to do a better job of parsing the
        // command properly to start with.
        if (strlen(type))
        {
            songfile = find_song(type + " " + song_id);
        }

    }

    return songfile ? songfile : "You know of no such song, \"" + which + "\".";
}

public string
query_title(string song)
{
    string str;
    string *data;

    setuid();
    seteuid(getuid());

    str = read_file(song, 1, 1);
    if (!str)
    {
        return 0;
    }

    data = explode(str, "**");

    if (sizeof(data) < (SONG_DATA_TITLE + 1))
    {
        return 0;
    }

    return capitalize_title(data[SONG_DATA_TITLE]);   
}


public string
query_author(string song)
{
    string str;
    string *data;

    setuid();
    seteuid(getuid());

    str = read_file(song, 1, 1);
    if (!str)
    {
        return 0;
    }

    data = explode(str, "**");

    if (sizeof(data) < (SONG_DATA_TITLE + 1))
    {
        return 0;
    }

    return capitalize_title(data[SONG_DATA_AUTHOR]);   
}

public string
create_new_mundane(string title, string author, string text)
{
    string fname;
    int version = 0;

    fname = MUNDANE_SONGS_DIR + title_to_filename(title) + SONG_EXT;
    while (file_size(fname + (version ? ("_" + version) : "")) != -1)
    {
        version++;
    }

    fname += (version ? ("_" + version) : "");

    write_file(fname, title + "**" + author + "\n" + text);

    return fname;
}
