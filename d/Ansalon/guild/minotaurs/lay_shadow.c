#pragma strict_types

inherit "/std/guild/guild_lay_sh";

#include "guild.h"

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <state_desc.h>

#include "special_attacks.c"

#define GUILD_SUBLOC  GUILD_NAME + " subloc"
#define MAX_GUILD_LEVEL 11


static string *titles = ({"Yearling of the Bloodsea Minotaurs",
  "Maverick of the Bloodsea Minotaurs",
  "Antagonist of the Bloodsea Minotaurs",
  "Scrapper of the Bloodsea Minotaurs",
  "Assailant of the Bloodsea Minotaurs",
  "Challenger of the Bloodsea Minotaurs",
  "Challenger of the Bloodsea Minotaurs",
  "Challenger of the Bloodsea Minotaurs",
  "Minotaur Champion of the Bloodsea Isles",
  "Minotaur Champion of the Bloodsea Isles",
  "Minotaur Champion of the Bloodsea Isles",
  "Warrior of the Bloodsea Minotaurs, Champion of the Isles",});



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
check_valid_minotaur_race(object who)
{
    if((who->query_race_name() != "minotaur") &&
      (!who->query_wiz_level()) &&
      (!who->query_ghost()))
    {
        who->catch_tell("You are no longer a minotaur!\n");
	set_alarm(1.0, 0.0, remove_lay_member);
    }
}

public mixed acceptable_member(object player)
{
    if (player->query_race_name() != "minotaur")
    {
        return "You are not a minotaur!";
    }
    return 0;
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
    set_alarm(10.0, 0.0, &check_valid_minotaur_race(ob));

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

    /* We don't want our members joining thief guilds */
    if (style == "thief")
    {
	player->catch_msg("Minotaurs are honourable and strong! They do not " +
       "stoop to skulking like thieves! What they want they take over the " +
       "corpses of their foes!\n");
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
    return MIN(MAX_GUILD_LEVEL, query_shadow_who()->query_stat(SS_LAYMAN) /10);
}


string
query_str_title()
{
    int str_lvl = query_shadow_who()->query_stat(SS_STR);

    if(str_lvl >= 210)
      return "Fabled";
    if(str_lvl >= 185)
      return "Supreme";
    if(str_lvl >= 165)
      return "Elite";
    if(str_lvl >= 150)
      return "Titanic";
    if(str_lvl >= 138)
      return "Mighty";
    if(str_lvl >= 126)
      return "Crushing";
    if(str_lvl >= 114)
      return "Forceful";
    if(str_lvl >= 102)
      return "Ironlike";
    if(str_lvl >= 90)
      return "Musclebound";
    if(str_lvl >= 79)
      return "Powerful";
    if(str_lvl >= 68)
      return "Strong";
    if(str_lvl >= 58)
      return "Hefty";
    else
      return "Immature";


}


/*
 * Function name: query_guild_title_lay
 * Description:   Return the member's guild title
 * Returns:       string - the title
 */
string 
query_guild_title_lay()
{
    return query_str_title() + " " +titles[query_guild_level_lay()];
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
	return "gore";
    }

    if (type == SS_SAILING_SKILL)
    {
        return "sailing";
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

    if(who->query_guild_name_craft() != "Mariners of Genesis")
        who->remove_skill(SS_SAILING_SKILL);

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
