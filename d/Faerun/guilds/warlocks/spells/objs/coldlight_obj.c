/*
*
 * Updated to inherit from /d/Genesis/specials/new/magic/
 * Arman (AoB) December 2021
*/

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <files.h>
#include "../../guild.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "objs/light_obj";

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_coldlight_object_");
    set_short("coldlight spell object");    
    set_long("This is the object for the light spell of the "
    +"warlocks.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "This is a spell object created by the "
        + "coldlight spell.\n");
    set_spell_effect_desc("Coldlight");

}


/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started()
{
    object caster = query_effect_caster();

    if (objectp(caster))
    {
        caster->catch_tell("Your body starts to radiate a "
        +"sickening cold blue glow, illuminating the environment!\n");
            
        tell_room(environment(caster), QTNAME(caster) 
        + " body starts to radiate a sickening cold "
		+"blue glow that "
        +"illuminates the environment!\n",
        ({ caster }) );
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
        target->catch_tell("You stop radiating coldlight.\n");
            
        tell_room(environment(target), "The sickening cold blue "
        +"glow surrounding "+ QTNAME(target) 
        + " diminishes.\n", ({ target }));
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
        target->catch_tell("The sickening cold blue glow "
        +"dims for a short moment. You sense it will "
        +"fade soon.\n");
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
        caster->catch_tell("Mentally drained, your control over "
        +"Urfiviel is lost.\n");
    }    
}


/*
 * Function:    query_light_subloc_description
 * Description: When someone examines a person with this spell effect,
 *              they will see whatever is returned by this function.
 */
public string
query_light_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
        return  "You radiate a sickening cold blue "
        +"glow.\n";
    else
        return capitalize(on->query_pronoun()) 
	    + " radiates a sickening cold blue "
        +"glow.\n";
}