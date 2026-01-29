/*
 * blade_shadow.c
 *
 * This is the guild shadow for the Blademasters of Khalakhor.
 * 
 * Khail - May 14/97
 * 
 * Modifications:
 *   - Fixed so that shadow uses query_top_shadow to get the skill. Certain
 *     guilds and items will modify skill using a shadow, and this was not
 *     being captured correctly. Petros, September 2009
 *   - Added functions to check for racial Khalakhor membership and title
 *     merging,
 *   - Moved leave guild function from guild object to the shadow (here) and
 *     added code to remove players from guild member mapping file upon leaving
 *     the guild as well as kicking players from the guild when their skill is
 *     too low (this part was missing entirely and the only way to leave the
 *     guild was for players to break their guild item),
 *   - Changed titles by adding more variety to them. Zhar, November 2012
 */
#pragma save_binary

#include "defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <macros.h>
#include <formulas.h>

inherit "/d/Khalakhor/guilds/blademasters/special/blade_utility";
inherit "/std/guild/guild_lay_sh";

// global variables
int greet_alarm,
    skill_alarm;

// Prototypes
public object query_top_shadow();

/*
 * Function name: is_khalakhor_blademaster
 * Description  : Identifies the person being shadowed as
 *                a blademaster.
 * Arguments    : n/a
 * Returns      : 1 Always.
 */
public int
is_khalakhor_blademaster()
{
    return 1;
}

/*
 * Function name: query_guild_style_lay
 * Description  : Returns the guild style.
 * Arguments    : n/a
 * Returns      : GUILD_STYLE defined in guild.h
 */
public string
query_guild_style_lay()
{
    return GUILD_STYLE;
}

/*
 * Function name: query_guild_name_lay
 * Description  : Returns the guild name
 * Arguments    : n/a
 * Returns      : GUILD_NAME defined in guild.h
 */
public string
query_guild_name_lay()
{
    return GUILD_NAME;
}

/*
 * Function name: query_guild_tax_lay
 * Description  : Returns the guild tax.
 * Arguments    : n/a
 * Returns      : GUILD_TAX defined in guild.h
 */
public int 
query_guild_tax_lay() 
{ 
    return GUILD_TAX; 
}

/*
 * Function name: greeting
 * Description  : Delivers a greetings message to the player, adds
 *                the cmdsoul and guild object.
 * Arguments    : n/a
 * Returns      : n/a
 */
static varargs void
greeting()
{
    setuid();
    seteuid(getuid());
    
    string name = shadow_who->query_real_name();

    GMASTER->update_list(name,
        shadow_who->query_base_skill(SS_WEP_SWORD),
        shadow_who->query_base_stat(SS_LAYMAN));
        	
    if (is_skilled_blademaster(query_top_shadow()))
    {
        tell_object(shadow_who, "Glory thy Blade, Blademaster.\n");
    }
    else
    {
        tell_object(shadow_who, "You are not skilled enough to be " +
            "considered a Blademaster.\n");    
    }
    
    if (GMASTER->query_news(name))
    {
        shadow_who->catch_tell("There is NEW Blademaster news. Use " +
            "the 'bnews' command to read it.\n");
    }
	
  /* Add the cmdsoul to the player. */
    shadow_who->add_cmdsoul(SOUL);
    shadow_who->update_hooks();

  /* Give the chain (guild object) to the player. We add */
  /* the chain here rather than make it an autoloader, as */
  /* shadows are more stable anyway. This also means if it's */
  /* lost, recovering it is a matter of logging out and back */
  /* in. */
    if (!present(BLADEMASTER_CHAIN_NAME, shadow_who))
    {
        seteuid(getuid());
        
        object chain = clone_object(TOKEN);
        
        if (chain->move(shadow_who, 1))
        {
            tell_object(shadow_who, "You drop your chain.\n");
            chain->move(environment(shadow_who));
        }
    }
}

/*
 * Function name: init_lay_shadow
 * Description  : Called when the shadow is loaded.
 *                Here, it delivers a greeting to the player.
 * Arguments    : str - A string of possible arguments which
 *                      are taken from the auto_shadow_list array.
 * Returns      : n/a
 */
public void
init_lay_shadow(string str)
{
    ::init_lay_shadow();
    greet_alarm = set_alarm(2.0, 0.0, greeting);
}

