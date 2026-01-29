/* 
 * pslow object - slow the target down
 */

#pragma strict_types
#pragma save_binary

#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>


#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "slow_obj";

#define SLOW_SUBLOC "pot_slow_subloc"


int changeAmount;
int alarm;

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    add_name("pot_slow_id");
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "PoT magical object slowing the affected.\n");
    set_spell_effect_desc("slow"); 
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
        target->catch_tell("Your feel hampered by a thick red haze that " +
            "surrounds you and slows your movements.\n");
        tell_room(environment(target), QCTNAME(target) + " is hampered by "
            + "a thick red haze that slows " +HIS(target)+ " movements.\n", 
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
        target->catch_tell("The air around you changes back to normal.\n");
        tell_room(environment(target), "The air around "+
        QTNAME(target)+" changes back to normal.\n", ({ target }));
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
            + "slowness prayer on " + QTNAME(target) + " begin to waver.\n");
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
            + "the slowness prayer.\n");
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
        + ", but are hampered by the red haze surrounding you.\n");
    tell_room(environment(player), QCTNAME(player) + " starts to move "
         + direction + ", but is hampered by " 
        + "the red haze surrounding " +HIM(player)+ ".\n", ({ player }) );
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
        + direction + ", but are still hampered by the red haze surrounding " +
        "you.\n");
    tell_room(environment(player), QCTNAME(player) + " changes direction "
        + "and begins to move towards the " + direction + ", but "
        + "is hampered by the red haze surrounding " +HIM(player)
        + ".\n", ({ player }) );
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
        + " exit, but are still hampered by the red haze surrounding you.\n");
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
        return "You are surrounded by a red haze that hampers your " +
        "ability to move.\n";

    return "A red haze surrounds " +HIM(me)+ ", hampering " +
        HIS(me)+ " ability to move.\n";
}
