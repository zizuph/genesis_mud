/*
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


public void config_ability()
{
    ::config_ability();

    set_ability_name("ethereal");
    set_ability_time(30);

    set_ability_stationary(1);
    set_ability_peaceful(1);
    set_ability_offensive(0);
    
    //Vocal is 0, since mist form blocks noise.  This is
    //explicitly checked in check_valid_action instead.
    set_ability_vocal(0);
    set_ability_visual(0);
    set_ability_no_stun(0);
    
    set_ability_target(target_actor);
    
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/bloodletter.c");
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/trucidate.c");
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/execute.c");
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/mesmerize.c");
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/strangulate.c");
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/vampfly.c");
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
    int valid = VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(actor->query_name());
    
    
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(actor->query_name()) != 1 
    && VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(actor->query_name()) != 3)
    {
        write("What?\n");
        return 0;
    }
 
    if (actor->query_ethereal() == 1)
    {
    	write("You are already in the ethereal realm.\n");
        return 0;
    }
    
    if (actor->query_prop(IAM_OBFUSCATED) == 1)
    {
        write("This ability is not available while you "
        +"are obfuscated.\n");
        return 0;
    }
    
    // We allow ethereal if there is no player fighting going on.
    if (!actor->query_relaxed_from_combat())
    {
        write("You are still too active from combat to use this ability.\n");
        return 0;
    }

    return ::check_valid_action(actor,targets,arg,execute);
}


static void resolve_ability(object actor, mixed * items, 
            mixed * targets, int * resist, mixed * results)
{
    setuid();
    seteuid(getuid());
    
    actor->set_ethereal();   
}


static void ability_msg(object actor,mixed * targets,string arg)
{
    actor->catch_tell("You prepare to enter the ethereal realm.\n");
}

