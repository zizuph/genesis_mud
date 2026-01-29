/*
 * /d/Shire/guild/pered/pered_shadow
 * Shadow for the orcish race guild in the Shire domain
 * Modified from Noldor and Hobbit guilds
 * Altrus, May 2005
*/
// To test:
// Call *yourname add_autoshadow full/path/name

#pragma save_binary
#pragma strict_types

inherit "/std/guild/guild_race_sh";
inherit "/lib/guild_support";
#include "/d/Shire/sys/defs.h"
#include "pered.h"
#include "houses.h"
#include <language.h>
#include <stdproperties.h>
#include <ss_types.h>

#define JOINROOM (PERED_DIR + "lobby")

/*
    *Global variables. Contain the adjective and title chosen by the player,
    *and the geographical location from which the player hails.
*/
private string house_name;
private string orc_adj;
private string orc_title;
private string orc_loc;    

/*
 * Function name: log_guild
 * Description  : This function logs some actions of members of the guild.
 *                It uses a larger cycle than basically coded.
 * Arguments    : string text - the message to log.
 */
nomask private void log_guild(string text)
{
    setuid();
    seteuid(getuid());
    
    if (file_size(PERED_LOG) > LOG_SIZE)
    {
        rename(PERED_LOG, (PERED_LOG + ".old"));
    }
    
    write_file(PERED_LOG, text);
}


//public mixed query_guild_trainer_race()
//{
//    return PERED_TRAINER;
//}

/*
 * Function name: query_guild_house_name
 * Description  : Indicates that this guild gives its members a house name
 *                name rather than a guild-title.
 * Returns      : int 1 - always.
 */
public int query_guild_house_name()
{
    return 1;
}

/*
    * Function name: query_guild_tax_race
    * Description: Returns the tax for the Noldor race guild.
    * Returns: int - the tax value
*/

nomask public int query_guild_tax_race()
{
    return PERED_TAX;
}

/*
    * Function name: query_guild_name_race
    * Description: Returns the name of the guild
    * Returns: string - the name
*/
nomask public string query_guild_name_race()
{
    return PERED_NAME;
}

/*
    * Function name: query_guild_not_allow_join_race
    * Description  : Returns whether we should allow this player to join another
    *                guild if he wants to.
    * Arguments    : player - the player that wants to join
    *                type   - the type of the guild
    *                style  - the styles of the guild
    *                name   - the name of the guild
    * Returns      : 1 - if the player is rejected
    *                0 - if the player is accepted as a member
*/
nomask public int query_guild_not_allow_join_race(object player, string type, string style, string name)
{
    /*         
        *It is a redefinition, so call the original. All tests in the
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
    
    // If the player changed his/her race, we kick him/her out.
    if (player->query_race() != "elf" && player->query_race() != "human")
    {
        call_other(JOINROOM, "remove_player_changed_race", player);
        return 0;
    }
    
    // If the alignment of the player is too low, we kick him/her out.
    if (player->query_alignment() <= BOOT_ALIGN)
    {
        call_other(JOINROOM, "remove_player_high_alignment", player);
        return 0;
    }
    
    return 1;
}

/*
    * Function name: query_guild_title_race
    * Description  : This function will return the title for the orc.
    * Returns      : string - the title.
*/
nomask public string query_guild_title_race()
{
    return clan_name;
}

/*
    * Function name: get_pered_soul
    * Description  : Gets the orc soul and guild item for the player.
    * Arguments    : int news - a flag used to tell if there is new news
    *                relating to the guild
 */
void get_pered_soul(int news)
{
    if (news)
    shadow_who->catch_tell("\n\nThere is some news about the " + PERED_NAME + ". See 'help pered news' " + "for more information.\n\n");
    setuid();
    seteuid(getuid());
    shadow_who->add_cmdsoul(PERED_SOUL);
    shadow_who->update_hooks();
    shadow_who->set_race_name(PERED_RACE_NAME);
}

/*
    * Function name: init_race_shadow
    * Description  : This function is called when a player logs in. It adds
    *                the subloc to the player and make a query to the
    *                joinroom for the family name of the player.
    * Arguments    : string foobar - an init-string if there was any.
*/
nomask public void init_race_shadow(string foobar)
{
    int news;
    
    setuid();
    seteuid(getuid());
    
    shadow_who->add_subloc(PERED_NAME, this_object());
    clan_name = find_object(JOINROOM)->query_house_name(shadow_who->query_real_name());
    
    shadow_who->set_appearance_offset(50);
    
    if(shadow_who->query_login_time() <= file_time(PERED_NEWS))
    {
        news = 1;
    }
    set_alarm(1.0,0.0,&get_pered_soul(news));
}

int set_clan_name(string adj, string title, string loc)
{
    if ((member_array(adj, ADJS) == -1) | (member_array(title, TITLES) == -1) | (member_array(loc, LOCALES) == -1)) // no member
    {
    write("Bad house name, please report this to the guildmaster!\n");
    return 0;
    }
    else
    { 
        house_name = " of the house " + loc;
    }
    return 1;
}

public string
race_sound()
{
    return "snarls";
}

public string
actor_race_sound()
{
    return "snarl";
}
