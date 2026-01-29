/* 
 * Warfare Club Manager Object
 *
 * This manager will take care of the member data. It will only return info
 * for real players, not npcs.
 *
 * Created by Arman June 2018
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
public mapping      cached_war_info = ([ ]);

#define EVENT_LOG (CLUBLOG + "events")
#define WOHS_MANAGER     ("/d/Krynn/guilds/sohm/lib/sohm_manager")
#define NEIDAR_MANAGER   ("/d/Ansalon/guild/neidar/lib/neidar_member_manager")
 
// Prototypes
public void increase_krynn_war_player_conquers(mixed player, int increase);
public void increase_krynn_war_losses(string army, int increase);
public void increase_krynn_war_conquers(string army, int increase);

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


/*=======================
 * WAR-SPECIFIC FUNCTIONS
 ========================*/

/* 
 * Function:    load_war_info
 * Description: This loads the war info from their specific file
 *              and returns the mapping of it.
 */
public mapping
load_war_info()
{
    mapping war_info;    
        
    war_info = ([ ]);
        
    // Look for the file
    if (file_size(CLUBDATA + "krynn_war.o") >= 0)
    {
        war_info = restore_map(CLUBDATA + "krynn_war");
    }

    // Add the value to the cache
    cached_war_info["krynn_war"] = war_info;
    return war_info;
}

/* 
 * Function:    query_war_property
 * Description: Generic function to return values from the
 *              manager mapping. This will be used by all
 *              customized getters
 */
public mixed
query_war_property(string prop)
{
    mapping war_info = load_war_info();
    
    return war_info[prop];    
}

/*
 * Function:    set_war_property
 * Description: Generic function to set the values in
 *              the manager mapping. This will be used by all customized
 *              setters
 */
public string
set_war_property(string prop, mixed value)
{
    mapping war_info = load_war_info();
    
    if (value)
    {
        war_info[prop] = value;
    }
    else
    {
        m_delkey(war_info, prop);
    }
    
    cached_war_info["krynn_war"] = war_info;
    save_map(war_info, CLUBDATA + "krynn_war");    
    return "krynn_war";
}


/*=====================
 * MEMBERSHIP FUNCTIONS
 ======================*/
public void
add_member(mixed player)
{
    if(player->query_npc())
        return;

    string player_name = set_player_property(player, "is_member", 1);
    send_debug_message("wfclub", capitalize(player_name)
        + " has joined the warfare club.", EVENT_LOG);
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
    send_debug_message("wfclub", capitalize(player_name)
        + " has left the warfare club.", EVENT_LOG);    
}


public string *
query_members()
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
        if (query_is_member(name))
        {
            members += ({ name });
        }
    }
    
    return members;
}


/*======================================
 *     TITLES AND ARMY SUPPORTING
 =======================================*/

public int
query_is_warfare_army(string army)
{ 
    switch (army)
    {
        case "knights":
        case "knight":
        case "knights of solamnia":
            army = "Knights";
            break;
        case "neidar clan":
        case "neidar":
            army = "Neidar Clan";
            break;
        case "free people":
        case "free":
        case "free people of krynn":
            army = "Free People";
            break;
        case "red dragon army":
        case "red":
        case "red dragonarmy":
            army = "Red Dragon Army";
            break;
        case "blue dragon army":
        case "blue":
        case "blue dragonarmy":
            army = "Blue Dragon Army";
            break;
        case "black dragon army":
        case "black":
        case "black dragonarmy":
            army = "Black Dragon Army";
            break;
        case "green dragon army":
        case "green":
        case "green dragonarmy":
            army = "Green Dragon Army";
            break;
        case "white dragon army":
        case "white":
        case "white dragonarmy":
            army = "White Dragon Army";
            break;
        default:
            army = army;
    }
   
    switch (army)
    {
        case "Knights":
        case "Neidar Clan":
        case "Free People":
        case "Red Dragon Army":
        case "Blue Dragon Army":
        case "Black Dragon Army":
        case "Green Dragon Army":
        case "White Dragon Army":
        return 1;
    }   
 
    return 0;
}

public string
convert_warfare_army_name(string army)
{ 
    army = lower_case(army);

    switch (army)
    {
        case "knights":
        case "knight":
        case "knights of solamnia":
            army = "Knights of Solamnia";
            break;
        case "neidar clan":
        case "neidar":
            army = "Neidar Clan";
            break;
        case "free people":
        case "free":
        case "free people of krynn":
            army = "Free People of Krynn";
            break;
        case "red dragon army":
        case "red":
        case "red dragonarmy":
            army = "Red Dragonarmy";
            break;
        case "blue dragon army":
        case "blue":
        case "blue dragonarmy":
            army = "Blue Dragonarmy";
            break;
        case "black dragon army":
        case "black":
        case "black dragonarmy":
            army = "Black Dragonarmy";
            break;
        case "green dragon army":
        case "green":
        case "green dragonarmy":
            army = "Green Dragonarmy";
            break;
        case "white dragon army":
        case "white":
        case "white dragonarmy":
            army = "White Dragonarmy";
            break;
        default:
            army = army;
    }
 
    return army;
}

