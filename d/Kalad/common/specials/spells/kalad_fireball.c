/*
 * Created by Zignur 2017-11-10
 * A fireball used by Urians mage in Kalad
 *
 *  2021-08-22 Meton fixed typo slighlty to slightly
 *  2021-08-22 Meton fixed typo evily to evilly
 */

#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

inherit "/d/Genesis/specials/std/spells/harm";

/*
 * Function:    config_harm_spell
 * Description: Config function for harm spells. Redefine this in your
 *              own harm spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_harm_spell()
{
    set_spell_name("fireball");
    set_spell_desc("Fireball - summon a fireball");
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(150.0);
    set_spell_task(TASK_HARD); 

    set_spell_element(SS_ELEMENT_FIRE, 40);
    set_spell_form(SS_FORM_CONJURATION, 40);

}

/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_harm_ingredients(object caster)
{
    // no regents required
    return ({ "" });
}


/*
 * Function:    query_spell_can_be_learned
 * Description: See if the user can learn/use the spell
 * Arguments:   object player
 * Returns:     1 Success 0 Fail
 */
public int
query_spell_can_be_learned(object player)
{
    if (!objectp(player))
    {
        return 0;
    }
    
    if (player->query_npc())
    {
        // npcs can always learn the spell.
        return 1;
    }
    
    return 1;
}

/*
 * Function:    check_valid_action
 * Description: check if the spell can be used.
 * Arguments:   object caster, mixed * targets, string arg, int execute
 * Returns:     1 Success 0 Fail
 */
public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if(caster->query_skill(SS_SPELLCRAFT) < 10)
    {
       caster->catch_tell("You need to be trained in spellcraft to at least " +
           "superior student to cast this spell.\n");
       return 0;
     }
  
    return 1;
}

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1.  object    The caster
 *                2.  mixed *   The targets
 *                3.  string    The arguments passed to the "cast" command
 */
public void
concentrate_msg(object caster, mixed * targets, string arg)
{
    string caster_message, watcher_message;

        caster_message = "Your eyes glow with black flames as you start to"
            + " chant in the ancient language of magic, 'Fireball!'\n";
        watcher_message = QCTNAME(caster) + " eyes glow with black flames as"
            +" he chants in an ancient language.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }));  
    
    setuid();
    seteuid(getuid());  
}

/*
 * Function name: desc_harm_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                mixed *result - return value from harm's hit_me.
 */
public void
desc_harm_damage(object caster, object target, mixed *result)
{
    string caster_message, target_message, watcher_message;
    int phurt = result[0];
    string hitloc_desc = result[1];

    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "The blazing fireball flies harmlessly past you.\n";
        watcher_message = "The blazing fireball flies harmlessly past " + 
        QTNAME(target) + ".\n";
    }
    else
    {        
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "The fireball barely touches your "+ hitloc_desc +
            ", doing no damage.\n";
            watcher_message = "The fireball barely touches " + QTNAME(target)
                + " on the " + hitloc_desc + ", doing no damage.\n"; 
            break;
            
        case 1..15:
            target_message = "The fireball hits your " + hitloc_desc
                + " burning you slightly.\n";
            watcher_message = "The fireball hits " + QTPNAME(target)
                + " in the " + hitloc_desc + ", burning " +
                target->query_objective()
                + " slightly.\n";
            break;
                      
        case 16..65:
            target_message = "The fireball slams into your " + hitloc_desc
                + " causing severe burns.\n";
           watcher_message = "The fireball slams into " + QTPNAME(target)
                + "'s " + hitloc_desc + ", causing severe burns.\n";
            break;
       
        default:
            target_message = "The fireball consumes you, nearly burning your " 
                 +hitloc_desc + " so cinders.\n";
            watcher_message = "The fireball consumes "
                + QTNAME(target) + ", nearly burning " + 
                target->query_possessive()+ " " + hitloc_desc + " to "+
                "cinders.\n";
            break;
        }
    }
        
    caster->catch_msg(watcher_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
}

/*
 * Function name: desc_harm_cast
 * Description:   Describe casting of the spell, not including damage messages.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_harm_cast(object caster, object * targets)
{
    string caster_message, target_message, watcher_message;
    object target;
    
    target = targets[0];

        caster_message = "You raise your hands and point a bony finger at " + 
            QTNAME(target) + " and cackle evilly conjuring a massive " +
            "fireball in " +HIS(target)+ " direction.\n";
        target_message = QCTNAME(caster)+ " raises his hands and points a "+
            "bony finger towards you and cackles evilly while conjuring a " +
            "massive fireball, releasing it at you.\n";

        watcher_message = QCTNAME(caster)+ " raises his hands and points a " +
            "bony finger at "+ QTNAME(target) + " while conjuring a "+
            "massive fireball.\n";
    
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
}

/*
 * Function:    resolve_harm_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_harm_spell(object caster, object *targets, int *resist, int result)
{
   
}

/*
 * Function name: hook_no_ingredients_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have the right ingredients
 * Returns:       The message to print.
 */
public void
hook_no_ingredients_fail(mixed * ingredients_needed)
{
    write("You need a regent.\n");
}
