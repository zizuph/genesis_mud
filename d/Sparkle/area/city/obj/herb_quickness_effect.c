/*
 *  /d/Sparkle/area/city/obj/herb_quickness_effect.c
 *
 *  This object is given out to players who complete the Friday Chef's
 *  Quest in Sparkle. It gives them a haste bonus for 24 hours and can
 *  only be obtained once per week.
 *
 *  Created November 2012, by Cooper Sherry (Gorboth)
 */

#pragma strict_types

inherit "/d/Genesis/specials/std/spells/obj/haste_obj";

#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"

#define        SUBLOC_NAME    "_herbvender_cordial_sublocation"

/*
 * Function:    create_spell_object
 * Description: We set our own version of the effect here.
 */
public void 
create_spell_object()
{
    set_name("_haste_object_");
    set_short("haste spell object");    
    set_long("This is the standard haste spell's object. It causes "
        + "one to move faster.\n");

    add_prop(OBJ_S_WIZINFO, "This haste effect is given by the Friday"
      + " Chef's Quest in Sparkle. It lasts for 24 hours or until the"
      + " player logs out.\n");
    set_spell_effect_desc("haste");
    
    set_dispel_time(86400);
} /* create_spell_object */


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
        target->catch_tell("A shudder goes through you, and you feel"
          + " your body positively tingling with speed!\n");
        tell_room(environment(target), QCTNAME(target) + " shudders,"
          + " and begins to blink rapidly.\n", ({ target }));
    } 

    target->add_subloc(SUBLOC_NAME, this_object());
} /* hook_spell_effect_started */


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
        target->catch_tell("All the speed from the Chef's cordial"
          + " seems to have gone, at last.\n");
        tell_room(environment(target), QCTNAME(target) + " droops a bit "
            + "and blinks much more slowly.\n", ({ target }));
    }

    target->remove_subloc(SUBLOC_NAME);
} /* hook_spell_effect_ended */


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
        target->catch_tell("You sense the Chef's cordial beginning"
          + " to finally wear off.\n");
    }
} /* hook_spell_effect_warn_fading */


/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *		  me      - I
 *		  for_obj - The looker
 * Returns:	  The string the looker shall see
 */
public string
show_subloc(string subloc, object me, object for_obj)
{
    string str;

    if (for_obj == me)
    {
	return "You still feel very wired from the Chef's cordial.\n";
    }

    return capitalize(me->query_pronoun()) + " looks positively"
      + " wired, and is blinking rapidly.\n";
} /* show_subloc */