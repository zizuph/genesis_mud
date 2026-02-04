/*
 *
 *  Meld
 *
 *  For effect description, see doc/abilities.txt
 *
 *  Created May 2008, by Novo
 *
 * Modifications:
 *  October 2009 - Relaxed the restriction for combat activity to PvP
 *                 only. We check the enemy list. If there are no players,
 *                 we will allow it. (Petros)
 */

#pragma strict_types

#include "../defs.h"

inherit CORELIB_DIR+"timed_ability";

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <std.h>
#include <math.h>

#define FATIGUE_COST    10


public void config_ability()
{
    ::config_ability();

    set_ability_name("meld");
    set_ability_time(5);

    set_ability_stationary(1);
    set_ability_peaceful(1);
    set_ability_offensive(0);
    
    //Vocal is 0, since mist form blocks noise.  This is
    //explicitly checked in check_valid_action instead.
    set_ability_vocal(0);
    set_ability_visual(0);
    set_ability_no_stun(0);
    
    set_ability_target(target_actor);


}

/*
 * Function name: check_valid_action
 * Description:   Perform ability-specific checks
 * Arguments:     1. (object) The actor
 *                2. (mixed *) The targets
 *                3. (string) Arguments passed to the command
 *                4. (int) Actual spell execution
 * Returns:       (int) 1 if we can continue, 0 if failure
 */
static int check_valid_action(object actor,mixed * targets,string arg,int 
                                execute = 0)
{
    if (environment(actor)->query_prop(ROOM_I_INSIDE))
    {
    	write("You can't seem to penetrate the surface.\n");
        return 0;
    }
    if (MASTER_OB(environment(actor))==ROOM_DIR+"air")
    {
        write("Your feet must be on the ground to meld.\n");
        return 0;
    }
    if (actor->query_mist() && !execute)
    {
        write("You are not ready to meld.\n");
        return 0;
    }
    if (actor->query_fatigue()<FATIGUE_COST && !execute)
    {
        write("You are too tired to do that.\n");
        return 0;
    }
    mixed why = actor->query_prop(LIVE_M_MOUTH_BLOCKED);
    if (!execute && why)
    {
        hook_cannot_speak_fail(stringp(why) ? why : 0);
        return 0;
    }
    
    // We allow melding if there is no player fighting going on.
    if (actor->query_vampire_in_pvp() && !actor->query_relaxed_from_combat())
    {
        write("You are still too active from combat to meld.\n");
        return 0;
    }

    return ::check_valid_action(actor,targets,arg,execute);
}

public void unset_mist(object actor)
{
    actor->unset_mist();
}

static void resolve_ability(object actor, mixed * items, 
            mixed * targets, int * resist, mixed * results)
{
    setuid();
    seteuid(getuid());
    object meldcont=clone_object(ROOM_DIR+"meld_cont");
    
    if (objectp(meldcont))
    {
        write("Your body sinks deep into the earth.\n");
        meldcont->move(environment(actor),1);
        actor->move_living("X",meldcont,1,1);
    }
}

static void ability_msg(object actor,mixed * targets,string arg)
{
    actor->catch_tell("You focus your energies inward.\n");
    actor->add_fatigue(-FATIGUE_COST);
    actor->set_mist();
    set_alarm(7.0,0.0,&unset_mist(actor));
}

