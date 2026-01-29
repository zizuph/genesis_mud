/*
 * Filename:    locate_sh.c
 * Description: This is the spell shadow for the locate spell that finds
 *              the shortest path to a desired area, it runs until it finds a
 *              room matching the perform_locate_check or until the end of the
 *              limit if multiple checks is enabled.
 *
 * Created by Carnak at 2018-01-18
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/obj/shadow_base_sh";

/* Global Variables */
static mapping paths = ([]);

/*
 * Function name:   initialize_shadow
 * Description:     Called after first cloned. Should do all the initialization
 *                  effects for this particular shadow.
 * Arguments:       1. (object) spell_object - The effect object
 * Arguments:       1. (mapping) spell_input - Unique spell input
 * Returns:         Nothing
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    object  target;
    int     power, duration;
    
    spell_object->set_spell_effect_desc("locate");
    spell_object->set_short("locate spell object");

    power = spell_object->query_spell_effect_power();
    // Power determines how long the spell lasts
    duration = power / 10;
    spell_object->set_dispel_time(duration);
    
    target = spell_object->query_spell_effect_target();
    
    paths[spell_object] = spell_input["paths"][target];
} /* initialize_shadow */

/*
 * Function name:   hook_spell_effect_started
 * Description:     Override this to customize the message when this spell
 *                  effect is added to th target.
 * Arguments:       (object) spell_object - The effect object
 * Returns:         Nothing
 */
public void
hook_spell_effect_started(object spell_object)
{
    object target = spell_object->query_effect_target();

    if (!m_sizeof(paths[spell_object]))
    {
        target->catch_tell("A faint glimmer fills the air, aimlessly spiraling "
        + "around you.\n");
        return;
    }
    
    if (objectp(target))
    {
        target->catch_tell("A faint glimmer fills the air. It quickly spirals "
        + "towards the ground forming a glowing path infront of you.\n");
    }
} /* hook_spell_effect_started */

/*
 * Function name:   hook_spell_effect_ended
 * Description:     Override this to customize the message when this spell
 *                  effect is dispelled.
 * Arguments:       (object) spell_object - The effect object
 * Returns:         Nothing
 */
public void
hook_spell_effect_ended(object spell_object)
{
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("The glimmer fades, leaving no traces behind.\n");
    }
} /* hook_spell_effect_ended */

/*
 * Function name:   hook_spell_effect_warn_fading
 * Description:     Override this to customize the message for when the effect
 *                  has only a minute left.
 * Arguments:       (object) spell_object - The effect object
 * Returns:         Nothing
 */
public void
hook_spell_effect_warn_fading(object spell_object)
{
    object  caster = spell_object->query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You feel your ability to maintain the glowing path "
        + "begin to waver.\n");
    }
} /* hook_spell_effect_warn_fading */

/* 
 * Function name:   hook_spell_effect_not_maintained
 * Description:     Override this to describe the effect when the caster cannot
 *                  maintain the effect.
 * Arguments:       (object) spell_object - The effect object
 * Returns:         Nothing
 */
public void
hook_spell_effect_not_maintained(object spell_object)
{
    object caster = spell_object->query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain the chosen "
        + "path.\n");
    }
} /* hook_spell_effect_not_maintained */

/*
 * Function name:   hook_return_to_path
 * Description:     A hook for when you return to the path after having left it.
 * Arguments:       1. (object) to      - The environment we are entering.
 *                  2. (object) from    - The environment we are leaving.
 * Returns:         Nothing
 */
public void
hook_return_to_path(object to, object from)
{
    shadow_who->catch_msg("You return to the glowing path.\n");
} /* hook_return_to_path */

/*
 * Function name:   hook_follow_path
 * Description:     A hook for when you follow the path.
 * Arguments:       1. (object) to      - The environment we are entering.
 *                  2. (object) from    - The environment we are leaving.
 * Returns:         Nothing
 */
public void
hook_follow_path(object to, object from)
{
    shadow_who->catch_msg("You follow to the glowing path.\n");
} /* hook_follow_path */

/*
 * Function name:   hook_end_of_path
 * Description:     A hook for when you reach the end of the path.
 * Arguments:       1. (object) to      - The environment we are entering.
 *                  2. (object) from    - The environment we are leaving.
 * Returns:         Nothing
 */
