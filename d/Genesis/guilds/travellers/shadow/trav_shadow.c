/*
 *  The Traveller-guild shadow
 *
 *
 *  Edited by McCram   may/97
 *  added:
 *      leave_travellers()
 * Mona adds start location reset july/97
 *
 * Totally redone and moved to Earthsea by Shiva, August 31, 1997
 */

#pragma strict_types
#pragma save_binary

inherit "/std/guild/guild_race_sh";

#include "guild.h"
#include <ss_types.h>
#include <language.h>
#include <const.h>
#include <stdproperties.h>

#define SW shadow_who

static string *titles = ({
  "New Initiate of the Travellers",
  "Dawdling Straggler of the Travellers",
  "Distracted Tourist of the Travellers",
  "Inexperienced Escort of the Travellers",
  "Resolute Pioneer of the Travellers",
  "Inquisitive Inquirer of the Travellers",
  "Incisive Interrogator of the Travellers",
  "Roaming Errand Runner of the Travellers",
  "Adventurous Courier of the Travellers",
  "Cautious Tracker of the Travellers",
  "Furtive Scout of the Travellers",
  "Meandering Rambler of the Travellers",
  "Curious Wayfarer of the Travellers",
  "Excited Pilgrim of the Travellers",
  "Impulsive Gadabout of the Travellers",
  "Eager Ambler of the Travellers",
  "Inspired Peregrinator of the Travellers",
  "Energetic Wanderer of the Travellers",
  "Sure Footed Rover of the Travellers",
  "Arduous Trekker of the Travellers",
  "Enthusiastic Explorer of the Travellers",
  "Spirited Voyager of the Travellers",
  "Avid Mountaineer of the Travellers",
  "Impetuous Itinerant of the Travellers",
  "Enterprising Excursionist of the Travellers",
  "Ardent Adventurer of the Travellers",
  "Courageous Daredevil of the Travellers",
  "Sharp Witted Navigator of the Travellers",
  "Vivacious Pathfinder of the Travellers",
  "Zealous Trailblazer of the Travellers",
  "Incessant Surveyor of the Travellers",
  "Scampering Sketcher of the Travellers",
  "Magniloquent Mapmaker of the Travellers",
  "Calculating Cartographer of the Travellers",
  "Whimsical Whittler of the Travellers",
  "Encrypting Engraver of the Travellers",
  "Skilled Carver of the Travellers",
  "Industrious Sculpturer of the Travellers",
  "Animated Storyteller of the Travellers",
  "Irrepressible Talespinner of the Travellers",
  "Scholarly Scribe of the Travellers",
  "Admired Historian of the Travellers",
  "Irrefutable Antiquarian of the Travellers",
  "Esteemed Elder of the Travellers",
  "Venerable Traveller of Legend",
});


int leave_travellers();

private mixed stat_names, title, badge;

/*
 * Function name: query_guild_tax
 * Description  : Set the initial tax
 */
nomask int
query_guild_tax_race()
{
    return GUILD_TAX;
}

nomask mixed
query_guild_trainer_race()
{
    return TRAVELLERS_ROOM_DIR + "train";
}

/*
 * Function name: acceptable_member
 * Description:   test to see if the player is an acceptable member of this
 *                guild.
 * Arguments:     object who - the player to test
 * Returns:       0 or a string message saying why the player isn't acceptable
 */
nomask mixed
acceptable_member(object who)
{
    /* throw out goblins */
    if ((who->query_race() != "human") && (who->query_race() != "ghost"))
    {
	return "You're not human!\n";
    }

    return 0;
}

/* Function name: query_guild_keep_player
 * Description:   Test if we want to keep the player in the guild.
 *                If we discover a fighter or thief, we will throw
 *                him out
 * Arguments:     ob - the player.
 * Returns:       1 if keeping, 0 if not.
 */
int
query_guild_keep_player(object ob)
{
    mixed why;

    if (stringp(why = acceptable_member(ob)))
    {
	tell_object(ob, why);
	set_alarm(2.0,0.0, leave_travellers);
    }

    return 1;
}

/* Function name: query_traveller_level
 * Description:   Get the players numerical guild level
 * Returns:       The numeric guild level
 */
int
query_traveller_level()
{
    return SW->query_base_stat(SS_RACE) * 4 / 9;
}

string
get_title(mixed title, int gender)
{
    if (!pointerp(title))
    {
	return title;
    }

    return title[((gender == G_MALE) ? 0 : 1)];
}

/* Function name: query_guild_title_race
 * Description:   We change the title of our members depending on their level
 * Returns:       The title
 */
string query_guild_title_race()
{
    int stat;
    mixed title;

    setuid();
    seteuid(getuid());

    if (COUNCIL_MEMBER(shadow_who->query_real_name()))
    {
	return "Supreme Traveller of the Realms";
    }

    if (!sizeof(titles))
    {
	return "";
    }

    stat = min(sizeof(titles) - 1, query_traveller_level());

    title = titles[stat];

    return get_title(title, SW->query_gender());
}

string *
query_male_titles()
{
    return map(titles, &get_title(, G_MALE));
}

string *
query_female_titles()
{
    return map(titles, &get_title(, G_FEMALE));
}

/*
 * Function name: query_guild_style_race
 * Description:   Get the style of this guild
 * Returns:       String describing guild style
 */
string
query_guild_style_race()
{
    return GUILD_STYLE;
}

/*
 * Function name: query_guild_name_race
 * Description:   Get the name of this guild
 * Returns:       String naming guild
 */
string
query_guild_name_race()
{
    return GUILD_NAME;
}

int
leave_travellers()
{
    SW->catch_tell("You are no longer a member of the Travellers Guild.\n");

    setuid();
    seteuid(getuid());

    SW->remove_cmdsoul(TRAVELLERS_SOUL);
    SW->update_hooks();

    SW->clear_guild_stat(SS_RACE);

    filter(deep_inventory(SW), &wildmatch(TRAVELLERS_GUILD_EMBLEM + "*") @
      file_name)->remove_object();

    if (SW->query_default_start_location() == TRAVELLERS_STARTLOC)
    {
	SW->set_default_start_location(SW->query_def_start());
    }

    log_file("travellers", capitalize(SW->query_real_name()) + 
      " left " + ctime(time()) + "\n");

    remove_guild_race();
}

void 
init_traveller()
{
    setuid();
    seteuid(getuid());

    if (!sizeof(filter(deep_inventory(SW), 
	  &->id(TRAVELLERS_GUILD_EMBLEM_ID))))
    {
	clone_object(TRAVELLERS_GUILD_EMBLEM)->move(SW, 1);
    }

    SW->add_cmdsoul(TRAVELLERS_SOUL);
    SW->update_hooks();
}

void
init_race_shadow(string arg)
{
    set_alarm(1.0, 0.0, init_traveller);
}

int add_race_shadow(object who)
{
    return shadow_me(who, "race", GUILD_STYLE, GUILD_NAME);
}


