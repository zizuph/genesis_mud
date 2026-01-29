/*
 * Standard Slow Object
 *
 * This is the spell object for the standard Genesis Magic System Slow
 * spell. When started, this spell object clones the slow shadow
 * to cause people to be able to move from rooms once per specified
 * interval (usually one second).
 *
 * Specific guild implementations must inherit from this one to get
 * the standard AoB approved effects.
 *
 * Created by Petros, March 2010
 *
 * Modified at 2021-06-01 by Carnak:
 *  - Lowered the base value by leaps and bounds.
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>

#include "defs.h"

inherit "/d/Genesis/specials/std/spells/obj/spell_obj_base";

// Defines
#define SLOW_SUBLOC        "_slow_subloc"

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_slow_object_");
    set_short("slow spell object");    
    set_long("This is the standard slow spell's object. It restricts "
        + "movement so speedwalking is not possible.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the slow spell.\n");
    set_spell_effect_desc("slow movement");    
}

/*
 * Function:    setup_spell_effect
 * Description: This is called to set up all the things for the
 *              spell. Must call the parent's setup_spell_effect
 *              in order to get the maintainence stuff.
 */
public int
setup_spell_effect()
{
    int result = ::setup_spell_effect();
    if (!result)
    {
        return result;
    }

    float interval = query_spell_effect_input();
    if (!interval)
    {
        interval = 1.0;
    }
    
    int power = query_spell_effect_power();
    // Power determines how long the spell lasts
    //int duration = power / 4; // F_PENMOD(60,100) = 396 / 4 = 99 seconds
    //duration = random(duration / 2) + random(duration / 2) + random(duration / 2);
    int duration = power / 40; // Changed to lower the effect of PvP abilities
    duration = ftoi(itof(duration) * log(itof(duration) / interval) + interval);
    duration = duration / 2 + random(duration / 2) + random(duration / 2);
    
    set_dispel_time(duration);
    
    object slow_shadow = clone_object("/d/Genesis/specials/std/slow_sh");
    slow_shadow->set_message_object(this_object());
    slow_shadow->set_slow_interval(interval);
    object target = query_effect_target();
    slow_shadow->shadow_me(target);
    
    return result;
}

public varargs int
dispel_spell_effect(object dispeller)
{
    int result = ::dispel_spell_effect(dispeller);
    if (!result)
    {
        return result;
    }
    
    object target = query_effect_target();
    target->remove_slow_shadow();
    
    return 1;
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started()
{
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("Your feel your movements slow down.\n");
        tell_room(environment(target), QCTNAME(target) + " seems to slow "
            + "down.\n", ({ target }));
    }    
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("Your movement speed returns to normal.\n");
        tell_room(environment(target), QCTPNAME(target) + " movement "
            + "returns back to normal.\n", ({ target }));
    }
}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading()
{    
    // Alert the caster that the effect is about to expire.
    object caster = query_effect_caster();
    object target = query_effect_target();
    
    if (objectp(caster) && objectp(target))
    {
        caster->catch_tell("You feel your ability to maintain the "
            + "slowness on " + QTNAME(target) + " begin to waver.\n");
    }
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained()
{
    object caster = query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
            + "the slowness effect.\n");
    }    
}

/*
 * Function:    hook_slow_start_moving
 * Description: Hook that gets called when the person starts to move with
 *              the slow effect.
 */
public void
hook_slow_start_moving(object player, string direction)
{
    player->catch_tell("You start to move towards the " + direction
        + " exit, but are slowed by something.\n");
    tell_room(environment(player), QCTNAME(player) + " starts to move "
        + "towards the " + direction + " exit, but is slowed by "
        + "something.\n", ({ player }) );
}

/*
 * Function:    hook_slow_change_direction
 * Description: Hook that gets called when the person changes direction while
 *              already trying to move.
 */
public void
hook_slow_change_direction(object player, string direction)
{
    player->catch_tell("You change your mind and start to move towards the " 
        + direction + " exit, but are still slowed by something.\n");
    tell_room(environment(player), QCTNAME(player) + " changes direction "
        + "and begins to move towards the " + direction + " exit, but "
        + "contisues to be slowed by "
        + "something.\n", ({ player }) );
}

/*
 * Function:    hook_slow_already_moving
 * Description: Hook that gets called when the person continues to try to break 
 *              free in the same direction that they already were trying.
 */
public void
hook_slow_already_moving(object player, string direction)
{
    player->catch_tell("You are already moving towards the " + direction
        + " exit, but are still slowed by something.\n");
}

/*
 * Function:    hook_slow_move_succeeded
 * Description: Hook that gets called when the person completes the move
 *              that they wanted to and are allowed to move to the next
 *              room.
 */
public void
hook_slow_move_succeeded(object player, string direction)
{
    player->catch_tell("You successfully make your way to the " + direction
        + " exit.\n");
    tell_room(environment(player), QCTNAME(player) + " successfully makes "
        + player->query_possessive() + " way to the " + direction
        + " exit.\n", ({ player }) );
}
