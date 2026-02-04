/*
 *
 *  Mesmerize spell
 *
 *  For spell effect description, see doc/mesmerize.txt
 *
 *  Created May 2008, by Novo
 *
 * Modified May 2009 by Petros
 *   - Changed element to match documentation (illusion, not enchantment)
 *   - Changed mana cost and blood cost to match documentation
 *   - Changed check_valid_action to allow stacking by multiple Vampyr 
 * Modified October 2009 by Petros:
 *   - Changed argument list for config_spell since base pell.c was changed
 */

#include "../defs.h";

inherit SPELL_DIR+"blood_spell";

#include <stdproperties.h>
#include <tasks.h>
#include <ss_types.h>
#include <macros.h>

/*
 * Mesmerize now uses the standard stun object. February 2009
 * Rationale:
 *  Mesmerize will be modified to make use of the standard stun
 *  library. When the guild was first coded, this library did not
 *  exist, but now like all guilds, the effect will be centralized at
 *  its core.
 */

public void
config_spell()
{
    ::config_spell();
        
    set_spell_name("mesmerize");
    set_spell_mana(144);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR, 60);
    set_spell_form(SS_FORM_ILLUSION, 60);

    set_blood_cost(18);
    set_min_guild_stat(140);
    
    set_spell_resist(spell_resist_basic);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_visual(0);
    
    set_ability_target(target_one_other_present_living_or_enemy);

    set_spell_desc("Confuse your opponent");
}

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    object mes_obj, enemy;
    
    enemy = targets[0];
    if (resist[0] <= random(100))
    {
        setuid();
        seteuid(getuid());
        
        // Create the stun object for both the caster and the target.
        mes_obj = clone_object(SPELLOBJ_DIR + "mesmerize_obj");
        mes_obj->set_effect_caster(caster);
        mes_obj->set_effect_target(enemy);
        mes_obj->set_defender(enemy);
        mes_obj->move(enemy, 1);
        mes_obj->start();    
        
        mes_obj = clone_object(SPELLOBJ_DIR + "mesmerize_obj");
        mes_obj->set_effect_caster(caster);
        mes_obj->set_effect_target(caster);
        mes_obj->set_defender(enemy);
        mes_obj->move(caster, 1);
        mes_obj->start();
    }
    else
    {
        caster->catch_msg("Try as you might, you cannot penetrate "
            + "the mind of " + QCTNAME(enemy) + ".\n");
    }
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
static int check_valid_action(object actor, mixed * targets,string arg,int 
                                execute = 0)
{
    // Two Vampires can stack their effects, but a single Vampire
    // cannot stack multiple effects. This uses the base stun library,
    // so stacking effects increases the combat aid, and reduces the
    // cooldown times for the stun.
    object * effects;
    
    effects = filter(all_inventory(actor), &->is_mesmerize_object());
    if (sizeof(effects))
    {
        actor->catch_tell("You are already focused on pressing your "
            + "mind into someone and cannot focus on anything else!\n");
        return 0;
    }
    
    return ::check_valid_action(actor,targets,arg,execute);
}

