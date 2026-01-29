/* 
 * School of High Magic Master Object, based on Academic code by Petros
 *
 * This manager will take care of the member data. It will only return info
 * for real players, not npcs.
 *
 * Created by Petros, September 2009
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

#define EVENT_LOG (SOHM_LOGS + "events")
#define LEADER_LOG ("/d/Krynn/guilds/wohs/logs/wohs_conclave")

/*
 * Things that the School of High Magic Manager Keeps track of:
 *
 * is_member                      - flag indicates membership in the guild
 * *_aspirant_title               - functions relating to turning on and off aspirant title
 * *_krynn_race_title             - functions relating to turning on and off Krynn race titles
 * *_passed_wohs_test             - functions relating to the Test of High Sorcery
 * *_wohs_order_colour            - functions relating to WoHS Order choice
 * query_moon_phase               - query phases of the magic moons
 * set_specialisation_element     - function sets element specialisation
 * query_specialisation_element   - function queries element specialisation
 * set_specialisation_form        - function sets form specialisation
 * query_specialisation_form      - function queries form specialisation
 * scribe_spell_to_spellbook      - function adding a spell to spellbook
 * unscribe_spell_from_spellbook  - function removing a spell from spellbook
 * memorise_spell                 - function adding spell to spell list from spellbook
 * unmemorise_spell               - function removing spell from spell list
 * query_scribed_spell            - function checking whether a spell is in spellbook
 * query_memorised_spell          - function checking whether a spell is in spell list
 * query_cantrips_memorised       - number of cantrips currently memorised
 * query_minors_memorised         - number of minor spells currently memorised
 * query_lessers_memorised        - number of lesser spells currently memorised
 * query_greaters_memorised       - number of greater spells currently memorised
 * query_advanced_memorised       - number of advanced spells currently memorised (should be zero for SoHM)
 * set_cantrips_memorised         - sets the number of cantrips currently memorised
 * set_minors_memorised           - sets the number of minor spells currently memorised
 * set_lessers_memorised          - sets the number of lesser spells currently memorised
 * set_greaters_memorised         - sets the number of greater spells currently memorised
 * set_advanced_memorised         - sets the number of advanced spells currently memorised
 * add_memorise_time              - sets counter to wait before being able to memorise a spell type again
 * query_memorise_time            - returns the time one can memorise again for a spell type
 * clear_memorise_time            - clears all memorise time delays currently in place
 * casting_banned                 - stores when casting ban ends
 * join_restricted                - stores when join restriction ends
 * tell_history                   - last 10 wind whisper tells received
 * *_teleport_locations           - functions relating to SoHM and WoHS teleport spell
 */
 
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
    if (file_size(SOHM_DATA + name + ".o") >= 0)
    {
        player_info = restore_map(SOHM_DATA + name);
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
    save_map(player_info, SOHM_DATA + name);    
    return name;
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
    if (file_size(SOHM_DATA + "wohs_council.o") >= 0)
    {
        council_info = restore_map(SOHM_DATA + "wohs_council");
    }

    // Add the value to the cache
    cached_council_info["wohs_council"] = council_info;
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
    
    cached_council_info["wohs_council"] = council_info;
    save_map(council_info, SOHM_DATA + "wohs_council");    
    return "wohs_council";
}

/*=====================
 * MEMBERSHIP FUNCTIONS
 ======================*/
public void
add_member(mixed player)
{
    string player_name = set_player_property(player, "is_member", 1);
    send_debug_message("sohm", capitalize(player_name)
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
           return (player->query_guild_name_occ() == GUILD_NAME);
       }
    }
    
    return query_player_property(player, "is_member");
}

public void
remove_member(mixed player)
{
    string player_name = set_player_property(player, "is_member", 0);
    send_debug_message("sohm", capitalize(player_name)
        + " has left the guild.", EVENT_LOG);    
}

// Mapping to track WoHS Order membership

public mapping
query_wohs_members_list()
{ 
    mixed list = query_council_property("wohs_members_list");
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}

public void
add_wohs_members_list(string name, string order)
{
    mapping list = query_wohs_members_list();
    
    if (!m_sizeof(list) || !member_array(name, m_indexes(list)) > -1)
        list += ([ name : order ]);
    
    set_council_property("wohs_members_list", list);
}

public void 
remove_wohs_members_list(string name)
{
    mapping list = query_wohs_members_list();
    
    if (m_sizeof(list) && member_array(name, m_indexes(list)) > -1)
        m_delkey(list, name);
    
    set_council_property("wohs_members_list", list);
}

public int
count_wohs_order_members(string order)
{
    mapping list = query_wohs_members_list();
    int     order_no = 0;

    foreach(string name, string robe: list)
    {
        if(robe == order)
          order_no += 1;
     }

    return order_no;
}

/*=====================================
 * WOHS COUNCIL AND ELECTION FUNCTIONS
  =====================================*/

public void
add_council_red(mixed player)
{
    // string leader = player->query_real_name();
    string leader = player;

    string council_name = set_council_property("red_council_member", leader);
    send_debug_message("wohs", capitalize(leader)
        + " is now head of the Red Order.", LEADER_LOG);
}

