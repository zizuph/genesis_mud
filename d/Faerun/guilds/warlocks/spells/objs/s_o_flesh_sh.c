/*
 * The shadow should be cloned when the effect is
 * added, and removed when the is gone. 
 *
 */
 
#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "objs/shadow_base_sh";

#include "../../guild.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

int strength_value, spell_power, mana_bonus;

object owner;
/*
 * Function:    initialize_shadow
 * Description: Should do all the initialization effects for this 
 *              particular shadow. Shadows derived from this one should
 *              override this.
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    spell_object->set_spell_effect_desc("sculptor of flesh");
    spell_power = spell_object->query_spell_effect_power();
}


void 
display_mana_message()
{
    string caster_message, watcher_message;
    caster_message = "An ethereal connection beyond time and "
    +"space injects your mind with additional power!\n";
    owner->catch_msg(caster_message);
    owner->add_mana(mana_bonus);
   
    set_alarm(60.0, 0.0, "display_mana_message");
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
    int transmute_bonus = (target->query_skill(SS_FORM_TRANSMUTATION) / 5);
    int caster_int = target->query_stat(SS_INT);
    int caster_str = target->query_stat(SS_STR);
    int caster_int_bonus = (caster_int - caster_str);
    
    if (objectp(target))
    {
        target->catch_tell("You grimace slightly as your body cracks "
        +"and snaps into a physically enhanced being.\n");
        
        tell_room(environment(target), "Eerie cracks and snaps echo into "
        +"the surroundings as "+QCTNAME(target)+" appears to grow "
        +"stronger.\n",    ({ target }));
        
    }    
    
    // spellcasters with lower strength but higher intelligence get higher 
    // bonuses to their strength. The bonus to strength will range from 
    // 10 to 40 max.
    if(caster_str < caster_int)
    {
        if(transmute_bonus > caster_int_bonus)
        {
            strength_value = transmute_bonus;
        }
        else
        {
            if(caster_int_bonus > 40)
            {
                strength_value = 40;
            }
            else
            { 
                strength_value = caster_int_bonus;
            }
        }
    }
    else
    {
        strength_value = transmute_bonus;
    } 
        
    target->set_stat_extra(SS_STR, target->query_stat_extra(SS_STR) 
    + strength_value);
    
    // Calculate mana bonus - max of 50 every 60 seconds
    mana_bonus = min(50, ftoi(itof(spell_power) / 7.0));
    
    owner = spell_object->query_effect_target();
    // Int/wis of 100, spell skills  50 / 75 / 100
    //     spell power:              284 / 302 / 317
    //     mana bonus:               40 / 43 / 45
    // Int/wis of 200, spell skills  50 / 75 / 100
    //     spell power:              348 / 364 / 384
    //     mana bonus:               49 / 50 / 50
    
    // spell_object->set_dispel_time(1800);
    set_alarm(10.0, 0.0, "display_mana_message");
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
    if (objectp(target))
    {
        target->catch_tell("You feel yourself shrinking as "
        +"Sculptor of Flesh wears off. Painful.\n");
        
        tell_room(environment(target), QCTNAME(target)+" grimaces "
        +"as "+target->query_pronoun()+" shrinks, strength fading away.\n",({ target }));
        
    }
    
    target->set_stat_extra(SS_STR, 
    target->query_stat_extra(SS_STR) - strength_value);
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
        target->catch_tell("You sense your Sculptor of Flesh spell is " 
        +"beginning to fade.\n");
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
            + "your Sculptor of Flesh spell.\n");
    }    
}