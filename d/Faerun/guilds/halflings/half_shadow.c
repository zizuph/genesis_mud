/*
 * half_shadow.c
 * Shadow of the Halflings guild.
 * Modified from the orc guild in the shire
 * Finwe, september 2015
 */

// To test:
// Call *yourname add_autoshadow full/path/name

#pragma save_binary
#pragma strict_types

inherit "/std/guild/guild_race_sh";
inherit "/lib/guild_support";

#include "/d/Faerun/defs.h"
#include "halflings.h"
#include <language.h>
#include <stdproperties.h>
#include <ss_types.h>

#define JOINROOM (HALFGLD_DIR + "rm_join")

#define RACE    " Halfling"
private static string *titles = ({
    "Inquisitive" + RACE + " Scout", 
    "Daring" + RACE + " Scout", 
    "Brave" + RACE + " Scout", 
    "Curious" + RACE + " Explorer", 
    "Plucky" + RACE + " Explorer", 
    "Confident" + RACE + " Explorer", 
    "Quizzical" + RACE + " Wayfarer", 
    "Intrepid" + RACE + " Wayfarer", 
    "Unafraid" + RACE + " Wayfarer", 
    "Spunky" + RACE + " Wayfarer", 
    "Curious" + RACE + " Knockabout", 
    "Daring" + RACE + " Knockabout", 
    "Brave" + RACE + " Knockabout", 
    "Defiant" + RACE + " Knockabout", 
    "Curious" + RACE + " Perigrinator", 
    "Confident" + RACE + " Perigrinator", 
    "Stout-Hearted" + RACE + " Perigrinator", 
    "Stalwart" + RACE + " Perigrinator", 
    "Valiant" + RACE + " Perigrinator", 
    "Inquisitive" + RACE + " Vagabond", 
    "Gutsy" + RACE + " Vagabond", 
    "Unafraid" + RACE + " Vagabond", 
    "Defiant" + RACE + " Vagabond", 
    "Unfearing" + RACE + " Vagabond", 
    "Nosey" + RACE + " Gadabout", 
    "Intrepid" + RACE + " Gadabout",
    "Courageous" + RACE + " Gadabout", 
    "Spunky" + RACE + " Gadabout", 
    "Determined" + RACE + " Gadabout", 
    "Reckless" + RACE + " Gadabout", 
    "Well Travelled" + RACE,
    "Renowned"+ RACE, 
    "Famed"+ RACE, 
    "Fabulous"+ RACE, 
    "Heroic"+ RACE, 
    "Epic"+ RACE, 
    "Legendary"+ RACE, 
    "Mythic"+ RACE,
});

nomask public void 
set_food_alarm (float min);

// food flag. if set to 1, initial alarm expired and ok to find food.
static int food_flag;


/*
 * Function name:   log_guild
 * Description:     This function logs some actions of members of the guild.
 *                  It uses a larger cycle than basically coded.
 * Arguments:       string text - the message to log.
*/
nomask private void 
log_guild(string text)
{
    setuid();
    seteuid(getuid());

    if (file_size(GUILD_LOG) > LOG_SIZE)
    {
        rename(GUILD_LOG, (GUILD_LOG + ".old"));
    }

    write_file(GUILD_LOG, text);
}

/*
 * Function name:   query_guild_tax_race
 * Description:     Returns the tax for the Noldor race guild.
 * Returns:         int - the tax value
*/

nomask public int 
query_guild_tax_race()
{
    return GUILD_TAX;
}

/*
 * Function name:   query_guild_name_race
 * Description:     Returns the name of the guild
 * Returns:         string - the name
 */
nomask public string 
query_guild_name_race()
{
    return GUILD_NAME;
}

/*
 * Function name:   query_guild_not_allow_join_race
 * Description  :   Returns whether we should allow this player to join another
 *                  guild if he wants to.
 * Arguments    :   player - the player that wants to join
 *                  type   - the type of the guild
 *                  style  - the styles of the guild
 *                  name   - the name of the guild
 * Returns      :   1 - if the player is rejected
 *                  0 - if the player is accepted as a member
 */
