#pragma no_clone
#pragma no_shadow
#pragma no_inherit

#include "../guild_defs.h"
#include <mail.h>

#define BASE_FILENAME_LENGTH 30

// If you change the length of the extension, be sure to update SONG_EXT_LEN
#define SONG_EXT      ".song"
#define SONG_EXT_LEN  5

#define SONG_DATA_TITLE  0
#define SONG_DATA_AUTHOR 1

#define BALLAD_REVIEW_LOG (MINSTREL_LOG + "ballad_reviews")
#define BALLAD_SONGS_DENIED_DIR (BALLAD_SONGS_SUBMISSION_DIR + "denied/")

// Each entry must be of uniform size to allow the fastest access when
// they're read.  We allow extra spaces beyond the declared base
// filename length.  This extra space allows for the unique identifier
// that is added to otherwise duplicate filenames, the file extension,
// and also for a newline.
#define INDEX_ENTRY_SIZE (BASE_FILENAME_LENGTH + 4 + SONG_EXT_LEN)

string *song_indexes;
mapping ballad_data_map = ([]);

public void update_songs(string type);
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

    // First, make all letters lower case
    title = implode(map(explode(title, ""), lower_case), "");

    // Next, remove extra space and then words which we don't want
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
                                       position + INDEX_ENTRY_SIZE);
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
                                   INDEX_ENTRY_SIZE);
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
        list = regexp(list, "^(.*/)*" + fname);
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
    //
    // I have three ways to write this out:
    //     1) Concatenate all the strings normally (+ operator) and write
    //     2) Implode the strings and write
    //     3) write each string individually
    // Concatenation of a large number of strings is notoriously inefficient
    // because of all of the memory allocation that goes on.  Large numbers
    // of calls to write_file is going to be slow because each call has a
    // fair bit of overhead (file open/close).  Implode concatenates the
    // strings most efficiently, and writing one single string eliminates
    // the waste of multiple writes.
    index_str = implode(map(songs, pad), "");

    if (file_size(index) >= 0)
    {
        rm(index);
    }

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

