/*
 *
 *  Flicker
 *
 *  For spell effect description, see doc/flicker.txt
 *
 *  Created May 2008, by Novo
 *  Modifications:
 *    October 2009 - Changed argument list for config_spell since base
 *                   spell.c was changed. - Petros
 */

#include "../defs.h";

inherit SPELL_DIR+"blood_spell";

#include <stdproperties.h>
#include <tasks.h>
#include <ss_types.h>

#define COOLDOWN_TIME       60
#define FLICKER_PROP        "_live_o_action_last_flicker"

public void
config_spell()
{
    ::config_spell();
        
    set_spell_name("flicker");
    set_spell_mana(81);
    set_spell_task(TASK_DIFFICULT);
    set_spell_element(SS_ELEMENT_AIR, 50);
    set_spell_form(SS_FORM_CONJURATION, 40);
    set_blood_cost(2);
    set_min_guild_stat(90);
    
    set_spell_ingredients(({ "topaz" }));
    
    set_spell_resist(spell_resist_basic);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    
    set_spell_target(spell_target_caster);

    set_spell_desc("Draw upon the winds to extinguish light");
    
    set_spell_object(SPELLOBJ_DIR+"flicker_obj");
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
    if (present("_flicker_obj",actor))
    {
        actor->catch_tell("The wind dances strongly as it is, "+
        "and you have no further need to call upon your gift.\n");
        return 0;
    }
    
    if (actor->query_prop(FLICKER_PROP) + COOLDOWN_TIME >= time())
    {
        actor->catch_tell("You find yourself unable to draw upon the "
            + "winds so soon again.\n");
        return 0;
    }
    
    return ::check_valid_action(actor,targets,arg,execute);
}

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    make_spell_effect_object(query_spell_object(), caster, 
        targets,resist,result); 

    /* 
    * Adding a cooldown to Flicker so that it cannot be immediately
    * recast, allowing opponents a chance to see. Flicker, by
    * guaranteeing darkness, is pretty much a stun effect.
    * February 2009.
    * Rationale:
    *   The duration of the flicker spell will be reduced to around 20
    *   seconds or so. Its a great ability, and lovely for the theme, so
    *   we want to keep it. However, in that it reduces parry, defence,
    *   and tohit against the opponents, it renders them practically
    *   helpless against the Vampire, so long as the Vampire has enough
    *   darkness items in their possession to overcome the 1 torch per
    *   10 second relight allowance (which they always seem to.) We
    *   do not want such a powerful game-changer to last the entire
    *   duration of battle (5 minutes, currently.)    
    */
    caster->add_prop(FLICKER_PROP, time());
}

public void
hook_no_ingredients_fail(mixed *ingredients_needed)
{
    write("Without a topaz to channel your energies, you cannot "+
    "create this effect.\n");
}

