/*
 * Mana regeneration spell object, based on regeneration spell object
 *
 * Created by Arman, 2017
 */

#pragma strict_types
#pragma save_binary
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "spell_obj_base";

// Defines
#define NOTIFICATION_INTERVAL   30.0
#define MANA_REGEN_SUBLOC "_mana_regen_subloc"
#define DEBUG(x)	     find_player("arman")->catch_msg("[Mana] " + x + "\n")

// Global Variables
public int        Heal_alarm    = 0;
public int        Heal_number   = 0; // number of times that player has been regenerated
public int        Heal_combat_aid = 25;
public int        Notify_timestamp = 0;
public int        regen_element_skill = SS_ELEMENT_WATER;

// Prototypes
public void         do_regeneration();

/*
 * Function:    set_regeneration_combat_aid
 * Description: Sets the combat aid that this regeneration object
 *              will perform. It translates into accelerated healing
 *              rate.
 */
public void
set_regeneration_combat_aid(int aid)
{
    Heal_combat_aid = aid;
}

/*
 * Function:    query_regeneration_combat_aid
 * Description: Returns the combat aid that this regeneration object
 *              will perform. It translates into accelerated healing
 *              rate.
 */
public int
query_regeneration_combat_aid()
{
    return Heal_combat_aid; 
}

/*
 * Function:    query_regeneratio_percentage
 * Description: Returns the percentage modifier based on the combat
 *              aid using the standard caid => percentage calculation.
 */
public int
query_regeneration_percentage()
{
    int caid = query_regeneration_combat_aid();
    // Formula for Calculating effect percentage from the combat aid (c)
    //   (100 * c) / (100 + c)
    // eg. 25% combat aid => (100 * 25) / (100 + 25) = 20%
    int percentage = max(0, min(100, (100 * caid) / (100 + caid)));
    return percentage;
}

/*
 * Function name: set_element_skill_effect
 * Description  : Allows you to set the element skill that effects the
 *                regeneration effectiveness of this spell. Defaults to
 *                SS_ELEMENT_WATER.
 * Arguments    : int element_skill  - the new SS_ELEMENT_* skill.
 */

public int
set_element_skill_effect(int element_skill)
{
    regen_element_skill = element_skill;
}

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_mana_regen_object_");
    set_short("test mana regen object");    
    set_long("This is a mana regen spell object. It regenerates "
      + "the caster's mana.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
      "created by the test mana regen spell.\n");
    set_spell_effect_desc("regenerate mana");  

}

/*
 * Function:    setup_spell_effect
 * Description: This is called to set up all the things for the
 *              spell. Must call the parent's setup_spell_effect
 *              in order to get the maintainence stuff.
 */
public int
setup_spell_effect()
{
    int result = ::setup_spell_effect();
    if (!result)
    {
	return result;
    }

    int power = max(2, query_spell_effect_power());
    // ~24 minutes
    // int duration = ftoi(log(itof(power)) * 240.0);

    set_dispel_time(get_default_spell_time());

    // Combat aid determines the amount that should be healed per interval
    float aid = query_spell_effect_input();

    if (aid)
    {
	set_regeneration_combat_aid(ftoi(aid));
    }

    // Set the actual alarm that will perform the regeneration as outlined
    // in formulas.h (every 20 seconds currently).  
    float interval = itof(F_INTERVAL_BETWEEN_MANA_HEALING);  

    remove_alarm(Heal_alarm);
    Heal_alarm = set_alarm(interval, interval, do_regeneration);

    return result;
}


/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to the target.
 */
public void
hook_spell_effect_started()
{
    object target = query_effect_target();

    if (!objectp(target))
    {
	return;
    }
    object caster = query_effect_caster();

    string caster_message = "As you complete your spell, "
    + "you sense your mind recovering at an increased speed. ";
    string target_message = "\n";
    string watcher_message = QCTNAME(caster)+ " blinks, and seems to look " +
    "mentally sharper.\n";

    if (target == query_effect_caster())
    {
	caster->catch_msg(caster_message + target_message);
    }
    else
    {
	caster->catch_msg(caster_message + "\n");
	target->catch_msg(target_message);
    }
    tell_room(environment(target), watcher_message, ({ target, caster }));
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    object target = query_effect_target();
    if (!objectp(target))
    {
	return;
    }

    target->catch_tell("The mana regeneration spell ends.\n");
    tell_room(environment(target), QCTNAME(target)+ " seems to look less " +
      "mentally sharp.\n",
      ({ target }));
}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading()
{
    object target = query_effect_target();
    if (!objectp(target))
    {
	return;
    }

    target->catch_tell("You sense the mana regeneration spell fading.\n");
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained()
{
    object caster = query_effect_caster();

    if (objectp(caster))
    {
	caster->catch_tell("You are mentally unable to maintain "
	  + "the mana regeneration spell.\n");
    }    
}

/*
 * Function:    hook_describe_regeneration
 * Description: Mask this to give messages for when the target gets healed
 *              by the regeneration effect.
 */
public void
hook_describe_regeneration(object target, int amount)
{       
    target->catch_tell("You feel mentally invigorated.\n");
}

/*
 * Function:    query_mana_regen_subloc_description
 * Description: When someone examines a person with this spell effect,
 *              they will see whatever is returned by this function.
 */
public string
query_mana_regen_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
	return  "You have a spell of mana regeneration on you.\n";
    else
	return capitalize(on->query_pronoun()) + " is surrounded " +
	"by a mana regeneration spell.\n";
}

// Subloc Information

