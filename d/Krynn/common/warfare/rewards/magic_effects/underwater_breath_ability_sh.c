/*
 * Shadow for water breathing ability
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

int spell_power;
object spell_target;
object helm; 

int water_breath_boost = 100;

/*
 * Function:    initialize_shadow
 * Description: Called after first cloned. Should do all the initialization
 *              effects for this particular shadow.
 */

public void
initialize_shadow(object spell_object, mapping spell_input)
{
    ::initialize_shadow(spell_object, spell_input);
    spell_object->set_name("_mw_water_breathe_sh_");
    spell_object->set_spell_effect_desc("water breathe");
    spell_object->set_short("masterwork water breathe spell object");
    spell_object->set_dispel_time(1800);

    spell_power = spell_object->query_spell_effect_power();
    spell_target = spell_object->query_effect_target();
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
    helm = shadow_who->query_armour(TS_HEAD);

    if (objectp(target))
    {
        // target->catch_tell("You feel yourself able to breathe water.\n");
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
    string helm_str = helm->query_short();

    if (objectp(target))
    {
        target->catch_tell("You feel the protective bubble surrounding " +
            "your " +helm_str+ " vanish.\n");
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
    string helm_str = helm->query_short();
    
    if (objectp(target))
    {
        target->catch_tell("You feel the protective bubble surrounding " +
            "your " +helm_str+ " begin to fade.\n");
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
    string helm_str = helm->query_short();
    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
            + "the water breathing enchantment.\n");
    }    
}
