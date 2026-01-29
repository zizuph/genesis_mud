/*
 * pMirage
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/spells/std_pot_spell";

#include "/d/Ansalon/common/defs.h"
#include "../spells.h"
#include "../guild.h"
#include <macros.h>
#include <tasks.h>
#include <filter_funs.h>

#define PMIRAGE_DIRALIAS    ([ "e" : "east", "w" : "west",          \
    "n" : "north", "s" : "south", "sw" : "southwest",               \
    "se" : "southeast", "nw" : "northwest", "ne" : "northeast" ])

mapping pMirageDirs = ([]);

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 6;
}

public object *
pmirage_target(object caster, string str)
{
    string *dirs;
    int i;
    object *to;
    
    if (!stringp(str))
    {
        caster->catch_tell("You need to specify a direction for the mirage.\n");
        return ({ });
    }

    dirs = E(caster)->query_exit_cmds();
    if ((i = member_array(str, dirs)) < 0)
    {
        str = PMIRAGE_DIRALIAS[str];
        if ((i = member_array(str, dirs)) < 0)
        {
    	    caster->catch_tell("There is no exit in that direction.\n");
    	    return ({ });
        }
    }

//    find_player("stralle")->catch_tell("#pm# i: " + i + "\n");

    pMirageDirs[caster->query_real_name()] = dirs[i];
    to = caster->query_team_others();
    
    return FILTER_LIVE(all_inventory(environment(caster))) - ({ caster }) -
        to;
}

public void
concentrate_msg(object caster, object *targets, string arg)
{
    object old_tp = TP;
    
    set_this_player(caster);
    caster->catch_tell("You begin a prayer to spin an illusion.\n");
    all_msg(QCTNAME(caster) + " starts to chant a prayer.\n", caster);
    set_this_player(old_tp);
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_spell( object caster, object *targets, int *resist, int result )
{
    int i;

    caster->catch_tell("You form an illusion from the air, a " +
        "mirage of yourself leaving " +
        pMirageDirs[caster->query_real_name()] + ".\n");

    for (i=0; i<sizeof(targets); i++)
    {
    	object t = targets[i];

    	// Check to make sure the target is still present, otherwise
    	// skip that particular target.

    	if (environment(t) != environment(caster))
    	    continue;

    	// The resist array is filled with each target's resistance
    	// to illusion. The greater resistance to illusion, the less
    	// chance they are fooled.

    	if (resist[i] > random(100))
    	{
    	    // Make it look as if the player has really left, stopping
    	    // fights and sending hunting messages where appropriate.
    	    
    	    if (member_array(t, caster->query_enemy(-1)) >= 0)
    	    {
    	    	t->catch_tell("You are now hunting " +
    	    	    caster->query_the_name(t) + ".\n");
    	    	caster->stop_fight(t);
    	    }
    	    if (interactive(t))
    	        t->catch_tell(caster->query_The_name(t) + " " +
    	            caster->query_m_out() + " " +
    	            pMirageDirs[caster->query_real_name()] + ".\n");

    	    if (member_array(caster, t->query_enemy(-1)) >= 0)
    	        t->stop_fight(caster);
    	}
    	else
    	{
    	    // Give a message to those that resist the illusion, so they
    	    // know what is going on. The caster does not know they saw
    	    // through the illusion, so the caster will stop fighting anyway.
    	    
    	    t->catch_tell("You see a weak illusion of " +
    	        caster->query_the_name(t) + " leaving " +
    	        pMirageDirs[caster->query_real_name()] +
    	        ", but it does not fool you.\n");
    	    caster->stop_fight(t);
    	}
    }
}

/*
 * Function name: create_spell_pmirage
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       0/1 - spell configured/not configured (cannot be cast)
 */
public varargs int
config_spell(object caster, object *targets, string argument)
{
    set_spell_name("pmirage");
    set_spell_desc("Create the illusion of yourself leaving the room");

    set_spell_element(SS_ELEMENT_AIR, 45);
    set_spell_form(SS_FORM_CONJURATION,  20);
    set_spell_stationary(1);
    set_spell_target(pmirage_target);

    set_spell_time(3);
    set_spell_mana(50);

#ifndef NO_INGREDIENTS
    set_spell_ingredients(({"locoweed"}));
#endif

    set_spell_task(TASK_ROUTINE);

    set_spell_resist(spell_resist_illusion);

    set_spell_visual(0);

    return 0;
}
