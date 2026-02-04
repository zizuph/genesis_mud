#include "../guild_defs.h"

#include <time.h>

int clean_time;
string *all_songs;
string *active_songs;

public varargs void
retire_songs()
{
    string fname = MUNDANE_SONGS_DIR + "old/mundane_clean.";
    string tstr;
    string *existing_files;
    int tmp, fileno = 1, i, pos, size;

    if (all_songs == 0)
    {
        all_songs = get_dir(MUNDANE_SONGS_DIR);
    }

    tstr = TIME2FORMAT(time(), "ddmmyyyy");
    tstr = tstr[..3] + tstr[6..];
        
    existing_files = get_dir(fname + tstr + ".*");
    for (i = 0; i < sizeof(existing_files); i++)
    {
        if (sscanf(existing_files[i], "mundane_clean." + tstr + ".%d", tmp))
        {
            if (tmp > fileno)
            {
                fileno = tmp;
            }
        }
    }

    size = file_size(MUNDANE_SONGS_DIR + "mundane_clean." + tstr +
		     sprintf(".%02d", fileno));

    for (i = 0; (i < sizeof(all_songs)) && (i < 25); i++)
    {
        if ((pos = member_array(all_songs[i], active_songs)) != -1)
        {
            // Take the song out of the list to speed up subsequent searches
            write(active_songs[pos] + " ACTIVE.\n");
            active_songs = exclude_array(active_songs, pos, pos);
        }
        else
        {
	    string tmpsong;

            if (size > 20000)
            {
                fileno++;
            }

            write(all_songs[i] + " RETIRED.\n");

	    tmpsong = read_file(MUNDANE_SONGS_DIR + all_songs[i]) + "\n";
            write_file(fname + tstr + sprintf(".%02d", fileno), tmpsong);
	    size += strlen(tmpsong);

	    rm(MUNDANE_SONGS_DIR + all_songs[i]);
        }
    }

    all_songs = all_songs[25..];
    if (sizeof(all_songs) > 0)
    {
        set_alarm(1.0, 0.0, &retire_songs(active_songs, all_songs));
        return;
    }

    write("Done.\n");
}

public varargs void
collect_songs(string *books, string * song_listing = ({}))
{
    int i;

    for (i = 0; (i < sizeof(books)) && (i < 25); i++)
    {
        string *mundanes = SONGBOOK_MANAGER->query_mundane_songs(books[i]);
        if (mundanes)
        {
            song_listing += mundanes;
        }
    }

    books = books[25..];
    if (sizeof(books) > 0)
    {
        set_alarm(1.0, 0.0, &collect_songs(books, song_listing));
        return;
    }

    active_songs = song_listing;
    set_alarm(1.0, 0.0, &retire_songs());
}

public void
clean()
{
    string *books;

    setuid();
    seteuid(getuid());

    books = SONGBOOK_MANAGER->query_all_songbooks();
    set_alarm(1.0, 0.0, &collect_songs(books));
}
