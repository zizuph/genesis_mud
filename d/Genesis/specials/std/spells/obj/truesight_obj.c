/*
 * Standard Truesight Object
 *
 * This is the spell object for the standard Genesis Magic System Truesight
 * spell. It provides the ability to see the invisible as a duration
 * spell effect, and continually drains mana.
 *
 * Specific guild implementations must inherit from this one to get
 * the standard AoB approved effects.
 *
 * Created by Navarre, October 2010.
 * Adapted by Petros, August 2012
 */
#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "defs.h"

inherit "/d/Genesis/specials/std/spells/obj/spell_obj_base";

#define INVIS_LEVEL 10

// Global Variables
int g_invis_amount = INVIS_LEVEL;

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_truesight_object_");
    set_short("truesight spell object");    
    set_long("This is the standard truesight spell's object. It grants "
        + "the ability to see the invisible.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the truesight spell.\n");
    set_spell_effect_desc("see the invisible");
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
        return 0;  // result will be 0
    }

    int power = query_spell_effect_power();
    // Power determines how long the spell lasts
    int duration = ftoi(log(itof(power)) * 300.0);
    set_dispel_time(duration);
    
    object target = query_effect_target();

    int current_see_invis = target->query_prop(LIVE_I_SEE_INVIS);
    if (g_invis_amount + current_see_invis >= 100)
    {
        // don't allow someone to see to 100. That is wizard-style see invis.
        // assume that they're not at 99 already.
        g_invis_amount = max(1, 100 - current_see_invis);
    }
    target->inc_prop(LIVE_I_SEE_INVIS, g_invis_amount);
    return result;
}

public varargs int
dispel_spell_effect(object dispeller)
{
    int result = ::dispel_spell_effect(dispeller);
    
    if (!result)
    {
        return 0; // result with be 0;
    }
    
    object target = query_effect_target();

    target->dec_prop(LIVE_I_SEE_INVIS, g_invis_amount);
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
        target->catch_tell("You eyes tingle and it seems your vision changes.\n");
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
        target->catch_tell("Your enhanced vision fades.\n");
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
    object target = query_effect_target();
    
    if (objectp(target))
    {
        target->catch_tell("You sense your enhanced vision " +
                           "beginning to decrease.\n");
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
        caster->catch_tell("You are mentally unable to maintain " +
                           "your enhanced vision.\n");
    }    
}
