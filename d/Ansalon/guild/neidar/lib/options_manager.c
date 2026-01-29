/* 
 *  Options Handling Code for the Neidar Clan
 *  
 *  This manager keeps track of the options available to the guild member
 *  
 *  By keeping track of this information in a centralized place, it can
 *  be displayed and queried even if players aren't logged in. 
 *
 *  Created by Petros, May 2008
 */

#pragma strict_types
#pragma save_binary

#include "../guild.h"

inherit "/d/Genesis/specials/guilds/council/options_manager";

// Defines
#define OPTIONS_DATA      (GUILD_DIR + "data/options_data")

/*
 * Function:    query_options_file
 * Description: Mask this function to specify where the option data should
 *              be stored.
 */
public string
query_options_file()
{
    return OPTIONS_DATA;
}
