/*
 * Filename:    aura.c
 * Description: This is a spell that adds an aura to the target, it allows
 *              for masking functions that involves meeting others or entering
 *              rooms..
 *
 * Created by Carnak at 2018-01-18
 */
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/shadow";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"
#include "/d/Genesis/specials/debugger/debugger_tell.h"

/* Global Variables*/
static mapping      gFunctionMap = ([]),    /* Mapping of functions pointers */
                    gActiveEffects = ([]);  /* Mapping of active effects */
static function     gAuraDuration;          /* Determines the aura duration */
static mixed       *gAuraAlarm,             /* Unique alarm for each spell object */
                    gAuraEffects;           /* The effects being added by the aura */

/* Prototypes */
public void     resolve_aura_spell(object caster, object *targets, int *resist,
                                   int result, mapping input);
public void     hook_aura_effect_not_maintained(object spell_object);
public void     hook_aura_effect_warn_fading(object spell_object);
public void     hook_aura_effect_started(object spell_object);
public void     hook_aura_effect_ended(object spell_object);

/*
 * Function name:   query_aura_effects
 * Description:     Returns the effects with which the aura will affect targets
 * Arguments:       None
 * Returns:         (mixed *) - Array of effects
 */
public mixed
query_aura_effects()
{
    return gAuraEffects;
} /* query_aura_effects */

/*
 * Function name:   set_aura_effects
 * Description:     Sets which effects the aura affects others with
 * Arguments:       (mixed) effects - the effect or effects
 * Returns:         Nothing
 */
public void
set_aura_effects(mixed effects)
{
    if (!pointerp(effects))
        effects = ({ effects });
    
    gAuraEffects = effects;
} /* query_aura_effects */

/*
 * Function name:   has_effect_object
 * Description:     Checks to see if the target is already affected by the aura
 * Arguments:       (object) target
 * Returns:         (status) 1 - Affected by aura
 *                           0 - Not affected
 */
public status
has_effect_object(object target)
{
    mixed effects = ({});
    
    foreach(mixed effect: query_aura_effects())
    {
        effects += filter(target->query_magic_effects(),
                        &wildmatch(effect + "#*") @ file_name);
    }
    
    if (sizeof(effects))
        return 1;
    
    return 0;
} /* has_effect_object */

/*
 * Function name:   add_aura_effect
 * Description:     Adds the spells effects to the target when called.
 * Arguments:       (object) spell_object - The original aura spell object
 *                  (object) caster - The one excuding the aura 
 *                  (object) target - The one affected by the aura
 * Returns:         Nothing
 */
public void
add_aura_effect(object spell_object, object caster, object target)
{
    int     resist;
    object *effects = ({});
    
    if (pointerp(gActiveEffects[target]))
        effects = gActiveEffects[target];
    
    resist = use_spell_resist(caster, target, query_ability_name());
    
    foreach(mixed effect: query_aura_effects())
    {
        effects += ({ make_spell_object(effect, caster, target, resist, 100) });
    }
    
    gActiveEffects[target] = effects;
} /* add_aura_effect */

/*
 * Function name:   remove_aura_effect
 * Description:     Removes all the active effects from the target.
 * Arguments:       (object) spell_object - The original aura spell object
 *                  (object) caster - The one excuding the aura 
 *                  (object) target - The one affected by the aura
 * Returns:         Nothing
 */
public void
remove_aura_effect(object spell_object, object caster, object target)
{
    if (objectp(gActiveEffects[target]))
        gActiveEffects[target] = ({ gActiveEffects[target] });
    
    if (pointerp(gActiveEffects[target]))
        gActiveEffects[target] -= ({ 0 });
    
    if (sizeof(gActiveEffects[target]))
        gActiveEffects[target]->dispel_effect(caster);
} /* remove_aura_effect */

/*
 * Function name:   set_aura_alarm
 * Description:     Sets the alarm time and function to which we callback for
 *                  our aura alarms. The vectors are applied as arguments to the
 *                  specified function.
 * Arguments:       (float) delay - The time for the alarm
 *                  (float) repeat - The repetitive float value
 *                  (function) func - The function to which we callback.
 * Vectors:         (object) - The spell object
 * Returns:         Nothing
 */
public void
set_aura_alarm(float delay, float repeat, function func)
{
    gAuraAlarm = ({ delay, repeat, func });
} /* set_aura_alarm */

/*
 * Function name:   set_aura_duration
 * Description:     Sets the function to which we callback for determining the
 *                  duration of the aura. The vectors are applied as arguments
 *                  to the specified function.
 * Arguments:       (function) duration - The function to which we callback.
 * Vectors:         (object) - The spell object
 * Returns:         Nothing
 */
public void
set_aura_duration(function duration)
{
    gAuraDuration = duration;
} /* set_aura_duration */

/*
 * Function name:   add_function_pointer
 * Description:     Adds a function pointer to which we callback from the aura
 *                  shadow. A vector of arguments are applied to the specified
 *                  function from the shadow.
 * Arguments:       (string) function_name - The name of the function masked in
 *                                           the aura_sh.
 *                  (function) func - The function to which we callback.
 * Returns:         Nothing
 */
public void
add_function_pointer(string function_name, function func)
{
    gFunctionMap[function_name] = func;
} /* add_function_pointer */

/*
 * Function name:   remove_function_pointer
 * Description:     Remove a function pointer to which we callback from the aura
 *                  shadow.
 * Arguments:       (string) function_name - The name of the function masked in
 *                                           the aura_sh.
 * Returns:         Nothing
 */
