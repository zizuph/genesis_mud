/* 
 * Heralds Master Object
 *
 * This manager will take care of the member data. It will only return info
 * for real players, not npcs.
 *
 * Created by Arman May 2018
 */

#pragma strict_types

#include <files.h>
#include <ss_types.h>
#include <const.h>
#include "../herald.h"

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
public mapping      cached_player_info = ([ ]);
public mapping      cached_council_info = ([ ]);

#define EVENT_LOG   (HERALD_LOGS + "events")
#define CORRUPTION_LOG   (HERALD_LOGS + "corruption")
 
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
    if (file_size(HERALD_DATA + name + ".o") >= 0)
    {
        player_info = restore_map(HERALD_DATA + name);
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
    save_map(player_info, HERALD_DATA + name);    
    return name;
}



/*=====================
 * MEMBERSHIP FUNCTIONS
 ======================*/
public void
add_member(mixed player)
{
    string player_name = set_player_property(player, "is_member", 1);
    send_debug_message("heralds", capitalize(player_name)
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
           return (player->query_guild_name_lay() == HERALD_GUILD_NAME);
       }
    }
    
    return query_player_property(player, "is_member");
}

public void
remove_member(mixed player)
{
    string player_name = set_player_property(player, "is_member", 0);
    send_debug_message("heralds", capitalize(player_name)
        + " has left the guild.", EVENT_LOG);    
}


public string *
query_members()
{
    string * files = get_dir(HERALD_DATA);
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
    object * all_players = users();

    list = filter(all_players, &operator(==)(HERALD_GUILD_NAME) @
        &->query_guild_name_lay());
    list = filter(list, &can_see_in_alist(, for_obj));
    
    return list;
}

/*======================================
 *        GUILD SPECIFIC SETTINGS
 =======================================*/

// Corruption functions

public void
set_herald_corruption(object player, int corrupt)
{
    set_player_property(player, "herald_corruption", corrupt);
}

public int
query_herald_corruption(mixed player)
{    
    int corrupt = query_player_property(player, "herald_corruption");
    
    return corrupt;
}

public void
add_herald_corruption(object player, int corrupt)
{
    int new_corrupt = min(100, (query_herald_corruption(player) + corrupt));

    send_debug_message("heralds", capitalize(player->query_real_name())
        + " corruption increased by " +corrupt+ ".", CORRUPTION_LOG);

    set_player_property(player, "herald_corruption", new_corrupt);
}

public void
reduce_herald_corruption(object player, int corrupt)
{
    int new_corrupt = max(0, (query_herald_corruption(player) - corrupt));

    send_debug_message("heralds", capitalize(player->query_real_name())
        + " corruption decreased by " +corrupt+ ".", CORRUPTION_LOG);

    set_player_property(player, "herald_corruption", new_corrupt);
}

public void
remove_herald_corruption(object player)
{
    set_player_property(player, "herald_corruption", 0);
}

// Dark Lord detection functions - may not need them, but added anyway

public void
set_dark_lord_detection(object player, int detect)
{
    set_player_property(player, "dark_lord_detection", detect);
}

public int
query_dark_lord_detection(mixed player)
{    
    int detect = query_player_property(player, "dark_lord_detection");
    
    return detect;
}

public void
add_dark_lord_detection(object player, int detect)
{
    int new_detect = min(100, (query_dark_lord_detection(player) + detect));

    set_player_property(player, "dark_lord_detection", detect);
}

public void
reduce_dark_lord_detection(object player, int detect)
{
    int new_detect = max(0, (query_dark_lord_detection(player) - detect));

    set_player_property(player, "dark_lord_detection", detect);
}

public void
remove_dark_lord_detection(object player)
{
    set_player_property(player, "dark_lord_detection", 0);
}

// Herald focus functions, impacting spell options
// Options are 0 (no focus), dual (air/water/earth), or singular focus

public void
set_herald_focus(mixed player, string focus)
{
    string player_name = set_player_property(player, "herald_focus", 
        focus);
}

public string
query_herald_focus(mixed player)
{    
    return query_player_property(player, "herald_focus");
}

// Herald maintained spell check to help manage caid restrictions

public int
query_herald_maintained_spells(mixed player)
{
    int spell_no = 0;

    if("/d/Shire/guild/heralds/spells/ondo"->has_spell_object(player))
        spell_no += 1;
    if("/d/Shire/guild/heralds/spells/namotir"->has_spell_object(player))
        spell_no += 1;
    if("/d/Shire/guild/heralds/spells/hortale"->has_spell_object(player))
        spell_no += 1;
    if("/d/Shire/guild/heralds/spells/noleme"->has_spell_object(player))
        spell_no += 1;
    
    return spell_no;
}