/*
 * Function name: enter_env
 * Description  : When we enter an interactive environment, add a subloc to
 *                indicate that the person has a beating heart now
 * Arguments    : object to - the object we are entering.
 *                object from - the object we come from.
 */
void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (interactive(to))
    {
	to->add_subloc(MANA_REGEN_SUBLOC, this_object());        
    }
}

/*
 * Function name: leave_env
 * Description  : This function is called each time this object leaves an
 *                old environment. If you mask it, be sure that you
 *                _always_ call the ::leave_env(dest, old) function.
 * Arguments    : object old  - the location we are leaving.
 *                object dest - the destination we are going to. Can be 0.
 */
public void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);

    if (interactive(old))
    {
	old->remove_subloc(MANA_REGEN_SUBLOC);
    }
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    string data;

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if (subloc != MANA_REGEN_SUBLOC)
    {
	return "";
    }

    return query_mana_regen_subloc_description(on, for_obj);
}

public nomask int
calculate_heal_amount(object target)
{
    // Mana regen is based on the formula used by the regeneration
    // spell.
    //
    // We base the amount of healing on the following steps:
    // 1. Use F_PENMOD(40, 100) to start with 280 Penetration value
    // 2. Use F_NEW_DAMAGE(280, 60, 60) to get 160 as the starting value.
    //
    // Given this, we will calculate the actual amount for the aid given. For
    // 100% combat aid, this should equal 80. For 25%, this should equal 32.
    //
    // Input Variables will be:
    // A. Player Wisdom (variable => WIS)
    // B. Player's Water Skill (variable => WATER)
    // C. Starting Damage Amount (variable => DAM)
    //
    // We make adjustments as below (before adjusted for aid):
    // (DAM / 2) + (MIN(100, MAX(WIS - 50, 0)) * DAM / 400) + (MIN(100, WATER) * DAM / 400)
    //
    // In other words, half the amount will be guaranteed. A quarter will be based on
    // the player's wisdom, and the other quarter will be based on the player's water
    // skill.
    int penetration = F_PENMOD(40, 100);
    int max_healing = F_NEW_DAMAGE(penetration, 60, 60);
    int wisdom = target->query_stat(SS_WIS);
    int water_skill = target->query_skill(regen_element_skill);

    int adjusted_healing = (max_healing / 2) + (min(100, max(wisdom - 50, 0)) * max_healing / 400)
    + (min(100, water_skill) * max_healing / 400);

    send_debug_message("regeneration_obj", "Initial adjusted healing: " + adjusted_healing);

    // Adjust healing for actual interval
    adjusted_healing = adjusted_healing * F_INTERVAL_BETWEEN_MANA_HEALING / 5;

    send_debug_message("regeneration_obj", "Adjusted healing after adjusting for interval: " +
      adjusted_healing);    

    // Adjust healing for combat aid
    adjusted_healing = query_regeneration_percentage() * adjusted_healing / 100;
    send_debug_message("regeneration_obj", "Adjusted healing after adjusting for combat aid: " +
      adjusted_healing);        

    // Adjust healing for if the player is in combat or not relaxed. If that's the case, then we
    //reduce the regeneration by a factor.

    if (!target->query_relaxed_from_combat()) 
    {
	adjusted_healing = 2 * (adjusted_healing / 3);
	send_debug_message("regeneration_obj", "Adjusted healing after adjusting for not being relaxed: " + 
	  adjusted_healing);                
    }

    // Adjust healing dependant on how soaked a player is (drinking water helps speed recovery).

    int maxsoak = target->query_prop(LIVE_I_MAX_DRINK);
    int soaked = max(1, (target->query_soaked()));

    if(soaked != maxsoak)
    {
	float soaked_factor = max(1.0, (3.0 * (itof(soaked) / itof(maxsoak))));
	adjusted_healing = ftoi((itof(adjusted_healing) / 3.0) * soaked_factor);
    }   

    // Using the calculate_heal_amount results in a 400% increase in mana regeneration at 25% combat aid, 
    // Will limit mana regeneration to 15% increase for 25% caid, so adjust_mana_amount will be divided 
    // by 500 and multipled by 115.

    adjusted_healing = ftoi((itof(adjusted_healing) / 500.0) * 115.0);

    /*
	DEBUG("Adjusted mana for "+target->query_real_name()+": "+adjusted_healing+", using element: "+regen_element_skill+".");
    */

    // Return the final result
    return adjusted_healing;
}

/*
 * Function:    do_regeneration
 * Description: The function that gets called every interval to heal
 *              the target.
 */
public void
do_regeneration()
{
    object target = query_effect_target();
    if (!objectp(target) || target->query_linkdead() 
      || target->query_linkdead_in_combat())
    {
	return;
    }

    int maxmana = target->query_max_mana();
    int currentmana = target->query_mana();
    if (maxmana == currentmana)
    {
	// No need for regeneration
	return;
    }

    int mana_amount = (calculate_heal_amount(target));
    int adjusted_mana_amount = min(mana_amount, maxmana - currentmana);

    target->add_mana(adjusted_mana_amount);

    if (mana_amount == adjusted_mana_amount)
    {
	/*
		DEBUG("Regenerating "+ adjusted_mana_amount + " mana point(s).");
	*/
    }
    else
    {
	send_debug_message("regeneration_obj", "Regenerating "
	  + adjusted_mana_amount + " mana point(s) instead "
	  + "of " + mana_amount + " because the target has "
	  + "full mana.");
    }

    ++Heal_number;

    // Only notify if the notification interval has passed
    if (Notify_timestamp + ftoi(NOTIFICATION_INTERVAL) < time())
    {
	hook_describe_regeneration(target, mana_amount);
	Notify_timestamp = time();
    }
}
