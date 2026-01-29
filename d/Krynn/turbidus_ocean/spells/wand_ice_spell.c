/*
 * Ice harm spell for ice wand.
 *
 * Arman - December 2020
 */

#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include "/d/Krynn/common/defs.h"

inherit "/d/Genesis/specials/std/spells/harm";

#define ICE_SPELL "/d/Krynn/turbidus_ocean/spells/wand_ice_spell"
#define DEBUG(x)	find_player("arman")->catch_tell(x);

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
    set_spell_name("iceblast");
    set_spell_desc("ice blast - shred your foes with ice shards");

    // Must set this so guild spells cannot be stacked with
    // the wand ability.
    set_ability_exclusive(1);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);

    // Default caid.
    // The caid of the spell is determined in check_valid_action 
    // and is based on the caster's SS_SPELLCRAFT and the
    // SS_ELEMENT_WATER spell skills, maximum of 75 for max skill
    // in both.
    set_spell_combat_aid(50.0);
    set_spell_task(TASK_ROUTINE);

    // 2.5x the standard cast time for a harm spell 
    set_spell_time_factor(2.5);     

    set_spell_element(SS_ELEMENT_WATER, 20);
    set_spell_form(SS_FORM_CONJURATION, 20);

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

    return 1;
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    mixed conc_prop;
    object conc_ob;

    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if(caster->query_prop(LIVE_I_CONCENTRATE) &&
       MASTER_OB(caster->query_prop(LIVE_I_CONCENTRATE)) != ICE_SPELL)
    {
        caster->catch_tell("You are currently concentrating on casting " +
            "another spell, and cannot activate the wand.\n");
        return 0;
    }

    // To avoid spell stacking, need to check whether a spell has been cast
    // after the wand has been activated. If so, no longer a valid action.

    object * spell_list;
    spell_list = caster->query_spellobjs();

    if (sizeof(spell_list))
    {
        foreach(object preparing_spell: spell_list)
        {
            if(preparing_spell->query_ability_preparing(caster))
            {
                DEBUG("Spell preparing: " +preparing_spell->query_spell_name()+ ".\n");
                caster->catch_tell("You are currently concentrating on casting " +
                    "another spell, " +preparing_spell->query_spell_name()+ 
                    ", disrupting your attempt to activate the wand.\n");
               tell_room(environment(caster), QCTPNAME(caster)+ " attempt to " +
                    "activate the magic of the wand fails.\n", 
                    ({ caster }), caster);
                return 0;
            }
        }
    }

    int spellcraft, water_element_skill;
    float caid;

    // The caid of the spell is determined by the caster's SS_SPELLCRAFT
    // and SS_ELEMENT_WATER spell skills, maximum of 75 for max skill
    // in both.

    spellcraft = caster->query_skill(SS_SPELLCRAFT);
    water_element_skill = caster->query_skill(SS_ELEMENT_WATER);

    caid = itof(((spellcraft + water_element_skill) * 3) / 8);

    set_spell_combat_aid(caid);

    // caster->catch_tell("Caid: " +ftoi(caid)+ ".\n");
    
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

    caster_message = "You raise your wand in preparation.\n";
    watcher_message = QCTNAME(caster) +" raises " +caster->query_possessive()+ 
        " wand in preparation.\n";
        
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
    object corpse_sh;

    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "A blast of cold air wails harmlessly past you.\n";
        watcher_message = "A blast of cold air wails harmlessly past " + 
            QTNAME(target) + ".\n";
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
            
        case 1..5:
            target_message = "A spray of sharp icicles strike your " + hitloc_desc
                + " piercing you slightly.\n";
            watcher_message = "A spray of sharp icicles strike " + QTPNAME(target)
                + " in the " + hitloc_desc + ", piercing " + target->query_objective()
                + " slightly.\n";
            break;
            
        case 6..10:
            target_message = "A spray of sharp icicles strike your " + hitloc_desc + 
                " cutting you.\n";
            watcher_message = "A spray of sharp icicles strike " +QTNAME(target) + 
                " in the " + hitloc_desc + ", cutting " +target->query_objective()+ ".\n";
            break;
            
        case 11..15:
            target_message = "Ice spikes strike your " + hitloc_desc + 
                ", wounding you.\n";
            watcher_message = "Ice spikes strike " +QTNAME(target) + 
                " in the " + hitloc_desc + ", wounding " +target->query_objective()+ ".\n";
            break;
            
        case 26..35:
            target_message = "Spear-like spikes of ice strike your " + hitloc_desc + 
                ", seriously piercing you.\n";
            watcher_message = "Spear-like spikes of ice strike " +QTNAME(target) + 
                " in the " + hitloc_desc + ", seriously piercing " +
                target->query_objective()+ ".\n";
            break;
            
        case 36..45:
            target_message = "Your " + hitloc_desc + " is pierced by a jagged spear of "
                + " ice, penetrating you viciously.\n";
            watcher_message = QCTNAME(target) + " is pierced by a jagged spear of ice, " +
                "penetrating " + target->query_possessive() + " " + hitloc_desc + 
                " viciously.\n";
            break;
            
        case 46..55:
            target_message = "Your " + hitloc_desc + " is shredded by savage " +
                "spikes of ice, causing severe damage.\n";
            watcher_message = QCTNAME(target) + " is shredded by savage spikes of ice, " +
                "causing severe damage to " + target->query_possessive() + " " + 
                hitloc_desc + ".\n";
            break;
                    
        case 56..99:
            target_message = "A mighty lance of ice impales you brutally, penetrating your " +
                hitloc_desc + " and causing you grievous injuries.\n";
            watcher_message = "A mighty lance of ice impales " + QTPNAME(target) + 
                " brutally, penetrating " + target->query_possessive() + " " + hitloc_desc + 
                " and causing " +target->query_objective()+ " grievous injuries.\n";
            break;
            
        default:
            target_message = "A mighty lance of ice skewers you with deadly " +
                "force, eviscerating your " + hitloc_desc + " and causing " +
                "multiple fatal injuries.\n";
            watcher_message = "A mighty lance of ice skewers " + QTNAME(target) + 
                " with deadly force, eviscerating " + target->query_possessive()+ 
                " " + hitloc_desc + " and cause multiple fatal injuries.\n";
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

    caster_message = "You point your wand towards " + QTNAME(target) + 
        " and draw upon the ice magic of the winternorns. ";
    target_message = QCTNAME(caster)+ " points " + caster->query_possessive() + " " +
        "wand at you. ";

    watcher_message = QCTNAME(caster)+ " points " + caster->query_possessive() + " " +
        "wand at " + QTNAME(target) + ". ";
    
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
