/*
 * Slow Object - based on the Standard Slow Object
 *
 * It tracks that a target has been slowed for a
 * limited duration.
 *
 * Specific guild implementations can inherit this object and set it
 * it up to match their specific needs.
 *
 * Created by Jaacar, February 2017.
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>

inherit "/d/Genesis/specials/std/spells/obj/slow_obj";

#define SLOW_SUBLOC "EC_slow_subloc"

int changeAmount;
int alarm;

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

    add_prop(OBJ_M_NO_DROP, 1);
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
    
    return result;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    int result = ::dispel_spell_effect(dispeller);
    if (!result)
    {
        return result;
    }
    
    object target = query_effect_target();
    target->remove_subloc(SLOW_SUBLOC);
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
        target->catch_tell("A slight fog surrounds you and you feel your "+
            "movements slow down.\n");
        tell_room(environment(target), QCTNAME(target) + " is surrounded by "+
            "a slight fog that seems to slow " + target->query_objective()+
            " down.\n", ({ target }));
    } 

    target->add_subloc(SLOW_SUBLOC, this_object());
   
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
        target->catch_tell("The slight fog dissipates and your movement speed "+
            "returns to normal.\n");
        tell_room(environment(target), QCTPNAME(target) + " movement "
            + "returns back to normal as the slight fog surrounding "+
            target->query_objective()+" dissipates.\n", ({ target }));
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
            + "fragmos prayer on " + QTNAME(target) + " begin to waver.\n");
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
            + "fragmos.\n");
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
        + " exit, but are slowed by the slight fog.\n");
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
        + direction + " exit, but are still slowed by the slight fog.\n");
    tell_room(environment(player), QCTNAME(player) + " changes direction "
        + "and begins to move towards the " + direction + " exit, but "
        + "continues to be slowed by "
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
        + " exit, but are still slowed by the slight fog.\n");
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

public string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == me)
        return "You are surrounded by a fog that hampers your " +
        "ability to move.\n";

    return "A fog surrounds " +me->query_objective()+ ", hampering " +
        me->query_possessive()+ " ability to move.\n";
}
