/*
 *  /d/Shire/estehilde/este_shadow.c
 *
 *  This is the shadow of the Estehilde 
 *  occ cleric guild.
 *  Jaypeg, June 1999
 * 
 */

#pragma save_binary

inherit "/std/guild/guild_occ_sh";
#include "titles.h"
#include "estehilde.h"
#include <language.h>
#include <stdproperties.h>
#include <ss_types.h>

#define ESTE_KILLS "/d/Shire/guild/estehilde/log/estekill"
#define NPC_KILLS "/d/Shire/guild/estehilde/log/estenpckill"

#define QSW      shadow_who
#define JOINROOM (ESTE_DIR + "join")


public mixed
query_guild_trainer_occ()
{
    return ESTE_GUILD_TRAINER;
}

/*
 * Function name: query_guild_tax_occ
 * Description  : Returns the tax for the guild.
 * Returns      : int - the tax value
 */

nomask public int
query_guild_tax_occ()
{
    return ESTE_GUILD_TAX;
}

nomask public string
query_guild_style_occ()
{
    return ESTE_GUILD_STYLE;

}
/*
 * Function name: query_guild_name_occ
 * Description  : Returns the name of the guild
 * Returns      : string - the name
 */
nomask public string
query_guild_name_occ()
{
    return ESTE_GUILD_NAME;
}

/*
 * Function name: query_este_level
 * Description  : This function will return the level of the player in this
 *                guild. The level will range from 0 to the number of
 *                titles possible (defined in NUM_TITLES) minus one.
 * Returns      : the level
 */
nomask public int
query_este_level()
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
    buffoon = player->query_race();


    setuid(); seteuid(getuid());
    /* If the player changed his/her race, we kick him/her out.
     */

    if (buffoon == "goblin" || buffoon == "dwarf" || buffoon == "gnome")
    {
	write("Only the creations of Eru Illuvatar may serve the Valar.\n");
	call_other(JOINROOM, "remove_player_changed_race", player);
	return 1;
    }


    /* If the alignment of the player is too low, we kick him/her out.
     */
    if (player->query_alignment() < ESTE_GUILD_ALIGN_MIN)
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
 * Description  : This function will return the title for the estehilde.
 * Returns      : string - the title.
 */
nomask public string
query_guild_title_occ()
{
    return TITLES[query_este_level()] + " ";
}

/*
 * Function name: show_subloc
 * Description  : This function is called to display the sublocs
 * Arguments    : subloc  - the sublock to check
 *		  on_obj  - Whom the subloc is on
 *		  for_obj - Who wants to know the subloc
 * Returns      : The string to display

public string
show_subloc(string subloc, object on_obj, object for_obj)
{
    /* Since this is a redefinition, call the original if the call was
     * not meant for us.
     */
    if ((on_obj->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS)) ||
      (subloc != ESTE_GUILD_NAME))
    {
	return QSW->show_subloc(subloc, on_obj, for_obj);
    }

    return (((for_obj == on_obj) ? "You are" :
	(capitalize(on_obj->query_pronoun()) + " is")) +
      " of the Estehilde .\n");
}
 */

nomask public void
get_este_soul(int news)
{
//    object robe;

    shadow_who->catch_tell("Greetings, Estehilde!\n");
    if (news)
	shadow_who->catch_tell("There is NEW news about the Estehilde. "+
          "Type 'help estehilde news' to read all about it.\n");
    setuid(); seteuid(getuid());
    shadow_who->add_cmdsoul(ESTE_GUILD_SOUL);
    shadow_who->update_hooks();
/*
    clone_object(ESTE_GUILD_SPELLS)->move(shadow_who, 1);
    robe = clone_object(ESTE_GUILD_OBJ);
    robe->move(shadow_who, 1);
    robe->wear_me();
*/
}

/*
 * Function name: init_occ_shadow
 * Description  : This function is called when a player logs in. It adds
 *                the subloc to the player and make a query to the
 *                joinroom for the family name of the player.
 * Arguments    : string foobar - an init-string if there was any.
 */
