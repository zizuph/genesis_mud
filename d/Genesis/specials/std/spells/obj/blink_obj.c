/*
 * Standard Blink Object
 *
 * This is the spell object for the standard Genesis Magic System Blink
 * spell. It allows the caster to "blink" in and out of the material
 * plane. Effectively, the spell behaves as a move behind (Calian special)
 * in that it will force those who attack them to no longer attack.
 *
 * Specific guild implementations must inherit from this one to get
 * the standard AoB approved effects.
 *
 * Created by Petros, February 2016
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "defs.h"

inherit "/d/Genesis/specials/std/spells/obj/spell_obj_base";

// Global Variables
private string BLINK_SUBLOC = "_blink_spell_subloc";
private int blink_alarm = 0;
private float blink_interval = 30.0;

// Hook Prototypes
public void hook_spell_effect_started();
public void hook_spell_effect_ended();
public void hook_spell_effect_warn_fading();
public void hook_spell_effect_not_maintained();
public string query_blink_subloc_description(object on, object for_obj);
public void hook_describe_blink_action(object player, object friend, object * enemies);
public void hook_describe_blink_no_attack_room(object player, object friend, object * enemies);

// Other Prototypes
public void do_blink_action(object player, object friend);
public void stopattack_object(object enemy, object blinker, object friend);
public void reattack_object(object enemy, object friend);
public int is_valid_blink_target(object teammate, object player);
public int is_attacking_this_living(object enemy, object player);
public void set_blink_interval(float interval);
public float query_blink_interval();

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_blink_object_");
    set_short("blink spell object");    
    set_long("This is the standard blink spell's object. It causes "
        + "one to blink in and out of the material plane.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the blink spell.\n");
    set_spell_effect_desc("randomly teleport during combat");
    
    set_dispel_time(1800);
}

/*
 * Function:    query_blink_interval
 * Description: Returns the time in between blink checks.
 */
public float
query_blink_interval()
{
    return blink_interval;
}

/*
 * Function:    set_blink_interval
 * Description: Sets the blink interval for this spell object.
 */
public void
set_blink_interval(float interval)
{
    blink_interval = interval;
}

/*
 * Function:    trigger_blink_action
 * Description: Triggered by the blink_alarm. Will also reset the
 *              alarm at the end of its logic.
 */
public void
trigger_blink_action()
{
    object player = query_effect_target();
    // Start a random interval alarm that will continuously check
    // if person is:
    // 1. In combat
    // 2. In a team
    // 3. Currently tanking
    // If so, it will trigger a move behind action to focus on a
    // random teammate (if more than one teammate).
    object * teammates = filter(player->query_team_others(), &is_valid_blink_target(,player));
    if (sizeof(teammates) > 0)
    {
        object * attackers = filter(all_inventory(environment(player)), &is_attacking_this_living(,player)); 
        if (sizeof(attackers) > 0)
        {
            // Select a random teammate to blink to.
            object random_teammate = teammates[random(sizeof(teammates))];
            set_alarm(0.0, 0.0, &do_blink_action(player, random_teammate));
        }
        else
        {
            send_debug_message("blink_obj", capitalize(player->query_real_name()) + " has no attackers. No blink will occur.");
        }
    }
    else
    {
        send_debug_message("blink_obj", capitalize(player->query_real_name()) + " has no teammates. No blink will occur.");
    }

    // We randomize the next interval a bit. It'll range from 0.5x to 1.5x
    // of the actual query interval set.
    float next_interval = player->query_speed(query_blink_interval() / 2.0);
    next_interval += rnd() * next_interval + rnd() * next_interval;

    remove_alarm(blink_alarm);
    send_debug_message("blink_obj", capitalize(player->query_real_name())
                       + " will attempt another blink in " + sprintf("%.2f", next_interval)
                       + " (" + sprintf("%.2f", query_blink_interval()) + ") seconds.");
    blink_alarm = set_alarm(next_interval, 0.0, &trigger_blink_action());
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

    // The spell passes its own query_blink_interval(). We will use this
    // to set it on the spell object.
    float interval;
    if (interval = query_spell_effect_input())
    {
        set_blink_interval(interval);
    }
    
    remove_alarm(blink_alarm);
    // We start the first blink attempt a random amount of time in the future based
    // on the blink interval.
    blink_alarm = set_alarm(rnd() * query_blink_interval(), 0.0, &trigger_blink_action());
    
    return result;
}

public varargs int
dispel_spell_effect(object dispeller)
{
    int result = ::dispel_spell_effect(dispeller);
    if (!result)
    {
        return result;
    }
    
    remove_alarm(blink_alarm);
    blink_alarm = 0;
    
    return 1;
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
        to->add_subloc(BLINK_SUBLOC, this_object());        
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
        old->remove_subloc(BLINK_SUBLOC);
    }
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    string data;

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (subloc != BLINK_SUBLOC)
    {
        return "";
    }
    
    return query_blink_subloc_description(on, for_obj);
}

/* 
 * Function:     is_attacking_this_living 
 * Description:  Should return whether enemy attacks player. 
 * Arguments:    object enemy    -  the enemy 
 *               object player   -  the possible victim 
 * Returns:      1 if enemy is attacking player, 0 otherwise. 
 */ 
public int 
is_attacking_this_living(object enemy, object player) 
{ 
    return enemy->query_attack() == player; 
} 

/* 
 * Function:     is_valid_blink_target
 * Description:  Should return whether the person is a teammate and
 *               they're currently present and available to be blinked
 *               behind.
 * Arguments:    object teammate    -  the teammate to blink behind
 *               object player      -  the person blinking
 * Returns:      1 if player can blink behind teammate, 0 otherwise
 */ 
