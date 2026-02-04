/* 
 * Minstrel Bravuro SS_DIS statboost object
 */

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"
#include "../../guild_defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "objs/statboost_obj";

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_bravuro_object_");
    set_short("Minstrel bravuro song object");    
    set_long("This is the Minstrel brave song object, based on the " +
        "standard statboost spell's object.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object created by " +
        "the bravuro song.\n");
    set_spell_effect_desc("song of bravery"); 
    set_spell_effect_notes("This Song of Power inspires a Minstrel's " +
        "team to perform with bravery. However that inspiration " +
        "fades shortly after team members move away from the presence " +
        "of the Minstrel.\n");   
}

/*
 * Function:    query_spell_effect_still_valid()
 * Description: For a maintained spell effect, this allows the spell
 *              effect to determine whether it is still valid or not.
 *              In the maintain_spell_effects function, it will dispel
 *              the effect object if it determines that it is no longer
 *              valid.
 */
public int
query_spell_effect_still_valid()
{
    object target = query_effect_target();
    object caster = query_effect_caster();

    if (!target)
        return 0;

    if(present(caster, environment(target)))
        return 1;
    else
        return 0;
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
    object caster = query_effect_caster();

    if (objectp(target))
    {
/*
        target->catch_tell("A powerful Song of Battle fills the air and " +
            "strengthens your heart as you prepare for battle.\n");
        tell_room(environment(target), "A powerful Song of Battle fills " +
            "the air and seems to inspire " +QTNAME(target)+ " to acts " +
            "of bravery in battle.\n", ({ target }));
*/
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

    if (objectp(target))
    {
        if(caster != target)
        {
            caster->catch_tell("You feel the inspiration of your Song " +
               "of Battle leave " +target->query_the_name(caster)+ ".\n");
            target->catch_tell("You feel the inspiration from the Song " +
               "of Battle leave you.\n");
        }
        else
            caster->catch_tell("You feel the inspiration of your Song " +
               "of Battle leave you.\n");
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
        target->catch_tell("You feel the inspiration of the Song of Battle " + 
           "begin to wane.\n");
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
        caster->catch_tell("Mentally drained, you feel the inspiration of " +
           "the Song of Battle fade away.\n");
    }    
}
