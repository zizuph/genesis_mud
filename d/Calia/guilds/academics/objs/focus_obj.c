/*
 * Focus Object for Academics
 *
 * This is the spell object that will allow an academic to be elementally
 * focused enough to cast the cheiropoto spell.
 *
 * Created by Petros, Decemeber 2009
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>

#include "defs.h"

inherit "/d/Genesis/specials/std/spells/obj/spell_obj_base";

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_academic_focus_object_");
    set_short("academic focus object");    
    set_long("This is the standard focus object. It merely indicates whether "
        + "an Academic is focused or not.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created whenever an Academic focuses themselves.\n");
    set_spell_effect_desc("elemental focus");
    set_maintain_mana(0); // no need to charge mana to remain focused.   
}

/*
 * Function:    setup_spell_effect
 * Description: This is called to set up all the things for the
 *              spell. Must call the parent's setup_spell_effect
 *              in order to get the maintainence stuff.
 */
public int
setup_spell_effect()
{
    int result = ::setup_spell_effect();
    if (!result)
    {
        return result;
    }

    // 20-40 minutes.
    int duration = 1200 + random(1200);
    set_dispel_time(duration);
        
    return result;
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
        target->catch_tell("Your mind is aware of all the intricate workings "
            + "of the elemental energies that surround you. You feel "
            + "elementally focused!\n");
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
        target->catch_tell("You feel a sense of loss as your elemental focus "  
            + "dissipates.\n");
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
        target->catch_tell("You can sense yourself losing your elemental "
            + "focus.\n");
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
    // Do nothing.
}
