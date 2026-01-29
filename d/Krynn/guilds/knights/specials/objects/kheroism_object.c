/*
 * Knight Heroism Object
 * 
 * This object handles the actual heroism aspect and is implemented
 * as a poison to prevent players from abusing it via death, and
 * linkdead, etc.
 *
 * 3/12/2009 - Balance recommended the following changes
 *    Adding a random timer to the duration of kheroism.
 *    Reducing the heal from 50% to 30%
 *    Removing kheroism effects when Knight is relaxed from combat
 */
 
inherit "/std/poison_effect";

#include "/d/Krynn/common/defs.h"
#include "../../guild.h"
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <poison_types.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define HERO_SUBLOC   "hero_subloc"

// Global variables
public int      check_alarm;
public int      removal_alarm;
public int      strength_bonus;
public int      discipline_bonus;
public int      heroism_duration = 300;
public int      heroism_cooldown = 3600;

// Prototypes
public void     remove_heroism_benefits();
public int      query_heroism_total_duration();
static int      query_str_bonus(object player);
static int      query_dis_bonus(object player);


public void
set_heroism_duration(int duration)
{
    int quarter_duration = duration / 4;
    // we need to randomize the time so that it's not so predictable    
    heroism_duration = 3 * quarter_duration + random(quarter_duration)
        + random(quarter_duration);
    set_time(query_heroism_total_duration());
}

public int
query_heroism_duration()
{
    return heroism_duration;
}

public void
set_heroism_cooldown(int duration)
{
    int quarter_duration = duration / 4;
    // we need to randomize the time so that it's not so predictable    
    heroism_cooldown = 3 * quarter_duration + random(quarter_duration) 
                     + random(quarter_duration);
    set_time(query_heroism_total_duration());
}

public int
query_heroism_cooldown()
{
    return heroism_cooldown;
}

public int
query_heroism_total_duration()
{
    return query_heroism_duration() + query_heroism_cooldown();
}

void
create_poison_effect()
{
    add_name( ({"knight_heroism_object", "heroism object", "object",
                "knight object", "knight heroism object" }) );
    set_long("This is the Knight Heroism Object.\n");
    set_short("knight heroism object");
    
    set_interval(query_heroism_total_duration());
    set_silent(2);
    set_time(query_heroism_total_duration());
    set_damage(({ POISON_USER_DEF, 15 }));
    set_strength(100);
    set_no_cleanse(); // don't allow this poison to be cleansed
    
    // Allow the poison to recover after quitting or LD
    recovery = 1;
}

public void
start_heroism_benefits(int initial)
{
    // Heroism has a few benefits
    // 1. Adds 100 Quickness to the Knight
    poisonee->add_prop(LIVE_I_QUICKNESS,
        poisonee->query_prop(LIVE_I_QUICKNESS) + 100);
    // 2. Increases their Strength and Discipline by 50%
    strength_bonus = query_str_bonus(poisonee);
    poisonee->set_stat_extra(SS_STR, 
        poisonee->query_stat_extra(SS_STR) + strength_bonus);
    discipline_bonus = query_dis_bonus(poisonee);
    poisonee->set_stat_extra(SS_DIS,
        poisonee->query_stat_extra(SS_DIS) + discipline_bonus);
        
    if (initial)
    {
        // 3. Removes all Fatigue
        poisonee->set_fatigue(poisonee->query_max_fatigue());
        // 4. Heals 30% of hit points
        poisonee->heal_hp((poisonee->query_max_hp() * 3) / 10);
    }
    
    // Add the sublocations
    poisonee->add_prop("_knight_hero_prop", 1);
    poisonee->add_subloc(HERO_SUBLOC, TO);

    if (initial)
    {
        poisonee->catch_msg("You feel a divine peace as you call upon your inner "
            + "reserves and feel strengthened. You look at your wounds and you "
            + "feel them close. You continue the fight with renewed vigour "
            + "and heroism!\n");
        tell_room(environment(poisonee), QCTNAME(poisonee)
            + " looks invigorated as a peaceful expression comes across "
            + poisonee->query_possessive() + " face and looks renewed in "
            + "the battle against the forces of evil!\n", ({ poisonee }));
    }
}

public void
remove_pending_alarms()
{
    remove_alarm(check_alarm);
    remove_alarm(removal_alarm);
    check_alarm = 0;
    removal_alarm = 0;
}

public void
check_relaxed_state()
{
    if (!objectp(poisonee))
    {
        return;
    }
    
    send_debug_message("kheroism", "Checking relaxed state.");

    if (query_time_left() < query_heroism_cooldown())
    {
        // If we're already in the cooldown, we simply remove
        // the alarm so that it won't be checked again.
        remove_pending_alarms();
        return;
    }
    
    if (poisonee->query_relaxed_from_combat())
    {
        send_debug_message("kheroism", "Removing kheroism because "
            + "relaxed from combat.");
        remove_heroism_benefits();
        
        // We need to reset the duration and cooldown
        int total = query_heroism_total_duration();
        heroism_cooldown = query_time_left();
        heroism_duration = total - heroism_cooldown;
    } 
}

/*
 * Function name: start_poison
 * Description  : This function simply starts the poison working.  Until the
 *                poison is acivated, it is a simple object. Once activated,
 *                the poison will disappear after 'time' seconds.
 * Arguments    : object poisoner - the living that is responsible for the
 *                    poisoning of this player. This could be an NPC or real
 *                    player, if any.
 */
