/*
 * pHeal
 */

#pragma strict_types

inherit "/d/Genesis/specials/std/spells/heal";

#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <files.h>
#include <composite.h>
#include "/d/Krynn/common/defs.h"

#include <macros.h>
#include <tasks.h>

/*
 * Function:    config_heal_spell
 * Description: Config function for heal spells. Redefine this in your
 *              own heal spells to override the defaults.
 */
public void
config_heal_spell(void)
{
    set_spell_name("heal");
    set_spell_desc("Healing hands - a prayer of healing");

    set_spell_element(SS_ELEMENT_LIFE, 20);
    set_spell_form(SS_FORM_TRANSMUTATION, 20);
    set_spell_fail("Your prayer of healing is unheard.\n");

    set_spell_task(TASK_ROUTINE);
    // 1.5 times the standard cast time for a heal spell 
    set_spell_time_factor(1.5);  

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_combat_aid(80.0);
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
 * Function:    query_heal_ingredients
 * Description: This function defines what components are required for
 *              this heal spell.
 */
public string *
query_heal_ingredients(object caster)
{
    return ({  });
}

/*
 * Function:    query_spell_ingredients_description
 * Description: Returns a string description of the ingredients. Can be used 
 *              in messages to casters about what is actually required
 *              for this spell.
 */
public string
query_spell_ingredients_description()
{
    return "no prayer components";
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
        return 0;

    return 1;
}

/*
 * Function:    resolve_heal_spell
 * Description: Called at the beginning of resolve_spell in order to perform 
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_heal_spell(object caster, object *targets, int *resist, int result)
{
}

/*
 * Function name: hook_describe_heal_cast
 * Description:   Describe casting of the spell. This takes place before the
 *                actual healing happens.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 */
public void
hook_describe_heal_cast(object caster, object *targets)
{
  // deliberately kept blank. Healing message covered under concentrate_msg
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

        caster_message = "You whisper a prayer, supplicating Paladine" + 
              " for the blessing of divine healing.\n";
        watcher_message = QCTNAME(caster) + " whispers a prayer to the "
              +"god Paladine.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
}


/*
 * Function name: hook_describe_heal_result
 * Description:   Describe the results of the spell upon its targets. This
 *                happens after the healing has happened.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 *                int * heal_amts - the amounts healed
 */
public void
hook_describe_heal_result(object caster, object *targets, int * heal_amounts)
{
    object tar = targets[0];
    int heal = heal_amounts[0];
    string heal_desc;

    switch(heal)
    {
       case 0..50:
         heal_desc = " slightly";
         break;
       case 51..150:
         heal_desc = " somewhat";
         break;
       case 151..250:
         heal_desc = "";
         break;
       case 251..450:
         heal_desc = " greatly";
         break;
       case 451..750:
         heal_desc = " miraculously";
         break;
       default:
         heal_desc = "";
         break;
    }

    // casting on evil aligned targets results in a standing adjustment.

    if (tar->query_alignment() < -100)
    {
	caster->catch_tell("You find it more difficult healing someone " +
	    "dark of heart.\n");
    }

    if (tar == caster)
    {
	caster->catch_tell("You feel the blessings of Paladine" +
            " wash over you and new health infuse your body, your wounds" +
            heal_desc+ " healed.\n");
	tell_room(environment(caster), QCTNAME(caster) +
	    " straightens up, looking" +heal_desc+ " more hale.\n", targets);
    }
    else
    {
	caster->catch_tell("You place your hands on " +
	    tar->query_the_name(caster) + ", and " + HE(tar) +
	    " shivers as " + HIS(tar) + " wounds are" +heal_desc+ 
            " healed.\n");
	tar->catch_tell(caster->query_The_name(tar) + " places " +
	    HIS(caster) + " hands on you, and you shiver as your " +
	    "wounds are" +heal_desc+ " healed.\n");
	tell_room(environment(caster), QCTNAME(caster) + " places " +
	    HIS(caster) + " hands on " + QTNAME(tar) + ", and " +
	    HE(tar) + " shivers as " + HIS(tar) + " wounds are" +heal_desc+ 
            " healed.\n", ({ caster, tar }), caster);
    }

}