public string
query_is_council_red()
{    
    return query_council_property("red_council_member");
}

public void
remove_council_red()
{
    string council_name = set_council_property("red_council_member", 0);
    send_debug_message("wohs", "The leadership of the Red Order " +
       "has been vacated.", LEADER_LOG);    
}

public void
add_council_white(mixed player)
{
    // string leader = player->query_real_name();
    string leader = player;

    string council_name = set_council_property("white_council_member", leader);
    send_debug_message("wohs", capitalize(leader)
        + " is now head of the White Order.", LEADER_LOG);
}

public string
query_is_council_white()
{    
    return query_council_property("white_council_member");
}

public void
remove_council_white()
{
    string council_name = set_council_property("white_council_member", 0);
    send_debug_message("wohs", "The leadership of the White Order " +
       "has been vacated.", LEADER_LOG);    
}

public void
add_council_black(mixed player)
{
    // string leader = player->query_real_name();
    string leader = player;

    string council_name = set_council_property("black_council_member", leader);
    send_debug_message("wohs", capitalize(leader)
        + " is now head of the Black Order.", LEADER_LOG);
}

public string
query_is_council_black()
{    
    return query_council_property("black_council_member");
}

public void
remove_council_black()
{
    string council_name = set_council_property("black_council_member", 0);
    send_debug_message("wohs", "The leadership of the Black Order " +
       "has been vacated.", LEADER_LOG);    
}


public int
query_council_last_login(string order)
{    
    switch (order)
    {
       case "white":
       {
          return query_council_property("council_white_last_login");
          break;
       }
       case "red":
       {
          return query_council_property("council_red_last_login");
          break;
       }
       case "black":
       {
          return query_council_property("council_black_last_login");
          break;
       }
    }
}

public void
add_council_last_login(string order)
{
    int login_time;

    switch (order)
    {
       case "white":
       {
          login_time = time();
          set_council_property("council_white_last_login", login_time);
          break;
       }
       case "red":
       {
          login_time = time();
          set_council_property("council_red_last_login", login_time);
          break;
       }
       case "black":
       {
          login_time = time();
          set_council_property("council_black_last_login", login_time);
          break;
       }
    }    
}

// Elections to be set for every 300 days, or 25,920,000

public void
reset_annual_council_vote(string order)
{
    int next_vote = time() + 25920000;
    // int next_vote = time() + 600;

    switch (order)
    {
       case "white":
       {
          // next_vote = time() + 25920000;
          set_council_property("next_council_white_vote", next_vote);
          break;
       }
       case "red":
       {
          // next_vote = time() + 25920000;
          set_council_property("next_council_red_vote", next_vote);
          break;
       }
       case "black":
       {
          set_council_property("next_council_black_vote", next_vote);
          break;
       }
    }    
}

public int
query_next_annual_council_vote(string order)
{    
    switch (order)
    {
       case "white":
       {
          return query_council_property("next_council_white_vote");
          break;
       }
       case "red":
       {
          return query_council_property("next_council_red_vote");
          break;
       }
       case "black":
       {
          return query_council_property("next_council_black_vote");
          break;
       }
    }
}

// int open is set at time() + 864000 when voting open, 0 voting is closed.
// 86400 is one day, 864000 is 10 days

public void
set_council_voting_open(string order, int open)
{
    switch (order)
    {
       case "white":
       {
          set_council_property("council_white_vote_open", open);
          break;
       }
       case "red":
       {
          set_council_property("council_red_vote_open", open);
          break;
       }
       case "black":
       {
          set_council_property("council_black_vote_open", open);
          break;
       }
    }    
}

public int
query_council_voting_open(string order)
{    
    switch (order)
    {
       case "white":
       {
          return query_council_property("council_white_vote_open");
          break;
       }
       case "red":
       {
          return query_council_property("council_red_vote_open");
          break;
       }
       case "black":
       {
          return query_council_property("council_black_vote_open");
          break;
       }
    }
}

public mapping
query_council_nomination_list(string order)
{ 
    mixed list; 

    switch (order)
    {
       case "white":
       {
          list = query_council_property("wohs_white_nomination_list");
          break;
       }
       case "red":
       {
          list = query_council_property("wohs_red_nomination_list");
          break;
       }
       case "black":
       {
          list = query_council_property("wohs_black_nomination_list");
          break;
       }
    }
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}

public void
add_council_nomination_list(string name, string order, int level)
{
    mapping list = query_council_nomination_list(order);
    
    if (!m_sizeof(list) || !member_array(name, m_indexes(list)) > -1)
        list += ([ name : level ]);

    switch (order)
    {
       case "white":
       {
          set_council_property("wohs_white_nomination_list", list);
          break;
       }
       case "red":
       {
          set_council_property("wohs_red_nomination_list", list);
          break;
       }
       case "black":
       {
          set_council_property("wohs_black_nomination_list", list);
          break;
       }
    }
}