public string
query_warfare_army_string(string army)
{ 
    army = lower_case(army);

    switch (army)
    {
        case "knights":
        case "knight":
        case "knights of solamnia":
            army = "Knights";
            break;
        case "neidar clan":
        case "neidar":
            army = "Neidar Clan";
            break;
        case "free people":
        case "free":
        case "free people of krynn":
            army = "Free People";
            break;
        case "red dragon army":
        case "red":
        case "red dragonarmy":
            army = "Red Dragon Army";
            break;
        case "blue dragon army":
        case "blue":
        case "blue dragonarmy":
            army = "Blue Dragon Army";
            break;
        case "black dragon army":
        case "black":
        case "black dragonarmy":
            army = "Black Dragon Army";
            break;
        case "green dragon army":
        case "green":
        case "green dragonarmy":
            army = "Green Dragon Army";
            break;
        case "white dragon army":
        case "white":
        case "white dragonarmy":
            army = "White Dragon Army";
            break;
        default:
            army = army;
    }
   
    if(army)
        return army;
 
    return 0;
}

public void
set_warfare_army(object player, string army)
{
    if(player->query_npc())
        return;

    switch (army)
    {
        case "knights":
            army = "Knights";
            break;
        case "neidar clan":
            army = "Neidar Clan";
            break;
        case "free people":
            army = "Free People";
            break;
        case "red dragon army":
            army = "Red Dragon Army";
            break;
        case "blue dragon army":
            army = "Blue Dragon Army";
            break;
        case "black dragon army":
            army = "Black Dragon Army";
            break;
        case "green dragon army":
            army = "Green Dragon Army";
            break;
        case "white dragon army":
            army = "White Dragon Army";
            break;
        default:
            army = army;
    }

    set_player_property(player, "warfare_army", army);
}

public string
query_warfare_army(mixed player)
{    
    string army = query_player_property(player, "warfare_army");
    switch (army)
    {
        case "Knights":
        case "Neidar Clan":
        case "Free People":
        case "Red Dragon Army":
        case "Blue Dragon Army":
        case "Black Dragon Army":
        case "Green Dragon Army":
        case "White Dragon Army":
        return army;
    }    
    return 0;
}

public void
remove_warfare_army(object player)
{
    set_player_property(player, "warfare_army", 0);
}

// A check to see if the member is one of the five dragonarmies

public int
query_warfare_dragonarmy(mixed player)
{    
    string army = query_player_property(player, "warfare_army");

    switch (army)
    {
        case "Red Dragon Army":
        case "Blue Dragon Army":
        case "Black Dragon Army":
        case "Green Dragon Army":
        case "White Dragon Army":
        return 1;
    }    
    return 0;
}

public int
query_warfare_is_dragonarmy(string army)
{    
    army = query_warfare_army_string(army);

    switch (army)
    {
        case "Red Dragon Army":
        case "Blue Dragon Army":
        case "Black Dragon Army":
        case "Green Dragon Army":
        case "White Dragon Army":
        return 1;
    }    
    return 0;
}

/* Another function needed for cosmetic display of army names,
 * with query_warfare_army returning the name that aligns with 
 * /d/Krynn/common/warfare.h
 */

public string
query_warfare_army_name(mixed player)
{    
    string army = query_player_property(player, "warfare_army");
    switch (army)
    {
        case "Knights":
            return "Knights of Solamnia";
        case "Neidar Clan":
            return "Neidar Clan";
        case "Free People":
            return "Free People of Krynn";
        case "Red Dragon Army":
            return "Red Dragonarmy";
        case "Blue Dragon Army":
            return "Blue Dragonarmy";
        case "Black Dragon Army":
            return "Black Dragonarmy";
        case "Green Dragon Army":
            return "Green Dragonarmy";
        case "White Dragon Army":
            return "White Dragonarmy";
    }    
    return 0;
}


// if set to 1 the subloc is not shown.

public void
set_warfare_subloc_incognito(mixed player, int incognito)
{
    set_player_property(player, "warfare_subloc", incognito);
}

public int
query_warfare_subloc_incognito(mixed player)
{
    int incognito = query_player_property(player, "warfare_subloc");

    return incognito;
}

