/*
 * Psychic blast spell for School of High Magic - Arman 2016
 */

#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"

inherit "/d/Genesis/specials/std/spells/harm";

/*
 * Function:    config_harm_spell
 * Description: Config function for harm spells. Redefine this in your
 *              own harm spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_harm_spell()
{
    set_ability_group(GUILD_NAME);
    set_spell_name("ricindenthanus");
    set_spell_desc("Psychic blast - a mental blast of psychic energy");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(113.0);
    set_spell_task(TASK_HARD); 

    // 3 times the standard cast time for a harm spell 
    set_spell_time_factor(3.0);     

    set_spell_element(SS_ELEMENT_WATER, 40);
    set_spell_form(SS_FORM_ENCHANTMENT, 40);
}

/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_harm_ingredients(object caster)
{
    // One herb, and the requirement to be wielding a staff 
    // or holding a wand. 
    return ({ "_ricindenthanus_charge" });
}

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
    return SOHM_MANAGER->query_memorised_spell(player,"ricindenthanus_memorised");
}

int
filter_tool(object obj)
{
      if (obj->id("wand"))
        return 1;
      else if (obj->id("staff"))
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

    if (caster->query_npc())
    {
        // npcs can always cast the spell.
        return 1;
    }

    if (!caster->query_weapon(-1) && !caster->query_tool(-1))
    {
        caster->catch_tell("You need to be wielding a staff or holding a wand " +
              "to cast psychic blast.\n");
        return 0;
    }

    object *weapon;

    /* Filter out non-staffs */
    if(caster->query_tool(-1))
      weapon = filter(caster->query_tool(-1), filter_tool);  

    if(!sizeof(weapon))
    {
        caster->catch_tell("You aren't wielding a staff or holding a wand " +
              "to cast psychic blast.\n");
	return 0;
    }

    if(caster->query_prop("_sohm_stoneskin_effect"))
    {
        caster->catch_tell("Your stoneskin spell interferes with your ability " +
              "to cast psychic blast.\n");
	return 0; 
    }
    
    if(caster->query_prop("_sohm_magic_shield_effect"))
    {
        caster->catch_tell("Your magic shield spell interferes with your ability " +
              "to cast psychic blast.\n");
	return 0; 
    }

    if(caster->query_prop("_sohm_blur_effect"))
    {
        caster->catch_tell("Your blur spell interferes with your ability " +
              "to cast psychic blast.\n");
	return 0; 
    }

    if(caster->query_prop("_sohm_portents_and_omens_effect"))
    {
        caster->catch_tell("Your portents and omens spell interferes with your ability " +
              "to cast psychic blast.\n");
	return 0; 
    }

    object * effects = caster->query_prop("_live_o_maintained_effects");
    string caster_name = caster->query_real_name();

    foreach (object effect : effects)
    {
        if (objectp(effect))
        {
           if (environment(effect)->query_prop("_sohm_retributive_ward_effect") == caster_name)
           {
                caster->catch_tell("The retributive ward you are maintaining interferes " +
                                   "with your ability to cast psychic blast.\n");
                return 0;
           }
        }
    }

    return 1;
}

// HOOKS TO BE DEFINED

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
    string caster_message, watcher_message, wep_str;
    object *wep;
    /* Filter out non-staffs and wands */
    wep = filter(caster->query_tool(-1), filter_tool);

    if(!sizeof(wep))
        wep_str = "hands";
    else
        wep_str = wep[0]->short();

    caster_message = "You raise your " +wep_str+ " and begin chanting, " +
       "your voice rising to a high-pitched wail.\n";
    watcher_message = QCTNAME(caster) + " raises " +
       caster->query_possessive()+ " " +wep_str+ " and begins chanting, " +
       caster->query_possessive()+ " voice rising to a high-pitched " +
       "wail.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);
    
    setuid();
    seteuid(getuid());
}

/*
 * Function name: desc_harm_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                mixed *result - return value from harm's hit_me.
 */