nomask public void
init_occ_shadow(string foobar)
{
    int news;

    setuid();
    seteuid(getuid());

//    shadow_who->add_subloc(ESTE_GUILD_NAME, this_object());

    if (shadow_who->query_alignment() < 100)
    {
	write("\nServants of Melkor are not allowed in the " +
	  ESTE_GUILD_NAME + ".  If you do not change your ways, you will "+
	  "be expelled.\n\n");
    }
    MEMBER_TRACKER->update_member(shadow_who);

    if (shadow_who->query_login_time() <= file_time(ESTE_NEWS))
    {
	news = 1;
    }
    set_alarm(1.0, 0.0, &get_este_soul(news));
}

/*
 * Are the Valar angry?
 * Well not yet, but soon!
 *
 */
void log_killing(object killed, string whom)
{
    string file, domain;

    file = file_name(environment(query_shadow_who()));
    if((domain = explode(file,"/")[2]) == "SHIRE")
	domain = capitalize(explode(file,"/")[3]);
    write_file(ESTE_KILLS, ctime(time()) + " " +
      query_shadow_who()->query_name() + " killed " +
      killed->query_name() + ", " + LANG_ADDART(whom) + ", in " + domain + ".\n");
    write_file(NPC_KILLS, ctime(time()) + " " +
      query_shadow_who()->query_name() + " killed " +
      killed->query_name() + ", " + LANG_ADDART(whom) + " (" +
      file_name(environment(query_shadow_who())) + ").\n");
}

int
notify_you_killed_me(object killed)
{
    string  killed_race = killed->query_race_name();
    mixed   whom;

    /* you have to do this in case more than one shadow defines the function, Olorin */
    query_shadow_who()->notify_you_killed_me(killed);
    seteuid(getuid(this_object()));

    if (killed->id("_estehilde_eagle_"))
    {
	tell_object(query_shadow_who(),
	  "The Valar do not like for the Eagles that serve "+
	  "you to be slain.  Fear their wrath!\n");
	log_killing(killed, "eagle");
	query_shadow_who()->add_prop("_i_killed_against_valar",1);
	JOINROOM->valar_wrath(query_shadow_who());
    }
    if (killed->id("hobbit"))
    {
	tell_object(query_shadow_who(),
	  "You are not serving the Lords of the West! "+
	  "You should not slay those you're supposed "+
	  "to protect.\n");
	log_killing(killed, "hobbit");
	query_shadow_who()->add_prop("_i_killed_against_valar",1);
	JOINROOM->valar_wrath(query_shadow_who());
    }


    if (killed->id("elf") && (killed->query_alignment() > 0))
    {
	tell_object(query_shadow_who(),
	  "You should not kill the Eldar!\n");
	log_killing(killed, "elf");
	query_shadow_who()->add_prop("_i_killed_against_valar",1);
	JOINROOM->valar_wrath(query_shadow_who());
    }



    if (killed->id("Cityguard") || killed->id("_gondor_guard"))
    {
	tell_object(query_shadow_who(),
	  "You should not go around killing the guardians of the "+
	  "White Tower.\n");
	query_shadow_who()->add_prop("_i_killed_against_valar",1);
	tell_object(query_shadow_who(),
	  "The Valar may take their wrath upon you.\n");
	JOINROOM->valar_wrath(query_shadow_who());
    }
    else if(killed->id("ranger"))
    {
	tell_object(query_shadow_who(),
	  "You can't kill rangers!\n" +
	  "The Valar look upon you with scorning eyes.\n");
	query_shadow_who()->add_prop("_i_killed_against_valar",1);
	log_killing(killed, "ranger");
	JOINROOM->valar_wrath(query_shadow_who());
    }
    else if(killed->id("rohirrim"))
    {
	tell_object(query_shadow_who(),
	  "You should not kill the defenders of the Shire to the south!\n");
	log_killing(killed, "rohirrim");
	JOINROOM->valar_wrath(query_shadow_who());
    }
    return 1;
}
