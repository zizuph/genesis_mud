/* Hobgoblin marauder layman guild.
 *
 * Started in 1996, dusted off and recoded in 2020.
 *
 * Arman, July 2020
 */

#pragma strict_types

inherit "/std/guild/guild_lay_sh";

#include "guild.h"
#include "/d/Krynn/clubs/warfare/defs.h"

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <state_desc.h>

#define MAX_GUILD_LEVEL 30

static string *hobgob_titles = HOBGOB_TITLES;
static string *gob_titles = GOB_TITLES;
static string *human_titles = HUMAN_TITLES;
static string *monstrous_titles = MONST_TITLES;

/* Prototypes */
void remove_lay_member();

/* 
 * Function name: query_guild_tax_lay
 * Description:   Give the amount of tax the guild charges
 * Returns:       int - The tax amount
 */
int
query_guild_tax_lay() 
{ 
    int tax = GUILD_TAX;

    return tax; 
}

/*
 * Function name: query_guild_style_lay
 * Description:   return the guild style for this guild
 * Returns:       string - the style
 */
string
query_guild_style_lay()
{
    return GUILD_STYLE;
}

/*
 * Function name: query_guild_name_lay
 * Description:   return the guild's name
 * Returns:       string - the guild name
 */
string
query_guild_name_lay()
{
    return GUILD_NAME;
}

public nomask void
check_valid_hobgoblin_race(object who)
{
    if((who->query_race_name() != "hobgoblin") &&
      (who->query_race_name() != "ogre") &&
      (who->query_race_name() != "goblin") &&
      (who->query_race_name() != "orc") &&
      (who->query_race_name() != "drow") &&
      (who->query_race_name() != "human") &&
      (!who->query_wiz_level()) &&
      (!who->query_ghost()))
    {
        who->catch_tell("You are no longer of a race accepted " +
            "by the Raiders of Throtyl!\n");
	set_alarm(1.0, 0.0, remove_lay_member);
    }
}

/* 
 * Function name: query_guild_keep_player
 * Description:   Test if we want to keep the player in the guild.
 * Arguments:     ob - the player.
 * Returns:	  1 if keeping, 0 if not.
 */
int
query_guild_keep_player(object ob)
{
    mixed why;
    string str = query_shadow_who()->query_real_name();

    /* Set an alarm to be sure the proper souls are loaded, then check race. */
    set_alarm(10.0, 0.0, &check_valid_hobgoblin_race(ob));

    return 1;
}

/* 
 * Function name: query_guild_not_allow_join_lay
 * Description:	  Check if we allow the player to join another guild.
 * Arguments:     player - the player
 *		  type, style, name - the type, style and name of the
 *			intended guild.
 * Returns:	  1 if we do not allow, else 0
 */
int
query_guild_not_allow_join_lay(object player, string type, string style,
  string name)
{
    /* This checks to make sure that the new guild is not layman */
    if (::query_guild_not_allow_join_lay(player, type, style, name))
	return 1;

    /* It is an evil aligned guild to join. If alignment goes over neutral
       you can't join and members can't use their special. */
    if (player->query_alignment() > 100)
    {
	player->catch_msg("You don't have a cruel enough nature to be even " +
        "considered a Raider of Throtyl!\n");
	return 1;
    }

    if((player->query_race_name() != "hobgoblin") &&
      (player->query_race_name() != "ogre") &&
      (player->query_race_name() != "goblin") &&
      (player->query_race_name() != "orc") &&
      (player->query_race_name() != "drow") &&
      (player->query_race_name() != "human"))
    {
        player->catch_msg("Only goblinoids, ogres, drow, and evil humans " +
            "are welcome to claim a place amongst the Throtyl Raiders! " +
            "Begone!\n");
        return 1;
    }

    return 0;
}

/* Function name: query_guild_level_lay
 * Description:   What is the member's level within the guild?
 * Returns:	  int - the level
 */
int
query_guild_level_lay()
{
    int layman_stat = min(80, query_shadow_who()->query_stat(SS_LAYMAN));

    // 4,080,000 points of loot donated needed to reach max level, where:
    //    Steel coin    = 1000 points
    //    Platinum coin = 172 points
    //    Gold coin     = 14 points
    //    Silver coin   = 1 point
    // ~23.7k worth of platinum, or 4080 warfare steel coins with a guild
    // stat of 80.  For a guild stat of 1 you'd need 23,000,000 points of
    // loot to max out, which will equate to 133,700 platinum.

    int guild_stat;

    if(shadow_who->query_skill(SS_RAIDERS_LOOT_VALUE) > 0)
       guild_stat = max(0, RAIDERS_STAT_FORMULA(shadow_who));
    else
       guild_stat = 0;

    return MIN(MAX_GUILD_LEVEL, 
              (layman_stat + guild_stat) / RAIDERS_PROGRESSION_MOD);
}


