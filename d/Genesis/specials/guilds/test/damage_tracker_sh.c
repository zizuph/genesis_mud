/*
 * Damage Tracker Shadow
 * 
 * The purpose of this shadow is to track the amount of damage that a
 * particular person is dealing. It does this by adding a shadow
 * upon attack or attacking to the opponent. The opponent's shadow
 * will report back every time there is a hit_me
 *
 * Created by Petros, January 2009
 */

#pragma strict_types
#pragma save_binary
#pragma no_inherit


#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <filter_funs.h>

inherit "/std/shadow";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define LOGFILE     "/d/Genesis/specials/guilds/test/log/dps_totals"

// Global Variables
public int          total_damage = 0;
public int          begin_time = 0;
public int          is_tracking = 0;
public int          prevent_damage = 1; // by default we should prevent damage
public int *        all_damage = ({ }); // to keep track of standard deviation

// Prototypes
public varargs void         report_damage_tracker_dps(string file = 0);

public int
has_damage_tracker_shadow()
{
    return 1;
}

public void
remove_damage_tracker_shadow()
{
    report_damage_tracker_dps(LOGFILE);
    remove_shadow();
}

public void
set_is_tracking(int tracking)
{
    is_tracking = tracking;
}

public int
query_is_tracking()
{
    return is_tracking;
}

public void
set_prevent_damage(int prevent)
{
    prevent_damage = prevent;
}

public int
query_prevent_damage()
{
    return prevent_damage;
}

public varargs void
report_damage_tracker_dps(string file = 0)
{
    int duration, dps;
    string text;
    
    if (!query_is_tracking() || begin_time == 0 || total_damage == 0)
    {
        return;
    }
    
    duration = time() - begin_time;
    if (duration == 0)
    {
        // Can't divide by 0.
        return;
    }
    dps = ftoi( itof(total_damage) / itof(duration) );
    text = capitalize(shadow_who->query_real_name()) + " has dealt "
      + total_damage + " damage in " + duration
      + " seconds for a total DPS of " + dps + ".";
    send_debug_message("damage_tracker_totals", text, file);
    tell_room(environment(shadow_who), text + "\n");
}

public void
reset_dps_counter()
{
    begin_time = time();
    total_damage = 0;
    all_damage = ({ });
}

public void
finish_dps_counter()
{
    report_damage_tracker_dps(LOGFILE);
    reset_dps_counter();
}

public void
ensure_damage_tracker_shadow(object * others)
{
    foreach (object other : others)
    {
        if (other->has_damage_tracker_shadow())
        {
            continue;
        }
        setuid();
        seteuid(getuid());
        clone_object(MASTER)->shadow_me(other);        
    }
}

public void
hook_stop_tracking_event_occurred()
{
    // Ok, if there is a stopping event, there are two possibilities
    // 1. If you're a tracking shadow, you reset the dps counter
    // 2. If you're not tracking, you remove yourself
    //
    // A stopping event is when there is no combat involving a
    // tracking shadow.
    object * others;
    
    others = FILTER_LIVE(all_inventory(environment(shadow_who)));
    others = others - ({ shadow_who });
    others = filter(others, &operator(==)(shadow_who) 
                    @ &->query_attack());

    if (query_is_tracking())
    {
        if (!sizeof(others) && !shadow_who->query_attack())
        {
            // If no one is attacking me, and I'm not attacking anyone
            // I am done.
            finish_dps_counter();
        }
        else
        {
            ensure_damage_tracker_shadow(others);
        }
    }
    else
    {
        object target;
        
        target = shadow_who->query_attack();
        if (!sizeof(others)
            && (!target || !target->query_is_tracking()))
        {
            // If I'm not attacking someone who is tracking
            // and no one tracking is attacking me, I am done.
            set_alarm(0.0, 0.0, &remove_damage_tracker_shadow());
        }
    }
}

/*
 * Function name:   attacked_by
 * Description:     This routine is called when we are attacked.
 * Arguments:       ob: The attacker
 */
public void
attacked_by(object ob)
{
    ensure_damage_tracker_shadow( ({ ob }) );
    
    reset_dps_counter();
    shadow_who->attacked_by(ob);
}

/*
 * Function name:   attack_object
 * Description:     Start attacking, the actual attack is done in heart_beat
 * Arguments:       The object to attack
 */
public void
attack_object(object ob)
{
    ensure_damage_tracker_shadow( ({ ob }) );
    
    reset_dps_counter();
    shadow_who->attack_object(ob);
}

/*
 * Function name:   hit_me
 * Description:     Called to make damage on this object. The actually
 *                  made damage is returned and will be used to change
 *                  the score of the aggressor.
 * Arguments:       wcpen         - The wc-penetration
 *                  dt            - damagetype, use MAGIC_DT if ac will not
 *                                  help against this attack.
 *                  attacker      - Object hurting us
 *                  attack_id     - Special id saying what attack hit us. If 
 *                                  you have made a special attack, let the 
 *                                  id be -1
 *                  target_hitloc - Optional argument specifying a hitloc
 *                                  to damage.  If not specified or an
 *                                  invalid hitloc is given, a random
 *                                  one will be used.
 * Returns:         The hitresult as given by the external combat object
 */
