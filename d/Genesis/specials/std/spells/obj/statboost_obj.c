/*
 * Standard Stat Boost Object
 *
 * This is the spell object for the standard Genesis Magic System Stat Boost
 * spell. When started, the stat boost spell clones this object to provide
 * boosts to specified stats.
 *
 * Specific guild implementations must inherit from this one to get
 * the standard AoB approved effects.
 *
 * Created by Petros, December 2010
 *
 * Comments:
 * Carnak 2018-04-14: We have moved the formulas in this file, if you encounter
 *                    any issues you can restore the _bak file.
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>

#include "defs.h"

inherit "/d/Genesis/specials/std/spells/obj/spell_obj_base";

#include "/d/Genesis/specials/calculations.c"

public mapping      stat_boost_mapping = ([ ]);

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_stat_boost_object_");
    set_short("stat boost spell object");    
    set_long("This is the standard stat boost spell's object. It temporarily "
        + "increases one's stats.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the statboost spell.\n");
    set_spell_effect_desc("stat boost");    
}

/*
 * Function:    setup_spell_effect
 * Description: This is called to set up all the things for the
 *              spell. Must call the parent's setup_spell_effect
 *              in order to get the maintainence stuff.
 */
public int
setup_spell_effect()
{
    int result = ::setup_spell_effect();
    if (!result)
    {
        return result;
    }

    int power = query_spell_effect_power();
    // Power determines how long the spell lasts
    int duration = power * 5; // F_PENMOD(60, 100) = 396 * 5 = 33 minutes
    set_dispel_time(duration);
    
    object player = query_effect_target();
    // The input to the spell object will be a mapping of stat id and
    // the combat aid that the stat boost should have.
    mapping stat_mappings = query_spell_effect_input();
    foreach (int s_id, int caid : stat_mappings)
    {
        stat_boost_mapping[s_id] = convert_caid_to_stat(player, caid, s_id);
        player->set_stat_extra(s_id, player->query_stat_extra(s_id)
        + stat_boost_mapping[s_id]);
    }
    if (stat_boost_mapping[SS_CON])
    {
        // Add temporary HP if the boost included a CON boost
        player->heal_hp(stat_boost_mapping[SS_CON] * 20);
    }
    return result;
}

public varargs int
dispel_spell_effect(object dispeller)
{
    int result = ::dispel_spell_effect(dispeller);
    if (!result)
    {
        return result;
    }
    
    object player = query_effect_target();
    foreach (int stat_id, int boost : stat_boost_mapping)
    {
        player->set_stat_extra(stat_id, player->query_stat_extra(stat_id)
        - stat_boost_mapping[stat_id]);
    }
    if (stat_boost_mapping[SS_CON])
    {
        // Remove the temporary hp that the player gained.
        player->heal_hp(-stat_boost_mapping[SS_CON] * 20);
    }
    return 1;
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started()
{
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("You feel yourself boosted in your stats.\n");
        tell_room(environment(target), QCTNAME(target) + " glows briefly, "
            + "gaining stat boosts.\n", ({ target }));
    }    
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("You feel your stat boosts disappear.\n");
        tell_room(environment(target), QCTPNAME(target) + " skin "
            + "seems to lose a bit of luster as the stat boosts "
            + "dissipate.\n", ({ target }));
    }
}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading()
{
    object target = query_effect_target();
    
    if (objectp(target))
    {
        target->catch_tell("You feel the your stat boosts begin to "
            + "fade.\n");
    }
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained()
{
    object caster = query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
            + "the magical protection.\n");
    }    
}


