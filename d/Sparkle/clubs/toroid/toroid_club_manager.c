/* 
 * Fishing Functionality Master Object
 *
 * This manager will take care of angler data. It will only return info
 * for real players, not npcs.
 *
 * Fishing code found in /d/Krynn/common/fishing/
 *
 * Created by Arman May 2021
 */

#pragma strict_types

#include <files.h>
#include <ss_types.h>
#include <const.h>
#include "fishing.h"
#include "/d/Krynn/common/defs.h"
#include CLOCKH

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
public mapping      cached_player_info = ([ ]);
public mapping      cached_fishing_info = ([ ]);

#define FISHING_LOG (FISH_LOG + "events")

int * top_ten = ({ "one", "two", "three", "four", "five", "six",
                   "seven", "eight", "nine", "ten" });

int * top_three = ({ "one", "two", "three" });
 
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
    if (file_size(FISH_DATA + name + ".o") >= 0)
    {
        player_info = restore_map(FISH_DATA + name);
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
    save_map(player_info, FISH_DATA + name);    
    return name;
}

/*===========================
 * FISHING SAVING FUNCTIONS
 ============================*/

/* 
 * Function:    load_fishing_info
 * Description: This loads the fishing info from their specific file
 *              and returns the mapping of it.
 */
public mapping
load_fishing_info()
{
    mapping fishing_info;    
        
    fishing_info = ([ ]);
        
    // Look for the file
    if (file_size(FISH_DATA + "krynn_fishing.o") >= 0)
    {
        fishing_info = restore_map(FISH_DATA + "krynn_fishing");
    }

    // Add the value to the cache
    cached_fishing_info["krynn_fishing"] = fishing_info;
    return fishing_info;
}

/* 
 * Function:    query_fishing_property
 * Description: Generic function to return values from the
 *              manager mapping. This will be used by all
 *              customized getters
 */
public mixed
query_fishing_property(string prop)
{
    mapping fishing_info = load_fishing_info();
    
    return fishing_info[prop];    
}

/*
 * Function:    set_fishing_property
 * Description: Generic function to set the values in
 *              the manager mapping. This will be used by all customized
 *              setters
 */
public string
set_fishing_property(string prop, mixed value)
{
    mapping fishing_info = load_fishing_info();
    
    if (value)
    {
        fishing_info[prop] = value;
    }
    else
    {
        m_delkey(fishing_info, prop);
    }
    
    cached_fishing_info["krynn_fishing"] = fishing_info;
    save_map(fishing_info, FISH_DATA + "krynn_fishing");    
    return "krynn_fishing";
}


/*=====================
 * LEADERBOARD FUNCTIONS
 ======================*/

public void
add_leaderboard_fish_caught(mixed player, string fish_desc, int weight)
{
    if(sizeof(explode(fish_desc, " ")) > 1)
        return;

    mapping list = query_fishing_property(fish_desc + "_fish_caught");

    if (!m_sizeof(list))
    {
        // FISHING_DEBUG("List size: " +m_sizeof(list));
        list = ([ "one" : ({ player, weight }) ]);
    }
    else if (member_array("one", m_indexes(list)) == -1)
    {
        // FISHING_DEBUG("No fish_desc detected");
        list += ([ "one" : ({ player, weight }) ]);
    }
    else if (m_sizeof(list) < 10)
    {
        // FISHING_DEBUG("List size: " +m_sizeof(list));
        list += ([ top_ten[m_sizeof(list)] : ({ player, weight }) ]);
    }
    else
    {
        string new_rank = "one";
        mixed * lowest_weight = list[new_rank];
        object new_player = lowest_weight[0];
        int new_weight = lowest_weight[1];

        foreach(string rank, mixed * fish_stats: list)
        {
            new_player = lowest_weight[0];
            new_weight = lowest_weight[1];
            // FISHING_DEBUG("Lowest weight: " +lowest_weight[1]);

            if (fish_stats[1] < new_weight)
            {
                lowest_weight = list[rank];
                new_rank = rank;
            }
        }

        // FISHING_DEBUG("Lowest weight: " +lowest_weight[1]+ ", new weight: "+weight);
            
        if(lowest_weight[1] < weight)
            list += ([ new_rank : ({ player, weight }) ]);
    }

    set_fishing_property(fish_desc +"_fish_caught", list);
}

public mapping
query_leaderboard_fish_caught(string fish_desc)
{ 
    mapping list = query_fishing_property(fish_desc + "_fish_caught");
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}


