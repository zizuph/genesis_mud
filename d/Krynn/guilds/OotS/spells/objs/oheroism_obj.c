/* 
 * oheroism object - blessed by divine forces
 */

#include "/d/Ansalon/common/defs.h"
#include "../../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>

inherit STD_SPELL_SYSTEM + "objs/statboost_obj";

#include "../../oots_god_descs.h"

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_oheroism_object_");
    set_short("OotS oheroism spell object");    
    set_long("This is the OotS heroism spell object, based on the " +
        "standard statboost spell's object.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object created by " +
        "the oheroism spell.\n");
    set_spell_effect_desc("righteous heroism");    
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
        target->catch_tell(oots_god_name(target)+ " grants you a " +
           "blessing of strength and courage!\n");
        tell_room(environment(target), QCTNAME(target) + " is " +
           "blessed with the righteous favour of " + 
           oots_god_name(target)+".\n", ({ target }));
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
    object caster = query_effect_caster();

    if(target->query_ghost())
        return;
    
    if (objectp(caster))
    {
        caster->catch_tell("You feel the righteous blessings of " +
           oots_god_name(caster) + " " + "leave you.\n");
    }

/*
    if (objectp(target))
    {
        tell_room(environment(target), QCTNAME(target) + " is no "
            + "longer protected by the blessings of "+
            oots_god_name(target)+".\n", ({ target }));
    }
*/

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
        target->catch_tell("You feel the righteous blessings of " + 
           oots_god_name(target) + " begin to wane.\n");
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
        caster->catch_tell("Mentally drained, the righteous blessings of "
           + oots_god_name(caster) + " leave you.\n");
    }    
}
