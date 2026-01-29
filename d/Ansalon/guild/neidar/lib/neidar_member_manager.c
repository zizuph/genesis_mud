/* 
 * Neidar Member Manager Object
 *
 * This manager will take care of the member data for the
 * Neidar members.
 *
 * Created by Arman April 2019
 */

#pragma strict_types

#include <files.h>
#include <ss_types.h>
#include <const.h>
#include <std.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/neidar/guild.h"
#include DL_CLOCK

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
public mapping      cached_player_info = ([ ]);
public mapping      cached_member_info = ([ ]);
public mapping      cached_council_info = ([ ]);

#define EVENT_LOG (GUILD_LOG + "events")
 
// Prototypes


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


/*=======================
 * MEMBER-SPECIFIC FUNCTIONS
 ========================*/

/* 
 * Function:    load_member_info
 * Description: This loads the member info from their specific file
 *              and returns the mapping of it.
 */
public mapping
load_member_info()
{
    mapping member_info;    
        
    member_info = ([ ]);
        
    // Look for the file
    if (file_size(GUILD_DATA + "member_info.o") >= 0)
    {
        member_info = restore_map(GUILD_DATA + "member_info");
    }

    // Add the value to the cache
    cached_member_info["member_info"] = member_info;
    return member_info;
}

/* 
 * Function:    query_member_property
 * Description: Generic function to return values from the
 *              manager mapping. This will be used by all
 *              customized getters
 */
public mixed
query_member_property(string prop)
{
    mapping member_info = load_member_info();
    
    return member_info[prop];    
}

/*
 * Function:    set_member_property
 * Description: Generic function to set the values in
 *              the manager mapping. This will be used by all customized
 *              setters
 */
public string
set_member_property(string prop, mixed value)
{
    mapping member_info = load_member_info();
    
    if (value)
    {
        member_info[prop] = value;
    }
    else
    {
        m_delkey(member_info, prop);
    }
    
    cached_member_info["member_info"] = member_info;
    save_map(member_info, GUILD_DATA + "member_info");    
    return "member_info";
}


/* 
 * Function:    load_council_info
 * Description: This loads the council info from their specific file
 *              and returns the mapping of it.
 */
public mapping
load_council_info()
{
    mapping council_info;    
        
    council_info = ([ ]);
        
    // Look for the file
    if (file_size(GUILD_DATA + "elder_council.o") >= 0)
    {
        council_info = restore_map(GUILD_DATA + "elder_council");
    }

    // Add the value to the cache
    cached_council_info["elder_council"] = council_info;
    return council_info;
}

/* 
 * Function:    query_council_property
 * Description: Generic function to return values from the
 *              manager mapping. This will be used by all
 *              customized getters
 */
public mixed
query_council_property(string prop)
{
    mapping council_info = load_council_info();
    
    return council_info[prop];    
}

/*
 * Function:    set_council_property
 * Description: Generic function to set the values for a player in
 *              the manager mapping. This will be used by all customized
 *              setters
 */
public string
set_council_property(string prop, mixed value)
{
    mapping council_info = load_council_info();
    
    if (value)
    {
        council_info[prop] = value;
    }
    else
    {
        m_delkey(council_info, prop);
    }
    
    cached_council_info["elder_council"] = council_info;
    save_map(council_info, GUILD_DATA + "elder_council");    
    return "elder_council";
}


/*=====================
 * LEADERSHIP FUNCTIONS
 ======================*/
public mapping
query_neidar_thane_list()
{ 
    mixed list = query_council_property("neidar_thane_list");
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}

public void
add_neidar_thane_list(string name)
{
    mapping list = query_neidar_thane_list();
    
    if (!m_sizeof(list) || !member_array(name, m_indexes(list)) > -1)
        list += ([ name : 1 ]);
    
    set_council_property("neidar_thane_list", list);
}

public void 
remove_neidar_thane_list(string name)
{
    mapping list = query_neidar_thane_list();
    
    if (m_sizeof(list) && member_array(name, m_indexes(list)) > -1)
        m_delkey(list, name);
    
    set_council_property("neidar_thane_list", list);
}


public mapping
query_neidar_elder_list()
{ 
    mixed list = query_council_property("neidar_elder_list");
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}

public void
add_neidar_elder_list(string name)
{
    mapping list = query_neidar_elder_list();
    
    if (!m_sizeof(list) || !member_array(name, m_indexes(list)) > -1)
        list += ([ name : 1 ]);
    
    set_council_property("neidar_elder_list", list);
}