public void
clear_council_nomination_list(string order)
{
    mapping list = ([ ]);
  
    switch (order)
    {
       case "white":
       {
          set_council_property("wohs_white_nomination_list", list);
          break;
       }
       case "red":
       {
          set_council_property("wohs_red_nomination_list", list);
          break;
       }
       case "black":
       {
          set_council_property("wohs_black_nomination_list", list);
          break;
       }
    }
}

public void 
remove_council_nomination_list(string name, string order)
{
    mapping list = query_council_nomination_list(order);
    
    if (m_sizeof(list) && member_array(name, m_indexes(list)) > -1)
        m_delkey(list, name);
    
    switch (order)
    {
       case "white":
       {
          set_council_property("wohs_white_nomination_list", list);
          break;
       }
       case "red":
       {
          set_council_property("wohs_red_nomination_list", list);
          break;
       }
       case "black":
       {
          set_council_property("wohs_black_nomination_list", list);
          break;
       }
    }
}

public mapping
query_council_vote_list(string order)
{ 
    mixed list; 

    switch (order)
    {
       case "white":
       {
          list = query_council_property("wohs_white_vote_list");
          break;
       }
       case "red":
       {
          list = query_council_property("wohs_red_vote_list");
          break;
       }
       case "black":
       {
          list = query_council_property("wohs_black_vote_list");
          break;
       }
    }
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}

public void
add_council_vote_list(string name, string order, int votes)
{
    mapping list = query_council_vote_list(order);
    
    if (!m_sizeof(list) || member_array(name, m_indexes(list)) == -1)
    {
        DEBUG("First vote added: " +votes+ ".");
        list += ([ name : votes ]);
    }
    else 
    {
        DEBUG("Votes listed in map: " +list[name] + ".\n" +
              "Votes to be added: " +votes+ ".");
        list[name] += votes; 
        DEBUG("After votes added to map: " +list[name] + ".");       
    }

    switch (order)
    {
       case "white":
       {
          set_council_property("wohs_white_vote_list", list);
          break;
       }
       case "red":
       {
          set_council_property("wohs_red_vote_list", list);
          break;
       }
       case "black":
       {
          set_council_property("wohs_black_vote_list", list);
          break;
       }
    }
}

public void
clear_council_vote_list(string order)
{
    mapping list = ([ ]);
  
    switch (order)
    {
       case "white":
       {
          set_council_property("wohs_white_vote_list", list);
          break;
       }
       case "red":
       {
          set_council_property("wohs_red_vote_list", list);
          break;
       }
       case "black":
       {
          set_council_property("wohs_black_vote_list", list);
          break;
       }
    }
}

public void 
remove_council_vote_list(string name, string order)
{
    mapping list = query_council_vote_list(order);
    
    if (m_sizeof(list) && member_array(name, m_indexes(list)) > -1)
        m_delkey(list, name);
    
    switch (order)
    {
       case "white":
       {
          set_council_property("wohs_white_vote_list", list);
          break;
       }
       case "red":
       {
          set_council_property("wohs_red_vote_list", list);
          break;
       }
       case "black":
       {
          set_council_property("wohs_black_vote_list", list);
          break;
       }
    }
}

public mapping
query_has_voted(string order)
{ 
    mixed list; 

    switch (order)
    {
       case "white":
       {
          list = query_council_property("wohs_white_has_voted");
          break;
       }
       case "red":
       {
          list = query_council_property("wohs_red_has_voted");
          break;
       }
       case "black":
       {
          list = query_council_property("wohs_black_has_voted");
          break;
       }
    }
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}

public void
add_has_voted(string name, string order)
{
    mapping list = query_has_voted(order);
    
    if (!m_sizeof(list) || !member_array(name, m_indexes(list)) > -1)
        list += ([ name : order ]);

    switch (order)
    {
       case "white":
       {
          set_council_property("wohs_white_has_voted", list);
          break;
       }
       case "red":
       {
          set_council_property("wohs_red_has_voted", list);
          break;
       }
       case "black":
       {
          set_council_property("wohs_black_has_voted", list);
          break;
       }
    }
}

public void
clear_has_voted(string order)
{
    mapping list = ([ ]);
  
    switch (order)
    {
       case "white":
       {
          set_council_property("wohs_white_has_voted", list);
          break;
       }
       case "red":
       {
          set_council_property("wohs_red_has_voted", list);
          break;
       }
       case "black":
       {
          set_council_property("wohs_black_has_voted", list);
          break;
       }
    }
}

public void 
remove_has_voted(string name, string order)
{
    mapping list = query_has_voted(order);
    
    if (m_sizeof(list) && member_array(name, m_indexes(list)) > -1)
        m_delkey(list, name);
    
    switch (order)
    {
       case "white":
       {
          set_council_property("wohs_white_has_voted", list);
          break;
       }
       case "red":
       {
          set_council_property("wohs_red_has_voted", list);
          break;
       }
       case "black":
       {
          set_council_property("wohs_black_has_voted", list);
          break;
       }
    }
}

