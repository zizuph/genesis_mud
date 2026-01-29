/* 
 *  Options Handling Base Code for Guilds
 *  
 *  This manager keeps track of the options for guilds. This can be
 *  inherited and used by any guild.
 *  
 *  By keeping track of this information in a centralized place, it can
 *  be displayed and queried even if players aren't logged in. 
 *
 *  Created by Petros, March 2009
 *   
 */

#pragma strict_types
#pragma save_binary

#include <composite.h>
#include <std.h>
#include <const.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
mapping m_options;
mapping m_displayNames;

/*
 * Function:    query_options_file
 * Description: Mask this function to specify where the option data should
 *              be stored.
 */
public string
query_options_file()
{
    return "";
}

public void
save_data()
{
    string datafile;
    
    datafile = query_options_file();
    if (!strlen(datafile))
    {
        return;
    }

    // Set the id information to access the filesystem
    setuid();
    seteuid(getuid());

    save_object(datafile);    
}

public void
load_data()
{
    string datafile;
    
    datafile = query_options_file();
    if (!strlen(datafile))
    {
        return;
    }

    // Set the id information to access the filesystem
    setuid();
    seteuid(getuid());

    // Restore the values from the file
    if (file_size(datafile + ".o") > 0)
    {
        restore_object(datafile);
    }    
}

// The create function is called for every object. We mask it here
// to do some basic initialization for the handler
public void
create()
{
    // Initialize the variables
    m_options = ([ ]);
    m_displayNames = ([ ]);
    
    load_data();
    save_data(); // to write out the file if it hasn't been created    
}

/*
 * Function:    query_option_name
 * Description: Shows the Display Name for the option shown in
 *              the options text to the user.
 */
public string
query_option_name(string option)
{
    if (!IN_ARRAY(option, m_indices(m_displayNames))
        || !strlen(m_displayNames[option]))
    {
        return "Undefined Option";
    }
    
    return implode(map(explode(m_displayNames[option], " "), capitalize), " ");
}

/*
 * Function:    set_option_name
 * Description: Sets the Display Name for the option shown in
 *              the options text to the user.
 */
public int
set_option_name(string option, string name)
{
    setuid();
    seteuid(getuid());
    
    if (!option || !name)
    {
        return 0;
    }
    
    option = lower_case(option);
    name = lower_case(name);
    if (!IN_ARRAY(option, m_indices(m_options)))
    {
        // Create an empty mapping for the new option
        m_options[option] = ([ ]);
    }
    
    m_displayNames[option] = name;
    
    save_data();
    return 1;
}

/* 
 * Function name:       set_option
 * Description  :       Function to set an option for a player
 * Arguments    :       option - name of the option (key)
 *                      player - player who is setting the option
 *                      data   - value to set the option to
 * Returns      :       0/1 - failure/success
 */
public int
set_option(string option, string player, mixed data)
{
    mapping player_options;
    
    setuid();
    seteuid(getuid());
    
    if (!option || !player)
    {
        return 0;
    }
    
    option = lower_case(option);
    player = lower_case(player);
    if (!IN_ARRAY(option, m_indices(m_options)))
    {
        // Create an empty mapping for the new option
        m_options[option] = ([ ]);
    }
    player_options = m_options[option];

    // Set the option data for the player    
    player_options[player] = data;        

    save_data();
    return 1;
}

/* 
 * Function name:       query_option
 * Description  :       Looks up the option and returns it
 * Arguments    :       option - name of option to check
 *                      player - name of the player query
 * Returns      :       the value of the option or 0
 */
public mixed
query_option(string option, string player)
{
    mapping player_options;
    
    setuid();
    seteuid(getuid());
    
    if (!option || !player)
    {
        return 0;
    }
    
    option = lower_case(option);
    player = lower_case(player);
    if (!IN_ARRAY(option, m_indices(m_options)))
    {
        // Create an empty mapping for the new option
        return 0;
    }
    
    player_options = m_options[option];
    if (!IN_ARRAY(player, m_indices(player_options)))
    {
        return 0;
    }
    
    // Return the value found in the mapping.
    return player_options[player];    
}
