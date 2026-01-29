/*
* /d/Shire/trickster/trick_shadow.c
*
* This is the shadow of the Trickster layman guild. It is modified from the
   * shadow of the Rockfriend guild.
*
* /Mercade, Rockfriend shadow on 3 November 1993
*
* This shadow:
* /Dunstable, March 23, 1995
*
* Revision history:
*
* Added sneaky functionality, 26 August 1995
* Dunstable
*
* Added mischief functionality for use with 
* the itchpowder, sneezepowder, smokebomb, stinkbomb, and laughgas
*
* Igneous, 12 March 1996
*
* Made the mischief recoverable.
*
* Igneous, August 1996.
*/

#pragma save_binary

inherit "/std/guild/guild_lay_sh";
inherit "/d/Shire/trickster/autosneak.c";
#include "/d/Shire/trickster/titles.h"
#include "/d/Shire/trickster/trickster.h"
#include "/d/Shire/skills.h"
#include <language.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#define QSW      query_shadow_who()
#define JOINROOM (TRICK_DIR + "join")

//   Prototypes
void restore_tricks(string str);
void update_string();

static int sneaky = 1;
//  An array to hold the various charges for itchingpowder etc..
//                    sneeze itch smoke stink laugh
static int *charges = ({   0,   0,   0,   0,   0});

nomask public int
set_sneaky(int val)
{
    sneaky = val;
}

nomask public int
query_sneaky()
{
    return sneaky;
}

nomask public void
clear_charges()
{
    charges = ({0,0,0,0,0});
}

nomask public void
add_charge(int index)
{
    charges[index] += 1;
}

nomask public void
remove_charge(int index)
{
    charges[index] -= 1;
    update_string();
}

nomask public int
query_charge(int index)
{
    return charges[index];
}

nomask public void
set_charges()
{
    int   maxcharges = 15,
    totalcharges, i, guildstat, counter;

    clear_charges();
    guildstat = query_shadow_who()->query_stat(SS_LAYMAN);
    totalcharges = (guildstat/10) + 1;

    if (totalcharges > maxcharges)
	totalcharges = maxcharges;

    counter = 0;
    for (i = 0; i < totalcharges; i++)
    {
	add_charge(counter);
	if (counter < 4)
	    counter += 1;
	else
	    counter = 0;
    }
    update_string();
}

public mixed
query_guild_trainer_lay()
{
    return TRICK_GUILD_TRAINER;
}

/*
 * Function name: query_guild_tax_lay
 * Description  : Returns the tax for the dwarven race guild.
 * Returns      : int - the tax value
 */
nomask public int
query_guild_tax_lay()
{
    return TRICKSTER_GUILD_TAX;
}

/*
 * Function name: query_guild_name_lay
 * Description  : Returns the name of the guild
 * Returns      : string - the name
 */
nomask public string
query_guild_name_lay()
{
    return TRICKSTER_GUILD_NAME;
}

nomask public string
query_guild_style_lay()
{
    return TRICKSTER_GUILD_STYLE;
}

/*
 * Function name: query_rockfriend_level
 * Description  : This function will return the level of the player in this
 *                guild. The level will range from 0 to the number of
 *                titles possible (defined in NUM_TITLES) minus one.
 * Returns      : the level
 */
nomask public int
query_trickster_level()
{
    int level = QSW->query_stat(SS_LAYMAN);

    if (shadow_who->query_wiz_level())
	return NUM_TITLES;
    level = ((level * NUM_TITLES) / MAX_SS_LAYMAN) - 1;

    return ((level >= NUM_TITLES) ? (NUM_TITLES - 1) :
      ((level < 0) ? 0 : level));
}

/*
 * Function name: query_guild_not_allow_join_lay
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
query_guild_not_allow_join_lay(object player, string type, string style,
  string name)
{
    /* It is a redefinition, so call the original. All tests in the
    * guild are made in the joinroom before we allow the player to
    * join.
    */
    return ::query_guild_not_allow_join_lay(player, type, style, name);
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

