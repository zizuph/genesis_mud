/*
 *  /d/Shire/dunlinde/linde_shadow.c
 *
 *  This is the shadow of the Dunlinde 
 *  occ cleric guild.
 *  Jaypeg, March 2000
 * 
 */

#pragma save_binary

inherit "/std/guild/guild_occ_sh";
#include "titles.h"
#include "dunlinde.h"
#include <language.h>
#include <stdproperties.h>
#include <ss_types.h>

#define LINDE_KILLS "/d/Shire/guild/dunlinde/log/lindekill"
#define NPC_KILLS "/d/Shire/guild/dunlinde/log/lindenpckill"

#define QSW      shadow_who
#define JOINROOM (LINDE_DIR + "join")


public mixed
query_guild_trainer_occ()
{
    return LINDE_GUILD_TRAINER;
}

/*
 * Function name: query_guild_tax_occ
 * Description  : Returns the tax for the guild.
 * Returns      : int - the tax value
 */

nomask public int
query_guild_tax_occ()
{
    return LINDE_GUILD_TAX;
}

nomask public string
query_guild_style_occ()
{
    return LINDE_GUILD_STYLE;

}
/*
 * Function name: query_guild_name_occ
 * Description  : Returns the name of the guild
 * Returns      : string - the name
 */
nomask public string
query_guild_name_occ()
{
    return LINDE_GUILD_NAME;
}

/*
 * Function name: query_linde_level
 * Description  : This function will return the level of the player in this
 *                guild. The level will range from 0 to the number of
 *                titles possible (defined in NUM_TITLES) minus one.
 * Returns      : the level
 */
nomask public int
query_linde_level()
{
    int level = QSW->query_stat(SS_OCCUP);

    level = ((level * NUM_TITLES) / MAX_SS_OCCUP) - 1;

    return ((level >= NUM_TITLES) ? (NUM_TITLES - 1) :
      ((level < 0) ? 0 : level));
}


/*
 * Function name: query_guild_not_allow_join_occ
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
query_guild_not_allow_join_occ(object player, string type, string style,
  string name)
{
    /* It is a redefinition, so call the original. All tests in the
     * guild are made in the joinroom before we allow the player to
     * join.
     */
    return ::query_guild_not_allow_join_occ(player, type, style, name);
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
    string buffoon;
    buffoon = player->query_race_name();


    setuid(); seteuid(getuid());
    /* If the player changed his/her race, we kick him/her out.
     */

    if (buffoon == "goblin" || buffoon == "dwarf"  || buffoon == "orc" ||
        buffoon == "kender" || buffoon == "hobgoblin")
    {
	write("You haven't the singing voice to worship the Valar "+
            "in song.\n");
	call_other(JOINROOM, "remove_player_changed_race", player);
	return 1;
    }


    /* If the alignment of the player is too low, we kick him/her out.
     */
    if (player->query_alignment() < LINDE_GUILD_ALIGN_MIN)
    {
	call_other(JOINROOM, "remove_player_low_alignment", player);
	return 1;
    }

    // Do a check for illegal sub races.
    call_other(JOINROOM, "valid_race_check", player);
    return 1;
}

/*
 * Function name: query_guild_title_occ
 * Description  : This function will return the title for the dunlinde.
 * Returns      : string - the title.
 */
nomask public string
query_guild_title_occ()
{
    return TITLES[query_linde_level()] + " ";
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
      (subloc != LINDE_GUILD_NAME))
    {
	return QSW->show_subloc(subloc, on_obj, for_obj);
    }

    return (((for_obj == on_obj) ? "You are" :
	(capitalize(on_obj->query_pronoun()) + " is")) +
      " of the Dunlinde .\n");
}

nomask public void
get_linde_soul(int news)
{
    object robe;

    shadow_who->catch_tell("Welcome faithful servant!\n");
    if (news)
	shadow_who->catch_tell("There is NEW news about the Dunlinde. "+
          "Type 'help dunlinde news' to read all about it.\n");
    setuid(); seteuid(getuid());
    shadow_who->add_cmdsoul(LINDE_GUILD_SOUL);
    shadow_who->update_hooks();
/*
    clone_object(LINDE_GUILD_SPELLS)->move(shadow_who, 1);
    robe = clone_object(LINDE_GUILD_OBJ);
    robe->move(shadow_who, 1);
    robe->wear_me();
*/
}

/*
 * Function name: init_occ_shadow
 * Description  : This function is called when a player logs in. It adds
 *                the subloc to the player and make a query to the
 *                joinroom for the title of the player.
 * Arguments    : string foobar - an init-string if there was any.
 */
nomask public void
init_occ_shadow(string foobar)
{
    int news;

    setuid();
    seteuid(getuid());

    shadow_who->add_subloc(LINDE_GUILD_NAME, this_object());

    if (shadow_who->query_alignment() < 500)
    {
	write("\nServants of Melkor are not allowed in the " +
	  LINDE_GUILD_NAME + ".  If you are not pure of heart, you will "+
	  "be expelled.\n\n");
    }
//    MEMBER_TRACKER->update_member(shadow_who);

    if (shadow_who->query_login_time() <= file_time(LINDE_NEWS))
    {
	news = 1;
    }
    set_alarm(1.0, 0.0, &get_linde_soul(news));
}