public void
update_songs(string type)
{
    generate_index(SONG_ROOT + type + "/*" + SONG_EXT,
                   SONG_ROOT + type + ".index");
    set_alarm(0.0, 0.0, &generate_title_lists(type));
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


public string
pad(string str)
{
    return sprintf("%-" + (INDEX_ENTRY_SIZE - 1) + "s\n", str);
}

public string
unpad(string str)
{
    string padding;
    sscanf(str, "%s %s\n", str, padding);
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

    if (str[strlen(str) - 1] == '\n')
    {
        str = str[..-2];
    }

    data = explode(str, "**");

    if (sizeof(data) < (SONG_DATA_TITLE + 1))
    {
        return 0;
    }

    return data[SONG_DATA_TITLE];
}

public string
query_lc_title(string song)
{
    string title = query_title(song);
    if (!title)
    {
        return title;
    }

    return implode(map(explode(title, ""), lower_case), "");
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

    if (str[strlen(str) - 1] == '\n')
    {
        str = str[..-2];
    }

    data = explode(str, "**");

    if (sizeof(data) < (SONG_DATA_TITLE + 1))
    {
        return 0;
    }

    return capitalize_title(data[SONG_DATA_AUTHOR]);   
}

public string
query_text(string song)
{
    string str;
    string *data;

    setuid();
    seteuid(getuid());

    str = read_file(song, 2);

    if (!str)
    {
        return 0;
    }

    // Take off the trailing "\n**"
    return str[..-4];
}

public int
replace_text(string songfile, string newtext)
{
    string data = read_file(songfile, 1, 1);
    if (!data)
    {
        return 0;
    }

    rm(songfile);

    return write_file(songfile, data + newtext + "\n**");
}

public string
submit_ballad_edits(string songfile, string newtext, string comments)
{
    string fname, title, author;
    int version = 0;

    title = query_title(songfile);
    author = query_author(songfile);

    fname = BALLAD_SONGS_SUBMISSION_DIR + title_to_filename(title);
    while (file_size(fname + (version ? ("_" + version) : "") + SONG_EXT) != -1)
    {
        version++;
    }

    fname += (version ? ("_" + version) : "");

    save_map(([ "edit" : songfile, "comments" : comments ]), fname);
    write_file(fname + SONG_EXT, title + "**" + author + "\n" + newtext + "\n**");

    return fname;
}

public varargs string
create_new_ballad(string title, string author, string text, string comments, int notify = 1)
{
    string fname;
    int version = 0;

    fname = BALLAD_SONGS_SUBMISSION_DIR + title_to_filename(title);
    while (file_size(fname + (version ? ("_" + version) : "") + SONG_EXT) != -1)
    {
        version++;
    }

    fname += (version ? ("_" + version) : "");

    save_map(([ "edit" : 0, "comments" : comments, "submit_time" : time() ]),
	     fname);
    write_file(fname + SONG_EXT, title + "**" + author + "\n" + text + "\n**");

    if (notify)
    {
        CREATE_MAIL("Minstrel Ballad Submitted",
		    lower_case(author),
                    implode(MEMBER_MANAGER->query_council_members(), ","),
                    "",
                    "A song, \"" + title + "\" by " + capitalize(author) + 
                    " has been submitted for inclusion among the great " +
                    "Ballads of the August Order of Minstrels. Please review " +
                    "this new song as soon as possible.\n");
    }

    return fname;
}

public string *
query_ballad_submissions()
{
    string *files;

    files = get_dir(BALLAD_SONGS_SUBMISSION_DIR + "/*" + SONG_EXT);
    files = map(files, &operator(+)(BALLAD_SONGS_SUBMISSION_DIR));

    // Remove song files that don't have a corresponding ".o" file
    files = filter(files, &operator(>)(, 0) @
                          file_size @
                          &operator(+)(, ".o") @
                          &extract(, 0, -(strlen(SONG_EXT) + 1)));

    return files;
}

public string
create_new_epic(string title, string author, string text)
{
    string fname;
    int version = 0;

    fname = EPIC_SONGS_DIR + title_to_filename(title);
    while (file_size(fname + (version ? ("_" + version) : "") + SONG_EXT) != -1)
    {
        version++;
    }

    fname += (version ? ("_" + version) : "") + SONG_EXT;

    write_file(fname, title + "**" + author + "\n" + text + "\n**");

    set_alarm(0.0, 0.0, &update_songs("epic"));

    return fname;
}

public int
remove_epic(string song)
{
    if (!wildmatch(EPIC_SONGS_DIR + "*.song", song))
    {
        return 0;
    }

    if (file_size(song) <= 0)
    {
        return 0;
    }

    rm(song);

    set_alarm(0.0, 0.0, &update_songs("epic"));
    return 1;
}

public string
create_new_mundane(string title, string author, string text)
{
    string fname;
    int version = 0;

    fname = MUNDANE_SONGS_DIR + title_to_filename(title);
    while (file_size(fname + (version ? ("_" + version) : "") + SONG_EXT) != -1)
    {
        version++;
    }

    fname += (version ? ("_" + version) : "") + SONG_EXT;

    write_file(fname, title + "**" + author + "\n" + text + "\n**");

    set_alarm(0.0, 0.0, &update_songs("mundane"));

    return fname;
}

void
cap_titles(string type)
{
    string s, title, index = "/d/Terel/cedric/guild/songs/" + type + ".index";
    int pos = 200;
    while (s = read_bytes(index, pos * INDEX_ENTRY_SIZE, INDEX_ENTRY_SIZE))
    {
        s = "/d/Terel/cedric/guild/songs/" + type + "/" + unpad(s);
        title = capitalize_title(query_title(s));
        dump_array(title);
        write_bytes(s, 0, title);
        pos++;
    }
}

public mapping
get_ballad_data(string ballad)
{
    mapping ballad_data;

    if (ballad[-(strlen(SONG_EXT))..] != SONG_EXT)
    {
        return 0;
    }

    if (ballad[..(strlen(BALLAD_SONGS_SUBMISSION_DIR) - 1)] !=
        BALLAD_SONGS_SUBMISSION_DIR)
    {
        ballad = BALLAD_SONGS_SUBMISSION_DIR + ballad;
    }

    // I either need a more efficient way of accessing individual data elements
    // in the data file or just use a cache. For now, the cache is easiest.

    if (!(ballad_data = ballad_data_map[ballad]))
    {
        string ballad_data_file = ballad[..-(strlen(SONG_EXT) + 1)];
        ballad_data = restore_map(ballad_data_file);
        ballad_data_map[ballad] = ballad_data;
    }

    return ballad_data;
}

public void
clear_ballad_data(string ballad)
{
    if (ballad[-(strlen(SONG_EXT))..] != SONG_EXT)
    {
        return;
    }

    if (ballad[..(strlen(BALLAD_SONGS_SUBMISSION_DIR) - 1)] !=
        BALLAD_SONGS_SUBMISSION_DIR)
    {
        ballad = BALLAD_SONGS_SUBMISSION_DIR + ballad;
    }

    ballad_data_map = m_delete(ballad_data_map, ballad);
}

public void
save_ballad_data(mapping data, string ballad)
{
    if (ballad[-(strlen(SONG_EXT))..] != SONG_EXT)
    {
        return;
    }

    if (ballad[..(strlen(BALLAD_SONGS_SUBMISSION_DIR) - 1)] !=
        BALLAD_SONGS_SUBMISSION_DIR)
    {
        ballad = BALLAD_SONGS_SUBMISSION_DIR + ballad;
    }

    ballad_data_map[ballad] = data;
    save_map(data, ballad[..-(strlen(SONG_EXT) + 1)]);
}

public int
query_ballad_submit_time(string ballad)
{
    mapping ballad_data = get_ballad_data(ballad);

    if (!ballad_data)
    {
        return 0;
    }

    return ballad_data["submit_time"];
}

public string *
query_ballad_approve_votes(string ballad)
{
    mapping ballad_data = get_ballad_data(ballad);

    if (!ballad_data)
    {
        return 0;
    }

    return ballad_data["approve"] || ({});
}

public void
add_ballad_approve_vote(string ballad, string voter)
{
    mapping ballad_data = get_ballad_data(ballad);
    string *votes;

    if (!ballad_data)
    {
        return 0;
    }

    votes = ballad_data["deny"] || ({});
    votes -= ({ voter });
    ballad_data["deny"] = votes;

    votes = ballad_data["approve"] || ({});
    votes |= ({ voter });
    ballad_data["approve"] = votes;

    save_ballad_data(ballad_data, ballad);
}

public int
add_ballad_deny_vote(string ballad, string voter)
{
    mapping ballad_data = get_ballad_data(ballad);
    string *votes;

    if (!ballad_data)
    {
        return 0;
    }

    votes = ballad_data["approve"] || ({});
    votes -= ({ voter });
    ballad_data["approve"] = votes;

    votes = ballad_data["deny"] || ({});
    votes |= ({ voter });
    ballad_data["deny"] = votes;

    save_ballad_data(ballad_data, ballad);
}

public string *
query_ballad_deny_votes(string ballad)
{
    mapping ballad_data = get_ballad_data(ballad);

    if (!ballad_data)
    {
        return 0;
    }

    return ballad_data["deny"] || ({});
}

public string *
query_ballad_commenters(string ballad)
{
    mapping ballad_data = get_ballad_data(ballad);
    string *commenters = ({}), *review_commenters;

    if (!ballad_data)
    {
        return 0;
    }

    if (ballad_data["comments"])
    {
        commenters += ({ lower_case(query_author(ballad)) });
    }

    review_commenters = filter(m_indices(ballad_data), &wildmatch("comments_*"));
    commenters += map(review_commenters, &extract(, 9, -1));
    return commenters;
}

public string
query_ballad_comments(string ballad, string commenter)
{
    mapping ballad_data = get_ballad_data(ballad);
    string comments;

    if (!ballad_data)
    {
        return 0;
    }

    if (!(comments = ballad_data["comments_" + commenter]))
    {
        if (lower_case(commenter) == lower_case(query_author(ballad)))
        {
            comments = ballad_data["comments"];
        }
    }

    return comments;
}

public void
add_ballad_comments(string ballad, string commenter, string comments)
{
    mapping m = get_ballad_data(ballad) || ([]);
    m["comments_" + commenter] = comments;
    save_ballad_data(m, ballad);
}

public varargs string
approve_ballad(string ballad, int notify = 1)
{
    string fname;
    int version = 0;
    string title = query_title(ballad);
    string author = query_author(ballad);
    mapping ballad_data = get_ballad_data(ballad);

    fname = BALLAD_SONGS_DIR + title_to_filename(title);
    while (file_size(fname + (version ? ("_" + version) : "") + SONG_EXT) != -1)
    {
        version++;
    }

    fname += (version ? ("_" + version) : "") + SONG_EXT;

    write_file(fname, read_file(ballad));

#ifdef BALLAD_REVIEW_LOG
    {
        string *logs = get_dir(BALLAD_REVIEW_LOG + ".???");
        string accept, deny, comments, *commenters;
        int logno, this_log = 1;
        int i, subtime, t;

        for (i = 0; i < sizeof(logs); i++)
	{
	    if (!sscanf(logs[i], BALLAD_REVIEW_LOG + ".%d", logno))
	    {
	        continue;
	    }

            if (logno > this_log)
	    {
	        this_log = logno;
	    }
	}

	if (file_size(BALLAD_REVIEW_LOG + sprintf(".%03d", this_log)) > 50000)
	{
	    this_log++;
	}

	accept = implode(query_ballad_approve_votes(ballad) || ({}), ", ");
	deny = implode(query_ballad_deny_votes(ballad) || ({}), ", ");
        subtime = query_ballad_submit_time(ballad);

        commenters = query_ballad_commenters(ballad) || ({});

        for (i = 0, comments = ""; i < sizeof(commenters); i++)
	{
  	    comments += "(" + capitalize(commenters[i]) + ")\t" +
                query_ballad_comments(ballad, commenters[i]);
	}

        write_file(BALLAD_REVIEW_LOG + sprintf(".%03d", this_log),
            query_title(fname) + " by " + author + " approved.\n" +
	    "Accept: " + (strlen(accept) ? accept : "NONE") + "\n" +
	    "Deny: " + (strlen(deny) ? deny : "NONE") + "\n" +
            "Comments:\n" + comments +
	    "Submit time: " + ctime(subtime) + " (" + subtime + ")\n" +
	    "Approve time: " + ctime(t) + " (" + t + ")\n" +
	    "File: " + fname + "\n");
    }
#endif

    rm(ballad);
    rm(ballad[..-(strlen(SONG_EXT) + 1)] + ".o");

    update_songs("ballad");

    if (notify)
    {
        CREATE_MAIL("Minstrel Ballad Accepted",
	  	    "The Cycle",
		    lower_case(author),
                    implode(MEMBER_MANAGER->query_council_members(), ","),
                    "Your song, \"" + title + "\" has been accepted for " +
                    "inclusion among the great Ballads of the August Order " +
                    "of Minstrels. Your contribution is greatly appreciated." +
                    "\n\nThank you,\n\nThe Cycle of the August Order of " +
                    "Minstrels\n\nP.S. This is an automatically generated " +
                    "message. To contact the minstrel council, please mail " +
                    "them directly; do not reply to this message.\n");
    }

    return fname;
}

public varargs string
deny_ballad(string ballad, int notify = 1)
{
    string fname;
    int version = 0;
    string title = query_title(ballad);
    string author = query_author(ballad);
    mapping ballad_data = get_ballad_data(ballad);

    fname = BALLAD_SONGS_DENIED_DIR + title_to_filename(title);
    while (file_size(fname + (version ? ("_" + version) : "") + SONG_EXT) != -1)
    {
        version++;
    }

    fname += (version ? ("_" + version) : "") + SONG_EXT;

    write_file(fname, read_file(ballad));

#ifdef BALLAD_REVIEW_LOG
    {
        string *logs = get_dir(BALLAD_REVIEW_LOG + ".???");
        string accept, deny, comments, *commenters;
        int logno, this_log = 1;
        int i, subtime, t;

        for (i = 0; i < sizeof(logs); i++)
	{
	    if (!sscanf(logs[i], BALLAD_REVIEW_LOG + ".%d", logno))
	    {
	        continue;
	    }

            if (logno > this_log)
	    {
	        this_log = logno;
	    }
	}

	if (file_size(BALLAD_REVIEW_LOG + sprintf(".%03d", this_log)) > 50000)
	{
	    this_log++;
	}

	accept = implode(query_ballad_approve_votes(ballad) || ({}), ", ");
	deny = implode(query_ballad_deny_votes(ballad) || ({}), ", ");
        subtime = query_ballad_submit_time(ballad);

        commenters = query_ballad_commenters(ballad) || ({});

        for (i = 0, comments = ""; i < sizeof(commenters); i++)
	{
  	    comments += "(" + capitalize(commenters[i]) + ")\t" +
                query_ballad_comments(ballad, commenters[i]);
	}

        write_file(BALLAD_REVIEW_LOG + sprintf(".%03d", this_log),
            query_title(fname) + " by " + author + " denied.\n" +
	    "Accept: " + (strlen(accept) ? accept : "NONE") + "\n" +
	    "Deny: " + (strlen(deny) ? deny : "NONE") + "\n" +
            "Comments:\n" + comments +
	    "Submit time: " + ctime(subtime) + " (" + subtime + ")\n" +
	    "Deny time: " + ctime(t) + " (" + t + ")\n" +
	    "File: " + fname + "\n");
    }
#endif

    rm(ballad);
    rm(ballad[..-(strlen(SONG_EXT) + 1)] + ".o");

    if (notify)
    {
        CREATE_MAIL("Minstrel Ballad Rejected",
	  	    "The Cycle",
		    lower_case(author),
                    implode(MEMBER_MANAGER->query_council_members(), ","),
                    "Your song, \"" + title + "\" has been denied for " +
                    "inclusion among the Ballads of the August Order " +
                    "of Minstrels. Please contact the Minstrel Cycle for " +
                    "more information." +
                    "\n\nThank you,\n\nThe Cycle of the August Order of " +
                    "Minstrels\n\nP.S. This is an automatically generated " +
                    "message. To contact the minstrel council, please mail " +
                    "them directly; do not reply to this message.\n");
    }

    return fname;
}
