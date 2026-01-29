/*
 * Dazzle spell obj, based on standard slow spell obj
 */
#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>

#include "../defs.h"
#include "/d/Krynn/common/defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "slow_obj";

#define SLOW_SUBLOC "sohm_dazzle_subloc"

int changeAmount;
int alarm;


/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    add_name("sohm_dazzle_id");
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "SoHM magical object slowing the affected.\n");
    set_spell_effect_desc("dazzle");  
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
        target->catch_tell("Your stagger, your senses completely disoriented.\n");
        tell_room(environment(target), QCTNAME(target) + " staggers, " +HIS(target)+ 
          " senses completely disoriented.\n", 
        ({ target }));
    } 

    target->add_subloc(SLOW_SUBLOC, TO);
   
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

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        target->catch_tell("You feel yourself no longer disoriented.\n");
        tell_room(environment(target), QCTNAME(target)+" no longer looks " +
            "disoriented.\n", ({ target }));
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
            + "dazzle enchantment on " + QTNAME(target) + " begin to waver.\n");
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
            + "the dazzle enchantment.\n");
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
    player->catch_tell("You try and move towards the " + direction
        + ", but are dazed and disoriented.\n");
    tell_room(environment(player), QCTNAME(player) + " tries to move "
         + direction + ", but is clearly dazed and disoriented.\n", 
         ({ player }) );
}

/*
 * Function:    hook_slow_change_direction
 * Description: Hook that gets called when the person changes direction while
 *              already trying to move.
 */
public void
hook_slow_change_direction(object player, string direction)
{
    player->catch_tell("You stagger towards the " 
        + direction + ", but are still dazed and disoriented.\n");
    tell_room(environment(player), QCTNAME(player) + " staggers "
        + "towards the " + direction + ", but "
        + "is clearly dazed and disoriented.\n", ({ player }) );
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
        + " exit, but are still dazed and disoriented.\n");
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
    player->catch_tell("You manage to force your way " + direction
        + " through the red haze surrounding you.\n");
    tell_room(environment(player), QCTNAME(player) + " forces "
        + player->query_possessive() + " way to the " + direction
        + " through the red haze surrounding " +HIM(player)+ ".\n", ({ player }) );
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

public string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == me)
        return "You are dazzled and disoriented.\n";

    return "";
}
