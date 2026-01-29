/*
 * Protection from lightning spell for SOHM
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

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "resistance";

#include "sohm_spell_functions.h"

#define PROT_SPELL_OBJ(x, y)  (SOHM_SPELLS + "protect_" + x)->has_spell_object(y) 

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
    set_spell_name("trothshochraos");
    set_spell_desc("Minor protection, lightning - a lightning protection spell");

    set_spell_element(SS_ELEMENT_AIR,  50);
    set_spell_form(SS_FORM_ABJURATION, 50);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_3);
    set_spell_task(TASK_ROUTINE);
   
    set_spell_object(SOHM_SPELL_OBJS + "protect_lightning_obj");
    add_resistance(MAGIC_I_RES_ELECTRICITY, 48);


}

/*
 * Function:    query_resistance_ingredients
 * Description: This function defines what components are required for
 *              this resistance spell.
 */
public string *
query_resistance_ingredients(object caster)
{
    return ({ "elidross" });
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
    return SOHM_MANAGER->query_memorised_spell(player,"trothshochraos_memorised");
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
            "ancient words of magic, a ward of protection from lightning.\n";
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

    if(query_maintained_defensive_caid_spells(caster, "lesser") > 1)
    {
        // Allow spell to be renewed
        if(PROT_SPELL_OBJ("lightning", caster))
            return 1;

	caster->catch_tell("You can only maintain two lesser spells " +
           "that provide combat utility at any time.\n");
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
            caster->catch_tell("You cast a lightning protection spell upon "
                + "yourself and " + COMPOSITE_LIVE(message_targets) + ".\n");
        }
        else
        {
            caster->catch_tell("You cast a lightning protection spell " +
                  "upon yourself.\n");
        }
    }
    else
    {
        caster->catch_tell("You cast a lightning protection spell upon "
            + COMPOSITE_LIVE(message_targets) + ".\n");
    }
    caster->tell_watcher(QCTNAME(caster) + " casts a spell of protection.\n", ({ }) );
}