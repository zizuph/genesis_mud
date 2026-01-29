/* 
 *  Member handling code for Calians 
 *  
 *  This handler will take care of Member Information. It will keep track
 *  of things like basic membership (who is a member or not), as well
 *  as which branch they are in, and what rewards and punishments they
 *  have received.
 *  
 *  By keeping track of this information in a centralized place, it can
 *  be displayed and queried even if players aren't logged in. 
 *
 *  Created by Petros, May 2008
 *   
 */

#pragma strict_types
#pragma save_binary

#include <composite.h>
#include <std.h>
#include <const.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"
#include CALIAN_HEADER
#include RECRUITER_HEADER
#include COUNCIL_HEADER
#include DEBUGGER_TELL

// Defines
#define CALIAN_FILE_DIR (CRPALACE_TEXTS+"calian_player_info/")
#define LOGFILE (CRPALACE_LOGS + "shadow_conversions")
#define FOLLOWER_BRANCH 10
#define TRAINEE_BRANCH  11
#define WARRIOR_BRANCH  12

// Global Variables
mapping m_members;

// Prototypes
private int         is_valid_branch(int branch);
public void         remove_calian_member(string player);
public void         set_calian_branch(string player, int branch);

// The create function is called for every object. We mask it here
// to do some basic initialization for the handler
void
create()
{
    string datafile;
    string * deleted;
    
    // Set the id information to access the filesystem
    setuid();
    seteuid(getuid());
    
    // Initialize the variables
    m_members = ([ ]);
    
    // Restore the values from the file
    if (file_size(CALIAN_MEMBER_DATA + ".o") > 0)
    {
        restore_object(CALIAN_MEMBER_DATA);
    }
    
    deleted = ({ });
    // Clean up the data. Remove members that are deleted.
    foreach (string player : m_indices(m_members))
    {
        if (!SECURITY->exist_player(lower_case(player)))
        {
            deleted += ({ player });
            continue;
        }
        
        if (!is_valid_branch(m_members[player]))
        {
            // If there is an error, set the player to be the lowest
            // branch. This will have to be resolved manually.
            m_members[player] = FOLLOWER_BRANCH;
        }        
    }
    
    // Now delete all the deleted players
    foreach (string delkey : deleted)
    {
        remove_calian_member(delkey);
    }
    save_object(CALIAN_MEMBER_DATA);
}

/*
 * Function name: query_guild_tax
 * Description:   Calian Tax rates are defined in the define calian.h
 *                Tax has been defined for all branches of the Calians
 * Arguments    : branch - branch to return tax for
 * Returns:       the tax for Calians depending on branch
 */
public int 
query_guild_tax(int branch) 
{
    switch (branch)
    {
    case FOLLOWER_BRANCH:
        return CALIAN_FOLLOWER_TAX;
    
    case TRAINEE_BRANCH:
        return CALIAN_TRAINEE_TAX;       
    }

    return CALIAN_WARRIOR_TAX; 
}

/* 
 * Function name:       is_valid_branch
 * Description  :       Check to make sure that the branch is a valid
 *                      Calian branch
 * Arguments    :       branch - branch value
 * Returns      :       0/1 - invalid/valid
 */
private int
is_valid_branch(int branch)
{
    if (branch == FOLLOWER_BRANCH
        || branch == TRAINEE_BRANCH
        || branch == WARRIOR_BRANCH)
    {
        return 1;
    }
    
    return 0;
}

/* 
 * Function name:       add_calian_member
 * Description  :       Function to add a member
 * Arguments    :       player - name of the player to add
 *                      branch - which branch to add them as (optional)
 * Returns      :       void/nothing
 */
public varargs void
add_calian_member(string player, int branch)
{
    object player_obj;
    
    if (IN_ARRAY(player, m_indices(m_members)))
    {
        // Player is already a member
        set_calian_branch(player, branch);
    }    
    else if (branch && is_valid_branch(branch))
    {
        m_members[player] = branch;
    }
    else
    {
        // Default to Followers if nothing is set
        m_members[player] = FOLLOWER_BRANCH;
    }

    player_obj = find_living(player);
    if (objectp(player_obj))
    {
        // Now set the guild tax for the player
        player_obj->set_guild_pref(SS_OCCUP, query_guild_tax(branch));
    }
    save_object(CALIAN_MEMBER_DATA);
}

