/*
 * Breath water spell for warfare armour helms
 * found in /d/Krynn/common/warfare/rewards/
 * Coded by Arman Oct 2018.
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <composite.h>
#include <files.h>
#include <wa_types.h>

inherit "/d/Genesis/specials/std/spells/propchange_base";

#define ABILITY_LOC "/d/Krynn/common/warfare/rewards/magic_effects/"

string helm_str;

/*
 * Function:    config_propchange_spell
 * Description: Config function for propchange spell. Redefine this in your
 *              own propchange spells to override the defaults.
 */

public void
config_propchange_spell()
{

    set_spell_name("Watermere");
    set_spell_desc("breathe water");

    set_spell_element(SS_ELEMENT_WATER, 0);
    set_spell_form(SS_FORM_ABJURATION, 0);
    set_spell_task(TASK_SIMPLE);

    set_spell_time_factor(0.5);
    set_spell_mana_factor(5.0);

    set_spell_vocal(0);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0); 
    set_spell_offensive(0);

    set_shadow_filename(ABILITY_LOC + "underwater_breath_ability_sh");

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

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    object helm = caster->query_armour(TS_HEAD);

    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if (helm->query_crystal_id_two() != "_watermere_crystal")
    {
        return 0;
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
    object helm = caster->query_armour(TS_HEAD);
    helm_str = helm->query_short();

    if(helm_str)
    {
        caster_message = "You press the triangular gemstone on your " +
            helm_str+ ".\n";
        watcher_message = QCTNAME(caster) + " touches a gemstone upon " + 
            caster->query_possessive() + " " +helm_str+ ".\n";
        
        caster->catch_tell(caster_message);
        tell_room(environment(caster), watcher_message, 
            ({ caster }), caster);
    }
    setuid();
    seteuid(getuid());    
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
            caster->catch_tell("You feel the air around your " +helm_str+ 
                " blur slightly, as if it were briefly surrounded by " +
                "a protective bubble.\n");
        }
        else
        {
            caster->catch_tell("You feel the air around your " +helm_str+ 
                " blur slightly, as if it were briefly surrounded by " +
                "a protective bubble.\n");
        }
    }
    else
    {
            caster->catch_tell("You feel the air around your " +helm_str+ 
                " blur slightly, as if it were briefly surrounded by " +
                "a protective bubble.\n");
    }

}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("You already have activated your " +helm_str+ "'s " +
        "gemstone ability!\n");
}

public void
hook_already_active(object player)
{
    write("You already have activated your " +helm_str+ "'s " +
        "gemstone ability!\n");
}

public void
hook_no_mana_fail(object ability)
{
    object helm = this_player()->query_armour(TS_HEAD);
    helm_str = helm->query_short();

    write("You don't have mana enough to properly activate " +
        "your " +helm_str+ "'s gemstone ability!\n");
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