varargs public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id, int target_hitloc = -1)
{
    mixed results;
    
    results = shadow_who->hit_me(wcpen, dt, attacker, attack_id, target_hitloc);
    if (sizeof(results) < 5)
    {
        return ({ 0, 0, 0, 0, 0 });
    }
    
    // ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    if (results[3] > 0)
    {
        attacker->add_damage_dealt(results[3]);
        if (query_prevent_damage())
        {
            // Heal the damage done so that the fight can continue.
            shadow_who->heal_hp(results[3]);
        }
    }
    
    return results;
}

public void
heal_hp(int hp)
{
    shadow_who->heal_hp(hp);
    object prev = previous_object();
    if (!objectp(prev))
    {
        return;
    }
    
    object attacker;
    if (IS_WEAPON_OBJECT(prev))
    {
        attacker = prev->query_wielded();
    }
    else if (IS_ARMOUR_OBJECT(prev))
    {
        attacker = prev->query_worn();
    }
    
    if (objectp(attacker))
    {
        attacker->add_damage_dealt(-hp);
        send_debug_message("extra_damage",
            capitalize(attacker->query_real_name()) + " has dealt "
          + (-hp) + " extra damage.");
        if (query_prevent_damage())
        {
            shadow_who->heal_hp(-hp);
        }
    }
}

public void
add_damage_dealt(int damage)
{
    total_damage += damage;
    all_damage += ({ damage });
    if (query_is_tracking())
    {
        send_debug_message(shadow_who->query_real_name() + "_damage_track",
            capitalize(shadow_who->query_real_name()) + " has dealt "
          + damage + " damage.");
    }
}

/*
 * Function name:   do_die
 * Description:     Called from enemy combat object when it thinks we died.
 * Arguments:       killer: The enemy that caused our death.
 */
public void
do_die(object killer)
{
    killer->hook_stop_tracking_event_occurred();
    // Let the room know that the battle has ended.
    environment(shadow_who)->notify_death_occurred(killer, shadow_who);
    
    shadow_who->do_die(killer);
}

/*
 * Function name: stop_fight
 * Description  : Makes this living stop fighting others.
 * Arguments    : mixed elist - the enemy or enemies to stop fighting.
 */
public void
stop_fight(mixed elist)
{
    shadow_who->stop_fight(elist);
    object prev = previous_object();
    send_debug_message("damage_tracker_sh", MASTER_OB(prev));
    if (objectp(prev)
        && (IS_ROOM_OBJECT(prev) || MASTER_OB(prev) == "/cmd/wiz/normal"))
    {
        // Only test rooms and wizards who stop the fights should trigger
        // the event. Other stopping events shouldn't trigger this.
        set_alarm(0.0, 0.0, &hook_stop_tracking_event_occurred());
    }
}

/*
 * Function name: move_living
 * Description:   Posts a move command for a living object somewhere. If you
 *                have a special exit like 'climb tree' you might want to
 *                use set_dircmd() and set it to 'tree' in the room to allow
 *                teammembers to follow their leader.
 * Arguments:     how:      The direction of travel, like "north".
 *                          "X" for teleportation, team does not follow.
 *                          "M" if you write leave and arrive messages yourself.
 *                to_dest:  Destination
 *                dont_follow: A flag to indicate group shall not follow this
 *                          move if this_object() is leader
 *                no_glance: Don't look after move.
 *
 * Returns:       Result code of move:
 *                      0: Success.
 *
 *                      3: Can't take it out of it's container.
 *                      4: The object can't be inserted into bags etc.
 *                      5: The destination doesn't allow insertions of objects.
 *                      7: Other (Error message printed inside move() func)
 */
public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    int results;
    
    results = shadow_who->move_living(how, to_dest, dont_follow, no_glance);
    set_alarm(0.0, 0.0, &hook_stop_tracking_event_occurred());
   
    return results;       
}

/*
 * Function name: notify_enemy_leaves
 * Description  : This routine is called when an enemy leaves the room, that
 *                is, when someone leaves us. It is not called when we walk
 *                away from someone who is subsequently hunting us.
 *
 *                This routin does not actually exist. It is a trick to fool
 *                the document maker.
 * Arguments    : object enemy - the enemy who left us.
 */
void
notify_enemy_leaves(object enemy)
{
    shadow_who->notify_enemy_leaves(enemy);
    set_alarm(0.0, 0.0, &hook_stop_tracking_event_occurred());
}

public mixed
query_damage_data()
{
    int duration = 0;
    
    if (begin_time)
    {
        duration = time() - begin_time;
    }
    
    return ({ total_damage, duration, all_damage }); 
}
