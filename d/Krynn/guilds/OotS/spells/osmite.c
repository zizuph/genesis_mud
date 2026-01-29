/*
 * Smite AoE harm spell for OotS - Arman 2017
 */

#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../defs.h"
#include "/d/Krynn/common/defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "massharm";

#include "../oots_god_descs.h"

#define MAX_CAID           50.0
#define OMEND_CAID         15.0
#define OHERO_CAID         15.0
#define OSONG_CAID          5.0
#define BUFF_CAID          30.0

/*
 * Function:    config_massharm_spell
 * Description: Config function for harm spells. Redefine this in your
 *              own harm spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_massharm_spell()
{
    set_spell_name("osmite");
    set_spell_desc("Smite - Purify the unliving with holy wrath");

    set_spell_combat_aid(MAX_CAID);
    set_spell_task(TASK_ROUTINE);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_3);

    set_spell_time_factor(2.0);

    /* Limit spell targets */
    set_spell_target_limit(3);

    set_spell_element(SS_ELEMENT_LIFE, 40);
    set_spell_form(SS_FORM_ABJURATION, 30);
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

    // Level 9 (Cleric) spell
    if(OOTS_LEVEL(player) < 9)
    {
	return 0;
    }

    return 1;
}

/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_massharm_ingredients(object caster)
{ 
    return ({ "_oots_holy_water" });
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
    return "holy water";
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
    write("You need a phial of holy water to smite the undead!\n");
}

void
hook_use_ingredients(object *ingrs)
{
    write("A phial of holy water is consumed.\n");
}

/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{
    // modify base caid by active maintained spells.
    float total_combat_aid = MAX_CAID;
    float available_combat_aid = MAX_CAID;

    if (query_spell_apply_whitehit_aid())
    {
        total_combat_aid += itof(query_white_hit_combat_aid());
        available_combat_aid += itof(query_white_hit_combat_aid());
    }

    // If the player has defensive spells on, we reduce the
    // total combat aid provided by this spell.

    float caid_mod, align_mod;
    int caster_align = TP->query_alignment();

    if(caster_align < 1000)
    {
        align_mod = itof(caster_align) / 1000.0;
    }
    else
    {
        align_mod = 1.0;
    }

    // heal less effective if cleric is focusing on maintaining bless
    // or protect AND the unique god blessing
    if("/d/Krynn/guilds/OotS/spells/obless"->has_spell_object(TP) ||
       "/d/Krynn/guilds/OotS/spells/oprotect"->has_spell_object(TP))
    {
        available_combat_aid -= BUFF_CAID;
    }

    if("/d/Krynn/guilds/OotS/spells/oheroism"->has_spell_object(TP))
    {
        available_combat_aid -= OHERO_CAID;
    }

    if("/d/Krynn/guilds/OotS/spells/oheroism"->has_spell_object(TP))
    {
        available_combat_aid -= OMEND_CAID;
    }

    if("/d/Krynn/guilds/OotS/spells/osong"->has_spell_object(TP))
    {
        available_combat_aid -= OSONG_CAID;
    }

    caid_mod = (available_combat_aid / total_combat_aid) * 100.0;
    caid_mod = caid_mod * align_mod;
    
    return caid_mod;
}


