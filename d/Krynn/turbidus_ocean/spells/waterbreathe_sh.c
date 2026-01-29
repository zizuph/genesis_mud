/*
 * Support Shadow for the waterbreathe effect of the
 * sahuagin narwhale hornblade.
 *
 * Arman 2020
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <files.h>
#include "/d/Krynn/common/defs.h"

#ifndef MAGIC_I_BREATHE_WATER
#define MAGIC_I_BREATHE_WATER   ("_magic_i_breathe_water")
#endif

inherit "/d/Genesis/specials/std/spells/obj/propchange_base_sh";

int water_breath_boost;

/*
 * Function:    initialize_shadow
 * Description: Called after first cloned. Should do all the initialization
 *              effects for this particular shadow.
 */

public void
initialize_shadow(object spell_object, mapping spell_input)
{
    ::initialize_shadow(spell_object, spell_input);
    spell_object->set_name("_hornblade_waterbreath_shadow_");
    spell_object->set_spell_effect_desc("water breathing");
    spell_object->set_short("water breathing spell object");
    spell_object->set_dispel_time(1800);

    water_breath_boost = 100;

}

/* 
 * Function:    query_prop
 * Description: This is the primary function that you should override to
 *              implement the propchange shadow. Make sure to return
 *              the shadow_who->query_prop(prop) result if you don't
 *              want to handle that particular prop.
 */
public mixed
query_prop(string prop)
{
    mixed result = shadow_who->query_prop(prop);
    if (prop != MAGIC_I_BREATHE_WATER)
    {
        return result;
    }
    
    if (intp(result))
    {
        return max(1, water_breath_boost);
    }
    else 
    {
        return 1;
    }
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started(object spell_object)
{
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("You feel yourself able to breathe underwater.\n");
    }
    
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended(object spell_object)
{
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("You feel the globe of air surrounding you " +
            "dissipate.\n");
        target->tell_watcher("The globe of air surrounding " + QTNAME(target) + 
            " dissipates.\n", ({ }) );
    }

}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading(object spell_object)
{
    object target = spell_object->query_effect_target();
    
    if (objectp(target))
    {
        target->catch_tell("You feel the globe of air surrounding you " +
            "begin to dissipate.\n");
    }
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained(object spell_object)
{
    object caster = spell_object->query_effect_caster();
    object target = spell_object->query_effect_target();
    
    if (objectp(caster))
    {
        target->catch_tell("You feel the globe of air surrounding you " +
            "dissipate.\n");
        target->tell_watcher("The globe of air surrounding " + QTNAME(target) + 
            " dissipates.\n", ({ }) );
    }    
}