public void
endorse_order_change(mixed player, string colour)
{
    string endorsement = "endorse_wohs_order_" + colour;
    string player_name;

    set_player_property(player, endorsement, 1);

    if(!stringp(player))
       player_name = player->query_real_name();
    else
       player_name = player; 

    send_debug_message("wohs", capitalize(player_name)+ " has been endorsed " +
       "to change to the Order of the " +capitalize(colour)+ " Robes.", LEADER_LOG);

}

public void
unendorse_order_change(mixed player, string colour)
{
    string endorsement = "endorse_wohs_order_" + colour;
    string player_name;

    set_player_property(player, endorsement, 0);

    if(!stringp(player))
       player_name = player->query_real_name();
    else
       player_name = player;       

    //send_debug_message("wohs", capitalize(player_name)+ " has been unendorsed " +
    //   "to change to the Order of the " +capitalize(colour)+ " Robes.", LEADER_LOG);
}

public int
query_endorse_order_change(mixed player, string colour)
{
    string endorsement = "endorse_wohs_order_" + colour;
    
    return query_player_property(player, endorsement);
}

/*=================
 * TITLE FUNCTIONS
 ==================*/

// Sets an alternative title option for the WoHS - currently disabled
public void
set_alt_wohs_title(mixed player, int alt)
{
    string player_name = set_player_property(player, "alt_wohs_title", alt);
}

public int
query_alt_wohs_title(mixed player)
{    
    return query_player_property(player, "alt_wohs_title");
}


// set value to 1 to turn off, 0 defaults to on
public void
set_aspirant_title(mixed player, int on_or_off)
{
    string player_name = set_player_property(player, "aspirant_title_off", on_or_off);
}

public int
query_aspirant_title(mixed player)
{    
    return query_player_property(player, "aspirant_title_off");
}

// set value to 1 to turn on, 0 off
public void
set_krynn_race_title(mixed player, int on_or_off)
{
    string player_name = set_player_property(player, "krynn_race_title_on", on_or_off);
}

public int
query_krynn_race_title(mixed player)
{    
    return query_player_property(player, "krynn_race_title_on");
}

// set value to 1 to turn on, 0 off
public void
set_alt_race_title(mixed player, int on_or_off)
{
    string player_name = set_player_property(player, "alt_race_title_on", on_or_off);
}

public int
query_alt_race_title(mixed player)
{    
    return query_player_property(player, "alt_race_title_on");
}

// set value to 1 to turn on, 0 off
public void
set_alt_layman_title(mixed player, int on_or_off)
{
    string player_name = set_player_property(player, "alt_layman_title_on", on_or_off);
}

public int
query_alt_layman_title(mixed player)
{    
    return query_player_property(player, "alt_layman_title_on");
}

// set value to 1 to turn on, 0 off
public void
set_alt_craft_title(mixed player, int on_or_off)
{
    string player_name = set_player_property(player, "alt_craft_title_on", on_or_off);
}
public int
query_alt_craft_title(mixed player)
{    
    return query_player_property(player, "alt_craft_title_on");
}

