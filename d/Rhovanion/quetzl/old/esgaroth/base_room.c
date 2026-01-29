#pragma strict_types
 
#include "esg_defs.h"
 
inherit ROOM;
 
#include <tasks.h>
#include <macros.h>
#include <composite.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <wa_types.h>
#include "wd_support.c"
 
#define FIGHT_NOISE 200
#define SS_RANGER_HEAR 118209
 
/****************** Global Variables *************************************/
 
static string *directions = ({ "north", "northeast", "east", "southeast",
    "south", "southwest", "west", "northwest" }),
    *vary_names = ({ });
 
static mixed lower_floor = 0,
             lower_floor_noise = 0,
             base_desc = "",
             vary_descs = ({ });
 
static mapping exit_noises = ([]);
 
static function *vary_funcs = ({});
 
static int use_varies = 0;
 
public string
query_time_of_day()
{
    reset_euid();
    return CLOCK->query_time_of_day();
}

public string
query_weather()
{
    reset_euid();
    return LOCAL_WEATHER->query_weather();
}
/****************** Multi Level City! *************************************/
 
/*
 * Function name: set_lower_floor
 * Description:   set the filename of the room below this one.
 * Arguments:     arg - the filename
 */
public void
set_lower_floor(mixed arg)
{
    lower_floor = arg;
}
 
/*
 * Function name: query_lower_floor
 * Description:   get the room below this one.
 * Returns:       the room.
 */
public mixed
query_lower_floor()
{
    return lower_floor;
}
 
/*
 * Function name: set_lower_floor_noise
 * Description:   set the difficulty of making noise that is hear below.
 * Arguments:     noise - the difficulty -- higher means it is harder to
 *                        hear movement from below.
 */
public void
set_lower_floor_noise(mixed noise)
{
    lower_floor_noise = noise;
}
 
/*********** Walking Around Can be Noisy ***********************************/
 
/*
 * Function name: set_exit_noise
 * Description:   set the relative difficulty of hearing movement in dir.
 * Arguments:     dir - the direction of difficulty.
 *                noise - the noise value (or VBFC)
 */
public void
set_exit_noise(string dir, mixed noise)
{
    exit_noises[dir] = noise;
}
 
/*
 * Function name: filter_hear
 * Description:   Decide if we hear someone walking around.
 *                Factor in: ob - intelligence and awareness
 *                walker - dex, sneak, and (-) encumberance
 * Arguments:     ob - the object which wants to hear
 *                walker - the noisy oaf
 *                extra_diff - any extra difficulty (or easiness)
 * Returns:       1 if ob hears walker
 */
static int
filter_hear(object ob, object walker, int extra_diff = 0)
{
    if (!living(ob))
        return 0;
 
    return ob->resolve_task(TASK_ROUTINE + extra_diff, ({ SKILL_WEIGHT, 200,
        SKILL_MAX, SS_AWARENESS, SKILL_WEIGHT, 150, SS_RANGER_HEAR,
        SKILL_END, TS_INT }), walker,
        ({ SKILL_WEIGHT, 200, SS_SNEAK, TS_DEX })) > 0;
}
 
/*
 * Function name: swap_direction
 * Description:   just a utility function to swap the direction from which
 *                we 'hear' footsteps arrive.
 * Arguments:     arg - the direction
 * Returns:       the opposite direction
 */
static string
swap_direction(string arg)
{
    int i;
    i = member_array(arg, directions);
    if (i == -1)
        return "somewhere";
    return "the " + directions[(i + 4) % 8];
}
 
/*
 * Function name: leave_inv
 * Description:   handle noisiness here.
 * Arguments:     ob - the object moving
 *                to - where it is moving to.
 */
public void
leave_inv(object ob, object to)
{
    mixed a, b;
    string leave_direction;
    int extra_noise;
 
    ::leave_inv(ob, to);
    if (!living(ob) || !to || query_prop(ROOM_I_NO_FOOTSTEP_ECHO))
        return;
 
    leave_direction = ob->query_prop(LIVE_S_LAST_MOVE);
 
    extra_noise = check_call(exit_noises[leave_direction]);
 
    if (sizeof(filter(all_inventory(), objectp @ &->query_attack())))
        extra_noise += FIGHT_NOISE; // Fighting makes noise!
    filter(all_inventory(this_object()) - ({ ob }), 
        &filter_hear(, ob, extra_noise))->catch_msg("You hear the sound of " +
        "footsteps moving " + leave_direction + ".\n");
 
    if (!lower_floor)
        return;
    a = check_call(lower_floor);
    if (!objectp(a))
    {
        b = find_object(a);
        if (!b)
        {
            reset_euid();
            a->load_it();
            b = find_object(a);
            if (!b)
                return;
        }
        a = b;
    }
 
    extra_noise = check_call(lower_floor_noise);
    if (sizeof(filter(all_inventory(a), objectp @ &->query_attack())))
        extra_noise += FIGHT_NOISE;
    filter(all_inventory(a) - ({ ob }), &filter_hear(, ob, extra_noise))->
        catch_msg("You hear someone moving above you.\n");
    return;
}
 