public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
	return 0;

    if (caster->query_alignment() < 600)
    {
	caster->catch_tell("Your recent behaviours and actions do not " +
	  "align with the teachings of " +oots_god_name(caster)+ 
	  ". Your prayer goes unanswered.\n");
	return 0;
    }

    int c_aid = ftoi(query_spell_combat_aid());
    // DEBUG("Smite combat aid: " + c_aid);

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
    string caster_message, watcher_message;
    object target = targets[0];

    caster_message = "You raise your medallion of faith and call upon " 
    +oots_god_name(caster)+ " for righteous aid in smiting the unliving!\n";
    watcher_message = QCTNAME(caster) + " raises " +HIS(caster)+ " "+
    "medallion of faith and calls upon the " +oots_god_desc(caster)+ " " 
    +oots_god_name(caster)+" to smite the unliving!\n";


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

    if (!target->query_prop(LIVE_I_UNDEAD))
    {
	// DEBUG(target->short() + " not undead, no damage message.");
	return;
    }

    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    if (phurt < 0)
    {
	// Missed! give the miss messages.
	target_message = "You are unaffected by the divine azure light.\n";
	watcher_message = QCTNAME(target)+ " is unaffected by the " +
                          "divine azure light.\n";
    }
    else
    {        
	switch (phurt) // percentage hurt
	{
	case 0:
	    target_message = "The divine azure light does you no damage.\n";
	    watcher_message = "The divine azure light does no damage to " 
	       +QTNAME(target)+ ".\n"; 
	    break;

	case 1..5:
	    target_message = "The divine azure light singes you slightly.\n";
	    watcher_message = QCTNAME(target)+ " is slightly singed " +
	       "by the divine azure light.\n";
	    break;

	case 6..10:
	    target_message = "The divine azure light mildly scorches you.\n";
	    watcher_message = QCTNAME(target) + " is mildly scorched " +
               "on the " + hitloc_desc + " by the divine azure light.\n";
	    break;

	case 11..25:
	    target_message = "The divine azure light burns your " + 
               hitloc_desc + ".\n";
	    watcher_message = QCTNAME(target) + " is burnt on the " + 
               hitloc_desc + " by the divine azure light.\n";
	    break;

	case 26..35:
	    target_message = "The divine azure light seriously burns your " + 
	       hitloc_desc + ".\n";
	    watcher_message = QCTNAME(target) + " is seriously burnt " +
               "on the " + hitloc_desc + " by the divine azure light.\n";
	    break;

	case 36..45:
	    target_message = "You are painfully smited by the divine " +
	       "azure light, your " +hitloc_desc+ " burnt badly.\n";
	    watcher_message = QCTNAME(target) + " is painfully smited " +
               "by the divine azure light, " + target->query_possessive() +
               " " + hitloc_desc + " burnt badly.\n";
	    break;

	case 46..70:
	    target_message = "The radiant azure light engulfs you " +
	       "causing excrutiating pain, severely burning your " +
               hitloc_desc+ ".\n";
	    watcher_message = QCTNAME(target) + " is engulfed by the " +
	       "radiant azure light, causing severe damage to " + 
               target->query_possessive() + " " + hitloc_desc + ".\n";
	    break;

	case 71..90:
	    target_message = "The radiant azure light engulfs you, " +
               "causing excrutiating pain to your " +
	       hitloc_desc + " and grievous injuries.\n";
	    watcher_message = QCTNAME(target) + " is engulfed by the " +
	       "radiant azure light, causing excrutiating pain and " +
               "grievous injuries.\n";
	    break;

	default:
	    target_message = "You collapse to your knees as the divine " +
	       "power of the azure light purges your soul and burns " +
               "your undead body to ashes.\n";
	    watcher_message = QCTNAME(target)+ " collapses to " +
               HIS(target)+ " knees as the divine power of the azure " +
               "light purges " +HIS(target)+ " unholy soul and burns " +
	       HIS(target)+ " undead body to ashes.\n";
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
    string caster_message, target_message, watcher_message;

    caster_message = "Your medallion of faith blazes with purifying " +
       "azure light!\n";
    target_message = QCTPNAME(caster)+ " medallion of faith blazes with " +
       "a purifying azure light, a holy power antithesis to undeath!\n";
    watcher_message = QCTPNAME(caster)+ " medallion of faith blazes " +
       "with purifying azure light!\n";

    caster->catch_msg(caster_message);
    targets->catch_msg(target_message);
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
    // Check the harm spell on each target to see if they are undead
    for (int index = 0; index < sizeof(targets); ++index)
    {
	object target = targets[index];
	if (!target->query_prop(LIVE_I_UNDEAD))
	{
	    // DEBUG(target->short() + " no undead prop.");
	    // continue;
	    return;
	}
    }
    // DEBUG("Smite result: " +result);
}

public mixed *
do_massharm_damage(object caster, object target, int pen)
{
    // If not undead do no damage
    if (!target->query_prop(LIVE_I_UNDEAD))
    {
	// DEBUG(target->short() + " not undead, no damage.");
	return target->hit_me(0, MAGIC_DT, caster, -1);
    }

    return target->hit_me(pen, MAGIC_DT, caster, -1);
}

public void
hook_no_present_targets(object actor, string str)
{
    actor->catch_msg("You must first be in combat before you can call on "
    + "this prayer!\n");   
}