public varargs void
start_poison(object poisoner)
{
    ::start_poison(poisoner);
    
    // After the poison has been started, poisonee variable is
    // properly set.    
    if (query_time() > query_heroism_cooldown())
    {
        if (query_time() == query_heroism_total_duration())
        {
            send_debug_message("kheroism", "Starting kheroism initially.");
            start_heroism_benefits(1);
        }
        else
        {
            send_debug_message("kheroism", "Restarting kheroism with time "
                + "of " + query_time() + ".");
            start_heroism_benefits(0);
        }
        removal_alarm = set_alarm(itof(query_time() - query_heroism_cooldown()), 
                                 0.0, &remove_heroism_benefits());
        // As of December 21, 2013, we no longer end the kheroism benefit just because
        // they are relaxed from combat. This was making it not very useful for normal
        // day to day usage.
        // check_alarm = set_alarm(0.0, 5.0, check_relaxed_state);
    }
}

public void
timeout()
{
    poisonee->catch_msg("You feel your strength return to you and you "
        + "feel ready to perform acts of heroism again.\n");
    
    ::timeout();
}

public string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;

    if(carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
	    return "";
    }
    
    if(for_obj == carrier)
    {
	    str = "";
	}
    else
    {
	    str = C(PRONOUN(carrier))+" seems to be confident despite all, fearless "
	            + "in the face of danger, virtually unstoppable.\n";
    }
    
    return str;
}

public void
remove_heroism_benefits()
{
    // At the end of Heroism, we need to revert all the additions
    // 1. Remove 100 Quickness from the Knight
    poisonee->add_prop(LIVE_I_QUICKNESS,
        poisonee->query_prop(LIVE_I_QUICKNESS) - 100);
    // 2. Decrease their Strength and Discipline back to normal
    poisonee->set_stat_extra(SS_STR, 
        poisonee->query_stat_extra(SS_STR) - strength_bonus);
    poisonee->set_stat_extra(SS_DIS,
        poisonee->query_stat_extra(SS_DIS) - discipline_bonus);
    strength_bonus = 0;
    discipline_bonus = 0;
    
    // Reduce the Fatigue
    if (poisonee->query_fatigue() > (poisonee->query_max_fatigue() / 10))
    {
	    poisonee->set_fatigue((poisonee->query_max_fatigue() / 10));
	}
	
	// Reduce the Hit Points
    if (poisonee->query_hp() > (poisonee->query_max_hp() / 10))
    {
    	poisonee->heal_hp((poisonee->query_max_hp() / 10) - poisonee->query_hp());
	}
	
	// Reduce the Mana
    if (poisonee->query_mana() > (poisonee->query_max_mana() / 10))
    {
        poisonee->set_mana((poisonee->query_max_mana() / 10));
    }

    poisonee->remove_prop("_knight_hero_prop");
    poisonee->remove_subloc(HERO_SUBLOC);

    poisonee->catch_msg("You glance down at your many wounds, astonished that you cannot "+
      "recall getting most of them. You realize that you have survived, but you "+
      "are both physically and mentally exhausted.\n");
    tell_room(E(poisonee), QCTNAME(poisonee)+" glances down at "+ POSSESSIVE(poisonee)+
      " near-mortal many wounds, and smiles proudly as "+PRONOUN(poisonee)+" narrowly "+
      "escapes death.\n", poisonee);
      
    // Remove the strength of the poison so that damage is no longer applied
    set_strength(0);

    // remove the alarms so that it won't be called again.
    remove_pending_alarms();
}

/*
 * Function name: query_poison_recover
 * Description  : To add more information to the recover string, you should
 *                mask this function to return that information. Do not
 *                make a call to ::query_poison_recover!
 * Returns      : string - the extra recover string.
 */
public string
query_poison_recover()
{
    return sprintf("%d#%d#%d", query_time_left(), query_heroism_duration(),
                   query_heroism_cooldown());
}

/*
 * Function name: init_posion_recover
 * Description  : To add more information to the recover string, you should
 *                mask this function to process that information after you
 *                have added it with query_poison_recover().
 * Arguments    : string arg - the extra recover string.
 */
public void
init_poison_recover(string arg)
{
    int real_time_left;
    
    sscanf(arg, "%d#%d#%d", real_time_left, heroism_duration, 
           heroism_cooldown);
    
    set_time(real_time_left);
    
    send_debug_message("heroism", "Setting time left to "
        + real_time_left);
}

// Utility Functions for Determining Bonus. These are the same
// Functions that are being used by Gladiators
public int
query_stat_bonus(object player, int stat)
{
    // The goal of this function is to increase the F_STR_FACTOR aid
    // by 20%. This is done by modifying and plugging in the numbers
    // based on the current F_STR_FACTOR formula: ((600 + (str) * 4) / 10)    
    int base, modifier;
    float boost;
    
    base  = player->query_base_stat(stat);
    boost = 1.20; // gives 20% bonus
    modifier = ftoi(150.0 * (boost - 1.0) + (itof(base) * boost));    
    
    return modifier - base;
}

static int
query_str_bonus(object player)
{
    return query_stat_bonus(player, SS_STR);
}

static int
query_dis_bonus(object player)
{
    return query_stat_bonus(player, SS_DIS);
}
