#pragma save_binary
#pragma no_clone
#pragma no_shadow

#pragma no_inherit
#pragma strict_types

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include "../nov.h";

#define I_RANK 0
#define RECORD  NOV_DIR +"log/nov_record"
#define TP this_player()
#define CAP(x)           capitalize(x)

string *Nov = ({ });
mapping nov_members = ([]);


static nomask void save()
{
    setuid();
    seteuid(getuid());
    save_object(file_name(this_object()));
}

static nomask void create()
{
    setuid();
    seteuid(getuid());
    restore_object(file_name(this_object()));
}
 
int 
query_nov_member(string name) 
{ 
    return nov_members[lower_case(name)];
}

string *
query_nov_members()
{
    return m_indices(nov_members);
}

mapping 
query_nov_members_map()
{
    return nov_members + ([]);
}

int 
add_nov_member(string name, int type)
{
    nov_members[lower_case(name)] = type;
    save();
    return 1;
}


nomask int
remove_nov_member(string name)
{
    name = lower_case(name);

    if (member_array(name, m_indices(nov_members)) < 0)
    {
        return 0;
    }

    nov_members = m_delete(nov_members, lower_case(name));
    save();
    return 1;
}


public int
filter_nov(object x) 
{ 
    return (x->query_guild_name_lay() == GUILDNAME); 
}


public string *
query_nov()
{
    int     i;

    for (i = 0; i < sizeof(Nov); i++)
    {
        if (!SECURITY->exist_player(Nov[i]))
        {
            Nov -= ({ Nov[i] });           
        }
    }

    return (Nov + ({ }) );
}


public string
create_nov_list(string *noved_list)
{
    string  list,myname;   //ill_title
    int     i = 0,s;
    object pl;

    myname = lower_case(TP->query_name());

    list = "";

    for (i = 0, s = sizeof(noved_list); i < s; i++)
    {
        if (pl = find_player(noved_list[i]))
            list += "- " + CAP(noved_list[i]) + ", " + pl->query_guild_title_lay() + "\n";
        else
            list += "- " + CAP(noved_list[i]) + "\n";
    }
    if (!strlen(list))
        list = "- None available\n";
    return list + "\n";
}

public string
print_nov_list()
{
    return "These are the banedeads present in the world:\n\n" +
    create_nov_list(NOV_MANAGER->query_nov());
}

public string
print_nov_active()
{
    object *plist;
    string *noved_list;
    int i;
    
    plist = users();
    noved_list = ({ });
    for (i=0;i<sizeof(plist);i++) {
        if (filter_nov(plist[i]))
            noved_list += ({ lower_case(plist[i]->query_name()) });
    }
    
    return "The Necromancers serving Velsharoon currently present in the realms:\n\n" +
    create_nov_list(noved_list);
}
