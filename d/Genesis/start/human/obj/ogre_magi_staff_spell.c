/*
 * Medusa's gaze earth at-will harm spell for the 
 * ogre magi's staff.
 *
 * The death blow of this spell creates a unique corpse.
 *
 * Arman - January 2021
 */

#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <state_desc.h>

inherit "/d/Genesis/specials/std/spells/at_will_harm";

#define CORPSE_SHADOW   "/d/Genesis/start/human/obj/petrify_corpse_sh"

/*
 * Function:    config_at_will_spell
 * Description: Config function for at will damage spells. Redefine this in your
 *              own at will spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_at_will_spell()
{
    set_spell_name("petrify");
    set_spell_desc("Medusa's gaze - petrify your enemies");
    set_spell_element(SS_ELEMENT_EARTH, 20);
    set_spell_form(SS_SPELLCRAFT, 20);
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);

    set_spell_combat_aid(20.0);
    set_spell_task(TASK_ROUTINE);  

    set_spell_target(spell_target_one_present_enemy);
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    // Only newbies and immortals may wield this staff and use its spells.
    if(!SD_IS_NEWBIE(caster) && !caster->query_wiz_level())
    {
        caster->catch_tell("The staff writhes in your hands like a snake, " +
            "refusing to allow you to use its powers!\n");
        return 0;
    }
  
    return 1;
}

/*
 * Function:    query_spell_can_be_learned
 * Description: Place restrictions on whether this spell can be used
 *              by the guild member.
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

    caster_message = "As you activate your staff, the eyes of the " +
        "medusa head begin to glow a malevolent green.\n";
    watcher_message = "The eyes of the medusa head at the top of " + 
        QTPNAME(caster) + " staff begins to glow a malevolent green.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
}

public void
minor_spell_desc_cast(object caster, object target)
{
    string caster_message, target_message, watcher_message;
    
    caster_message = "You point the staff of the medusa towards "+ 
        QTNAME(target) + ".\n";
    target_message = QCTNAME(caster) + " points " + caster->query_possessive()
        + " staff of the medusa towards you.\n";
    watcher_message = QCTNAME(caster) + " points " + caster->query_possessive()
        + " staff of the medusa towards " + QTNAME(target) + ".\n";
    
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    caster->tell_watcher(watcher_message, target, ({ caster, target }));    
}

public void
minor_desc_damage(object caster, object target, int phurt, string hitloc_desc)
{
    string target_message, watcher_message;
    object corpse_sh;

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
        corpse_sh = clone_object(CORPSE_SHADOW);
        corpse_sh->shadow_me(target);
        target->do_die(caster); 
        corpse_sh->remove_shadow();
    }

}

public void
minor_spell_desc_damage(object caster, object target, mixed * result)
{
    string caster_message, target_message, watcher_message;
    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    int phurt = result[0];
    string hitloc_desc = result[1];

    minor_desc_damage(caster, target, phurt, hitloc_desc); 
}

// HOOKS TO BE DEFINED

/*
 * Function:    hook_special_complete
 * Description: Override this to print out the message players will see
 *              when they can use their at will spell again.
 */
public void 
hook_special_complete()
{
    write("You feel ready to use the staff of the medusa again.\n");
}

/*
 * Function:    hook_special_in_cooldown
 * Description: Override this to print out the message players will see
 *              when they cannot yet use their at will spell.
 */
public void
hook_special_in_cooldown()
{
    write("You do not feel ready to use the staff of the medusa again.\n");
}

public void
hook_already_active(object ability)
{
    write("You are currently in the process of activating the staff!\n");
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
 * Function name: desc_harm_cast
 * Description:   Describe casting of the spell, not including damage messages.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_harm_cast(object caster, object *targets)
{
    object target = targets[0];
    minor_spell_desc_cast(caster, target);
}

/*
 * Function name: desc_harm_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                mixed *result - return value from do_bolt_damage() call.
 */
public void
desc_harm_damage(object caster, object target, mixed *result)
{
    minor_spell_desc_damage(caster, target, result);
}

/*
 * Function:    query_insufficient_skills
 * Description: Returns the skills that are not high enough to cast this
 *              spell.
 */
public int *
query_insufficient_skills(object caster)
{
    int * needed_skills = ({ });
    int * check_skills = ({ SS_ELEMENT_EARTH, SS_SPELLCRAFT });
    
    foreach (int snum : check_skills)
    {
        // minimum of superior amateur
        if (caster->query_skill(snum) < 20)
        {
            needed_skills += ({ snum });
        }
    }

    return needed_skills;
}

/*
 * Function:    restart_npc_special
 * Description: At will harm spells are like fighter specials. When testing
 *              them, we want it to trigger as soon as it finishes.
 */
public void
restart_npc_special(object player, string arg)
{
    if (player->no_repeat_harm_spell())
        return;

    if (query_ability_time() > 0)
    {
        set_alarm(0.0, 0.0, &recast_spell(player, arg));
    }
}

public object *
spell_target_one_present_enemy(object actor, string str)
{
    object enemy = actor->query_attack();

    if (!enemy || !present(enemy, environment(actor)))
    {
        actor->catch_msg("You must first be in combat before you can activate " +
            "the petrification magic of the staff of the medusa!\n");

        return ({ });
    }

    return ({ enemy });
}
