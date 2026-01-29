/*
 * Standard Spell Shadow Object
 *
 * This is the spell object for standard Genesis Magic System
 * shadow spells. It shadows the target to provide the intended effects.
 *
 * Specific guild implementations of shadow spells must inherit from this 
 * one to get the standard AoB approved effects.
 *
 * Created by Petros, March 2011
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "defs.h"

inherit "/d/Genesis/specials/std/spells/obj/spell_obj_base";

// Global Variables
public string   Shadow_filename = STD_SPELL_OBJ_DIR + "shadow_base_sh";
public function Remove_shadow_func = 0;
public function Has_shadow_func = 0;
public function Hook_spell_effect_started_func = 0;
public function Hook_spell_effect_ended_func = 0;
public function Hook_spell_effect_warn_fading_func = 0;
public function Hook_spell_effect_not_maintained_func = 0;

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_standard_shadow_spell_object_");
    set_short("shadow spell object");    
    set_long("This is the standard shadow spell's object. It creates "
        + "an effect on the target.\n");

    set_spell_effect_desc("shadow target");
    
    set_dispel_time(1800);
}

/*
 * Function:    query_shadow_filename
 * Description: Returns the set filename for the shadow.
 */
public string
query_shadow_filename()
{
    return Shadow_filename;
}

/*
 * Function:    set_shadow_filename
 * Description: Allows someone to set the shadow that should be cloned and
 *              shadow the target.
 */
public void
set_shadow_filename(string filename)
{
    Shadow_filename = filename;
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

    setuid();
    seteuid(getuid());
    object target = query_effect_target();
    mapping spell_input = query_spell_effect_input();
    if (mappingp(spell_input))
    {
        if (spell_input["shadow_filename"])
        {
            set_shadow_filename(spell_input["shadow_filename"]);
        }
    }
    object shadow_obj = clone_object(query_shadow_filename());
    shadow_obj->initialize_shadow_base(this_object(), spell_input);
    if (!shadow_obj->shadow_me(target)) {
        shadow_obj->remove_shadow();
        return 0;
    }
    
    // Set all the function pointers so the right functions can be called.
    Remove_shadow_func = shadow_obj->remove_spell_shadow;
    Has_shadow_func = shadow_obj->has_spell_shadow;
    Hook_spell_effect_started_func = shadow_obj->hook_spell_effect_started;
    Hook_spell_effect_ended_func = shadow_obj->hook_spell_effect_ended;
    Hook_spell_effect_warn_fading_func = shadow_obj->hook_spell_effect_warn_fading;
    Hook_spell_effect_not_maintained_func = shadow_obj->hook_spell_effect_not_maintained;
    
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
    
    if (IS_CLONE && functionp(Remove_shadow_func))
    {
        Remove_shadow_func();
    }

    return 1;
}

/*
 * Function:    alarmed_hook_spell_effect_started
 * Description: The function called by an alarm to ensure that the startup
 *              messages get displayed.
 */
public void
alarmed_hook_spell_effect_started(object spell_object)
{
    Hook_spell_effect_started_func(spell_object);
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to the target.
 */
public void
hook_spell_effect_started()
{
    // Because hook_spell_effect_started gets called before the shadow gets set
    // up normally, we need an alarm to call the started function.
    set_alarm(0.0, 0.0, &alarmed_hook_spell_effect_started(this_object()));
    if (functionp(Hook_spell_effect_started_func))
    {
        Hook_spell_effect_started_func(this_object());
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
    if (functionp(Hook_spell_effect_ended_func))
    {
        Hook_spell_effect_ended_func(this_object());
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
    if (functionp(Hook_spell_effect_warn_fading_func))
    {
        Hook_spell_effect_warn_fading_func(this_object());
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
    if (functionp(Hook_spell_effect_not_maintained_func))
    {
        Hook_spell_effect_not_maintained_func(this_object());
    }
}
