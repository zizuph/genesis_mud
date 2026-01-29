/*
 * Evimero (Haste) Spell Effect Object
 *
 * This is the spell object based on the the standard Genesis Magic 
 * System Haste spell. 
 *
 * Created by Petros, December 2010
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "defs.h"

inherit "/d/Genesis/specials/std/spells/obj/haste_obj";

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_evimero_object_");
    set_short("evimero spell object");    
    set_long("This is the standard haste spell's object. It causes "
        + "one to move faster.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the evimero spell.\n");
    set_spell_effect_desc("haste");
    
    set_dispel_time(1800);
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
        target->catch_tell("The world around you suddenly slows and all "
            + "seems to move sluggishly. You feel revitalized and ready "
            + "to tackle the world with the fury of the whirlwind!\n");
        tell_room(environment(target), QCTNAME(target) + " begins to move "
            + "more quickly.\n", ({ target }));
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
        target->catch_tell("The enchantment granted by Lady Aeria dissipates, "
            + "and the world around you seems to move normally again.\n");
        tell_room(environment(target), QCTNAME(target) + " seems to slow "
            + "down.\n", ({ target }));
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
        target->catch_tell("You sense that the gift of evimero is beginning "
            + "to dissipate.\n");
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
            + "the gift of evimero.\n");
    }    
}
