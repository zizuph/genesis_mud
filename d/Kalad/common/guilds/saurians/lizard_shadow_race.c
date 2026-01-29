/*
 * lizard_shadow.c
 * Shadow of the Lizardman Guild.
 * Modified from the Halfling guild in the Faerun
 * Mirandus, February, 2018
 */

// To test:
// Call *yourname add_autoshadow full/path/name

#pragma save_binary
#pragma strict_types

inherit "/std/guild/guild_race_sh";
inherit "/lib/guild_support";

#include "lizards.h"
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>

#define JOINROOM (LIZGUILD + "join")


/*
 * Function name:   log_guild
 * Description:     This function logs some actions of members of the guild.
 *                  It uses a larger cycle than basically coded.
 * Arguments:       string text - the message to log.
*/
nomask private void 
log_guild(string text)
{
    setuid();
    seteuid(getuid());

    if (file_size(GUILD_LOG) > LOG_SIZE)
    {
        rename(GUILD_LOG, (GUILD_LOG + ".old"));
    }

    write_file(GUILD_LOG, text);
}

/*
 * Function name:   query_guild_tax_race
 * Description:     Returns the tax for the Lizard race guild.
 * Returns:         int - the tax value
*/

nomask public int 
query_guild_tax_race()
{
    return GUILD_TAX_RACE;
}

/*
 * Function name:   query_guild_name_race
 * Description:     Returns the name of the guild
 * Returns:         string - the name
 */
nomask public string 
query_guild_name_race()
{
    return GUILD_NAME_RACE;
}

/*
 * Function name:   query_guild_not_allow_join_race
 * Description  :   Returns whether we should allow this player to join another
 *                  guild if he wants to.
 * Arguments    :   player - the player that wants to join
 *                  type   - the type of the guild
 *                  style  - the styles of the guild
 *                  name   - the name of the guild
 * Returns      :   1 - if the player is rejected
 *                  0 - if the player is accepted as a member
 */
nomask public int 
query_guild_not_allow_join_race(object player, string type, string style, string name)
{
/*
 * It is a redefinition, so call the original. All tests in the
 * guild are made in the joinroom before we allow the player to join.
 */
    return ::query_guild_not_allow_join_race(player, type, style, name);
}


/*
 * Function name: query_guild_keep_player
 * Description  : Tests whether we want to keep a player if he logs in.
 * Arguments    : player - the player to check
 * Returns      : 0 - if the player will be kicked out
 *                1 - the player will remain
 */
public int 
query_guild_keep_player(object player)
{
    setuid();
    seteuid(getuid());

// If the player changed is no longer a hobbit, they get kicked out.
    if(TP->query_race() != "human" || -1 == member_array(TP->query_race_name()
        , VALID_SUBRACES) )
    {
        call_other(JOINROOM, "remove_player_changed_race", player);

        return 0;
    }
/*
 * we dont check for alignment
 */

/*
    // If the alignment of the player is too low, we kick him/her out.
    if (player->query_alignment() > GUILD_ALIGN)
    {
        call_other(JOINROOM, "remove_player_high_alignment", player);
        return 0;
    }
*/
    return 1;
}




/* Function name: query_saurian_level
 * Description:   Get the players numerical guild level
 * Returns:       The numeric guild level
 */
public int
query_saurian_level()
{
    return shadow_who->query_base_stat(SS_RACE) / 3;
}


/* Function name: query_guild_title_race
 * Description:   We change the title of our members depending on their level
 * Returns:       The title
 */
public string
query_guild_title_race()
{
   
   setuid();
   seteuid(getuid());

   return "";
}

public string
query_guild_trainer_race()
{
    return (LIZGUILD + "train");
}