/* 
 * Function name:       remove_calian_member
 * Description  :       Remove the information about the member from the
 *                      records.
 * Arguments    :       player - name of the player to remove
 * Returns      :       void/nothing
 */
public void
remove_calian_member(string player)
{
    if (!IN_ARRAY(player, m_indices(m_members)))
    {
        // No such player in the member mapping
        return;
    }
    
    m_delkey(m_members, player);
    save_object(CALIAN_MEMBER_DATA);

    // There are a number of other handlers that need to be notified
    RECRUITER_CODE->rem_app(player);
    CALIAN_INFO_HANDLER->remove_info(player); 
    CALIAN_TITLE_HANDLER->remove_calian_special_title(capitalize(player)); 
    COUNCIL_CODE->remove_has_glass_medallion(capitalize(player));
}

/* 
 * Function name:       set_calian_branch
 * Description  :       Changes the branch that the calian is a part of
 *                      This involves changing the player's tax.
 * Arguments    :       player - name of the player to remove
 *                      branch - which branch to set them to
 * Returns      :       void/nothing
 */
public void
set_calian_branch(string player, int branch)
{
    object player_obj;
    
    if (!IN_ARRAY(player, m_indices(m_members)))
    {
        // Player is not a member, so no need to set
        return;
    }
    
    if (m_members[player] == branch
        || !is_valid_branch(branch))
    {
        // Don't set if the branch is already the same or invalid
        return;
    }
    
    m_members[player] = branch;

    player_obj = find_living(player);
    if (objectp(player_obj))
    {
        // Now set the guild tax for the player
        player_obj->set_guild_pref(SS_OCCUP, query_guild_tax(branch));
    }
    save_object(CALIAN_MEMBER_DATA);
}

/* 
 * Function name:       set_calian_follower
 * Description  :       Makes the Calian into a follower
 * Arguments    :       player - name of the player to remove
 * Returns      :       void/nothing
 */
public void
set_calian_follower(string player)
{
    set_calian_branch(player, FOLLOWER_BRANCH);
}

/* 
 * Function name:       set_calian_trainee
 * Description  :       Makes the Calian into a Trainee
 * Arguments    :       player - name of the player to remove
 * Returns      :       void/nothing
 */
public void
set_calian_trainee(string player)
{
    set_calian_branch(player, TRAINEE_BRANCH);
}

/* 
 * Function name:       set_calian_warrior
 * Description  :       Makes the calion into a full Warrior
 * Arguments    :       player - name of the player to remove
 * Returns      :       void/nothing
 */
public void
set_calian_warrior(string player)
{
    set_calian_branch(player, WARRIOR_BRANCH);
}

/* 
 * Function name:       query_is_calian
 * Description  :       Check whether the player is a Calian
 * Arguments    :       player - player to check
 * Returns      :       void/nothing
 */
public int
query_is_calian(string player)
{
    return IN_ARRAY(player, m_indices(m_members));
}

/* 
 * Function name:       query_is_follower
 * Description  :       Check whether the player is a Calian Follower
 * Arguments    :       player - player to check
 * Returns      :       void/nothing
 */
public int
query_is_follower(string player)
{
    if (IN_ARRAY(player, m_indices(m_members)))
    {
        return (m_members[player] == FOLLOWER_BRANCH);
    }
    
    return 0;
}

/* 
 * Function name:       query_is_trainee
 * Description  :       Check whether the player is a Calian Trainee
 * Arguments    :       player - player to check
 * Returns      :       void/nothing
 */
public int
query_is_trainee(string player)
{
    if (IN_ARRAY(player, m_indices(m_members)))
    {
        return (m_members[player] == TRAINEE_BRANCH);
    }
    
    return 0;
}

/* 
 * Function name:       query_is_warrior
 * Description  :       Check whether the player is a Calian Warrior
 * Arguments    :       player - player to check
 * Returns      :       void/nothing
 */
public int
query_is_warrior(string player)
{
    if (IN_ARRAY(player, m_indices(m_members)))
    {
        return (m_members[player] == WARRIOR_BRANCH);
    }
    
    return 0;
}

/* 
 * Function name:       query_calian_members
 * Description  :       Returns the full list of Calians
 * Arguments    :       none
 * Returns      :       string array of calians
 */