public int
query_valid_warfare_army(mixed player, string army)
{
    army = query_warfare_army_string(army);

    if(!query_is_warfare_army(army))
        return 0;

    switch (army)
    {
        case "Knights":
        {
            if (player->query_guild_name_occ() == "Solamnian Knights")
                return 1;
            if (player->query_guild_name_occ() == "Priests of Takhisis")
                return 0;
            if (player->query_guild_name_occ() == "Army of Darkness")
                return 0;
            if (player->query_guild_name_occ() == "Cult of Chemosh")
                return 0;
            if (player->query_guild_name_lay() == "Templars of Takhisis")
                return 0;
            if (player->query_guild_name_lay() == "Warlocks of Faerun")
                return 0;
            if (player->query_guild_name_lay() == "Pirate of the Bloodsea")
                return 0;
            if (player->query_race_name() == "goblin")
                return 0;
            if (player->query_race_name() == "orc")
                return 0;
            if (player->query_race_name() == "hobgoblin")
                return 0;
            if ((player->query_guild_name_occ() == "Wizards of High Sorcery") &&
                (WOHS_MANAGER->query_wohs_order_colour(player) == "white"))
                return 1;
            if (player->query_guild_name_occ() == "Rangers of the Westlands")
                return 1;
            if (player->query_guild_name_occ() == "Calian warrior's guild")
                return 1;
            if (player->query_guild_name_lay() == "Holy Order of the Stars")
                return 1;
            if (player->query_guild_name_race() == "Gnomish Inventors")
                return 1;
            if ((player->query_guild_name_race() == "Krynn race guild") &&
                (player->query_region_title() == "kayolin mountain dwarf" ))
                return 1;
            if ((player->query_guild_name_race() == "Krynn race guild") &&
                (player->query_region_title() == "vingaard mountain dwarf" ))
                return 1;
            if ((player->query_guild_name_occ() == "Free Mercenary Guild") &&
                (player->query_alignment() > 900 ))
                return 1;
        }
        case "Neidar Clan":
        {
            if (player->query_guild_name_occ() == "Dwarven Warriors of the Neidar Clan")
                return 1;
            if (player->query_guild_name_occ() == "Priests of Takhisis")
                return 0;
            if (player->query_guild_name_occ() == "Army of Darkness")
                return 0;
            if (player->query_guild_name_occ() == "Cult of Chemosh")
                return 0;
            if (player->query_guild_name_lay() == "Templars of Takhisis")
                return 0;
            if (player->query_guild_name_lay() == "Warlocks of Faerun")
                return 0;
            if (player->query_race_name() == "goblin")
                return 0;
            if (player->query_race_name() == "orc")
                return 0;
            if (player->query_race_name() == "hobgoblin")
                return 0;
            if ((player->query_guild_name_race() == "Krynn race guild") &&
                (player->query_region_title() == "kayolin mountain dwarf" ))
                return 0;
            if ((player->query_guild_name_race() == "Krynn race guild") &&
                (player->query_region_title() == "thorbardin mountain dwarf" ))
                return 0;
            if ((player->query_guild_name_race() == "Krynn race guild") &&
                (player->query_region_title() == "vingaard mountain dwarf" ))
                return 0;
            if ((player->query_guild_name_race() == "Krynn race guild") &&
                (player->query_region_title() == "zhakar mountain dwarf" ))
                return 0;

            if (player->query_guild_name_race() == "Gnomish Inventors")
                return 1;
            if (player->query_guild_name_race() == "Rockfriend guild")
                return 1;
            if ((player->query_guild_name_race() == "Krynn race guild") &&
                (player->query_region_title() == "kender" ))
                return 1;
            if ((player->query_guild_name_race() == "Krynn race guild") &&
                (player->query_region_title() == "kharolis hill dwarf" ))
                return 1;
            if (player->query_guild_name_occ() == "Free Mercenary Guild")
                return 1;
            if (player->query_guild_name_lay() == "Shieldbearers of Iron Delving")
                return 1;
            if (NEIDAR_MANAGER->query_is_friend(player))
                return 1;
        }
        case "Free People":
        {
            if (player->query_guild_name_occ() == "Priests of Takhisis")
                return 0;
            if (player->query_guild_name_occ() == "Solamnian Knights")
                return 0;
            if (player->query_guild_name_occ() == "Dragonarmy")
                return 0;
            if (player->query_guild_name_occ() == "Dwarven Warriors of the Neidar Clan")
                return 0;

            return 1;
        }
        case "Red Dragon Army":
        {
            if (player->query_dragonarmy_division() == "red")
                return 1;
            if (player->query_guild_name_occ() == "Rangers of the Westlands")
                return 0;
            if (player->query_guild_name_occ() == "Calian warrior's guild")
                return 0;
            if (player->query_guild_name_lay() == "Holy Order of the Stars")
                return 0;

            if (player->query_guild_name_occ() == "Priests of Takhisis")
                return 1;
            if ((player->query_guild_name_occ() == "Wizards of High Sorcery") &&
                (WOHS_MANAGER->query_wohs_order_colour(player) == "black"))
                return 1;

            if (player->query_race_name() == "elf")
                return 0;

            if (player->query_guild_name_occ() == "Army of Darkness")
                return 1;
            if (player->query_guild_name_lay() == "Templars of Takhisis")
                return 1;
            if (player->query_race_name() == "goblin")
                return 1;
            if (player->query_race_name() == "orc")
                return 1;
            if (player->query_race_name() == "hobgoblin")
                return 1;
            if (player->query_guild_name_occ() == "Free Mercenary Guild")
                return 1;
        }

        case "Blue Dragon Army":
        {
            if (player->query_dragonarmy_division() == "blue")
                return 1;
            if (player->query_guild_name_occ() == "Rangers of the Westlands")
                return 0;
            if (player->query_guild_name_occ() == "Calian warrior's guild")
                return 0;
            if (player->query_guild_name_lay() == "Holy Order of the Stars")
                return 0;

            if (player->has_undead_shadow())
                return 1;
            if (player->query_guild_name_occ() == "Priests of Takhisis")
                return 1;
            if (player->query_guild_name_occ() == "Army of Darkness")
                return 1;
            if (player->query_guild_name_lay() == "Templars of Takhisis")
                return 1;
            if (player->query_race_name() == "goblin")
                return 1;
            if (player->query_race_name() == "orc")
                return 1;
            if (player->query_race_name() == "hobgoblin")
                return 1;
            if ((player->query_guild_name_occ() == "Wizards of High Sorcery") &&
                (WOHS_MANAGER->query_wohs_order_colour(player) == "black"))
                return 1;
            if (player->query_guild_name_occ() == "Free Mercenary Guild")
                return 1;
        }
        case "Black Dragon Army":
        {
            if (player->query_guild_name_occ() == "Rangers of the Westlands")
                return 0;
            if (player->query_guild_name_occ() == "Calian warrior's guild")
                return 0;
            if (player->query_guild_name_lay() == "Holy Order of the Stars")
                return 0;

            if ((player->query_guild_name_race() == "Krynn race guild") &&
                (player->query_region_title() == "minotaur" ))
                return 1;
            if (player->query_guild_name_occ() == "Priests of Takhisis")
                return 1;
            if (player->query_guild_name_occ() == "Army of Darkness")
                return 1;
            if (player->query_guild_name_lay() == "Templars of Takhisis")
                return 1;
            if (player->query_guild_name_lay() == "Pirate of the Bloodsea")
                return 1;
            if (player->query_race_name() == "goblin")
                return 1;
            if (player->query_race_name() == "orc")
                return 1;
            if (player->query_race_name() == "hobgoblin")
                return 1;
            if ((player->query_guild_name_occ() == "Wizards of High Sorcery") &&
                (WOHS_MANAGER->query_wohs_order_colour(player) == "black"))
                return 1;
            if (player->query_guild_name_occ() == "Free Mercenary Guild")
                return 1;
        }
        case "Green Dragon Army":
        {
            if (player->query_guild_name_occ() == "Rangers of the Westlands")
                return 0;
            if (player->query_guild_name_occ() == "Calian warrior's guild")
                return 0;
            if (player->query_guild_name_lay() == "Holy Order of the Stars")
                return 0;

            if ((player->query_guild_name_race() == "Krynn race guild") &&
                (player->query_region_title() == "minotaur" ))
                return 1;
            if (player->query_guild_name_occ() == "Priests of Takhisis")
                return 1;
            if (player->query_guild_name_occ() == "Army of Darkness")
                return 1;
            if (player->query_guild_name_lay() == "Templars of Takhisis")
                return 1;
            if (player->query_guild_name_lay() == "Cabal of Hiddukel")
                return 1;
            if (player->query_race_name() == "goblin")
                return 1;
            if (player->query_race_name() == "orc")
                return 1;
            if (player->query_race_name() == "hobgoblin")
                return 1;
            if ((player->query_guild_name_occ() == "Wizards of High Sorcery") &&
                (WOHS_MANAGER->query_wohs_order_colour(player) == "black"))
                return 1;
            if (player->query_guild_name_occ() == "Free Mercenary Guild")
                return 1;
        }
        case "White Dragon Army":
        {
            if (player->query_guild_name_occ() == "Rangers of the Westlands")
                return 0;
            if (player->query_guild_name_occ() == "Calian warrior's guild")
                return 0;
            if (player->query_guild_name_lay() == "Holy Order of the Stars")
                return 0;

            if ((player->query_guild_name_race() == "Krynn race guild") &&
                (player->query_region_title() == "minotaur" ))
                return 1;
            if (player->query_guild_name_occ() == "Priests of Takhisis")
                return 1;
            if (player->query_guild_name_occ() == "Army of Darkness")
                return 1;
            if (player->query_guild_name_lay() == "Templars of Takhisis")
                return 1;
            if (player->query_race_name() == "goblin")
                return 1;
            if (player->query_race_name() == "orc")
                return 1;
            if (player->query_race_name() == "hobgoblin")
                return 1;
            if ((player->query_guild_name_occ() == "Wizards of High Sorcery") &&
                (WOHS_MANAGER->query_wohs_order_colour(player) == "black"))
                return 1;
            if (player->query_guild_name_occ() == "Free Mercenary Guild")
                return 1;
        }
    }

    return 0;
}

