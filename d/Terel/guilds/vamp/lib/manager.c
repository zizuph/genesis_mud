    /* manager.c created by Shiva@Genesis.
 * This file takes care of the logs and a few miscellanea
 * for the vampire guild.
 */

#pragma save_binary
#pragma no_clone
#pragma no_shadow

#include "../guild.h"
#include "../defs.h"
#include <std.h>

inherit "/d/Emerald/lib/data_manager";

#define MEMBER_FILE(who)       save_dir + who

#define GUILD_MAP_TITLES        "guild_titles"
#define GUILD_MAP_PTITLES_SHOWN "ptitles_shown"
#define GUILD_MAP_MAX_LEVEL     "max_level"

#define IS_INDEX(x, map)  (member_array(x, m_indices(map)) >= 0)

string save_dir;

string *query_all_guild_members();
int remove_member(mixed who);

public void
set_save_dir(string dir)
{
    save_dir=dir;
    ::set_save_dir(dir);
}

int
query_start_time(mixed who)
{
    return get_info(who, "start_time");
}

int 
set_start_time(mixed who, int when)
{
    return set_info(who, "start_time", when);
}

int
query_start_age(mixed who)
{
    return get_info(who, "start_age");
}

int
set_start_age(mixed who, int age)
{
    return set_info(who, "start_age", age);
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


int
remove_member(mixed who)
{
    return delete_data(who);
}

int
set_options(mixed who, int i)
{
  return set_info(who, "options", i);
}

int
query_options(mixed who)
{
    return get_info(who, "options");
}

int
add_personal_title(mixed who, string title)
{
    return set_info(who, "ptitle", title);
}

int
remove_personal_title(mixed who)
{
    return remove_info(who, "ptitle");
}

string
query_personal_title(mixed who)
{
    return get_info(who, "ptitle");
}

int
set_guild_titles(string *titles)
{
    set_info("master",GUILD_MAP_TITLES,titles);
    return 1;
}

string *
query_guild_titles() 
{
    return secure_var(get_info("master",GUILD_MAP_TITLES));

}

int
add_guild_title(string title, int level, int replace)
{
    string *guild_titles = get_info("master",GUILD_MAP_TITLES);

    if (!guild_titles)
    {
      guild_titles = ({});
    }

    if (!title || level < 0)
    {
        return 0;
    }
  
    if (level >= sizeof(guild_titles))
    {
        guild_titles += ({ title });
    }
    else if (replace)
    {
        guild_titles[level] = title;
    }
    else
    {
        guild_titles = guild_titles[0..(level - 1)] + ({ title }) +
	    guild_titles[level..(sizeof(guild_titles) - 1)];
    }
  
    set_guild_titles(guild_titles);
    save();
    return 1;
}

int
remove_guild_title(mixed which)
{
     string *guild_titles = query_guild_titles();
    if (stringp(which))
    {
        which = member_array(which, guild_titles);
    }
  
    if (!intp(which) || which < 0 || which >= sizeof(guild_titles))
    {
        return 0;
    }
    set_guild_titles(exclude_array(guild_titles, which, which));
    return 1;
}

int
set_max_level(int max)
{
    set_info("master",GUILD_MAP_MAX_LEVEL,max);
    return 1;
}

int
query_max_level()
{
    return max(1,get_info("master",GUILD_MAP_MAX_LEVEL));
}


void set_drained_resistances(mixed who,mapping resistances)
{
    set_info(who,"drained_resistances",resistances);
}

mapping query_drained_resistances(mixed who)
{
    mapping result=get_info(who,"drained_resistances");
    if (result && mappingp(result))
    {
        return result;
    }
    return ([ ]);
}

void set_drained_skills(mixed who,mapping skills)
{
    set_info(who,"drained_skills",skills);
}

mapping query_drained_skills(mixed who)
{
    mapping result=get_info(who,"drained_skills");
    if (result && mappingp(result))
    {
        return result;
    }
    return ([ ]);
}

void set_drained_quickness(mixed who,int quickness)
{
    set_info(who,"drained_quickness",quickness);
}

int query_drained_quickness(mixed who)
{
    return get_info(who,"drained_quickness");
}

public mapping query_drain_focus(mixed who)
{
    return get_info(who,"drain_focus");
}

public int set_drain_focus(mixed who,mapping value)
{
    return set_info(who,"drain_focus",value);
}


string member_name_from_member_file(string file)
{
    string name;

    if (!sscanf(file, "%s.o", name))
    {
        return 0;
    }

    if (!SECURITY->exist_player(name))
    {
        return 0;
    }

    return name;
}

int hidden_member(string name)
{
    if (name[-2..]=="jr")
    {
        return 1;
    }
    if (SECURITY->query_wiz_rank(name))
    {
        return 1;
    }
    return 0;
}


string *query_all_guild_members()
{
    string *names;

    setuid();
    seteuid(getuid());

    names = map(get_dir(save_dir), member_name_from_member_file);
    names -= ({ 0 });

    names -= (filter(names,hidden_member));

    return names;
}

int set_ptitles_shown(int i)
{
    return set_info("master",GUILD_MAP_PTITLES_SHOWN,i);
}

int query_ptitles_shown()
{
    return get_info("master",GUILD_MAP_PTITLES_SHOWN);
}

/* Add someone to the list of guild members, noting the time
 * and the new member's age
 */
int
add_member(mixed who)
{
    int age = 0;
    object ob;
  
    if (objectp(who))
    {
    	age = who->query_age();
    	who = who->query_real_name();
    }
  
    if (!stringp(who))
    {
        return 0;
    }
  
    if (!age && (ob = find_player(who)))
    {
        age = ob->query_age();
    }
  
    set_start_time(who, time());
    set_start_age(who,age);

    return 1;
}
