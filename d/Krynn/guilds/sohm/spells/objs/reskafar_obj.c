/*
 * Standard Summoning Object
 *
 * This is the spell object for the standard Genesis Magic System Summon
 * spell. It creates a summoned npc. By default, it creates a messenger
 * that can be sent to others. This spell object will be a maintained spell 
 * effect, so will drain the caster's mana while it is in effect.
 *
 * Specific guild implementations must inherit from this one to get
 * the standard AoB approved effects.
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <language.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "summon_obj";

// Global Variables
// public object       summon_object = 0;


public int
setup_spell_effect()
{
    int result = ::setup_spell_effect();
    if (!result)
    {
        return result;
    }
    set_name("_summon_object_");
    set_short("summon spell object");    
    set_long("This is the standard summon spell's object. It exists "
        + "to keep track of the caster's maintained effects.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object created by the " +
        "WoHS reskafar summon spell.\n");
    set_spell_effect_desc("Dimensional Rift");
    set_dispel_time(30); 
    return result;
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to the target.
 */
public void
hook_spell_effect_started()
{
    object caster = query_effect_caster();

    caster->catch_tell("With a concussive crack of sound, you tear open " +
       "a rift in the fabric of space and time!\n");
    tell_room(environment(caster), "With a concussive crack of sound, " +
       "a rift in the fabric of space and time suddenly is torn " +
       "open!\n", ({ caster }), caster);
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    object caster = query_effect_caster();

    if (objectp(summon_object))
    {
        object env = environment(summon_object);

        tell_room(env, "With a loud 'snap' the dimensional rift " +
            "vanishes.\n", ({ caster }));
        caster->catch_tell("With a loud 'snap' the dimensional rift " +
            "vanishes, the backlash of which blasts your mental " +
            "reserves.\n");

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
    object caster = query_effect_caster();
    if (!objectp(caster) || !objectp(summon_object))
    {
        return;
    }
    
    caster->catch_tell("You struggle to maintain the dimensional rift. You " +
        "feel it will shortly close.\n");    
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
    
    if (objectp(caster) && objectp(summon_object))
    {
        caster->catch_tell("You are mentally unable to keep open "
            + "the dimensional rift.\n");
    }    
}

/*
 * Function:    query_spell_effect_still_valid()
 * Description: For a maintained spell effect, this allows the spell
 *              effect to determine whether it is still valid or not.
 *              In the maintain_spell_effects function, it will dispel
 *              the effect object if it determines that it is no longer
 *              valid.
 */
public int
query_spell_effect_still_valid()
{
    if (!objectp(summon_object))
    {
        summon_object = 0;
        return 0;
    }
    
    return 1;
}