/*===========================================
 *          CONQUER AND KILL FUNCTIONS
 ============================================*/

public string
query_warfare_location_string(string location)
{
    switch(location)
    {
        case "Newports Area":
            return "newports";
        case "Western Solamnian Plains":
            return "wsp";
        case "Estwilde Plains":
            return "estwilde";
        case "Solace Area":
            return "solace";
        case "Central Abanasinian Plains":
            return "central_abanasinia";
        case "North Abanasinian Plains":
            return "north_abanasinia";
        case "Nightlund Plains":
            return "nightlund";
        case "Guardlund Plains":
            return "guardlund";
        case "Throtyl Pass":
            return "throtyl";
        case "Icewall Plains":
            return "icewall";
        case "Trelgorn Forest":
            return "trelgorn";
    }

    return location;
}

public string
query_warfare_string_location(string location)
{
    switch(location)
    {
        case "newports":
            return "Newports Area";
        case "wsp":
            return "Western Solamnian Plains";
        case "estwilde":
            return "Estwilde Plains";
        case "solace":
            return "Solace Area";
        case "central_abanasinia":
            return "Central Abanasinian Plains";
        case "north_abanasinia":
            return "North Abanasinian Plains";
        case "nightlund":
            return "Nightlund Plains";
        case "guardlund":
            return "Guardlund Plains";
        case "throtyl":
            return "Throtyl Pass";
        case "icewall":
            return "Icewall Plains";
        case "trelgorn":
            return "Trelgorn Forest";
    }

    return location;
}

