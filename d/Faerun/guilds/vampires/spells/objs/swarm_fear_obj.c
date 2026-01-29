/*
 * /d/Faerun/guilds/vampires/spells/objs/swarm_fear_obj.c
 *
 *
 * Coded by Nerull, 2021
 *
 */
 
inherit "std/object";

#include "../../guild.h";
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <filter_funs.h>

#define IMMUNITYTIMER  "_swarm_immunitytimer"

void
remove_me()
{
    environment(this_object())->remove_prop(IMMUNITYTIMER);
    remove_object();
    
    return;
}

void
stop_panic()
{
    environment(this_object())->add_prop(IMMUNITYTIMER, 1);
    
    environment(this_object())->catch_msg("The swarm of bloodthirsty bats "
    +"suddenly flies away!\nYou regain your sense and composure.\n");
}

void
panic_me()
{
    if (environment(this_object())->query_prop(IMMUNITYTIMER) == 1)
    {
        return;
    }
    
    environment(this_object())->catch_msg("Your legs runs away with you while "
    +"you are in desperation clawing your way through the swarm of "
    +"bloodthirsty bats that is busy cutting, biting and scratching "
    +"you everywhere while blocking your sight!\n");
    
    environment(this_object())->command("scream");
    environment(this_object())->run_away();
}


/*
 * Function name: create_monster()
 * Description  : Sets up our monster.
 */
nomask void create_object()
{
    seteuid(getuid());

    set_name("swarm_fear_obj");
    
    add_prop(OBJ_I_INVIS, 100);
    add_prop(OBJ_I_NO_DROP, 1);
    
    set_no_show();

    set_short("swarm_obj");
    set_long("swarm_obj.\n");

    add_prop(CONT_I_WEIGHT, 1);
    add_prop(CONT_I_HEIGHT, 1);
    
    set_alarm(20.0, 0.0, &remove_me());
    set_alarm(1.0, 1.0, &panic_me());
    set_alarm(10.0, 0.0, &stop_panic());
}
