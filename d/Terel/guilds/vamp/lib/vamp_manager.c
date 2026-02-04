/* manager.c created by Shiva@Genesis.
 * This file takes care of the logs and a few miscellanea
 * for the vampire guild.
 */

#pragma save_binary
#pragma no_clone
#pragma no_shadow

#include "../guild.h"
#include "../voptions.h"
#include <std.h>

inherit LIB_DIR+"manager";

#define OLD_MANAGER "/d/Emerald/common/guild/vamp/log/manager"

#define GUILD_MAP_TITLES        "guild_titles"
#define GUILD_MAP_PTITLES_SHOWN "ptitles_shown"
#define GUILD_MAP_MAX_LEVEL     "max_level"

#define IS_INDEX(x, map)  (member_array(x, m_indices(map)) >= 0)

#define OFFSET_UPDATE_INTERVAL (30 * 60)


/*
 * Function name:        create_data_manager
 * Description  :        set up the manager
 */
public void
create_data_manager()
{
    ::create_data_manager();    
    set_save_dir(DATA_DIR + "vamp/");
    set_garbage_dir(DATA_DIR + "vamp/old/");
} /* create_data_manager */


int
query_generation(mixed who)
{
    return get_info(who, "generation");
}

int
query_scars(mixed who)
{
    return get_info(who, "scar");
}

int
set_scars(mixed who, int scar)
{
    return set_info(who, "scar", scar);
}

int
query_scar_age(mixed who)
{
    return get_info(who, "scar_age");
}

int
set_scar_age(mixed who, int age)
{
    return set_info(who, "scar_age", age);
}

int
set_sire(mixed who1, mixed who2)
{
    int generation;

    if (!(who2 = get_name(who2)))
    {
        return 0;
    }

    generation = query_generation(who2) + 1;
    set_info(who1, "generation", generation);
    return set_info(who1, "sire", who2);
}

int
remove_sire(mixed who)
{
    return remove_info(who, "sire");
}

string
query_sire(mixed who)
{
    return get_info(who, "sire");
}

int
set_last_embrace_time(mixed who, int t)
{
    return set_info(who, "embrace_time", t);
}

int
query_last_embrace_time(mixed who)
{
    return get_info(who, "embrace_time");
}

int
is_covenmaster(mixed who)
{
    return get_info(who, "covenmaster");
}

int
remove_covenmaster(mixed who)
{
    return remove_info(who, "covenmaster");
}

int
set_covenmaster(mixed who)
{
    if (set_info(who, "covenmaster", 1))
    {
        map(filter(query_all_guild_members() -
            ({ get_name(who) }), is_covenmaster), remove_covenmaster);
        return 1;
    }

    return 0;
}

public mapping query_known_disguises(mixed who)
{
    return get_info(who,"known_disguises");
}

public mapping query_chosen_disguise(mixed who)
{
    return get_info(who,"chosen_disguise");
}

public void set_known_disguises(mixed who,mapping val)
{
    set_info(who,"known_disguises",val);
}

public void set_chosen_disguise(mixed who,mapping val)
{
    set_info(who,"chosen_disguise",val);
}

public void set_unprotected(mixed who,int val)
{
    set_info(who,"unprotected",val);
}

public int query_unprotected(mixed who)
{
    return get_info(who,"unprotected");
}

public void set_known_flight_locations(mixed who,string * val)
{
    set_info(who,"flight",val);
}

public string * query_known_flight_locations(mixed who)
{
    string * result=get_info(who,"flight");
    if (!result)
    {
        return ({ });
    }
    return result;
}

public void set_known_scries(mixed who,string * val)
{
    set_info(who,"scry",val);
}

public string * query_known_scries(mixed who)
{
    string * result=get_info(who,"scry");
    if (!result)
    {
        return ({ });
    }
    return result;
}


public string * query_allowed()
{
    string * allowed=get_info("master","allowed");
    if (!allowed)
    {
        allowed=({ });
    }
    return allowed;
}

public void add_allowed(string name)
{
    string * allowed=query_allowed();
    
    if (member_array(name,allowed)==-1)
    {
        allowed+=({ name });
    }
    allowed-=({ 0 });
    set_info("master","allowed",allowed);
}

public int remove_allowed(string name)
{
    int result;
    string * allowed=query_allowed();
    result=member_array(name,allowed);
    allowed-=({ name });
    set_info("master","allowed",allowed);
    return (result >=0 ? 1 : 0);
}


/* Add someone to the list of guild members, noting the time
 * and the new member's age
 */
int
convert_member(mixed who)
{
    setuid();
    seteuid(getuid());
    if (!OLD_MANAGER->load_member(who))
    {
        return 0;
    }
    

    add_member(who);
    
    set_start_time(who,OLD_MANAGER->query_start_time(who));
    set_start_age(who,OLD_MANAGER->query_start_age(who));
    add_personal_title(who,OLD_MANAGER->query_personal_title(who));
    set_info(who, "sire", OLD_MANAGER->query_sire(who));
    set_info(who, "generation", OLD_MANAGER->query_generation(who));
    if (OLD_MANAGER->is_covenmaster(who))
    {
        set_covenmaster(who);
    }        
    return 1;
}
    
int
add_member(mixed who)
{
    int result=::add_member(who);
    
    if (result)
    {
        set_options(who,VOPT_NOTIFY_THIRST 
                    | VOPT_NOTIFY_SUNLIGHT 
                    | VOPT_NOTIFY_LIGHT 
                    | VOPT_NOTIFY_LOGIN
                    | VOPT_VSAY);
    }
    return result;
}
