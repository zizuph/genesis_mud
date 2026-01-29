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
    set_spell_name("steamblast");
    set_spell_desc("Steam Blast - a blast of superheated steam");

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

    caster_message = "You begin drawing from the elemental realm of Water.\n";
    watcher_message = QCTNAME(caster) +" raises " +caster->query_possessive()+ 
        " had and begins drawing power from the Elemental Realm of water.\n";
        
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
        target_message = "The column of boiling water surges " +
            "harmlessly past you.\n";
        watcher_message = "The column of boiling water surges " +
            "harmlessly past " + QTNAME(target) + ".\n";
    }
    else
    {        
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "Boiling water splashes your "+ hitloc_desc +
                ", doing no damage.\n";
            watcher_message = "Boiling water splashes " + QTNAME(target)
                + " on the " + hitloc_desc + ", doing no damage.\n"; 
            break;
            
        case 1..5:
            target_message = "Boiling water splashes your " + hitloc_desc
                + " heating you slightly.\n";
            watcher_message = "Boiling water splashes " + QTPNAME(target)
                + " in the " + hitloc_desc + ", heating " + target->query_objective()
                + " slightly.\n";
            break;
            
        case 6..10:
            target_message = "Boiling water splashes your " + hitloc_desc + 
                " causing mild steaming.\n";
            watcher_message = "Boiling water " +QTNAME(target) + 
                " in the " + hitloc_desc + ", causing mild steaming.\n";
            break;
            
        case 11..25:
            target_message = "Boiling water strikes your " + hitloc_desc + 
                " causing blistering wounds.\n";
            watcher_message = "Boiling water strikes " +QTNAME(target) + 
                " in the " + hitloc_desc + ", causing blistering wounds.\n";
            break;
            
        case 26..35:
            target_message = "You are doused with boiling water, your " + 
                hitloc_desc + " seriously burnt.\n";
            watcher_message = QCTNAME(target) + " is doused with boiling " +
                "water from the geyser, " +HIS(target)+ " " + hitloc_desc +
                " seriously burnt.\n";
            break;
            
        case 36..45:
            target_message = "Your " + hitloc_desc + " is drenched by " +
                "the geyser, painfully scalded by the boiling water.\n";
            watcher_message = QCTNAME(target) + " is drenched by the " +
                "geyser, the boiling water painfully scalding " +
                target->query_possessive() + " " + hitloc_desc + ".\n";
            break;
            
        case 46..55:
            target_message = "Your " + hitloc_desc + " is excoriated " +
                "by the broiling geyser, causing severe damage.\n";
            watcher_message = QCTNAME(target) + " is excoriated by the " +
                "broiling geyser, causing severe damage to " + 
                target->query_possessive() + " " + hitloc_desc + ".\n";
            break;
                    
        case 56..99:
            target_message = "The superheated geyser engulfs you, flaying your " +
                hitloc_desc + " and causing you grievous injuries.\n";
            watcher_message = "The superheated geyser engulfs " + QTNAME(target) + ", flaying " + 
                HIS(target)+ " " + hitloc_desc + " and causing grievous injuries.\n";
            break;
            
        default:
            target_message = "The superheated geyser consumes you, " +
                 "boiling to pieces your " + hitloc_desc + 
                 " and causing multiple fatal injuries.\n";
            watcher_message = "The superheated geyser consumes "
                + QTNAME(target) + ", boiling to pieces " + target->query_possessive()
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
    object target = targets[0];

    caster_message = "You point your hand towards " +
        QTNAME(target) + " and call out a word of power, releasing " +
        "a column of boiling water in " +HIS(target)+ " direction.\n";
    target_message = QCTNAME(caster)+ " points " + caster->query_possessive() + " " +
        "hand towards you and calls out a word of power, " +
        "releasing a column of boiling water at you!\n";
    watcher_message = QCTNAME(caster)+ " points " + caster->query_possessive() + 
            " hand towards " + QTNAME(target) + 
            " and calls out a word of power, releasing a column of " +
            "boiling water!\n";
    
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
