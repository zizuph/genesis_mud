/*
 * Amulet storm spell - Arman 2018
 */

#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <composite.h>
#include <files.h>
#include <wa_types.h>
#include "/d/Krynn/common/defs.h"

inherit "/d/Genesis/specials/std/spells/massharm";

/*
 * Function:    config_massharm_spell
 * Description: Config function for harm spells. Redefine this in your
 *              own harm spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_massharm_spell()
{
    set_spell_name("stormfury");
    set_spell_desc("Zeboim's fury - summon the fury of the Sea Queen.");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);

    // set_spell_combat_aid(113.0);

    set_spell_combat_aid(100);
    set_spell_task(TASK_ROUTINE);

    // Very expensive mana cost
    set_spell_mana_factor(10.0);

    // For testing checking the impact of a 3x time factor
    set_spell_time_factor(1.0); 

    /* Limit spell targets */
    set_spell_target_limit(3);
  
    set_spell_element(SS_ELEMENT_WATER, 0);
    set_spell_form(SS_FORM_CONJURATION, 0);
}

/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_massharm_ingredients(object caster)
{ 
    return ({ });
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
    
    return 1;
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    object env = environment(caster);

    if(env->query_prop(ROOM_I_INSIDE))
    {
        caster->catch_tell("You can only summon Zeboim's fury when " +
            "outside!\n");
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

    caster_message = "You grasp the dark amulet of the storms in your hands, " +
        "and suddenly call out: Zeboim! Goddess of the Sea! Come! Rain your fury " +
        "upon me!\nThe amulet pulses in your hands, and suddenly above you dark " +
        "storm clouds begin to form!\n";
    watcher_message = QCTNAME(caster) +" grasps "+ caster->query_objective()+
        " dark amulet around " +caster->query_objective()+ " neck, and suddenly " +
        "calls out: Zeboim! Goddess of the Sea! Come! Rain your fury upon me!\n" +
        "Suddenly, ominous storm clouds begin to form above you!\n";
   
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
        target_message = "A blast of cold air buffets you harmlessly.\n";
        watcher_message = "A blast of cold air buffets " +QTNAME(target) + 
            "harmlessly.\n";
    }
    else
    {        
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "Hailstones bounces off your "
                + hitloc_desc + ", doing no damage.\n";
            watcher_message = "Hailstones bounce off " + QTPNAME(target)
                + " " + hitloc_desc + ", doing no damage.\n"; 
            break;
            
        case 1..5:
            target_message = "Sharp icicles strike your " + hitloc_desc
                + " piercing you slightly.\n";
            watcher_message = "Sharp icicles strike " + QTPNAME(target)
                + " in the " + hitloc_desc + ", piercing " + target->query_objective()
                + " slightly.\n";
            break;
            
        case 6..10:
            target_message = "Sharp icicles strike your " + hitloc_desc + 
                " cutting you.\n";
            watcher_message = "Sharp icicles strike " +QTNAME(target) + 
                " in the " + hitloc_desc + ", cutting " +target->query_objective()+ ".\n";
            break;
            
        case 11..15:
            target_message = "A hail of jagged ice strikes your " + hitloc_desc + 
                " causing shallow wounds.\n";
            watcher_message = QCTNAME(target) + " is struck by a hail of jagged ice " +
                "on the " + hitloc_desc + ", causing shallow wounds.\n";
            break;
            
        case 16..25:
            target_message = "A hail of jagged ice slashes your " + hitloc_desc + 
                ", seriously hurting you.\n";
            watcher_message = QCTNAME(target) + " is seriously slashed on the " +
                hitloc_desc + " by a hail of jagged ice.\n";
            break;
            
        case 26..35:
            target_message = "Your " + hitloc_desc + " is slashed by a torrent of " +
                "jagged ice, wounding you painfully.\n";
            watcher_message = QCTNAME(target) + " is slashed by a torrent of jagged " +
                "ice, wounding " + target->query_possessive() + " " + hitloc_desc + 
                " painfully.\n";
            break;
            
        case 36..50:
            target_message = "Your " + hitloc_desc + " is shredded by an onslaught "
                + "of jagged ice, causing severe damage.\n";
            watcher_message = QCTNAME(target) + " is shredded by an onslaught " +
                "of jagged ice, causing severe damage to " + target->query_possessive() + 
                " " + hitloc_desc + ".\n";
            break;
                    
        case 51..70:
            target_message = "You are blasted with jagged shards of ice, ripping " +
                "apart your " + hitloc_desc + " and causing you grievous injuries.\n";
            watcher_message = QCTNAME(target) + " is blasted with jagged shards of ice"+
                ", ripping apart " + target->query_possessive() + " " + hitloc_desc + 
                " and causing " +target->query_objective()+ " grievous injuries.\n";
            break;
            
        default:
            target_message = "Lancing daggers of ice overwhelm you, ripping apart your " 
                 +hitloc_desc + " and causing multiple fatal injuries.\n";
            watcher_message = "Lancing daggers of ice overwhelm "
                + QTNAME(target) + ", ripping apart " +target->query_possessive()
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
    object env = environment(caster);

    string go_plural;

    if(sizeof(targets) > 1)
      go_plural = "them";
    else
      go_plural = HIM(targets[0]);


    caster_message = "You point your hand in the direction of " + 
        COMPOSITE_LIVE(targets) + ". The massing storm above you answers " +
        "your call, pounding "+go_plural+" with the fury of the elements!\n";
    target_message = QCTNAME(caster)+ " points " + caster->query_possessive() + " " +
        "hand in your direction. The massing storm above " +QTPNAME(caster)+ 
        " head answers " +HIS(caster)+ " call, pounding you with the " +
        "fury of the elements!\n";

    watcher_message = QCTNAME(caster)+ " points " + caster->query_possessive() + " " +
        "hand towards " + COMPOSITE_LIVE(targets) + ". The massing storm above " +
        QTPNAME(caster)+ " head answers " +HIS(caster)+ " call, pounding "+
        COMPOSITE_LIVE(targets)+" with the fury of the elements!\n";
    
    caster->catch_msg(caster_message);
    targets->catch_msg(target_message);
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

public void
hook_no_present_targets(object actor, string str)
{
    actor->catch_msg("You must first be in combat before you can call on "
    + "the fury of Zeboim!\n");   
}