/*
 * Function name: enter_inv
 * Description:   more noisiness!
 */
public void
enter_inv(object ob, object from)
{
    mixed a, b;
    string enter_direction;
    int extra_noise;
 
    ::enter_inv(ob, from);
    if (!living(ob) || !from || query_prop(ROOM_I_NO_FOOTSTEP_ECHO))
        return;
 
    enter_direction = swap_direction(ob->query_prop(LIVE_S_LAST_MOVE));
    extra_noise = check_call(exit_noises[enter_direction]);
    if (sizeof(filter(all_inventory(), objectp @ &->query_attack())))
        extra_noise += FIGHT_NOISE;
    filter(all_inventory() - ({ ob }), &filter_hear(, ob, extra_noise))->
        catch_msg("You hear the sound of footsteps arriving from the " +
            enter_direction + ".\n");
 
    if (!lower_floor)
        return;
    a = check_call(lower_floor);
    if (!objectp(a))
    {
        b = find_object(a);
        if (!b)
        {
            reset_euid();
            a->load_it();
            b = find_object(a);
            if (!b)
                return;
        }
        a = b;
    }
 
    extra_noise = check_call(lower_floor_noise);
    if (sizeof(filter(all_inventory(a), objectp @ &->query_attack())))
        extra_noise += FIGHT_NOISE;
    filter(all_inventory(a) - ({ ob }), &filter_hear(, ob, extra_noise))->
        catch_msg("You hear someone moving above you.\n");
    return;
}
 
/********************** Do Some Time Stuff Here *****************************/
 
/*
 * Function name: set_vary_desc
 * Description:   Set a description which might vary on the value of a function
 * Arguments:     time_name - the string which will be returned by the function
 *                desc - a string or vbfc with a description
 */
public void
set_vary_desc(string func_name, string time_name, mixed desc)
{
    int i;
    i = member_array(func_name, vary_names);
    if (i == -1)
    {
        vary_names += ({ func_name });
        vary_descs += ({ ([ time_name : desc ]) });
        vary_funcs += ({ 0 });
    }
    else
        vary_descs[i][time_name] = desc;
}
 
/*
 * Function name: set_base_desc
 * Description:   set the base description of the room
 * Arguments:     desc - the description
 */
public void
set_base_desc(mixed desc)
{
    use_varies = 1;
    base_desc = desc;
}
 
/*
 * Function name: set_vary_func
 * Description:   set a function to use in the long description
 * Arguments:     name - an index name for the function
 *                f - the function to call
 */
public void
set_vary_func(string func_name, function f)
{
    int i;
    use_varies = 1;
    i = member_array(func_name, vary_names);
    if (i == -1)
    {
        vary_names += ({ func_name });
        vary_funcs += ({ f });
        vary_descs += ({ ([]) });
    }
    else
        vary_funcs[i] = f;
}
 
/*
 * Function name: long
 * Description:   set obj_long to what it ought to be, then return ::long
 */
public varargs string
long(string obj, object for_obj)
{
    string tmp, *f_rets;
    int i;
    function f;
    if (!use_varies || strlen(obj))
        return ::long(obj, for_obj);
 
    tmp = check_call(base_desc);
    obj_long = (tmp ? tmp : "");
 
    i = sizeof(vary_funcs);
    f_rets = allocate(i);
    while (i--)
    {
        f = vary_funcs[i];
        if (!f)
            continue;
        f_rets[i] = check_call(vary_descs[i][f()]);
    }
    f_rets -= ({ 0 });
 
    if (sizeof(f_rets))
        obj_long += (strlen(obj_long) ? " " : "") + implode(f_rets, " ");
    obj_long += "\n";
 
    return ::long(obj, for_obj);
}
 
/*
 * Function name: query_exit_cmds
 * Description:   a little trick to let people 'sneak' in fake exits
 * Returns:       the exit commands of the room
 */
public string *
query_exit_cmds()
{
    if (query_verb() != "sneak")
        return ::query_exit_cmds();
    return ::query_exit_cmds() + map(fake_exits, check_call);
}

public string
query_weather_region()
{
    return "Esgaroth";
}

public string
same_dir(int j = 1)
{
    int i;
    string *f;
    f = explode(file_name(this_object()), "/");
    i = sizeof(f);
    f = slice_array(f, 0, i - j - 1);
    return implode(f, "/") + "/";
}
