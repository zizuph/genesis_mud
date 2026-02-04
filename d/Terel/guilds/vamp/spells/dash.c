/*
 *
 *  Dash
 *
 *  For spell effect description, see doc/dash.txt
 *
 *  Created May 2008, by Novo
 *  Modifications:
 *    October 2009 - Changed argument list for config_spell since base
 *                   spell.c was changed. - Petros
 */

#pragma strict_types

#include "../guild.h"

inherit SPELL_DIR+"blood_spell";

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <std.h>

#define STD_DIRECTIONS ([ "w" : "west", \
                          "nw" : "northwest", \
                          "n"  : "north", \
                          "ne" : "northeast", \
                          "e" : "east", \
                          "se" : "southeast", \
                          "s" : "south", \
                          "sw" : "southwest", \
                          "d" : "down", \
                          "u" : "up" ])
#define COOLDOWN_TIME     10
#define DASH_PROP         "_live_o_action_last_dash"

public mixed * target_direction(object actor, string str);


public void
config_spell()
{
    ::config_spell();

    set_spell_name("dash");
    set_spell_desc("Travel quickly between rooms");
    set_spell_time(1);
    set_ability_visual(1);
    set_ability_stationary(1);
    set_spell_target(target_direction);
    set_ability_target_verify(0);
    set_ability_no_stun(0);
    set_ability_resist(0);
    set_ability_vocal(0);
    
    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR, 10);
    set_spell_form(SS_FORM_ILLUSION, 10);

    set_blood_cost(10);
    set_min_guild_stat(45);    
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
    if (actor->query_encumberance_weight()>75)
    {
        write("You are too encumbered to move quickly.\n");
        return 0;
    }
    if (actor->query_mist() && !execute)
    {
        write("You are not ready to dash.\n");
        return 0;
    }

    /*
     * A cooldown is being applied for dash. February 2009.
     * Rationale:
     *  A cooldown will be applied to the Dash ability so that it cannot be
     *  rapid cast to guarantee escape. We want Vampires to be hard to be
     *  hard to catch, but not impossible. The duration of the cooldown will
     *  be around 10 seconds.
     */
    if (actor->query_prop(DASH_PROP) + COOLDOWN_TIME >= time())
    {
        write("You are not ready to dash.\n");
        return 0;
    }                

    return ::check_valid_action(actor,targets,arg,execute);
}

public void unset_mist(object actor)
{
    actor->unset_mist();
}


public void
resolve_spell(object actor, mixed * targets, int *resist, int result)
{
    object prior_room=environment(actor);
    
    mixed * watchers=WATCHERS(actor);

    actor->add_prop(LIVE_I_NO_FOOTPRINTS,1);
    
    setuid();
    seteuid(getuid());

    actor->set_no_show();
    actor->add_prop(OBJ_I_INVIS,actor->query_prop(OBJ_I_INVIS)+100);
    actor->command(targets[0][1]);    
    actor->add_prop(OBJ_I_INVIS,actor->query_prop(OBJ_I_INVIS)-100);
    actor->unset_no_show();
    actor->set_no_show_composite(0);
    
    actor->remove_prop(LIVE_I_NO_FOOTPRINTS);
    
    if (environment(actor)!=prior_room)
    {
        watchers->catch_msg("The roiling mist dissipates " +
        "quickly into nothing.\n");
        watchers=filter(watchers,&->query_vampire());
        actor->catch_msg("You reach your destination.\n");
        watchers->catch_msg("Your preternatural senses tell you that "
        + QTNAME(actor) + " has gone " +targets[0][1]+".\n");

        watchers=WATCHERS(actor);
        watchers->catch_msg("A roiling cloud of mist forms from "+
        "nothingness.\n");
    }
    else
    {
        actor->catch_msg("Your attempt to leave fails.\n");
    }
    
    // Setting property for cooldown. See check_valid_action for
    // more details.
    actor->add_prop(DASH_PROP, time());
}


public mixed * target_direction(object actor, string str)
{
    if (!strlen(str))
    {
        write("Dash where?\n");
        return ({ });
    }
    
    if (STD_DIRECTIONS[str])
    {
        str=STD_DIRECTIONS[str];
    }

    // Get all the normal exits
    string * names =({ });
    
    mixed exits=environment(actor)->query_exit();

    for (int i=1;i<sizeof(exits);i+=3)
    {
        names+=({ exits[i] });
    }

    // Now check for door exits
    object * objects = all_inventory(environment(actor));
    foreach (object obj : objects)
    {
        // Check if it's a door
        if (IN_ARRAY("/std/door.c", inherit_list(obj))
            && sizeof(obj->query_pass_command()) > 0)
        {
            names += obj->query_pass_command();
            break;
        }
    }
    if (member_array(str,names)>=0)
    {
        return ({ ({ actor, str }) });
    }
    
    write("Dash where?\n");
    return ({ });
}

public void
concentrate_msg(object actor, mixed * targets, string arg)
{
    actor->catch_tell("You focus your energies inward.\n");
    actor->set_mist();
    set_alarm(2.0,0.0,&unset_mist(actor));
}
