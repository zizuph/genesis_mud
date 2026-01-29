/*
 * Filename: aura_sh.c
 *
 * Description: This is a shadow that is used for auras, it performs
 *              a callback functionality on objects, more specifically
 *              determining interactions with surroundings, such as
 *              entering or leaving an environment or meeting living
 *              objects.
 */
#pragma strict_types
#pragma save_binary
#pragma no_inherit

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <formulas.h>

inherit "/d/Genesis/specials/std/spells/obj/shadow_base_sh";

/* Global Variables */
static mapping  spell_object_list = ([]), input = ([]), aura_alarm = ([]);

/*
 * Function name:   query_aura_input
 * Description:     Returns the spell_input set for the spell_object
 * Arguments:       (object) spell_object - The spell object
 * Returns:         (mapping) - Spell_object specific spell_input
 */
public mapping
query_aura_input(object spell_object)
{
    if (!objectp(spell_object))
        return ([]);
    
    return input[spell_object];
} /* query_aura_input */

/*
 * Function name:   query_aura_alarm
 * Description:     Returns the alarm set for the spell_object
 * Arguments:       (object) spell_object - The spell object
 * Returns:         (int) - The alarm id
 */
public int
query_aura_alarm(object spell_object)
{
    if (!objectp(spell_object))
        return 0;
    
    return aura_alarm[spell_object];
} /* query_aura_alarm */

/*
 * Function name:   set_aura_alarm
 * Description:     Sets an alarm in the aura for the specified spell object. It
 *                  returns the alarm id.
 * Arguments:       (object) spell_object - The spell object
 *                  (float) delay - The delay for the alarm
 *                  (float) repeat - The repetitive float value
 *                  (function) func - Function to call
 * Returns:         (int) - The alarm id
 */
public int
set_aura_alarm(object spell_object, float delay, float repeat, function func)
{
    if (!objectp(spell_object) || !functionp(func))
        return 0;
    
    if (aura_alarm[spell_object])
        remove_alarm(aura_alarm[spell_object]);
    
    aura_alarm[spell_object] = set_alarm(delay, repeat, papplyv(func,
                                        ({ spell_object })));
    
    return aura_alarm[spell_object];
} /* set_aura_alarm */

/*
 * Function name:   query_spell_objects
 * Description:     Returns the spell objects matching the aura_id
 * Arguments:       (mixed) aura_id - The id for which we query
 * Returns:         (object *) - Array of spell objects matching aura_id 
 */
public object *
query_spell_objects(mixed aura_id)
{
    if (member_array(aura_id, m_indexes(spell_object_list)) < 0)
        return ({});
    
    return filter(spell_object_list[aura_id], &objectp());
} /* query_spell_objects */
                
/*
 * Function name:   initialize_shadow
 * Description:     Called after first cloned. Should do all the initialization
 *                  effects for this particular shadow.
 * Arguments:       (object) spell_object - The spell object
 *                  (object) spell_input - The spell input
 * Returns:         Nothing
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    function func;
    
    spell_object->set_spell_effect_desc("aura");
    spell_object->set_short("aura spell object");
    
    if (functionp(func = spell_input["dispel_time"]))
        spell_object->set_dispel_time(applyv(func, ({ spell_object })));
    
    if (pointerp(spell_input["aura_alarm"]))
        applyv(set_aura_alarm, ({ spell_object }) + spell_input["aura_alarm"]);
    
    spell_object_list[spell_input["aura_id"]] = spell_object;
    
    input[spell_object] = spell_input;
} /* initialize_shadow */

/*
 * Function name:   hook_spell_effect_started
 * Description:     Override this to customize the message when this spell
 *                  effect is added to the target.
 * Arguments:       (object) spell_object - The spell object
 * Returns:         Nothing
 */
public void
hook_spell_effect_started(object spell_object)
{
    function func;
    
    if (functionp(func = input[spell_object]["hook_spell_effect_started"]))
        applyv(func, ({ spell_object }));
} /* hook_spell_effect_started */

