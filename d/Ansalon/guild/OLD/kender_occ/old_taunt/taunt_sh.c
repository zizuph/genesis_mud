#pragma strict_types
#pragma save_binary
 
inherit "/std/shadow";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <composite.h>

#include "guild.h"

// Max rage value
#define MAX_RAGE                 50
// Has a chance of increasing did_hit dmg
#define PERCENT_DAMAGE           40

int     kender_rage;
mapping list_kenders;
mixed   rage_alarm;

/*
 * Function name :  turned_aggression
 * Description   :  This functions checks which specials are active.
 */
public int
query_special_attacks(object player)
{
    int specials = 0;
    
    if (SLING_ABILITY->query_ability_active(player))
        specials++;
    
    if (DODGE_ABILITY->query_ability_active(player))
        specials--;
    
    return specials;
}

/*
 * Function name :  remove_kender_rage
 * Description   :  Handles the removal of the shadow.
 */
public void
remove_kender_rage()
{
    shadow_who->catch_msg("You manage to regain a bit of your " +
    "self control.\n");
    tell_room(environment(shadow_who), QCTNAME(shadow_who) +
    " seems to be regaining " + shadow_who->query_possessive() +
    " self control.\n", shadow_who);
    
    remove_shadow();
}

/*
 * Function name :  query_kender_rage
 * Returns       :  Returns the value of kender_rage
 */
public int
query_kender_rage()
{
    return kender_rage;
}

/*
 * Function name :  turned_aggression
 * Description   :  This function is called to check when there is a target
 *                  switch.
 */
public int
turned_aggression(int task, object actor)
{
    if (objectp(shadow_who->query_attack()) &&
        actor->query_special_attacks() > 0)
    {
        if (list_kenders[actor->query_real_name()][1] < random(kender_rage))
            return 1; // Adds a random chance to switching of targets
    }
        
    if (!objectp(shadow_who->query_attack()) ||
        shadow_who->query_attack() != actor)
    {
        if (objectp(shadow_who->query_attack()))
            shadow_who->stop_fight(shadow_who->query_attack());
        
        shadow_who->attack_object(actor);
    }
    
    return 1;
}

/*
 * Function name :  add_kender_rage
 * Description   :  This function handles the rage values, each taunting kender
 *                  has its own value.
 */
public varargs int
add_kender_rage(int task, object actor, int dodge = 0)
{
    int     rage,
            etask;
    string  name,
            ename;
    
    if (!intp(task))
        return 0;
    
    if (!objectp(actor))
        return 0;
    
    name = actor->query_real_name();
    /*
     * The task before the formula is capped at 33, meaning the best taunt with
     * the following formula, (if the target is not already affected by taunt)
     * increases the rage value by 13, which decreases by 1 every 2 seconds.
     * The taunt stacks, and this formula controls its increment. Skills cannot
     * be decreased below superior layman, or more than a total of 50 levels.
     */
    
    task = (((100 / (kender_rage + 5)) + task ) / 4);
    
    if (!mappingp(list_kenders))
        list_kenders = ([]);
    
    if (!pointerp(list_kenders[name]))
    {
        list_kenders += ([ name : ({ time(), task }) ]);
    }
    else
    {
        rage = min(MAX_RAGE, (list_kenders[name][1] + task));
        list_kenders[name] = ({ time(), rage });
    }
    kender_rage = min(MAX_RAGE, (kender_rage + task));
    
    if (dodge) // Prevent dodge from triggering turned_aggression
        return 1;
    
    if (objectp(shadow_who->query_attack()))
        ename = shadow_who->query_attack()->query_real_name();
    else
        return turned_aggression(task, actor);
    
    if (pointerp(list_kenders[ename]))
        etask = list_kenders[ename][1];
    
    if (etask && random(etask) > random(rage))
        return 1;
    
    turned_aggression(task, actor);

    return 1;
}

/*
 * Function name :  subtract_kender_rage
 * Description   :  This function removes rage from the mapping list_kenders.
 */
