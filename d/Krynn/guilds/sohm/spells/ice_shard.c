/*
 * xarzith inloilfrey: Ice Shard - Arman 2020
 *
 * At will damage spell for the Students of High Magic. This is based
 * on the Genesis generic At-Will Harm spell (Petros 2009).
 */

#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "at_will_harm";

// Defines
#include "minor_at_will_check.h"

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
    set_spell_name("xarzithinloilfrey");
    set_spell_desc("Ice shard - a spray of sharp ice shards");
    set_spell_element(SS_ELEMENT_WATER, 30);
    set_spell_form(SS_FORM_CONJURATION, 30);

    set_spell_combat_aid(35.0);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_2);
    set_spell_task(TASK_ROUTINE); 

    set_spell_resist(&spell_resist_damage_type(MAGIC_I_RES_COLD));   
}


public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if(minor_at_will_rotation_check(caster) > 2)
    {
        caster->catch_tell("You are mentally unable to cast so many minor " +
           "offensive spells in quick succession!\n");
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
    
    setuid();
    seteuid(getuid());
    return SOHM_MANAGER->query_memorised_spell(player,"xarzithinloilfrey_memorised");
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

        caster_message = "You close your eyes and begin reciting from "
            + "memory powerful words of magic, 'Xarzith Inloilfrey!'\n";
        watcher_message = QCTNAME(caster) + " closes "
            + caster->query_possessive() + " eyes and begins reciting " +
              "mystical words of magic.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
}

public void
minor_spell_desc_cast(object caster, object target)
{
    string caster_message, target_message, watcher_message;
    
        caster_message = "You hurl your open hands towards "+ QTNAME(target) + 
            ".\n";
        target_message = QCTNAME(caster) + " hurls " + caster->query_possessive()
            + " open hands towards you.\n";
        watcher_message = QCTNAME(caster) + " hurls " + caster->query_possessive()
            + " open hands towards " + QTNAME(target) + ".\n";
    
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    caster->tell_watcher(watcher_message, target, ({ caster, target }));    
}

public void
minor_desc_damage(object caster, object target, int phurt, string hitloc_desc)
{
    string target_message, watcher_message;
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "Shards of sharp ice scatter past you, "
            + "melting harmlessly.\n";
        watcher_message = "Shards of sharp ice scatter past " + 
            QTNAME(target) + " and melting harmlessly.\n";
    }
    else
    {   
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "Shards of ice shower your " + hitloc_desc 
                + " ineffectually.\n";
            watcher_message = "Shards of ice shower " + QTNAME(target) +
                " in the " + hitloc_desc +  " ineffectually.\n";
            break;
            
        case 1..10:
            target_message = "Shards of ice shower your " + hitloc_desc 
                + ", mildly stinging it.\n";
            watcher_message = "Shards of ice shower " + QTNAME(target) +
                " on the " + hitloc_desc +  ", mildly stinging it.\n";
            break;
            
        case 11..30:
            target_message = "Shards of sharp ice slice in to you, "
                + "wounding your " + hitloc_desc + " painfully.\n";
            watcher_message = "Shards of sharp ice slice in to " + 
                QTNAME(target) + ", wounding " +target->query_possessive()+
                " " + hitloc_desc + " painfully.\n";

            break;
            
        case 31..60:
            target_message = "Daggers of sharp ice lance through your " +
                hitloc_desc+ " causing serious wounds.\n";
            watcher_message = "Daggers of sharp ice lance through " + 
                QTPNAME(target)+ " " +hitloc_desc+ " causing serious wounds.\n";
            break;
            
        default:
            target_message = "Deadly spears of ice impale you, " +
               "causing grievous injuries to your " +hitloc_desc+ "!\n";

            watcher_message = "Deadly spears of ice impale "+ QTNAME(target) + 
                ", causing grievous injuries to " +target->query_possessive()+
                " " +hitloc_desc+ "!\n"; 
            break;            
        }
    }
        
    caster->catch_msg(watcher_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
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
    write("You feel ready to conjure ice shards again.\n");
}

/*
 * Function:    hook_special_in_cooldown
 * Description: Override this to print out the message players will see
 *              when they cannot yet use their at will spell.
 */
public void
hook_special_in_cooldown()
{
    write("You do not feel ready to conjure ice shards again.\n");
}

public void
hook_already_active(object ability)
{
    write("You are currently conjuring ice shards!\n");
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
    int * check_skills = ({ SS_ELEMENT_WATER, SS_FORM_CONJURATION });
    
    foreach (int snum : check_skills)
    {
        // minimum of superior student
        if (caster->query_skill(snum) < 10)
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