/*
 * Function name:   hook_spell_effect_ended
 * Description:     Override this to customize the message when this spell
 *                  effect is dispelled.
 * Arguments:       (object) spell_object - The spell object
 * Returns:         Nothing
 */
public void
hook_spell_effect_ended(object spell_object)
{
    function func;
    
    if (functionp(func = input[spell_object]["hook_spell_effect_ended"]))
        applyv(func, ({ spell_object }));
} /* hook_spell_effect_ended */

/*
 * Function name:   hook_spell_effect_warn_fading
 * Description:     Override this to customize the message for when the effect
 *                  has only a minute left.
 * Arguments:       (object) spell_object - The spell object
 * Returns:         Nothing
 */
public void
hook_spell_effect_warn_fading(object spell_object)
{
    function func;
    
    if (functionp(func = input[spell_object]["hook_spell_effect_warn_fading"]))
        applyv(func, ({ spell_object }));
} /* hook_spell_effect_warn_fading */

/* 
 * Function name:   hook_spell_effect_not_maintained
 * Description:     Override this to describe the effect when the caster cannot
 *                  maintain the effect.
 * Arguments:       (object) spell_object - The spell object
 * Returns:         Nothing
 */
public void
hook_spell_effect_not_maintained(object spell_object)
{
    function func;
    
    if (functionp(func = input[spell_object]["hook_spell_effect_not_maintained"]))
        applyv(func, ({ spell_object }));
} /* hook_spell_effect_not_maintained */

/*
 * Function name:   init_living
 * Description:     Tells us of new living entities in our vicinity.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
init_living()
{
    function func;
    shadow_who->init_living();
    
    foreach(object spell_object: m_indexes(input))
    {
        if (functionp(func = input[spell_object]["init_living"]))
            applyv(func, ({ spell_object, this_player(), this_object() }));
    }
} /* init_living */

/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 */
void
enter_env(object dest, object old)
{
    function func;
    shadow_who->enter_env(dest, old);
    
    foreach(object spell_object: m_indexes(input))
    {
        if (functionp(func = input[spell_object]["enter_env"]))
            applyv(func, ({ spell_object, dest, old }));
    }
} /* enter_env */

/*
 * Function name: leave_env
 * Description  : This function is called each time this object leaves an
 *                old environment. If you mask it, be sure that you
 *                _always_ call the ::leave_env(dest, old) function.
 * Arguments    : object old  - the location we are leaving.
 *                object dest - the destination we are going to. Can be 0.
 */
void
leave_env(object old, object dest) 
{
    function func;
    shadow_who->leave_env(old, dest);
    
    foreach(object spell_object: m_indexes(input))
    {
        if (functionp(func = input[spell_object]["leave_env"]))
            applyv(func, ({ spell_object, old, dest }));
    }
} /* leave_env */

/*
 * Function name:   team_join
 * Description:     Make someone a member of our team.
 *                  Fails if we have a leader, then we can't lead others.
 * Arguments:       (object) member - The new member of my team.
 * Returns:         (int) 1 - success
 *                        0 - failure
 */
public int
team_join(object member)
{
    function func;
    
    if (shadow_who->team_join(member))
    {
        foreach(object spell_object: m_indexes(input))
        {
            if (functionp(func = input[spell_object]["team_join"]))
                applyv(func, ({ spell_object, member }));
        }
        
        return 1;
    }
    
    return 0;
} /* team_join */

/*
 * Function name:   team_leave
 * Description:     Someone leaves my team.
 * Arguments:       (object) member - the member leaving my team.
 * Returns:         Nothing
 */
public void 
team_leave(object member)
{
    function func;
    
    shadow_who->team_leave(member);
    
    foreach(object spell_object: m_indexes(input))
    {
        if (functionp(func = input[spell_object]["team_leave"]))
            applyv(func, ({ spell_object, member }));
    }
} /* team_leave */