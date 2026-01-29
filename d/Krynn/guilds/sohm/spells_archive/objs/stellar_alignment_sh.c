/*
 * Support Shadow for the Stellar Alignment Spell
 *
 * This shadow gets cloned by the shadow object when the spell
 * is cast. We use this shadow to override the props in a shadow
 * instead of altering it. Using a shadow is typically safer
 * because it can handle stacking from multiple effects well.
 *
 * Created by Petros, modified by Arman - August 2020
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <files.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/guilds/wohs/defs.h"

#ifndef WOHS_STELLAR_ALIGNMENT
#define WOHS_STELLAR_ALIGNMENT   ("_wohs_stellar_alignment_spell_prop")
#endif

inherit "/d/Genesis/specials/std/spells/obj/propchange_base_sh";

/*
 * Function:    initialize_shadow
 * Description: Called after first cloned. Should do all the initialization
 *              effects for this particular shadow.
 */

public void
initialize_shadow(object spell_object, mapping spell_input)
{
    ::initialize_shadow(spell_object, spell_input);
    spell_object->set_spell_effect_desc("stellar alignment");
    spell_object->set_short("stellar alignment spell object");

    int power = spell_object->query_spell_effect_power();

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

    if (prop != WOHS_STELLAR_ALIGNMENT)
    {
        return result;
    }
    
    if (intp(result))
    {
        return max(1, result + 1);
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
    string moon;

    switch(QUERY_WOHS_ROBE(target))
    {
        case "white":
            moon = "Solinari";
            break;
        case "red":
            moon = "Lunitari";
            break;
        case "black":
            moon = "Nuitari";
            break;
        default:
            moon = "Armanari";
            break;
    }

    if (objectp(target))
    {
        target->catch_tell("You magnify the phase of your moon of magic, " +moon+ 
            ", and project some of the benefits to your team.\n");
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
        target->catch_tell("You feel your stellar alignment spell disappear.\n");
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
        target->catch_tell("You feel the stellar alignment spell begin to "
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
            + "the stellar alignment spell.\n");
    }    
}
