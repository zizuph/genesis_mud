/* 
 * phearing - true hearing
 * 
 * This is a shadow for spell effects. It gets cloned by the shadow
 * spell object. One should inherit from this shadow only when defining shadow
 * effects. The shadow_obj.c file should automatically clone the right shadow.
 *
 * The shadow should be cloned when the effect is
 * added, and removed when the is gone. 
 *
 */
#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/specials/std/spells/obj/shadow_base_sh";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

#include "../../guild.h"
#include "/d/Ansalon/common/defs.h"

int spell_power;
object  effect_owner;

/*
 * Function:    initialize_shadow
 * Description: Should do all the initialization effects for this 
 *              particular shadow. Shadows derived from this one should
 *              override this.
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    spell_object->set_spell_effect_desc("phear");
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
    int level = target->query_priest_level();

    target->catch_tell("You close your eyes. When you open them again you " +
        "almost feel overwhelmed by the myriad of sounds that are all around you.\n");
    tell_room(environment(target), QCTNAME(target) + " closes " +HIS(target)+ 
        " eyes suddenly, slowly reopening them like a serpent awakening.\n", 
        ({ target }));
   
    switch(level) 
    {
      case 2:
      {
        spell_power = 24 + random(5);
        break;
      }
      case 1:
      {
        spell_power = 16 + random(5);
        break;
      }  
      case 0:
      {
        spell_power = 8 + random(5);
        break;
      } 
      default:
      {
        spell_power = 8;
        break;
      } 
    }

    effect_owner = target;

    effect_owner->set_skill_extra(SS_LANGUAGE, 
         effect_owner->query_skill_extra(SS_LANGUAGE) + spell_power);
    effect_owner->set_skill_extra(SS_AWARENESS, 
         effect_owner->query_skill_extra(SS_AWARENESS) + spell_power);

    spell_object->set_dispel_time(1200);

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

    effect_owner->set_skill_extra(SS_LANGUAGE, 
         effect_owner->query_skill_extra(SS_LANGUAGE) - spell_power);
    effect_owner->set_skill_extra(SS_AWARENESS, 
         effect_owner->query_skill_extra(SS_AWARENESS) - spell_power);

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        target->catch_tell("Suddenly it grows quieter.\n");
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
        target->catch_tell("You feel the effects of your prayer of hearing " +
            "begin to wane.\n");
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
        caster->catch_tell("Suddenly it grows quieter.\n");
    }    
}

