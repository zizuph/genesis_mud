/* 
 *  /d/Sparkle/guilds/new_merc/occ_shadow.c
 *
 *  This is the guild shadow for the new Mercenary Guild.
 *
 *  Created 2008-2009 by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/guild/guild_occ_sh";

#include "../merc_defs.h"

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#define GUILD_SUBLOC  GUILD_NAME + " subloc"
#define MAX_GUILD_LEVEL 2
#define BETA_TESTERS   ({ "madmartigan", "azalin", "amberlee", "gorbyjr", \
                          "porter" })

#define SW shadow_who

/* Global Variables */
static string  *Merc_Gs_Titles =({
                                   "Newcomer",
                                   "Rookie",
                                   "Initiate",
                                   "Hireling",
                                   "Blade for Hire",
                                   "Professional", 
                                   "Specialist", 
                                   "Veteran", 
                                   "Savant",  
                                   "Soldier of Fortune",  
                                   "Weaponmaster for Hire", 
                                   "Battle Authority",
                                   "Warlord of Fortune",
                                 });
static string  *F_Merc_Gs_Titles =({
                                   "Newcomer",
                                   "Rookie",
                                   "Initiate",
                                   "Hireling",
                                   "Blade for Hire",
                                   "Professional", 
                                   "Specialist", 
                                   "Veteran", 
                                   "Savant",  
                                   "Soldier of Fortune",  
                                   "Weaponmistress for Hire", 
                                   "Battle Authority",
                                   "Warlady of Fortune",
                                 });
static string  *Merc_Ad_Titles =({
                                   "Untalented",
                                   "Fairly Limited",
                                   "Somewhat Resourceful",
                                   "Resourceful",
                                   "Well-Rounded",
                                   "Extremely Well-Rounded", 
                                   "Versatile", 
                                   "Highly Versatile", 
                                   "Exceptionally Versatile",  
                                   "Supremely Adaptable",  
                                   "Limitless", 
                                 });

/* Prototypes */
void remove_occ_member();

public string *   query_gs_titles()   { return Merc_Gs_Titles;   }
public string *   query_f_gs_titles() { return F_Merc_Gs_Titles; }
public string *   query_ad_titles()   { return Merc_Ad_Titles;   }


/* 
 * Function name: query_guild_tax_occ
 * Description:   Give the amount of tax the guild charges
 * Returns:       int - The tax amount
 */
int
query_guild_tax_occ() 
{ 
    return GUILD_TAX; 
} /* query_guild_tax_occ */


/*
 * Function name: query_guild_style_occ
 * Description:   return the guild style for this guild
 * Returns:       string - the style
 */
string
query_guild_style_occ()
{
    return GUILD_STYLE;
} /* query_guild_style_occ */


/*
 * Function name: query_guild_name_occ
 * Description:   return the guild's name
 * Returns:       string - the guild name
 */
string
query_guild_name_occ()
{
    return GUILD_NAME;
} /* query_guild_name_occ */


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
    /* The guild is now open, so I'll comment this out. If it needs to
     * be closed for later testing we can uncomment it then.
     *
    if (member_array(who->query_real_name(), BETA_TESTERS) == -1)
    {
        return "The guild is currently only open to beta testers. You"
          + " will need to try back later.\n";
    }
     */

    /* We allow all races, alignments, etc. */
    return 0;
} /* acceptable_member */

      
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

    if (stringp(why = acceptable_member(ob)))
    {
	ob->catch_msg(why);

        /* Normally we would just return 0 here, and the player would be
         * removed from the guild.  We want to make sure a few cleanup
         * actions happen, though, so we'll return 1 here and remove
         * the member ourselves.
         */

        set_alarm(1.0, 0.0, remove_occ_member);

        return 1;
    }

    return 1;
} /* query_guild_keep_player */


/* 
 * Function name: query_guild_not_allow_join_occ
 * Description:	  Check if we allow the player to join another guild.
 * Arguments:     player - the player
 *		  type, style, name - the type, style and name of the
 *			intended guild.
 * Returns:	  1 if we do not allow, else 0
 */
int
query_guild_not_allow_join_occ(object player, string type, string style,
				string name)
{
    /* This checks to make sure that the new guild is not occupational */
    if (::query_guild_not_allow_join_occ(player, type, style, name))
    {
        return 1;
    }

    /* We allow Mercenaries to join ANY layman guild! */
    return 0;
} /* query_guild_not_allow_join_occ */


/* Function name: query_guild_level_occ
 * Description:   What is the member's level within the guild?
 * Returns:	  int - the level
 */
int
query_guild_level_occ()
{
    return MIN(MAX_GUILD_LEVEL, query_shadow_who()->query_stat(SS_OCCUP) / 50);
} /* query_guild_level_occ */

    
/* Function name: query_def_post
 * Description:   We change the default post office to Sparkle
 *                for new members.
 * Returns:	  string - the path to the new postoffice
 */
string
query_def_post() 
{
    /* Only bother using the guild's post office if the player is
     * using the guild's start location.
     */
    if (this_player()->query_default_start_location() == GUILD_STARTLOC)
    {
        return GUILD_POST;
    }

    return query_shadow_who()->query_def_post();
} /* query_def_post */


/*
 * Function name:        get_merc_ranks
 * Description  :        get the mercenary ranks for this player
 * Returns      :        string - the rank titles
 */
public string
get_merc_ranks()
{
    object  who = query_shadow_who();
    string  title;
    int     gsnum,
            adnum;

    setuid();
    seteuid(getuid());

    gsnum = MERC_MASTER->compute_guildstat_title(who);
    adnum = MERC_MASTER->compute_adapt_title(who);

    title = Merc_Ad_Titles[adnum] + " " + Merc_Gs_Titles[gsnum];

    if (who->query_gender() == G_FEMALE)
    {
        title = Merc_Ad_Titles[adnum] + " " + F_Merc_Gs_Titles[gsnum];
    }

    return title;
} /* get_merc_ranks */


