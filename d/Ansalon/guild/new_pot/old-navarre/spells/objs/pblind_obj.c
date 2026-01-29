/*
 * Priests Of Takhisis Blind Object
 *
 * Created by Navarre, May 2013.
 */
#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "../../spells.h"
#include "../../defs.h"

inherit "/d/Genesis/specials/std/spells/obj/blind_obj";

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name(BLIND_ID);
    set_short("pblind spell object");    
    set_long("This is the pblind spell object from the Priests of " +
             "Takhisis.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the pblind spell from the " +
                            "Priests of Takhisis.\n");
    set_spell_effect_desc("blindness");
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
    query_effect_target()->inc_prop(LIVE_I_BLIND);
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
    
    query_effect_target()->dec_prop(LIVE_I_BLIND);
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
    object target = query_spell_effect_target();
    object caster = query_spell_effect_caster();
    
    if (objectp(target))
    {
        target->catch_tell("You feel a sharp pain in your eyes.\nYou have been blinded!\n");
    }
    
    if (objectp(caster))
    {
        caster->catch_msg(QCTNAME(target) + " has been blinded!\n");
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
    object target = query_spell_effect_target();
    object caster = query_spell_effect_caster();

    if (objectp(target))
    {
        target->catch_tell("The black fire leaves your eyes, and you can "+
                           "see again.\n");
    }

    if (objectp(caster))
    {
        caster->catch_msg(target->query_The_name(caster) + 
                          " blinks a few times and seems to be able to " +
                          "see again.\n");
    }
}
