/*
 * Disable Attack Effect Object
 * 
 * This is the base disable attack effect object that handles 
 * disable attack in conjunction
 * with the disable attack shadow. disable attack objects stack with one another.
 *
 * Created by Ziziph, Dec 2021
 */
 
#pragma strict_types

#include "defs.h"

inherit EFFECT_BASE_OBJ;
inherit "/d/Genesis/specials/calculations";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Prototypes
public void         set_disable_attack_combat_aid(int caid);
public void         set_disable_attack_chance(int percentage);
public void         set_disable_attack_tohit(int tohit);
public void         set_disable_attack_time(int time);
public void         hook_disable_attack_begin(object attacker, object target);
public void         hook_disable_attack_ended(object target);
public int          query_disable_attack_combat_aid(object player);

// Global Variables
static int       m_disableAttackChance = 100;
static int       m_disableAttackTohit = 100;
static int       m_time = 30;
static int*      m_attackIds = ({});


static function     gDisableAttackBegin,
                    gDisableAttackEnded,
                    gDisableAttackFailed;


public function
query_hook_disable_attack_begin()
{
    return gDisableAttackBegin;
}

public void
set_hook_disable_attack_begin(function func)
{
    gDisableAttackBegin = func;
}

public function
query_hook_disable_attack_ended()
{
    return gDisableAttackEnded;
}

public void
set_hook_disable_attack_ended(function func)
{
    gDisableAttackEnded = func;
}

public function
query_hook_disable_attack_failed()
{
    return gDisableAttackFailed;
}

public void
set_hook_disable_attack_failed(function func)
{
    gDisableAttackFailed = func;
}

/*
 * Function Name:   hook_disable_attack_failed
 * Description:     The text displayed when the disable attack fails to apply.
 * Arguments:       (object) actor - The actor of the ability
 *                  (object) target - The target of the disable attack
 * Returns:         Nothing 
 */
public void
hook_disable_attack_failed(object actor, object target)
{
} /* hook_disable_attack_failed */

/*
 * Function     : set_disable_attack_skills
 * Description  : Set the skills that will be used in calculating
 *                the strength of the disable attack
 * Arguments    : skills
 * Returns      : nothing
 */
public nomask void 
set_disable_attack_skills(mixed skills)
{
    set_effect_skills(skills);
}

/*
 * Function     : query_disable_attack_skills
 * Description  : Returns the skills being used to calculate disable attack
 * Arguments    : none
 * Returns      : Skills_used variable
 */
public nomask mixed 
query_disable_attack_skills()
{
    return query_effect_skills();
}

/*
 * Function     : set_disable_attack_stats
 * Description  : Set the stats that will be used in calculating
 *                the strength of the disable attack
 * Arguments    : stats
 * Returns      : nothing
 */
public nomask void 
set_disable_attack_stats(mixed stats)
{
    set_effect_stats(stats);
}

/*
 * Function     : query_disable_attack_stats
 * Description  : Returns the stats being used to calculate disable
                  attack strength
 * Arguments    : none
 * Returns      : Skills_used variable
 */
public nomask mixed 
query_disable_attack_stats()
{
    query_effect_stats();
}


/*
 * Function     : set_disable_attack_time
 * Description  : Set how many seconds this effect will last.                  
 * Arguments    : Time for effect.
 * Returns      : none
 */
public nomask void
set_disable_attack_time(int time)
{
    m_time = time;
}

/*
 * Function     : query_disable_attack_time
 * Description  : Query how many seconds this effect will last.                  
 * Arguments    : none
 * Returns      : Time of effect
 */
public int 
query_disable_attack_time()
{
    return m_time;
}

/*
 * Function     : set_disable_attack_attack_ids
 * Description  : Sets the specific attack IDs that are affected.
 * Arguments    : ids List of attack IDs
 * Returns      : none
 */
public nomask void
set_disable_attack_attack_ids(int* ids)
{
    m_attackIds = ids;
}

/*
 * Function     : query_disable_attack_attack_ids
 * Description  : Queries the specific attack IDs that are affected.
 * Arguments    : none
 * Returns      : List of attack IDs
 */
public nomask int*
query_disable_attack_attack_ids()
{
    return m_attackIds;
}

public void
create_disable_attack_effect()
{
}