// Location string as defined for warfare areas in 
// /d/Krynncommon/warfare/warfare.h

public void
set_warfare_conquer_location(mixed player, int value, string location)
{
    location = query_warfare_location_string(location);
    string loc = "warfare_conquer_" + location;

    set_player_property(player, loc, value);
}

public int
query_warfare_conquer_location(mixed player, string location)
{
    location = query_warfare_location_string(location);
    string loc = "warfare_conquer_" + location;
    int value = query_player_property(player, loc);

    return value;
}

public void
player_conquer_location(mixed player, string location, int score, string army,
                        string old_army)
{
    /*
     * Note to Arman:
     *
     * Either handle the following in this function or refer to another
     * function.
     *
     * Modify the score based on the location, add the value to the score
     * of the old army.
     * 
     * The score is the number of seconds that the area has been held by
     * the old army.
     */
    increase_krynn_war_player_conquers(player, 1);
    increase_krynn_war_conquers(army, 1);
    increase_krynn_war_losses(old_army, 1);
    
    location = query_warfare_location_string(location);

    string loc = "warfare_conquer_" + location;
    int value = query_warfare_conquer_location(player, location) + 1;

    set_player_property(player, loc, value);
}

// int level   : the level of the mob slain, range of 0-5 as set in 
//               base file for warfare npcs. 
// string army : the 'colour' of the mob slain, as set in base file
//               for warfare npcs.

public void
set_warfare_enemy_vanquished(mixed player, int value, int lvl, string army)
{
    string level;
    if(lvl < 3)
        level = "standard";
    else if(lvl < 10)
        level = "elite";
    else
        level = "dragon";

    if(army == "crown" || army == "sword" || army == "rose")
        army = "knight";

    if(army == "ice" || army == "rebel" || army == "seeker" || 
       army == "qualinesti" || army == "que-kiri" || army == "que-shu" || 
       army == "que-teh" || army == "que-nal" || army == "throtyl")
        army = "free";

    army = "warfare_" + army + "_" + level + "_vanquished";

    set_player_property(player, army, value);
}

public int
query_warfare_enemy_vanquished(mixed player, int lvl, string army)
{
    string level;
    if(lvl < 3)
        level = "standard";
    else if(lvl < 10)
        level = "elite";
    else
        level = "dragon";

    army = "warfare_" + army + "_" + level + "_vanquished";
    int value = query_player_property(player, army);

    return value;
}

public void
add_warfare_enemy_vanquished(mixed player, int lvl, string army)
{
    string level;
    if(lvl < 3)
        level = "standard";
    else if(lvl < 10)
        level = "elite";
    else
        level = "dragon";

    if(army == "crown" || army == "sword" || army == "rose")
        army = "knight";

    if(army == "ice" || army == "rebel" || army == "seeker" || 
       army == "qualinesti" || army == "que-kiri" || army == "que-shu" || 
       army == "que-teh" || army == "que-nal" || army == "throtyl")
        army = "free";

    int value = query_warfare_enemy_vanquished(player, lvl, army) + 1;
    army = "warfare_" + army + "_" + level + "_vanquished";

    set_player_property(player, army, value);
}

public int
query_total_dragons_slain(mixed player)
{
    int value;
    string * armies = ({ "blue", "red", "green", "white", "black"});

    foreach(string army: armies)
    {    
        army = "warfare_" + army + "_dragon_vanquished";
        value += query_player_property(player, army);
    }

    return value;
}

public void
set_time_attacked_own_army(mixed player)
{
    int value = time();

    set_player_property(player, "_time_attacked_own_army", value);
}

public int
query_time_attacked_own_army(mixed player)
{
    int value = query_player_property(player, "_time_attacked_own_army");

    return value;
}

/*===========================================
 * DRAGONARMY SECONDARY WEAPON FUNCTIONS
 ============================================*/

