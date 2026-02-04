/* manager.c created by Shiva@Genesis.
 * This file takes care of the logs and a few miscellanea
 * for the vampire guild.
 */

#pragma save_binary
#pragma no_clone
#pragma no_shadow

#include "../guild_defs.h"
#include <macros.h>
#include <std.h>

#define DEBUG_WHO this_interactive()
#define DEBUG_ON
#include "/d/Emerald/sys/debug.h"

#define MANAGER_LOG_DIR        (MINSTREL_LOG)
#define MEMBER_SAVE_DIR        (MANAGER_LOG_DIR + "members/")
#define OLD_MEMBER_SAVE_DIR    (MANAGER_LOG_DIR + "members/old/")
#define MEMBER_FILE(who)       (MEMBER_SAVE_DIR + FCHAR(who) + "/" + who)
#define OLD_MEMBER_FILE(who)   (OLD_MEMBER_SAVE_DIR + FCHAR(who) + "/" + who)
#define MANAGER_SAVE           (MANAGER_LOG_DIR + "member_manager")
#define MANAGER_LOG            (MANAGER_LOG_DIR + "member_manager.log")

#define IS_INDEX(x, map)  (member_array(x, m_indices(map)) >= 0)

#define MEMBER_FILE_UPDATE_INTERVAL (itof(60 * 60 * 4))

static mapping mem_map = ([]);
mapping council_map = ([]);
int member_file_update_alarm = 0;

string *query_all_guild_members();
int remove_member(mixed who);
public int set_start_time(mixed who, int t);
public void member_file_update();
public void member_file_update2();
public void member_file_update3(string *members);
public void member_file_update4(string *members);
public void member_file_update_finish();
public int query_start_time(mixed who);

/*
 * Function name: member_file_update
 * Description:   Triggers the creation of a series of files which list
 *                current members. Routines which need a listing of members
 *                should typically reference these files, rather than building
 *                a list dynamically, especially if it may be done frequently.
 *                This routine is spread out among several functions using
 *                set_alarm so as to avoid eval_cost errors.
 */
public void
member_file_update()
{
    // cancel any active updates
    if (member_file_update_alarm != 0)
    {
        remove_alarm(member_file_update_alarm);
    }

    // Simply get things going
    member_file_update_alarm = set_alarm(0.0, 0.0, member_file_update2);
}

public void
member_file_update2()
{
    // Get a list of member names from the member data files.
    string *members = query_all_guild_members();
    // Pause for the next step
    member_file_update_alarm = set_alarm(1.0,
                                         0.0,
                                         &member_file_update3(members));
}

public void
member_file_update3(string *members)
{
    string member_str;
    string *output_arr;
    int pad, i;

    // Sort the member list by name.
    members = sort_array(members);
    output_arr = allocate(sizeof(members));
    pad = strlen(sizeof(members) + "");

    for (i = 0; i < sizeof(members); i++)
    {
        output_arr[i] = sprintf("%" + pad + "d. %s",
                                i + 1,
                                capitalize(members[i]));
    }

    member_str = implode(output_arr, "\n") + "\n";

    if (file_size(MANAGER_LOG_DIR + "members_alpha") > 0)
    {
        rm(MANAGER_LOG_DIR + "members_alpha");
    }

    // write the names out to a file
    write_file(MANAGER_LOG_DIR + "members_alpha", member_str);

    // Pause for the next step
    member_file_update_alarm = set_alarm(1.0,
                                         0.0,
                                         &member_file_update4(members));
}

public void
member_file_update4(string *members)
{
    string member_str;
    string *output_arr;
    int pad, i;

    // Sort the member list by join date
    members = sort_array(members, mkcompare(query_start_time));
    output_arr = allocate(sizeof(members));
    pad = strlen(sizeof(members) + "");

    for (i = 0; i < sizeof(members); i++)
    {
        output_arr[i] = sprintf("%" + pad + "d. %s",
                                i + 1,
                                capitalize(members[i]));
    }

    member_str = implode(output_arr, "\n") + "\n";

    if (file_size(MANAGER_LOG_DIR + "members_start") > 0)
    {
        rm(MANAGER_LOG_DIR + "members_start");
    }

    // write the names out to a file
    write_file(MANAGER_LOG_DIR + "members_start", member_str);

    // Pause for the next step
    member_file_update_alarm = set_alarm(1.0,
                                         0.0,
                                         &member_file_update_finish());
}

public void
member_file_update_finish()
{
    // Schedule the next update and quit
    member_file_update_alarm = set_alarm(MEMBER_FILE_UPDATE_INTERVAL,
                                         0.0,
                                         member_file_update);
}


static void
manager_log(string text)
{
    setuid();
    seteuid(getuid());
    write_file(MANAGER_LOG, ctime(time()) + " " + text + "\n");
}

int
load_member(string who)
{
    who = lower_case(who);
  
    if (mem_map[who])
    {
        return 1;
    }
  
    if (file_size(MEMBER_FILE(who) + ".o") < 0)
    {
        return 0;
    }
  
    mem_map[who] = restore_map(MEMBER_FILE(who));  
    return 1;
}

int
update_member(string who)
{
    who = lower_case(who);
  
    if (IS_INDEX(who, mem_map))
    {
        mem_map = m_delete(mem_map, who);
    }
  
    return load_member(who);
}