public string *
query_calian_members()
{
    return m_indices(m_members);
}

/* 
 * Function name:       query_calian_followers
 * Description  :       Returns the full list of Calian Followers
 * Arguments    :       none
 * Returns      :       string array of calian followers
 */
public string *
query_calian_followers()
{
    return filter(m_indices(m_members), query_is_follower);
}

/* 
 * Function name:       query_calian_trainees
 * Description  :       Returns the full list of Calian Trainees
 * Arguments    :       none
 * Returns      :       string array of calian trainees
 */
public string *
query_calian_trainees()
{
    return filter(m_indices(m_members), query_is_trainee);
}

/* 
 * Function name:       query_calian_warriors
 * Description  :       Returns the full list of Calian Warriors
 * Arguments    :       none
 * Returns      :       string array of calian warriors
 */
public string *
query_calian_warriors()
{
    return filter(m_indices(m_members), query_is_warrior);
}

/* 
 * Function name:       query_calian_branch
 * Description  :       Returns the branch that the player belongs to
 * Arguments    :       player - name of player to check
 * Returns      :       0 if not a calian, branch value otherwise
 */
public int
query_calian_branch(string player)
{
    if (IN_ARRAY(player, m_indices(m_members)))
    {
        return m_members[player];
    }
    
    return 0;
}

/* 
 * Function name:       has_old_calian_shadow
 * Description  :       Goes through the shadows and sees if the player
 *                      has the old calian shadow.
 * Arguments    :       player - player to check if they have the calian
 *                               shadow
 * Returns      :       0/1 - does not have old shadow/has old shadow
 */
public int
has_old_calian_shadow(object player)
{
    object current_shadow;
    
    current_shadow = player;
    while (current_shadow = shadow(current_shadow, 0))
    {
        if (MASTER_OB(current_shadow) == OLD_CALIAN_SHADOW)
        {
            return 1;
        }
    }
    
    return 0;
}

public int
replace_calian_medallion(object player)
{
    object medallion;
    if (medallion = present(MEDALLION_ID, player))
    {
        medallion->replace_old_medallion();
    }
}

/* 
 * Function name:       convert_calian_shadow
 * Description  :       Converts the Calian to the new Calian Shadow
 * Arguments    :       player - player to do the conversion on
 * Returns      :       0/1 - failure - success
 */
