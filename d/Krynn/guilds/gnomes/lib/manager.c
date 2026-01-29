#pragma save_binary
#pragma no_clone
#pragma no_shadow

#include "../guild.h"

#include <macros.h>

static  mapping members  = ([]);
static  string  head_tin;

public int query_join_time(mixed who);

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
  
    save_map(member_save, MEMBER_DIR(who));
    return 1;
}

public int
load_member(string who)
{
    if (file_size(MEMBER_DIR(who) + ".o") < 0)
        return 0;
    
    members[who] = restore_map(MEMBER_DIR(who));
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

int
add_member(mixed who)
{
    int     join_time,
            gender,
            age;
    object  ob;
  
    if (objectp(who))
    {
        age = who->query_age();
        gender = who->query_gender();
    	who = who->query_real_name();
    }
  
    if (!stringp(who))
        return 0;
    
    if (!age && (ob = find_player(who)))
        age = ob->query_age();
    
    if (!intp(gender) && (ob = find_player(who)))
        gender = ob->query_gender();
    
    join_time = time();
    
    members[who] = ([
                        "join_time"     : join_time,
                        "last_awake"    : join_time,
                        "join_age"      : age,
                        "gender"        : gender,
                        "promote"       : 0
                    ]);
    
    return save_member(who);
}

public int
query_join_time(mixed who)
{
    return get_map(who, "join_time");
}

public int
query_join_age(mixed who)
{
    if (stringp(who))
        who = find_player(who);
    
    return who->query_age() - get_map(who, "join_age");
}

public void
set_last_awake(mixed who)
{
    set_map(who, "last_awake", time());
}

public int
query_last_awake(mixed who)
{
    return get_map(who, "last_awake");
}

public int
get_headtin()
{
    string *all_members = get_dir(MEMBERS);
    int     mp, hp, last, days = 1728000; // 20 days last active
    object  ob;
    
    if (!sizeof(all_members))
    {
        head_tin = "";
        return 0;
    }
    
    foreach(string member: all_members)
    {
        sscanf(member,"%s.o", member);
        
        if (load_member(member) && (time() - query_last_awake(member) < days))
        {
            if ((mp = get_map(member, "promote")) > (hp = get_map(head_tin, "promote")) ||
                (mp == hp && get_map(member, "join_time") < get_map(head_tin, "join_time")) ||
                !strlen(head_tin))
            {
                head_tin = member;
            }
        }
    }
    
    return 1;
}

public string
query_headtin_gender()
{
    get_headtin();
    
    return get_map(head_tin, "gender");
}

public string
query_headtin_name()
{
    get_headtin();
    
    return head_tin;
}

public int
set_promote(mixed who, int promote)
{
    set_map(who, "promote", promote);
}

public int
query_promote(mixed who)
{
    return get_map(who, "promote");
}