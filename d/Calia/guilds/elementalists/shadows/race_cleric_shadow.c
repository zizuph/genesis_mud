/* 
 * Elemental Clerics of Calia Racial Guild Shadow
 *
 * This is the racial guild shadow for the Elemental Clerics of Calia. This is
 * a clerical occupational + layman guild. Members of this guild will
 * select one branch to focus on, which equates to serving one of
 * the Five Elementals of Calia. The racial section is optional and
 * gives the player more RP functions as well as a boost in some skills
 * and their elemental form (Skiamorfi).
 *
 * Created by Petros, April 2010
 */

#pragma save_binary

#include <ss_types.h>
#include <macros.h>
#include <files.h>
#include <composite.h>
#include <std.h>
#include <const.h>
#include "../defs.h"

inherit "/std/guild/guild_race_sh";

#include "/d/Genesis/specials/debugger/debugger_tell.h"
#include "/d/Calia/guilds/elementalists/shadows/racial_options.h"

// Defines
#define EC_RACIAL_SUBLOC "_elemental_guild_racial_subloc"

// Prototypes
public void     initialize_race_cleric();
public object   query_top_shadow();
private mixed   special_title;

public string 
query_guild_style_race() 
{ 
    return GUILD_STYLE; 
}

public string 
query_guild_name_race() 
{ 
    return GUILD_EC_NAME; 
}

int 
query_guild_tax_race() 
{ 
    return GUILD_EC_RACE_TAX; 
}

public int
query_guild_family_name()
{
	return 1;
}

public string *
query_title_spirits()
{
	return TITLE_SPIRITS;
}

public string *
query_title_prefix()
{
	return TITLE_SECONDS_PREFIX;
}

public string *
query_title_suffix()
{
	return TITLE_SECONDS_SUFFIX;
}

void
init_race_shadow(string str)
{
    ::init_race_shadow(); 
    
    set_alarm(1.0, 0.0, initialize_race_cleric);
}

public void
initialize_race_cleric()
{
    setuid();
    seteuid(getuid());
    
    // Make sure the command soul gets added
    shadow_who->add_cmdsoul(EC_RACE_SOUL);
    shadow_who->add_cmdsoul(SPELL_MANAGER_SOUL);

    shadow_who->update_hooks();
    shadow_who->add_subloc(EC_RACIAL_SUBLOC, TO);
    
    // Every caster guild using the new Genesis magic system will
    // use the mana shadow to get the new regeneration rates for mana.
    if (!query_top_shadow()->has_mana_shadow())
    {
        clone_object(MANA_SHADOW)->shadow_me(shadow_who);
    }    
    
}

/*
 * Function:    show_subloc
 * Description: Displays the appropriate message for the racial subloc
 */
public string
show_subloc(string subloc, object on, object for_obj)
{
    string str;
    
    if (subloc != EC_RACIAL_SUBLOC)
        return shadow_who->show_subloc(subloc, on, for_obj);

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";    
    
    if (for_obj == on)
        str = "You have a Kyrullian aura surrounding you.\n";
    else
    {
        if (for_obj->query_guild_name_occ() == "Elemental Clerics of Calia")
        {
            if (GUILD_MANAGER->query_has_completed_scenarios(for_obj))
                str = capitalize(on->query_pronoun()) + 
                " has a Kyrullian aura surrounding " + 
                on->query_objective() + ".\n";
        }
        
        else
            str = capitalize(on->query_pronoun()) + 
            " has a strange aura surrounding " + 
            on->query_objective() + ".\n";
    }
    
    return str;
}

public void
remove_shadow()
{
    // We use the removal of the shadow as a way to ensure that the
    // spells for the command soul are removed.
    EC_RACE_SOUL->remove_spells(shadow_who);
    
    // We also need to remove the mana shadow. This removal assumes
    // that the person can only have one caster guild shadow.
    query_top_shadow()->remove_mana_shadow();
    shadow_who->remove_subloc(EC_RACIAL_SUBLOC);
    ::remove_shadow();    
}

public string 
query_guild_title_race() 
{
    string racial_spirit_surname;
    string racial_chosen_surname;
    int racial_hide_title;

    if (shadow_who->query_npc())
        return "";
        
    racial_spirit_surname = GUILD_MANAGER->
    	query_racial_spirit_surname(shadow_who);
    racial_chosen_surname = GUILD_MANAGER->
    	query_racial_chosen_surname(shadow_who);
    racial_hide_title = GUILD_MANAGER->
    	query_racial_hide_title(shadow_who);
    
    if (racial_hide_title)
        return "";
    else
        return racial_spirit_surname + "-" + racial_chosen_surname;
} 

public string
query_guild_trainer_race()
{
    return ELEMENTALIST_TEMPLE + "ec_practice";
}

/* function name: query_guild_keep_player
 * Description:   This gives you a chance to tell if you want to keep the
 *                the player when the shadow is autoloading when a player
 *                logs on.
 * Arguments:     player - the player
 * Returns:       1 - keep player, 0 - kick him out.
 */
public int
query_guild_keep_player(object player)
{
    int result = ::query_guild_keep_player(player);
    
    if (!result)
    {
        // Even the base shadow doesn't want to keep this player. Just return.
        return 0;
    }
    
    setuid();
    seteuid(getuid());
    // Conditions to kick out should be here, and should return 0
    
    return 1;
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

public int
is_elemental_racial_cleric()
{
    return 1;
}