nomask public int 
query_guild_not_allow_join_race(object player, string type, string style, string name)
{
/*
 * It is a redefinition, so call the original. All tests in the
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
public int 
query_guild_keep_player(object player)
{
    setuid();
    seteuid(getuid());

// If the player changed is no longer a hobbit, they get kicked out.
    if (player->query_race() != "hobbit")
    {
        call_other(JOINROOM, "remove_player_changed_race", player);

        return 0;
    }
/*
 * we dont check for alignment
 */

/*
    // If the alignment of the player is too low, we kick him/her out.
    if (player->query_alignment() > GUILD_ALIGN)
    {
        call_other(JOINROOM, "remove_player_high_alignment", player);
        return 0;
    }
*/
    return 1;
}

/*
 * Function name:   get_halfling_soul
 * Description  :   Gets the halfling soul and guild item for the player.
 * Arguments    :   int news - a flag used to tell if there is new news
 *                  relating to the guild
 */
void 
get_halfling_soul(int news)
{
    setuid();
    seteuid(getuid());

    if (news)
    {
        shadow_who->catch_tell("\n\nThere is some news about the Halflings. " +
            "See 'help halfling news' for more information.\n\n");
    }

	shadow_who->add_cmdsoul(GUILD_SOUL);
	shadow_who->update_hooks();
    shadow_who->set_race_name("halfling");
}

// returns the status if players can search for food or not. 0 = no, 1 = yes
// This is set after set_food_alarm() is complete
public int
query_food_flag()
{
    return food_flag;
}

// the food flag is set here after set_food_alarm() is complete.
// 0 = no, 1 = yes
public int
set_food_flag(int num)
{
    food_flag = num;
    return 1;
}

nomask public void
set_food_alarm (float min)
{
    set_alarm(min, 0.0, &set_food_flag(1));   
}

/*
 * Function name:   init_race_shadow
 * Description  :   This function is called when a player logs in. It adds
 *                  the subloc to the player and make a query to the
 *                  joinroom for the family name of the player.
 * Arguments    :   string foobar - an init-string if there was any.
 */
nomask public void 
init_race_shadow(string foobar)
{
	setuid();
	seteuid(getuid());
// test time
// float alarm_time = itof(30);

// player must wait this long when they first log in before they 
// execute the special.
    float alarm_time = itof(15 + random(10) * 60);

	shadow_who->add_subloc(GUILD_NAME, this_object());

    set_alarm(1.0, 0.0, &get_halfling_soul());
    set_food_alarm(alarm_time);
}

public string
race_sound()
{
    return "chatters";
}

public string
actor_race_sound()
{
    return "chatter";
}

/* Function name: query_traveller_level
 * Description:   Get the players numerical guild level
 * Returns:       The numeric guild level
 */
public int
query_traveller_level()
{
    return shadow_who->query_base_stat(SS_RACE) / 3;
}

/*
 * Function name: query_guild_family_name
 * Description  : If the guild consists of families that give their members
 *                a family name, this function should return true. It
 *                moves the article 'the' to the occupational title of
 *                the member giving:
 *                "<race title>, the <occ title> and <lay title>"
 *                if the player is a member of all major guild types.
 * Returns      : int - true if the function query_guild_title_race()
 *                      returns the family name and not a normal guild
 *                      title.
 */
public int
query_guild_family_name()
{
    string surname = SURNAME_MANAGER->query_halfling_surname(shadow_who);

    if(surname)
      return 1;
    else
      return 0;
}


/* Function name: query_guild_title_race
 * Description:   We change the title of our members depending on their level
 * Returns:       The title
 */
public string
query_guild_title_race()
{
   int stat;
   mixed title;

   string surname = SURNAME_MANAGER->query_halfling_surname(shadow_who);

   setuid();
   seteuid(getuid());

   if (!sizeof(titles))
   {
       return "";
   }

   stat = min(sizeof(titles) - 1, query_traveller_level());

   if(surname)
   {
      title = capitalize(surname) + ", the " + titles[stat];
   }
   else
   {
      title = titles[stat];
   }

   return title;
}

public string
query_guild_trainer_race()
{
    return (HALFGLD_DIR + "rm_train");
}
