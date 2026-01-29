/*
 * Temporary code added to add an enemy system, may
 * need improving.
 *
 */

#pragma save_binary
#pragma no_clone
#pragma no_shadow

#include <std.h>
#include "../guild.h"

#include <macros.h>

static mapping members  = ([]);

void
create()
{
    setuid();
    seteuid(getuid());
}

public int
save_member(string who)
{
    mapping member_save;
   
    who = lower_case(who);
    
    if (!mappingp(member_save = members[who]))
        return 0;
  
    save_map(member_save, STATUS_DIR(who));
    return 1;
}

public int
load_member(string who)
{
    if (file_size(STATUS_DIR(who) + ".o") < 0)
        return 0;
    
    members[who] = restore_map(STATUS_DIR(who));
    return 1;
}

public string
get_name(mixed who)
{
    if (objectp(who))
        who = who->query_real_name();
    
    if (!stringp(who))
        return "";
    
    return who;
}

mixed
get_map(mixed who, string map)
{
    if (!(who = get_name(who)) || !load_member(who) ||
        (member_array(map, m_indexes(members[who])) < 0))
        return 0;
  
    return members[who][map];
}

int
set_map(mixed who, string map, mixed set)
{
    if (!(who = get_name(who)) || !load_member(who))
        return 0;
    
    members[who][map] = set;
    return save_member(who);
}

varargs mapping
query_status_list(mixed who)
{
    if (!load_member("status_list") || !stringp(who))
        return ([]);
	
    if (member_array(who, m_indexes(members["status_list"])) > -1)
        return members["status_list"][who];
	
    return members["status_list"];
}

public int
add_status(mixed who, string action)
{
    if (objectp(who))
        who = who->query_real_name();
	
    if (!stringp(who))
        return -2;
	
    if (!(SECURITY->exist_player(who)))
        return -1;
    
    if (member_array(who, m_indexes(query_status_list())) > -1)
        return 0;
	
    members["status_list"][who] = action;
	
    return save_member(who);
}

int
remove_status(string who)
{
    if (!load_member("status_list") || !stringp(who))
        return -1;
	
    if (member_array(who, m_indexes(query_status_list())) < 0)
        return 0;
	
    members["status_list"][who] = "";
	
    return save_member(who);
}