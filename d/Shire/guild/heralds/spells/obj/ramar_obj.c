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
 *
 * Created by Petros, March 2010
 * Adapted for generic summoning by Petros, May 2011
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <language.h>
#include "/d/Genesis/specials/new/magic/spells/objs/defs.h"

inherit "/d/Genesis/specials/new/magic/spells/objs/summon_obj";

// Global Variables
// public object       summon_object = 0;

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_summon_object_");
    set_short("summon spell object");    
    set_long("This is the standard summon spell's object. It exists "
        + "to keep track of the caster's maintained effects.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object created by the " +
        "ramar summon spell.\n");
    set_spell_effect_desc("summon messenger");
    
    set_dispel_time(7200); // by default, a summoned npc can last for up to 2 hours
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

    caster->catch_tell("You hear a shrill cry from on high, and " +
       lower_case(LANG_ASHORT(summon_object)) + " lands on your " +
       "shoulder.\n");
    tell_room(environment(caster), "You hear a shrill cry from " +
       "right above you as " + lower_case(LANG_ASHORT(summon_object)) + 
       " swoops down from the sky and lands upon " + QCTPNAME(caster) + 
       " shoulder.\n", ({ caster }), caster);
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

    if (!objectp(caster))
    {
        return;
    }
    
    if (!objectp(summon_object))
    {
        caster->catch_tell("You sense that your summoned eagle has "
            + "returned to its eyrie.\n");
        return;
    }

    object env = environment(summon_object);

    if(env->query_humanoid())
    {
        env->catch_tell(capitalize(LANG_THESHORT(summon_object)) + 
        " launches off your shoulder and into the air, returning to " +
        "its eyrie.\n");

        tell_room(environment(env), capitalize(LANG_THESHORT(summon_object)) + 
            " launches off the shoulder of " +QTNAME(env)+ " and into " +
            "the air, returning to its eyrie.\n", ({ env }));
    }
    else
        tell_room(env, capitalize(LANG_THESHORT(summon_object))
            + " launches into the air and flies away, returning to its " +
            "eyrie.\n", ({ }));

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
    
    caster->catch_tell("Your sense the summoned " 
        + summon_object->short() + " is getting restless, and wants " +
        "to return to its eyrie.\n");    
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
        caster->catch_tell("You are mentally unable to maintain "
            + "the summoned " + summon_object->short() + ".\n");
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
    // THis spell effect is only valid if the summoned npc is still alive.
    if (!objectp(summon_object))
    {
        summon_object = 0;
        return 0;
    }
    
    return 1;
}

/*
 * Function:    summon_object_killed
 * Description: When the summoned object is killed, we should remove the
 *              spell effect.
 */
public void
summon_object_killed(object killer)
{
    set_alarm(0.0, 0.0, &dispel_effect(killer));
}
