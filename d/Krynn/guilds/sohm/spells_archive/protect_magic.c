/*
 * Protection from magic spell for WoHS
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
#include <language.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"
#include CLOCKH

inherit "/d/Genesis/specials/std/spells/resistance";

#include  "/d/Krynn/guilds/wohs/wohs_moon_benefit.h";

#define PROT_MAGIC_PROP     "_wohs_prot_element_type"
#define PROT_MAGIC_CASTER   "_wohs_prot_element_caster"

string element_string;

/*
 * Function:    config_resistance_spell
 * Description: Config function for resistance spells. Redefine this in your
 *              own shadow spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_resistance_spell()
{
    set_spell_name("trotharcanis");
    set_spell_desc("Magic protection - a spell of protection from the arcane");

    set_spell_element(SS_ELEMENT_WATER,  50);
    set_spell_form(SS_FORM_ABJURATION, 60);
    set_spell_task(TASK_HARD);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);
    set_spell_target(spell_target_one_present_living);
   
    set_spell_object(SOHM_SPELL_OBJS + "protect_magic_obj");
}

public object *
spell_target_one_present_living(object actor, string str)
{
   // resistance_aid needs to be cleared here otherwise it allows the caster to
   // stack resistance types as the map doesn't get cleared when spell dispelled.
   resistance_aid = ([ ]);

   string target_string, caster_spec, elemental_string;
   object caster = actor;
   int resistance;
   int wohs_level = caster->query_guild_level_occ();

   if(!SOHM_MANAGER->query_specialisation_element(caster))
       caster_spec = "water";
   else 
       caster_spec = SOHM_MANAGER->query_specialisation_element(caster);
	
   if(str)
   {
       parse_command(str, environment(caster), "[on] %w [with] %w [protection]", 
           target_string, elemental_string);
   }
   else
   {
       target_string = "myself";
       elemental_string = caster_spec;
   }    

   element_string = elemental_string;

    if (elemental_string)
    {       
        if((elemental_string != "fire") && (elemental_string != "earth") &&
           (elemental_string != "water") && (elemental_string != "air") &&
           (elemental_string != "cold") && (elemental_string != "poison") &&
           (elemental_string != "electricity") && (elemental_string != "life") &&
           (elemental_string != "death") && (elemental_string != "acid") &&
           (elemental_string != "illusion"))
        {
           if (!target_string)
    	      caster->catch_tell("What type of element were you trying to protect " +
                  "yourself from? Protection from fire, earth, water, " +
                  "air, cold, poison, electricity, life, death, acid or illusion?\n");
           else
    	      caster->catch_tell("What type of element were you trying to protect " +
                  capitalize(target_string)+ " from? Protection from fire, earth, " +
                  "water, air, cold, poison, electricity, life, death, acid or " +
                  "illusion?\n");
           return 0;
        }
        caster_spec = elemental_string;
    }
    else
    {
        elemental_string = caster_spec;
        element_string = elemental_string;
    }
    
   if (!target_string)
   {
       target_string = "myself";
   }

   string moon_bonus = SOHM_MANAGER->query_wohs_moon_phase_aid(caster);
   string resistance_type = "_magic_i_res_" +caster_spec;

   if(!moon_bonus)
       moon_bonus = "none";
   if(caster->query_wohs_alignment_penalty())
       moon_bonus = "penalty";

   // 30 caid with only one element protection gets a 20% loading to base 37 protection
   // Modify combat aid depending on phase of the magic moons:

   if(caster->query_wohs_alignment_penalty())
       resistance = 29; // 25% penalty
   if(moon_bonus == "night of the eye")
       resistance = 51; // 40% bonus
   else if(moon_bonus == "maximum")
       resistance = 46; // 25% bonus
   else if(moon_bonus == "partial")
       resistance = 40; // 10% bonus
   else if(moon_bonus == "none")
       resistance = 37; // base protection
   else if(moon_bonus == "partial_penalty")
       resistance = 34; // 10% penalty
   else if(moon_bonus == "penalty")
       resistance = 29; // 25% penalty

    // If a team member has the Stellar Alignment spell being 
    // maintained, the moon penalty is nullified.
    if(check_stellar_alignment_benefit(TP) && (resistance < 37))
        resistance = 37; // base protection

   setuid();
   seteuid(getuid());

   add_resistance(resistance_type, resistance);
   //DEBUG("Target: " +target_string+ ", resistance: " +resistance+ ", resistance type: " +
   //       resistance_type+ ", moon phase " +moon_bonus+ ".");

   return target_one_present_living(actor, target_string);
}

/*
 * Function:    query_resistance_ingredients
 * Description: This function defines what components are required for
 *              this resistance spell.
 */
public string *
query_resistance_ingredients(object caster)
{
    return ({ "solinaith" });
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
    return SOHM_MANAGER->query_memorised_spell(player,"trotharcanis_memorised");
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
    string caster_message, watcher_message, magic_type;
    object target = targets[0];

    if(!element_string)
      magic_type = "magic";
    else
      magic_type = element_string + " magic";

        caster_message = "Your eyes narrow in concentration as you begin reciting " +
            "ancient words of magic, a ward of protection from " +magic_type+ ".\n";
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

    // To stop the caster from being able to add additional resistances to the existing
    // maintained spell object (which is unintended), this function needs to be called.
    foreach(object target: targets)
    {
        if(target->query_prop(PROT_MAGIC_CASTER) == caster->query_real_name())
        {
            string magic_type = element_string + " magic";
            string existing_prot = target->query_prop(PROT_MAGIC_PROP);

            if(magic_type == existing_prot)
            {
                return 1;
            }
            caster->catch_tell("You currently have trotharcanis protecting against " +
                "a different element. You will need to dispel that first before " +
                "adding a ward of protection against " +magic_type+ ".\n");
            return 0;
         }
    }

    return 1;
}

/*
 * Function:    resolve_resistance_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_resistance_spell(object caster, mixed * targets, int * resist, int result)
{

}

/*
 * Function:    hook_describe_cast_resistance
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_resistance(object caster, object * targets)
{
    string magic_type;

    if(!element_string)
      magic_type = "magic";
    else
      magic_type = element_string + " magic";

    object * message_targets = targets + ({ });
    message_targets -= ({ caster });
    if (IN_ARRAY(caster, targets))
    {
        if (sizeof(message_targets))
        {
            caster->catch_tell("You cast " +LANG_ADDART(magic_type)+ " protection spell upon "
                + "yourself and " + COMPOSITE_LIVE(message_targets) + ".\n");
        }
        else
        {
            caster->catch_tell("You cast " +LANG_ADDART(magic_type)+ " protection spell " +
                  "upon yourself.\n");
            caster->add_prop(PROT_MAGIC_PROP, magic_type);
            caster->add_prop(PROT_MAGIC_CASTER, caster->query_real_name());
        }
    }
    else
    {
        caster->catch_tell("You cast " +LANG_ADDART(magic_type)+ " protection spell upon "
            + COMPOSITE_LIVE(message_targets) + ".\n");

        foreach(object target: message_targets)
        {
            target->add_prop(PROT_MAGIC_PROP, magic_type);
            target->add_prop(PROT_MAGIC_CASTER, caster->query_real_name());
        }
    }

    caster->tell_watcher(QCTNAME(caster) + " casts a spell of protection.\n", ({ }) );
}
