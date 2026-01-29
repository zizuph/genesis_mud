/*
 * Filename:    turn_target.c
 * Description: 
 *
 * Created by Carnak at 2018-01-18
 */
#pragma strict_types

#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <formulas.h>
#include <macros.h>
#include <tasks.h>
#include "defs.h"

inherit STD_SPELLS_DIR + "unfinished/locate";

#define PANIC_LEVEL 50

/* Prototypes */
public void     resolve_turn_target_spell(object caster, object *targets,
                        int *resist, int result, mapping paths);
varargs status  validate_turn_target_effect(object spell_object, mapping path);
public void     meet_living(object spell_object, object met, object affected);
public void     hook_turn_target_brave(object spell_object);
public void     hook_turn_target_flee(object spell_object);
public void     hook_turn_target_stay(object spell_object);
public void     hook_turn_target_immune(object spell_object);
public void     hook_turn_target_blind(object spell_object);
public void     hook_spell_effect_started(object spell_object);
public void     hook_spell_effect_ended(object spell_object);
public void     hook_spell_effect_warn_fading(object spell_object);
public void     hook_spell_effect_not_maintained(object spell_object);
public int      calculate_dispel_time(object spell_object);

/* Global Variables */
static status   Visual_turn_target;


/*
 * Function name:   turn_target_success
 * Description:     Calculate the success of the turn target.
 * Arguments:       (object) spell_object - the spell object in question
 * Returns:         (int) - The success of the spell effect
 */
public int
turn_target_success(object spell_object)
{
    int     success;
    object  caster = spell_object->query_spell_effect_caster(),
            target = spell_object->query_spell_effect_target();
    
    success = caster->resolve_task(
    TASK_ROUTINE,   ({  SKILL_WEIGHT, 40, TS_INT, SKILL_WEIGHT, 40, TS_WIS,
                        SKILL_WEIGHT, 20, SKILL_AVG, SS_ELEMENT_DEATH,
                        SS_SPELLCRAFT, SKILL_END }),
    target,         ({  SKILL_WEIGHT, 20, TS_WIS, SKILL_WEIGHT, 60, TS_DIS,
                        SKILL_WEIGHT, 20, SKILL_AVG, SS_ELEMENT_LIFE,
                        SKILL_END}));
    
    send_debug_message("turn_target","Success: " + success);
    return success;
} /* turn_target_success */

/*
 * Function name:   calculate_dispel_time
 * Description:     Calculate the duration of the turn effect.
 * Arguments:       (object) spell_object - the spell object in question
 * Returns:         (int) - The duration of the spell effect
 */
public int
calculate_dispel_time(object spell_object)
{
    int     wimp, panic, power, temp;
    object  caster = spell_object->query_spell_effect_caster(),
            target = spell_object->query_spell_effect_target();
    
    wimp = F_PANIC_WIMP_LEVEL(target->query_stat(SS_DIS));
    panic = target->query_panic();
    power = spell_object->query_spell_effect_power() / 10;
    // Power is the base length of the spell.
    // Duration is determined by % wimpy
    send_debug_message("turn_target","Power: " + power);
    temp = ftoi(itof(min(panic + power, wimp)) / (itof(wimp) / 100.0));
    send_debug_message("turn_target","Dispel time: " + temp);
    return temp;
} /* calculate_dispel_time */

/*
 * Function name:   query_turn_target_visual
 * Description:     Return a status on whether the fear requires visual or not.
 * Arguments:       None
 * Returns:         (status) 1: visual
 *                           0: non-visual
 */
public status
query_turn_target_visual()
{
    return Visual_turn_target;
} /* query_turn_target_visual */

/*
 * Function name:   set_turn_target_visual
 * Description:     Sets whether the fear requires visual or not.
 * Arguments:       (status) visual - Visual or not.
 * Returns:         Nothing
 */
public void
set_turn_target_visual(status visual)
{
    Visual_turn_target = visual;
} /* set_turn_target_visual */

/*
 * Function name:   config_turn_target_spell
 * Description:     Config function for turn spells. Redefine this in your own
 *                  turn spell to override the defaults.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
config_turn_target_spell()
{
} /* config_turn_target_spell */

