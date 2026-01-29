// To test:
// Call *yourname add_autoshadow full/path/name

#pragma save_binary
#pragma strict_types

inherit "/std/guild/guild_race_sh";
#include "sindar_racial.h"
#include <language.h>
#include <stdproperties.h>
#include <ss_types.h>

#define HERALD_KILLS "/d/Shire/guild/sindar_racial/log/sindarkill"
#define NPC_KILLS "/d/Shire/guild/sindar_racial/log/sindarnpckill"
#define QSW      query_shadow_who()
#define JOINROOM (SINDAR_RACE_DIR + "join_rm")


/*
 * Global variable. It contains the family name of the player.
 */
private string family_name = "of the Sindar of Mithlond";

public mixed
query_guild_trainer_race()
{
    return SINDAR_RACE_GUILD_TRAINER;
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
 * Description  : Returns the tax for the Noldor race guild.
 * Returns      : int - the tax value
 */
nomask public int
query_guild_tax_race()
{
    return SINDAR_RACE_GUILD_TAX;
}

/*
 * Function name: query_guild_name_race
 * Description  : Returns the name of the guild
 * Returns      : string - the name
 */
nomask public string
query_guild_name_race()
{
    return SINDAR_RACE_GUILD_NAME;
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
    return ("/d/Shire/bree/rooms/town/post");
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
    if (player->query_race() != "elf")
    {
	call_other(JOINROOM, "remove_player_changed_race", player);
	return 0;
    }
    // If the alignment of the player is too low, we kick him/her out.
    if (player->query_alignment() <= SINDAR_RACE_GUILD_ALIGN)
    {
	call_other(JOINROOM, "remove_player_low_alignment", player);
	return 0;
    }
/*  disable game booting of players for now. is this booting
    players from the guild when they die? doesn't affect jr chars
    though, only mortals.
*/
/*
    if(!JOINROOM->query_is_member(player->query_real_name()))
    {
        call_other(JOINROOM, "remove_player_inactive", player);
        return 0;
    }
*/
    return 1;
}

/*
 * Function name: query_guild_title_race
 * Description  : This function will return the title for the Noldor.
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
      (subloc != SINDAR_RACE_GUILD_NAME))
    {
	return QSW->show_subloc(subloc, on_obj, for_obj);
    }

    return (((for_obj == on_obj) ? "You are" :
	(capitalize(on_obj->query_pronoun()) + " is")) +
      " surrounded by a glowing aura of light.\n");
}


/*
 * Function name: get_sindar_race_soul
 * Description  : Gets the sindar soul and guild item for the player.
 * Arguments    : int news - a flag used to tell if there is new news
 *                relating to the guild
 */
void
get_sindar_race_soul(int news)
{
    if (news)
    shadow_who->catch_tell("\n\nThere is some news about the "+
          SINDAR_RACE_GUILD_NAME+". See 'help sindar news' " +
          "for more information.\n\n");
    setuid(); seteuid(getuid());
    shadow_who->add_cmdsoul(SINDAR_RACE_GUILD_SOUL);
    shadow_who->update_hooks();
    shadow_who->set_race_name("grey-elf");
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

    shadow_who->add_subloc(SINDAR_RACE_GUILD_NAME, this_object());
// make the elves look like the picture of perfection
     shadow_who->set_appearance_offset(-50);

    if (shadow_who->query_login_time() <= file_time(SINDAR_RACE_NEWS))
    {
	news = 1;
    }
    set_alarm(1.0,0.0,&get_sindar_race_soul(news));
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
    write_file(HERALD_KILLS, ctime(time()) + " " +
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

    if (killed->id("_herald_eagle_"))
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
	  "Mithrandir has asked us to watch over the Little People. " +
      "Killing them is not tolerated.\n");
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
	  "The Guardians of the White Tower are defending against " +
      "the Nameless One. Do not kill them!\n");
	query_shadow_who()->add_prop("_i_killed_against_valar",1);
//	tell_object(query_shadow_who(),
//	  "Your foolishness may cost you.\n");
	JOINROOM->valar_wrath(query_shadow_who());
    }
    else if(killed->id("ranger"))
    {
	tell_object(query_shadow_who(),
	  "How dare you kill the Dunedain!.\n");
	query_shadow_who()->add_prop("_i_killed_against_valar",1);
	log_killing(killed, "ranger");
	JOINROOM->valar_wrath(query_shadow_who());
    }
    else if(killed->id("rohirrim"))
    {
	tell_object(query_shadow_who(),
	  "Don't go killing allies of the White Tower!\n");
	log_killing(killed, "rohirrim");
	JOINROOM->valar_wrath(query_shadow_who());
    }
    return 1;
}
