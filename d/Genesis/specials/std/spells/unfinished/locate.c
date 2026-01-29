/*
 * Filename:    locate.c
 * Description: This a spell that finds the shortest path to a desired area, it
 *              runs until it finds a room matching the perform_path_check or
 *              until the end of the limit if multiple checks is enabled.
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
static int      gPathLimit;
static status   gMultipleChecks;

/* Prototypes */
private mapping locate(object caster, mixed start, object caller,
                            int limit = 1);
public void     resolve_locate_spell(object caster, object *targets, int *resist,
                                   int result, mapping paths);
public int      perform_locate_check(object actor, object target, object room);
public status   query_multiple_checks();
public void     set_multiple_checks(int checks);
public void     set_locate_limit(int limit);
public int      query_locate_limit();

/*
 * Function name:   config_locate_spell
 * Description:     Config function for locate spells. Redefine this in your own
 *                  locate spells to override the defaults.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
config_locate_spell()
{
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_stationary(1);
    set_spell_can_be_renewed(0);
    
    // The size of the radius in which we expand our concentric locating circle
    // Example: 1 - All the rooms that are adjacent to ours.
    //          2 - All the rooms that are adjacent to the rooms in 1.
    //          3 - All the rooms that are adjacent to the rooms in 2.
    //          ... And so on
    set_locate_limit(4);
    // Results in multiple paths
    set_multiple_checks(1);
} /* config_locate_spell */

/*
 * Function name:   query_locate_ingredients
 * Description:     This function defines what components are required for this
 *                  locate spell.
 * Arguments:       (object) caster - The caster in whom we look for ingredients
 * Returns:         (string *) - Array of ingredient strings
 */
