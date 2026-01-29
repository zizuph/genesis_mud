#pragma strict_types
#pragma save_binary
 
inherit "/std/shadow";

#include <comb_mag.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <composite.h>

#include "../guild.h"

// Max rage value
#define MAX_RAGE                 50

int     kender_rage, old_rage;
mapping list_kenders,
        skill_list = ([ SS_UNARM_COMBAT:0,
                        SS_WEP_SWORD:0,
                        SS_WEP_POLEARM:0,
                        SS_WEP_AXE:0,
                        SS_WEP_KNIFE:0,
                        SS_WEP_CLUB:0,
                        SS_WEP_MISSILE:0,
                        SS_WEP_JAVELIN:0,
                        SS_DEFENCE:0,
                        SS_PARRY:0
                    ]);
/*
 * Function name :  turned_aggression
 * Description   :  This functions checks which specials are active.
 */
public int
query_special_attacks(object player)
{
    int specials = 0;
    
    /*
    if (SLING_ABILITY->query_ability_active(player))
        specials++;
    */
    if (DODGE_ABILITY->query_ability_active(player))
        specials--;
    
    return specials;
}

public mapping
query_kender_list()
{
    return list_kenders;
}


/*
 * Function name :  update_taunt_effects
 * Description   :  This lowers the combat skills of the taunted based on the
 *                  rage value, stacks to a maximum of 50, cant force the
 *                  target below 30 in skill level (superior layman).
 */
public void
update_taunt_effects()
{
    if (kender_rage == old_rage)
        return;
    
    int  diff_rage, skill_rage;
    
    diff_rage = old_rage - kender_rage;
    old_rage  = kender_rage;
    
    foreach(int skill: m_indexes(skill_list))
    {
        skill_rage = diff_rage;
        
        if (skill_rage < 0 && (shadow_who->query_skill(skill) + skill_rage) < 30)
        {
            if (shadow_who->query_skill(skill) <= 30)
            {
                skill_list[skill] += skill_rage;
                continue;
            }
            
            skill_rage = -(shadow_who->query_skill(skill) - 30);
            skill_list[skill] += diff_rage - skill_rage;
        }
        
        if (skill_rage > 0 && (skill_list[skill] < 0 || kender_rage < 5))
        {
            if ((skill_rage + skill_list[skill] < 1) || (kender_rage > 0))
            {
                skill_list[skill] += skill_rage;
                continue;
            }
            
            skill_rage += skill_list[skill];
            skill_list[skill] = 0;
        }
        
        shadow_who->set_skill_extra(skill, shadow_who->query_skill_extra(skill)
                                    + skill_rage);
    }
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
    
    if (kender_rage > 0)
    {
        kender_rage = 0;
        update_taunt_effects();
    }
    
    remove_shadow();
}

/*
 * Function name :  query_kender_rage
 * Returns       :  Returns the value of kender_rage
 */
public varargs int
query_kender_rage(mixed actor)
{
    if (objectp(actor) && living(actor))
        actor = actor->query_real_name();
    
    if (stringp(actor) && member_array(actor, m_indexes(list_kenders)) > -1)
        return list_kenders[actor][1]; 
    
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
    object target;
    
    if (objectp(target = shadow_who->query_attack()) &&
        actor->query_special_attacks() > -1)
    {
        if (list_kenders[actor->query_real_name()][1] < random(kender_rage))
            return 1; // Adds a random chance of not switching targets
                      // This effect does affect those who are dodging
    }
        
    if (!objectp(target) || target != actor)
    {
        // Never initiate combat between those who can't be attacked.
        if (NPATTACK(shadow_who) || NPATTACK(actor)) 
        {
            return 1;
        }


        if (objectp(target))
            shadow_who->stop_fight(target);
        
        shadow_who->catch_msg("You " + (objectp(target) ? "turn to " : "")
        + "attack " + QTNAME(actor) + ".\n");
        actor->catch_msg(QCTNAME(shadow_who)
        + (objectp(target) ? " turn to attack" : " attacks") + " you.\n");
        shadow_who->tell_watcher(QCTNAME(shadow_who) + (objectp(target) ? " "
        + "turns to attack " : " attacks ") + QTNAME(actor) + ".\n", ({actor}));
        
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
    update_taunt_effects();
    
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
        set_alarm(0.0, 0.0, &remove_kender_rage());
        return -1;
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

    if (list_kenders[name][1] < 1)
        list_kenders = m_delete(list_kenders, name);
    
    kender_rage = max(0, (kender_rage - task));
    update_taunt_effects();
    
    return 1;
}