public void
set_dragonarmy_second_wep(mixed player, string wep)
{
    set_player_property(player, "dragonarmy_second_wep", wep);
}

public void
clear_dragonarmy_second_wep(mixed player)
{
    set_player_property(player, "dragonarmy_second_wep", 0);
}

public string
query_dragonarmy_second_wep(mixed player)
{
    string weapon = query_player_property(player, "dragonarmy_second_wep");

    return weapon;
}

public int
query_dragonarmy_ss_wep_type(mixed player)
{
    string weapon = query_player_property(player, "dragonarmy_second_wep");

    if(!weapon)
        return -1;

    if(weapon == "sword")
        return SS_WEP_SWORD;
    if(weapon == "polearm")
        return SS_WEP_POLEARM;
    if(weapon == "axe")
        return SS_WEP_AXE;
    if(weapon == "knife")
        return SS_WEP_KNIFE;
    if(weapon == "club")
        return SS_WEP_CLUB;
    if(weapon == "bow")
        return SS_WEP_MISSILE;

    return -1;
}

public int
query_dragonarmy_second_wep_skill_bonus(mixed player)
{
    int bonus_skill = 35;

    int base_knights = query_warfare_enemy_vanquished(player, 0, "knight");
    int elite_knights = query_warfare_enemy_vanquished(player, 5, "knight");
    int base_clan = query_warfare_enemy_vanquished(player, 0, "neidar");
    int elite_clan = query_warfare_enemy_vanquished(player, 5, "neidar");
    int base_free = query_warfare_enemy_vanquished(player, 0, "free");
    int elite_free = query_warfare_enemy_vanquished(player, 5, "free");

    int total_conquests = 
        query_warfare_conquer_location(player, "Newports Area") + 
        query_warfare_conquer_location(player, "Western Solamnian Plains") + 
        query_warfare_conquer_location(player, "Estwilde Plains") + 
        query_warfare_conquer_location(player, "Solace Area") +
        query_warfare_conquer_location(player, "Central Abanasinian Plains") +
        query_warfare_conquer_location(player, "North Abanasinian Plains") +
        query_warfare_conquer_location(player, "Nightlund Plains") +
        query_warfare_conquer_location(player, "Guardlund Plains") +
        query_warfare_conquer_location(player, "Throtyl Pass") +
        query_warfare_conquer_location(player, "Icewall Plains");

    if(base_knights > 100)
        bonus_skill += min(10, (4 + (base_knights / 100)));
    if(elite_knights > 100)
        bonus_skill += min(10, (4 + (elite_knights / 100)));
    if(base_clan > 100)
        bonus_skill += min(10, (4 + (base_clan / 100)));
    if(elite_clan > 100)
        bonus_skill += min(10, (4 + (elite_clan / 100)));
    if(base_free > 100)
        bonus_skill += min(10, (4 + (base_free / 100)));
    if(elite_free > 100)
        bonus_skill += min(10, (4 + (elite_free / 100)));
    if(total_conquests > 5)
        bonus_skill += min(30, (5 + (total_conquests / 20)));

    // No more than 85 skillpoints 
    bonus_skill = min(85, bonus_skill);

    return bonus_skill;
}


/*===========================================
 * PRIESTS OF TAKHISIS GURU QUEST FUNCTIONS
 ============================================*/

public void
clear_pot_guru_army_focus(mixed player)
{
    set_player_property(player, "pot_guru_army_focus", 0);
}

public void
set_pot_guru_army_focus(mixed player, string army)
{
    if (!query_warfare_is_dragonarmy(army))
        return;

    set_player_property(player, "pot_guru_army_focus", army);
}

public string
query_pot_guru_army_focus(mixed player)
{    
    return query_player_property(player, "pot_guru_army_focus");
}

public mapping
query_pot_guru_remaining_armies(mixed player)
{ 
    mixed list = query_player_property(player, "pot_guru_remaining_armies");
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}

// Clears the list
public void
reset_pot_guru_remaining_armies(mixed player)
{ 
    mapping list = query_player_property(player, "pot_guru_remaining_armies");
    
    list = ([ ]);
    
    set_player_property(player, "pot_guru_remaining_armies", list);
}

// This removes one of the five armies required to
// conquer an area with to get a guru quest 
public void
remove_pot_guru_remaining_armies(object player, string army)
{
    if (!query_warfare_is_dragonarmy(army))
        return;

    mapping list = query_pot_guru_remaining_armies(player);
    
    if (m_sizeof(list) && member_array(army, m_indexes(list)) > -1)
        m_delkey(list, army);

    set_player_property(player, "pot_guru_remaining_armies", list);
}