public string
query_alt_guild_title_occ(mixed player, string guildtype)
{
  if(guildtype == "layman")
  {
    // DEBUG("Layman title called from admin file.");

    if(player->query_guild_member("Pirate of the Bloodsea"))
        return "Bloodsea Spellswain";
    if(player->query_guild_member("Angmar Army"))
        return "Battlemage of the Misty Mountains";
    if(player->query_guild_member("Necromancers Of Vile Darkness"))
        return "Arcanist of Thasmudyan";
    if(player->query_guild_member("Warlocks of Faerun"))
        return "Arcane Occultist";
    if(player->query_guild_member("Shieldbearers of Iron Delving"))
        return "Arcane Warden of the Neidar Clan";
    if(player->query_guild_member("Heralds of the Valar"))
        return "Servant of the Secret Fire";
    if(player->query_guild_member("Thornlin Militia"))
        return "Arcane Warden of Lossarnach";
    if(player->query_guild_member("Vampires of Faerun"))
        return "Neonate Blood Magus";
    if(player->query_guild_member("Elemental Worshippers of Calia"))
      {
        string elem = capitalize(SOHM_MANAGER->query_specialisation_element(player));

        if(!elem)
          elem = "the Elements";

        return "Primal Arcanist of " +elem;
      }
    if(player->query_guild_member("Templars of Takhisis"))
        return "Arcane Spellwarden of the Temple of Neraka";
    if(player->query_guild_member("Ansalon Elvish Archers"))
      {
       if(player->query_alignment() > -101)
        return "Arcane Spellwarden of Qualinesti Forest";
      }
    if(player->query_guild_member("The August Order of Minstrels"))
        return "Arcane Spellsinger of the Muses";
    if(player->query_guild_member("Holy Order of the Stars"))
        return "Pious Theologian";
    if(player->query_guild_member("Blademasters of Khalakhor"))
        return "Spellblade D'Eria of Khalakhor";
    if(player->query_guild_member("Gardeners of Gont"))
      {
        if(player->query_gender() == G_MALE)
          return "Hedge Wizard";
        else
          return "Hedge Witch";
      }
    if(player->query_guild_member("Raiders of Throtyl"))
        return "Magi Reaver of East Keep";
  }

  if(guildtype == "race")
  {
    if(player->query_guild_member("Drow of Underdark"))
        return "Arachnomancer of the Underdark";
    if(player->query_guild_member("Eil-Galaith"))
        return "Spellweaver of the Tower of Sanctuary of Galaith";
    if(player->query_guild_member("Gnomish Inventors"))
        return "Artificer of the Arcane Guild of Mount Nevermind";
    if(player->query_guild_member("Traveller guild"))
        return "Itinerant Thaumaturge";
    if(player->query_guild_member("Krynn race guild"))
    {
      if(player->query_region_title() == "silvanesti elf")
        return "Arcane Savant of the Silvanesti House Mystic";
      if(player->query_region_title() == "qualinesti elf")
        return "Arcane Practitioner of the Qualinesti House of Mystic Arts";
      if(player->query_region_title() == "kagonesti elf")
        return "Sylvan Magus of the Wild Elves";
      if(player->query_region_title() == "icereach human")
        return "Winternorn of the Ice Folk";
    }
    if(player->query_guild_member("Thanar race guild"))
    {
        return "Zealous Magister";
    }
    if(player->query_guild_member("Halflings of Faerun"))
      {
        if(player->query_gender() == G_MALE)
          return "Hin Wizard of the Sword Coast";
        else
          return "Hin Witch of the Sword Coast";
      }
    if(player->query_guild_member("Dunedain"))
      {
        if(player->query_gender() == G_MALE)
          return "Wardmaster of Eriador";
        else
          return "Wardmistress of Eriador";
      }
  }

  if(guildtype == "craft")
  {
    if(player->query_guild_member("Gardeners of Gont"))
    {
        if(player->query_gender() == G_MALE)
          return "Hedge Wizard";
        else
          return "Hedge Witch";
    }
    if(player->query_guild_member("Mariners of Genesis"))
    {
      if(SOHM_MANAGER->query_specialisation_element(player) == "air")
       return "Wind Magus of the Northern Courrain Ocean";
      if(SOHM_MANAGER->query_specialisation_element(player) == "water")
       return "Wave Magus of the Northern Courrain Ocean";
      else 
       return "Sea Mage of the Northern Courrain Ocean";
    }
  }

   return 0;
}

/*================
 * WOHS FUNCTIONS
 =================*/

public void
set_wohs_xp_last_checked(mixed player, int exp)
{
    string player_name = set_player_property(player, "wohs_xp_last_checked", exp);  
}

public int
query_wohs_xp_last_checked(mixed player)
{    
    return query_player_property(player, "wohs_xp_last_checked");
}

public void
set_invited_wohs_test(mixed player)
{
    string player_name = set_player_property(player, "invited_wohs_test", 1);

    send_debug_message("wohs", capitalize(player_name)
        + " has been invited to take the Test of High Sorcery.", LEADER_LOG);
}

public int
query_invited_wohs_test(mixed player)
{    
    return query_player_property(player, "invited_wohs_test");
}

public void
remove_invited_wohs_test(mixed player)
{
    string player_name = set_player_property(player, "invited_wohs_test", 0); 

    //send_debug_message("wohs", capitalize(player_name)+ " has been uninvited " +
    //   "to take the Test of High Sorcery.", LEADER_LOG); 
}

public mapping
query_invited_wohs_test_list()
{ 
    mixed list = query_council_property("invited_wohs_test_list");
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}

public void
add_invited_wohs_test_list(string name, string sponsor)
{
    mapping list = query_invited_wohs_test_list();
    
    if (!m_sizeof(list) || !member_array(name, m_indexes(list)) > -1)
        list += ([ name : sponsor ]);
    
    set_council_property("invited_wohs_test_list", list);
}

public void 
remove_invited_wohs_test_list(string name)
{
    mapping list = query_invited_wohs_test_list();
    
    if (m_sizeof(list) && member_array(name, m_indexes(list)) > -1)
        m_delkey(list, name);
    
    set_council_property("invited_wohs_test_list", list);
}


public void
add_started_wohs_test(mixed player)
{
    string aspirant = player;

    string council_name = set_council_property("started_wohs_test", aspirant);
    string player_name = set_player_property(player, "started_wohs_test", 1);
    send_debug_message("wohs", capitalize(aspirant)
        + " has started the Test of High Sorcery.", LEADER_LOG);
}

public string
query_started_wohs_test()
{    
    return query_council_property("started_wohs_test");
}

public int
query_player_started_wohs_test(mixed player)
{    
    return query_player_property(player, "started_wohs_test");
}

public void
remove_player_started_wohs_test(mixed player)
{ 
    string player_name = set_player_property(player, "started_wohs_test", 0);  
}

public void
remove_started_wohs_test()
{
    string aspirant = set_council_property("started_wohs_test", 0);    
}

