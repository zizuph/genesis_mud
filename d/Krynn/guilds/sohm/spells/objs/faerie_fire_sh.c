/*
 * Spell Shadow for SOHM
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

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "shadow_base_sh";

#include "../defs.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

#define ACTIVE_ENCHANTMENT "_sohm_enchant_weapon_active"

public varargs string glowing_short();

public object            oldwf;
// public mixed             unwield(object obj);

int     flicker_alarm, spell_power, light_bonus;
mixed   original_short;

/*
 * Function:    initialize_shadow
 * Description: Should do all the initialization effects for this 
 *              particular shadow. Shadows derived from this one should
 *              override this.
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    spell_object->set_spell_effect_desc("faerie fire");
    spell_power = spell_object->query_spell_effect_power();
    oldwf = shadow_who->query_wf();
    shadow_who->set_wf(shadow_who);
}

void 
display_flicker_message()
{
    object owner = environment(shadow_who);
    string caster_message, watcher_message;

    switch (random(2))
    {
     case 0:
       caster_message = "Your surroundings are dimly illuminated by the pale "+
            "violet enchantment surrounding your " + original_short + ".\n";
       watcher_message = "Your surroundings are dimly illuminated by the " +
            "pale violet enchantment surrounding " +
            "the " + original_short + " held by " + QTNAME(owner)+ ".\n";
     break;
     case 1:
     default:
       caster_message = "Your " + original_short + " flickers with a pale " +
             "violet glow.\n";
       watcher_message = "The " + original_short + " held by " + QTNAME(owner)+
              " flickers with a pale violet glow.\n";
     break;
    }

    owner->catch_msg(caster_message);
    tell_room(environment(owner), watcher_message, ({ owner }), owner);
   
    set_alarm(60.0, 0.0, "display_flicker_message");
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

    int power = spell_power;

    if (objectp(target))
    {
        tell_room(owner, "The " + target->short() + " is outlined in a violet "+
            "glow.\n", ({ target }));
        tell_room(environment(owner), "The " + target->short() + " is " +
            "outlined in a violet glow.\n", ({ owner }));
    } 

    original_short = target->short(); 
    target->set_short(glowing_short);

    // int duration = ftoi(itof(power) * 5.0);

    spell_object->set_dispel_time(get_default_spell_time());

    light_bonus = min(5, max(1, (power - 220) / 30));

    // Int/wis of 100, spell skills 20 / 50 / 75 / 100
    //             spell power:  269 / 284 / 302 / 317
    //             light bonus:   1 / 2 / 2 / 3
    //             duration: 1345 / 1420 / 1510 / 1585

    // Int/wis of 200, spell skills  50 / 75 / 100
    //             spell power:    348 / 364 / 384 
    //             light bonus:     4 / 4 / 5
    //             duration:    1720 / 1820 / 1920

    //owner->catch_msg("Spell power: "+power+".\n");
    //owner->catch_msg("Duration: "+duration+".\n");
    //owner->catch_msg("Light: "+light_bonus+".\n");

    int old_light = this_object()->query_prop(OBJ_I_LIGHT);
    this_object()->add_prop(OBJ_I_LIGHT, old_light + light_bonus); 
    target->add_prop(ACTIVE_ENCHANTMENT, 1); 

    set_alarm(10.0, 0.0, "display_flicker_message");    
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
    this_object()->add_prop(OBJ_I_LIGHT, old_light - light_bonus);

    if (objectp(target))
    {
      if(living(owner))
      {
        caster->catch_msg("Your faerie fire enchantment on the " + 
            original_short + " expires.\n");
        tell_room(owner, "The " +original_short+ " is no longer outlined in a "+
            "violet glow.\n", ({ target }));
        tell_room(environment(owner), "The " + original_short + " held by " 
            + QTNAME(owner)+ 
            " is no longer outlined in a violet glow.\n", ({ owner }));
      }
      else
      { 
        tell_room(environment(owner), "The " + original_short + " in " 
            + owner->short()+ " is no longer outlined in a violet glow.\n", 
            ({ owner })); 
       }
    }

    target->set_short(original_short);
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
        target->catch_tell("You sense the faerie fire spell on your " 
              + original_short + " is beginning to fade.\n");
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
            + "the faerie fire spell.\n");
    }    
}

public varargs string 
glowing_short() 
{
    string text;
    if (functionp(original_short)) 
    {
        text = shadow_who->check_call(original_short);
    }
    else 
    {
        text = original_short;
    }
    
    return "glowing " + text;
}

string 
long(string str, object for_obj)
{
    return (shadow_who->long(str, for_obj) 
        + "It is outlined in a cold violet glow, shedding a pale light on " +
           "your surroundings.\n");
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

/*
public mixed
unwield(object obj)
{
    
    mixed res = oldwf->unwield(obj);
    if (stringp(res)) return res;
    if ((res >= 0) && (calling_function(-3) != "recursive_rm"))
    {
        set_alarm(0.0, 0.0, &remove_spell_object());
    }
    return res;
} 

public mixed
command_unwield()
{
    set_alarm(0.0, 0.0, &remove_spell_object());
    return 1;
}
*/

public void
leave_env(object from, object to)
{
    set_alarm(0.0, 0.0, &remove_spell_object());
}