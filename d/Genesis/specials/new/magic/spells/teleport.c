/*
 * General Teleport Spell
 * 
 * This is a generic teleport spell that should be used as the basis for all
 * teleport spells under the Genesis Magic system created in 2009.
 *
 * Created by Petros, December 2010
 */

#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include "defs.h"

inherit SPELL_DIR + "centralized_spell";
inherit "/d/Sparkle/area/city/lib/utility_functions";
#include "centralized_spell_restrictions.h"


// Delay when a player is choosing a specific destination - 2 hours.
static nomask int DEFAULT_TELEPORT_TO_DESTINATION_DELAY = 3600 * 2;

// Delay when a player is just teleporting home - 1 hour.
static nomask int DEFAULT_TELEPORT_TO_HOME_DELAY = 3600;

// Prototypes
public int              check_valid_action(object caster, mixed * targets, string arg, int execute);
private nomask void     config_required_parameters();
public string *         query_teleport_ingredients(object caster);
public void             resolve_teleport_spell(object caster, mixed * targets, int * resist, int result);
public object *         spell_target_teleport(object actor, string str);
// Hook Prototypes
public void             hook_cannot_teleport_caster_in_combat(object caster, mixed * targets, string arg, int execute);
public void             hook_cannot_teleport_target_not_relaxed(object caster, object target, string arg, int execute);
public void             hook_cannot_teleport_target_too_soon(object caster, object target, string arg, int execute);
public void             hook_cannot_teleport_caster_room_not_valid(object caster, mixed * targets, string arg, int execute, object caster_room);
public void             hook_cannot_teleport_target_room_not_valid(object caster, mixed * targets, string arg, int execute, object target_room);
public void             hook_cannot_teleport_same_room(object caster, mixed * targets, string arg, int execute);
public void             hook_describe_teleport_origin_room(object caster, mixed* targets, object origin_room);
public void             hook_describe_teleport_target_room(object caster, mixed* targets, object target_room);

// How long after a teleport in seconds until a player can be teleported again.
int next_teleport_delay;

void set_next_teleport_delay(int delay)
{
    next_teleport_delay = delay;
}

int get_next_teleport_delay(object caster, object destination)
{
    return next_teleport_delay;
}

/*
 * Function:    config_teleport_spell
 * Description: Config function for teleport spells. Redefine this in your
 *              own teleport spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_teleport_spell()
{
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("teleport");
    set_spell_desc("Magically transport to another location");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);
    
    // Two hour delays between teleports.
    set_next_teleport_delay(DEFAULT_TELEPORT_TO_DESTINATION_DELAY);
    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(30);
    set_spell_target(spell_target_teleport);
    set_ability_target_verify(0);
    set_spell_ingredients(query_teleport_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_EARTH, 25);
    set_spell_form(SS_FORM_CONJURATION, 25);
        
    // Call the specific configuration that is to be masked.
    config_teleport_spell();
    
    // Call this after the config_teleport_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
}

/*
 * Function name: spell_target_teleport
 * Description:   This is the default targetting functions for the teleport
 *                spell. The spell should return list with a single object.
 *                The object should be the target room, followed by the 
 *                targets to move.
 */
public object *
spell_target_teleport(object actor, string str)
{
    // Safely load the default start location. 
    // See /d/Sparkle/area/city/lib/utility_functions for implementation.
    string target_room_file = actor->query_default_start_location();
    setuid();
    seteuid(getuid());
    object target_room = safely_load_master_file(target_room_file);
    return ({ target_room, actor });
}

/*
 * Function:    query_teleport_ingredients
 * Description: This function defines what components are required for
 *              this teleport spell.
 */
public string *
query_teleport_ingredients(object caster)
{
    return ({ "breadroot", "_leftover_heart" });
}

private nomask void
config_required_parameters()
{
    // Place required parameters here.
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);
}

/*
 * Function:    check_valid_action
 * Description: Checks conditions to see whether this spell can be cast.
 */
