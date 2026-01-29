/*
 * Protection from cold spell for SOHM
 *
 * Coded by Arman 2016.
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

inherit "/d/Genesis/specials/std/spells/resistance";

/*
 * Function:    config_shadow_spell
 * Description: Config function for shadow spells. Redefine this in your
 *              own shadow spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_resistance_spell()
{
    set_spell_name("trothgul");
    set_spell_desc("Minor protection, cold - a cold protection spell");

    set_spell_element(SS_ELEMENT_WATER,  50);
    set_spell_form(SS_FORM_ABJURATION, 50);
    set_spell_task(TASK_HARD);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);
   
    set_spell_object(SOHM_SPELL_OBJS + "protect_cold_obj");
    add_resistance(MAGIC_I_RES_COLD, 30);


}

/*
 * Function:    query_resistance_ingredients
 * Description: This function defines what components are required for
 *              this resistance spell.
 */
public string *
query_resistance_ingredients(object caster)
{
    return ({ "frostheal" });
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
    return SOHM_MANAGER->query_memorised_spell(player,"trothgul_memorised");
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

        caster_message = "Your eyes narrow in concentration as you begin reciting " +
            "ancient words of magic, a ward of protection from cold.\n";
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

   object tar = targets[0];

    if(tar->query_has_shadow_veil_shadow())
    {
        caster->catch_tell("A shadow veil illusion interferes with your protection spell, " +
            "causing it to fail.\n");
	return 0; 
    }
  
    return 1;
}

/*
 * Function:    hook_describe_cast_resistance
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_resistance(object caster, object * targets)
{
    object * message_targets = targets + ({ });
    message_targets -= ({ caster });
    if (IN_ARRAY(caster, targets))
    {
        if (sizeof(message_targets))
        {
            caster->catch_tell("You cast a cold protection spell upon "
                + "yourself and " + COMPOSITE_LIVE(message_targets) + ".\n");
        }
        else
        {
            caster->catch_tell("You cast a cold protection spell " +
                  "upon yourself.\n");
        }
    }
    else
    {
        caster->catch_tell("You cast a cold protection spell upon "
            + COMPOSITE_LIVE(message_targets) + ".\n");
    }
    caster->tell_watcher(QCTNAME(caster) + " casts a spell of protection.\n", ({ }) );
}