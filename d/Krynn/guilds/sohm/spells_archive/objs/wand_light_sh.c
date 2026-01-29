/*
 * Shadow for wand light spell for SOHM
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

#include "../defs.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

#define ACTIVE_ENCHANTMENT "_sohm_enchant_weapon_active"

int     flicker_alarm;

/*
 * Function:    initialize_shadow
 * Description: Should do all the initialization effects for this 
 *              particular shadow. Shadows derived from this one should
 *              override this.
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    spell_object->set_spell_effect_desc("light spell");
    // Maintenance of this spell is 6x higher, being a cantrip
    spell_object->set_maintain_mana(30);
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
    object owner = environment(target);

    if (objectp(target))
    {
        tell_room(owner, "Your " + target->short() + " suddenly glows with a bright light!\n", 
            ({ target }));
        tell_room(environment(owner), "The " + target->short() + " held by " + QTNAME(owner)+ " suddenly " +
                 "glows with a bright light, illuminating the surroundings.\n", ({ owner }));
    } 

    int old_light = this_object()->query_prop(OBJ_I_LIGHT);
    this_object()->add_prop(OBJ_I_LIGHT, old_light + 1);
    target->add_prop(ACTIVE_ENCHANTMENT, 1); 
  
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
    object caster = spell_object->query_effect_caster();
    object owner = environment(target);

    int old_light = this_object()->query_prop(OBJ_I_LIGHT);
    this_object()->add_prop(OBJ_I_LIGHT, old_light - 1);

    if (objectp(target))
    {
      if(living(owner))
      {
          caster->catch_msg("Your light spell on the " + shadow_who->short() +
              " expires.\n");
          tell_room(owner, "The " + shadow_who->short() + " suddenly dims, " +
              "and its glow fades away.\n", ({ target }));
          tell_room(environment(owner), "The " + shadow_who->short() +
              " held by " + QTNAME(owner)+ " suddenly dims, with its glow " +
              "fading away.\n", ({ owner }));
      }
      else
      {
          tell_room(environment(owner), "The " + shadow_who->short() + " in the " +
              owner->short()+ " suddenly dims, and its glow fades away.\n", 
              ({ target }));  
      }
    }

    target->remove_prop(ACTIVE_ENCHANTMENT);

}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading(object spell_object)
{
    object target = spell_object->query_effect_caster();
    
    if (objectp(target))
    {
        target->catch_tell("You sense the light spell on your " +
        shadow_who->short() + " is beginning to fade.\n");
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
            + "the light spell.\n");
    }    
}

public string 
short() 
{
    return "glowing " + shadow_who->short();
}

public string 
long(string str, object for_obj)
{
    return (shadow_who->long(str, for_obj) + "It is glowing brightly.\n");
}

private void
remove_spell_object()
{
    m_spell_object->set_dispel_time(2);
}

public mixed
command_unwield()
{
    mixed results = shadow_who->command_unwield();
    if (intp(results) && results == 1)
    {
        set_alarm(0.0, 0.0, &remove_spell_object());
    }
    return results;
}

public mixed
release()
{
    mixed results = shadow_who->release();
    if (results >= 0)
    {
        set_alarm(0.0, 0.0, &remove_spell_object());
    }
    return results;
}