/*
 * Function name:   query_turn_target_ingredients
 * Description:     This function defines what components are required for this
 *                  turn spell.
 * Arguments:       (object) caster - The caster in whom we look for ingredients
 * Returns:         (string *) - Array of ingredient strings
 */
public string *
query_turn_target_ingredients(object caster)
{
    return ({ });
} /* query_turn_target_ingredients */

/*
 * Function name:   config_locate_spell
 * Description:     Config function for path spells. Redefine this in your own
 *                  path spells to override the defaults.
 * Arguments:       None
 * Returns:         Nothing
 */
public nomask void
config_locate_spell()
{
    set_spell_name("turn");
    set_spell_desc("Turn someone");
    
    set_spell_can_be_renewed(0);
    set_spell_stationary(1);
    set_spell_offensive(1);
    set_spell_peaceful(0);
    set_spell_visual(1);
    set_spell_vocal(1);
    
    /* How far could the target potentially run */
    set_locate_limit(4);
    
    set_turn_target_visual(1);

    set_spell_ingredients(query_turn_target_ingredients);
    set_spell_target(spell_target_present_livings);
    
    set_spell_element(SS_ELEMENT_DEATH, 10);
    set_spell_form(SS_FORM_ENCHANTMENT, 15);

    config_turn_target_spell();
    
    /* Stops at first occurrence of rooms, not applicable to fear */
    set_multiple_checks(1);
    
    set_shadow_filename(STD_SPELLS_DIR + "unfinished/aura_sh");
    //set_shadow_filename(STD_SPELL_OBJ_DIR + "turn_sh");
    
} /* config_path_spell */

/*
 * Function name:   perform_locate_check
 * Description:     Checks the caller to see if it has reached the desired
 *                  destination.
 * Arguments:       (object) actor - Caster of the spell
 *                  (object) target - Target of the spell
 *                  (object) room - Either object or file_name of the room.
 * Returns:         (int)  0 - Not the desired destination, loop continues with
 *                             the current destinations exits
 *                  (int)  1 - Desired destination, continues with exits
 *                  (int) -1 - Desired destination, ignores exits
 */
public nomask int
perform_locate_check(object caster, object target, object room)
{
    object *locate;
    
    if (!objectp(room) || !room->query_prop(ROOM_I_IS))
        return 0;
    
    /* replace this.. not used anymore.. */
    if (!pointerp(locate = target->query_turn_target_casters()))
        locate = ({});
    
    locate += ({ caster });
    
    /* If the turn is not present, we are fine */
    if (!sizeof(filter(locate, &present(, room))))
        return 1;
    
    return 0;
} /* perform_path_check */


/*
 * Function name:   resolve_locate_spell
 * Description:     Called at the beginning of resolve_spell in order to perform
 *                  spell specific actions.
 * Arguments:       Same as resolve_spell
 * Returns:         Nothing
 */
public nomask void
resolve_locate_spell(object caster, object *targets, int *resist, int result,
                   mapping spell_input)
{
    resolve_turn_target_spell(caster, targets, resist, result, spell_input);
    
    spell_input["effect_maintain"] = &hook_spell_effect_not_maintained();
    spell_input["effect_started"] = &hook_spell_effect_started();
    spell_input["effect_fading"] = &hook_spell_effect_warn_fading();
    spell_input["effect_ended"] = &hook_spell_effect_ended();
    spell_input["dispel_time"] = &calculate_dispel_time();
    spell_input["meet_aura"] = &meet_living();
    spell_input["aura_id"] = this_object();
} /* resolve_locate_spell */

/*
 * Function name:   resolve_turn_target_spell
 * Description:     Called at the beginning of resolve_spell in order to perform
 *                  spell specific actions.
 * Arguments:       Same as resolve_spell
 * Returns:         Nothing
 */
public void
resolve_turn_target_spell(object caster, object *targets, int *resist, int result,
                     mapping paths)
{
} /* resolve_locate_spell */

/*
 * Function name:   resolve_path
 * Description:     Transform the mapping path into exits.
 * Arguments:       (mapping) path - paths derived from locate spell
 * Returns:         (string *) - An array string of exits.
 */