public int
is_valid_blink_target(object teammate, object player)
{
    if (!objectp(player) || !objectp(teammate))
    {
        return 0;
    }
    // Condition: Check that the teammate is in player's team.
    object * teammates = player->query_team_others();
    if (!pointerp(teammates)
        || sizeof(teammates) == 0
        || !IN_ARRAY(teammate, teammates))
    {
        return 0;
    }
    // Condition: Check that the teammate is actually in the same
    //            room.
    if (environment(teammate) != environment(player))
    {
        return 0;
    }
    
    return 1;
}    

/* 
 * Function:      reattack_object 
 * Description:   Called to make an enemy re-attack someone whom 
 *                the blinker moves behind
 * Arguments:     object enemy   - the person attacking 
 *                object friend  - the person attacked 
 */ 
public void 
reattack_object(object enemy, object friend) 
{ 
    enemy->stop_fight(friend); 
    enemy->attack_object(friend); 
} 

/* 
 * Function:      stopattack_object 
 * Description:   Called to make an enemy stop fighting a blinker who 
 *                blinks behind someone in a ROOM_M_NO_ATTACK room. 
 * Arguments:     object enemy    - the person attacking 
 *                object blinker  - the person who moved behind 
 *                object friend   - person who is now in front 
 */ 
public void 
stopattack_object(object enemy, object blinker, object friend) 
{ 
    enemy->stop_fight(blinker); 
    blinker->stop_fight(enemy); 
    if (friend->query_attack() == enemy) 
    { 
        enemy->stop_fight(friend); 
        enemy->attack_object(friend); 
    } 
} 

/*
 * Function     : do_blink_action
 * Description  : Actual code that executes blink action
 * Arguments    : player - player executing the blink action
 *                friend - the friend who will tank
 * Returns      : nothing
 */
public void
do_blink_action(object player, object friend)
{
    object * enemies;
    string current_adverb;
    
    object oldtp = this_player();
    set_this_player(player);
    // Get the list of people attacking this player
    enemies = filter(all_inventory(environment(player)), &is_attacking_this_living(,player)); 

    object room = environment(player);
    if (room->query_prop(ROOM_M_NO_ATTACK)) 
    {
        // In a ROOM_M_NO_ATTACK room, we just stop all the combat.
        map(enemies, &stopattack_object(,player, friend));
        hook_describe_blink_no_attack_room(player, friend, enemies);
    } 
    else 
    {
        map(enemies, &reattack_object(,friend));
        hook_describe_blink_action(player, friend, enemies);
    } 
    set_this_player(oldtp);            
}

// HOOK FUNCTIONS
/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started()
{
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("You begin to move in and out of the material plane.\n");
        tell_room(environment(target), QCTNAME(target) + " begins to move "
            + "in and out of the material plane.\n", ({ target }));
    }    
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

    if (objectp(target))
    {
        target->catch_tell("You stop moving in and out of the material plane.\n");
        tell_room(environment(target), QCTNAME(target) + " seems to solidify "
            + "in view.\n", ({ target }));
    }
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
    
    if (objectp(target))
    {
        target->catch_tell("You sense yourself starting to materialize fully "
                           + "in the material plane.\n");
    }
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
            + "your blinking in and out of the material plane.\n");
    }    
}

/*
 * Function:    query_blink_subloc_description
 * Description: When someone examines a person with this spell effect,
 *              they will see whatever is returned by this function.
 */
public string
query_blink_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
        return  "Your body is phasing in and out of the material realm.\n";
    else
        return capitalize(on->query_pronoun()) + " seems to be periodically "
            + "fading slightly from view.\n";
}

/*
 * Function:    hook_describe_blink_action
 * Description: When someone successfully blinks behind someone else,
 *              they will see the messages described in this function.
 * Arguments:   object player    - the person who is blinking
 *              object friend    - the person who is going to be tanking
 *              object * enemies - the list of enemies that will attack the
 *                                 friend instead.
 */
public void
hook_describe_blink_action(object player, object friend, object * enemies)
{
    player->catch_msg("You blink behind "
                      + QTNAME(friend) + " and your enemies move "
                      + "to attack " + friend->query_objective()
                      + ".\n");
    friend->catch_msg(QCTNAME(player) + " blinks behind you, and "
                      + player->query_possessive() + " enemies "
                      + "move to attack you!\n");                           
    tell_room(environment(player), QCTNAME(player) + " " 
              + " disappears and reappears behind " + QTNAME(friend) 
              + ", who is attacked by " + player->query_possessive()
              + " enemies!\n", ({ player, friend }) );
}

/*
 * Function:    hook_describe_blink_no_attack_room
 * Description: When someone successfully blinks behind someone else
 *              in a ROOM_M_NO_ATTACK room, all combat will stop. This
 *              function describes what they will see.
 * Arguments:   object player    - the person who is blinking
 *              object friend    - the person who is going to be tanking
 *              object * enemies - the list of enemies that will attack the
 *                                 friend instead.
 */
public void
hook_describe_blink_no_attack_room(object player, object friend, object * enemies)
{
    player->catch_msg("You blink behind " + QTNAME(friend) + ".\n");
    friend->catch_msg(QCTNAME(player) 
                      + " blinks behind you.\n"); 
    tell_room(environment(player), QCTNAME(player)
              + " disappears and reappears behind "
              + QTNAME(friend) + ".\n", ({ player, friend }) ); 
}
