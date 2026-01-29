/* /d/Faerun/guilds/vampires/specials/vampfly.c
 *
 * Nerull 2021
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


public void config_ability()
{
    ::config_ability();

    set_ability_name("vfly");
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
    
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/bloodletter.c");
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/trucidate.c");
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/execute.c");
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/mesmerize.c");
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/strangulate.c");
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/ethereal.c");
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
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_4(actor->query_name()) == 0)
    {
        write("What?\n");
        return 0;
    }
    
    if (actor->query_ethereal() == 1)
    {
        write("This ability is not available while you "
        +"are in the ethereal realm.\n");
        return 0;
    }
    
    //Avenir is indoors, but has no roof to constrain travel, so we 
    //check for the allow_steed to determine if we can fly from here.
    if (environment(actor)->query_prop(ROOM_I_INSIDE)
        && !(environment(actor)->query_prop(ROOM_I_ALLOW_STEED)))
    {
        write("You cannot fly while indoors.\n");
        return 0;
    }
    
    if (MASTER_OB(environment(actor))==ROOM_DIR+"air")
    {
        write("You are already flying.\n");
        return 0;
    }
    
    if (!actor->query_relaxed_from_combat())
    {
        actor->catch_tell("You need to calm down from the excitement "
            + "of combat before flying.\n");
        return 0;
    }    
    return ::check_valid_action(actor,targets,arg,execute);
}


static void resolve_ability(object actor, mixed * items, 
            mixed * targets, int * resist, mixed * results)
{
    setuid();
    seteuid(getuid());
    
    object aircont=clone_object(VAMPIRES_GUILD_DIR + "rooms/air");
    
    if (objectp(aircont))
    {
        write("You concentrate deeply, channeling your inner will to "+
        "lift your body up. Something deep within you responds, and "+
        "your feet rise up slowly from the ground, levitating a few "+
        "just off the ground. Your mind in control over gravity itself, "+
        "you travel higher and higher, until you are high above the "+
        "solid earth below.\n");
        
        object * watchers=WATCHERS(actor);

        watchers->catch_msg(QCTNAME(actor) + " starts to levitate a "+
        "few feet off the ground, literally leaving the solid earth. "+
        capitalize(PRO(actor)) + " hovers for a moment, before lifting "+
        "higher and higher until "+PRO(actor)+ " is up and out of "+
        "sight!\n");

        aircont->set_start_location(actor);
        actor->move_living("M",aircont,1,0);
    }
}


static void ability_msg(object actor,mixed * targets,string arg)
{
    actor->catch_tell("You focus your energies inward.\n");
}

