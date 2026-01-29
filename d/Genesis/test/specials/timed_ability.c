/*
 * Timed special - support for non-spell abilities that need explicit
 * alarms called out.  An alarm is added at query_ability_time()/2 +
 * random (query_ability_time()/2) + random (query_ability_time()/2)
 * seconds.  If the ability_time is 0, the effect is immediate, and
 * quickness is applied to the special if applicable.
 *
 *
 * set_ability_hasted(int)
 *     Set whether LIVE_I_QUICKNESS affects the speed of this ability
 *     Default: 1
 *
 *
 */

#include "defs.h"

inherit ABILITY_LIB;

#include <stdproperties.h>
#include <ss_types.h>
#include <comb_mag.h>
#include <macros.h>
#include <formulas.h>


static int Ability_haste;    //Is this ability affected by haste?


public void set_ability_hasted(int hasted)
{
    Ability_haste=hasted;
}

public int query_ability_hasted()
{
    return Ability_haste;
}

static nomask void prepare_ability(object actor,mixed * targets,string arg)
{
    object tp=this_player();
    set_this_player(actor);
    execute_ability(actor,targets,arg);
    set_this_player(tp);
}

/*
 * Function:    notify_prep_time
 * Description: This is a hook that abilities can use to know how long
 *              the prep time is before execution. A common usage of
 *              this may be to provide interim messages for long
 *              delays.
 * Arguments:   prep_time - the time before preparation and execution
 * Returns:     nothing
 */
static void
notify_prep_time(float prep_time, object actor, mixed * targets)
{
}

static nomask
void schedule_ability(object actor,mixed * targets,string arg)
{
    float prep_factor, prep_time;
        
    if (!query_ability_time())
    {
        prepare_ability(actor, targets, arg);
        return;
    }

    // First get the total prep time adjusted by speed
    prep_factor = query_ability_time() 
                  + actor->query_prop(LIVE_I_ATTACK_DELAY);
    if (query_ability_hasted())
    {
        prep_factor = actor->query_speed(prep_factor);
    }
    prep_factor = prep_factor / 2.0;
    prep_time = prep_factor + rnd() * prep_factor + rnd() * prep_factor;
    
    // Added so that abilities have the knowledge of how long their
    // prep time is going to be. That way, they can customize special
    // messages in the interim.
    notify_prep_time(prep_time, actor, targets);
    
    set_alarm(prep_time, 0.0, &prepare_ability(actor, targets, arg));
}

public void
default_config_ability()
{
    ::default_config_ability();
    set_ability_hasted(1);
    set_ability_time(15);
}

public int
stop_ability(object player)
{
    if (objectp(player))
    {
        mixed *calls = get_all_alarms();
        mixed *args;
        int i;

        for (i = 0; i < sizeof(calls); i++)
        {
            if (calls[i][1] == "prepare_ability")
            {
                args = calls[i][4];
                if (args[0] == player)
                {
                    remove_alarm(calls[i][0]);
                    set_ability_pending(player,0,0);
                    hook_stopped_ability(this_object(),player);
                    return 1;
                }
            }
        }
    }
    return 0;
}

public int
query_ability_active(object player)
{
    if (objectp(player))
    {
        mixed *calls = get_all_alarms();
        mixed *args;
        int i;

        for (i = 0; i < sizeof(calls); i++)
        {
            if (calls[i][1] == "prepare_ability")
            {
                args = calls[i][4];
                if (args[0] == player)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}