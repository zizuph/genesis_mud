/*
 * Featherweight object
 *
 * Updated to inherit from /d/Genesis/specials/new/magic/
 * Arman (AoB) December 2021
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <tasks.h>
#include "../../guild.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "objs/featherweight_obj";


/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_witchstep_object_");
    set_short("witchstep spell object");    
    set_long("This is the standard featherweight spell's object. It allows "  
        + "a person to lighten their load\n");
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the witchstep spell.\n");
    set_spell_effect_desc("Witchstep");        
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
        target->catch_tell("You feel less burdened as the weight of your "
        +"belongings eases dramatically.\n");
            
        tell_room(environment(target), QCTNAME(target) 
        + " appears to be less affected by "
        +target->query_possessive()+ " belongings.\n", 
        ({ target }));
    } 
    
    target->add_prop(WITCHSTEP_EFFECT, 1);   
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
        target->catch_tell("You feel more taxed as the effect of "
        +"the spell Urhuew ends.\n");
           
        tell_room(environment(target), QCTNAME(target) 
        + " suddenly looks more taxed.\n", ({ target }));
    }
    
    target->remove_prop(WITCHSTEP_EFFECT);
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
        target->catch_tell("You feel Urhuew is starting to " +
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
            + "the witchstep spell.\n");
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
        return  "Your feel less taxed.\n";
    else
        return capitalize(on->query_pronoun()) + " looks less taxed "
            + "than usual.\n";
}