// Assigns a random area to an army to be conquered.
public void
set_pot_guru_remaining_armies(object player)
{
    mapping list = query_player_property(player, "pot_guru_remaining_armies");

    string * areas = ({ "Newports Area", "Western Solamnian Plains",
        "Estwilde Plains", "Solace Area", "Central Abanasinian Plains",
        "North Abanasinian Plains", "Nightlund Plains", "Guardlund Plains",
        "Throtyl Pass", "Icewall Plains" });
    string * armies = ({ "Red Dragon Army", "Blue Dragon Army", "Black Dragon Army",
        "Green Dragon Army", "White Dragon Army" });
    
    if (!mappingp(list))
    {
        list = ([ ]);

        foreach (string army: armies)
        {
            string area = ONE_OF(areas);
            CLUB_DEBUG("Army: " +army+ ", area: " +area);
            list += ([ army : area ]);
        }  
    } 

    set_player_property(player, "pot_guru_remaining_armies", list);
}

/*===========================================
 *          STEEL COIN BANKING FUNCTIONS
 ============================================*/

public int
query_warfare_steel_coins_banked(mixed player)
{
    int coins = query_player_property(player, "warfare_steel_coins_banked");

    return coins;
}

public void
add_warfare_steel_coins_banked(mixed player, int coins)
{
    int banked_coins = query_warfare_steel_coins_banked(player);

    banked_coins = max(0, (banked_coins + coins));

    set_player_property(player, "warfare_steel_coins_banked", banked_coins);
}

/*===========================================
 *          WARFARE STATS FUNCTIONS
 ============================================*/

public mapping
query_krynn_war_stats()
{ 
    mixed list = query_war_property("krynn_war_stats");
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}

public void
add_krynn_war_stats(string army, int kills, int conquers, int losses)
{
    mapping list = query_krynn_war_stats();
    
    if (!m_sizeof(list) || !member_array(army, m_indexes(list)) > -1)
        list += ([ army : ({ kills, conquers, losses }) ]);
    
    set_war_property("krynn_war_stats", list);
}

public void
increase_krynn_war_kills(string army, int increase)
{
    mapping list = query_krynn_war_stats();
    int * army_stats;
    int kills, conquers, losses;
    
    if (!m_sizeof(list))
    {
        kills = kills + increase;
        list += ([ army : ({ kills, conquers, losses }) ]);
    }
    else if (member_array(army, m_indexes(list)) == -1)
    {
        kills = kills + increase;
        list += ([ army : ({ kills, conquers, losses }) ]);
    }
    else
    {
        foreach(string army_list, int * army_stats : list)
        {
            if(army_list == army)
            {
                kills = army_stats[0] + increase;
                conquers = army_stats[1];
                losses = army_stats[2];
            }
        }
        list += ([ army : ({ kills, conquers, losses }) ]);
    }

    set_war_property("krynn_war_stats", list);
}

public void
increase_krynn_war_conquers(string army, int increase)
{
    mapping list = query_krynn_war_stats();
    int * army_stats;
    int kills, conquers, losses;
    
    if (!m_sizeof(list))
    {
        conquers = conquers + increase;
        list += ([ army : ({ kills, conquers, losses }) ]);
    }
    else if (member_array(army, m_indexes(list)) == -1)
    {
        conquers = conquers + increase;
        list += ([ army : ({ kills, conquers, losses }) ]);
    }
    else
    {
        foreach(string army_list, int * army_stats : list)
        {
            if(army_list == army)
            {
                kills = army_stats[0];
                conquers = army_stats[1] + increase;
                losses = army_stats[2];
            }
        }
        list += ([ army : ({ kills, conquers, losses }) ]);
    }

    set_war_property("krynn_war_stats", list);
}

public void
increase_krynn_war_losses(string army, int increase)
{
    mapping list = query_krynn_war_stats();
    int * army_stats;
    int kills, conquers, losses;
    
    if (!m_sizeof(list))
    {
        losses = losses + increase;
        list += ([ army : ({ kills, conquers, losses }) ]);
    }
    else if (member_array(army, m_indexes(list)) == -1)
    {
        losses = losses + increase;
        list += ([ army : ({ kills, conquers, losses }) ]);
    }
    else
    {
        foreach(string army_list, int * army_stats : list)
        {
            if(army_list == army)
            {
                kills = army_stats[0];
                conquers = army_stats[1];
                losses = army_stats[2] + increase;
            }
        }
        list += ([ army : ({ kills, conquers, losses }) ]);
    }

    set_war_property("krynn_war_stats", list);
}

public mapping
query_krynn_war_player_stats()
{ 
    mixed list = query_war_property("krynn_war_player_stats");
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}

public void
add_krynn_war_player_stats(mixed player, string army, int kills, int conquers)
{
    mapping list = query_krynn_war_player_stats();
    string name = get_id(player);
    
    if (!m_sizeof(list) || !member_array(name, m_indexes(list)) > -1)
        list += ([ name : ({ army, kills, conquers }) ]);
    
    set_war_property("krynn_war_player_stats", list);
}

