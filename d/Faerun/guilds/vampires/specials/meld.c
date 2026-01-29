/*
 *
 *  
 *
 * Nerull, 2021
 */

inherit "/d/Genesis/specials/timed_ability";

#include "../guild.h"


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

public void
hook_combat_fail(object *combatants,object ability)
{
    int gauge2;
    gauge2 = VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name());
    
    if (gauge2 < 150)
    {
        write("What?\n");
        return;
    }
    
    write("You cannot "+ability->short()+" while in combat with " + 
        FO_COMPOSITE_ALL_LIVE(combatants, this_player()) + ".\n");
}



public void config_ability()
{
    ::config_ability();

    set_ability_name("vmeld");
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
    int gauge;
    gauge = VAMPIRES_MAPPINGS->query_vampires_gauge(actor->query_name());
    
    if (gauge < 150)
    {
        write("What?\n");
        return 0;
    }
    
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
    
    // We allow melding if there is no player fighting going on.
    if (!actor->query_relaxed_from_combat())
    {
        write("You are still too active from combat to meld.\n");
        return 0;
    }

    return ::check_valid_action(actor,targets,arg,execute);
}


static void resolve_ability(object actor, mixed * items, 
            mixed * targets, int * resist, mixed * results)
{
    setuid();
    seteuid(getuid());
    
    object meldcont=clone_object(VAMPIRES_GUILD_DIR + "rooms/meld_cont");
    
    if (objectp(meldcont))
    {
        write("Your body sinks deep into the earth.\n");
        
         tell_room(environment(actor), QCTNAME(actor)
            + " melds into the ground!\n", actor);
        
        meldcont->move(environment(actor),1);
        
        actor->move_living("M",meldcont,1,1);    
    }
}


static void ability_msg(object actor,mixed * targets,string arg)
{
    actor->catch_tell("You focus your energies inward.\n");
}


public void
hook_special_complete()
{
    write("\n");
}

