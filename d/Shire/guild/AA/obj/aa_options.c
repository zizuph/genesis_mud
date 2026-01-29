/* 
 * Options Handling Code for the Army of Angmar
 *  
 * This options manager tracks all the options that are available to
 * the Army of Angmar members. It uses the base Genesis options manager
 * to handle most of the heavy lifting, specifying only the location of
 * the data file to be used.
 * 
 * Created by Petros, March 2009
 */

#pragma strict_types
#pragma save_binary

#include <composite.h>
#include <std.h>
#include <const.h>
#include <macros.h>
#include <ss_types.h>
#include "../guild.h"

inherit "/d/Genesis/specials/guilds/council/options_manager";

// Defines
#define OPTIONS_DATA      (AA_DIR + "save_files/AA_OPTIONS")

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
