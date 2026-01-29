#pragma strict_types

inherit "/std/guild/guild_craft_sh";

#include "guild.h"

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <state_desc.h>

#define GUILD_SUBLOC  GUILD_NAME + " subloc"
#define MAX_GUILD_LEVEL 1



/* Prototypes */
void remove_craft_member();

/* 
 * Function name: query_guild_tax_craft
 * Description:   Give the amount of tax the guild charges
 * Returns:       int - The tax amount
 */

int
query_guild_tax_craft() 
{ 
    int tax = GUILD_TAX;

    return tax; 
}


/*
 * Function name: acceptable_member
 * Description:   test to see if the player is an acceptable member of this
 *                guild.
 * Arguments:     object who - the player to test
 * Returns:       0 or a string message saying why the player isn't acceptable
 */
mixed
acceptable_member(object who)
{
    return 0;
}



/*
 * Function name: query_guild_style_craft
 * Description:   return the guild style for this guild
 * Returns:       string - the style
 */
string
query_guild_style_craft()
{
    return GUILD_STYLE;
}

/*
 * Function name: query_guild_name_craft
 * Description:   return the guild's name
 * Returns:       string - the guild name
 */
string
query_guild_name_craft()
{
    return GUILD_NAME;
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

    return 1;
}


/* 
 * Function name: query_guild_not_allow_join_craft
 * Description:	  Check if we allow the player to join another guild.
 * Arguments:     player - the player
 *		  type, style, name - the type, style and name of the
 *			intended guild.
 * Returns:	  1 if we do not allow, else 0
 */
int
query_guild_not_allow_join_craft(object player, string type, string style,
  string name)
{
    /* This checks to make sure that the new guild is not craft */
    if (::query_guild_not_allow_join_craft(player, type, style, name))
	return 1;

    return 0;
}

/* Function name: query_guild_level_craft
 * Description:   What is the member's level within the guild?
 * Returns:	  int - the level
 */

int
query_guild_level_craft()
{
 
   return 0;
}



/*
 * Function name: query_guild_title_craft
 * Description:   Return the member's guild title
 * Returns:       string - the title
 */

string 
query_guild_title_craft()
{
    return 0;
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
	return "sailing";
    }


    return 0;
}



/*
 * Function name: query_guild_trainer_craft
 * Description:   Returns the skill trainers for the guild
 * Returns:       string * - an array of paths to the guild's
 *                trainers.
 */
mixed
query_guild_trainer_craft()
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
 * Function name: init_craft_shadow()
 * Description:   This function is called from autoload_shadow and may
 *                be used to initialize the shadow when it's loaded.
 * Arguments:     The argument string sent to autoload_shadow.
 */
void init_craft_shadow(string arg)
{
    /* delay for a moment so that the player completes all
     * of login before we continue
     */
    set_alarm(1.0, 0.0, init_guild_member);
}

/* 
 * Function name: add_craft_shadow
 * Description:   Shadow an object with this shadow
 * Arguments:     object who - the object to shadow
 * Returns:       as shadow_me in /std/guild/guild_base.c
 */
int add_craft_shadow(object who)
{
    return shadow_me(who, "craft", GUILD_STYLE, GUILD_NAME);
}



/*
 * Function name: remove_craft_member
 * Description:   remove this member from the guild
 */
void
remove_craft_member()
{
    object emblem, who = query_shadow_who();

    /* Remove special skills */ 
    if(who->query_guild_member("Pirate of the Bloodsea"))
    {
        if(who->query_skill(SS_GUILD_SPECIAL_SKILL) > 85)
            who->set_skill(SS_GUILD_SPECIAL_SKILL, 85);
    }
    else if(who->query_guild_member("Bloodsea Minotaurs"))
    {
        if(who->query_skill(SS_GUILD_SPECIAL_SKILL) > 80)
            who->set_skill(SS_GUILD_SPECIAL_SKILL, 80);
    }
    else
        who->remove_skill(SS_GUILD_SPECIAL_SKILL);

    /* Clear the player's guild stat */
    who->clear_guild_stat(SS_CRAFT);

    /* Remove any instances of the guild emblem on the player */
    while (emblem = present(GUILD_EMBLEM_ID, who))
    {
	emblem->remove_object();
    }

    /* Remove the guild soul */
    who->remove_cmdsoul(GUILD_CMDSOUL);
    who->update_hooks();

    /* Remove the guild shadow.  This also resets tax to 0. */
    remove_guild_craft();
}
