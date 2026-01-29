/* 
 * Order of the Stars Master Object
 *
 * This manager will take care of the member data. It will only return info
 * for real players, not npcs.
 *
 * Created by Arman April 2017
 */

#pragma strict_types

#include <files.h>
#include <ss_types.h>
#include <const.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"
#include CLOCKH

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
public mapping      cached_player_info = ([ ]);
public mapping      cached_council_info = ([ ]);

#define EVENT_LOG (OOTS_LOGS + "events")
 
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
    if (file_size(OOTS_DATA + name + ".o") >= 0)
    {
        player_info = restore_map(OOTS_DATA + name);
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
    save_map(player_info, OOTS_DATA + name);    
    return name;
}



/*=====================
 * MEMBERSHIP FUNCTIONS
 ======================*/
public void
add_member(mixed player)
{
    string player_name = set_player_property(player, "is_member", 1);
    send_debug_message("oots", capitalize(player_name)
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
           return (player->query_guild_name_lay() == GUILD_NAME);
       }
    }
    
    return query_player_property(player, "is_member");
}

public void
remove_member(mixed player)
{
    string player_name = set_player_property(player, "is_member", 0);
    send_debug_message("oots", capitalize(player_name)
        + " has left the guild.", EVENT_LOG);    
}


public string *
query_members()
{
    string * files = get_dir(OOTS_DATA);
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

/* Removing linkdead people from the list... otherwise add following to 
   the object all_players above... 
        + filter(all_inventory(find_object("/d/Genesis/obj/statue")), living);
*/

    list = filter(all_players, &operator(==)(GUILD_NAME) @
        &->query_guild_name_lay());
    list = filter(list, &can_see_in_alist(, for_obj));
    
    return list;
}

/*======================================
 * TITLES AND GOD WORSHIPPED SETTING
 =======================================*/

public void
set_oots_god(object player, string god)
{
    set_player_property(player, "oots_god", god);
}

public string
query_oots_god(mixed player)
{    
    string god = query_player_property(player, "oots_god");
    switch (god)
    {
    case "Mishakal":
    case "Paladine":
    case "Kiri-Jolith":
    case "Branchala":
    case "Majere":
    case "Habbakuk":
        return god;
    }    
    return 0;
}

public void
remove_oots_god(object player)
{
    set_player_property(player, "oots_god", 0);
}


/*======================================
 * TASKS AND SPELL ACQUISITION FUNCTIONS
 =======================================*/

public int
query_scribed_spell(object player, string spell_scribed)
{
    return query_player_property(player, spell_scribed);
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
    send_debug_message("sohm", capitalize(player_name)
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
    send_debug_message("sohm", capitalize(player_name)
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

// Revelation functions

public mapping
query_oots_revelations(object player)
{ 
    mixed revelations = query_player_property(player, "oots_revelations");
    
    if (!mappingp(revelations))
        revelations = ([ ]);
    
    return revelations;
}

public void
add_oots_revelations(object player, string name, string rev)
{
    mapping revelations = query_oots_revelations(player);
    
    if (!m_sizeof(revelations) || !member_array(name, m_indexes(revelations)) > -1)
        revelations += ([ name : rev ]);
    
    set_player_property(player, "oots_revelations", revelations);
}

public void 
remove_oots_revelations(object player, string name)
{
    mapping revelations = query_oots_revelations(player);
    
    if (m_sizeof(revelations) && member_array(name, m_indexes(revelations)) > -1)
        m_delkey(revelations, name);
    
    set_player_property(player, "oots_revelations", revelations);
}

public void 
remove_oots_all_revelations(object player)
{
    mapping revelations = query_oots_revelations(player);
    
    if (mappingp(revelations))
        revelations = ([ ]);
    
    set_player_property(player, "oots_revelations", revelations);
}

