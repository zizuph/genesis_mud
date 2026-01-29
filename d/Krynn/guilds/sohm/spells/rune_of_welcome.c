/*
 * Cantrip allowing access to the Tower of High Sorcery for WoHS
 *
 * Coded by Arman 2017.
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <composite.h>
#include <files.h>
#include "/d/Krynn/guilds/wohs/defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "propchange_base";

/*
 * Function:    config_propchange_spell
 * Description: Config function for propchange spell. Redefine this in your
 *              own propchange spells to override the defaults.
 */

public void
config_propchange_spell()
{
    set_spell_name("nuadealdoer");
    set_spell_desc("Rune of welcome - a mark allowing passage through " +
         "the forest of Wayreth");

    set_spell_element(SS_ELEMENT_EARTH,  50);
    set_spell_form(SS_FORM_ABJURATION, 60);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_0);
    set_spell_task(TASK_HARD);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);
   
    set_shadow_filename(SOHM_DIR + "spells/objs/rune_of_welcome_sh");

}

/*
 * Function:    query_propchange_ingredients
 * Description: This function defines what components are required for
 *              this spell.
 */
public string *
query_propchange_ingredients(object caster)
{
    return ({  });
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
    
    setuid();
    seteuid(getuid());
    return WOHS_MANAGER->query_memorised_spell(player,"nuadealdoer_memorised");
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

        caster_message = "You trace complex runes before " +
            COMPOSITE_LIVE(targets)+ " while reciting words of magic, granting " +
              "passage through the magical forest of Wayreth.\n";
        watcher_message = QCTNAME(caster) + " traces complex runes in the air while reciting " +
              "words of magic.\n";
        
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

    if (QUERY_IS_RENEGADE(caster))
    {
        caster->catch_tell("As a Renegade, the magical forest of Wayreth will not " +
           "recognise your rune of passage!\n");
        return 0;
    }

    if (QUERY_IS_RENEGADE(targets[0]))
    {
        caster->catch_tell("The magical forest of Wayreth will now allow a renegade into " +
           "the Tower of High Sorcery!\n");
        return 0;
    }

    if (caster == targets[0])
    {
        caster->catch_tell("Being a Wizard of High Sorcery, the magical forest of " +
           "Wayreth will grant you passage to the Tower. You have no need " +
           "of a rune of welcoming!\n");
        return 0;
    }

    if (QUERY_WHITE_COUNCIL(caster) || QUERY_RED_COUNCIL(caster) ||
        QUERY_BLACK_COUNCIL(caster))
    {
        return 1;
    }
 
    if (QUERY_IS_ARCHMAGE(caster))
    {
       // DEBUG("Archmage called");
       return 1;
    }
  
    caster->catch_tell("Only Archmages and members of the Conclave may " +
           "mark someone with a rune of welcoming!\n");
    return 0;
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
            caster->catch_tell("You mark yourself and " + 
               COMPOSITE_LIVE(message_targets) + " with a rune of welcome.\n");
        }
        else
        {
            caster->catch_tell("You protect yourself with a rune of welcome.\n");
        }
    }
    else
    {
        caster->catch_tell("You mark " + COMPOSITE_LIVE(message_targets) + 
            " with a rune of welcome, allowing free passage through the " +
            "forest of Wayreth to the Tower of High Sorcery.\n");
    }
    // caster->tell_watcher(QCTNAME(caster) + " .\n", ({ }) );
}

/*
 * Function:    hook_already_has_spell_object
 * Description: Function that gets called to tell the caster that the spell is
 *              already in effect on the target and cannot be stacked.
 */
public void
hook_already_has_spell_object(object caster, object target)
{
    caster->catch_msg(QCTNAME(target) + " already has been marked with a rune of " +
        "welcome!\n");
}