public void
set_passed_wohs_test(mixed player)
{
    string player_name = set_player_property(player, "passed_wohs_test", 1);
    send_debug_message("wohs", capitalize(player_name)
        + " has passed the Test of High Sorcery.", LEADER_LOG);
}

public int
query_passed_wohs_test(mixed player)
{
    if (!stringp(player))
    {
      if (player->query_npc())
      {
          return 1;
      }
    }
    
    return query_player_property(player, "passed_wohs_test");
}

public void
remove_wohs_test(mixed player)
{
    string player_name = set_player_property(player, "passed_wohs_test", 0);  
}


public mapping
query_wohs_test_time_stamp()
{ 
    mixed list = query_council_property("wohs_test_time_stamp");
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}

public void
add_wohs_test_time_stamp(mixed name, int date, int var)
{
    mapping list = query_wohs_test_time_stamp();
    
    if (!m_sizeof(list) || !member_array(name, m_indexes(list)) > -1)
        list += ([ name : ({ date, var }) ]);
    
    set_council_property("wohs_test_time_stamp", list);
}

public void 
remove_wohs_test_time_stamp(mixed name)
{
    mapping list = query_wohs_test_time_stamp();
    
    if (m_sizeof(list) && member_array(name, m_indexes(list)) > -1)
        m_delkey(list, name);
    
    set_council_property("wohs_test_time_stamp", list);
}

// mapping of the props set for the Test of High Sorcery

public mapping
query_wohs_test_props(mixed player)
{ 
    mixed list = query_player_property(player, "wohs_test_props");
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}

public mixed
query_wohs_test_prop(mixed player, string prop)
{ 
    mapping list; 
    
    if (!mappingp(list = query_player_property(player, "wohs_test_props")))
        return 0;
    
    if(member_array(prop, m_indexes(list)) > -1)
       return list[prop];

    return 0;
}

public void
add_wohs_test_props(mixed player, string prop, int val)
{
    mapping list = query_wohs_test_props(player);
    
    if (!m_sizeof(list) || !member_array(prop, m_indexes(list)) > -1)
        list += ([ prop : val ]);
    
    string player_name = set_player_property(player, "wohs_test_props", list);
}

public void 
remove_wohs_test_props(mixed player)
{
    mapping list = ([ ]);
    
    string player_name = set_player_property(player, "wohs_test_props", list);
}

public void
set_wohs_test_marking(object player, string marking)
{
    set_player_property(player, "wohs_test_marking", marking);
}

public string
query_wohs_test_marking(mixed player)
{    
    return query_player_property(player, "wohs_test_marking");
}

public void
remove_wohs_test_marking(mixed player)
{
    string player_name = set_player_property(player, "wohs_test_marking", 0);  
}

public void
set_wohs_test_marking_status(object player, int val)
{
    set_player_property(player, "wohs_test_marking_status", val);
}

public int
query_wohs_test_marking_status(mixed player)
{    
    return query_player_property(player, "wohs_test_marking_status");
}

public void
remove_wohs_test_marking_status(mixed player)
{
    string player_name = set_player_property(player, "wohs_test_marking_status", 0);  
}


public void
set_renegade_wohs(mixed player)
{
    string player_name = set_player_property(player, "renegade_wohs", 1);
    send_debug_message("wohs", capitalize(player_name)
        + " has been declared a renegade and exiled from the Tower.", LEADER_LOG);
}

public int
query_renegade_wohs(mixed player)
{   
    return query_player_property(player, "renegade_wohs");
}

public void
remove_renegade_wohs(mixed player)
{
    string player_name = set_player_property(player, "renegade_wohs", 0); 
    //send_debug_message("wohs", capitalize(player_name)
    //    + " has been forgiven and is no longer exiled from the Tower.", LEADER_LOG); 
}

public int
query_renegade_wohs_hunter(mixed player)
{   
    return query_player_property(player, "renegade_wohs_hunter");
}

public void
set_renegade_wohs_hunter(mixed player)
{
    int renegades_killed = query_renegade_wohs_hunter(player) + 1;
    string player_name = set_player_property(player, "renegade_wohs_hunter", renegades_killed);
    send_debug_message("wohs", capitalize(player_name)
        + " has slain a renegade, taking his slayer tally to " +renegades_killed+ ".", LEADER_LOG);
}

public void
remove_renegade_wohs_hunter(mixed player)
{
    string player_name = set_player_property(player, "renegade_wohs_hunter", 0);  
}

public void
set_wohs_order_colour(object player, string colour)
{
    set_player_property(player, "wohs_order", colour);
}

public string
query_wohs_order_colour(mixed player)
{    
    string order = query_player_property(player, "wohs_order");
    switch (order)
    {
    case "red":
    case "black":
    case "white":
        return order;
    }    
    return 0;
}

