/*
 * Achievements Controller
 *
 * This bracelet can take on the appearance of anyone's bracelet.
 * This is mostly useful for grabbing information about achievements
 * whether the player is logged in or not.
 *
 * Created by Petros, February 2014
 */
#pragma no_shadow
#pragma strict_types

#include <files.h>
#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <state_desc.h>
#include <cmdparse.h>

inherit "/d/Genesis/specials/achievements/achievement_bracelet";

// Global Variables
public string       PlayerName = "";

public string
construct_file_location()
{
    string player_name = PlayerName;
    string first_char = player_name[..0];
    return "/d/Genesis/specials/achievements/player_data/" + first_char + "/" + player_name;
}

public void
set_player_name(string name)
{
    PlayerName = name;
    string file_location = construct_file_location();
    if (file_size(file_location) <= 0)
    {
        return;
    }
    
    // Re-initialize the database if it's a valid file
    init_database();
}

public string
long_description()
{
    return "This is the Genesis Achievements Controller. You can see badges "
        + "for others by typing <showbadges [player name]>\n";
}

/*
 * Function:    query_database_file
 * Description: Mask this function to specify where the data should
 *              be stored.
 */
public string
query_database_file()
{
    string player_name = PlayerName;
    string first_char = player_name[..0];
    return "/d/Genesis/specials/achievements/player_data/" + first_char + "/" + player_name;
}

