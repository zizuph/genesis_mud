/* 
 * Sculptor of Flesh spell object
 * 
 * Updated to inherit from /d/Genesis/specials/new/magic/
 * Arman (AoB) December 2021
 */

#include "../../guild.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "objs/statboost_obj";


/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_sculptor_object_");
    set_short("Warlock sculptor spell object");    
    set_long("This is the Warlock sculptor spell object, "
    +"based on the standard statboost spell's object.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object created by "
    +"the warlock sculptor spell.\n");
    
    set_spell_effect_desc("Sculptor Of Flesh");    
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
        target->catch_tell("You grimace slightly as your body cracks "
        +"and snaps into a physically enhanced being.\n");
        
        tell_room(environment(target), "Eerie cracks and snaps echo into "
        +"the surroundings as "+QCTNAME(target)+" appears to grow "
        +"stronger.\n",    ({ target }));
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
        target->catch_tell("You feel yourself shrinking as "
        +"Urhagash wears off. Painful.\n");
        
        tell_room(environment(target), QCTNAME(target)+" grimaces "
        +"as "+target->query_pronoun()+" shrinks, strength fading "
        +"away.\n",({ target }));
        
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
        target->catch_tell("You sense your Urhagash spell is " 
        +"beginning to fade.\n");
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
        + "your Urhagash spell.\n");
    }    
}
