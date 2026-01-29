/* 
 *  Member handling code for Neidar Exiles 
 *  
 *  This handler will take care of tracking the exile status of people
 *  in the realms. It will keep track of the names and the dates
 *  of the exiles.
 *  
 *  By keeping track of this information in a centralized place, it can
 *  be displayed and queried even if players aren't logged in. 
 *
 *  Created by Petros, September 2008
 *   
 */

#pragma strict_types
#pragma save_binary

#include <composite.h>
#include <std.h>
#include <const.h>
#include <macros.h>
#include <ss_types.h>
#include "guild.h"
#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define EXILE_DATA      "/d/Ansalon/guild/dwarf/log/exile_data"

// Global Variables
mapping m_exiles;

// Prototypes

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
    m_exiles = ([ ]);
    
    // Restore the values from the file
    if (file_size(EXILE_DATA + ".o") > 0)
    {
        restore_object(EXILE_DATA);
    }
    
    deleted = ({ });
    // Clean up the data. Remove exiles that are deleted.
    foreach (string player : m_indices(m_exiles))
    {
        if (!SECURITY->exist_player(lower_case(player)))
        {
            deleted += ({ player });
            continue;
        }               
    }
    
    // Now delete all the deleted players
    foreach (string delkey : deleted)
    {
        m_delkey(m_exiles, delkey);
    }
    save_object(EXILE_DATA);
}

/* 
 * Function name:       add_exile
 * Description  :       Function to add an exile
 * Arguments    :       player - name of the player to add
 * Returns      :       0/1 - failure/success
 */
public int
add_exile(string player)
{
    object player_obj;
    
    setuid();
    seteuid(getuid());
    
    if (IN_ARRAY(player, m_indices(m_exiles)))
    {
        write("You have already banished that person " +
          "from Iron Delving!\n");
        return 0;
    }

    // Default to Followers if nothing is set
    m_exiles[player] = time();
    save_object(EXILE_DATA);
    return 1;
}

/* 
 * Function name:       remove_exile
 * Description  :       Remove the information about the exile from the
 *                      records.
 * Arguments    :       player - name of the player to remove
 * Returns      :       removal success or failure
 */
public int
remove_exile(string player)
{
    if (!IN_ARRAY(player, m_indices(m_exiles)))
    {
        write(capitalize(player) + " is not currently exiled.\n");
        // No such player in the member mapping
        return 0;
    }
    
    m_delkey(m_exiles, player);
    save_object(EXILE_DATA);
    return 1;
}

/* 
 * Function name:       query_exiles
 * Description  :       Returns the full list of exiles
 * Arguments    :       none
 * Returns      :       string array of exiles
 */
public string *
query_exiles()
{
    return m_indices(m_exiles);
}

/* 
 * Function name:       query_is_exile
 * Description  :       Returns whether the player is an exile
 * Arguments    :       player - name of the player
 * Returns      :       0/1 - not an exile/is an exile
 */
public int
query_is_exile(string player)
{
    player = lower_case(player);
    if (IN_ARRAY(player, m_indices(m_exiles)))
    {
        return 1;
    }
    
    return 0;
}

/* 
 * Function name:       list_exiles
 * Description  :       Used to list all Exiles
 * Arguments    :       player - player requesting the info
 * Returns      :       nothing
 */
public void
list_exiles(object player)
{
    string output;
    string * exiles, * filtered_exiles;

    seteuid(getuid());
    exiles = m_indices(m_exiles);
    filtered_exiles = ({ });
    foreach (string exile : exiles)
    {
        if (wildmatch("*jr", exile) == 1)
        {
            continue;
        }

        filtered_exiles += ({ capitalize(exile) });
    }    

    if (sizeof(filtered_exiles) > 0)
    {
        output = "Those exiled from the Iron Delving include:\n";
        output += sprintf("%-#80s\n", 
                    implode(sort_array(filtered_exiles), "\n"));
        output += "\n"
               + "You can see the banish time using 'exile info <name>'\n";
    }
    else
    {
        output = "There is currently no one exiled from the "
               + "Iron Delving.\n";
    }
            
    player->more(output);
}

/* 
 * Function name:       see_info
 * Description  :       Used to display the time when the person was
 *                      banished
 * Arguments    :       player - player requesting the info
 *                      to_see - person to look up info for
 * Returns      :       nothing
 */
public void
see_info(object player, string to_see)
{
    string name, capitalname;
    
    seteuid(getuid());
    name = lower_case(to_see);    
    capitalname = capitalize(name);
    if (IN_ARRAY(name, m_indices(m_exiles)))
    {
        player->catch_msg(capitalname + " was banished on " 
            + ctime(m_exiles[name]) + ".\n");
    }
    else
    {
        player->catch_msg(capitalname 
            + " does not look like someone who "
            + "has been banished from the Iron Delving.\n");
    }
}