public void
hook_end_of_path(object to, object from)
{
    shadow_who->catch_msg("You have reached the end of the path.\n");
} /* hook_end_of_path */

/*
 * Function name:   hook_strayed_from_path
 * Description:     A hook for when you strayed from the path but have a chance
 *                  of returning to it.
 * Arguments:       1. (object) to      - The environment we are entering.
 *                  2. (object) from    - The environment we are leaving.
 * Returns:         Nothing
 */
public void
hook_strayed_from_path(object to, object from)
{
    shadow_who->catch_msg("You have strayed from the path.\n");
} /* hook_strayed_from_path */

/*
 * Function name:   hook_abandoned_path
 * Description:     A hook for when you abandon the path, removing all traces.
 * Arguments:       1. (object) to      - The environment we are entering.
 *                  2. (object) from    - The environment we are leaving.
 * Returns:         Nothing
 */
public void
hook_abandoned_path(object to, object from)
{
    shadow_who->catch_msg("You abandon the path entirely.\n");
} /* hook_abandoned_path */

/*
 * Function name:   hook_path_description
 * Description:     A hook for displaying the path when glancing or looking.
 * Arguments:       1. (string *) exits - The array string list of exits.
 *                  2. (int) brief      - Brief of full description.
 * Returns:         Nothing
 */
public void
hook_path_description(string *exits, int brief)
{
    shadow_who->catch_msg("The glowing path leads " + COMPOSITE_WORDS(exits)
    + ".\n");
} /* hook_path_description */

/*
 * Function name:   enter_env
 * Description:     Determine if the room is amongst the path.
 * Arguments:       (object) to - the object we are entering
 *                  (object) from - the object we come from
 * Returns:         Nothing
 */
void
enter_env(object to, object from)
{
    string *all_path = ({});
    int     strayed, abandoned,
            followed, returned;
    
    shadow_who->enter_env(to, from);
    
    foreach(object spell_obj, mapping path_list: paths)
    {
        if (member_array(file_name(to), m_indexes(path_list)) > -1)
        {
            hook_end_of_path(to, from);
            spell_obj->dispel_effect(shadow_who);
        }
        
        foreach(string room, string *path: path_list)
        {
            all_path += path;
            
            if (member_array(file_name(from), path) < 0 &&
                member_array(file_name(to), path) < 0)
                paths[spell_obj] = m_delete(paths[spell_obj], room);
        }
        
        if (!m_sizeof(paths[spell_obj]))
            spell_obj->dispel_effect(shadow_who);
    }
    
    if (member_array(file_name(to), all_path) > -1)
    {
        if (member_array(file_name(from), all_path) > -1)
            hook_follow_path(to, from);
        else
            hook_return_to_path(to, from);
    }
    else if (member_array(file_name(from), all_path) > -1)
        hook_strayed_from_path(to, from);
    else
        hook_abandoned_path(to, from);
} /* enter_env */

/*
 * Function name:   do_glance
 * Description:     This is the routine describing rooms to livings. It will
 *                  print the long or short description of the room, the
 *                  possible exits, all visible non-living and living objects
 *                  in the room (but not this_object() itself) and then it
 *                  will print possible attacks going on. Note that this
 *                  function performs a write(), so this_player() will get the
 *                  descriptions printed to him/her.
 * Arguments:       (int) brief - if true, write the short-description, else
 *                                write the long-description.
 * Returns:         (int) 1 - always.
 */
public int
do_glance(int brief)
{
    string *exits = ({}),
           *locs = ({}),
            loc, exit;
    int     arr_num;
    
    shadow_who->do_glance(brief);
    
    foreach(object spell_obj, mapping path_list: paths)
    {
        foreach(string room, string *path: path_list)
        {
            if (file_name(environment(shadow_who)) == room)
                continue;
            
            loc = file_name(environment(shadow_who));
            path += ({ room });
            
            if ((arr_num = member_array(loc, path)) > -1)
            {
                locs = loc->query_exit();
                foreach(mixed arr: locs)
                {
                    if (stringp(arr) && explode(arr, ".c")[0] == path[arr_num + 1])
                        exit = locs[member_array(arr, locs) + 1];
                }
                
                if (member_array(exit, exits) < 0)
                    exits += ({ exit });
            }
        }
    }
    
    if (sizeof(exits))
        hook_path_description(exits, brief);
    
    return 1;
} /* do_glance */