public void
add_club_trophy(mixed player, string fish_desc, int weight)
{
    mapping list = query_fishing_property("club_trophy");

    if (!m_sizeof(list))
    {
        // FISHING_DEBUG("List size: " +m_sizeof(list));
        list = ([ "one" : ({ player, fish_desc, weight }) ]);
    }
    else if (member_array("one", m_indexes(list)) == -1)
    {
        // FISHING_DEBUG("No fish_desc detected");
        list += ([ "one" : ({ player, fish_desc, weight }) ]);
    }
    else if (m_sizeof(list) < 3)
    {
        // FISHING_DEBUG("List size: " +m_sizeof(list));
        list += ([ top_three[m_sizeof(list)] : ({ player, fish_desc, weight }) ]);
    }
    else
    {
        string new_rank = "one";
        mixed * lowest_weight = list[new_rank];
        mixed new_player = lowest_weight[0];
        string new_fish = lowest_weight[1];
        int new_weight = lowest_weight[2];

        foreach(string rank, mixed * fish_stats: list)
        {
            new_player = lowest_weight[0];
            new_fish = lowest_weight[1];
            new_weight = lowest_weight[2];
            // FISHING_DEBUG("Lowest weight: " +lowest_weight[2]);

            if (fish_stats[2] < new_weight)
            {
                lowest_weight = list[rank];
                new_rank = rank;
            }
        }

        // FISHING_DEBUG("Lowest weight: " +lowest_weight[2]+ ", new weight: "+weight);
            
        if(lowest_weight[2] < weight)
            list += ([ new_rank : ({ player, fish_desc, weight }) ]);
    }

    set_fishing_property("club_trophy", list);
}

public mapping
query_club_trophy()
{ 
    mapping list = query_fishing_property("club_trophy");
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}

public void
clear_club_trophy()
{ 
    mapping list = ([ ]);
    
    set_fishing_property("club_trophy", list);
}


/*===========================
 * FISHING FUNCTIONS
 ============================*/

// player_fish_caught consists of fish description, fish weight,
// and maximum weight for the fish caught, and number of fish caught

public mapping
query_player_fish_caught(mixed player)
{ 
    mixed list = query_player_property(player, "player_fish_caught");
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}

public void
add_player_fish_caught(mixed player, string fish_desc, int weight)
{
    int max_weight, num_caught, * fishing_stats;
    mixed *a;
    string fish_map_name;

    mapping list = query_player_property(player, "player_fish_caught");

    if (!m_sizeof(list))
    {
        num_caught = 1;
        max_weight = weight;
        list = ([ fish_desc : ({ max_weight, num_caught }) ]);
    }
    else if (member_array(fish_desc, m_indexes(list)) == -1)
    {
        num_caught = 1;
        max_weight = weight;
        list += ([ fish_desc : ({ max_weight, num_caught }) ]);
    }
    else
    {
        fishing_stats = list[fish_desc];
        max_weight = max(weight, fishing_stats[0]);
        num_caught = fishing_stats[1] + 1;
        list += ([ fish_desc : ({ max_weight, num_caught }) ]);
    }

    a = explode(fish_desc, " ");
    fish_map_name = a[0] + "_" + a[1];

    add_leaderboard_fish_caught(player->query_real_name(), fish_map_name, weight);

    set_player_property(player, "player_fish_caught", list);
}

public int
query_new_max_weight_fish(mixed player, string fish, int weight)
{
    mapping list = query_player_fish_caught(player);

    if (!m_sizeof(list))
    {
        return 1;
    }

    if (member_array(fish, m_indexes(list)) == -1)
    {
        return 1;
    }

    int * fish_stats = list[fish];
    int current_max = fish_stats[0];

    if (weight > current_max)
        return 1;
    else
        return 0;
}

public int
query_max_weight_fish(mixed player, string fish)
{
    mapping list = query_player_fish_caught(player);

    if (!m_sizeof(list))
    {
        return 0;
    }

    if (member_array(fish, m_indexes(list)) == -1)
    {
        return 0;
    }

    int * fish_stats = list[fish];
    int current_max = fish_stats[0];

    return current_max;
}

public int
query_num_caught_fish(mixed player, string fish)
{
    mapping list = query_player_fish_caught(player);

    if (!m_sizeof(list))
    {
        return 0;
    }

    if (member_array(fish, m_indexes(list)) == -1)
    {
        return 0;
    }

    int * fish_stats = list[fish];
    int current_num = fish_stats[1];

    return current_num;
}

/*=====================
 * FISHING EXPERIENCE
 ======================*/

// General experience through fishing is recorded here.

public int
query_fishing_experience(mixed player)
{    
    return query_player_property(player, "fishing_experience");
}

public void
add_fishing_experience(mixed player, int xp)
{
    int experience = query_fishing_experience(player) + xp;

    set_player_property(player, "fishing_experience", experience);
}


/*=====================
 * MEMBERSHIP FUNCTIONS
 ======================*/
public void
add_member(mixed player)
{
    string player_name = set_player_property(player, "is_member", 1);
    send_debug_message("angler", capitalize(player_name)
        + " has become an angler.", FISHING_LOG);
}

public int
query_is_member(mixed player)
{    
    return query_player_property(player, "is_member");
}

public void
remove_member(mixed player)
{
    string player_name = set_player_property(player, "is_member", 0);
    send_debug_message("angler", capitalize(player_name)
        + " is no longer an angler.", FISHING_LOG);    
}


public string *
query_members()
{
    string * files = get_dir(FISH_DATA);
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
