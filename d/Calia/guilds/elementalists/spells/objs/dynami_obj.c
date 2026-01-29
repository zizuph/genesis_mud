/*
 * Stat Boost Spell Object (Dynami) for the Elementalists of Calia
 *
 * This is the spell object based on the standand stat boost spell object
 * maintained in the Genesis Magic System.
 *
 * Created by Petros, August 2011
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>

#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "statboost_obj";

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_dynami_object_");
    set_short("dynami spell object");    
    set_long("This is the stat boost spell's object for dynami. It temporarily "
        + "increases one's stats.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "This is a spell object "
                          + "created by the dynami spell. It will temporarily "
                          + "increase con, and int of Elemental Clerics.\n");
    set_spell_effect_desc("increase health and mana pools");    
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
        target->catch_tell("You feel physically stronger, more sturdy, and "
            + "mentally more focused.\n");
        tell_room(environment(target), QCTNAME(target) + " glows briefly, "
            + "appearing strengthened.\n", ({ target }));
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
        target->catch_tell("The enchantment gifted by Lady Gu dissipates, "
            + "returning your body and mind to normal.\n");
        tell_room(environment(target), QCTPNAME(target) + " skin "
            + "seems to lose a bit of luster.\n", ({ target }));
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
        target->catch_tell("You feel the gift of dynami begin to weaken.\n");
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
            + "the gift of dynami.\n");
    }    
}


