/*
	* /d/Shire/guild/orc_guild/orc_shadow
	*Shadow for the orcish race guild in the Shire domain
	*Modified from Noldor and Hobbit guilds
	*Altrus, May 2005
*/
// To test:
// Call *yourname add_autoshadow full/path/name

#pragma save_binary
#pragma strict_types

inherit "/std/guild/guild_race_sh";
inherit "/lib/guild_support";
#include "/d/Shire/sys/defs.h"
#include "orc.h"
#include "orc_titles.h"
#include <language.h>
#include <stdproperties.h>
#include <ss_types.h>

#define JOINROOM (ORCGLD_DIR + "rooms/join")

/*
	*Global variables. Contain the adjective and title chosen by the player,
	*and the geographical location from which the player hails.
*/
private string clan_name;
private string orc_adj;
private string orc_title;
private string orc_loc;	

// To be able to hide their title
int hide_title = 0;	

/*
	* Function name: log_guild
	* Description:This function logs some actions of members of the guild.
	*                	It uses a larger cycle than basically coded.
	* Arguments: string text - the message to log.
*/
nomask private void log_guild(string text)
{
	setuid();
	seteuid(getuid());
	
	if (file_size(ORC_RACE_GUILD_LOG) > LOG_SIZE)
	{
		rename(ORC_RACE_GUILD_LOG, (ORC_RACE_GUILD_LOG + ".old"));
	}
	
	write_file(ORC_RACE_GUILD_LOG, text);
}


public mixed query_guild_trainer_race()
{
	return ORC_RACE_GUILD_TRAINER;
}

/*
	* Function name: query_guild_family_name
	* Description: Indicates that this guild gives its members a family
	*                name rather than a guild-title.
	* Returns: int 1 - always.
 */
public int query_guild_family_name()
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
	return ORC_RACE_GUILD_TAX;
}

/*
	* Function name: query_guild_name_race
	* Description: Returns the name of the guild
	* Returns: string - the name
*/
nomask public string query_guild_name_race()
{
	return ORC_RACE_GUILD_NAME;
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
	if (player->query_race() != "elf" && player->query_race() != "goblin")
	{
		call_other(JOINROOM, "remove_player_changed_race", player);
		return 0;
	}
	
	// If the alignment of the player is too low, we kick him/her out.
	if (player->query_alignment() > ORC_RACE_GUILD_ALIGN)
	{
		call_other(JOINROOM, "remove_player_high_alignment", player);
		return 0;
	}
	
	return 1;
}

/*
	* Function name: query_hide_title
	* Description  : This function will see if the title is hidden.
	* Returns      : 0 / 1.
*/
int
query_hide_title()
{
  return hide_title;
}

/*
	* Function name: set_hide_title
	* Description  : This function will hide the title.
	* Returns      : 0 / 1.
*/
void
set_hide_title(int i)
{
  hide_title = i;
}

/*
	* Function name: query_guild_title_race
	* Description  : This function will return the title for the orc.
	* Returns      : string - the title.
*/
nomask public string query_guild_title_race()
{
	if(hide_title)
		return "";

	return clan_name;
}

/*
	* Function name: query_guild_title_race_olist
	* Description  : This function will return the title for the orc.
	* Returns      : string - the title.
*/
nomask public string query_guild_title_race_olist()
{
	return clan_name;
}

/*
	* Function name: get_orc_soul
	* Description  : Gets the orc soul and guild item for the player.
	* Arguments    : int news - a flag used to tell if there is new news
	*                relating to the guild
 */
void get_orc_soul(int news)
{
	if (news)
	shadow_who->catch_tell("\n\nThere is some news about the " + ORC_RACE_GUILD_NAME + ". See 'help orc news' " + "for more information.\n\n");
	setuid();
	seteuid(getuid());
	shadow_who->add_cmdsoul(ORC_RACE_GUILD_SOUL);
	shadow_who->update_hooks();
    if (shadow_who->query_race_name() != "wraith")
        shadow_who->set_race_name("orc");
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
	
	shadow_who->add_subloc(ORC_RACE_GUILD_NAME, this_object());
	clan_name = find_object(JOINROOM)->query_clan_name(shadow_who->query_real_name());
	
	shadow_who->set_appearance_offset(50);
	
	if(shadow_who->query_login_time() <= file_time("/d/Shire/guild/orc_guild/help/news"))
	{
		news = 1;
	}
	set_alarm(1.0,0.0,&get_orc_soul(news));
}

int set_clan_name(string adj, string title, string loc)
{
    if ((member_array(adj, ADJS) == -1) | (member_array(title, TITLES) == -1) | (member_array(loc, LOCALES) == -1)) // no member
    {
	write("Bad clan name, please report this to the guildmaster!\n");
	return 0;
    }
    else
    { 
        clan_name = "the " + adj + " " + title + " of " + loc;
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