public void 
remove_neidar_elder_list(string name)
{
    mapping list = query_neidar_elder_list();
    
    if (m_sizeof(list) && member_array(name, m_indexes(list)) > -1)
        m_delkey(list, name);
    
    set_council_property("neidar_elder_list", list);
}

public void
add_thane(mixed player)
{
    if(player->query_npc())
        return;

    string player_name = set_player_property(player, "is_thane", 1);
    add_neidar_thane_list(player_name);

    send_debug_message("neidar", capitalize(player_name)
        + " has become Thane of the Neidar Clan.", EVENT_LOG);
}

public int
query_is_thane(mixed player)
{    
    return query_player_property(player, "is_thane");
}

public void
remove_thane(mixed player)
{
    string player_name = set_player_property(player, "is_thane", 0);
    remove_neidar_thane_list(player_name);

    send_debug_message("neidar", capitalize(player_name)
        + " is no longer Thane of the Neidar Clan.", EVENT_LOG);    
}

public void
add_elder(mixed player)
{
    if(player->query_npc())
        return;

    string player_name = set_player_property(player, "is_elder", 1);
    add_neidar_elder_list(player_name);

    send_debug_message("neidar", capitalize(player_name)
        + " has become an Elder of the Neidar Clan.", EVENT_LOG);
}

public int
query_is_elder(mixed player)
{    
    return query_player_property(player, "is_elder");
}

public void
remove_elder(mixed player)
{
    string player_name = set_player_property(player, "is_elder", 0);
    remove_neidar_elder_list(player_name);

    send_debug_message("neidar", capitalize(player_name)
        + " is no longer an Elder of the Neidar Clan.", EVENT_LOG);    
}

public int
query_elder_bits(object player)
{
    // Both quest bits means they are banished
    if(player->test_bit("Ansalon",3,4) &&
       player->test_bit("Ansalon",3,3))
        return 0;

    // Ansalon bits 3,4 is set for Elders
    if(player->test_bit("Ansalon",3,4))
        return 1;

    return 0;
}

public int
query_thane_bits(object player)
{
    // Both quest bits means they are banished
    if(player->test_bit("Ansalon",3,4) &&
       player->test_bit("Ansalon",3,3))
        return 0;

    // Ansalon bits 3,3 is set for the Thane
    if(player->test_bit("Ansalon",3,3))
        return 1;

    return 0;
}

/*===========================================
 *          DOOMSEEKER FUNCTIONS
 ============================================*/

public mapping
query_neidar_doomseeker_list()
{ 
    mixed list = query_council_property("neidar_doomseeker_list");
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}

public void
add_neidar_doomseeker_list(string name, int guildstat)
{
    mapping list = query_neidar_doomseeker_list();
    
    if (!m_sizeof(list) || !member_array(name, m_indexes(list)) > -1)
        list += ([ name : guildstat ]);
    
    set_council_property("neidar_doomseeker_list", list);
}

public void 
remove_neidar_doomseeker_list(string name)
{
    mapping list = query_neidar_doomseeker_list();
    
    if (m_sizeof(list) && member_array(name, m_indexes(list)) > -1)
        m_delkey(list, name);
    
    set_council_property("neidar_doomseeker_list", list);
}

public void
add_doomseeker(mixed player)
{
    int guildstat = player->query_stat(SS_OCCUP);

    string player_name = set_player_property(player, "is_doomseeker", guildstat);
    add_neidar_doomseeker_list(player_name, guildstat);

    send_debug_message("neidar", capitalize(player_name)
        + " has become a Doomseeker.", EVENT_LOG);
}

public int
query_is_doomseeker(mixed player)
{    
    return query_player_property(player, "is_doomseeker");
}

public void
remove_doomseeker(mixed player)
{
    string player_name = set_player_property(player, "is_doomseeker", 0);
    remove_neidar_doomseeker_list(player_name);

    send_debug_message("neidar", capitalize(player_name)
        + " is no longer a Doomseeker.", EVENT_LOG);    
}

public void
add_doomseeker_killed_by(mixed player, string killer)
{
    int death_time;
    death_time = time();

    string player_name = set_player_property(player, "doomseeker_killed_by", killer);
    set_player_property(player, "doomseeker_time_killed", time);

    send_debug_message("neidar", capitalize(player_name)
        + " was slain by " +killer+ ".", EVENT_LOG);
}

public string
query_doomseeker_killed_by(mixed player)
{    
    return query_player_property(player, "doomseeker_killed_by");
}

