/*
 * Shadow Veil Shadow for SOHM 
 *
 */
 
#pragma strict_types
#pragma save_binary

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "shadow_base_sh";

#include "../defs.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"

int skill_bonus, spell_power, sneak_hack, hide_hack, backstab_hack;

public int
query_has_shadow_veil_shadow()
{
     return 1;
}

/*
 * Function:    initialize_shadow
 * Description: Should do all the initialization effects for this 
 *              particular shadow. Shadows derived from this one should
 *              override this.
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    spell_object->set_name("_shadow_veil_spell_obj_");
    spell_object->set_spell_effect_desc("shadow veil");
    spell_power = spell_object->query_spell_effect_power();
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started(object spell_object)
{
    object target = spell_object->query_effect_target();

    // WoHS skill bonus +20 to +60, dependant on illusion spell form  
    // SoHM skill bonus +20 to +50, due to max skill of 75 for illusion 
    skill_bonus = (max(20, min(60, target->query_skill(SS_FORM_ILLUSION) - 25)));


    if (objectp(target))
    {
        target->catch_tell("You feel the shadows around you grow and embrace you, making " +
           "you less perceptible when being stealthy.\n");
        tell_room(environment(target), "The shadows around " +QTNAME(target) + " seem " +
           "to grow and embrace " +HIM(target)+ ", making " +HIM(target)+ " less perceptible.\n", 
            ({ target }));
    }    

    // Because set_skill_extra doesn't work if skill is zero,
    // putting in a hack until fixed to give the caster one point
    // of skill so it works. Removed in hook_spell_effect_ended
    if(!target->query_skill(SS_SNEAK))
    {
      sneak_hack = 1;
      target->set_skill(SS_SNEAK, 1);
    }

    if(!target->query_skill(SS_HIDE))
    {
      hide_hack = 1;
      target->set_skill(SS_HIDE, 1);
    }

    if(!target->query_skill(SS_BACKSTAB))
    {
      backstab_hack = 1;
      target->set_skill(SS_BACKSTAB, 1);
    }

    target->set_skill_extra(SS_SNEAK, 
         target->query_skill_extra(SS_SNEAK) + skill_bonus);
    target->set_skill_extra(SS_HIDE, 
         target->query_skill_extra(SS_HIDE) + skill_bonus);
    target->set_skill_extra(SS_BACKSTAB, 
         target->query_skill_extra(SS_BACKSTAB) + skill_bonus);

    spell_power = spell_object->query_spell_effect_power();
    // Power determines how long the spell lasts
    // int duration = ftoi(itof(spell_power) * 10.0);

    // spell_object->set_dispel_time(get_default_spell_time());

}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended(object spell_object)
{
    object target = spell_object->query_effect_target();

    target->set_skill_extra(SS_SNEAK, 
         target->query_skill_extra(SS_SNEAK) - skill_bonus);
    target->set_skill_extra(SS_HIDE, 
         target->query_skill_extra(SS_HIDE) - skill_bonus);
    target->set_skill_extra(SS_BACKSTAB, 
         target->query_skill_extra(SS_BACKSTAB) - skill_bonus);

    if(sneak_hack)
    {
      target->set_skill(SS_SNEAK, target->query_skill(SS_SNEAK) - 1);
    }

    if(hide_hack)
    {
      target->set_skill(SS_HIDE, target->query_skill(SS_HIDE) - 1);
    }

    if(backstab_hack)
    {
      target->set_skill(SS_BACKSTAB, target->query_skill(SS_BACKSTAB) - 1);
    }

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        target->catch_tell("The shadowy veil surrounding you suddenly dissipates, leaving " +
           "you feeling less stealthy.\n");
    }  
  
}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading(object spell_object)
{
    object target = spell_object->query_effect_target();
    
    if (objectp(target))
    {
        target->catch_tell("You sense your shadowy veil illusion is " +
            "beginning to wane.\n");
    }
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained(object spell_object)
{
    object caster = spell_object->query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
            + "your shadowy veil illusion.\n");
    }    
}
