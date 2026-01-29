/* 
 *  Contribution Handling Code for the Elven Camp
 *  
 *  This manager keeps track of player contribution and options
 *  
 *  By keeping track of this information in a centralized place, it can
 *  be displayed and queried even if players aren't logged in. 
 *
 *  Created by Petros, May 2008
 *  Copied by Carnak
 */

#pragma strict_types
#pragma save_binary

#include "../local.h"

inherit "/d/Genesis/specials/guilds/council/options_manager";

// Defines
#define DATA        (CONTRIB + "data/contribution_data")

/*
 * Function:    query_options_file
 * Description: Mask this function to specify where the option data should
 *              be stored.
 */
public string
query_options_file()
{
    return DATA;
}