/*                          The Grunt Shadow.                              */
/*    The shadow gives you a lovely new title when you join the guild.     */
/*    Based on code from Quis, Tricky, Nick, Uncle Tom Cobley and all.     */
/*    Bodged together 25/3/1993 by Tulix I.                                */
/*    Kat 3-3-94 fixed the title to conform with query_guild_title_race()  */
/*    Recoded 19/08/95 by Tulix III.                                       */
/*    Fixed title performance Cotillion, 31/03/10                          */

inherit "/std/guild/guild_race_sh";

#include <ss_types.h>
#include <macros.h>
#include <math.h>
#include "../guild.h"

#define SW shadow_who
#define BUGGY 0

/* ************************************************************************
 * Define the array of guild titles.
 */

#define GRUNTS_SMELLS ({ "Slightly Perfumed", "Perfumed", "Very Perfumed" \
      , "Highly Perfumed", "Slightly Aromatic", "Aromatic", "Very Aromatic" \
      , "Highly Aromatic", "Slightly Fragranced", "Fragranced" \
      , "Very Fragranced", "Highly Fragranced", "Slightly Musty" \
      , "Musty", "Very Musty", "Highly Musty", "Slightly Sour" \
      , "Sour", "Very Sour", "Highly Sour", "Slightly Offensive" \
      , "Offensive", "Very Offensive", "Highly Offensive" \
      , "Slightly Odoriferous", "Odoriferous", "Very Odoriferous" \
      , "Highly Odoriferous" \
      , "Slightly Malodorous", "Malodorous", "Very Malodorous" \
      , "Highly Malodorous", "Slightly Smelly", "Smelly" \
      , "Very Smelly", "Highly Smelly", "Slightly Stinking" \
      , "Stinking", "Strongly Stinking", "Highly Stinking" \
      , "Slightly Nauseating", "Nauseating" , "Very Nauseating" \
      , "Highly Nauseating", "Slightly Rank", "Rank" \
      , "Very Rank", "Highly Rank", "Slightly Fetid" \
      , "Fetid", "Very Fetid", "Highly Fetid" \
      , "Slightly Rancid", "Rancid", "Very Rancid", "Highly Rancid" \
      , "Slightly Putrid", "Putrid", "Very Putrid" \
      , "Highly Putrid", "Slightly Noxious", "Noxious" \
      , "Very Noxious", "Highly Noxious", "Slightly Toxic" \
      , "Toxic", "Very Toxic", "Highly Toxic", "Lethal" })

/* Globals */
static string *smells = GRUNTS_SMELLS;

/* Prototype functions */
public int query_grunts_level();
void remove_grunts_member();
public void delay_init_grunt();

/* ************************************************************************                  
 * Set the tax for our smelly little guild.
 */
public int
query_guild_tax_race()
{
    return GUILD_TAX;
}

/* ************************************************************************
 * Get the players guild level. This is based on STR, DEX, CON.
 */
public int
query_grunts_level()
{
    int kills, stats, level;
    
    kills = shadow_who->query_skill(GRUNT_KILLS_COUNT);
    
    stats = shadow_who->query_base_stat(SS_STR) +
            shadow_who->query_base_stat(SS_DEX) +
            shadow_who->query_base_stat(SS_CON);

    level = SQUARE_ROOT(kills) / 2 + SQUARE_ROOT(stats); /* This may change */

    return (level);
}

/* ************************************************************************
 * Give the player a title that is dependent on their level.
 */
public string
query_guild_title_race()
{
  return smells[max(0, min(sizeof(smells) - 1,
			   query_grunts_level()))] + " Grunt";
}

/* ************************************************************************
 * Get the style of the guild.
 */

public string
query_guild_style_race()
{
    return GUILD_STYLE;
}

/* ************************************************************************
 * Get the name of the guild. 
 */
public string
query_guild_name_race()
{
    return GUILD_NAME;
}

#ifdef GUILD_POST
string
query_def_post()
{
    if (this_player()->query_default_start_location() == GUILD_STARTLOC)
    {
        return GUILD_POST;
    }

    return SW->query_def_post();
}
#endif

mixed
acceptable_grunts_member(object player)
{
    if ((player->query_race() != "goblin") && !player->query_wiz_level())
    {
        return "You are not a goblin!  You cannot be a Grunt!\n";
    }

    return 0;
}
    
int 
query_guild_keep_player(object player)
{
    mixed why;

    if (stringp(why = acceptable_grunts_member(player)))
    {
        set_alarm(0.5, 0.0, &tell_object(SW, why));
        set_alarm(1.0, 0.0, remove_grunts_member);
    }

    if (BUGGY)
        SW->catch_msg("Member kept....\n");

    return 1;
}

/* ************************************************************************
 * Update kill count when the player kills something. 
 */
public void
notify_you_killed_me(object victim)
{
    int kills;
    object collar;

    shadow_who->notify_you_killed_me(victim);

    collar = present("grunts_collar", shadow_who);
    if (collar)
    {
        kills = shadow_who->query_skill(GRUNT_KILLS_COUNT) + 1;
        shadow_who->set_skill(GRUNT_KILLS_COUNT, kills);


        shadow_who->catch_tell("You grunt happily, and record your " +
            "victory by adding a notch to your collar.\n");

        tell_room(environment(shadow_who), QCTNAME(shadow_who) + " grunts happily, " +
            "recording the victory with a notch on " + 
            shadow_who->query_possessive() + " collar.\n", shadow_who);
    }
    else
    {
        shadow_who->catch_tell("You grunt happily at your victory.\n");

        tell_room(environment(shadow_who), QCTNAME(shadow_who) + " grunts happily " +
            "at the victory.\n", shadow_who);
    }

    return;
}

public void
delay_init_grunt()
{
    object collar;

    SW->add_cmdsoul(GRUNTS_GUILD_SOUL);
    SW->update_hooks();

    if (BUGGY)
        SW->catch_msg("Soul added...\n");

    setuid();
    seteuid(getuid());
    if (BUGGY)
        SW->catch_msg("Uid & euid set...\n");
 
    collar = clone_object(GUILD_OBJECT);
    if (BUGGY)
        SW->catch_msg("Collar cloned...\n");
    collar->move(SW);
    if (BUGGY)
        SW->catch_msg("Collar moved to member...\n");
}

void
init_race_shadow(string arg)
{
    set_alarm(1.0, 0.0, delay_init_grunt);
}

varargs int
add_grunts_shadow(object who)
{
    return shadow_me(who, "race", "fighter", GUILD_NAME);
}

void
remove_grunts_member()
{
#ifdef GRUNT_KILLS_COUNT
    SW->remove_skill(GRUNT_KILLS_COUNT);
#endif

    SW->clear_guild_stat(SS_RACE);
    remove_guild_race();
}

string
full_adverb(string str)
{
    string adverb;

    setuid();
    seteuid(getuid());

    if (strlen(adverb = ADVERB_MANAGER->full_adverb(str)))
    {
        return adverb;
    }

    return SW->full_adverb(str);
}
