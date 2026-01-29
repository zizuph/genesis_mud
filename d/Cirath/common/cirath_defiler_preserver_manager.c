/* 
 * Cirath Defiler-Preserver Magic Manager Object
 *
 * This manager will take care of participants data. It will only return info
 * for real players, not npcs.
 *
 * Created by Arman for Meton, May 2020 
 */

#pragma strict_types

#include <files.h>
#include <ss_types.h>
#include <const.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
public mapping      cached_player_info = ([ ]);
public mapping      cached_war_info = ([ ]);

#define EVENT_LOG ("/d/Cirath/log/magic_events")
#define CLUBDATA  ("/d/Cirath/common/magic_player_data/")

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
    if (file_size(CLUBDATA + name + ".o") >= 0)
    {
        player_info = restore_map(CLUBDATA + name);
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
    save_map(player_info, CLUBDATA + name);    
    return name;
}


/*============================
 * DEFILER/PRESERVER FUNCTIONS
 ==============================*/

public int
query_defiler_casts(mixed player)
{
    return query_player_property(player, "defiler_casts");
}

public void
add_defiler_casts(mixed player, int value)
{
    int defiler_value = query_defiler_casts(player) + value;

    string player_name = set_player_property(player, "defiler_casts", defiler_value);
}

public void
set_defiler_casts(mixed player, int value)
{
    string player_name = set_player_property(player, "defiler_casts", value);
}

public int
query_is_preserver(mixed player)
{
    int defiler_value = query_defiler_casts(player);
    
    if(defiler_value > 0)
        return 1;
    else
        return 0;
}

public int
query_is_defiler(mixed player)
{
    int defiler_value = query_defiler_casts(player);
    
    if(defiler_value < 0)
        return 1;
    else
        return 0;
}


public string *
query_defilers()
{
    string * files = get_dir(CLUBDATA);
    string * members = ({ });
    
    foreach (string file : files)
    {
        if (!wildmatch("*.o", file))
        {
            continue;
        }
        
        string name = file[..-3];
        if (query_is_defiler(name))
        {
            members += ({ name });
        }
    }    
    return members;
}

public string *
query_preservers()
{
    string * files = get_dir(CLUBDATA);
    string * members = ({ });
    
    foreach (string file : files)
    {
        if (!wildmatch("*.o", file))
        {
            continue;
        }
        
        string name = file[..-3];
        if (query_is_preserver(name))
        {
            members += ({ name });
        }
    }    
    return members;
}
