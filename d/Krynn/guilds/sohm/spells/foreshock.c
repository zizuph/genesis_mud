/*
 * Foreshock spell for WoHS - Arman 2021
 */

#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Genesis/specials/local.h"

inherit SPELL_DIR + "harm";

#define STATUE_OBJ   "/d/Krynn/throtyl/obj/petrify_corpse_sh"

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
    set_spell_name("edarjikmada");
    set_spell_desc("Foreshock - a damaging ray of earth energy");

    set_spell_combat_aid(100.0);

    set_spell_class(SPELL_CLASS_4);
    set_spell_task(TASK_DIFFICULT);

    set_ability_stats(STAT_WEIGHTING);

    // Low component requirement with gem shards
    set_spell_component_factor(COMPONENT_AID_LOW);

    // 2 times the standard cast time for a harm spell 
    set_spell_time_factor(2.0);     

    set_spell_element(SS_ELEMENT_EARTH, 50);
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
    // any gem shard.  
    return ({ "shard" });
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
    return SOHM_MANAGER->query_memorised_spell(player,"edarjikmada_memorised");
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

    if(SOHM_MANAGER->too_many_spells_memorised(caster))
    {
        caster->catch_tell("You have more spells memorised than you are capable of " +
            "mentally handling. You need to balance your memorised spell list before " +
            "you can cast spells again.\n");
        return 0;
    }

    if (caster->query_npc())
    {
        // npcs can cast the spell with defensive spells activated.
        return 1;
    }

    /*  Can only be cast with the stonneskin spell active  */

    if(!caster->query_prop("_sohm_stoneskin_effect"))
    {
        caster->catch_tell("You can only cast foreshock with the stoneskin spell " +
              "active!\n");
	return 0; 
    }

    /*  If in underwater or air terrain, cannot cast foreshock  */

    if(environment(caster)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
    {
        caster->catch_tell("You cannot form a good enough connection with the earth " +
            "while underwater to cast foreshock!\n");
	return 0; 
    }

    if(environment(caster)->query_prop(ROOM_I_TYPE) == ROOM_IN_AIR)
    {
        caster->catch_tell("You cannot form a good enough connection with the earth " +
            "while airborn to cast foreshock!\n");
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

    caster_message = "You raise your hand and begin chanting powerful " +
        "words of conjuration, drawing a connection between yourself " +
        "and the earth.\n";
    watcher_message = QCTNAME(caster) +" raises " +caster->query_possessive() +
        " hand and begins chanting powerful words of magic.\n";
        
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
        target_message = "A ray of earthly power misses you.\n";
        watcher_message = "A ray of earthly power misses " + 
            QTNAME(target) + ".\n";
    }
    else 
    {        
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "A ray of earthly power ineffectively strikes your " +
                hitloc_desc+ ", doing no damage.\n";
            watcher_message = "A ray of earthly power ineffectively strikes " + 
                QTNAME(target) + " on the " + hitloc_desc + ", doing no damage.\n"; 
            break;
            
        case 1..5:
            target_message = "A ray of earthly power strikes your " + hitloc_desc
                + ", stinging you slightly.\n";
            watcher_message = "A ray of earthly power strikes " + QTNAME(target)
                + " in the " + hitloc_desc + ", stinging " + target->query_objective()
                + " slightly.\n";
            break;
            
        case 6..10:
            target_message = "A ray of earthly power strikes your " + hitloc_desc + 
                ", causing it to harden slightly.\n";
            watcher_message = "A ray of earthly power strikes " +QTNAME(target) + 
                " in the " + hitloc_desc + ", causing it to harden slightly.\n";
            break;
            
        case 11..15:
            target_message = "A harsh tellurian ray strikes your " + 
                hitloc_desc + " abrading you harshly.\n";
            watcher_message = "A harsh tellurian ray strikes " +
                QTNAME(target) + " in the " + hitloc_desc + ", abrading " +
                target->query_objective()+ " harshly.\n";
            break;
            
        case 26..35:
            target_message = "A harsh tellurian ray blasts " +
                "your " + hitloc_desc + ", scouring you painfully.\n";
            watcher_message = "A harsh tellurian ray blasts into " +
                QTPNAME(target) + " " + hitloc_desc + ", scouring " +
                target->query_objective()+ " painfully.\n";
            break;
            
        case 36..45:
            target_message = "An intense tellurian ray blasts into " +
                "your " + hitloc_desc + ", eroding it horribly.\n";                
            watcher_message = "An intense tellurian ray blasts into " +
                QTPNAME(target) + " " + hitloc_desc + ", eroding it horribly.\n";
            break;
            
        case 46..55:
            target_message = "Your " + hitloc_desc + " is engulfed by a corroding "
                + "tellurian ray, causing severe damage.\n";
            watcher_message = QCTNAME(target) + " is engulfed by a corroding " +
                "tellurian ray, causing severe damage to " + 
                target->query_possessive() + " " +hitloc_desc+ ".\n";
            break;
                    
        case 56..99:
            target_message = "A mighty tellurian ray engulfs you, consuming your " +
                hitloc_desc+ " and causing you grievous injuries.\n";
            watcher_message = "A mighty tellurian ray engulfs " +QTNAME(target) + 
                ", consuming " + target->query_possessive() + " " + hitloc_desc + 
                " and causing " +target->query_objective()+ " grievous injuries.\n";
            break;
            
        default:
            target_message = "A deadly tellurian ray engulfs you, petrifying your " +
                hitloc_desc+ " and causing you fatal injuries!\n";
            watcher_message = "A deadly tellurian ray engulfs " + QTPNAME(target) + 
                " " +hitloc_desc+ " causing fatal injuries!\n";
            break;
        }
    }
        
    caster->catch_msg(watcher_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));

    if (objectp( target ) && (target->query_hp() <= 0) && 
        !target->query_prop(LIVE_I_NO_CORPSE))
    {
        corpse_sh = clone_object(STATUE_OBJ);
        corpse_sh->shadow_me(target);
        target->do_die(caster); 
        corpse_sh->remove_shadow();
    }
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

    caster_message = "You draw upon the latent energy of the earth and " +
        "direct it towards " + QTNAME(target) + ". ";
    target_message = QCTNAME(caster)+ " draws upon the latent energy " +
        "of the earth and directs it towards you. ";
    watcher_message = QCTNAME(caster)+ " draws upon the latent energy of the " +
        "earth and directs it at " + QTNAME(target) + ". ";
    
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
    write("You need a gem shard to be able to cast foreshock.\n");
}
