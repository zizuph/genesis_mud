/*
 * Ice strike spell for School of High Magic - Arman 2016
 */

#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "harm";

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
    set_spell_name("xarzithnar");
    set_spell_desc("Ice strike - a blast of destructive ice");

    set_spell_combat_aid(100.0);

    set_spell_class(SPELL_CLASS_4);
    set_spell_task(TASK_DIFFICULT); 

    set_ability_stats(STAT_WEIGHTING);

    // Low component requirement with potion charges
    set_spell_component_factor(COMPONENT_AID_LOW);

    // 2.5 times the standard cast time for a harm spell 
    set_spell_time_factor(2.5);     

    set_spell_element(SS_ELEMENT_WATER, 40);
    set_spell_form(SS_FORM_CONJURATION, 40);

    set_spell_resist(spell_resist_cold);
}

/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_harm_ingredients(object caster)
{
    // One herb, and the requirement to be wielding a staff or holding a wand. 
    return ({ "_xarzithnar_charge" });
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
    
    setuid();
    seteuid(getuid());
    return SOHM_MANAGER->query_memorised_spell(player,"xarzithnar_memorised");
}

int
filter_tool(object obj)
{
      if (obj->id("wand"))
        return 1;
      else if (obj->id("staff"))
        return 1;
      else if (obj->query_magic_spellpower())
        return 1;
      else 
        return 0;
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if (!caster->query_weapon(-1) && !caster->query_tool(-1))
    {
        caster->catch_tell("You need to be wielding a staff or holding a wand " +
              "to cast ice strike.\n");
        return 0;
    }

    object *weapon;

    /* Filter out non-staffs */
    if(caster->query_tool(-1))
      weapon = filter(caster->query_tool(-1), filter_tool);  

    if(!sizeof(weapon))
    {
        caster->catch_tell("You aren't wielding a staff or holding a wand " +
              "to cast ice strike.\n");
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
    object *wep;
    /* Filter out non-staffs and wands */
    wep = filter(caster->query_tool(-1), filter_tool);

        caster_message = "Your surroundings chill dramatically as you raise your " 
             +wep[0]->short()+ " and begin conjuring.\n";
        watcher_message = "Your surroundings chill dramatically as " +QTNAME(caster) +
            " raises " +caster->query_possessive()+ " " +wep[0]->short()+ ".\n";
        
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
        target_message = "A blast of cold air wails harmlessly past you.\n";
        watcher_message = "A blast of cold air wails harmlessly past " + QTNAME(target) + ".\n";
    }
    else
    {        
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "A blast of hailstones bounces off your "
                + hitloc_desc + ", doing no damage.\n";
            watcher_message = "A blast of hailstones bounces off " + QTPNAME(target)
                + " " + hitloc_desc + ", doing no damage.\n"; 
            break;
            
        case 1..2:
            target_message = "A spray of sharp icicles strike your " + hitloc_desc
                + " piercing you slightly.\n";
            watcher_message = "A spray of sharp icicles strike " + QTPNAME(target)
                + " in the " + hitloc_desc + ", piercing " + target->query_objective()
                + " slightly.\n";
            break;
            
        case 3..5:
            target_message = "A spray of sharp icicles strike your " + hitloc_desc + 
                " cutting you.\n";
            watcher_message = "A spray of sharp icicles strike " +QTNAME(target) + 
                " in the " + hitloc_desc + ", cutting " +target->query_objective()+ ".\n";
            break;
            
        case 6..9:
            target_message = "Ice spikes strike your " + hitloc_desc + 
                ", wounding you.\n";
            watcher_message = "Ice spikes strike " +QTNAME(target) + 
                " in the " + hitloc_desc + ", wounding " +target->query_objective()+ ".\n";
            break;
            
        case 10..15:
            target_message = "Spear-like spikes of ice strike your " + hitloc_desc + 
                ", seriously piercing you.\n";
            watcher_message = "Spear-like spikes of ice strike " +QTNAME(target) + 
                " in the " + hitloc_desc + ", seriously piercing " +target->query_objective()+ ".\n";
            break;
            
        case 16..25:
            target_message = "Your " + hitloc_desc + " is pierced by a jagged spear of "
                + " ice, penetrating you viciously.\n";
            watcher_message = QCTNAME(target) + " is pierced by a jagged spear of ice, " +
                "penetrating " + target->query_possessive() + " " + hitloc_desc + " viciously.\n";
            break;
            
        case 26..40:
            target_message = "Your " + hitloc_desc + " is shredded by savage spikes of ice, "
                + "causing severe damage.\n";
            watcher_message = QCTNAME(target) + " is shredded by savage spikes of ice, " +
                "causing severe damage to " + target->query_possessive() + " " + hitloc_desc + ".\n";
            break;
                    
        case 41..65:
            target_message = "A mighty lance of ice impales you brutally, penetrating your " +
                hitloc_desc + " and causing you grievous injuries.\n";
            watcher_message = "A mighty lance of ice impales " + QTPNAME(target) + 
                " brutally, penetrating " + target->query_possessive() + " " + hitloc_desc + 
                " and causing " +target->query_objective()+ " grievous injuries.\n";
            break;
            
        default:
            target_message = "A mighty lance of ice skewers you with deadly force, eviscerating your " 
                 +hitloc_desc + " and causing multiple fatal injuries.\n";
            watcher_message = "A mighty lance of ice skewers " + QTNAME(target) + " with deadly force, " +
                "eviscerating " + target->query_possessive()+ " " + hitloc_desc + 
                " and cause multiple fatal injuries.\n";
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

    object *wep;
    /* Filter out non-staffs and wands */
    wep = filter(caster->query_tool(-1), filter_tool);

        caster_message = "You point your " +wep[0]->short()+ " towards " + QTNAME(target) + 
            " and call out 'xarzith nar!'\n";
        target_message = QCTNAME(caster)+ " points " + caster->query_possessive() + " " +
            wep[0]->short()+ " towards you and calls out a word of power!\n";

        watcher_message = QCTNAME(caster)+ " points " + caster->query_possessive() + " " +
            wep[0]->short()+ " towards " + QTNAME(target) + " and calls out a word of power!\n";
    
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

/*
 * Function name: hook_no_ingredients_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have the right ingredients
 * Returns:       The message to print.
 */
public void
hook_no_ingredients_fail(mixed * ingredients_needed)
{
    write("You need to quaff a xarzithnar potion to be able to cast ice strike.\n");
}
