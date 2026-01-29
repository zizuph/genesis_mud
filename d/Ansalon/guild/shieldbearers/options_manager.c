/* 
 *  Options Handling Code for the Shieldbearers
 *  
 *  This manager keeps track of the options for all the Shieldbearers.
 *  
 *  By keeping track of this information in a centralized place, it can
 *  be displayed and queried even if players aren't logged in. 
 *
 *  Created by Petros, September 2008
 *
 *  Modifications:
 *    - Moved code to Genesis central code - 3/29/2009, Petros  
 */

#pragma strict_types
#pragma save_binary

#include <composite.h>
#include <std.h>
#include <const.h>
#include <macros.h>
#include <ss_types.h>
#include "guild.h"

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
