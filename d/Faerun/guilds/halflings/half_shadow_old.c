/*
 * half_shadow.c
 * Shadow of the Halflings guild.
 * Modified from the orc guild in the shire
 * Finwe, september 2015
 */

// To test:
// Call *yourname add_autoshadow full/path/name

#pragma save_binary
#pragma strict_types

inherit "/std/guild/guild_race_sh";
inherit "/lib/guild_support";
#include "/d/Faerun/defs.h"
#include "halflings.h"
#include <language.h>
#include <stdproperties.h>
#include <ss_types.h>

#define JOINROOM (HALFGLD_DIR + "join")

/*
 * Global variables. Contain the adjective and title chosen by the player,
 * and the geographical location from which the player hails.
*/
private string clan_name;
// private string orc_adj;
private string half_adj;
// private string orc_title;
private string half_surname;
//private string orc_loc;
private string half_loc;

/*
 * Function name:   log_guild
 * Description:     This function logs some actions of members of the guild.
 *                  It uses a larger cycle than basically coded.
 * Arguments:       string text - the message to log.
*/
nomask private void log_guild(string text)
{
    setuid();
    seteuid(getuid());

    if (file_size(GUILD_LOG) > LOG_SIZE)
    {
        rename(GUILD_LOG, (GUILD_LOG + ".old"));
    }

    write_file(GUILD_LOG, text);
}


public mixed query_guild_trainer_race()
{
    return GUILD_TRAINER;
}

/*
 * Function name:   query_guild_family_name
 * Description:     Indicates that this guild gives its members a family
 *                  name rather than a guild-title.
 * Returns:         int 1 - always.
 */
public int query_guild_family_name()
{
    return 1;
}

/*
 * Function name:   query_guild_tax_race
 * Description:     Returns the tax for the Noldor race guild.
 * Returns:         int - the tax value
*/

nomask public int query_guild_tax_race()
{
    return GUILD_TAX;
}

/*
 * Function name:   query_guild_name_race
 * Description:     Returns the name of the guild
 * Returns:         string - the name
 */
nomask public string query_guild_name_race()
{
    return GUILD_NAME;
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
nomask public int query_guild_not_allow_join_race(object player, string type, string style, string name)
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
public int query_guild_keep_player(object player)
{
    setuid();
    seteuid(getuid());

    // If the player changed is no longer a hobbit, they get kicked out.
    if (player->query_race() != "hobbit")
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

/*
 * Function name:   query_guild_title_race
 * Description  :   This function will return the title for the halfling.
 * Returns      :   string - the title.
*/
nomask public string query_guild_title_race()
{
    return clan_name;
}

/*
 * Function name:   get_halfling_soul
 * Description  :   Gets the halfling soul and guild item for the player.
 * Arguments    :   int news - a flag used to tell if there is new news
 *                  relating to the guild
 */
void get_halfling_soul()
{
    setuid();
    seteuid(getuid());

	shadow_who->add_cmdsoul(GUILD_SOUL);
	shadow_who->update_hooks();
    shadow_who->set_race_name("halfling");
}

/*
 * Function name:   init_race_shadow
 * Description  :   This function is called when a player logs in. It adds
 *                  the subloc to the player and make a query to the
 *                  joinroom for the family name of the player.
 * Arguments    :   string foobar - an init-string if there was any.
 */
nomask public void init_race_shadow(string foobar)
{

	setuid();
	seteuid(getuid());

	shadow_who->add_subloc(GUILD_NAME, this_object());

    set_alarm(1.0,0.0,&get_halfling_soul());
}

public string
race_sound()
{
    return "chatters";
}

public string
actor_race_sound()
{
    return "chatter";
}
