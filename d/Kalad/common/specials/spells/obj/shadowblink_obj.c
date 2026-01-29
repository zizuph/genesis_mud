/* 
 * Shadowblink blink spell used in Kalad
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <tasks.h>
#include <composite.h>

inherit "/d/Genesis/specials/std/spells/obj/blink_obj";

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_kalad_shadowblink_object_");
    set_short("shadowblink spell object");    
    set_long("This is the standard shadowblink spell's object. It provides " +
         "an aura of dark shadows that lets you slip away from harm.\n");
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the shadowblink spell.\n");
    set_spell_effect_desc("dark shadows");
    
    set_dispel_time(1800);   
}

/* 
 * Function:     is_valid_blink_target
 * Description:  Should return whether the person is a teammate and
 *               they're currently present and available to be blinked
 *               behind.
 * Arguments:    object teammate    -  the teammate to blink behind
 *               object player      -  the person blinking
 * Returns:      1 if player can blink behind teammate, 0 otherwise
 */ 
public int
is_valid_blink_target(object teammate, object player)
{
    if (!objectp(player) || !objectp(teammate))
    {
        return 0;
    }
    // Condition: Check that the teammate is in player's team.
    object * teammates = player->query_team_others();
    if (!pointerp(teammates)
        || sizeof(teammates) == 0
        || !IN_ARRAY(teammate, teammates))
    {
        return 0;
    }
    // Condition: Check that the teammate is actually in the same
    //            room.
    if (environment(teammate) != environment(player))
    {
        return 0;
    }
   
    return 1;
}    

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to the target.
 */
public void
hook_spell_effect_started()
{
    object target = query_effect_target();
    if (objectp(target))
    {
        target->catch_tell("Dark shadows emerge and shrouds you in " +
            "darkness.\n");
        tell_room(environment(target), QCTNAME(target) + " is shrouded by" +
            " dark shadows.\n", ({ target }));
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

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        target->catch_tell(" The shadows surrounding you disappear.\n");
        tell_room(environment(target), QCTNAME(target) + " is no"
            + " longer surrounded by dark shadows.\n", ({ target }));
    }
}

/*
 * Function   : query_blink_subloc_description
 * Description: When someone examines a person with this spell effect,
 *              they will see whatever is returned by this function.
 * Arguments  : object on, object for_obj
 * Returns    : A string with the message
 */
public string
query_blink_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
        return  "You are surrounded by dark swirling shadows.\n";
    else
        return capitalize(on->query_pronoun()) + " is surrounded by dark " +
            "swirling shadows.\n";
}

/*
 * Function:    hook_describe_blink_action
 * Description: When someone successfully blinks behind someone else,
 *              they will see the messages described in this function.
 * Arguments:   object player    - the person who is blinking
 *              object friend    - the person who is going to be tanking
 *              object * enemies - the list of enemies that will attack the
 *                                 friend instead.
 */
public void
hook_describe_blink_action(object player, object friend, object * enemies)
{
    player->catch_msg("Dark swirling shadows distract your enemies" +
                      " momentarily, allowing you to step behind " +
                      QTNAME(friend) + ". Your enemies are forced "
                      + "to engage " + friend->query_objective()+ "!\n");
    enemies->catch_msg("You are distracted by dark swiling shadows, " +
                      QTNAME(player) + " takes advantage of the situation" +
                      " and manages to blink behind " +QTNAME(friend)+ ".\n");
    friend->catch_msg("Dark swirling shadows distract " +
                     COMPOSITE_LIVE(enemies)+ ", allowing " +QTNAME(player)+
                     " to blink out of harms way behind you!\n");                 
}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading()
{
    object target = query_effect_target();
    
    if (objectp(target))
    {
        target->catch_tell("You sense that the dark shadows surrounding you" +
        " is about to vanish.\n");
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
            + "the dark shadows surrounding you.\n");
    }    
}