/*
 * Function name: query_guild_title_lay
 * Description:   Return the member's guild title
 * Returns:       string - the title
 */
string 
query_guild_title_lay()
{
    if (query_shadow_who()->query_alignment() > 100)
    {
        string race_desc = query_shadow_who()->query_race_name();
        if(race_desc == "human")
            race_desc = "Marauder";

        return "Morally Conflicted " +capitalize(race_desc)+ 
            " of the Throtyl Raiders";
    }

    if (query_shadow_who()->query_race_name() == "hobgoblin")
    {
        return hobgob_titles[query_guild_level_lay()];
    }

    if (query_shadow_who()->query_race_name() == "goblin")
    {
        return gob_titles[query_guild_level_lay()];
    }

    if (query_shadow_who()->query_race_name() == "human")
    {
        return human_titles[query_guild_level_lay()];
    }

    if (query_shadow_who()->query_race_name() == "drow")
    {
        return human_titles[query_guild_level_lay()];
    }

    return monstrous_titles[query_guild_level_lay()];
}

/* 
 * Function name: query_guild_skill_name
 * Description:   Give a names for the guild's special skills
 * Arguments:     type - the number of the skill
 * Returns:	  0 if no skill of mine, else the string.
 */
mixed
query_guild_skill_name(int type)
{
    if (type == SS_GUILD_SPECIAL_SKILL)
    {
	return "bleeding wound";
    }


    return 0;
}



/*
 * Function name: query_guild_trainer_lay
 * Description:   Returns the skill trainers for the guild
 * Returns:       string * - an array of paths to the guild's
 *                trainers.
 */
mixed
query_guild_trainer_lay()
{
    return ({ GUILD_DIR + "joinroom" });
}

/*
 * Function name: init_guild_member
 * Description:   Add necessary guild items to the player and
 *                do any other kind of initialization necessary.
 */
void
init_guild_member()
{
    object guild_emblem, who = query_shadow_who();

    /* clone the guild emblem and move it to the player */

    setuid();
    seteuid(getuid());

    // Add to warfare system if not already a member.
    if(!IS_CLUB_MEMBER(who))
    {
        CLUB_MANAGER->add_member(who);
        CLUB_MANAGER->set_warfare_army(who, "Free People");
        who->catch_tell("You now maraud the battlefields of Krynn " +
            "for the Free People! You receive a dark steel chit as " +
            "a token of your involvement.\n");
    }

    if (guild_emblem = clone_object(GUILD_EMBLEM))
    {    
	guild_emblem->move(who, 1);
    }

    /* add the guild's soul to the player */
    who->add_cmdsoul(GUILD_CMDSOUL);
    who->update_hooks();

}

/*
 * Function name: init_lay_shadow()
 * Description:   This function is called from autoload_shadow and may
 *                be used to initialize the shadow when it's loaded.
 * Arguments:     The argument string sent to autoload_shadow.
 */
void init_lay_shadow(string arg)
{
    /* delay for a moment so that the player completes all
     * of login before we continue
     */
    set_alarm(1.0, 0.0, init_guild_member);
}

/* 
 * Function name: add_lay_shadow
 * Description:   Shadow an object with this shadow
 * Arguments:     object who - the object to shadow
 * Returns:       as shadow_me in /std/guild/guild_base.c
 */
int add_lay_shadow(object who)
{
    return shadow_me(who, "layman", GUILD_STYLE, GUILD_NAME);
}

/*
 * Function name: remove_lay_member
 * Description:   remove this member from the guild
 */
void
remove_lay_member()
{
    object emblem, who = query_shadow_who();

    /* Remove special skills */ 
    who->remove_skill(SS_GUILD_SPECIAL_SKILL);
    who->remove_skill(SS_RAIDERS_LOOT_VALUE);

    /* Clear the player's guild stat */
    who->clear_guild_stat(SS_LAYMAN);

    /* Remove any instances of the guild emblem on the player */
    while (emblem = present(GUILD_EMBLEM_ID, who))
    {
	emblem->remove_object();
    }

    /* Remove the guild soul */
    who->remove_cmdsoul(GUILD_CMDSOUL);
    who->update_hooks();

    /* Remove the guild shadow.  This also resets tax to 0. */
    remove_guild_lay();
}