public void
remove_function_pointer(string function_name)
{
    m_delkey(gFunctionMap, function_name);
} /* remove_function_pointer */

/*
 * Function name:   config_aura_spell
 * Description:     Config function for aura spells. Redefine this in your own
 *                  aura spells to override the defaults.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
config_aura_spell()
{
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_stationary(1);
    set_spell_can_be_renewed(0);
    
    add_function_pointer("hook_spell_effect_not_maintained",
                         &hook_aura_effect_not_maintained());
    add_function_pointer("hook_spell_effect_warn_fading",
                         &hook_aura_effect_warn_fading());
    add_function_pointer("hook_spell_effect_ended",
                         &hook_aura_effect_ended());
    add_function_pointer("hook_spell_effect_started",
                         &hook_aura_effect_started());
} /* config_aura_spell */

/*
 * Function name:   query_aura_ingredients
 * Description:     This function defines what components are required for this
 *                  aura spell.
 * Arguments:       (object) caster - The caster in whom we look for ingredients
 * Returns:         (string *) - Array of ingredient strings
 */
public string *
query_aura_ingredients(object caster)
{
    return ({  });
} /* query_aura_ingredients */

/*
 * Function name:   config_spell
 * Description:     Basic spell construct
 * Arguments:       None
 * Returns:         Nothing
 */
public nomask void
config_shadow_spell()
{
    ::config_shadow_spell();

    set_spell_name("aura");
    set_spell_desc("activate an aura");
    set_spell_target(spell_target_caster);

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_ingredients(query_aura_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each harm spell should customize these to their specific guild skills.
    set_spell_element(SS_ELEMENT_AIR, 40);
    set_spell_form(SS_FORM_ABJURATION, 40);
        
    // Call the specific configuration that is to be masked.
    config_aura_spell();
    
    set_shadow_filename(STD_SPELLS_DIR + "unfinished/aura_sh");
} /* config_spell */

/*
 * Function name:   resolve_spell
 * Description:     Complete the casting of the spell
 * Arguments:       (object) caster   - the caster
 *                  (object) *targets - an array of targets
 *                  (int) *resist     - resistance percentages corresponding to
 *                                      each target
 *                  (int) result      - how well the spell was cast
 * Returns:         Nothing
 */
public nomask void
resolve_shadow_spell(object caster, object * targets, int * resist, int result,
                     mapping spell_input)
{
    foreach(string function_name, function func: gFunctionMap)
    {
        if (functionp(func))
            spell_input[function_name] = func;
    }
    
    spell_input["dispel_time"] = gAuraDuration;
    spell_input["aura_alarm"] = gAuraAlarm;
    spell_input["aura_id"] = this_object();
    
    resolve_aura_spell(caster, targets, resist, result, spell_input);
} /* resolve_spell */

/*
 * Function name:   check_valid_action
 * Description:     Checks conditions to see whether this spell can be cast.
 * Arguments:       1. (object) The actor
 *                  2. (mixed *) The targets
 *                  3. (string) Arguments passed to the command
 *                  4. (int) Actual spell execution
 * Returns:         (int) 1 if we can continue, 0 if failure
 */
public int
check_valid_action(object caster, mixed * targets, string arg, int execute)
{
    int result = ::check_valid_action(caster, targets, arg, execute);
    
    if (!result)
        return result;
    
    if (!query_spell_can_be_renewed())
    {
        // The aura spell cannot be cast if it is already in effect
        foreach (object target : targets)
        {
            if (has_spell_object(target))
            {
                hook_already_has_spell_object(caster, target);
                return 0;
            }
        }
    }
    
    return result;    
} /* check_valid_action */

/*
 * Function name:   resolve_aura_spell
 * Description:     Called at the beginning of resolve_spell in order to perform
 *                  spell specific actions.
 * Arguments:       Same as resolve_spell
 * Returns:         Nothing
 */
public void
resolve_aura_spell(object caster, object *targets, int *resist, int result,
                   mapping spell_input)
{
} /* resolve_aura_spell */

/*
 * Function name:   hook_aura_effect_started
 * Description:     Override this to customize the message when this spell
 *                  effect is added to th target.
 * Arguments:       (object) spell_object - The spell object
 * Returns:         Nothing
 */
public void
hook_aura_effect_started(object spell_object)
{
    send_debug_message("aura_spell","Started");
} /* hook_aura_effect_started */

/*
 * Function name:   hook_aura_effect_ended
 * Description:     Override this to customize the message when this spell
 *                  effect is dispelled.
 * Arguments:       (object) spell_object - The spell object
 * Returns:         Nothing
 */
public void
hook_aura_effect_ended(object spell_object)
{
    send_debug_message("aura_spell","Ended");
} /* hook_aura_effect_ended */

/*
 * Function name:   hook_aura_effect_warn_fading
 * Description:     Override this to customize the message for when the effect
 *                  has only a minute left.
 * Arguments:       (object) spell_object - The spell object
 * Returns:         Nothing
 */
public void
hook_aura_effect_warn_fading(object spell_object)
{
    send_debug_message("aura_spell","Warn Fading");
} /* hook_aura_effect_warn_fading */

/* 
 * Function name:   hook_aura_effect_not_maintained
 * Description:     Override this to describe the effect when the caster cannot
 *                  maintain the effect.
 * Arguments:       (object) spell_object - The spell object
 * Returns:         Nothing
 */
public void
hook_aura_effect_not_maintained(object spell_object)
{
    send_debug_message("aura_spell","Not Maintained");
} /* hook_aura_effect_not_maintained */