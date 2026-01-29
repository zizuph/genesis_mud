/*
 *  /d/Gondor/guilds/rangers/spells/obj/nightv_ob.c
 *
 *  Standardized nightvision object for the new spell system.
 *     Zizuph 2022-06 - converted from the old shadow.
 */
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../../rangers.h"

#include "/d/Genesis/specials/local.h";
inherit SPELL_OBJ_DIR + "darkvision_obj";

#define EYES_SUBLOC "nightvision_eyes"

public string
show_subloc(string subloc, object on, object for_obj)
{
    if (subloc == EYES_SUBLOC && for_obj != on)
        return "";

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
        subloc != EYES_SUBLOC)
        return "";

    if (for_obj != on)
    {
        return capitalize(POSSESSIVE(on)) +" eyes sparkle with " +
            "a strange emerald-green glow.\n";
    }
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
        target->catch_tell("Your eyes feel strange and more perceptive.\n");
        tell_room(ENV(target), QCTNAME(target) + " exclaims " +
          "'Elbereth!', and " + POSSESSIVE(target) + " eyes start " +
          "glowing a faint emerald-green.\n", target);
        target->add_subloc(EYES_SUBLOC, this_object());
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
        target->catch_tell("Your nightvision slowly fades away.\n");
        tell_room(ENV(target), QCTPNAME(target) + " eyes slowly " +
          "stop glowing.\n", target);
        target->remove_subloc(EYES_SUBLOC);
    }
}
