/*
 * Enchantment stun spell for SOHM
 *
 * Created by Arman 2016, based on base spell
 * /d/Genesis/specials/std/spells/stun
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <composite.h>
#include <files.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"

inherit "/d/Genesis/specials/std/spells/stun";

/*
 * Function:    config_stun_spell
 * Description: Config function for stun spells. Redefine this in your
 *              own stun spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_stun_spell()
{
    set_ability_group(GUILD_NAME);
    set_spell_name("reelojawa");
    set_spell_desc("Dominate - bend a target's mind to your will, stunning them");

    set_spell_element(SS_ELEMENT_WATER,  50);
    set_spell_form(SS_FORM_ENCHANTMENT, 60);
    set_spell_task(TASK_HARD);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(45.0);
    set_spell_object(SOHM_SPELL_OBJS + "dominate_obj");    

}

/*
 * Function:    query_resistance_ingredients
 * Description: This function defines what components are required for
 *              this resistance spell.
 */
public string *
query_stun_ingredients(object caster)
{
    return ({ "_reelojawa_charge" });
}


/*
 * Function:    query_spell_can_be_learned
 * Description: Place restrictions on whether this spell can be used
 *              by the guild member.
 */
public int
query_spell_can_be_learned(object player)
{
    if (!objectp(player))
    {
        return 0;
    }
    
    if (player->query_npc())
    {
        // npcs can always learn the spell.
        return 1;
    }
    
    setuid();
    seteuid(getuid());
    return SOHM_MANAGER->query_memorised_spell(player,"reelojawa_memorised");
}

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (mixed *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */
public void
concentrate_msg(object caster, mixed * targets, string arg)
{
    string caster_message, watcher_message;
    object target = targets[0];

        caster_message = "Your eyes narrow in concentration as you begin chanting " +
            "magical words of mind manipulation and domination.\n";
        watcher_message = QCTNAME(caster) + " narrows " + caster->query_possessive() + 
              " eyes in concentration and begins reciting mystical words of magic.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    object *target;

    if (sizeof(target = filter(targets[0]->query_stun_effects(),
        &operator(==)(, caster->query_real_name()) @ &->query_sohm_dominate())))
    {   
        if (target[0]->query_sohm_active())
        {
            caster->catch_tell("The mind of " + COMPOSITE_LIVE(targets) +
            " is currently being dominated.\n");
            return 0;
        }
    }

    object tar = targets[0];

    if(tar->query_has_sohm_curse_shadow())
    {
        caster->catch_tell("A curse of uncertainty interferes with your spell, " +
            "causing it to fail.\n");
        return 0;
    }

    if("/d/Krynn/guilds/sohm/spells/gravity"->has_spell_object(tar))
    {
        caster->catch_tell("A burdening transmutation interferes with your spell, " +
            "causing it to fail.\n");
	return 0; 
    }

    if("/d/Krynn/guilds/sohm/spells/haste"->has_spell_object(caster))
    {
        caster->catch_tell("Your haste spell interferes with your ability " +
              "to cast dominate.\n");
	return 0; 
    }
 
    return 1;
}

/*
 * Function:    hook_describe_cast_stun
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_stun(object caster, object * targets)
{
    caster->catch_tell("You attempt to dominate the mind of " 
        + COMPOSITE_LIVE(targets) + " with a powerful enchantment.\n");
    caster->tell_watcher(QCTNAME(caster) + " casts an enchantment of " +
        "domination.\n", ({ }) );
 
}
/*
 * Function:    hook_target_stun_resisted
 * Description: Called to show the messages of the targets that were not
 *              stunned because they resisted the spell.
 */
public void
hook_target_stun_resisted(object caster, object * targets)
{
    if (!sizeof(targets))
    {
        return;
    }
    
    caster->catch_tell("You try to dominate " + COMPOSITE_LIVE(targets) 
        + ", but your attempt is resisted.\n");
    targets->catch_tell("You resist the enchantment of domination.\n"); 
}

/*
 * Function:    hook_target_stun_succeeded
 * Description: Called to show the messages of the targets that were
 *              affected by the stun. Part of the stun messages
 *              will also be described by the stun object itself. Note
 *              that it's entirely possible the stun spell may hit,
 *              but because of a cooldown period, the stun may not
 *              actually have any effect.
 */
public void
hook_target_stun_succeeded(object caster, object * targets)
{
    if (!sizeof(targets))
    {
        return;
    }
    
    caster->catch_tell("You enter the mind of " + COMPOSITE_LIVE(targets) + 
        " with your enchantment of domination.\n"); 
}