static void
update_members()
{
    int i;
    string *member_files, who;
  
    setuid();
    seteuid(getuid());
  
    member_files = filter(get_dir(MEMBER_SAVE_DIR), &wildmatch("*.o"));
    
    for (i = sizeof(member_files); i--;)
    {
        who = lower_case(member_files[i][..(strlen(member_files[i]) - 3)]);
    
        if (!SECURITY->exist_player(who))
        {
            rename(MEMBER_SAVE_DIR + member_files[i], 
                   OLD_MEMBER_SAVE_DIR + member_files[i]);
            manager_log(member_files[i] + " removed: player no longer exists.\n");
        }
    }
}

void
create()
{
    setuid();
    seteuid(getuid());
  
    restore_object(MANAGER_SAVE);

    member_file_update_alarm = set_alarm(1.0, 0.0, member_file_update);

    /* This seems to be deleting all members periodically
    update_members();
    */
}

varargs int
save(string who = 0)
{
    mapping member_info;
  
    if (!who)
    {
        save_object(MANAGER_SAVE);
        return 1;
    }

    who = lower_case(who);
   
    if (!mappingp(member_info = mem_map[who]))
    {
        return 0;
    }
  
    save_map(member_info, MEMBER_FILE(who));
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
    if (!(who = get_name(who)) || !load_member(who) ||
        !IS_INDEX(who, mem_map) || !IS_INDEX(info, mem_map[who]))
    {
        return 0;
    }
  
    return mem_map[who][info];
}

int
set_info(mixed who, string info, mixed val)
{
    if (!(who = get_name(who)) || !load_member(who) ||
        !IS_INDEX(who, mem_map))
    {
        return 0;
    }
  
    mem_map[who][info] = val;
    return save(who);
}

int
remove_info(mixed who, string info)
{
    if (!(who = get_name(who)) || !load_member(who) ||
        !IS_INDEX(who, mem_map))
    {
        return 0;
    }
  
    mem_map[who] = m_delete(mem_map[who], info);
    return save(who);
}

/* Add someone to the list of guild members, noting the time
 * and the new member's age
 */
int
add_member(mixed who)
{
    string name;

    if (!(who = get_name(who)))
    {
        return 0;
    }
      
    if (!stringp(who))
    {
        return 0;
    }
  
    mem_map[who] = ([ ]);

    set_alarm(0.0, 0.0, member_file_update);

    return save(who);
}

public int
new_member(mixed who)
{
    if (!add_member(who))
    {
        return 0;
    }

    set_start_time(who, time());
    return 1;
}

int
remove_member(mixed who)
{
    if (!(who = get_name(who)))
    {
        return 0;
    }
  
    if (IS_INDEX(who, mem_map))
    {
        mem_map = m_delete(mem_map, who);
    }
  
    if (file_size(MEMBER_FILE(who) + ".o") >= 0)
    {    
        rename(MEMBER_FILE(who) + ".o", OLD_MEMBER_FILE(who) + ".o");
    }

    set_alarm(0.0, 0.0, member_file_update);
  
    return 1;
}

mapping
query_member_map() { return mem_map + ([]); }

string *query_members() { return m_indices(mem_map); }

public int
query_member(mixed who)
{
    who = get_name(who);
    return load_member(who);
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

public string
query_muse(mixed who)
{
    return (string)get_info(who, "muse");
}

public int
set_muse(mixed who, string muse)
{
    return set_info(who, "muse", muse);
}

public string
query_mood(mixed who)
{
    return (string)get_info(who, "mood");
}

public int
set_mood(mixed who, string mood)
{
    return set_info(who, "mood", mood);
}

public 
/* Designate a player as being punished in some way.
 * Punishments are saved in a bit map, each 1
 * representing a specific punishment
 */
int
add_punishment(mixed who, int punishment)
{
    return set_info(who, "punish", get_info(who, "punish") | punishment);
}

int
remove_punishment(mixed who, int punishment)
{
    int previous_pun = get_info(who, "punish");
  
    if (!(previous_pun & punishment))
    {
        return 1;
    }
  
    return set_info(who, "punish", previous_pun ^ punishment);
}

int
set_punishment(mixed who, int punishment)
{
    return set_info(who, "punish", punishment);
}

int
query_punished(mixed who, int punishment)
{
    return (!!(punishment & get_info(who, "punish")));
}

int
query_punishment(mixed who)
{
    return get_info(who, "punish");
}

string member_name_from_member_file(string file)
{
    string name;

    if (file[-2..] != ".o")
    {
        return 0;
    }

    name = file[..-3];

    if (!SECURITY->exist_player(name))
    {
        return 0;
    }

    return name;
}

string *query_all_guild_members()
{
    string *names = ({});
    int c;

    setuid();
    seteuid(getuid());

    for (c = 'a'; c <= 'z'; c++)
    {
        names += map(get_dir(MEMBER_SAVE_DIR + strchar(c) + "/"),
                     member_name_from_member_file);
    }

    names -= ({ 0 });

    return names;
}

public int
add_council_position(string position)
{
    council_map[position] = 0;
    return save();
}

public int
remove_council_position(string position)
{
    council_map = m_delete(council_map, position);
    return save();
}

public int
set_council_position(string position, string who)
{
    council_map[position] = lower_case(who);
    return save();
}

public string *
query_council_members()
{
    return m_values(council_map) - ({ 0 });
}

public string *
query_council_positions()
{
    return m_indices(council_map);
}

public mixed
query_council_position(mixed who)
{
    string *positions = query_council_positions();
    int i;

    if (!(who = get_name(who)))
    {
        return 0;
    }

    for (i = 0; i < sizeof(positions); i++)
    {
        if (council_map[positions[i]] == who)
        {
            return positions[i];
        }
    }

    return 0;
}