private nomask string *
resolve_path(mapping path)
{
    int     arr_num;
    string *exits = ({}),
           *loc, *dest,
            end, exit;
    
    if (m_sizeof(path))
    {
        end  = one_of_list(m_indexes(path));
        dest = path[end];
        
        if (!pointerp(dest))
            dest = ({});
        
        dest += ({ end });
        
        foreach(string room: dest)
        {
            if (room == end)
                break;
            
            if ((arr_num = member_array(room, dest)) > -1)
            {
                loc = room->query_exit();
            
                /* Get the command for the exit */
                exit = loc[member_array(dest[arr_num + 1], loc) + 1];
        
                if (!pointerp(exits))
                    exits = ({});
                
                exits += ({ exit });
            }
        }
        
        if (sizeof(exits))
            exits = ({ exits });
    }
    
    return exits;
}

/*
 * Function name:   turn_run_away
 * Description:     Handles fleeing in the turn spell.
 * Arguments:       (object) spell_object - the spell object in question
 *                  (string *) path - paths derived from locate spell
 * Returns:         (string *) - An array string of exits.
 */
static varargs void
turn_run_away(object spell_object, string *exits)
{
    string  m_in, m_out;
    object  target, caster, here;
    int     panic;
    mixed   exit;
    
    send_debug_message("turn_target","Turn run away");
    if (!objectp(spell_object))
        return;
    
    if (target->query_ghost() || target->query_prop(NPC_I_NO_RUN_AWAY))
        return hook_turn_target_immune(spell_object);
    
    if (turn_target_success(spell_object) < 0)
        return hook_turn_target_brave(spell_object);
    
    target = spell_object->query_spell_effect_target();
    caster = spell_object->query_spell_effect_caster();
    panic  = (F_PANIC_WIMP_LEVEL(target->query_stat(SS_DIS)) *
             spell_object->query_spell_effect_power()) / 3960;
    here   = environment(target);
    
    /* Add the panic before all the checks */
    target->add_panic(panic);
        
    if (!sizeof(exits) && !sizeof(exits = here->query_exit_cmds()))
        return hook_turn_target_stay(spell_object);
    
    if (!pointerp(exit = exits[random(sizeof(exits))]))
        exit = ({ exit }) - ({ 0 });
    
    if (!sizeof(exit))
        return hook_turn_target_stay(spell_object);
           
    m_out = target->query_m_out();
    target->set_m_out("panics and flees");
    m_in = target->query_m_in();
    target->set_m_in("rushes in, panicky");
    
    foreach(string cmd: exit)
    {
        if (member_array(cmd, environment(target)->query_exit_cmds()) < 0)
            continue;
        
        if (!target->command(cmd))
            break;
    }
    
    target->set_m_out(m_out);
    target->set_m_in(m_in);
    
    if (here != environment(target))
        return hook_turn_target_flee(spell_object);
    
    return hook_turn_target_stay(spell_object);
} /* turn_run_away */

/*
 * Function name:   validate_turn_target_effect
 * Description:     Determines if the fear is situationally successful.
 * Arguments:       (object) spell_object - the spell object in question
 *                  (string *) path - optional path to force
 * Returns:         (status) 1: Successful
 *                           0: Failure
 */
varargs status
validate_turn_target_effect(object spell_object, string *path)
{
    send_debug_message("turn_target","Validate");
    object  caster = spell_object->query_spell_effect_caster(),
            target = spell_object->query_spell_effect_target();
    
    if (Visual_turn_target && !CAN_SEE(target, caster))
    {
        hook_turn_target_blind(spell_object);
        return 0;
    }
    
    send_debug_message("turn_target","validate fear..");
    target->set_aura_alarm(spell_object, 0.5, 0.0,
            &turn_run_away(spell_object, path));
            
    return 1;
} /* validate_turn_target_effect */

/*
 * Function name:   meet_living
 * Description:     Tells us of new living entities in our vicinity.
 * Arguments:       (object) spell_object - The spell object
 *                  (object) met - The living met in the room
 *                  (object) affected - The one affected by the shadow
 * Returns:         Nothing
 */