#ifndef TRICKSTER_NO_ALIGN_RESTRICTION
    /* If the alignment of the player is too high, we kick him/her out.
    */
    if (player->query_alignment() > TRICKSTER_GUILD_ALIGN_MAX)
    {
	JOINROOM->remove_player_high_alignment(player);
	return 1;
    }

    /* If the alignment of the player is too low, we kick him/her out.
    */
    if (player->query_alignment() < TRICKSTER_GUILD_ALIGN_MIN)
    {
	JOINROOM->remove_player_low_alignment(player);
	return 1;
    }
#endif

    /* If the player changed his/her race, we kick him/her out.
    */
    if (player->query_race() == "elf")
    {
	JOINROOM->test_player_changed_race_with_delay(player);
	return 1;
    }

    return 1;
}

/*
 * Function name: query_guild_title_lay
 * Description  : This function will return the title for the Tricksters.
 * Returns      : string - the title.
 */
nomask public string
query_guild_title_lay()
{
    if(query_sneaky())
    {
	return "";
    }

    return TITLES[query_trickster_level()] + " Trickster";
}

/*
 * Function name: show_subloc
 * Description  : This function is called to display the sublocs
 * Arguments    : subloc  - the sublock to check
 *  on_obj  - Whom the subloc is on
 *  for_obj - Who wants to know the subloc
 * Returns      : The string to display
 */
public string
show_subloc(string subloc, object on_obj, object for_obj)
{
    /* Since this is a redefinition, call the original if the call was
       * not meant for us.
    */
    if ((on_obj->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS)) ||
      (subloc != TRICKSTER_GUILD_NAME))
    {
	return QSW->show_subloc(subloc, on_obj, for_obj);
    }
    if (query_sneaky()) return "";

    else
	return (((for_obj == on_obj) ? "You have the rascally look" :
	    (capitalize(on_obj->query_pronoun()) + " has the rascally looks")) +
	  " of a Trickster.\n");
}

public mixed
query_guild_skill_name(int num)
{
    if (num == SS_SET_TRAPS)
	return "set traps";
    if (num == SS_DISGUISE)
	return "disguise";
#ifndef NO_TRICKSTER_SHINKICK
    if (num == SS_SHINKICK)
	return "shinkick";
#endif
}

int
query_guild_incognito_lay()
{
    return query_sneaky();
}

/*
 * Function name: init_lay_shadow
 * Description  : This function is called when a player logs in. It adds
 *                the subloc to the player and make a query to the
 *                joinroom for the family name of the player.
 * Arguments    : string foobar - an init-string if there was any.
 */
nomask public void
init_lay_shadow(string foobar)
{
    string name;

    setuid();
    seteuid(getuid());

    query_shadow_who()->add_subloc(TRICKSTER_GUILD_NAME, this_object());

#ifndef TRICKSTER_NO_ALIGN_RESTRICTION
    if (query_shadow_who()->query_alignment() < -400)
    {
	write("\nWe don't like crusaders in the " +
	  TRICKSTER_GUILD_NAME + ". You should change that attitude " +
	  "before you get too evil for then you are expelled.\n\n");
    }


    if (query_shadow_who()->query_alignment() > 400)
    {
	write("\nWe don't like crusaders in the " +
	  TRICKSTER_GUILD_NAME + ". You should change that attitude " +
	  "before you become too good for then you will be expelled.\n\n");
    }
#endif

    restore_tricks(foobar);
    MEMBER_TRACKER->update_member(shadow_who);
}

void
restore_tricks(string str)
{
    if (!stringp(str))
	return;
    sscanf(str, "##%d,%d,%d,%d,%d##",charges[0],charges[1],charges[2],
      charges[3],charges[4]);
}

void
update_string()
{
    object player = query_shadow_who();

    if (player->query_wiz_level())  // We can't add autoshadows to wizards
	return;
    player->remove_autoshadow(MASTER);
    player->add_autoshadow(MASTER+":"+"##"+charges[0]+","+charges[1]+","+
      charges[2]+","+charges[3]+","+charges[4]+"##");
}
