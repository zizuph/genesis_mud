/*
 * Object for quick reflex ability
 */

#pragma strict_types
#pragma save_binary

#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/warfare/warfare.h"
#include <wa_types.h>

inherit "/d/Genesis/specials/std/spells/obj/haste_obj";

#define MW_HASTE_EFFECT "_mw_haste_effect"

object helm; 

public void 
create_spell_object()
{
    set_name("_mw_haste_object_");
    set_short("haste spell object");    
    set_long("This is the standard haste spell's object. It makes "
        + "one faster.\n");
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the haste spell.\n");
    set_spell_effect_desc("enhanced reflexes");  
    set_dispel_time(1200);  
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
    helm = target->query_armour(TS_HEAD);
    string helm_str = helm->query_short();

    if (objectp(target))
    {
        target->catch_tell("You feel your vision sharpen through your " +
            helm_str+ " and your reflexes quicken.\n");
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
    string helm_str = helm->query_short();

    if (objectp(target))
    {
        target->catch_tell("You feel the enhanced reflex enchantment " +
            "surrounding your " +helm_str+ " vanish.\n");
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
    string helm_str = helm->query_short();
    
    if (objectp(target))
    {
        target->catch_tell("You feel the enhanced reflex enchantment " +
            "surrounding your " +helm_str+ " begin to fade.\n");
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
    string helm_str = helm->query_short();
    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
            + "the enhanced reflexes enchantment.\n");
    }    
}
