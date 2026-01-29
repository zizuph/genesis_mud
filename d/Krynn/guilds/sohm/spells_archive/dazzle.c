/*
 * Dazzle (slow) spell for SoHM
 * 
 * Created by Arman 2016.
 * Based on base slow spell by Petros, September 2009
 */
 
#pragma strict_types

#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <composite.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"

inherit "/d/Genesis/specials/std/spells/slow";

/*
 * Function:    config_slow_spell
 * Description: Config function for slow spells. Redefine this in your
 *              own slow spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */

public void
config_slow_spell()
{
    set_ability_group(GUILD_NAME);
    set_spell_name("okiai");
    set_spell_desc("Dazzle - unbalance the directional senses");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);

    set_spell_element(SS_ELEMENT_AIR, 30);
    set_spell_form(SS_FORM_ENCHANTMENT, 30);
    set_spell_task(TASK_ROUTINE);    

    // Spell effect object
    set_spell_object(SOHM_SPELL_OBJS + "dazzle_obj");

    // By default, set the slow interval to 1.0
    set_slow_interval(1.0);

}

/*
 * Function:    query_slow_ingredients
 * Description: This function defines what components are required for
 *              this slow spell.
 */
public string * 
query_slow_ingredients(object caster)
{
    return ({ });
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

/*  Allowing these spells to potentially be more widely used than just SoHM
  
    if (!IS_MEMBER(caster))
    {
        caster->catch_tell("You are not a student of High Magic!\n");
        return 0;
    }
    
    if (SOHM_MANAGER->is_casting_banned(caster))
    {
        caster->catch_tell("You have been banned from casting combat "
            + "spells for breaking the rules. Please see <help sohm "
            + "rules>.\n");
        return 0;
    }
*/
        
    return 1;
}

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
    return SOHM_MANAGER->query_memorised_spell(player,"okiai_memorised");
}

// HOOKS TO BE DEFINED

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

        caster_message = "With a snap of your hands you invoke a word " +
            "of a power, 'okiai!'\n";
        watcher_message = QCTNAME(caster) + " snaps " +HIS(caster)+ " hands " +
            "in the air and invokes a dazzling word of power.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());    
}

/*
 * Function:    hook_describe_cast_slow
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_slow(object caster, object * targets)
{
    object tar = targets[0];

    caster->catch_msg("You dazzle " +QTNAME(tar) + 
                       " with an enchantment, making " +HIM(tar)+
                       " uncertain on " +HIS(tar)+ " feet.\n");

    tar->catch_tell(caster->query_The_name(tar)+" dazzles you with "+
	    "an enchantment, making you uncertain on your feet.\n");

    tell_room(environment(caster), QCTNAME(caster)+" dazzles "+
	    QTNAME(tar)+" with an enchantment, making "+HIM(tar)+
	    " uncertain on " +HIS(tar)+ " feet.\n", ({ caster, tar }), caster);

}
/*
 * Function:    hook_already_has_spell_object
 * Description: Function that gets called to tell the caster that the spell is
 *              already in effect on the target and cannot be stacked.
 */
public void
hook_already_has_spell_object(object caster, object target) 
{
    caster->catch_msg(QCTNAME(target) + " is already dazzled!\n");
}
/*
 * Function:    hook_slow_resisted
 * Description: Function that gets called to tell that the spell did
 *              not succeed against the targets.
 */
public void
hook_slow_resisted(object caster, object* targets)
{
    caster->catch_msg("You sense that " + COMPOSITE_LIVE(targets) + " is " +
                      "unaffected by your spell.\n");
    targets->catch_msg("You resist an attempt by " + QTNAME(caster) +
                       "to dazzle you with an enchantment.\n");
    caster->tell_watcher(QCTPNAME(caster) + " enchantment was " +
                         "resisted by " + COMPOSITE_LIVE(targets) + ".\n",
                         ({ caster }) + targets); 
}