public void
desc_harm_damage(object caster, object target, mixed *result)
{
    string caster_message, target_message, watcher_message;
    int phurt = result[0];
    string hitloc_desc = result[1];

    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "A wave of psychic energy washes harmlessly against your " +
             "mental walls.\n";
        watcher_message = "A wave of psychic energy washes harmlessly over " + 
             QTNAME(target) + ".\n";
    }
    else
    {        
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "A wave of psychic energy washes over you, "
                + ", however you are unphased by the assault.\n";
            watcher_message = "A wave of psychic energy washes over " + QTNAME(target)
                + ", however " +HE(target)+ " stands firm to the mental assault.\n"; 
            break;
            
        case 1..2:
            target_message = "A wave of psychic energy strikes you, causing an " +
               "annoying mental pain.\n";
            watcher_message = "A wave of psychic energy strikes " + QTNAME(target)
                + ", causing an annoying mental pain.\n";
            break;
            
        case 3..5:
            target_message = "A wave of psychic energy washes over you, causing you " +
               "to stagger backwards in pain.\n";
            watcher_message = "A wave of psychic energy washes over " +QTNAME(target) + 
                " causing " +HIM(target)+ " to stagger backwards in pain.\n";
            break;

        case 6..9:
            target_message = "A blast of psychic energy pierces through your mind like " + 
                "a jagged spear, causing excrutiating pain.\n";
            watcher_message = "A blast of psychic energy pierces through " +QTPNAME(target) + 
                " mind like a jagged spear, causing excrutiating pain.\n";
            break;
            
        case 10..15:
            target_message = "Hostile waves of psychic energy wash over you, buffeting " +
                "your mind and causing agonizing pain.\n";
            watcher_message = "Hostile waves of psychic energy wash over " +QTNAME(target) + 
                " buffeting " +HIS(target)+ " mind and causing agonizing pain.\n";
            break;
            
        case 16..25:
            target_message = "Hostile waves of psychic energy pound your mind viciously, " + 
                "mentally crushing you.\n";
            watcher_message = "Hostile waves of psychic energy pound " +QTNAME(target) + 
                " viciously, mentally crushing " +HIM(target)+ ".\n";
            break;
                       
        case 26..40:
            target_message = "Hostile waves of psychic energy shred your mind, " + 
                "causing severe damage.\n";
            watcher_message = "Hostile waves of psychic energy shred " + QTPNAME(target) + 
                " mind, causing severe damage.\n";
            break;
                    
        case 41..65:
            target_message = "You moan in agony as a brutal wave of psychic energy " +
                "assaults your mind, grievously shredding your sanity.\n";
            watcher_message = QCTNAME(target) + " moans in agony as a brutal wave of " +
                "psychic energy assaults "  +HIS(target)+ " mind, grievously shredding " +
                HIS(target)+ " sanity.\n";
            break;
            
        default:
            target_message = "An unforgiving wave of psychic energy crushes you with deadly " +
                "force, eviscerating your sentience and leaving your body an empty husk.\n";
            watcher_message = "An unforgiving wave of psychic energy crushes " + 
                QTNAME(target) + " with deadly force, eviscerating " +HIS(target)+ " " + 
                "sentience and leaving " +HIS(target)+ " body a collapsed, empty husk.\n";
            break;
        }
    }
        
    caster->catch_msg(watcher_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
}

/*
 * Function name: desc_harm_cast
 * Description:   Describe casting of the spell, not including damage messages.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_harm_cast(object caster, object * targets)
{
    string caster_message, target_message, watcher_message, wep_str;
    object target;
    
    target = targets[0];
    object *wep;
    /* Filter out non-staffs and wands */
    wep = filter(caster->query_tool(-1), filter_tool);

    if(!sizeof(wep))
        wep_str = "hands";
    else
        wep_str = wep[0]->short();

    caster_message = "You point your " +wep_str+ " towards " + 
        QTNAME(target) + " and project the words of power 'ricin " +
        "denthanus!'\n";
    target_message = QCTNAME(caster)+ " points " + 
        caster->query_possessive() + " " +wep_str+ " towards you and " +
        "projects mystical words of power!\n";

    watcher_message = QCTNAME(caster)+ " points " + 
        caster->query_possessive() + " " +wep_str+ " towards " + 
        QTNAME(target) + " and projects mystical words of power!\n";
    
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    caster->tell_watcher(watcher_message, targets, ({ caster }) + targets);    
}

/*
 * Function:    resolve_harm_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_harm_spell(object caster, object *targets, int *resist, int result)
{
}

/*
 * Function name: hook_no_ingredients_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have the right ingredients
 * Returns:       The message to print.
 */
public void
hook_no_ingredients_fail(mixed * ingredients_needed)
{
    write("You need to quaff a ricindenthanus potion to be able to " +
        "cast psychic blast.\n");
}