public void
meet_living(object spell_object, object met, object affected)
{
    send_debug_message("turn_target","Meet Living");
    if (spell_object->query_spell_effect_caster() == met)
        validate_turn_target_effect(spell_object);
} /* meet_living */

/*
 * Function name:   hook_turn_target_stay
 * Description:     A hook triggered after the target failed to flee.
 * Arguments:       (object) spell_object - The spell object
 * Returns:         Nothing
 */
public void
hook_turn_target_brave(object spell_object)
{
    send_debug_message("turn_target","Brave");
    object  caster = spell_object->query_spell_effect_caster(),
            target = spell_object->query_spell_effect_target();
    
    target->catch_tell("You quell the urge to flee.\n");
    
    caster->catch_tell(target->query_The_name(caster) + " quells the urge to "
    + "flee.\n");
    
    tell_room(environment(target), QCTNAME(target) + " quells the urge to flee "
    + "from " + QTNAME(caster) + ".\n", (({caster, target})));
} /* hook_turn_target_stay */

/*
 * Function name:   hook_turn_target_stay
 * Description:     A hook triggered after the target failed to flee.
 * Arguments:       (object) spell_object - The spell object
 * Returns:         Nothing
 */
public void
hook_turn_target_stay(object spell_object)
{
    send_debug_message("turn_target","Stay");
    object  caster = spell_object->query_spell_effect_caster(),
            target = spell_object->query_spell_effect_target();
    
    target->catch_tell("You try to run away in fear of "
    + caster->query_the_name(target) + ", but find no place to run!\n");
    
    caster->catch_tell(target->query_The_name(caster) + " looks deathly "
    + "afraid of you, but finds nowhere to run.\n");
    
    tell_room(environment(target), QCTNAME(target) + " looks deathly "
    + "afraid of " + QTNAME(caster) + ", but finds nowhere to run.\n",
    (({caster, target})));
    
} /* hook_turn_target_stay */

/*
 * Function name:   hook_turn_target_flee
 * Description:     A hook triggered after the target flees.
 * Arguments:       (object) spell_object - The spell object
 * Returns:         Nothing
 */
public void
hook_turn_target_flee(object spell_object)
{
    send_debug_message("turn_target","Flee");
    object  caster = spell_object->query_spell_effect_caster(),
            target = spell_object->query_spell_effect_target();
    
    target->catch_tell("You run away in terror from "
    + caster->query_the_name(target) + "!\n");
    /*
    caster->catch_tell(target->query_The_name(caster) + " looks at you in "
    + "terror, and runs away!\n");
    
    tell_room(environment(target), QCTNAME(target) + " looks at "
    + QTNAME(caster) + " in terror, and runs away!\n", (({caster, target})));
    */  
} /* hook_turn_target_flee */

/*
 * Function name:   hook_turn_target_immune
 * Description:     A hook triggered if the target is immune to fear.
 * Arguments:       (object) spell_object - The spell object
 * Returns:         Nothing
 */
public void
hook_turn_target_immune(object spell_object)
{
    send_debug_message("turn_target","Immune");
} /* hook_turn_target_immune */

/*
 * Function name:   hook_turn_target_blind
 * Description:     A hook triggered after the target flees.
 * Arguments:       (object) spell_object - The spell object
 * Returns:         Nothing
 */
public void
hook_turn_target_blind(object spell_object)
{
    send_debug_message("turn_target","Cant see");
} /* hook_turn_target_blind */

/*
 * Function name:   hook_spell_effect_started
 * Description:     Override this to customize the message when this spell
 *                  effect is added to th target.
 * Arguments:       (object) spell_object - The spell object
 * Returns:         Nothing
 */
public void
hook_spell_effect_started(object spell_object)
{
    send_debug_message("turn_target","Started");
    object  target = spell_object->query_spell_effect_target();
    
    mapping input = target->query_aura_input(spell_object)["paths"][target];
    
    validate_turn_target_effect(spell_object, resolve_path(input));
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
    send_debug_message("turn_target","Ended");
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
    send_debug_message("turn_target","Warn Fading");
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
    send_debug_message("turn_target","Not Maintained");
} /* hook_spell_effect_not_maintained */
