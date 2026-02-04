#include "guild_defs.h"

#define BATCH_SIZE 15

#define TEMPFILE "/d/Terel/cedric/guild/temp_index"

public void batch_write_indices(mapping song_map);
public void insert(string song_file, string index_file);

public void
create()
{
    setuid();
    seteuid(getuid());
}

public string *
query_ignored_title_words()
{
    return ({ "a", "an", "the" });
}

public void
create_index()
{
    mapping song_map = ([]);
    string *songs;

    songs = get_dir(BALLADDIR + "*.song");
    songs = map(songs, &operator(+)(BALLADDIR));
    song_map["ballads_index"] = songs;

    songs = get_dir(BALLADDIR + "*.epic");
    songs = map(songs, &operator(+)(BALLADDIR));
    song_map["epics_index"] = songs;

    set_alarm(1.0, 0.0, &batch_write_indices(song_map));
}

public void
batch_write_indices(mapping song_map)
{
    int i;
    string index_file = m_indices(song_map)[0];
    string *song_files = song_map[index_file];
    string *batch = song_files[..BATCH_SIZE - 1];
    song_files = song_files[BATCH_SIZE..];

    for (i = 0; i < sizeof(batch); i++)
    {
        write("Indexing " + batch[i] + "\n");
        insert(batch[i], "/d/Terel/cedric/guild/" + index_file);
        insert(batch[i], "/d/Terel/cedric/guild/full_index");
    }

    if (sizeof(song_files) < 1)
    {
        song_map = m_delete(song_map, index_file);
    }
    else
    {
        song_map[index_file] = song_files;
    }

    if (m_sizeof(song_map))
    {
        set_alarm(1.0, 0.0, &batch_write_indices(song_map));
    }
}

public void insert(string song_file, string index_file)
{
    string title, author;
    string *title_words;

    sscanf(read_file(song_file, 1, 1), "%s**%s", title, author);
    title_words = explode(title, " ") -
                  ({ "" }) -
                  query_ignored_title_words();
    title = implode(title_words, " ");

    if (file_size(index_file) < 4)
    {
        write_file(index_file, "0001\n" + title + "\t" + song_file + "\n");
    }
    else
    {
        int high, low, mid, entry_count, position;
        string entry_count_str, next_title, next_file, entry, head, tail;
       
        low = 2;
        sscanf(read_bytes(index_file, 0, 4), "%d", entry_count);
        high = entry_count + 1;
    
        while (low <= high)
        {
            mid = (high + low) / 2;
            entry = read_file(index_file, mid, mid);
            sscanf(entry, "%s\t%s", next_title, next_file);
            if (title > next_title)
            {
                low = mid + 1;
            }
            else if (title < next_title)
            {
                high = mid - 1;
            }
            else
            {
                break;
            }
        }

        position = low;
        entry_count_str = ++entry_count + "\n";
        while (strlen(entry_count_str) < 5)
        {
            entry_count_str = "0" + entry_count_str;
        }

        rm(TEMPFILE);

        head = entry_count_str + (position > 2 ? read_file(index_file, 2, position - 1) : "");
	write("head: " +  head[..30] + "\n");
        tail = (position > (entry_count + 1) ? "" : read_file(index_file, position));
	write("tail: " +  tail[..30] + "\n");
        write_file(TEMPFILE, head + 
                             title + "\t" + song_file + "\n" +
                             tail);

        rm(index_file);
        rename(TEMPFILE, index_file);
    }
}

public string
find_song(string title)
{
    int high, low, mid, entry_count;
    string next_title, next_file, entry;
    string *title_words;

    string index_file = "/d/Terel/cedric/guild/full_index";

    title_words = explode(title, " ") -
                  ({ "" }) -
                  query_ignored_title_words();
    title = implode(title_words, " ");

    
    low = 2;
    sscanf(read_bytes(index_file, 0, 4), "%d", entry_count);
    high = entry_count + 1;
    
    while (low <= high)
    {
        mid = (high + low) / 2;
        entry = read_file(index_file, mid, mid);
        sscanf(entry, "%s\t%s", next_title, next_file);
        if (title > next_title)
        {
            low = mid + 1;
        }
        else if (title < next_title)
        {
            high = mid - 1;
        }
        else
        {
            return next_file;
        }
    }

    return 0;
}
