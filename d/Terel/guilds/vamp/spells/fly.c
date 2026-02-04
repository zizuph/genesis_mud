/*
 *
 *  Fly
 *
 *  For spell effect description, see doc/fly.txt
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
#include <math.h>


public void
config_spell()
{
    ::config_spell();

    set_spell_name("fly");
    set_spell_desc("Travel between rooms using flight");


    set_spell_time(40);
    set_ability_visual(1);
    set_ability_stationary(1);
    set_spell_target(target_actor);
    set_ability_target_verify(0);
    set_ability_no_stun(1);
    set_ability_resist(0);
    set_ability_vocal(1);
    set_ability_peaceful(1); // Added February 2009, see check_valid_action
    
    set_spell_mana(96);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR, 60);
    set_spell_form(SS_FORM_CONJURATION, 60);

    set_blood_cost(26);
    
    set_min_guild_stat(150);
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
    
    /*
     * New Check Added February 2009 by Balance Team
     * Rationale:
     *  Fly will be changed so that it cannot be case while in combat. 
     *  This is something that will be enforced globally - no combat 
     *  ports.
     */
    if (!actor->query_relaxed_from_combat())
    {
        actor->catch_tell("You need to calm down from the excitement "
            + "of combat before flying.\n");
        return 0;
    }    
    return ::check_valid_action(actor,targets,arg,execute);
}

public void
resolve_spell(object actor, object *targets, int *resist, int result)
{
    
    object aircont=clone_object(ROOM_DIR+"air");
    
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

