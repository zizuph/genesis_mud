
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>

public void
hook_combat_fail(object *combatants,object ability)
{
    write("You cannot "+ability->short()+" while in combat with " + 
        FO_COMPOSITE_ALL_LIVE(combatants, this_player()) + ".\n");
}

public void
hook_cannot_speak_fail(mixed why)
{
    if (stringp(why))
    {
        write(why);
    }
    else
    {
        write("You can't seem to speak the words.\n");
    }
}

public void
hook_attack_object(object ob)
{
    this_player()->catch_msg("You attack "+QTNAME(ob)+".\n");
    ob->catch_msg(QCTNAME(this_player())+" attacks you!\n");
    tell_room(environment(ob),QCTNAME(this_player())+" attacks "+
        QTNAME(ob)+".\n",({ ob, this_player() }));
}

/*
 * Function name: hook_no_magic_attack_fail
 * Description:   Return the message that should be printed when noone
 *                is supplied with ROOM_M_NO_MAGIC_ATTACK.
 * Arguments:     obj - The room object.
 * Returns:       The message to print.
 */
public void
hook_room_no_attack_fail(mixed reason, object room)
{
    if (stringp(reason))
    {
        write(reason);
    }
    else
    {
        write("You sense a divine force preventing your attack.\n");
    }
}

/*
 * Function name: hook_autochanged_target
 * Description:   Writes the message when a special's target is changed
 *                due to the original target being dead or attack-immune
 *                is supplied with ROOM_M_NO_MAGIC_ATTACK.
 * Arguments:     target - the new target
 */
public void hook_autochanged_target(mixed target)
{
}

/*
 * Function name: hook_no_magic_attack_fail
 * Description:   Return the message that should be printed when noone
 *                is supplied with ROOM_M_NO_MAGIC_ATTACK.
 * Arguments:     obj - The room object.
 * Returns:       The message to print.
 */
public void
hook_no_attack_fail(mixed reason)
{
    if (stringp(reason))
    {
        write(reason);
    }
    else
    {
        write("You feel a divine force protecting this being, your " +
               "attack fails.\n");
    }
}

public void
hook_already_active(object ability)
{
    write("You are already preparing to "+ability->short()+".\n");
}


/*
 * Function name: hook_no_mana_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have enough mana.
 * Returns:       The message to print.
 */
public void
hook_no_mana_fail()
{
    write("You don't have enough mana.\n");
}

/*
 * Function name: hook_dont_dare_attack_fail
 * Description:   Return the messages that should be printed to the caster
 *                when he/she don't dare to cast the spell.
 * Arguments:     target - The victim that is too strong.
 * Returns:       The message to print.
 */
public void
hook_dont_dare_attack_fail(object target)
{
    
    write("You don't dare to attack the " +
        target->query_the_name(this_player()) + ".\n");
}

/*
 * Function name: hook_targets_gone
 * Description:   Return the string that will be printed to the actor when
 *                the targets has disappeared during the prepartion of the
 *                ability.
 * Returns:       The message to print
 */
public void
hook_targets_gone(object * targets)
{
    object* remaining = targets - ({ 0 });
    if (sizeof(remaining))
    {
      write("The main "+
      (sizeof(remaining)> 1 ? "targets" : "target")+ " of " +
      COMPOSITE_LIVE(remaining) + " " +
      (sizeof(remaining)> 1 ? "are" : "is") + " not in this room.\n");
    }
    else
    {
      write("You have no more targets in this room.\n");
    }
}

/*
 * Function name: hook_changed_env
 * Description:   Return the string that will be printed to the player when
 *                he or she has moved rooms while preparing the ability.
 * Returns:       The message to print.
 */
public void
hook_changed_env()
{
    write("You have lost concentration while moving!\n");
}

/*
 * Function name: hook_stun_fail
 * Description:   Return the string that will be printed to the player when
 *                he or she is stunned
 * Returns:       The message to print.
 */
public void
hook_stun_fail(object ability)
{
    write("You are too stunned to "+ability->short()+"!\n");
}

/*
 * Function name: hook_stun_fail
 * Description:   Return the string that will be printed to the player when
 *                he or she is stunned
 * Returns:       The message to print.
 */
public void
hook_search_fail(object ability)
{
    write("You are too busy doing something else to " + ability->short() 
        + "!\n");
}

/*
 * Function name: hook_stopped_ability
 * Description:   Return the string that will be printed to the player when
 *                he or she is stunned
 * Returns:       The message to print.
 */
public void
hook_stopped_ability(object ability,object player)
{
    player->catch_msg("You stop preparing your "+ability->short()+".\n");
}


/*
 * Function name: hook_cannot_see_fail
 * Description:   Return the string that will be printed to the player when
 *                he needs to see to use the ability
 * Returns:       The message to print.
 */
public void
hook_cannot_see_fail()
{
    write("You cannot see!\n");
}

public void
hook_confirm_attack(object target,object ability)
{
    this_player()->catch_msg(capitalize(ability->short())+
        " "+QTNAME(target)+ "?!? Please confirm by trying again.\n");
}

public void
hook_no_attack_teammate(object target)
{
    this_player()->catch_msg(capitalize(QTNAME(target))+ " is on your team.\n");
}

