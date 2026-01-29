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
    "Uninitiated Traveller",
    "Errand Runner of the Travellers",
    "Inexperienced Escort of the Travellers",
    "Esteemed Escort of the Travellers",
    "Understudy Wanderer of the Travellers",
    "Rising Wanderer of the Travellers",
    "Learned Wanderer of the Travellers",
    "Hardened Wanderer of the Travellers",
    "Lauded Wanderer of the Travellers",
    "Understudy Explorer of the Travellers",
    "Rising Explorer of the Travellers",
    "Learned Explorer of the Travellers",
    "Hardened Explorer of the Travellers",
    "Lauded Explorer of the Travellers",
    "Understudy Trailblazer of the Travellers",
    "Rising Trailblazer of the Travellers",
    "Learned Trailblazer of the Travellers",
    "Hardened Trailblazer of the Travellers",
    "Lauded Trailblazer of the Travellers",
    "Understudy Surveyor of the Travellers",
    "Rising Surveyor of the Travellers",
    "Learned Surveyor of the Travellers",
    "Hardened Surveyor of the Travellers",
    "Lauded Surveyor of the Travellers",
    "Understudy Cartographer of the Travellers",
    "Rising Cartographer of the Travellers",
    "Learned Cartographer of the Travellers",
    "Hardened Cartographer of the Travellers",
    "Lauded Cartographer of the Travellers",
    "Understudy Talespinner of the Travellers",
    "Rising Talespinner of the Travellers",
    "Learned Talespinner of the Travellers",
    "Hardened Talespinner of the Travellers",
    "Lauded Talespinner of the Travellers",
    "Understudy Historian of the Travellers",
    "Rising Historian of the Travellers",
    "Learned Historian of the Travellers",
    "Understudy Elder of the Travellers",
    "Rising Elder of the Travellers",
    "Learned Elder of the Travellers",
    "Hardened Elder of the Travellers",
    "Lauded Elder of the Travellers",
    "Traveller of Legend",
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


