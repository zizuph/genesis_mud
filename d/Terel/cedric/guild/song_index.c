#include "/d/Terel/cedric/guild/guild_defs.h"

#define SONG_ENTRY_SIZE   3
#define SONG_ENTRY_TITLE  0
#define SONG_ENTRY_AUTHOR 1
#define SONG_ENTRY_FILE   2

mapping song_map = ([]);

public void load_song(string song_file);
public void load_epics();

public void
create()
{
    setuid();
    seteuid(getuid());

    // load songs on an alarm to avoid any serious problems from
    // eval cost errors
    set_alarm(0.0, 0.0, load_epics);
}

void
load_epics()
{
    string *epic_files;

    epic_files = get_dir(BALLADDIR + "*.epic");
    if (sizeof(epic_files) > 300)
    {
        epic_files = epic_files[..300];
    }

    map(epic_files, load_song @ &operator(+)(BALLADDIR,));
}

public string *
query_ignored_title_words()
{
    return ({ "a", "an", "the" });
}

public mixed *
get_song_entry(string song_file)
{
    string song_info;
    string *song_data;
    string *title_words;
    string song_title;
    mixed *song_entry;

    song_info = read_file(song_file, 1, 1);
    song_data = explode(song_info, "**");
    title_words = explode(song_data[0], " ") -
                  ({ "" }) -
                  query_ignored_title_words();
    song_title = implode(title_words, " ");

    song_entry = allocate(SONG_ENTRY_SIZE);
    song_entry[SONG_ENTRY_TITLE]  = song_title;
    song_entry[SONG_ENTRY_AUTHOR] = song_data[1];
    song_entry[SONG_ENTRY_FILE]   = song_file;
    return song_entry;
}

public void
load_song(string song_file)
{
    if (song_map[song_file] == 0)
    {
        song_map[song_file] = get_song_entry(song_file);
    }
}

public int
query_max_search_size()
{
    return 120;
}

public varargs string
find_song(string title, string *subset = 0)
{
    mixed *song_entries;
    string *split;
    int i;
    string entry_title;

    if (!subset)
    {
        song_entries = m_values(song_map);
	if (sizeof(song_entries) > query_max_search_size())
	{
  	    song_entries = song_entries[..query_max_search_size() - 1];
	}
    }
    else
    {
	if (sizeof(subset) > query_max_search_size())
	{
  	    subset = subset[..query_max_search_size() - 1];
	}

        song_entries = map(subset, &operator([])(song_map, )) - ({ 0 });
    }

    // Remove from the title words we wish to ignore
    split = explode(title, " ") - ({ "" });
    split -= query_ignored_title_words();
    title = implode(split, " ");

    for (i = 0; i < sizeof(song_entries); i++)
    {
        entry_title = song_entries[i][SONG_ENTRY_TITLE];
        if ((strlen(entry_title) >= strlen(title)) &&
            (entry_title[..(strlen(title) - 1)] == title))
        {
            return song_entries[i][SONG_ENTRY_FILE];
        }
    }

    return 0;
}
