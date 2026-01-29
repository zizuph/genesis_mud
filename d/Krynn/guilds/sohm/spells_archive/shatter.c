/*
 * Transmutation gem shatter cantrip for SOHM
 *
 * Coded by Arman 2017.
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <composite.h>
#include <ss_types.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"

inherit "/d/Genesis/specials/std/spells/shatter";

/*
 * Function:    config_shatter_spell
 * Description: Config function for shatter spells. Redefine this in your
 *              own shatter spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */

public void
config_shatter_spell()
{
    set_spell_name("jikmadakethend");
    set_spell_desc("Shatter - a basic transmutation allowing the caster to " +
        "split gemstones");

    set_spell_element(SS_ELEMENT_EARTH,  20);
    set_spell_form(SS_FORM_TRANSMUTATION, 20);
    set_spell_task(TASK_ROUTINE);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);

}

/* 
 * Function:    resolve_shatter_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_shatter_spell(object caster, mixed * targets, int * resist, int result)
{
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
    return SOHM_MANAGER->query_memorised_spell(player,"jikmadakethend_memorised");
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
    object * all_gems = get_valid_gems_for_spell(caster);

    caster_message = "You stretch out a hand toward " +COMPOSITE_DEAD(all_gems)+ 
        " and begin chanting words of magic, 'Jikmada Kethend!'\n";
    watcher_message = QCTNAME(caster) + " stretches out a hand toward " +
        COMPOSITE_DEAD(all_gems)+ " and begins chanting words of magic.\n";
        
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
  
    return 1;
}


/*
 * Function:    hook_describe_shatter_success
 * Description: Mask this function to describe the message that occurs when
 *              the spell completes successfully and gems are shattered. It
 *              gives a list of all the gems prior to shattering and all the
 *              shards resulting from the shatter.
 */
public void
hook_describe_shatter_success(object caster, object * all_gems, object * all_shards)
{
    tell_room(environment(caster), "A brilliant burst of light temporarily "
        + "blinds you and you hear a loud shattering sound from " 
        + COMPOSITE_DEAD(all_gems) + ". As the light fades, you see "  
        + COMPOSITE_DEAD(all_shards) + ".\n");
}
/*
 * Function:    hook_describe_shatter_no_valid_gems_precast
 * Description: Mask this function to describe the message that occurs when the
 *              caster doesn't find any gems. Called from check_valid_action
 */
public void
hook_describe_shatter_no_valid_gems_precast(object caster)
{
    caster->catch_tell("You don't find anything on the ground that you "
        + "can shatter.\n");
}
/*
 * Function:    hook_describe_shatter_no_valid_gems_postcast
 * Description: Mask this function to describe the message that occurs when
 *              the caster completes the spell, but finds no valid gems
 *              to shatter. This can occur if someone picks up the gems, 
 *              for example.
 */
public void
hook_describe_shatter_no_valid_gems_postcast(object caster)
{
    caster->catch_tell("You realize much too late that there are no gems "
        + "on the ground and your spell has no effect.\n");
}