/*
 * Function name: query_blademaster_title
 * Description  : Returns the player's full blademaster title.
 *                Coded separately from query_guild_title_lay
 *                to allow 'merging' with clan titles.
 * Arguments    : n/a
 * Returns      : Guild title as a string.
 */
public string
query_blademaster_title()
{
    string title;

    string *titles = ({"Acolyte ", 
	"Talented ", 
	"Adept ", 
	"Skilled ", 
	"Brilliant ", 
	"Master "});

    string *high_titles = ({"Rising ", 
    	"Prestigious ", 
    	"Renowned ", 
    	"Distinguished ",
	"Exalted ", 
    	"Fabled "});
    					
    int level = min(5, shadow_who->query_base_stat(SS_LAYMAN) / 40);
    
    if (query_top_shadow()->query_skill(SS_WEP_SWORD) >= HIGH_SWORD_SKILL)
    {
	title = high_titles[level];
    }
    else if (!is_skilled_blademaster(query_top_shadow()))
    {
    	title = "Incompetent and Clumsy ";
    }
    else
    {
    	title = titles[level];
    }
    
    if (shadow_who->query_gender() == 1)
    {
    	title += "Swordmaiden";
    }
    else
    {
    	title += "Swordsman";
    }
    
    return title;
}

/*
 * Function name: query_guild_title_lay
 * Description  : Returns the guild title for this player.
 * Arguments    : n/a
 * Returns      : Guild title as a string.
 */
public string
query_guild_title_lay()
{
    // if player is a clan member the title is handled there
    if (query_top_shadow()->is_khalakhor_clan_member())
    {
        return "";
    }
	
    return query_blademaster_title();
}

/*
 * Function name: set_skill (MASK)
 * Description  : Sets the specified skill number to the specified
 *                skill value. Masked here to automatically catch
 *                and expel players as their sword skill drops below
 *                the value required to stay in the guild.
 * Arguments    : skill - Skill number as an integer
 *                val - The new value as an integer.
 * Returns      : 0 - Fail
 *                1 - Success
 */
public int
set_skill(int skill, int val)
{
    int old_is_skilled, new_is_skilled, result;
    
    old_is_skilled = is_skilled_blademaster(query_top_shadow());
    result = shadow_who->set_skill(skill, val);
    new_is_skilled = is_skilled_blademaster(query_top_shadow());
    
    if (old_is_skilled && !new_is_skilled)
    {
        // The skill has been lowered
        tell_object(shadow_who, "Your skill with a blade has " +
            "fallen. Your peers now recognize how incompenent " +
            "and clumsy you are.\n");
    }
    else if (!old_is_skilled && new_is_skilled)
    {
        // The skill has been raised to an acceptable level
        tell_object(shadow_who, "Your skill with a blade has " +
            "increased. Your peers now recognize you as a " +
            "competent Blademaster once again.\n");
    } 
    
    return result;       
}

/*
 * Function name: leave_guild_lay
 * Description  : Steps to take in order to remove player from the guild
 * Arguments	: object who - player to remove
 * Returns		: int - 1 success, 0 fail
 */
public int
leave_guild_lay()
{
	setuid();
    seteuid(getuid());
    
    object chain = present(BLADEMASTER_CHAIN_NAME, shadow_who);
    string name = shadow_who->query_real_name();
		
    // clear stats and update commands
    shadow_who->clear_guild_stat(SS_LAYMAN);
    shadow_who->remove_cmdsoul(SOUL);
    shadow_who->clear_bit(IS_BLADEMASTER_BIT);
    shadow_who->update_hooks();
 
    // remove guild object       
    if (objectp(chain))
    {   		
    	chain->remove_object();
    }
    
    // remove entries in member list
    GMASTER->remove_master(name);
    
    // write a log
    log_file("blademasters/quit", capitalize(name) + " quit " +
        "the Blademasters on " + ctime(time()) + ".\n");
            
    return remove_guild_lay();
}

/*
 * Function name: query_top_shadow
 * Description:   Because shadows exist in layers, sometimes you need
 *                to reference functions in a shadow above you. Calling
 *                functions can fail if one doesn't call from the top
 *                shadow. this function allows one to obtain the
 *                top most shadow, giving access to all functions.
 * Returns:       object - top level shadow
 */
public object
query_top_shadow()
{
    object last_me, me;
    
    me = shadow_who;
    last_me = me;
    
    while (me = shadow(me, 0))
    {
        // loop through to find the top level shadow who
        last_me = me;
    }   
    
    // We return now the top level shadow
    return last_me;
}