/*
 * Function     : create_disable_attack_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
    set_name("_base_disable_attack_object_");
    add_name( ({"base_disable_attack_obj" }) );
    set_short("hidden base disable attack object");    
    set_long("A basic disable attack object. One should not be able to see it "
           + "in their inventory.\n");

    set_disable_attack_stats( TS_STR );
    set_disable_attack_skills( SS_DEFENCE );
    // 25% combat aid == 20% disable attack (at 100% attackuse)
    set_disable_attack_combat_aid(100);
    // By default disable attack always hits 100%
    set_disable_attack_chance(100);
    // By default stun is always triggered at 100%
    set_disable_attack_tohit(100);
    
    set_disable_attack_time(30);
    
    set_hook_disable_attack_begin(hook_disable_attack_begin);
    set_hook_disable_attack_ended(hook_disable_attack_ended);
    set_hook_disable_attack_failed(hook_disable_attack_failed);

    create_disable_attack_effect();

    setuid();
    seteuid(getuid());
}


// This should only affect an attack ID that is in the list.
public int
query_effect_valid(object player, object attacker, int attack_id)
{
    foreach (int id : m_attackIds)
    {
        if ((id & attack_id) > 0)
            return 1;
    }
    return 0;
} 

/*
 * Function     : set_disable_attack_chance
 * Description  : Sets the chance that the disable attack will have effect.
 * Arguments    : percentage between 0 and 100
 * Returns      : nothing
 */
public nomask void
set_disable_attack_chance(int percentage)
{
    if (percentage < 0)
    {
        percentage = 0;
    }
    else if (percentage > 100)
    {
        percentage = 100;
    }
    m_disableAttackChance = percentage;
}

/*
 * Function     : query_disable_attack__chance
 * Description  : returns the chance that the stun will succeed
 * Arguments    : player - the player who is receiving combat aid
 * Returns      : combat aid number
 */
public nomask int
query_disable_attack_chance(object player)
{
    return m_disableAttackChance;
}

/*
 * Function     : set_disable_attack_tohit
 * Description  : This sets the tohit that the disable 
                  attack will actually
 *                hit because of an external ability. For example, if
 *                a shield slam causes the disable attack, then the 
                  tohit of the shield slam would be set here.
 * Arguments    : 
 * Returns      : nothing
 */
public nomask void
set_disable_attack_tohit(int tohit)
{
    if (tohit < 0)
    {
        tohit = 0;
    }
    else if (tohit > 200)
    {
        tohit = 200;
    }
    m_disableAttackTohit = tohit;
}

/*
 * Function     : query_disable_attack_tohit
 * Description  : returns the chance that the stun will actually be
 *                triggered.
 * Arguments    : player - the player who is receiving combat aid
 * Returns      : percentage for the ability triggering the stun
 */
public nomask int
query_disable_attack_tohit(object player)
{
    return m_disableAttackTohit;
}

/*
 * Function     : set_disable_attack_combat_aid
 * Description  : Sets the disable attack combat aid which is 
 *                used to determine the blocked percentage
 * Arguments    : combat aid number
 * Returns      : nothing
 */
public nomask void
set_disable_attack_combat_aid(int caid)
{
    set_effect_combat_aid(caid);
}

/*
 * Function     : query_disable_attack_combat_aid
 * Description  : returns the disable attack combat aid for player
 * Arguments    : player - the player who is receiving combat aid
 * Returns      : combat aid number
 */
public nomask int
query_disable_attack_combat_aid(object player)
{
    int aid, chance, tohit;
    
    // The actual disable attack combat aid is modified by the 
    // disable attack chance as well as the declared miss chance
    aid = ::query_effect_combat_aid(player);
    chance = query_disable_attack_chance(player);
    tohit = query_disable_attack_tohit(player);
    send_debug_message("base_disable_attack", 
                    "Final disable attack combat aid before any "
                    + "adjustment is " + aid + ".");
    if (chance > 0)
    {
        aid = aid * 100 / chance;
    }
    send_debug_message("base_disable_attack", 
                    "Final disable attack combat aid after chance is "
                    + aid + ".");
    
    if (tohit > 0)
    {
        aid = aid * 100 / 
            (100 - convert_tohit_to_combat_aid_reduction(tohit));
    }
    send_debug_message("base_disable_attack", 
                    "Final disable attack combat aid after "
                    + "tohit/chance adjustment is " + aid + ".");
    return aid;
}

public nomask int
query_effect_combat_aid(object player)
{
    return query_disable_attack_combat_aid(player);
}

/*
 * Function     : query_stun_valid
 * Description  : Validation function to see whether this stun object is
 *                valid in the current situation
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : 0/1 - invalid/valid
 */
public int
query_disable_attack_valid(object player)
{
    return 1;
}

/*
 * Function name: remove_disable_attack_effect
 * Description:   Remove this disable_attack from a target, also removing the
 *                shadow as needed
 * Arguments:     object target - the one affected by the disable attack
 * Returns:       1/0 - effect dispelled/not dispelled
 */
varargs public int
remove_disable_attack_effect(object target)
{
    if (!target)
    {
        // We only care if the environment is a living person.
        // Master objects will simply be removed.
        send_debug_message("base_disable_attack", 
            "Master object, will not process shadow check.");
        return 0;
    }
    
    // Remove the effect from the shadow
    target->remove_disable_attack_effect(this_object());
    
    function func;
    if (functionp(func = gDisableAttackEnded))
        applyv(func, ({ target }));
    
    if (!sizeof(target->query_disable_attack_effects()) 
        && target->has_disable_attack_shadow())
    {
        send_debug_message("base_disable_attack", 
            "Removing shadow because there are no more effects.");        
        target->remove_disable_attack_shadow();
    }
    return 1;
}