public int
query_doomseeker_time_killed(mixed player)
{    
    return query_player_property(player, "doomseeker_time_killed");
}

public void
remove_doomseeker_killed_by(mixed player)
{
    string player_name = set_player_property(player, "doomseeker_killed_by", 0);   
    set_player_property(player, "doomseeker_time_killed", 0);
}

public mapping
query_doomseeker_tree()
{ 
    mixed list = query_council_property("doomseeker_tree");
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}

public void
add_doomseeker_tree(mixed name, int date, string death_details)
{
    mapping list = query_doomseeker_tree();
    
    if (!m_sizeof(list) || !member_array(name, m_indexes(list)) > -1)
        list += ([ name : ({ date, death_details }) ]);

    set_council_property("doomseeker_tree", list);
}

public void 
remove_doomseeker_tree(mixed name)
{
    mapping list = query_doomseeker_tree();
    
    if (m_sizeof(list) && member_array(name, m_indexes(list)) > -1)
        m_delkey(list, name);
    
    set_council_property("doomseeker_tree", list);
}

public void
add_doomseeker_kills(mixed player, int kills)
{
    string player_name = set_player_property(player, "doomseeker_kills", kills);
}

public int
query_doomseeker_kills(mixed player)
{    
    return query_player_property(player, "doomseeker_kills");
}

public void
increase_doomseeker_kills(mixed player)
{
    int kills = query_doomseeker_kills(player) + 1;

    string player_name = set_player_property(player, "doomseeker_kills", kills);
}

public void
remove_doomseeker_kills(mixed player)
{
    string player_name = set_player_property(player, "doomseeker_kills", 0);    
}

public void
add_doomseeker_average(mixed player, int average)
{
    string player_name = set_player_property(player, "doomseeker_average", average);
}

public int
query_doomseeker_average(mixed player)
{    
    return query_player_property(player, "doomseeker_average");
}

public void
increase_doomseeker_average(mixed player, int average)
{
    int kills = query_doomseeker_average(player) + average;

    string player_name = set_player_property(player, "doomseeker_average", kills);
}

public void
remove_doomseeker_average(mixed player)
{
    string player_name = set_player_property(player, "doomseeker_average", 0);    
}


// This records the ratio of the Doomseekers health upon slaying something.
// Allows for an average measure of how often they are fighting hurt when
// divided by total kills.

public void
add_doomseeker_health(mixed player, int ratio)
{
    string player_name = set_player_property(player, "doomseeker_health", ratio);
}

public int
query_doomseeker_health(mixed player)
{    
    return query_player_property(player, "doomseeker_health");
}

public void
increase_doomseeker_health(mixed player, int ratio)
{
    // ratio can be a number between 1 and 100
    ratio = max(1, min(ratio, 100));

    int health = query_doomseeker_health(player) + ratio;

    string player_name = set_player_property(player, "doomseeker_health", health);
}

public void
remove_doomseeker_health(mixed player)
{
    string player_name = set_player_property(player, "doomseeker_health", 0);    
}

public mapping
query_greatest_kill()
{ 
    mapping list = query_council_property("greatest_kill");
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}

public void
add_greatest_kill(mixed name, int stat, string kill_short)
{
    mapping list = query_greatest_kill();
    
    if (!m_sizeof(list) || !member_array(name, m_indexes(list)) > -1)
        list += ([ name : ({ stat, kill_short }) ]);

    set_council_property("greatest_kill", list);
}

public void 
remove_greatest_kill(mixed name)
{
    mapping list = query_greatest_kill();
    
    if (m_sizeof(list) && member_array(name, m_indexes(list)) > -1)
        m_delkey(list, name);
    
    set_council_property("greatest_kill", list);
}


/*===========================================
 *          EXPULSION FUNCTIONS
 ============================================*/

public int
query_exile_bits(object player)
{
    // Both quest bits means they are banished
    if(player->test_bit("Ansalon",3,4) &&
       player->test_bit("Ansalon",3,3))
        return 1;

    return 0;
}

public mapping
query_neidar_exile_list()
{ 
    mixed list = query_council_property("neidar_exile_list");
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}

public void
add_neidar_exile_list(string name)
{
    mapping list = query_neidar_exile_list();
    
    if (!m_sizeof(list) || !member_array(name, m_indexes(list)) > -1)
        list += ([ name : 1 ]);
    
    set_council_property("neidar_exile_list", list);
}