public string
query_wohs_moon_phase_aid(object player)
{
    string sol = GET_MOON_PHASE(SOLINARI);
    string lun = GET_MOON_PHASE(LUNITARI);
    string nui = GET_MOON_PHASE(NUITARI); 

    string moon_phase;
    string colour = query_wohs_order_colour(player);

    if(!colour)
         return 0;

    if(query_renegade_wohs(player))
         return "penalty";

    if((sol == "full") && (lun == "full") && (nui == "full"))
         return "night of the eye";

    switch(colour)
    {
     case "red":
       moon_phase = lun;
       break;
     case "white":
       moon_phase = sol;
       break;
     case "black":
       moon_phase = nui;
       break;
    }

    if(!moon_phase)
         return 0;

//  waxing&waning three quarter have been removed from the Krynn clock

    switch(moon_phase)
    {
     case "full":
        return "maximum";
        break;
     case "waxing three quarter":
     case "waning three quarter":
     case "waxing gibbous":
     case "waning gibbous":
        return "partial";
        break;
     case "waxing crescent":
     case "waning crescent":
        return "partial_penalty";
        break;
     case "new":
        return "penalty";
        break;
     default:
        return "none";
        break;
    }
    return 0;
}

public void
add_wayreth_study_time(object player)
{
    // Every four days (345600) can study for a new spell
    // in the Tower of Wayreth great library

    int study_time;

    study_time = time() + (345600);
    set_player_property(player,"wayreth_study_time", study_time);    
}

public int
query_wayreth_study_time(object player)
{
    return query_player_property(player,"wayreth_study_time");       
}

public string *
query_members()
{
    string * files = get_dir(SOHM_DATA);
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
query_awake_wohs(object for_obj = this_player())
{
    mixed list;
    object * all_players = users();

    list = filter(all_players, &operator(==)("Wizards of High Sorcery") @
        &->query_guild_name_occ());
    list = filter(list, &can_see_in_alist(, for_obj));
    
    return list;
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
        &->query_guild_name_occ());
    list = filter(list, &can_see_in_alist(, for_obj));
    
    return list;
}

/*==========================================
 * FORM AND ELEMENT SPECIALISATION FUNCTIONS
  ==========================================*/
public void
set_specialisation_element(object player, string element)
{
    set_player_property(player, "specialisation_element", element);
}

