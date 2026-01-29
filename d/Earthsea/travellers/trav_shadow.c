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
 * Added Zhar's nifty new title prefixes, Gorboth, March 25, 2014
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

private static string *titles = ({
    "Uninitiated Traveller",
    "Errand Runner of the Travellers",
    "Inexperienced Courier of the Travellers",
    "Dependable Courier of the Travellers",
    "Inquisitive Wanderer of the Travellers",
    "Eager Wanderer of the Travellers",
    "Ambitious Wanderer of the Travellers",
    "Vigorous Wanderer of the Travellers",
    "Spirited Wanderer of the Travellers",
    "Adventurous Explorer of the Travellers",
    "Intrepid Explorer of the Travellers",
    "Daring Explorer of the Travellers",
    "Audacious Explorer of the Travellers",
    "Gallant Explorer of the Travellers",
    "Determined Trailblazer of the Travellers",
    "Resolute Trailblazer of the Travellers",
    "Stalwart Trailblazer of the Travellers",
    "Tenacious Trailblazer of the Travellers",
    "Dauntless Trailblazer of the Travellers",
    "Rising Surveyor of the Travellers",
    "Capable Surveyor of the Travellers",
    "Skilled Surveyor of the Travellers",
    "Experienced Surveyor of the Travellers",
    "Gifted Surveyor of the Travellers",
    "Competent Cartographer of the Travellers",
    "Proficient Cartographer of the Travellers",
    "Adept Cartographer of the Travellers",
    "Talented Cartographer of the Travellers",
    "Brilliant Cartographer of the Travellers",
    "Acclaimed Talespinner of the Travellers",
    "Eminent Talespinner of the Travellers",
    "Renowned Talespinner of the Travellers",
    "Celebrated Talespinner of the Travellers",
    "Illustrious Talespinner of the Travellers",
    "Studious Historian of the Travellers",
    "Cultivated Historian of the Travellers",
    "Sage Historian of the Travellers",
    "Prominent Elder of the Travellers",
    "Respectable Elder of the Travellers",
    "Distinguished Elder of the Travellers",
    "Venerable Elder of the Travellers",
    "Hallowed Elder of the Travellers",
    "Traveller of Legend",
});


public int leave_travellers();

private mixed stat_names, title, badge;

/*
 * Function name: query_guild_tax
 * Description  : Set the initial tax
 */
public nomask int
query_guild_tax_race()
{
    return GUILD_TAX;
}

public nomask mixed
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
public nomask mixed
acceptable_member(object who)
{
    /* throw out goblins */
    if(!who->query_wiz_level() && (who->query_race() != "human" &&
        who->query_race() != "ghost"))
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
public int
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
public int
query_traveller_level()
{
    return SW->query_base_stat(SS_RACE) * 4 / 9;
}

public string
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
public string
query_guild_title_race()
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

public string *
query_male_titles()
{
    return map(titles, &get_title(, G_MALE));
}

public string *
query_female_titles()
{
    return map(titles, &get_title(, G_FEMALE));
}

/*
 * Function name: query_guild_style_race
 * Description:   Get the style of this guild
 * Returns:       String describing guild style
 */
public string
query_guild_style_race()
{
    return GUILD_STYLE;
}

/*
 * Function name: query_guild_name_race
 * Description:   Get the name of this guild
 * Returns:       String naming guild
 */
public string
query_guild_name_race()
{
    return GUILD_NAME;
}

public int
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

    TRAVELLERS_MANAGER->remove_council_member(SW->query_real_name());

    log_file("travellers", capitalize(SW->query_real_name()) + 
        " left " + ctime(time()) + "\n");

    remove_guild_race();
}

public void 
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

public void
init_race_shadow(string arg)
{
    set_alarm(1.0, 0.0, init_traveller);
}

public int
add_race_shadow(object who)
{
    return shadow_me(who, "race", GUILD_STYLE, GUILD_NAME);
}

public void
remove_race_shadow()
{
    remove_shadow();
}