/*
 * Function name: remove_object
 * Description:   Called upon object destruction. This will need to
 *                be done so that the shadow can be properly removed
 *                when there are no more effects.
 * Arguments:     none
 * Returns:       nothing
 */
public void
remove_object()
{
    foreach (object shadowobj : query_shadow_list())
    {
        remove_disable_attack_effect(shadowobj->query_shadow_who());
    }
    ::remove_object();
}

/*
/*
 * Function name: dispel_effect
 * Description:   Cause this effect to be dispelled.
 *                If the effect is removed, 1 should be returned,
 *                else 0.  Returning 0 should be a rare occurance,
 *                since there generally should not be spell effects
 *                that cannot be dispelled.
 * Arguments:     object dispeler - the person responsible for dispelling
 *                                  the effect.
 * Returns:       1/0 - effect dispelled/not dispelled
 */
varargs public int
dispel_effect(object dispeler)
{
    remove_object();
    return ::dispel_effect(dispeler);
}
    

/*
 * Function name: add_disable_attack_effect
 * Description;   Add this effect to a target
 * Returns:       1/0 - effect added/not added
 */
public int add_disable_attack_effect(object target)
{
    function func;
    
    if (random(100) >= query_disable_attack_chance(target))
    {
        // The disable attack chance did not succeed. In this case, we just
        // return.
        send_debug_message("base_disable_attack", 
            "Disable attack chance failed. Object is to be removed.");
        remove_object();
        return 0;
    }

    // Objects which cannot be stunned should not have the stun effect added.
    if (target->query_prop(LIVE_I_NO_STUN))
    {
        send_debug_message("base_disable_attack",
            "Target cannot be stunned. Object is to be removed.");
        remove_object();
        return 0;
    }

    if (target && living(target))
    {
        if (!target->has_disable_attack_shadow())
        {
            send_debug_message("base_disable_attack",
                "Did not find shadow, creating shadow.");
            object sh;
            if (target->query_npc())
            {
               sh = clone_object(DISABLE_ATTACK_NPC_SH);
            }
            else
            {
               sh = clone_object(DISABLE_ATTACK_SH);
            }
            if (!sh->shadow_me(target)) {
                send_debug_message("base_disable_attack",
                    "Could not add shadow, disable attack failed.");
                sh->remove_object();
                remove_object();
                return 0;
            }
        }
        else
        {
            send_debug_message("base_disable_attack",
                "Found disable_attack shadow.");
        }
        
        if (target->add_disable_attack_effect(this_object()))
        {
            set_alarm(itof(m_time), 0.0, remove_object);
             if (functionp(func = gDisableAttackBegin))
             {
                applyv(func, ({ query_effect_caster(), query_effect_target() }));
             }
            return 1;
        }
        
    }    
    if (functionp(func = gDisableAttackFailed))
        applyv(func, ({ query_effect_caster(), target }));
    return 0;
}

/*
 * Function     : hook_attack_blocked
 * Description  : Function to display messages that the attack was
 *                blocked because the player is stunned
 * Arguments    : player    - player who is trying to attack
 *                attack_id - attack ID that was blocked
 *                weapon    - weapon in that attack ID, if known.
 * Returns      : nothing
 */
public void
hook_attack_blocked(object player, int attack_id, object weapon)
{
    object enemy;
    
    enemy = player->query_attack();
    if (enemy)
    {
        
        // There's a person that is being fought. We display messages
        // about the stun.
        player->catch_msg("You attempt to attack " + QTNAME(enemy)
                         + ", but find that you are stunned.\n");
        enemy->catch_msg(QCTNAME(player) + " tries to attack you, but "
                           + "cannot seem to move.\n");
        tell_room(environment(player), QCTNAME(player) + " tries to "
                + "attack " + QTNAME(enemy) + ", but cannot seem to "
                + "move.\n", ({ player, enemy }), player);
    }        
}

public void
hook_disable_attack_ended(object player)
{
    player->catch_msg("You feel like you can move freely again.\n");
    player->tell_watcher(QCTNAME(player) + " seems to be able to move "
                       + "freely again.\n");
}

public void
hook_disable_attack_begin(object attacker, object target)
{
    if (!objectp(target))
    {
        return;
    }
    
    if (objectp(attacker))
    {            
        target->catch_msg(QCTNAME(attacker) + " disarms you!\n");
        target->tell_watcher(QCTNAME(attacker) + " disarms " + QCTNAME(target));
    }
    else
    {
        target->catch_msg("You have been disarmed!\n");
        target->tell_watcher(QCTNAME(target) + " has been disarmed!\n");
    }
}

/*
 * Function name: start
 * Description;   Start up the spell effect.  This should be redefined
 *                to provide specific behaviour for a given spell
 *                effect.
 * Returns:       1/0 - effect started/not started
 */
public int
start()
{
    return add_disable_attack_effect(query_effect_target());
}
