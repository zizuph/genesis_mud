/*
 * /d/Gondor/spells/antiscry_spell_effect
 *
 * Protect from divination spell for the lesser ring
 * found in Cair Andros.
 *
 * Based on SoHM protection from divination spell:
 *    /d/Krynn/guilds/sohm/spells/protect_divination.c
 *
 * Modified by Arman - March, 2020
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <composite.h>
#include <files.h>

inherit "/d/Genesis/specials/std/spells/propchange_base";

/*
 * Function:    config_propchange_spell
 * Description: Config function for propchange spell. Redefine this in your
 *              own propchange spells to override the defaults.
 */

public void
config_propchange_spell()
{
    set_spell_name("scry protection");
    set_spell_desc("Protection from scrying");

    set_spell_element(SS_ELEMENT_WATER,  0);
    set_spell_form(SS_FORM_ABJURATION, 0);
    set_spell_task(TASK_SIMPLE);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);
    set_spell_can_be_renewed(0);
    set_spell_time_factor(0.2);

    // Mana cost 30.0 times mana factor, so 180 mana cost per use.
    set_spell_mana_factor(6.0);
   
    set_shadow_filename("/d/Gondor/spells/antiscry_spell_sh");

}

/*
 * Function:    query_propchange_ingredients
 * Description: This function defines what components are required for
 *              this spell.
 */
public string *
query_propchange_ingredients(object caster)
{
    return ({ });
}


/* 
 * Function:    set_input_parameters
 * Description: This function should be overridden by the spell to set
 *              the input parameters that should be passed to the shadow
 *              object.
 */
public void
set_input_parameters(object caster, mixed * targets, int * resist, int result, mapping spell_input)
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
    
    return 1;
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

    caster_message = "Your twist the simple golden ring.\n";
    watcher_message = QCTNAME(caster) + " twists a simple golden ring on " +
        caster->query_possessive()+ " finger.\n";
        
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
 * Function:    hook_describe_cast_propchange
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */

public void
hook_describe_cast_propchange(object caster, object* targets)
{
    object * message_targets = targets + ({ });
    message_targets -= ({ caster });
    if (IN_ARRAY(caster, targets))
    {
        if (sizeof(message_targets))
        {
            caster->catch_tell("You and " + COMPOSITE_LIVE(message_targets) + 
                " seem to be protected from scrying.\n");
        }
        else
        {
            caster->catch_tell("You feel a cloaking ward fall over you.\n");
        }
    }
    else
    {
        caster->catch_tell("You notice a cloaking ward fall upon "
            + COMPOSITE_LIVE(message_targets) + ".\n");
    }
    caster->tell_watcher(QCTNAME(caster) + " is protected by a cloaking ward.\n", 
        ({ }) );
}

/*
 * Function:    hook_already_has_spell_object
 * Description: Function that gets called to tell the caster that the spell is
 *              already in effect on the target and cannot be stacked.
 */
public void
hook_already_has_spell_object(object caster, object target)
{
    caster->catch_msg(QCTNAME(target) + " is already warded!\n");
}

/*
 * Function name: hook_no_mana_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have enough mana.
 * Returns:       The message to print.
 */
public void
hook_no_mana_fail(object ability)
{
    write("You feel momentarily dizzy after twisting the ring, but apart " +
        "from that nothing seems to happen.\n");
}