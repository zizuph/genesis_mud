/*
 * Toxic Blast spell for Sahuagin priestess
 */

#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include "/d/Krynn/common/defs.h"
#include CLOCKH

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
    set_spell_name("toxicblast");
    set_spell_desc("Toxic Blast - a toxic blast of virulent gases");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);

    set_spell_combat_aid(150.0);
    set_spell_task(TASK_ROUTINE);

    // the standard cast time for a harm spell 
    set_spell_time_factor(1.0);     

    set_spell_element(SS_ELEMENT_WATER, 50);
    set_spell_form(SS_FORM_CONJURATION, 60);

    set_spell_resist(spell_resist_poison);
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

    return 0;
}

/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{
     return 100.0;
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

    caster_message = "You call out to the Darkling Sea for her " +
        "destructive blessings.\n";
    watcher_message = QCTNAME(caster) +" raises " +caster->query_possessive()+ 
        " voice in a gurgling chant, calling upon the malevolent powers of " +
        "the Darkling Sea.\n";
        
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
    string ground_desc;

    if(environment(target)->query_prop(ROOM_I_INSIDE))
      ground_desc = "floor";
    else if(environment(target)->query_prop(ROOM_IN_WATER))
      ground_desc = "water";
    else if(environment(target)->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
      ground_desc = "water";
    else if(environment(target)->query_prop(ROOM_UNDER_WATER))
      ground_desc = "watery depths";
    else if(environment(target)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
      ground_desc = "watery depths";
    else if(environment(target)->query_prop(ROOM_BEACH))
      ground_desc = "beach";
    else if(environment(target)->query_prop(ROOM_I_TYPE) == ROOM_BEACH)
      ground_desc = "beach";
    else if(environment(target)->query_prop(ROOM_IN_AIR))
      ground_desc = "air";
    else if(environment(target)->query_prop(ROOM_I_TYPE) == ROOM_IN_AIR)
      ground_desc = "air";
    else
      ground_desc = "ground";

    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "A maisma of toxic fumes harmlessly surround you.\n";
        watcher_message = "A maisma of toxic fumes harmlessly surround " + 
            QTNAME(target) + ".\n";
    }
    else
    {        
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "A maisma of toxic gases strikes your " +hitloc_desc+ 
                ", doing no damage.\n";
            watcher_message = "A maisma of toxic gases strikes " + QTNAME(target)
                + " on the " + hitloc_desc + ", doing no damage.\n"; 
            break;
            
        case 1..5:
            target_message = "A maisma of toxic gases strikes your " + hitloc_desc
                + ", stinging you slightly.\n";
            watcher_message = "A maisma of toxic gases strikes " + QTNAME(target)
                + " in the " + hitloc_desc + ", stinging " + target->query_objective()
                + " slightly.\n";
            break;
            
        case 6..10:
            target_message = "A maisma of toxic gases strikes your " + hitloc_desc + 
                " mildly blighting you.\n";
            watcher_message = "A maisma of toxic gases strikes " +QTNAME(target) + 
                " in the " + hitloc_desc + ", mildly blighting " 
                +target->query_objective()+ ".\n";
            break;
            
        case 11..15:
            target_message = "A violent blast of dark toxic gases strikes your " + 
                hitloc_desc + " scourging you harshly.\n";
            watcher_message = "A violent blast of dark toxic gases strikes " +
                QTNAME(target) + " in the " + hitloc_desc + ", scourging " +
                target->query_objective()+ " harshly.\n";
            break;
            
        case 26..35:
            target_message = "A writhing column of poisonous gases blasts into " +
                "your " + hitloc_desc + ", harming you painfully.\n";
            watcher_message = "A writhing column of poisonous gases blasts into " +
                QTPNAME(target) + " " + hitloc_desc + ", harming " +
                target->query_objective()+ " painfully.\n";
            break;
            
        case 36..45:
            target_message = "A virulent column of poisonous gases blasts into " +
                "your " + hitloc_desc + ", shriveling it horribly.\n";                
            watcher_message = "A virulent column of poisonous gases blasts into " +
                QTPNAME(target) + " " + hitloc_desc + ", shriveling it horribly.\n";
            break;
            
        case 46..55:
            target_message = "Your " + hitloc_desc + " is engulfed by a mighty eruption of "
                + "black poisonous gases that explodes out of the " +ground_desc+ 
                ", causing severe damage.\n";
            watcher_message = QCTNAME(target) + " is engulfed by a mighty eruption of black " +
                "poisonous gases that explodes out of the " +ground_desc+ ", causing severe " +
                "damage to " + target->query_possessive() + " " +hitloc_desc+ ".\n";
            break;
                    
        case 56..99:
            target_message = "A mighty column of roiling poisonous gases erupts into you " +
                "from out of the " +ground_desc+ ", withering your " +hitloc_desc+ 
                " and causing you grievous injuries.\n";
            watcher_message = "A mighty column of roiling poisonous gases erupts into " + 
                QTNAME(target) + " from out of the "+ground_desc+ ", withering " + 
                target->query_possessive() + " " + hitloc_desc + " and causing " +
                target->query_objective()+ " grievous injuries.\n";
            break;
            
        default:
            target_message = "A raging explosion of noxious gases erupts from out of the "
                +ground_desc+ " and fatally engulfs you!\n";
            watcher_message = "A raging explosion of noxious gases erupts from out of the "+
                ground_desc+ " and fatally engulfs "+ QTNAME(target) + "!\n";
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
    object target = targets[0];

    caster_message = "You point towards " + QTNAME(target) + 
        " and summon the Darkling Sea.\n";
    target_message = QCTNAME(caster)+ " points " + caster->query_possessive() + " " +
        "clawed hand at you and calls out dark words of power.\n";

    watcher_message = QCTNAME(caster)+ " points " + caster->query_possessive() + " " +
        "clawed hand at " + QTNAME(target) + " and calls out dark words of power.\n";
    
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
