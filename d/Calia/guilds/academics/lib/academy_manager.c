/* 
 * Academy Master Object
 *
 * This manager will take care of the member data. It will only return info
 * for real players, not npcs.
 *
 * Created by Petros, September 2009
 */

#pragma strict_types

#include <files.h>
#include <ss_types.h>
#include "defs.h"

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
public mapping      cached_player_info = ([ ]);

#define EVENT_LOG (ACADEMIC_LOGS + "events")

public void purge();

/*
 * Things that the Academy Manager Keeps track of:
 *
 * is_member                    - flag indicates membership in the guild
 * primary_element              - which element Academic is majoring in
 * acquired_fire_spell          - can cast fire spell (light)
 * acquired_water_spell         - can cast water spell (ice shards)
 * acquired_elemental_spell     - can cast elemental spell (cheiropoto)
 * acquired_earth_spell         - can cast earth spell (stoneskin)
 * completed_task_1             - completed first task
 * completed_task_2             - completed second task
 * completed_task_3             - completed third task
 * completed_task_4             - completed fourth task
 * practice_level               - how much practice they have in casting.
 * casting_banned               - stores when casting ban ends
 * join_restricted              - stores when join restriction ends
 * leftovers_collected          - number of leftovers collected for task 1
 * gems_collected               - number of gems collected for task 1
 * herbs_collected              - number of herbs collected for task 2
 * potion_parts_collected       - parts of potion that's been collected
 * tell_history                 - last 10 numastomo tells received
 */
 
