/*
 * /d/Shire/orc/orc_shadow.c
 *
 * This is the shadow of the orc race guild. It is modified from the
 * shadow of the Rockfriend guild.
 *
 * /Mercade, Rockfriend shadow on 3 November 1993
 *
 * This shadow:
 * /Mercade, 13 November 1994
 *
 * Revision history:
 * Added query_guild_family_name()
 * Dunstable, Jan 29, 1995
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/std/guild/guild_race_sh";
#include "titles.h"
#include "orc.h"
#include <language.h>
#include <stdproperties.h>
#include <ss_types.h>

#define QSW      query_shadow_who()
#define JOINROOM (ORCGLD_DIR + "join")

/*
 * Global variable. It contains the family name of the player.
 */
private string family_name;

public mixed
query_guild_trainer_race()
{
    return ORC_RACE_GUILD_TRAINER;
}

/*
 * Function name: query_guild_family_name
 * Description  : Indicates that this guild gives its members a family
 *                name rather than a guild-title.
 * Returns      : int 1 - always.
 */
public int
query_guild_family_name()
{
    return 1;
}

/*
 * Function name: query_guild_tax_race
 * Description  : Returns the tax for the dwarven race guild.
 * Returns      : int - the tax value
 */
nomask public int
query_guild_tax_race()
{
    return ORC_RACE_GUILD_TAX;
}

/*
 * Function name: query_guild_name_race
 * Description  : Returns the name of the guild
 * Returns      : string - the name
 */
nomask public string
query_guild_name_race()
{
    return ORC_RACE_GUILD_NAME;
}

/*
 * Function name: query_def_post
 * Description  : returns the path of the post office where the player will
 *                receives his mail.
 * Returns      : string - the path ;-)
 */
public string
query_def_post()
{
    return (ORCGLD_DIR + "po");
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
nomask public int
query_guild_not_allow_join_race(object player, string type, string style,
  string name)
{
    /* It is a redefinition, so call the original. All tests in the
     * guild are made in the joinroom before we allow the player to
     * join.
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

    // If the player changed his/her race, we kick him/her out.
    if (player->query_race() != "goblin")
    {
	call_other(JOINROOM, "remove_player_changed_race", player);
	return 0;
    }
    // If the alignment of the player is too low, we kick him/her out.
    if (player->query_alignment() >= ORC_RACE_GUILD_ALIGN)
    {
	call_other(JOINROOM, "remove_player_low_alignment", player);
	return 0;
    }
    return 1;
}

/*
 * Function name: query_guild_title_race
 * Description  : This function will return the title for the Orcs.
 * Returns      : string - the title.
 */
nomask public string
query_guild_title_race()
{
    return family_name;
}

/*
 * Function name: show_subloc
 * Description  : This function is called to display the sublocs
 * Arguments    : subloc  - the sublock to check
 *		  on_obj  - Whom the subloc is on
 *		  for_obj - Who wants to know the subloc
 * Returns      : The string to display
 */
public string
show_subloc(string subloc, object on_obj, object for_obj)
{
    /* Since this is a redefinition, call the original if the call was
     * not meant for us.
     */
    if ((on_obj->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS)) ||
      (subloc != ORC_RACE_GUILD_NAME))
    {
	return QSW->show_subloc(subloc, on_obj, for_obj);
    }

    return (((for_obj == on_obj) ? "You have" :
	(capitalize(on_obj->query_pronoun()) + " has")) +
      " extremely sharp, yellowed fangs.\n");
}


/*
 * Function name: get_orc_soul
 * Description  : Gets the orc soul and guild item for the player.
 * Arguments    : int news - a flag used to tell if there is new news 
 *                relating to the guild
 */
void
get_orc_soul(int news)
{
    shadow_who->catch_tell("Welcome, Fearsome Orc!\n");
    if (news)
	shadow_who->catch_tell("There is some news about the "+
          ORC_RACE_GUILD_NAME+" within the help files.  Please read "+
          "help orc news for more information.\n");
    setuid(); seteuid(getuid());
    shadow_who->add_cmdsoul(ORC_RACE_GUILD_SOUL);
    shadow_who->update_hooks();
//    clone_object(ORC_RACE_GUILD_ARMBAND)->move(shadow_who, 1);
}

/*
 * Function name: init_race_shadow
 * Description  : This function is called when a player logs in. It adds
 *                the subloc to the player and make a query to the
 *                joinroom for the family name of the player.
 * Arguments    : string foobar - an init-string if there was any.
 */
nomask public void
init_race_shadow(string foobar)
{
    int news;

    setuid();
    seteuid(getuid());

    shadow_who->add_subloc(ORC_RACE_GUILD_NAME, this_object());
    family_name = call_other(JOINROOM, "query_family_name", 
       shadow_who->query_real_name());

    if (!strlen(family_name))
    {
	write("\nYou have no tribe name. Please report this to one of the " +
	  "guildmasters of the " + ORC_RACE_GUILD_NAME + ".\n\n");
    }
write ("checked tribe name\n");
    if (shadow_who->query_alignment() > ORC_RACE_GUILD_ALIGN)
    {
	write("\nOrcs are the servants of the Dark Lord. You are " +
	    "sucumbing to the Light. To remain in his service and the " + 
		ORC_RACE_GUILD_NAME + ", you must do more evil deeds " +
		"lest he teach you lesson that are best saved for " +
		"others and expell you forever.\n\n");
    }
write("checked alignment\n");
/*
    if (call_other(JOINROOM, "query_is_birthday", 
        shadow_who->query_real_name))
    {
	write("\nCONGRATULATIONS!!!\n\nIt is your birthday today!\n\n"+
	  "You absolutely must throw a party!  It will be such fun!\n\n"+
	  "Don't forget to bring each guest a present!\n");
    }
*/
    if (shadow_who->query_login_time() <= file_time(ORC_NEWS))
    {
	news = 1;
    }
    set_alarm(1.0,0.0,&get_orc_soul(news));
}

int
set_family_name(string name)
{
    if (member_array(name, TITLES) == -1) // no member
    {
	write("Bad tribe name, please report this to the guildmaster!\n");
	return 0;
    }
    else
    { 
        family_name == name;
    }
    return 1;
}
