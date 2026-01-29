/*
 * Aurak npc flame special attack - Arman 2018
 */

#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include "defs.h"
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

    set_spell_name("aurakfire");
    set_spell_desc("A burst of elemental fire damage");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(200.0);
    set_spell_task(TASK_HARD);

    // 1.5 times the standard cast time for a harm spell 
    set_spell_time_factor(1.5);     

    set_spell_element(SS_ELEMENT_FIRE, 20);
    set_spell_form(SS_FORM_CONJURATION, 20);
}

/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_harm_ingredients(object caster)
{ 
    return ({  });
}

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

    if (player->query_race_name() != "aurak")
    {
        return 0;
    }
    
    return 1;
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    return 1;
}

// HOOKS TO BE DEFINED

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (mixed *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */
public void
concentrate_msg(object caster, mixed * targets, string arg)
{
    string caster_message, watcher_message;

    caster_message = "You raise your clawed hands and call upon your innate " +
        "draconian power to summon elemental fire.\n";
    watcher_message = QCTNAME(caster) +" raises " +HIS(caster)+ 
        " clawed hands and calls upon " +HIS(caster)+ " innate draconic " +
        "powers.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);
    
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

    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "The column of flame roars harmlessly past you.\n";
        watcher_message = "The column of flame roars harmlessly past " + QTNAME(target) + ".\n";
    }
    else
    {        
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "The column of flame warms your "
                + hitloc_desc + ", doing no damage.\n";
            watcher_message = "The column of flame warms " + QTNAME(target)
                + " on the " + hitloc_desc + ", doing no damage.\n"; 
            break;
            
        case 1..2:
            target_message = "The column of flame strikes your " + hitloc_desc
                + " singeing you slightly.\n";
            watcher_message = "The column of flame strikes " + QTNAME(target)
                + " in the " + hitloc_desc + ", singeing " + target->query_objective()
                + " slightly.\n";
            break;
            
        case 3..5:
            target_message = "The column of flame strikes your " + hitloc_desc + 
                " mildly scorching you.\n";
            watcher_message = "The column of flame strikes " +QTNAME(target) + 
                " in the " + hitloc_desc + ", mildly scorching " +target->query_objective()+ ".\n";
            break;
            
        case 6..9:
            target_message = "The column of flame strikes your " + hitloc_desc + 
                " causing burning wounds.\n";
            watcher_message = "The column of flame strikes " +QTNAME(target) + 
                " in the " + hitloc_desc + ", causing burning wounds.\n";
            break;
            
        case 10..15:
            target_message = "A powerful lance of flame strikes your " + hitloc_desc + 
                ", seriously burning you.\n";
            watcher_message = "A powerful lance of flame strikes " +QTNAME(target) + 
                " in the " + hitloc_desc + ", seriously burning " +target->query_objective()+ ".\n";
            break;
            
        case 16..25:
            target_message = "Your " + hitloc_desc + " is blasted by a powerful lance of "
                + " flame, broiling you painfully.\n";
            watcher_message = QCTNAME(target) + " is blasted by a powerful lance of flame, " +
                "broiling " + target->query_possessive() + " " + hitloc_desc + " painfully.\n";
            break;
            
        case 26..40:
            target_message = "Your " + hitloc_desc + " is engulfed by a mighty column of fire, "
                + "causing severe damage.\n";
            watcher_message = QCTNAME(target) + " is engulfed in a mighty column of fire, " +
                "causing severe damage to " + target->query_possessive() + " " + hitloc_desc + ".\n";
            break;
                    
        case 41..65:
            target_message = "A mighty column of fire detonates into you, melting your " +
                hitloc_desc + " and causing you grievous injuries.\n";
            watcher_message = "A mighty column of fire detonates into " + QTNAME(target) + 
                ", melting " + target->query_possessive() + " " + hitloc_desc + 
                " and causing " +target->query_objective()+ " grievous injuries.\n";
            break;
            
        default:
            target_message = "A raging column of hellfire detonates into you " +
                "with deadly force, exploding apart your " +hitloc_desc + 
                 " and causing multiple fatal injuries.\n";
            watcher_message = "A raging column of hellfire detonates into "
                + QTNAME(target) + " with deadly force, exploding apart " + target->query_possessive()
                + " " + hitloc_desc + " and causing multiple fatal injuries.\n";
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

    caster_message = "Your clawed hands are suddenly engulfed in elemental fire, " +
        "and you direct it towards " + QTNAME(target) + ".\n";
    target_message = QCTPNAME(caster)+ " clawed hands are suddenly engulfed in " +
        "elemental fire, which " +HE(caster)+ " directs towards you!\n";
    watcher_message = QCTPNAME(caster)+ " clawed hands are suddenly engulfed in " + 
        "elemental fire, which " +HE(caster)+ " directs towards " +QTNAME(target)+ "!\n";
    
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    caster->tell_watcher(watcher_message, targets, ({ caster }) + targets);    
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


