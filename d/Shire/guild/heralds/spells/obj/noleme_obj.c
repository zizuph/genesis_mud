/* 
 * noleme object - wisdom of Ulmo
 */

#include "/d/Shire/common/defs.h"
#include "../../herald.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>

inherit "/d/Genesis/specials/new/magic/spells/objs/statboost_obj";

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_noleme_object_");
    set_short("Heralds noleme spell object");    
    set_long("This is the Heralds noleme spell object, based on the " +
        "standard statboost spell's object.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object created by " +
        "the noleme spell.\n");
    set_spell_effect_desc("wisdom of Ulmo");    
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
        target->catch_tell("You channel Ulmo, the Dweller of the Deep, " +
            "and are enhanced with his temperance and wisdom.\n");
        tell_room(environment(target), QCTNAME(target) + " slowly " +
           "opens " +HIS_HER(target)+ " eyes to reveal a gaze calm and " +
           "deep like the ocean, full of temperance and wisdom.\n", 
           ({ target }));
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
        caster->catch_tell("You no longer channel the noleme blessing.\n"); 
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
        target->catch_tell("You feel you will be unable to maintain " +
            "channelling the noleme blessing for much longer.\n");
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
        caster->catch_tell("Mentally drained, you are unable to maintain " +
            "the noleme blessing.\n");
    }    
}