public string
query_specialisation_element(object player)
{
    if (player->query_npc()) 
    {
        if (!player->query_prop("_npc_specialisation_element"))
        {
            return "fire";
        }
        return player->query_prop("_npc_specialisation_element");
    }
    
    string element = query_player_property(player, "specialisation_element");
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

public int
query_specialisation_element_skillnum(object player)
{
    string element = query_specialisation_element(player);
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

public void
set_specialisation_form(object player, string form)
{
    set_player_property(player, "specialisation_form", form);
}

public string
query_specialisation_form(object player)
{
    if (player->query_npc()) 
    {
        if (!player->query_prop("_npc_specialisation_form"))
        {
            return "conjuration";
        }
        return player->query_prop("_npc_specialisation_form");
    }
    
    string form = query_player_property(player, "specialisation_form");
    switch (form)
    {
    case "transmutation":
    case "illusion":
    case "divination":
    case "enchantment":
    case "conjuration":
    case "abjuration":
        return form;
    }
    
    return 0;
}

public int
query_specialisation_form_skillnum(object player)
{
    string form = query_specialisation_form(player);
    switch (form)
    {
    case "transmutation":
        return SS_FORM_TRANSMUTATION;
        
    case "illusion":
        return SS_FORM_ILLUSION;
        
    case "divination":
        return SS_FORM_DIVINATION;
    
    case "enchantment":
        return SS_FORM_ENCHANTMENT;

    case "conjuration":
        return SS_FORM_CONJURATION;

    case "abjuration":
        return SS_FORM_ABJURATION;
    }
    return 0;    
}


/*======================================
 * TASKS AND SPELL ACQUISITION FUNCTIONS
 =======================================*/
public void
scribe_spell_to_spellbook(object player, string spell_scribed)
{
    string player_name = set_player_property(player, spell_scribed, time());
    send_debug_message("sohm", capitalize(player_name) + " has scribed " 
        +spell_scribed+ " into their spellbook.", EVENT_LOG); 
}

public void
unscribe_spell_from_spellbook(object player, string spell_unscribed)
{
    set_player_property(player, spell_unscribed, 0);

}

public void
memorise_spell(object player, string spell_memorised)
{
    string player_name = set_player_property(player, spell_memorised, time());
    send_debug_message("sohm", capitalize(player_name) + " has memorised " 
        +spell_memorised+ ".", EVENT_LOG); 
}

public void
unmemorise_spell(object player, string spell_unmemorise)
{
    set_player_property(player, spell_unmemorise, 0);
}

public int
query_scribed_spell(object player, string spell_scribed)
{
    return query_player_property(player, spell_scribed);
}

public int
query_memorised_spell(object player, string spell_memorised)
{
    return query_player_property(player, spell_memorised);
}

public int
query_cantrips_memorised(object player)
{
    return query_player_property(player,"cantrips_memorised");
}

public int
set_cantrips_memorised(object player, int new_value)
{
    set_player_property(player,"cantrips_memorised", new_value);
}


public int
query_minors_memorised(object player)
{
    return query_player_property(player,"minors_memorised");
}

public int
set_minors_memorised(object player, int new_value)
{
    set_player_property(player,"minors_memorised", new_value);
}

public int
query_lessers_memorised(object player)
{
    return query_player_property(player,"lessers_memorised");
}

public int
set_lessers_memorised(object player, int new_value)
{
    set_player_property(player,"lessers_memorised", new_value);
}

public int
query_greaters_memorised(object player)
{
    return query_player_property(player,"greaters_memorised");
}

public int
set_greaters_memorised(object player, int new_value)
{
    set_player_property(player,"greaters_memorised", new_value);
}

// SoHM members should not be able to learn advanced spells.
// Advanced spells will be restricted to WoHS members.

public int
query_advanced_memorised(object player)
{
    return query_player_property(player,"advanced_memorised");
}

public int
set_advanced_memorised(object player, int new_value)
{
    set_player_property(player,"advanced_memorised", new_value);
}

public int
too_many_spells_memorised(object player)
{
     if(player->query_cantrip_spells_max() < query_cantrips_memorised(player))
       return 1;
     if(player->query_minor_spells_max() < query_minors_memorised(player))
       return 1;
     if(player->query_lesser_spells_max() < query_lessers_memorised(player))
       return 1;
     if(player->query_greater_spells_max() < query_greaters_memorised(player))
       return 1;
     if(player->query_advanced_spells_max() < query_advanced_memorised(player))
       return 1;

     return 0;
}

public void
add_memorise_time(object player, int spell_type)
{
    // By default, 24 hours or 86400 (1 hour 3600). 
    // Arcane focus skill increases time to be able to unmemorise
    // a spell type by * 100 / skill
    int focus_skill = player->query_skill(SOHM_GUILD_SKILL);
    int base_memorise_time, mem_time;

    switch (spell_type)
    {
       case SOHM_CANTRIP_SPELL:
       {
          base_memorise_time = 10800; // 3 hours
          mem_time = time() + (base_memorise_time * (100 / max(10, focus_skill)));
          set_player_property(player,"cantrip_mem_time", mem_time);
          break;
       }
       case SOHM_MINOR_SPELL:
       {
          base_memorise_time = 21600; // 6 hours
          mem_time = time() + (base_memorise_time * (100 / max(10, focus_skill)));
          set_player_property(player,"minor_mem_time", mem_time);
          break;
       }
       case SOHM_LESSER_SPELL:
       {
          base_memorise_time = 43200; // 12 hours
          mem_time = time() + (base_memorise_time * (100 / max(10, focus_skill)));
          set_player_property(player,"lesser_mem_time", mem_time);
          break;
       }
       case SOHM_GREATER_SPELL:
       {
          base_memorise_time = 86400; // 24 hours
          mem_time = time() + (base_memorise_time * (100 / max(10, focus_skill)));
          set_player_property(player,"greater_mem_time", mem_time);
          break;
       }
       case SOHM_ADVANCED_SPELL:
       {
          base_memorise_time = 172800; // 48 hours
          mem_time = time() + (base_memorise_time * (100 / max(10, focus_skill)));
          set_player_property(player,"advanced_mem_time", mem_time);
          break;
       }
    }    
}

public int
query_memorise_time(object player, int spell_type)
{
    switch (spell_type)
    {
       case SOHM_CANTRIP_SPELL:
       {
          return query_player_property(player,"cantrip_mem_time");
       }
       case SOHM_MINOR_SPELL:
       {
          return query_player_property(player,"minor_mem_time");
       }
       case SOHM_LESSER_SPELL:
       {
          return query_player_property(player,"lesser_mem_time");
       }
       case SOHM_GREATER_SPELL:
       {
          return query_player_property(player,"greater_mem_time");
       }
       case SOHM_ADVANCED_SPELL:
       {
          return query_player_property(player,"advanced_mem_time");
       }
    }
    return 0;
}

public void
clear_memorise_time(object player)
{
    set_player_property(player,"cantrip_mem_time", 0);
    set_player_property(player,"minor_mem_time", 0);
    set_player_property(player,"lesser_mem_time", 0);
    set_player_property(player,"greater_mem_time", 0);
    set_player_property(player,"advanced_mem_time", 0);
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

// Teleport location functions

public mapping
query_teleport_locations(object player)
{ 
    mixed locations = query_player_property(player, "teleport_locations");
    
    if (!mappingp(locations))
        locations = ([ ]);
    
    return locations;
}

public void
add_teleport_locations(object player, string name, string loc)
{
    mapping locations = query_teleport_locations(player);
    
    if (!m_sizeof(locations) || !member_array(name, m_indexes(locations)) > -1)
        locations += ([ name : loc ]);
    
    set_player_property(player, "teleport_locations", locations);
}

public void 
remove_teleport_locations(object player, string name)
{
    mapping locations = query_teleport_locations(player);
    
    if (m_sizeof(locations) && member_array(name, m_indexes(locations)) > -1)
        m_delkey(locations, name);
    
    set_player_property(player, "teleport_locations", locations);
}