/*
 * Function name: query_guild_title_occ
 * Description:   Return the member's guild title
 * Returns:       string - the title
 */
string 
query_guild_title_occ()
{
    object  who = query_shadow_who();
    mixed   affiliated;
    string  title;

    setuid();
    seteuid(getuid());

    if (MERC_MASTER->get_info(who, "incognito") == "on")
    {
        return "";
    }

    affiliated = MERC_MASTER->get_info(who, "affiliation");

    title = get_merc_ranks() + " of the Mercenary Guild";

    if (affiliated)
    {
        if (MERC_MASTER->get_info(who, "incognito") == "aff")
        {
            title = MERC_MASTER->get_info(who, "title");
        }
        else
        {
            title += ", " + MERC_MASTER->get_info(who, "title");
        }
    }
    else
    {
        title = get_merc_ranks()
              + " and Free Agent of the Mercenary Guild";
    }

    return title;
} /* query_guild_title_occ */

    
/* 
 * Function name: query_guild_skill_name
 * Description:   Give a names for the guild's special skills
 * Arguments:     type - the number of the skill
 * Returns:	  0 if no skill of mine, else the string.
 */
mixed
query_guild_skill_name(int type)
{
    if (type == SS_MERC_ADAPT_SKILL)
    {
        return "adaptability";
    }
    if (type == SS_MERC_TACTICS_SKILL)
    {
        return "mercenary tactics";
    }

    return 0;
} /* query_guild_skill_name */


/*
 * Function name: query_guild_trainer_occ
 * Description:   Returns the skill trainers for the guild
 * Returns:       string * - an array of paths to the guild's
 *                trainers.
 */
mixed
query_guild_trainer_occ()
{
    return ({ ROOM_DIR + "wep_train",
              ROOM_DIR + "tactics_train",
              ROOM_DIR + "adapt_train"
           });
} /* query_guild_trainer_occ */


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

    /* add the guild subloc */
    who->add_subloc(GUILD_SUBLOC, this_object());
} /* init_guild_member */


/*
 * Function name: start_player
 * Description:   This is called when the player logs in.
 */
public void
start_player()
{
    SW->start_player();
    init_guild_member();
} /* start_player */


/* 
 * Function name: add_occ_shadow
 * Description:   Shadow an object with this shadow
 * Arguments:     object who - the object to shadow
 * Returns:       as shadow_me in /std/guild/guild_base.c
 */
int
add_occ_shadow(object who)
{
    int ret = shadow_me(who, "occupational", GUILD_STYLE, GUILD_NAME);

    if (ret == 1)
    {
        init_guild_member();
    }

    return ret;
} /* add_occ_shadow */


/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *		  me      - I
 *		  for_obj - The looker
 * Returns:	  The string the looker shall see
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    string str;

    if (subloc != GUILD_SUBLOC)
    {
        return me->show_subloc(subloc, me, for_obj);
    }

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
	return "";
    }

    if (for_obj == me)
    {
	str = "You are a member of the Free Mercenary Guild";
    }
    else
    {
	str = capitalize(me->query_pronoun())
          + " has the air of one who is experienced in many things";
    }

    return str + ".\n";
} /* show_subloc */


/*
 * Function name: remove_occ_member
 * Description:   remove this member from the guild
 */
void
remove_occ_member()
{
    object  emblem; 
    object  who = query_shadow_who();
    string  affiliated;
    string  affiliation;

    setuid();
    seteuid(getuid());

    /* Remove special skills */ 
    who->remove_skill(SS_MERC_ADAPT_SKILL);
    who->remove_skill(SS_MERC_TACTICS_SKILL);

    /* Clear the player's guild stat */
    who->clear_guild_stat(SS_OCCUP);

    /* Remove any instances of the guild emblem on the player */
    while (emblem = present(GUILD_EMBLEM_ID, who))
    {
        emblem->remove_object();
    }

    /* If the player is using our start location, remove it */
    if (who->query_default_start_location() == GUILD_STARTLOC)
    {
        who->set_default_start_location(who->query_def_start());
    }

    /* Clear all of the adapted skills the player may have. */
    MERC_MASTER->clear_adapt(who, -1, 1);

    /* Clear affiliations. */
    affiliated = MERC_MASTER->get_info(who, "affiliation");
    affiliation = MERC_MASTER->format_the_the(affiliated);

    TELL_G("affiliation = " + affiliation);

    if (strlen(affiliation))
    {
        who->catch_tell("You are no longer affiliated with "
          + affiliation + ".\n\n");
    }

    MERC_MASTER->set_info(this_player(), "affiliation", 0);
    MERC_MASTER->set_info(this_player(), "title", 0);

    /* Remove the guild soul */
    who->remove_cmdsoul(GUILD_CMDSOUL);
    who->update_hooks();

    /* Remove the guild shadow.  This also resets tax to 0. */
    remove_guild_occ();
} /* remove_occ_member */


/*
 * Function name:   query_skill
 * Description:     Gives the value of a specific skill.
 * Arguments:       skill: The number of the skill to check
 * Returns:         The value of the skill
 */
public int
query_skill(int skill)
{
    mapping enhance_map;
    int base_skill = shadow_who->query_skill(skill);

    if (catch(enhance_map = MERC_MASTER->get_info(shadow_who, "skill_enhance")))
    {
        // If catch returns true, then an error occurred.
        return base_skill;
    }
    
    if (!mappingp(enhance_map) || base_skill >= 100 || !enhance_map[skill])
    {
        return base_skill;
    }
    
    return min(100, base_skill + enhance_map[skill]);
}
