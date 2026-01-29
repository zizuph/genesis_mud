/*
 * Featherweight object
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <tasks.h>
#include "../defs.h"
#include "/d/Krynn/common/defs.h"

inherit "/d/Genesis/specials/std/spells/obj/featherweight_obj";

#define SOHM_FEATHERWEIGHT_EFFECT "_sohm_featherweight_effect"

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_featherweight_object_");
    set_short("featherweight spell object");    
    set_long("This is the standard featherweight spell's object. It allows "
        + "a person to lighten their load\n");
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the featherweight spell.\n");
    set_spell_effect_desc("featherweight");        
}


/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to the target.
 */
public void
hook_spell_effect_started()
{
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("You feel lighter as the weight of your items are " +
            "transmuted to be less of a burden.\n");
        tell_room(environment(target), QCTNAME(target) + " looks more comfortable "
            + "with " +HIS(target)+ " burdens.\n", 
            ({ target }));
    } 

    target->add_prop(SOHM_FEATHERWEIGHT_EFFECT, 1);   
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

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        target->catch_tell("Your featherweight spell ends, and your items are no " +
           "longer transmuted to be less of a burden.\n");
        tell_room(environment(target), QCTNAME(target) + " looks less comfortable "
            + "with " +HIS(target)+ " burdens.\n", ({ target }));
    }

    target->remove_prop(SOHM_FEATHERWEIGHT_EFFECT);
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
        target->catch_tell("You feel your featherweight transmution is starting to " +
           "expire.\n");
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
            + "the featherweight spell.\n");
    }    
}

/*
 * Function:    query_featherweight_subloc_description
 * Description: When someone examines a person with this spell effect,
 *              they will see whatever is returned by this function.
 */
public string
query_featherweight_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
        return  "Your burdens feel lighter upon you.\n";
    else
        return capitalize(on->query_pronoun()) + " looks less burdened "
            + "than usual.\n";
}
