/*
 * Detect resistance spell for SOHM
 *
 * Created by Arman 2016 based on base detect_resistance spell
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <files.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"

inherit "/d/Genesis/specials/std/spells/detect_resistance";

/*
 * Function:    config_detect_resistance_spell
 * Description: Config function for detect_resistance spells. Redefine this in your
 *              own detect_resistance spells to override the defaults.
 */
public void
config_detect_resistance_spell()
{
    set_spell_name("ickrakfethos");
    set_spell_desc("Detect resistances - divine magical resistances of a target");

    set_spell_element(SS_ELEMENT_AIR, 30);
    set_spell_form(SS_FORM_DIVINATION, 30);

    // Needs to be particularly easy to cast to break through some resistances
    set_spell_task(TASK_SIMPLE);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);

    set_spell_target(spell_target_one_present_living);
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
    return SOHM_MANAGER->query_memorised_spell(player,"ickrakfethos_memorised");
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

        caster_message = "You furtively gesture towards " + QTNAME(target) +
                         " while chanting the words of magic 'ickrak fethos'!\n";
        watcher_message = QCTNAME(caster) + " gestures mysteriously " + 
              "while chanting words of magic.\n";
        
    caster->catch_msg(caster_message);
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

/*  Allowing these spells to potentially be more widely used than just SoHM
    
    if (!IS_MEMBER(caster))
    {
        caster->catch_tell("You are not a Student of High Magic!\n");
        return 0;
    }
    
    if (SOHM_MANAGER->is_casting_banned(caster))
    {
        caster->catch_tell("You have been banned from casting "
            + "spells for breaking the rules.\n");
        return 0;
    }

*/
  
    return 1;
}

/*
 * Function:    hook_detect_resistance_cast
 * Description: Override this to customize the tell spell descriptions.
 */
public void
hook_detect_resistance_cast(object caster)
{
}

/*
 * Function:    hook_detect_resistance_resisted
 * Description: Override this to customize the tell spell descriptions.
 */
public void
hook_detect_resistance_resisted(object caster, object target, int resistance)
{
    DEBUG("Resistance value: " +resistance+ ".");
    string str = "";

    if((target->query_magic_res(MAGIC_I_RES_AIR) > 10) && 
       (target->query_magic_res(MAGIC_I_RES_MAGIC) > 10))
      str = " "+ C(HE(target))+ " seems to have some resistance to the air " +
            "element and magic in general, confounding your spell."; 
    else if(target->query_magic_res(MAGIC_I_RES_AIR) > 10)
      str = " "+ C(HE(target))+ " seems to have some resistance to the air " +
            "magic, confounding your spell.";
    else if(target->query_magic_res(MAGIC_I_RES_MAGIC) > 10)
      str = " "+ C(HE(target))+ " seems to have some resistance to magic " +
            "in general, confounding your spell.";

    caster->catch_msg(QCTNAME(target) + " resists your attempt to divine "
        + "any magical resistances." +str+ "\n");
}

string
reword_element(string element)
{
   string new_element;

   switch(element)
   {
     case "_magic_i_res_electricity":
      new_element = "electricity";
      break;
     case "_magic_i_res_poison":
      new_element = "poison";
      break;
     case "_magic_i_res_identify":
      new_element = "identification spells";
      break;
     case "_magic_i_res_life":
      new_element = "life magic";
      break;
     case "_magic_i_res_water":
      new_element = "water magic";
      break;
     case "_magic_i_res_air":
      new_element = "air magic";
      break;
     case "_magic_i_res_fire":
      new_element = "fire magic";
      break;
     case "_magic_i_res_death":
      new_element = "death magic";
      break;
     case "_magic_i_res_earth":
      new_element = "earth magic";
      break;
     case "_magic_i_res_magic":
      new_element = "magic in general";
      break;
     case "_magic_i_res_cold":
      new_element = "the cold";
      break;
     case "_magic_i_res_acid":
      new_element = "acid";
      break;
     case "_magic_i_res_life":
      new_element = "life magic";
      break;
     case "_magic_i_res_illusion":
      new_element = "illusion spells";
      break;
     default:
      new_element = "something you are unable to define";
    }

  return new_element;
}

 
/*
 * Function:    hook_detect_resistance_living_results
 * Description: Override this function to describe what a player should see
 *              when they are detecting magic on a living being.
 */
public void
hook_detect_resistance_success(object caster, object target, mapping resistances)
{
    int detect_resist = 0;

    caster->catch_msg("You divine the following from " +QTNAME(target)+ ":\n");
    foreach (string element, int resistance : resistances)
    {
      string new_element = reword_element(element);

      switch(resistance)
      {
        case -200..-61:
         caster->catch_msg("You detect extreme vulnerability to " + new_element + ".\n");
         detect_resist = 1;
         break;
        case -60..-41:
         caster->catch_msg("You detect high vulnerability to " + new_element + ".\n");
         detect_resist = 1;
         break;
        case -40..-31:
         caster->catch_msg("You detect considerable vulnerability to " + new_element + ".\n");
         detect_resist = 1;
         break;
        case -30..-11:
         caster->catch_msg("You detect some vulnerability to " + new_element + ".\n");
         detect_resist = 1;
         break;
        case -10..-1:
         caster->catch_msg("You detect minor vulnerability to " + new_element + ".\n");
         detect_resist = 1;
         break;
        case 0:
         break;
        case 1..10:
         caster->catch_msg("You detect minor resistance to " + new_element + ".\n");
         detect_resist = 1;
         break;
        case 11..30:
         caster->catch_msg("You detect some resistance to " + new_element+ ".\n");
         detect_resist = 1;
         break;
        case 31..40:
         caster->catch_msg("You detect considerable resistance to " + new_element+ ".\n");
         detect_resist = 1;
         break;
        case 41..60:
         caster->catch_msg("You detect high resistance to " + new_element+ ".\n");
         detect_resist = 1;
         break;
        case 61..80:
         caster->catch_msg("You detect extreme resistance to " + new_element+ ".\n");
         detect_resist = 1;
         break;
        default:
         caster->catch_msg("You detect almost invulnerability to " + new_element+ ".\n");
         detect_resist = 1;
      }
    }

    if(!detect_resist)
     caster->catch_msg(QCTNAME(target)+ " appears to have no magical resistances.\n");
}

/*
 * Function:    query_detect_resistance_ingredients
 * Description: This function defines what components are required for 
 *              this detect_resistance spell.
 */
public string *
query_detect_resistance_ingredients(object caster)
{
    // By default, use the herb for awareness
    return ({ "kuko" });
}