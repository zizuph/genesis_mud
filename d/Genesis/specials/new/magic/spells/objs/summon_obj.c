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

#include "defs.h"

inherit SPELL_OBJ_DIR + "spell_obj_base";

// Global Variables
public object       summon_object = 0;

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

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the summon spell.\n");
    set_spell_effect_desc("summoned monster");

}

/*
 * Function:    query_summoned_object()
 * Description: Returns the summoned object
 */
public object
query_summoned_object()
{
    return summon_object;
}

/*
 * Function:    customize_summoned_creature
 * Description: Called after the creature has been cloned and summoned, this
 *              allows inheriting spells to customize the summoned creature.
 */
public void
customize_summoned_object(object summon_object, mapping input)
{
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
    // We create the messenger first so that we can use the object in
    // the hook messages for starting the effect.
    setuid();
    seteuid(getuid());
    mapping input = query_spell_effect_input();
    summon_object = clone_object(input["summon_file"]);

    object caster = query_effect_caster();
    // Now we move it into either the inventory or the environment.
    int move_into_environment = 1;
    if (input["summon_into_inventory"])
    {
        // move returns 0 if it's a success. Anything else means it failed.
        move_into_environment = summon_object->move(caster);
    }    
    if (move_into_environment)
    {
        summon_object->move(environment(caster), 1);
    }
    
    // Set the spell effect target to the summeoned npc so that it
    // will show in "spelleffects" command correctly.
    set_spell_effect_target(summon_object);

    // Add the summoning shadow so that the spell effect will get removed
    clone_object(SPELL_OBJ_DIR + "summon_sh")->shadow_me(summon_object);
    summon_object->set_spell_object(this_object());
    customize_summoned_object(summon_object, input);
    
    int result = ::setup_spell_effect();
    if (!result)
    {
        summon_object-> ect();
        summon_object = 0;
        return result;
    }

    // by default, a summoned npc can last for up to 2 hours    
    // set_dispel_time(7200); 
    // No longer! Summon npcs stay depending on spell class
    // and spell skills.

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
    if (summon_object && environment(this_object()) == summon_object)
    {
        move(environment(summon_object), 1);
    }
    object tmp_obj = summon_object;
    summon_object = 0;
    tmp_obj->remove_object();

    return 1;
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
    caster->catch_tell("You summon a " + summon_object->short() + ".\n");
    tell_room(environment(caster), QCTNAME(caster) + " summons a "
        + summon_object->short() + ".\n", ({ caster }), caster);
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
        caster->catch_tell("You sense that your magically summoned "
            + "monster has faded from existence.\n");
        return;
    }
    
    caster->catch_tell("Your sense the magically summoned " 
        + summon_object->short() + " fade from existence.\n");
    tell_room(environment(summon_object), QCTNAME(summon_object)
        + " disappears.\n", ({ caster }));
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
    
    caster->catch_tell("Your sense the magically summoned " 
        + summon_object->short() + " begin to fade from existence.\n");    
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
