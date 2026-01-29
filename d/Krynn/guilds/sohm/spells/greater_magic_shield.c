/*
 * Greater magic shield for WoHS, based on the stoneskin spell 
 *
 * Coded by Arman 2016.
 *
 * Casting restrictions removed to take into account
 * disparity in mage guild style defensive skills compared to
 * melee guild defensive skills.
 * Arman, August 2021
 */
 
#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"
#include CLOCKH

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "stoneskin";

#include  "/d/Krynn/guilds/wohs/wohs_moon_benefit.h";
#include "sohm_spell_functions.h"

/*
 * Function:    config_stoneskin_spell
 * Description: Config function for stoneskin spells. Redefine this in your
 *              own stoneskin spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_stoneskin_spell()
{
    set_spell_name("jennufethos");
    set_spell_desc("Greater magic shield - A shield of magic force that absorbs damage");

    // 'normal' combat aid for this spell is 40.0
    // Night of the Eye maximum is 56.0 caid, modified
    // through query_spell_combat_aid_modifier() below
    // set_spell_combat_aid(40.0);

    set_spell_combat_aid(56.0);
    set_spell_can_be_renewed(1);
    set_spell_fail("Your attempt to cast the spell fails, fizzling harmlessly.\n");
    set_spell_element(SS_ELEMENT_AIR, 50);
    set_spell_form(SS_FORM_ABJURATION, 60);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_3);
    set_spell_task(TASK_HARD);    

    // Can cast greater magic shield on themself or another living
    set_spell_target(spell_target_one_present_living);

    // Spell effect object
    set_spell_object(SOHM_SPELL_OBJS + "greater_shield_obj");
}

/*
 * Function:    query_stoneskin_ingredients
 * Description: This function defines what components are required for
 *              this stoneskin spell.
 */
public string *
query_stoneskin_ingredients(object caster)
{
    return ({ "chokecherry", "chantrelle" });
}

/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{

/*  Moon phase bonuses:
 *  Night of the Eye (all three moons full): 40% bonus (56.0 caid)
 *  
 *  Maximum benefit (25%): full (50 caid)
 *  partial benefit (10%): waxing/waning gibbous (44 caid)
 *  no benefit: waxing/waning half (40 caid)
 *  partial penalty (-10%): waning/waxing crescent (36 caid)
 *  Full penalty (-25%): new (30 caid)
 *  
 *  See ~guilds/wohs/doc/WoHS.txt for specifics. 
 */

    // Modify combat aid depending on phase of the magic moons
    string moon_bonus = SOHM_MANAGER->query_wohs_moon_phase_aid(TP);
    float caid_mod, moon_mod;

    if(!moon_bonus)
       moon_bonus = "none";
    if(TP->query_wohs_alignment_penalty())
       moon_bonus = "penalty";

    switch(moon_bonus)
    {
        case "night of the eye":
          moon_mod = 1.0;
          break;
        case "maximum":
          moon_mod = 0.893;
          break;
        case "partial":
          moon_mod = 0.786;
          break;
        case "none":
          moon_mod = 0.715;
          break;
        case "partial_penalty":
          moon_mod = 0.643;
          break;
        case "penalty":
          moon_mod = 0.536;
          break;
     }

     // If a team member has the Stellar Alignment spell being 
     // maintained, the moon penalty is nullified.
     if(check_stellar_alignment_benefit(TP) && (moon_mod < 0.715))
          moon_mod = 0.715; 
 
     caid_mod = 100.0 * moon_mod;
     // DEBUG("Caid_mod: " +ftoi(caid_mod)+ ", moon bonus: "+moon_bonus+ ".");

     return caid_mod;
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if(SOHM_MANAGER->too_many_spells_memorised(caster))
    {
        caster->catch_tell("You have more spells memorised than you are capable of " +
            "mentally handling. You need to balance your memorised spell list before " +
            "you can cast spells again.\n");
        return 0;
    }

    if(strlen(query_restricted_advanced_spells(caster, targets)))
    {
        // Allow spell to be renewed
        if("/d/Krynn/guilds/sohm/spells/greater_magic_shield"->has_spell_object(caster))
            return 1;

        caster->catch_tell("You cannot cast this while concentrating on the " +
            query_restricted_advanced_spells(caster, targets)+ " spell.\n");
        return 0;
    }
       
    return 1;
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
    return SOHM_MANAGER->query_memorised_spell(player,"jennufethos_memorised");
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
    string caster_message, watcher_message;

        caster_message = "You swifty trace a large circular ward in the air while chanting " +
            "'Jennufethos!'\n";
        watcher_message = QCTNAME(caster) + " swiftly traces a large circular ward in the air " +
           "while chanting mystical words of magic.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());    
}

/*
 * Function:    resolve_stoneskin_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_stoneskin_spell(object caster, mixed * targets, int * resist, int result)
{
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("Your are already protected by a shield of magical force!\n");
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
    write("You are missing a component to create a shield of magical force.\n");
}