// The create function is called for every object. We mask it here
// to do some basic initialization for the handler
void
create()
{
    setuid();
    seteuid(getuid());

    set_alarm(6400.0, 86400.0, &purge());
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
    if (file_size(ACADEMIC_DATA + name + ".o") >= 0)
    {
        player_info = restore_map(ACADEMIC_DATA + name);
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
    save_map(player_info, ACADEMIC_DATA + name);    
    return name;
}

/*=====================
 * MEMBERSHIP FUNCTIONS
 ======================*/
public void
add_member(mixed player)
{
    string player_name = set_player_property(player, "is_member", 1);
    send_debug_message("academic", capitalize(player_name)
        + " has joined the guild.", EVENT_LOG);
}

public int
query_is_member(mixed player)
{
    if (objectp(player) && player->query_npc())
    {
        // NPCs are members if they possess the shadow
        return (player->query_guild_name_lay() == GUILD_NAME);
    }
    
    return query_player_property(player, "is_member");
}

public varargs void
remove_member(mixed player)
{
    string player_name = set_player_property(player, "is_member", 0);
    send_debug_message("academic", capitalize(player_name) + " has left the guild.", EVENT_LOG);    
}

public string *
query_members()
{
    string * files = get_dir(ACADEMIC_DATA);
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

public void
purge()
{
    foreach (string file: get_dir(ACADEMIC_DATA))
    {
        if (!wildmatch("*.o", file))
            continue;

        string name = file[..-3];

        if (SECURITY->exist_player(name))
            continue;

        send_debug_message("academic", capitalize(name) + " has been purged from the guild.", EVENT_LOG);
        rm(ACADEMIC_DATA + file);
    }
}

public int
can_see_in_alist(object target, object for_obj)
{
    if (for_obj->query_wiz_level())
    {
        // Wizards can see everyone
        return 1;
    }
    
    if (for_obj == target)
    {
        // Can always see self on list
        return 1;
    }
    
    if (!target->query_wiz_level())
    {
        // Not a wizard. If target is a junior, then cannot be seen by others
        if (wildmatch("*jr", target->query_real_name()))
        {
            return 0;
        }
        return 1;
    }
    
    if (target->query_invis() >= 100
        || !target->query_prop(LIVE_I_ALWAYSKNOWN))
    {
        // Invisible and unknown wizards don't show up on the who
        // list, and they shouldn't show up in alist
        return 0;
    }
    
    return 1;
}

public object *
query_awake_members(object for_obj = this_player())
{
    mixed list;
    object * all_players = users() 
        + filter(all_inventory(find_object("/d/Genesis/obj/statue")), living);
    list = filter(all_players, &operator(==)(GUILD_NAME) @
        &->query_guild_name_lay());
    list = filter(list, &can_see_in_alist(, for_obj));
    
    return list;
}

/*==========================
 * PRIMARY ELEMENT FUNCTIONS
 ===========================*/
public void
set_primary_element(object player, string element)
{
    set_player_property(player, "primary_element", element);
}

/*
 * Function:    query_primary_element
 * Description: This returns the string of the primary element that the
 *              Academic has chosen. It will return 0 if nothing has been
 *              chosen.
 */
public string
query_primary_element(object player)
{
    if (player->query_npc())
    {
        if (!player->query_prop("_npc_primary_element"))
        {
            return "fire";
        }
        return player->query_prop("_npc_primary_element");
    }
    
    string element = query_player_property(player, "primary_element");
    switch (element)
    {
    case "fire":
    case "water":
    case "air":
    case "earth":
        return element;
    }
    
    return 0;
}

/*
 * Function:    query_primary_element_skillnum
 * Description: This returns the element skillnum for the chosen primary
 *              element. It will return 0 if none has been selected.
 */
public int
query_primary_element_skillnum(object player)
{
    string element = query_primary_element(player);
    switch (element)
    {
    case "fire":
        return SS_ELEMENT_FIRE;
        
    case "water":
        return SS_ELEMENT_WATER;
        
    case "air":
        return SS_ELEMENT_AIR;
    
    case "earth":
        return SS_ELEMENT_EARTH;
    }

    return 0;    
}

/*==========================
 * PRACTICE LEVEL FUNCTIONS
 ===========================*/
public int
query_practice_level(object player)
{
    return query_player_property(player, "practice_level");
}

public void
set_practice_level(object player, int level)
{
    set_player_property(player, "practice_level", level);
}

public void
add_practice_level(object player, int amount)
{
    int level = query_practice_level(player);
    set_practice_level(player, level + amount);
}

/*======================================
 * TASKS AND SPELL ACQUISITION FUNCTIONS
 =======================================*/

public void
set_acquired_fire_spell(object player)
{
    string player_name = set_player_property(player, "acquired_fire_spell", time());
    send_debug_message("academic", capitalize(player_name)
        + " has acquired the fire spell.", EVENT_LOG);    
}

public void
set_unacquired_fire_spell(object player)
{
    set_player_property(player, "acquired_fire_spell", 0);
}

public int
acquired_fire_spell(object player)
{
    return query_player_property(player, "acquired_fire_spell");
}

public void
set_acquired_water_spell(object player)
{
    string player_name = set_player_property(player, "acquired_water_spell", time());
    send_debug_message("academic", capitalize(player_name)
        + " has acquired the water spell.", EVENT_LOG);       
}

public void
set_unacquired_water_spell(object player)
{
    set_player_property(player, "acquired_water_spell", 0);
}

public int
acquired_water_spell(object player)
{
    return query_player_property(player, "acquired_water_spell");
}

public void
set_acquired_earth_spell(object player)
{
    string player_name = set_player_property(player, "acquired_earth_spell", time());
    send_debug_message("academic", capitalize(player_name)
        + " has acquired the earth spell.", EVENT_LOG);    
}

public void
set_unacquired_earth_spell(object player)
{
    set_player_property(player, "acquired_earth_spell", 0);
}

public int
acquired_earth_spell(object player)
{
    return query_player_property(player, "acquired_earth_spell");
}

public void
set_acquired_elemental_spell(object player)
{
    string player_name = set_player_property(player, "acquired_elemental_spell", time());
    send_debug_message("academic", capitalize(player_name)
        + " has acquired the elemental spell.", EVENT_LOG);       
}

public void
set_unacquired_elemental_spell(object player)
{
    set_player_property(player, "acquired_elemental_spell", 0);
}

public int
acquired_elemental_spell(object player)
{
    return query_player_property(player, "acquired_elemental_spell");
}

public void
set_completed_task_1(object player)
{
    string player_name = set_player_property(player, "completed_task_1", time());
    send_debug_message("academic", capitalize(player_name)
        + " has completed task 1.", EVENT_LOG);    
}

public void
set_uncompleted_task_1(object player)
{
    set_player_property(player, "completed_task_1", 0);
}

public int
query_completed_task_1(object player)
{
    return query_player_property(player, "completed_task_1");
}

public void
set_completed_task_2(object player)
{
    string player_name = set_player_property(player, "completed_task_2", time());
    send_debug_message("academic", capitalize(player_name)
        + " has completed task 2.", EVENT_LOG);    
}

public void
set_uncompleted_task_2(object player)
{
    set_player_property(player, "completed_task_2", 0);
}

public int
query_completed_task_2(object player)
{
    return query_player_property(player, "completed_task_2");
}

public void
set_completed_task_3(object player)
{
    string player_name = set_player_property(player, "completed_task_3", time());
    send_debug_message("academic", capitalize(player_name)
        + " has completed task 3.", EVENT_LOG);    
}

public void
set_uncompleted_task_3(object player)
{
    set_player_property(player, "completed_task_3", 0);
}

public int
query_completed_task_3(object player)
{
    return query_player_property(player, "completed_task_3");
}

public void
set_completed_task_4(object player)
{
    string player_name = set_player_property(player, "completed_task_4", time());
    send_debug_message("academic", capitalize(player_name)
        + " has completed task 4.", EVENT_LOG);    
}

public void
set_uncompleted_task_4(object player)
{
    set_player_property(player, "completed_task_4", 0);
}

public int
query_completed_task_4(object player)
{
    return query_player_property(player, "completed_task_4");
}

/*===========================================
 * CASTING BAN AND JOIN RESTRICTION FUNCTIONS
 ============================================*/

public void
add_casting_ban(object player)
{
    // By default, banned for 24 hours. Each offense adds to the ban.
    int last_ban = query_player_property(player, "casting_banned");
    int new_ban;
    if (last_ban <= time())
    {
        new_ban = time() + 86400;
    }
    else
    {
        new_ban = last_ban + 86400;
    }
    string player_name = set_player_property(player, "casting_banned", new_ban);
    send_debug_message("academic", capitalize(player_name)
        + " has been banned from casting until " + ctime(new_ban), EVENT_LOG);    
}

public int
is_casting_banned(object player)
{
    int ban_expiration = query_player_property(player, "casting_banned");
    if (ban_expiration >= time())
    {
        return 1;
    }
    
    return 0;
}

public void
remove_casting_banned(object player)
{
    set_player_property(player, "casting_banned", 0);
}

public void
add_join_restricted(object player)
{
    // By default, restricts for 3 days
    int last_ban = query_player_property(player, "join_restricted");
    int new_ban;
    if (last_ban <= time())
    {
        new_ban = time() + (3 * 86400);
    }
    else
    {
        new_ban = last_ban + (3 * 86400);
    }
    string player_name = set_player_property(player, "join_restricted", new_ban);
    send_debug_message("academic", capitalize(player_name)
        + " has been restricted from joining until " + ctime(new_ban), EVENT_LOG);        
}

public int
is_join_restricted(object player)
{
    int ban_expiration = query_player_property(player, "join_restricted");
    if (ban_expiration >= time())
    {
        return 1;
    }
    
    return 0;
}

public void
remove_join_restricted(object player)
{
    set_player_property(player, "join_restricted", 0);
}

// TASK TRACKING FUNCTIONS

public int
query_leftovers_collected(object player)
{
    return query_player_property(player, "leftovers_collected");
}

public void
set_leftovers_collected(object player, int amount)
{
    set_player_property(player, "leftovers_collected", amount);
}

public int
query_gems_collected(object player)
{
    return query_player_property(player, "gems_collected");
}

public void
set_gems_collected(object player, int amount)
{
    set_player_property(player, "gems_collected", amount);
}

public int
query_herbs_collected(object player)
{
    return query_player_property(player, "herbs_collected");
}

public void
set_herbs_collected(object player, int amount)
{
    set_player_property(player, "herbs_collected", amount);
}

public string *
query_potion_parts_collected(object player)
{
    string * parts = query_player_property(player, "potion_parts_collected");
    if (!parts)
    {
        return ({ });
    }
    return parts;
}

public void
set_potion_parts_collected(object player, string * parts)
{
    set_player_property(player, "potion_parts_collected", parts);
}

// Tell History Functions

public mixed
query_tell_history(object player)
{
    mixed history = query_player_property(player, "tell_history");
    history = filter(history, pointerp);
    if (!sizeof(history))
    {
        return ({ });
    }
    return history;
}

public void
add_tell_message(object player, string sender, string message)
{
    mixed history = query_player_property(player, "tell_history");
    if (!pointerp(history))
    {
        history = ({ });
    }
    history = filter(history, not @ stringp);
    history += ({ ({ sender, message }) });
    if (sizeof(history) > 10)
    {
        history = history[-10..];
    }
    set_player_property(player, "tell_history", history);
}

