/*
 * /d/Shire/guild/orcr/orcr_shadow.c
 *
 * This is the shadow for the orc racial guild. It was modifed from the 
 * hobbit racial guild shadow which, in turn, was a modification of the 
 * Rockfriend's racial guild, developed 3 Nov 1993. Thanks Mercade!!!
 *
 * This shadow:
 * /Finwe, October 2000
 */

#pragma save_binary
#pragma strict_types

inherit "/std/guild/guild_race_sh";
#include "/d/Shire/sys/defs.h"
#include "/config/login/login.h"
//#include "titles.h"
#include "orcr.h"
#include <language.h>
#include <stdproperties.h>
#include <ss_types.h>

//#define QSW      query_shadow_who()
#define JOINROOM (ORCRGLD_DIR + "join")


/*
 * Global variable. It contains the tribe name of the player.
 */
//private string tribe_name;
string gTitle = DEFAULT_TITLE;
string gRegion = DEFAULT_REGION;


varargs public void
add_subloc(string sloc, mixed resp, mixed ids)
{
    if ((gRegion == "orc") && sloc == SUBLOC_MISCEXTRADESC)
      shadow_who->add_subloc(SUBLOC_MISCEXTRADESC, TO);
    else
      shadow_who->add_subloc(sloc, resp, ids);
}

void
setup_things()
{
    if (gRegion != "orc")
      shadow_who->add_subloc(ORCR_RACE_SUBLOC,TO);
    shadow_who->add_cmdsoul(ORCR_RACE_GUILD_SOUL);
    shadow_who->update_hooks();
    if (gRegion == "orc")
    {
	shadow_who->remove_subloc(SUBLOC_MISCEXTRADESC);
	shadow_who->add_subloc(SUBLOC_MISCEXTRADESC, TO);
    }
}

public mixed
query_guild_trainer_race()
{
    return ORCR_RACE_GUILD_TRAINER;
}

/*
 * Function name: query_guild_tribe_name
 * Description  : Indicates that this guild gives its members a tribe
 *                name rather than a guild-title.
 * Returns      : int 1 - always.
 */

/*public int
query_guild_tribe_name()
{
    return 1;
}
*/


/*
 * Function name: query_guild_tax_race
 * Description  : Returns the tax for the orc race guild.
 * Returns      : int - the tax value
 */
nomask public int
query_guild_tax_race()
{
    return ORCR_RACE_GUILD_TAX;
}

/*
 * Function name: query_guild_name_race
 * Description  : Returns the name of the guild
 * Returns      : string - the name
 */
nomask public string
query_guild_name_race()
{
    return ORCR_RACE_GUILD_NAME;
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
    return (ORCRGLD_DIR + "po");
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
    // If the alignment of the player is too high, we kick him/her out.
    if (player->query_alignment() >= ORCR_RACE_GUILD_ALIGN)
    {
	call_other(JOINROOM, "remove_player_low_alignment", player);
	return 0;
    }
    return 1;
}

/*
 * Function name: query_guild_title_race
 * Description  : This function will return the title for the Hobbits.
 * Returns      : string - the title.
 */

/*
nomask public string
query_guild_title_race()
{
    return tribe_name;
}
*/

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
      (subloc != ORCR_RACE_GUILD_NAME))
    {
	return query_shadow_who()->show_subloc(subloc, on_obj, for_obj);
    }

    return (((for_obj == on_obj) ? "You have" :
	(capitalize(on_obj->query_pronoun()) + " has")) +
      " jagged, yellow fangs.\n");
}


/*
 * Function name: get_orcr_soul
 * Description  : Gets the orc soul and guild item for the player.
 * Arguments    : int news - a flag used to tell if there is new news 
 *                relating to the guild
 */
void
get_orcr_soul(int news)
{
    shadow_who->catch_tell("Welcome, servant of the Dark Lord!\n");
    if (news)
	shadow_who->catch_tell("The Dark Lord has left some news about the"+
          ORCR_RACE_GUILD_NAME+" in the help files.  Read it!\n");
    setuid(); seteuid(getuid());
    shadow_who->add_cmdsoul(ORCR_RACE_GUILD_SOUL);
    shadow_who->update_hooks();
    clone_object(ORCR_RACE_GUILD_BAND)->move(shadow_who, 1);
}

/*
 * Function name: init_race_shadow
 * Description  : This function is called when a player logs in. It adds
 *                the subloc to the player and make a query to the
 *                joinroom for the tribe name of the player.
 * Arguments    : string foobar - an init-string if there was any.
 */
nomask public void
init_race_shadow(string foobar)
{
    int news;

    setuid();
    seteuid(getuid());

    shadow_who->add_subloc(ORCR_RACE_GUILD_NAME, this_object());
//    tribe_name = call_other(JOINROOM, "query_tribe_name", 
//       shadow_who->query_real_name());
/*
    if (!strlen(tribe_name))
    {
	write("\nYou lost your tribe name. Report it now to a wizard " +
        "of the " + ORCR_RACE_GUILD_NAME + ".\n\n");
    }
*/

// check alignment    
    if (shadow_who->query_alignment() < 0)
    {
	write("\nYou are a disgrace to all that is evil! The " +
	  ORCR_RACE_GUILD_NAME + " shall throw you into the dungeons " +
      "of Mordor if you don't change for the worse!!\n\n");
    }
// set race
    if (!foobar ||
	sscanf(foobar,"%s#%s",gTitle,gRegion) != 2)
    {
	gTitle = DEFAULT_TITLE;
	gRegion = DEFAULT_REGION;
    }

    /* Don't reduce the alarm time, or the miscextra subloc
     * will bug out and change back!!
     */
    set_alarm(1.0,0.0,"setup_things");



// check for guild news
    if (shadow_who->query_login_time() <= file_time(ORCR_NEWS))
    {
	news = 1;
    }
    set_alarm(1.0,0.0,&get_orcr_soul(news));
}

/*
int
set_tribe_name(string name)
{

    if (member_array(name, TITLES) == -1) // no member
    {
	write("Bad tribe name, please report this to the guildmaster!\n");
	return 0;
    }
    else

    { 
        tribe_name == name;
    }
    return 1;
}
*/