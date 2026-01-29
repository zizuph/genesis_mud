/*
 * Standard Haste Object
 *
 * This is the spell object for the standard Genesis Magic System Haste
 * spell. It causes one's LIVE_I_QUICKNESS to be higher, which allows
 * players to execute combat rounds more quickly.
 *
 * Specific guild implementations must inherit from this one to get
 * the standard AoB approved effects.
 *
 * Created by Petros, May 2010
 *
 * Comments:
 * Carnak 2018-04-14: We have moved the formulas in this file, if you encounter
 *                    any issues you can restore the _bak file.
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "defs.h"
inherit SPELL_OBJ_DIR + "spell_obj_base";

#include "/d/Genesis/specials/calculations.c"

// Global Variables
public int  Quickness = 100; // default to 25% aid, which is 100 quickness.

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_haste_object_");
    set_short("haste spell object");    
    set_long("This is the standard haste spell's object. It causes "
        + "one to move faster.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the haste spell.\n");
    set_spell_effect_desc("haste");

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

    object target = query_effect_target();
    int aid;
    if (aid = query_spell_effect_input())
    {
        Quickness = convert_caid_to_haste(target, aid);
    }
    target->inc_prop(LIVE_I_QUICKNESS, Quickness);
    target->query_combat_object()->cb_update_speed();
    
    set_dispel_time(get_default_spell_time());

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
    
    object target = query_effect_target();
    target->dec_prop(LIVE_I_QUICKNESS, Quickness); // Quickness is stored from start function.
    Quickness = 0;
    target->query_combat_object()->cb_update_speed();

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
        target->catch_tell("You begin to move faster.\n");
        tell_room(environment(target), QCTNAME(target) + " begins to move "
            + "more quickly.\n", ({ target }));
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
        target->catch_tell("You stop moving faster.\n");
        tell_room(environment(target), QCTNAME(target) + " seems to slow "
            + "down.\n", ({ target }));
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
        target->catch_tell("You sense yourself starting to slow down.\n");
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
            + "your quick movements.\n");
    }    
}