public int 
check_valid_action(object caster, mixed * targets, string arg, int execute)
{
    int result = ::check_valid_action(caster, targets, arg, execute);
    if (!result)
    {
        return result;
    }
    
    // Players cannot teleport if any of the following conditions are true
    // 1. Player is currently in combat (query_attack)
    // 2. Any target was recently in combat (query_relaxed_from_combat)
    // 3. The target room is invalid
    // 4. Caster or target room is not a teleport room (ROOM_M_NO_TELEPORT)
    // 5. Caster room is not a teleport from room (ROOM_M_NO_TELEPORT_FROM)
    // 6. Target room is not a teleport to room (ROOM_M_NO_TELEPORT_TO)
    // 7. Caster or target room has a no-magic prop set (OBJ_I_NO_MAGIC)
    // 8. Caster or Target has too recently teleported.
    if (objectp(caster->query_attack()))
    {
        hook_cannot_teleport_caster_in_combat(caster, targets, arg, execute);
        return 0;
    }
    if(!caster->query_relaxed_from_combat())
    {
        hook_cannot_teleport_target_not_relaxed(caster, caster, arg, execute);
        return 0;   
    }
    
    object target_room;   
    if (!sizeof(targets) 
        || !objectp(target_room = targets[0])
        || target_room->query_prop(ROOM_M_NO_TELEPORT)
        || target_room->query_prop(ROOM_M_NO_TELEPORT_TO)
        || target_room->query_prop(OBJ_I_NO_MAGIC))
    {
        hook_cannot_teleport_target_room_not_valid(caster, targets, arg, execute, target_room);
        return 0;
    }

    object caster_room = environment(caster);
    if (objectp(caster_room)
        && (caster_room->query_prop(ROOM_M_NO_TELEPORT)
           || caster_room->query_prop(ROOM_M_NO_TELEPORT_FROM)
           || caster_room->query_prop(OBJ_I_NO_MAGIC)))
    {
        hook_cannot_teleport_caster_room_not_valid(caster, targets, arg, execute, caster_room);
        return 0;
    }

    for (int i = 1; i < sizeof(targets); i++)
    {
        object target = targets[i];
        if (!target->query_relaxed_from_combat())
        {
            hook_cannot_teleport_target_not_relaxed(caster, target, arg, execute);
            return 0;
        }
        object timer = present("_teleport_timer_obj", target);
        if (timer && timer->is_teleport_blocked())
        {
            hook_cannot_teleport_target_too_soon(caster, target, arg, execute);
            return 0;
        }
    }

    if (target_room == caster_room)
    {
        hook_cannot_teleport_same_room(caster, targets, arg, execute);
        return 0;
    }
    
    return result;    
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                mixed *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public nomask void
resolve_spell(object caster, mixed * targets, int * resist, int result)
{
    resolve_teleport_spell(caster, targets, resist, result);
    
    // Move the caster to the target room.
    object target_room = targets[0];
    object origin_room = environment(caster);
    hook_describe_teleport_origin_room(caster, targets[1..], origin_room);
    for (int i = 1; i < sizeof(targets); i++)
    {
        object target = targets[i];
        if (environment(target) == origin_room)
        {
            int delay = get_next_teleport_delay(caster, target_room);
            setuid();
            seteuid(getuid());
            target->move_living("M", MASTER_OB(target_room), 1, 0);
            object timer = present("_teleport_timer_obj", target);
            if (!timer)
            {
                timer = 
                    clone_object(SPELL_OBJ_DIR + "teleport_timer_obj");
                timer->move(target, 1);
            }
            timer->add_teleport_delay(delay);
        }
    }
    hook_describe_teleport_target_room(caster, targets[1..], target_room);
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_teleport_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_teleport_spell(object caster, mixed * targets, int * resist, int result)
{
}

/*
 * Function:    hook_cannot_teleport_caster_in_combat
 * Description: Hook that gets called when trying to teleport while in combat.
 *              This can get called both at the beginning and at the end of
 *              the spell casting. The "execute" variable determines whether
 *              it's all the beginning or the end.
 */
public void
hook_cannot_teleport_caster_in_combat(object caster, mixed * targets, string arg, int execute)
{
    if (!execute)
    {
        caster->catch_tell("You cannot teleport while you are in combat.\n");
    }
    else
    {
        caster->catch_tell("You lose your concentration of your spell as you are "
            + "distracted by combat.\n");
    }
}

/*
 * Function:    hook_cannot_teleport_target_not_relaxed
 * Description: Hook that gets called when trying to teleport while having
 *              recently been in combat.
 *              This can get called both at the beginning and at the end of
 *              the spell casting. The "execute" variable determines whether
 *              it's all the beginning or the end.
 */
public void
hook_cannot_teleport_target_not_relaxed(object caster, object target, string arg, int execute)
{
    if (caster == target)
    {
        caster->catch_tell("You have too recently been in combat. You have to "
            + "relax first before you can teleport.\n");
    }
    else 
    {
        caster->catch_tell(QCTNAME(target) + " has too recently been in combat. They have to "
            + "relax first before they can be teleported.\n");
    }
}

/*
 * Function:    hook_cannot_teleport_target_too_soon
 * Description: Hook that gets called when trying to teleport while having
 *              recently teleported.
 *              This can get called both at the beginning and at the end of
 *              the spell casting. The "execute" variable determines whether
 *              it's all the beginning or the end.
 */
public void
hook_cannot_teleport_target_too_soon(object caster, object target, string arg, int execute)
{
    if (caster == target)
    {
        caster->catch_tell("You have teleported too recently. You have to "
            + "wait before you can teleport again.\n");
    }
    else 
    {
        caster->catch_tell(QCTNAME(target) + " has teleported too recently. They have to "
            + "wait before they can be teleported again.\n");
    }
}


/*
 * Function:    hook_cannot_teleport_caster_room_not_valid
 * Description: Hook that gets called when the caster's current room is not valid. It
 *              can be valid for a number of reasons. See check_valid_action for the
 *              conditions checked.
 */
public void
hook_cannot_teleport_caster_room_not_valid(object caster, mixed * targets, string arg, int execute, object caster_room)
{
    caster->catch_tell("The room you are in prevents you from teleporting.\n");
}

/*
 * Function:    hook_cannot_teleport_target_room_not_valid
 * Description: Hook that gets called when the spell's target room is not valid. It
 *              can be valid for a number of reasons. See check_valid_action for the
 *              conditions checked.
 */
public void
hook_cannot_teleport_target_room_not_valid(object caster, mixed * targets, string arg, int execute, object target_room)
{
    caster->catch_tell("The room you want to reach prevents you from teleporting there.\n");
}

/*
 * Function:    hook_cannot_teleport_same_room
 * Description: Hook that gets called when the user is trying to teleport to the same
 *              room that they are already in.
 */
public void             
hook_cannot_teleport_same_room(object caster, mixed * targets, string arg, int execute)
{
    caster->catch_tell("There's no need to teleport. You're already there!\n");
}


/*
 * Function:    hook_describe_teleport_origin_room
 * Description: This is the hook that describes the action of caster
 *              successfully teleporting out of the origin room.
 */
public void
hook_describe_teleport_origin_room(object caster, mixed* targets, object origin_room)
{
    foreach (object target : targets)
    {
        if (target == caster)
        {
            caster->catch_tell("You successfully complete the teleport spell and see "
                + "the world around you fade away.\n");
            tell_room(origin_room, QCTNAME(caster) + " closes "
                + caster->query_possessive() + " eyes, then shimmers "
                + "briefly and is gone.\n", ({ targets }) );
        }
        else
        {
            target->catch_tell("You feel teleported to another destination.\n");
            tell_room(origin_room, QCTNAME(target) + " shimmers "
                + "briefly and is gone.\n", ({ targets }) );
        }
    }
}

/*
 * Function:    hook_describe_teleport_target_room
 * Description: This is the hook that describes the action of caster
 *              successfully teleporting into the target room.
 */
public void
hook_describe_teleport_target_room(object caster, mixed* targets, object target_room)
{
    foreach (object target : targets)
    {
        if (target == caster)
        {
            tell_room(target_room, QCTNAME(caster) + " appears out of thin air, "
                + caster->query_possessive() + " eyes closed. "
                + capitalize(caster->query_pronoun()) + " opens them again, "
                + "glancing around.\n",  ({ targets }) );
        }
        else
        {
            tell_room(target_room, QCTNAME(target) + " appears out of thin air.\n",
                ({ targets }) );
        }
    }
}