public string *
query_locate_ingredients(object caster)
{
    return ({  });
} /* query_locate_ingredients */

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

    set_spell_name("locate");
    set_spell_desc("trace a path to something");
    set_spell_target(spell_target_caster);

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_ingredients(query_locate_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each harm spell should customize these to their specific guild skills.
    set_spell_element(SS_ELEMENT_EARTH, 40);
    set_spell_form(SS_FORM_DIVINATION, 40);
    set_shadow_filename(STD_SPELL_OBJ_DIR + "locate_sh");
        
    // Call the specific configuration that is to be masked.
    config_locate_spell();
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
    mapping paths = ([]);
    
    foreach(object target: targets)
    {
        paths[target] = locate(caster, target, this_object(),
                        query_locate_limit());
    }
    
    spell_input["paths"] = paths;
    
    resolve_locate_spell(caster, targets, resist, result, spell_input);
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
        // The locate spell cannot be cast if it is already in effect
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
 * Function name:   safely_load_master_file
 * Description:     This safely loads the master file if it hasn't already
 *                  been loaded. Otherwise, it just returns the existing
 *                  master file. If the file is not loadable, then it
 *                  simply returns 0
 * Arguments:       (string) filename - Filename of the file to load
 * Returns:         (object) - Loaded master file
 */
public object
safely_load_master_file(string filename)
{
    object master_obj;
    if (!objectp(master_obj = find_object(filename)))
    {
        LOAD_ERR(filename);
        master_obj = find_object(filename);
    }
    
    return master_obj;
} /* safely_load_master_file */

/*
 * Function name:   query_locate_limit
 * Description:     Returns the maximum radius set for locate.
 * Arguments:       None
 * Returns:         (int) - The locate limit
 */
public int
query_locate_limit()
{
    return gPathLimit;
} /* query_locate_limit */

/*
 * Function name:   set_locate_limit
 * Description:     Sets the set locate limit, a radius in which we scan the
 *                  surrounding rooms.
 * Arguments:       (int) - The locate limit
 * Returns:         Nothing
 */
public void
set_locate_limit(int limit)
{
    gPathLimit = limit;
} /* set_locate_limit */

/*
 * Function name:   query_multiple_checks
 * Description:     Checks if the locate should stop at the very first
 *                  successful return of the perform_locate_check.
 * Arguments:       None
 * Returns:         (status) 1 - Continues to look for paths.
 *                  (status) 0 - Stops at the first occurrence.
 */
public status
query_multiple_checks()
{
    return gMultipleChecks;
} /* query_multiple_checks */

/*
 * Function name:   set_multiple_checks
 * Description:     Determines if the locate should stop at the first
 *                  occurrence of the perform_locate_check.
 * Arguments:       (status) 1 - Enable multiple checks
 *                  (status) 0 - Disable multiple checks
 * Returns:         Nothing
 */
public void
set_multiple_checks(int checks)
{
    gMultipleChecks = checks;
} /* set_multiple_checks */

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
public int
perform_locate_check(object actor, object target, object room)
{
    if (!objectp(room) || !room->query_prop(ROOM_I_IS))
        return 0;
    
    if (!room->query_prop(ROOM_I_INSIDE))
        return 0;
    
    return -1;
} /* perform_locate_check */

/*
 * Function name:   locate
 * Description:     Finds the shortest path to reach whatever specified in the
 *                  perform_locate_check.
 * Arguments:       (mixed)     start   - The room to start the path from
 *                  (object)    caller  - The object containing the path check
 * Returns:         (mapping)   pathEnd - Ordered room names along the path
 */
private mapping
locate(object caster, mixed start, object caller, int limit = 1)
{
    mapping pathDir, pathHeap, pathEnd = ([]);
    int     instance, multiple, success;
    string *pathExits, *pathCurrent;
    object  current, next, target;
    
    if (!objectp(caller))
        return ([]);
    
    if (objectp(start))
    {
        if (living(target = start))
            start = environment(target);
        
        start = file_name(start);
    }
    
    if (!safely_load_master_file(start))
        return ([]);
    
    if (m_sizeof(pathHeap) || !mappingp(pathHeap))
        pathHeap = ([]);
    
    pathHeap[start] = ([ "parent" : "", "visited" : "nay" ]);
    pathDir = ([ 0 : ({ start }) ]);
    
    while(m_sizeof(pathDir))
    {
        pathCurrent = pathDir[instance];
        pathDir = m_delete(pathDir, instance);
        
        /* Limit to prevent infinite loop */
        instance++;
        if (instance > limit)
            break;
        
        foreach(string room: pathCurrent)
        {
            /* Room cant be loaded or has no exits */
            if (!objectp(current = safely_load_master_file(room)) ||
                !sizeof(pathExits = current->query_exit_rooms()))
                continue;
         
            /* Desired room found, compiling path and breaking loop */
            if (success = caller->perform_locate_check(caster, target, current))
            {
                if (!pointerp(pathEnd[room]))
                    pathEnd[room] = ({});
            
                string looproom = room;
                
                while(strlen(pathHeap[looproom]["parent"]))
                {
                    pathEnd[room] = ({ pathHeap[looproom]["parent"] })
                                    + pathEnd[room];
                    looproom = pathHeap[looproom]["parent"];
                }
                
                if (!sizeof(pathEnd[room]))
                    pathEnd = m_delete(pathEnd, room);
                
                if (!query_multiple_checks())
                    return pathEnd;
            }
                
            if (success < 0)
                continue;
            
            if (!pointerp(pathDir[instance]))
                pathDir[instance] = ({});
            
            foreach(string pathExit: pathExits)
            {
                if (wildmatch("*\\.c", pathExit))
                    pathExit = explode(pathExit, ".c")[0];
                
                if (member_array(pathExit, m_indexes(pathHeap)) < 0 ||
                    pathHeap[pathExit]["visited"] == "nay")
                {
                    pathHeap[room]["visited"] = "aye";
                    pathHeap[pathExit] = ([ "parent" : room,
                                            "visited" : "aye" ]);
                    pathDir[instance] += ({ pathExit });
                }
            }
        }
    }
    
    return pathEnd;
} /* locate */

/*
 * Function name:   resolve_locate_spell
 * Description:     Called at the beginning of resolve_spell in order to perform
 *                  spell specific actions.
 * Arguments:       Same as resolve_spell
 * Returns:         Nothing
 */
public void
resolve_locate_spell(object caster, object *targets, int *resist, int result,
                   mapping spell_input)
{
} /* resolve_locate_spell */