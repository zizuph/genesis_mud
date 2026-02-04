#pragma save_binary
#pragma no_clone
#pragma no_shadow

#include "../guild_defs.h"

#define SONGBOOK_SAVE_DIR (MINSTREL_LOG + "songbook/")
#define SONGBOOK_FILE(who) (SONGBOOK_SAVE_DIR + who[0..0] + "/" + who)
#define OLD_SONGBOOK_FILE(who) (SONGBOOK_SAVE_DIR + "old/" + who[0..0] + "/" + who)

#define IS_INDEX(x, map)  (member_array(x, m_indices(map)) >= 0)

static mapping songbook_map = ([]);

public int
load_songbook(string who)
{
    who = lower_case(who);

    if (songbook_map[who])
    {
        return 1;
    }

    if (file_size(SONGBOOK_FILE(who) + ".o") < 0)
    {
        return 0;
    }

    songbook_map[who] = restore_map(SONGBOOK_FILE(who));
    return 1;
}

public int
update_songbook(string who)
{
    who = lower_case(who);
  
    if (IS_INDEX(who, songbook_map))
    {
        songbook_map = m_delete(songbook_map, who);
    }
  
    return load_songbook(who);
}

void
create()
{
    setuid();
    seteuid(getuid());
}

varargs int
save(string who)
{
    mapping songbook_info;
  
    who = lower_case(who);
   
    if (!mappingp(songbook_info = songbook_map[who]))
    {
        return 0;
    }
  
    save_map(songbook_info, SONGBOOK_FILE(who));
    return 1;
}

string
get_name(mixed who)
{
    if (objectp(who))
    {
        who = who->query_real_name();
    }
  
    if (!stringp(who))
    {
        return 0;
    }
  
    return lower_case(who);
}

mixed
get_info(mixed who, string info)
{
    if (!(who = get_name(who)) || !load_songbook(who) ||
	!IS_INDEX(who, songbook_map) || !IS_INDEX(info, songbook_map[who]))
    {
        return 0;
    }
  
    return songbook_map[who][info];
}

int
set_info(mixed who, string info, mixed val)
{
    if (!(who = get_name(who)) || !load_songbook(who) ||
	!IS_INDEX(who, songbook_map))
    {
        return 0;
    }
  
    songbook_map[who][info] = val;
    return save(who);
}

int
remove_info(mixed who, string info)
{
    if (!(who = get_name(who)) || !load_songbook(who) ||
	!IS_INDEX(who, songbook_map))
    {
        return 0;
    }
  
    songbook_map[who] = m_delete(songbook_map[who], info);
    return save(who);
}

int
add_songbook(mixed who)
{
    who = get_name(who);
  
    songbook_map[who] = ([ ]);
  
    return save(who);
}

int
remove_songbook(mixed who)
{
    if (!(who = get_name(who)))
    {
	return 0;
    }
  
    if (IS_INDEX(who, songbook_map))
    {
	songbook_map = m_delete(songbook_map, who);
    }
  
    if (file_size(SONGBOOK_FILE(who) + ".o") >= 0)
    {    
	rename(SONGBOOK_FILE(who) + ".o", OLD_SONGBOOK_FILE(who) + ".o");
    }
  
    return 1;
}

mapping
query_songbook_map() { return songbook_map + ([]); }

string *query_songbooks() { return m_indices(songbook_map); }

public string *
query_power_songs(mixed who)
{
    return get_info(who, "power");
}

public int
set_power_songs(mixed who, string *power)
{
    return set_info(who, "power", power);
}

public int
add_power_songs(mixed who, mixed power)
{
    string *pre = query_power_songs(who);
    string *post;

    if (!pointerp(power))
    {
        power = ({ power });
    }

    if (pre)
    {
        post = pre | power;
    }
    else
    {
        post = power;
    }

    return set_power_songs(who, post);
}

public int
remove_power_songs(mixed who, mixed power)
{
    string *pre = query_power_songs(who);
    string *post;

    if (!pre)
    {
        return 1;
    }

    if (!pointerp(power))
    {
        power = ({ power });
    }

    post = pre - (string *)power;

    return set_power_songs(who, post);
}

public string *
query_mundane_songs(mixed who)
{
    string* result = get_info(who, "mundane");
    if (!sizeof(result))
    {
        return ({});
    }
    return result;
}

public int
set_mundane_songs(mixed who, string *mundane)
{
    return set_info(who, "mundane", mundane);
}

public int
add_mundane_songs(mixed who, mixed mundane)
{
    string *pre = query_mundane_songs(who);
    string *post;

    if (!pointerp(mundane))
    {
        mundane = ({ mundane });
    }

    if (pre)
    {
        post = pre + mundane;
    }
    else
    {
        post = mundane;
    }

    return set_mundane_songs(who, post);
}

public int
remove_mundane_songs(mixed who, mixed mundane)
{
    string *pre = query_mundane_songs(who);
    string *post;

    if (!pre)
    {
        return 1;
    }

    if (!pointerp(mundane))
    {
        mundane = ({ mundane });
    }

    post = pre - (string *)mundane;

    return set_mundane_songs(who, post);
}

string songbook_name_from_songbook_file(string file)
{
    string name;

    if (file[-2..] != ".o")
    {
        return 0;
    }

    name = file[..-3];

    return name;
}

string *query_all_songbooks()
{
    string *dirs;
    string *names = ({});
    int i;

    setuid();
    seteuid(getuid());

    // This is lazy on my part, not just hard-coding the array, but it's not
    // as if it's adding that much overhead.
    dirs = explode("abcdefghijklmnopqrstuvwxyz", "");
    for (i = 0; i < sizeof(dirs); i++)
    {
        names += map(get_dir(SONGBOOK_SAVE_DIR + dirs[i] + "/*.o"),
		     songbook_name_from_songbook_file);
    }

    names -= ({ 0 });

    return names;
}
