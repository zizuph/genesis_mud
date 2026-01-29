/*
 * Standard Darkvision Object
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>

inherit "/d/Genesis/specials/std/spells/obj/spell_obj_base";

// Global Variables
int darkness_sight = 1;
object helm;

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_mw_see_dark_object_");
    set_short("masterwork see dark spell object");    
    set_long("This is the standard dark vision spell's object"
        + " for enchanted masterwork armours.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the see_dark_ability.c spell.\n");
    set_spell_effect_desc("dark vision");  
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

    set_dispel_time(900);

    object target = query_effect_target();
    target->inc_prop(LIVE_I_SEE_DARK, darkness_sight);

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
    
    query_effect_target()->dec_prop(LIVE_I_SEE_DARK, darkness_sight);
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
    helm = target->query_armour(TS_HEAD);
    string helm_str = helm->query_short();

    if (objectp(target))
    {
        target->catch_tell("You feel vision sharpen, as if an invisible " +
            "visor that enhanced your night vision was placed across " +
            "your " +helm_str+ ".\n");
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
        target->catch_tell("You feel your vision dull, and your night vision " +
            "disappear.\n");
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
        caster->catch_tell("You feel your vision dull, and your night vision " +
            "disappear.\n");
    }    
}
