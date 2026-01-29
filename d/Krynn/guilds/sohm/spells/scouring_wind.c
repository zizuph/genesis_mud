/*
 * Scouring wind for School of High Magic - Arman 2016
 */

#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include <stdproperties.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"

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
    set_spell_name("iniksuaco");
    set_spell_desc("Scouring wind - conjure a damaging sandstorm");

    set_spell_combat_aid(100.0);

    set_ability_stats(STAT_WEIGHTING);

    // Low component requirement with potion charges
    set_spell_component_factor(COMPONENT_AID_LOW);

    set_spell_class(SPELL_CLASS_4);
    set_spell_task(TASK_DIFFICULT); 

    set_spell_time_factor(1.5); 

    set_spell_element(SS_ELEMENT_AIR, 40);
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
    // One herb, and the requirement to be wielding a staff or holding a wand. 
    return ({ "_suaco_charge" });
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
    return SOHM_MANAGER->query_memorised_spell(player,"iniksuaco_memorised");
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
        caster->catch_tell("You need to be wielding a staff or holding " +
            "a wand to cast scouring wind.\n");
        return 0;
    }

    object *weapon;

    /* Filter out non-staffs */
    if(caster->query_tool(-1))
      weapon = filter(caster->query_tool(-1), filter_tool);  

    if(!sizeof(weapon))
    {
        caster->catch_tell("You aren't wielding a staff or holding a " +
            "wand to cast scouring wind.\n");
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

    caster_message = "You spin your " +wep[0]->short()+ " through the air " +
        "while tracing mystical runes of magic, summoning the powers of a " +
        "sandstorm.\n";
    watcher_message = QCTNAME(caster) +" spins " + caster->query_possessive() 
        + " " +wep[0]->short()+ " through the air while tracing " +
        "mystical symbols.\n";
        
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
        target_message = "The sandstorm howls harmlessly past you.\n";
        watcher_message = "The sandstorm howls harmlessly past " + 
            QTNAME(target) + ".\n";
    }
    else
    {        
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "Sand tickles your "+ hitloc_desc + 
                ", doing no damage.\n";
            watcher_message = "Sand tickles " + QTNAME(target)
                + " on the " + hitloc_desc + ", doing no damage.\n"; 
            break;
            
        case 1..2:
            target_message = "Sand strikes your " + hitloc_desc
                + " chafing you slightly.\n";
            watcher_message = "Sand strikes " + QTNAME(target)
                + " in the " + hitloc_desc + ", chafing " + target->query_objective()
                + " slightly.\n";
            break;
            
        case 3..5:
            target_message = "Sand strikes your " + hitloc_desc + 
                " causing mild scouring.\n";
            watcher_message = "Sand strikes " +QTNAME(target) + 
                " in the " + hitloc_desc + ", causing mild scouring.\n";
            break;
            
        case 6..9:
            target_message = "Sand strikes your " + hitloc_desc + 
                " causing abrading wounds.\n";
            watcher_message = "Sand strikes " +QTNAME(target) + 
                " in the " + hitloc_desc + ", causing abrading wounds.\n";
            break;
            
        case 10..15:
            target_message = "The sandstorm engulfs you, your " + hitloc_desc + 
                " seriously shredded.\n";
            watcher_message = "The sandstorm engulfs " +QTNAME(target) + 
                ", " +HIS(target)+ " " + hitloc_desc + " seriously shredded.\n";
            break;
            
        case 16..25:
            target_message = "Your " + hitloc_desc + " is blasted by the "
                + "sandstorm,  painfully cut to ribbons by whirling debris.\n";
            watcher_message = QCTNAME(target) + " is blasted by the " +
                "sandstorm, the whirling debris cutting " +
                target->query_possessive() + " " + hitloc_desc + 
                " to ribbons.\n";
            break;
            
        case 26..40:
            target_message = "Your " + hitloc_desc + " is excoriated by " +
               "the powerful sandstorm, causing severe damage.\n";
            watcher_message = QCTNAME(target) + " is excoriated by the " +
                "powerful sandstorm, causing severe damage to " + 
                target->query_possessive() + " " + hitloc_desc + ".\n";
            break;
                    
        case 41..65:
            target_message = "The raging sandstorm engulfs you, flaying " +
                "your " + hitloc_desc + " with debris and causing you " +
                "grievous injuries.\n";
            watcher_message = "The raging sandstorm engulfs " + QTNAME(target) 
                + ", flaying " + HIS(target)+ " " + hitloc_desc + 
                ", causing grievous injuries.\n";
            break;
            
        default:
            target_message = "The raging sandstorm consumes you, tearing " +
                "apart your " +hitloc_desc + " and causing multiple " +
                "fatal injuries.\n";
            watcher_message = "The raging sandstorm consumes "
                + QTNAME(target) + ", tearing apart " + target->query_possessive()
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

    object *wep;
    /* Filter out non-staffs and wands */
    wep = filter(caster->query_tool(-1), filter_tool);

    caster_message = "You point your " +wep[0]->short()+ " towards " + 
        QTNAME(target) +  " and call out 'Inik Suaco!' - unleashing " +
        "a sandstorm in " +HIS(target)+ " direction.\n";
    target_message = QCTNAME(caster)+ " points " + caster->query_possessive() 
        + " " + wep[0]->short()+ " towards you and calls out a word of " +
        "power, unleashing a sandstorm towards you!\n";

    watcher_message = QCTNAME(caster)+ " points " + caster->query_possessive() 
        + " " + wep[0]->short()+ " towards " + QTNAME(target) + 
        " and calls out a word of power, unleashing a sandstorm!\n";
    
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
    // DEBUG("Target: " +targets[0]->short()+ ", Resist: " +resist[0]+ ", Result: " +result);
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
    write("You need to have quaffed a suaco potion to cast scouring wind.\n");
}
