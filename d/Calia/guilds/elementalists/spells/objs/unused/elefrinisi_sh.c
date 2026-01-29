/*
 * Elefrinisi Shadow for the Elemental Guilds of Calia
 *
 * This is the spell shadow based on the standard featherweight effect.
 *
 * Created by Petros, December 2010
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "defs.h"

inherit "/d/Genesis/specials/std/spells/obj/featherweight_sh";

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
        target->catch_tell("Your prayers are answered and everything you carry "
            + "seems lighter as if the pull of the earth itself has alleviated "
            + "your burdens.\n");
        tell_room(environment(target), QCTNAME(target) + " seems to have a heavy "
            + "burden lifted from " + target->query_objective() + ".\n", 
            ({ target }));
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
        target->catch_tell("The blessings of the gift of elefrinisi "
            + "subside, and you once again feel the full weight of "
            + "your belongings.\n");
        tell_room(environment(target), QCTNAME(target) + " seems to be "
            + "weighed down by something.   \n", ({ target }));
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
        target->catch_tell("You sense the gift of elefrinisi is about "
            + "to expire.\n");
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
            + "the gift of elefrinisi.\n");
    }    
}