public void
increase_krynn_war_player_kills(mixed player, int increase)
{
    mapping list = query_krynn_war_player_stats();
    int * player_stats;
    string name = get_id(player);
    string army = query_warfare_army(player);
    int kills, conquers;
    
    if (!m_sizeof(list))
    {
        kills = kills + increase;
        list += ([ name : ({ army, kills, conquers }) ]);
    }
    else if (member_array(name, m_indexes(list)) == -1)
    {
        kills = kills + increase;
        list += ([ name : ({ army, kills, conquers }) ]);
    }
    else
    {
        foreach(mixed player_list, mixed * player_stats : list)
        { 
            if(player_list == name)
            {
                if(army != player_stats[0])
                {
                    army = army;
// Need to change player stats to zero here  after fix rolled out
                    kills = player_stats[1] + increase;
                    conquers = player_stats[2];
                    list += ([ name : ({ army, kills, conquers }) ]);
                }
                else
                {
                    army = player_stats[0];
                    kills = player_stats[1] + increase;
                    conquers = player_stats[2];
                    list += ([ name : ({ army, kills, conquers }) ]);
                }
            }
        }
    }

    set_war_property("krynn_war_player_stats", list);
}

public void
increase_krynn_war_player_conquers(mixed player, int increase)
{
    mapping list = query_krynn_war_player_stats();
    int * player_stats;
    string name = get_id(player);
    string army = query_warfare_army(player);
    int kills, conquers;
    
    if (!m_sizeof(list))
    {
        conquers = conquers + increase;
        list += ([ name : ({ army, kills, conquers }) ]);
    }
    else if (member_array(name, m_indexes(list)) == -1)
    {
        conquers = conquers + increase;
        list += ([ name : ({ army, kills, conquers }) ]);
    }
    else
    {
        foreach(mixed player_list, mixed * player_stats : list)
        { 
            if(player_list == name)
            {
                if(army != player_stats[0])
                {
                    army = army;
// Need to change player stats to zero here  after fix rolled out
                    kills = player_stats[1];
                    conquers = player_stats[2] + increase;
                    list += ([ name : ({ army, kills, conquers }) ]);
                }
                else
                {
                    army = player_stats[0];
                    kills = player_stats[1];
                    conquers = player_stats[2] + increase;
                    list += ([ name : ({ army, kills, conquers }) ]);
                }
            }
        }
    }

    set_war_property("krynn_war_player_stats", list);
}

public void 
remove_krynn_war_stats(string army)
{
    mapping list = query_krynn_war_stats();
    
    if (m_sizeof(list) && member_array(army, m_indexes(list)) > -1)
        m_delkey(list, army);
    
    set_war_property("krynn_war_stats", list);
}

public void 
remove_krynn_war_player_stats(mixed player)
{
    mapping list = query_krynn_war_player_stats();
    
    if (m_sizeof(list) && member_array(player, m_indexes(list)) > -1)
        m_delkey(list, player);
    
    set_war_property("krynn_war_player_stats", list);
}

// Called when the war ends
public void
reset_krynn_war_stats()
{
    mapping list = ([ ]);
    
    set_war_property("krynn_war_stats", list);
    set_war_property("krynn_war_player_stats", list);
}

// Record the outcome of the war when it resets

public void
record_krynn_war_outcome()
{
    string * army_list = WARFARE_ARMIES;
    mapping list = query_krynn_war_player_stats();
    mapping war_outcome = query_krynn_war_stats();
    int list_size = m_sizeof(list);
    mapping outcome_list = ([ ]);

    foreach (string army_name: army_list)
    {

        int most_kills = 0;
        int most_conquests = 0;
        string most_killer = "";
        string most_conquerer = "";
        string army = "";
        int army_kills = 0;
        int army_conquers = 0;
        int army_conquered = 0;

        foreach (string name, mixed * var: list)
        {
            string army = var[0];
            int kills = var[1];
            int conquers = var[2];

            if((kills > most_kills) && (army_name == army))
            {
                most_killer = name;
                most_kills = kills;
            }

            if((conquers > most_conquests) && (army_name == army))
            {
                most_conquerer = name;
                most_conquests = conquers;
            }
        }

        foreach (string army, mixed *var: war_outcome)
        {
            if(army == army_name)
            {
                army_kills = var[0];
                army_conquers = var[1];
                army_conquered = var[2];
            }
        }

        outcome_list += ([ army_name : ({ most_killer, most_kills, most_conquerer,
            most_conquests, army_kills, army_conquers, army_conquered }) ]);
                               
    }

    set_war_property("krynn_war_leaderboard", outcome_list);

}

public mapping
query_krynn_war_outcome()
{ 
    mixed list = query_war_property("krynn_war_leaderboard");
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}

public void
set_army_winner(string army)
{
    army = query_warfare_army_string(army);

    set_war_property("krynn_war_winner", army);

    send_debug_message("wfclub", capitalize(army)
        + " has been victorious in the War of the Lance.", EVENT_LOG);
}

public void
clear_army_winner()
{
    set_war_property("krynn_war_winner", 0);
}

public string
query_army_winner()
{
    string winner = query_war_property("krynn_war_winner");

    return winner;
}

/*===========================================
 *          JOIN RESTRICTION FUNCTIONS
 ============================================*/

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
    send_debug_message("wfclub", capitalize(player_name)
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
