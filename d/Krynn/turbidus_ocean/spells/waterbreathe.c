/*
 * Water breathing spell for hornblade
 *
 * Coded by Arman 2020.
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
    set_spell_name("narbreath");
    set_spell_desc("Water breathing - the ability to breath underwater");

    set_spell_element(SS_ELEMENT_WATER,  0);
    set_spell_form(SS_FORM_TRANSMUTATION, 0);
    set_spell_task(TASK_SIMPLE);

    set_spell_fail("The narwhal hornblade fails to activate.\n");

    set_spell_time_factor(0.5);
    set_spell_mana_factor(5.0);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);
   
    set_shadow_filename("/d/Krynn/turbidus_ocean/spells/waterbreathe_sh");
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

    caster_message = "You press the bony nub on the narwhale hornblade, and " +
        "it comes alive with a brilliant, pulsing, blue-green glow.\n";
    watcher_message = QCTPNAME(caster) + " narwhale hornblade comes alive in " + 
        caster->query_possessive() + " hand with a brilliant, pulsing, " +
        "blue-green glow.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
}

int
filter_tool(object obj)
{
      if (obj->id("_narwhal_hornblade"))
        return 1;
      else 
        return 0;
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    object *weapon;

    if(caster->query_tool(-1))
      weapon = filter(caster->query_tool(-1), filter_tool);  

    if(!sizeof(weapon))
    {
        caster->catch_tell("You need to wield the narwhal hornblade to " +
            "activate it.\n");
        return 0;
    }

    if(!weapon[0]->query_wielded())
    {
        caster->catch_tell("You have to be wielding the narwhal hornblade to " +
            "activate it.\n");
        return 0;
    }

    if(caster->query_skill(SS_SPELLCRAFT) < 20)
    {
        caster->catch_tell("You press the bony nub but nothing seems to happen. " +
            "You likely need more spellcraft skill to be able to activate the " +
            "enchantment of this weapon.\n");
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
            caster->catch_tell("You cast a water breathing spell upon "
                + "yourself and " + COMPOSITE_LIVE(message_targets) + ".\n");
        }
        else
        {
            caster->catch_tell("You find yourself surrounded by a globe " +
                "of shimmering blue air.\n");
        }
    }
    else
    {
        caster->catch_tell("You cast a water breathing spell upon "
            + COMPOSITE_LIVE(message_targets) + ".\n");
    }
    caster->tell_watcher(QCTNAME(caster) + " is surrounded by a globe " +
        "of shimmering blue air.\n", ({ }) );
}

/*
 * Function:    hook_already_has_spell_object
 * Description: Function that gets called to tell the caster that the spell is
 *              already in effect on the target and cannot be stacked.
 */
public void
hook_already_has_spell_object(object caster, object target)
{
    caster->catch_msg(QCTNAME(target) + " is already surrounded by a globe " +
        "of air!\n");
}