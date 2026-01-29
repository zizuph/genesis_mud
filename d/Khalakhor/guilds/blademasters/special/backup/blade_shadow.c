/*
 * blade_shadow.c
 *
 * This is the guild shadow for the Blademasters of Khalakhor.
 * 
 * Khail - May 14/97
 */
#pragma save_binary

#include "defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <macros.h>
#include <formulas.h>

inherit "/std/guild/guild_lay_sh";

#include "battack.c"

int greet_alarm,
    skill_alarm;

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
greeting(int skilltest = 0)
{
    object chain;

    setuid(); seteuid(getuid());

    (SPECIAL + "guildmaster")->update_list(shadow_who->query_name(),
        shadow_who->query_base_skill(SS_WEP_SWORD),
        shadow_who->query_base_stat(SS_LAYMAN));

    if (shadow_who->query_base_skill(SS_WEP_SWORD) < REMAIN_SWORD_SKILL)
    {
        tell_object(shadow_who, "Your skill with a blade has " +
            "fallen. Your peers no longer recognize you as worthy " +
            "of the Blademasters.\n");
        log_file("blademasters/expel", shadow_who->query_name() + " was " +
            "expelled for a sword skill of " + 
            shadow_who->query_skill(SS_WEP_SWORD) + " on " +
            ctime(time()) + ".\n");
        shadow_who->clear_bit(IS_BLADEMASTER_BIT);
        shadow_who->clear_guild_stat(SS_LAYMAN);
        remove_guild_lay();    
        remove_shadow();
        return;
    }

    if (skilltest)
        return;

    tell_object(shadow_who, "Glory thy Blade, Blademaster.\n");

    if ((SPECIAL + "guildmaster")->query_news(shadow_who->query_name()))
        shadow_who->catch_tell("There is NEW Blademaster news. Use " +
            "the 'bnews' command to read it.\n");

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
        chain = clone_object(TOKEN);
        if (chain->move(shadow_who,1))
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
    string ret;

    if (shadow_who->query_skill(SS_WEP_SWORD) >= HIGH_SWORD_SKILL)
        ret = "High ";
    else
        ret = "";

    if (shadow_who->query_gender() == 1)
        ret += "Blademistress";
    else
        ret += "Blademaster";

    ret += " of Khalakhor";

    return ret;
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
  /* If the player is a member of a clan, the blademaster */
  /* title is taken care of there, so return nothing. */
    if (strlen(shadow_who->is_khalakhor_clan_member()))
        return "";

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
    if (get_alarm(skill_alarm))
        remove_alarm(skill_alarm);
    skill_alarm = set_alarm(1.0, 0.0,
        &greeting(1));
    return shadow_who->set_skill(skill, val);
}
