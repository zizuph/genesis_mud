/*
 * /d/Shire/hobbit/hobbit_shadow.c
 *
 * This is the shadow of the hobbit race guild. It is modified from the
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
//inherit COMMON_INFO;
//#include "titles.h"
#include "noldor.h"
#include <language.h>
#include <stdproperties.h>
#include <ss_types.h>

#define QSW      query_shadow_who()
#define JOINROOM (NOLGLD_DIR + "join")


/*
* Function name: log_guild
* Description  : This function logs some actions of members of the guild.
*                It uses a larger cycle than basically coded.
* Arguments    : string text - the message to log.
*/
nomask private void
log_guild(string text)
{
   setuid();
   seteuid(getuid());
   
   if (file_size(NOLDOR_RACE_GUILD_LOG) > LOG_SIZE)
      {
      rename(NOLDOR_RACE_GUILD_LOG, (NOLDOR_RACE_GUILD_LOG + ".old"));
   }
   
   write_file(NOLDOR_RACE_GUILD_LOG, text);
}

public mixed
query_guild_trainer_race()
{
    return NOLDOR_RACE_GUILD_TRAINER;
}


/*
 * Function name: query_guild_tax_race
 * Description  : Returns the tax for the noldor racial guild.
 * Returns      : int - the tax value
 */
nomask public int
query_guild_tax_race()
{
    return NOLDOR_RACE_GUILD_TAX;
}

/*
 * Function name: query_guild_name_race
 * Description  : Returns the name of the guild
 * Returns      : string - the name
 */
nomask public string
query_guild_name_race()
{
    return NOLDOR_RACE_GUILD_NAME;
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
    return (NOLGLD_DIR + "po");
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
    object tp = this_player();

    setuid();
    seteuid(getuid());

    // If the player changed his/her race, we kick him/her out.
    if (player->query_race() != "hobbit")
    {
	call_other(JOINROOM, "remove_player_changed_race", player);
    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " (race " +
    tp->query_alignment() + ") booted at log in.\n");

	return 0;
    }
    // If the alignment of the player is too low, we kick him/her out.
    if (player->query_alignment() < NOLDOR_RACE_GUILD_ALIGN)
    {
	call_other(JOINROOM, "remove_player_low_alignment", player);
    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " (alignment " +
    tp->query_alignment() + ") booted at log in.\n");

	return 0;
    }
    return 1;
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
      (subloc != NOLDOR_RACE_GUILD_NAME))
    {
	return QSW->show_subloc(subloc, on_obj, for_obj);
    }

    return (((for_obj == on_obj) ? "You are " :
	(capitalize(on_obj->query_pronoun()) + " is ")) +
      "surrounded by a faint white glow.\n");
}


/*
 * Function name: get_noldor_soul
 * Description  : Gets the noldor soul and guild item for the player.
 * Arguments    : int news - a flag used to tell if there is new news 
 *                relating to the guild
 */
void
get_noldor_soul(int news)
{
    shadow_who->catch_tell("Welcome to Arda, noble elf!\n");
    if (news)
	shadow_who->catch_tell("There is some news about the "+
          NOLDOR_RACE_GUILD_NAME+" within the help files.  Please read "+
          "help noldor news for more information.\n");
    setuid(); seteuid(getuid());
    shadow_who->add_cmdsoul(NOLDOR_RACE_GUILD_SOUL);
    shadow_who->update_hooks();
    clone_object(NOLDOR_RACE_GUILD_GLOW)->move(shadow_who, 1);
}

/*
 * Function name: init_race_shadow
 * Description  : This function is called when a player logs in. It adds
 *                the subloc to the player.
 * Arguments    : string foobar - an init-string if there was any.
 */
nomask public void
init_race_shadow(string foobar)
{
    int news;

    setuid();
    seteuid(getuid());

    shadow_who->add_subloc(NOLDOR_RACE_GUILD_NAME, this_object());

    if (shadow_who->query_alignment() <= NOLDOR_RACE_GUILD_ALIGN )
    {

	write("\nYour heart is darkened by the Shadow, and is not " +
       "tolerated by the " + NOLDOR_RACE_GUILD_NAME + 
       ". Return to the path of the Valar before it is to late " +
       "and you are expelled.\n\n");
    }


    if (shadow_who->query_login_time() <= file_time(NOLDOR_NEWS))
    {
	news = 1;
    }
    set_alarm(1.0,0.0,&get_noldor_soul(news));
}


int set_alignment(int align)
{
   if (align <= NOLDOR_RACE_GUILD_ALIGN +25)
    {
        shadow_who->catch_tell("\nYou are beginning to succumb " +
            "to the Shadow. Return to the path of the Valar " +
            "before it is too late or you will be forced to " +
            "leave them.\n");
    }
    shadow_who->set_alignment(align);
}