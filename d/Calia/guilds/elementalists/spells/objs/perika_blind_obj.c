/*
 * Standard Blind Object
 *
 * This is the spell object for the standard Genesis Magic System's
 * blind spell. It blinds the target for a limited duration.
 *
 * Specific guild implementations can inherit this object and set it
 * it up to match their specific needs.
 *
 * Created by Navarre, March 2010.
 */
#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <time.h>

#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "blind_obj";

/*
 * Function:    hook_blind_begin
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_blind_begin(object actor, object target, object *effects)
{
    if (objectp(target))
    {
        target->catch_tell("Your eyes begin to burn profusely.\nYou have "+
            "been blinded!\n");
    }
    
    if (objectp(actor))
    {
        actor->catch_msg(QCTNAME(target) + " has been blinded!\n");
    }
}


/*
 * Function:    hook_blind_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_blind_ended(object actor, object target, object *effects)
{
    if (objectp(target))
    {
        target->catch_tell("Your eyes stop burning and you can see again.\n");
    }

    if (objectp(actor) && objectp(target) 
        && environment(actor) == environment(target))
    {
        actor->catch_msg(QCTNAME(target) + " blinks a few times and seems "
            + "to be able to see again.\n");
    }
}

public void 
hook_blind_failed(object actor, object target)
{
    actor->catch_msg(QCTNAME(target) + " does not seem to be affected.\n");
}

