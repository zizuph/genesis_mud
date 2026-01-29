/* 
 * Saurian Racial Guild Master Surname Object
 *
 * This manager will take care of the member surname data. It will only return info
 * for real players, not npcs.
 *
 * Created by Arman Sept 2017
 * Modified by Mirandus for Saurian Racial
 */

#pragma strict_types

#include <files.h>
#include <ss_types.h>
#include <const.h>
#include "../lizards.h"

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
public mapping      cached_player_info = ([ ]);

#define EVENT_LOG (GUILD_LOG + "events")

// The create function is called for every object. We mask it here
// to do some basic initialization for the handler
void
create()
{
    setuid();
    seteuid(getuid());
}

/*
 * Function:    get_id
 * Description: Get the real name of the player string or object passed.
 *              It's just a convenience function so that the right answer
 *              is given without checking object types in the calling
 *              code.
 */
public string
get_id(mixed player)
{
    string name;
    
    if (stringp(player) && strlen(player))
    {
        name = player;
    }
    else if (objectp(player) && IS_PLAYER_OBJECT(player))
    {
        name = player->query_real_name();
    }    
    
    return name;
}

/* 
 * Function:    load_player_info
 * Description: This loads the player info from their specific file
 *              and returns the mapping of it.
 */
public mapping
load_player_info(mixed player)
{
    string name;
    mapping player_info;
    
    name = get_id(player);
    if (!strlen(name))
    {
        return ([ ]);
    }
    
    if (cached_player_info[name])
    {
        return cached_player_info[name];
    }
    
    if (!SECURITY->exist_player(name))
    {
        return ([ ]);
    }
    
    player_info = ([ ]);
        
    // Look for the file
    if (file_size(GUILD_DATA + name + ".o") >= 0)
    {
        player_info = restore_map(GUILD_DATA + name);
    }

    // Add the value to the cache
    cached_player_info[name] = player_info;
    return player_info;
}

/* 
 * Function:    query_player_property
 * Description: Generic function to return values from the
 *              manager mapping. This will be used by all
 *              customized getters
 */
public mixed
query_player_property(mixed player, string prop)
{
    mapping player_info = load_player_info(player);
    
    return player_info[prop];    
}

/*
 * Function:    set_player_property
 * Description: Generic function to set the values for a player in
 *              the manager mapping. This will be used by all customized
 *              setters
 */
public string
set_player_property(mixed player, string prop, mixed value)
{
    mapping player_info = load_player_info(player);
    string name = get_id(player);
    
    if (value)
    {
        player_info[prop] = value;
    }
    else
    {
        m_delkey(player_info, prop);
    }
    
    cached_player_info[name] = player_info;
    save_map(player_info, GUILD_DATA + name);    
    return name;
}



/*=====================
 * MEMBERSHIP FUNCTIONS
 ======================*/
public void
add_member(mixed player)
{
    string player_name = set_player_property(player, "is_member", 1);
    send_debug_message("Saurians", capitalize(player_name)
        + " has joined the guild.", EVENT_LOG);
}

public int
query_is_member(mixed player)
{
    if(!stringp(player))
    {
       if (player->query_npc())
       {
           // NPCs are members if they possess the shadow
           return (player->query_guild_name_race() == GUILD_NAME_RACE);
       }
    }
    
    return query_player_property(player, "is_member");
}

public void
remove_member(mixed player)
{
    string player_name = set_player_property(player, "is_member", 0);
    send_debug_message("Saurians", capitalize(player_name)
        + " has left the guild.", EVENT_LOG);    
}


public string *
query_members()
{
    string * files = get_dir(GUILD_DATA);
    string * members = ({ });
    
    foreach (string file : files)
    {
        if (!wildmatch("*.o", file))
        {
            continue;
        }
        
        string name = file[..-3];
        if (query_is_member(name))
        {
            members += ({ name });
        }
    }
    
    return members;
}


/*======================================
 * TITLES AND SURNAMES
 =======================================*/

public void
set_saurian_surname(object player, string surname)
{
    set_player_property(player, "saurian_surname", surname);
}

public string
query_saurian_surname(mixed player)
{
    return query_player_property(player, "saurian_surname");

}

public void
remove_saurian_surname(object player)
{
    set_player_property(player, "saurian_surname", 0);
}

public void
set_saurian_location(object player, string location)
{
    set_player_property(player, "saurian_location", location);
}

public string
query_saurian_location(mixed player)
{ 
    return query_player_property(player, "saurian_location");
}

public void
remove_saurian_location(object player)
{
    set_player_property(player, "saurian_location", 0);
}

