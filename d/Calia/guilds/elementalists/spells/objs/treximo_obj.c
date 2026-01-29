/*
 * Blink Object for the Elementalists of Calia
 *
 * This is the spell object based on the standand blink spell object
 * maintained in the Genesis Magic System.
 *
 * Created by Petros, August 2011
 */
 
#pragma strict_types
#pragma save_binary

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "blink_obj";

#include "defs.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>


/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_blink_object_");
    set_short("blink spell object");    
    set_long("This is the standard blink spell's object. It causes "
        + "one to blink behind someone.\n");
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the blink spell.\n");
    set_spell_effect_desc("blink out of combat");

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
        target->catch_tell("You will now phase in and out of the material "+
            "plane.\n");
        tell_room(environment(target), QCTNAME(target) + " begins to phase "
            + "in and out of the material plane.\n", ({ target }));
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
        target->catch_tell("You stop phasing in and out of the material "+
            "plane.\n");
        tell_room(environment(target), QCTNAME(target) + " seems to solidify "
            + "in view.\n", ({ target }));
    }
}

/*
 * Function:    query_blink_subloc_description
 * Description: When someone examines a person with this spell effect,
 *              they will see whatever is returned by this function.
 */
public string
query_blink_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
        return  "You feel your body is phasing in and out of the material "+
            "realm.\n";
    else
        return capitalize(on->query_pronoun()) + " seems to flicker out of "+
            "existance periodically.\n";
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
    player->catch_msg("You blink out of the material realm, reappearing "+
        "behind " + QTNAME(friend) + ". Your enemies move " +
        "to attack " + friend->query_objective() + "!\n");
    friend->catch_msg(QCTNAME(player) + " blinks out of the material realm, "+
        "reappearing behind you. " + capitalize(player->query_possessive()) +
        " enemies move to attack you!\n");                           
    tell_room(environment(player), QCTNAME(player) + " " 
              + " disappears and reappears behind " + QTNAME(friend) 
              + ", who is attacked by " + player->query_possessive()
              + " enemies!\n", ({ player, friend }) );
}