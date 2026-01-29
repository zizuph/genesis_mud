/*
 * Support Shadow for the Breath Water Spell
 *
 * This shadow gets cloned by the shadow object when the spell
 * is cast. We use this shadow to override the props in a shadow
 * instead of altering it. Using a shadow is typically safer
 * because it can handle stacking from multiple effects well.
 *
 * Created by Petros, modified by Arman - July 2016
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <files.h>
#include "/d/Krynn/common/defs.h"
#include "../defs.h"

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
    spell_object->set_spell_effect_desc("water breathing");
    spell_object->set_short("water breathing spell object");

    int power = spell_object->query_spell_effect_power();
    water_breath_boost = max(1, min(100, power / 3));

    // DEBUG("Waterbreath boost: " +water_breath_boost+ ", power: "+power);

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
        return max(1, result + water_breath_boost);
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
        target->catch_tell("You feel yourself able to breath underwater.\n");
        tell_room(environment(target), QCTNAME(target) + " is able to "
            + "breath underwater.\n", ({ target }));
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
        target->catch_tell("You feel your water breathing spell disappear.\n");
        tell_room(environment(target), QCTNAME(target) + " no longer " +
           "is protected by a water breathing spell.\n", ({ target }));
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
        target->catch_tell("You feel the water breathing spell begin to "
            + "fade.\n");
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
    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
            + "the water breathing spell.\n");
    }    
}
