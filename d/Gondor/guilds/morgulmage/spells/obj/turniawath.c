#pragma strict_types
#pragma save_binary

#include <macros.h>
#include "../../morgulmage.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "resistance_obj";

#define _NO_PREP_TIME_ADJUSTMENT
#include "../generic_functions.c"

public void 
create_spell_object()
{
    set_name("_turniawath_object_");
    set_short("resistance spell object");    
    set_long("This is the standard resistance spell's object.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the morgul mage turniawath spell.\n");
    set_spell_effect_desc("Shadow Shield");    
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
        target->catch_tell("Augmented by the flames, your undead flesh "
            + "crackles and tightens. As the wisps of smoke trail into "
            + "the air, your burns harden to a protective black scar.\n");
        can_see_caster(target)->catch_msg(QCTNAME(target) + " remains "
            + "still, as the wisps of smoke trail from " 
            + target->query_possessive() + " now blackened flesh "
            + "and disperse.\n", target);
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
        target->catch_tell("With a crackling sound, your scarred protective"
            + " coating crumbles and falls from you, clouding the area with"
            + " billows of ash.\n");
        can_see_caster(target)->catch_msg(QCTPNAME(target) + " scarred flesh"
          + " suddenly sloughs off with a crackling sound, clouding the area"
          + " with billows of ash.\n", target);  

        setuid();
        seteuid(getuid());

        object ashes = clone_object(MORGUL_SPELL_OBJ_DIR + "ashes");
        ashes->move(environment(target));
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
        target->catch_tell("You suddenly notice that your protective scarred"
            + " flesh is beginning to show cracks!\n");
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
        caster->catch_tell("You feel your mental fatigue overcoming your"
            + " ability to maintain your scarred protective flesh any"
            + " longer.\n");
    }    
}