public void 
remove_neidar_exile_list(string name)
{
    mapping list = query_neidar_exile_list();
    
    if (m_sizeof(list) && member_array(name, m_indexes(list)) > -1)
        m_delkey(list, name);
    
    set_council_property("neidar_exile_list", list);
}

public void
add_exile(mixed player)
{
    string player_name = set_player_property(player, "is_exile", 1);
    add_neidar_exile_list(player_name);

    send_debug_message("neidar", capitalize(player_name)
        + " is exiled from the Neidar Clan.", EVENT_LOG);
}

public int
query_is_exile(mixed player)
{    
    return query_player_property(player, "is_exile");
}

public void
remove_exile(mixed player)
{
    string player_name = set_player_property(player, "is_exile", 0);
    remove_neidar_exile_list(player_name);

    send_debug_message("neidar", capitalize(player_name)
        + " is no longer Exiled from the Neidar Clan.", EVENT_LOG);    
}

public mapping
query_neidar_death_mark_list()
{ 
    mixed list = query_council_property("neidar_death_mark_list");
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}

public void
add_neidar_death_mark_list(string name)
{
    mapping list = query_neidar_death_mark_list();
    
    if (!m_sizeof(list) || !member_array(name, m_indexes(list)) > -1)
        list += ([ name : 1 ]);
    
    set_council_property("neidar_death_mark_list", list);
}

public void 
remove_neidar_death_mark_list(string name)
{
    mapping list = query_neidar_death_mark_list();
    
    if (m_sizeof(list) && member_array(name, m_indexes(list)) > -1)
        m_delkey(list, name);
    
    set_council_property("neidar_death_mark_list", list);
}

public void
add_death_mark(mixed player)
{
    string player_name = set_player_property(player, "death_mark", 1);
    add_neidar_death_mark_list(player_name);

    send_debug_message("neidar", capitalize(player_name)
        + " has been death marked for expulsion.", EVENT_LOG);
}

public int
query_death_mark(mixed player)
{    
    return query_player_property(player, "death_mark");
}

public void
remove_death_mark(mixed player)
{
    string player_name = set_player_property(player, "death_mark", 0);
    remove_neidar_death_mark_list(player_name);

    send_debug_message("neidar", capitalize(player_name)
        + " has had their death mark revoked.", EVENT_LOG);    
}

/*===========================================
 *          JOIN RESTRICTION FUNCTIONS
 ============================================*/
public mapping
query_approved_to_join_shieldbearers_list()
{ 
    mixed list = query_council_property("approved_to_join_shieldbearers_list");
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}

public void
add_approved_to_join_shieldbearers_list(string name)
{
    mapping list = query_approved_to_join_shieldbearers_list();
    
    if (!m_sizeof(list) || !member_array(name, m_indexes(list)) > -1)
        list += ([ name : 1 ]);
    
    set_council_property("approved_to_join_shieldbearers_list", list);
}

public void 
remove_approved_to_join_shieldbearers_list(string name)
{
    mapping list = query_approved_to_join_shieldbearers_list();
    
    if (m_sizeof(list) && member_array(name, m_indexes(list)) > -1)
        m_delkey(list, name);
    
    set_council_property("approved_to_join_shieldbearers_list", list);
}

public void
approved_to_join_shieldbearers(mixed player, string elder)
{
    string player_name = set_player_property(player, "join_approved_shieldbearers", 1);
    add_approved_to_join_shieldbearers_list(player_name);
    send_debug_message("neidar", capitalize(player_name)
        + " has been approved to join the Shieldbearers by "+
        capitalize(elder), EVENT_LOG);        
}

public void
unapproved_to_join_shieldbearers(mixed player, string elder)
{
    string player_name = set_player_property(player, "join_approved_shieldbearers", 0);
    remove_approved_to_join_shieldbearers_list(player_name);
    send_debug_message("neidar", capitalize(player_name)
        + " is no longer approved to join the Shieldbearers by "+
        capitalize(elder), EVENT_LOG);        
}

public int
query_is_approved_shieldbearers(mixed player)
{    
    return query_player_property(player, "join_approved_shieldbearers");
}

public mapping
query_approved_to_join_list()
{ 
    mixed list = query_council_property("approved_to_join_list");
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}

public void
add_approved_to_join_list(string name)
{
    mapping list = query_approved_to_join_list();
    
    if (!m_sizeof(list) || !member_array(name, m_indexes(list)) > -1)
        list += ([ name : 1 ]);
    
    set_council_property("approved_to_join_list", list);
}