public int
convert_calian_shadow(object player)
{
    object calian_shadow;
    int branch;
    string start_location;
    
    setuid();
    seteuid(getuid());
    
    if (!has_old_calian_shadow(player))
    {
        // No need to do a conversion, since the player does not have
        // the old Calian shadow.
        player->catch_tell("An error occurred while trying to convert "
                         + "to the new Calian code. Please report the "
                         + "bug to the Calian GM.\n"
                         + "Error: Old Calian shadow not found.\n");
        send_debug_message("calian_shadow", 
                           "Calian does not have the old "
                         + "calian shadow: "
                         + capitalize(player->query_real_name()) + ".\n",
                           LOGFILE);
        return 0;
    }
    
    // Get the current branch that the Calian is in
    if (player->is_calian_follower())
    {
        branch = FOLLOWER_BRANCH;
        send_debug_message("calian_shadow", 
                           capitalize(player->query_real_name()) 
                         + " is a Follower.",
                           LOGFILE);
    }
    else if (player->is_calian_trainee())
    {
        branch = TRAINEE_BRANCH;
        send_debug_message("calian_shadow", 
                           capitalize(player->query_real_name()) 
                         + " is a Trainee.",
                           LOGFILE);
    }
    else if (player->is_calian_warrior())
    {
        branch = WARRIOR_BRANCH;
        send_debug_message("calian_shadow", 
                           capitalize(player->query_real_name()) 
                         + " is a Warrior.",
                           LOGFILE);
    }
    else
    {
        player->catch_tell("An error occurred while trying to convert "
                         + "to the new Calian code. Please report the "
                         + "bug to the Calian GM.\n"
                         + "Error: Could not determine Calian branch.\n");
        send_debug_message("calian_shadow", "Could not determine Calian "
                         + "branch for "
                         + capitalize(player->query_real_name()) + ".\n",
                           LOGFILE);
        return 0;
    }
        
    // Remove the existing Calian Shadow     
    player->remove_guild_occ();
    
    send_debug_message("calian_shadow", 
                       "Converting calian shadow for "
                     + capitalize(player->query_real_name()) + ".",
                     LOGFILE);
    calian_shadow = clone_object(CALIAN_SHADOW);
    if (calian_shadow->shadow_me(player, GUILD_TYPE, 
                                 GUILD_STYLE, GUILD_NAME) != 1)
    {
        send_debug_message("calian_shadow", 
                           "Failed converting the "
                         + "calian shadow with the new one.",
                           LOGFILE);
        player->catch_tell("An error occurred while trying to convert "
                         + "to the new Calian code. Please report the "
                         + "bug to the Calian GM.\n"
                         + "Error: Could not add new Calian shadow.\n");
        calian_shadow->remove_shadow();
        return 0;
    }
    else
    {
        send_debug_message("calian_shadow", 
                           "Successfully replaced "
                         + "the old calian shadow with the new one.",
                           LOGFILE);

        // Now properly set the correct Calian branch.
        add_calian_member(player->query_real_name(), branch);
                         
        // Successfully removed the shadow. Now remove the old cmdsoul
        // and add the new one.
        player->remove_cmdsoul(OLD_CALIAN_CMDSOUL);
        player->add_cmdsoul(CALIAN_CMDSOUL);
        player->update_hooks();
        player->setup_skill_decay();
        
        // Now we need to move the player to the new start location
        // and set their default start location
        start_location = player->query_default_start_location();
        switch (start_location)
        {
            case OLD_CALIAN_START_ROOM:
                player->set_default_start_location(CALIAN_START_ROOM);
                player->move_living("M", CALIAN_START_ROOM, 1, 1);
                break;
            
            case OLD_FOLLOWER_START_ROOM:
                player->set_default_start_location(FOLLOWER_START_ROOM);
                player->move_living("M", FOLLOWER_START_ROOM, 1, 1);
                break;        
        }
        
        // Now replace the calian medallion
        replace_calian_medallion(player);
        
        return 1;
    }        
}

/* 
 * Function name:       list_calians_with_info
 * Description  :       Used to list all Calians who have information, and
 *                      those that don't.
 * Arguments    :       player - player requesting the info
 * Returns      :       nothing
 */
public void
list_calians_with_info(object player)
{
    string output;
    string * infofiles, * calians;
    string * noinfo, * hasinfo, * notallowed;

    seteuid(getuid());
    calians = m_indices(m_members); // all calians    
    infofiles = get_dir(CALIAN_FILE_DIR);
    noinfo = ({ });
    hasinfo = ({ });
    notallowed = ({ });
    foreach (string calian : calians)
    {
        if (!query_is_warrior(calian)
            || wildmatch("*jr", calian) == 1)
        {
            notallowed += ({ calian });
            continue;
        }
        else if (IN_ARRAY(capitalize(calian), infofiles))
        {
            hasinfo += ({ capitalize(calian) });
        }
        else
        {
            noinfo += ({ capitalize(calian) });
        }
    }    

    if (sizeof(hasinfo) > 0)
    {
        output = "There is currently Calian player info on the "
               + "following Calian Warriors: \n";
        output += sprintf("%-#80s\n", implode(sort_array(hasinfo), "\n"));
    }
    else
    {
        output = "There is no available Calian player info.\n";
    }
    
    if (sizeof(noinfo) > 0)
    {
        output += "\nThe following Calians Warriors have not set their "
                + "Calian player info:\n";
        output += sprintf("%-#80s\n", implode(sort_array(noinfo), "\n"));
    }
        
    player->more(output);
}

/* 
 * Function name:       see_info
 * Description  :       Used to display the information that a Calian
 *                      entered about themselves.
 * Arguments    :       player - player requesting the info
 *                      to_see - person to look up info for
 * Returns      :       nothing
 */
public void
see_info(object player, string to_see)
{
    string nm;
  
    to_see = capitalize(lower_case(to_see));
    nm = CALIAN_FILE_DIR + to_see;

    seteuid(getuid());
    if (file_size(nm) == -1) {
        tell_object(player, 
                    "There is no Calian player info for a player called "
                  + to_see + ".\n");
        return;
    } 
    player->more("The following is written about " + to_see + ".\n" 
               + read_file(nm));
}
