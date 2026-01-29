/* 
 * Example Caster Guild Shadow
 *
 * This is a sample guild shadow for to show what needs to be done
 * for the new spell system.
 *
 * Created by Petros, February 2009
 */

#pragma save_binary

inherit "/std/guild/guild_lay_sh";

#include <ss_types.h>
#include <macros.h>

// Defines
#define MANA_SHADOW         "/d/Genesis/specials/guilds/shadows/mana_shadow"
#define SPELL_MANAGER_SOUL  "/d/Genesis/specials/guilds/souls/spell_manager_soul"
#define CASTER_SOUL         "/d/Genesis/specials/guilds/souls/example_caster_soul"

// Prototypes
public void     initialize_sample_shadow();
public object   query_top_shadow();

void
init_lay_shadow(string str)
{
    ::init_lay_shadow(); 

    set_alarm(1.0, 0.0, initialize_sample_shadow);
}

public void
initialize_sample_shadow()
{
    setuid();
    seteuid(getuid());
    
    // Make sure the command soul gets added
    shadow_who->add_cmdsoul(SPELL_MANAGER_SOUL);
    shadow_who->add_cmdsoul(CASTER_SOUL);

    shadow_who->update_hooks();
    
    // Every caster guild using the new Genesis magic system will
    // use the mana shadow to get the new regeneration rates for mana.
    if (!query_top_shadow()->has_mana_shadow())
    {
        clone_object(MANA_SHADOW)->shadow_me(shadow_who);
    }    
}

public void
remove_shadow()
{
    // Remove the spells specified in the soul
    CASTER_SOUL->remove_spells(shadow_who);
    
    // We also need to remove the mana shadow. This removal assumes
    // that the person can only have one caster guild shadow.
    query_top_shadow()->remove_mana_shadow();
        
    ::remove_shadow();    
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