public varargs int
subtract_kender_rage(int task, object actor)
{
    string *list,
            name,
            enemy;

    if (!intp(task))
        return 0;

    if (kender_rage - task <= 0)
    {
        remove_kender_rage();
    }
    
    if (!mappingp(list_kenders))
        return 0;
    
    if (!objectp(actor))
    {
        foreach(string names: m_indexes(list_kenders))
        {
            if (!pointerp(list))
                list = ({});
            
            if (list_kenders[names][1] > 0)
                list += ({ names });
        }
        
        if (!sizeof(list))
            return 0;
        
        if (enemy = shadow_who->query_attack()->query_real_name() &&
            sizeof(list) > 1)
            list -= ({ enemy });
        
        name = one_of_list(list);
    }
    else
    {
        name = actor->query_real_name();
    }
    
    if (!pointerp(list_kenders[name]))
        return 0;
    
    list_kenders[name][1] = max(0, list_kenders[name][1] - task);

    kender_rage = max(0, (kender_rage - task));

    return 1;
}

/*
 * Function name :  init_rage_decay
 * Description   :  This function sets an alarm to decrease the rage value by
 *                  1 every 2 seconds.
 */
void
init_rage_decay()
{
    if (rage_alarm)
        return;
    
    rage_alarm = set_alarm(2.0, 2.0, &subtract_kender_rage(1));
}

/*
 * Function name :  query_skill
 * Description   :  This lowers the combat skills of the taunted based on the
 *                  rage value, stacks to a maximum of 50, cant force the
 *                  target below 30 in skill level (superior layman).
 */
public int
query_skill(int skill)
{
    if (!kender_rage)
        return shadow_who->query_skill(skill);
    
    if (!IN_ARRAY(skill, ({ SS_UNARM_COMBAT, SS_WEP_SWORD,
                            SS_WEP_POLEARM,  SS_WEP_AXE,
                            SS_WEP_KNIFE,    SS_WEP_CLUB,
                            SS_WEP_MISSILE,  SS_WEP_JAVELIN,
                            SS_DEFENCE,      SS_PARRY })))
        return shadow_who->query_skill(skill);
    
    // Cant reduce skill below 30 (superior layman), or remove more than 50lvls
    return max(30, (shadow_who->query_skill(skill) - max(5, kender_rage)));
}

/*
 * Function name :  hit_me
 * Description   :  Increases damage of hits taken by members of the taunting 
 *                  kenders team. The chance of hitting is based on the number
 *                  of team members, so as to scale well with larger teams.
 *                  The chance of hitting is also reduced based on the number
 *                  of taunting kenders.
 */
varargs public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id, int target_hitloc =-1)
{
    string *kenders;
    object *party,
            player;
    mixed   hitres;
    int     damage;
    
    hitres  = shadow_who->hit_me(wcpen, dt, attacker, attack_id, target_hitloc);
    party   = attacker->query_team() + ({ attacker });
    kenders = filter(party->query_real_name(), &operator(>)(, -1) @
              &member_array(, m_indexes(list_kenders)));

    if (hitres[3] <= 0)
        return hitres;
    
    if (sizeof(kenders) && !random((1 + (sizeof(party)) * 3) - sizeof(kenders)))
    {
        foreach(string name: kenders)
        {
            if (!objectp(player = find_player(name)))
                continue;
            
            if (query_special_attacks(player) < 1) // Check if _only_ slinging
                continue;
            
            if (environment(player) != environment(shadow_who))
                continue;
            
            damage = hitres[3];
            
            if (damage > 0)
                break;
        }
        
        if (damage)
        {
            shadow_who->catch_msg("Overcome with rage, you leave your "+
            "defenses wide open allowing a painful strike.\n");
            
            attacker->catch_msg(QCTNAME(shadow_who) + " appears affected by " +
            "rage and fails to notice your advance, leaving " +
            shadow_who->query_objective() + " no time to brace for the " +
            "coming impact.\n");
            
            damage -= ((damage * (100 - PERCENT_DAMAGE)) / 100);
            shadow_who->heal_hp(-damage);
        }
    }

    return hitres;
}