public void 
remove_approved_to_join_list(string name)
{
    mapping list = query_approved_to_join_list();
    
    if (m_sizeof(list) && member_array(name, m_indexes(list)) > -1)
        m_delkey(list, name);
    
    set_council_property("approved_to_join_list", list);
}

public void
approved_to_join_neidar(mixed player, string elder)
{
    string player_name = set_player_property(player, "join_approved", 1);
    add_approved_to_join_list(player_name);
    send_debug_message("neidar", capitalize(player_name)
        + " has been approved to join the Neidar Clan by "+
        capitalize(elder), EVENT_LOG);        
}

public void
unapproved_to_join_neidar(mixed player, string elder)
{
    string player_name = set_player_property(player, "join_approved", 0);
    remove_approved_to_join_list(player_name);
    send_debug_message("neidar", capitalize(player_name)
        + " is no longer approved to join the Neidar Clan by "+
        capitalize(elder), EVENT_LOG);        
}

public int
query_is_approved(mixed player)
{    
    return query_player_property(player, "join_approved");
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
    send_debug_message("neidar", capitalize(player_name)
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

/*=====================
 * MEMBERSHIP FUNCTIONS
 ======================*/
// Mapping to track Neidar Clan membership

public mapping
query_neidar_members_list()
{ 
    mixed list = query_council_property("neidar_members_list");
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}

public void
add_neidar_members_list(string name)
{
    mapping list = query_neidar_members_list();
    
    if (!m_sizeof(list) || !member_array(name, m_indexes(list)) > -1)
        list += ([ name : 1 ]);
    
    set_council_property("neidar_members_list", list);
}

public void 
remove_neidar_members_list(string name)
{
    mapping list = query_neidar_members_list();
    
    if (m_sizeof(list) && member_array(name, m_indexes(list)) > -1)
        m_delkey(list, name);
    
    set_council_property("neidar_members_list", list);
}

public void
add_member(mixed player)
{
    if(player->query_npc())
        return;

    string player_name = set_player_property(player, "is_member", 1);
    add_neidar_members_list(player_name);

    set_player_property(player, "join_approved", 0);
    remove_approved_to_join_list(player_name);

    send_debug_message("neidar", capitalize(player_name)
        + " has joined the Neidar Clan.", EVENT_LOG);
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
    set_player_property(player_name, "is_elder", 0);
    set_player_property(player_name, "is_thane", 0);
    set_player_property(player_name, "is_doomseeker", 0);
    remove_neidar_thane_list(player_name);
    remove_neidar_elder_list(player_name);
    remove_neidar_doomseeker_list(player_name);
    remove_neidar_members_list(player_name);
    remove_doomseeker_killed_by(player_name);

    send_debug_message("neidar", capitalize(player_name)
        + " has left the Neidar Clan.", EVENT_LOG);    
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

public int
last_member_login(string player)
{
    player = lower_case(player);

    if(!query_is_member(player))
        return 0;
    if(file_time(PLAYER_FILE(player) + ".o"))
        return file_time(PLAYER_FILE(player) + ".o");

    return 0;
}

/*==========================
 * FRIENDSHIP RUNE FUNCTIONS
 ===========================*/
// Mapping to track Runes of Friendship

public mapping
query_neidar_friends_list()
{ 
    mixed list = query_council_property("neidar_friends_list");
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}

public void
add_neidar_friends_list(string name)
{
    mapping list = query_neidar_friends_list();
    
    if (!m_sizeof(list) || !member_array(name, m_indexes(list)) > -1)
        list += ([ name : 1 ]);
    
    set_council_property("neidar_friends_list", list);
}

public void 
remove_neidar_friends_list(string name)
{
    mapping list = query_neidar_friends_list();
    
    if (m_sizeof(list) && member_array(name, m_indexes(list)) > -1)
        m_delkey(list, name);
    
    set_council_property("neidar_friends_list", list);
}

public void
add_friend(mixed player)
{
    if(player->query_npc())
        return;

    string player_name = set_player_property(player, "is_friend", 1);
    add_neidar_friends_list(player_name);

    send_debug_message("neidar", capitalize(player_name)
        + " is a friend of the Neidar Clan.", EVENT_LOG);
}

public int
query_is_friend(mixed player)
{    
    return query_player_property(player, "is_friend");
}

public void
remove_friend(mixed player)
{
    string player_name = set_player_property(player, "is_friend", 0);
    remove_neidar_friends_list(player_name);

    send_debug_message("neidar", capitalize(player_name)
        + " is no longer a friend of the Neidar Clan.", EVENT_LOG);    
}

