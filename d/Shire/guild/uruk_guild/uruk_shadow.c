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
#include "uruk.h"
#include "titles.h"
#include <language.h>
#include <stdproperties.h>
#include <ss_types.h>

/*
 * Function name: query_uruk_level
 * Description  : This function will return the level of the player in this
 *                guild. The level will range from 0 to the number of
 *                titles possible (defined in NUM_TITLES in titles.h) minus one.
 * Returns      : the level
 */
nomask public int
query_uruk_level()
{
    int level = shadow_who->query_stat(SS_RACE);

    level = ((level * NUM_TITLES) / MAX_SS_RACE) - 1;

    return ((level >= NUM_TITLES) ? (NUM_TITLES - 1) :
      ((level < 0) ? 0 : level));
}

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
	
	if(file_size(URUK_RACE_GUILD_LOG) > LOG_SIZE)
		rename(URUK_RACE_GUILD_LOG, (URUK_RACE_GUILD_LOG + ".old"));
	
	write_file(URUK_RACE_GUILD_LOG, text);
}

/*
public mixed query_guild_trainer_race()
{
	//set this up to reflect both branches
	return URUK_RACE_GUILD_TRAINER;
}
*/
/*
	* Function name: query_guild_tax_race
	* Description: Returns the tax for the Noldor race guild.
	* Returns: int - the tax value
*/

nomask public int query_guild_tax_race()
{
	return URUK_RACE_GUILD_TAX;
}

/*
	* Function name: query_guild_name_race
	* Description: Returns the name of the guild
	* Returns: string - the name
*/
nomask public string query_guild_name_race()
{
	return URUK_RACE_GUILD_NAME;
}

/*
	* Function name: query_uruk_title
	* Uruk guild specific function, returns the uruk title of
	* of the player (rank + branch)
*/
/*public string
query_uruk_title()
{
	return (MANAGER->query_uruk_title(shadow_who->query_real_name(), query_uruk_level()));
}*/

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
	if(player->query_race() != "human" && player->query_race() != "goblin")
	{
		call_other(MANAGER, "remove_player_changed_race", player);
		return 0;
	}
	
	// If the alignment of the player is too low, we kick him/her out.
	if(player->query_alignment() > URUK_RACE_GUILD_ALIGN)
	{
		call_other(MANAGER, "remove_player_high_alignment", player);
		return 0;
	}
	
	return 1;
}

/*
	* Function name: query_guild_title_race
	* Description  : This function will return the title for the uruk.
	* Returns      : string - the title.
*/
nomask public string query_guild_title_race()
{
	return(MANAGER->query_uruk_title(shadow_who->query_real_name(), query_uruk_level()));
}

/*
	* Function name: get_uruk_soul
	* Description  : Gets the uruk soul and guild item for the player.
	* Arguments    : int news - a flag used to tell if there is new news
	*                relating to the guild
 */
void get_uruk_soul(int news)
{
	if(news)
	shadow_who->catch_tell("\n\nThere is some news about the " + URUK_RACE_GUILD_NAME + ". See 'help uruk news' " + "for more information.\n\n");
	setuid();
	seteuid(getuid());
	shadow_who->add_cmdsoul(URUK_RACE_GUILD_SOUL);
	shadow_who->update_hooks();
	shadow_who->set_race_name("uruk");
	
	if(MANAGER->query_uruk_type(shadow_who->query_real_name()) == URUK_MORDOR)
		shadow_who->add_prop(M_URUK, 1);
	
	if(MANAGER->query_uruk_type(shadow_who->query_real_name()) == URUK_ISENGARD)
		shadow_who->add_prop(I_URUK, 1);
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
	
	shadow_who->add_subloc(URUK_RACE_GUILD_NAME, this_object());
	
	shadow_who->set_appearance_offset(50);
	
	if(shadow_who->query_login_time() <= file_time("/d/Shire/guild/uruk_guild/help/news"))
	{
		news = 1;
	}
	set_alarm(1.0,0.0,&get_uruk_soul(news));
}

public string
race_sound()
{
    return "growls";
}

public string
actor_race_sound()
{
    return "growl";
}
