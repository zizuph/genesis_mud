/*
 * tonashingis: Ballistic spray - Arman 2016
 *
 * At will damage spell for the Students of High Magic. This is based
 * on the Genesis generic At-Will Harm spell (Petros 2009).
 */

#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"

inherit "/d/Genesis/specials/std/spells/at_will_harm";

// Defines

#include "/d/Krynn/guilds/sohm/spells/ballistic_spray_desc.h"
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
    set_ability_group(GUILD_NAME);
    set_spell_name("tonashingis");
    set_spell_desc("Ballistic spray - a conjured spray of solid " +
        "projectiles");
    set_spell_element(SS_ELEMENT_EARTH, 30);
    set_spell_form(SS_FORM_CONJURATION, 30);
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(36.0);
    set_spell_task(TASK_HARD);    
}

/*
 * Function:    query_spell_element_skill
 * Description: Returns the actual element skill number that is required
 *              for the spell.
 */
/*
public int
query_spell_element_skill()
{
    // This should end up returning whatever specialization the player
    // has for the skill.
    object player = this_player();

    // Spell's element is determined during concentrate_msg and stored.
    int element_skill = player->query_prop(SS_ELEMENT_AIR);
      
    return element_skill;
}
*/

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
    return SOHM_MANAGER->query_memorised_spell(player,"tonashingis_memorised");
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
            + "memory powerful words of magic, 'Tonash ingis!'\n";
        watcher_message = QCTNAME(caster) + " closes "
            + caster->query_possessive() + " eyes and begins reciting " +
              "mystical words of magic.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
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
    write("You feel ready to conjure a spray of ballistics again.\n");
}

/*
 * Function:    hook_special_in_cooldown
 * Description: Override this to print out the message players will see
 *              when they cannot yet use their at will spell.
 */
public void
hook_special_in_cooldown()
{
    write("You do not feel ready to conjure a spray of ballistics again.\n");
}

public void
hook_already_active(object ability)
{
    write("You are currently conjuring a ballistic spray!\n");
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
    ballistic_spray_desc_cast(caster, target);

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
        ballistic_spray_desc_damage(caster, target, result);
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
    int * check_skills = ({ SS_ELEMENT_EARTH, SS_FORM_CONJURATION });
    
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
