/*
 * Opportunity Attack Shadow
 * 
 * This shadow implements the basis for something called an opportunity
 * attack. An opportunity attack is when someone tries to attack someone
 * other than the tanker. Since they are busy and receiving attacks from
 * someone who is attacking them, the person whom they're currently
 * fighting gets an opportunity to score a hit.
 *
 * The basic concept is taken from D&D, although it does not implement
 * things like moving away from someone incurring an attack.
 *
 * Significant effort was spent in order to prevent abuse for opportunity
 * attacks. There are a few scenarios that need to be taken care of
 * so that people don't try to abuse it by leaving and re-entering and
 * also to make sure that hunting works correctly.
 *
 * Created by Petros, June 2008
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/shadow";

#include "defs.h"
#include "calian.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include DEBUGGER_TELL

// Global Variables
private string      ability_file = OPPORTUNITY_ATTACK; // default
private mapping     attack_mapping = ([ ]);

/*
 * Function name: has_opportunity_attack_shadow
 * Description  : Easy method to determine whether someone has this shadow
 * Arguments    : none
 * Returns      : always true
 */
public int
has_opportunity_attack_shadow()
{
    return 1;
}

/*
 * Function name: remove_opportunity_attack_shadow
 * Description  : Easy way to remove the opportunity attack shadow
 * Arguments    : none
 * Returns      : nothing
 */
public void
remove_opportunity_attack_shadow()
{
    remove_shadow();
}

/*
 * Function name: query_ability_file
 * Description  : Returns the file name for the ability to execute on
 *                opportunity attack.
 * Arguments    : none
 * Returns      : file for the opportunity attack
 */
public string
query_ability_file()
{
    return ability_file;
}

/*
 * Function name: set_ability_file
 * Description  : Allows the setting of the ability file for the
 *                actual opportunity attack
 * Arguments    : file - name of the file to use to execute the attack
 * Returns      : nothing
 */
public void
set_ability_file(string file)
{
    ability_file = file;
}

/*
 * Function name: query_old_attack_target
 * Description  : Because the combat object doesn't keep track of the
 *                previously attacked enemy, we keep our own internal
 *                tracking of that information. This function returns
 *                result of the last person attacked that was recorded
 *                By querying this, one can find out who the last person
 *                attacked was.
 * Arguments    : object enemy - the person we want to check enemies for
 * Returns      : the object that enemy was attacking
 */
public object
query_old_attack_target(object enemy)
{
    object enemy_target;
    
    if (IN_ARRAY(enemy, m_indices(attack_mapping)))
    {
        enemy_target = attack_mapping[enemy];
        if (objectp(enemy_target) && living(enemy_target))
        {
            return enemy_target;
        }
    }
    
    return 0;
}

/*
 * Function name: update_attack_target
 * Description  : Updates the mapping to record the currently attacked
 *                target.
 * Arguments    : enemy - the person doing the attacking
 *                target - the target of the enemy
 * Returns      : nothing
 */
public void
update_attack_target(object enemy, object target)
{
    if (!objectp(enemy))
    {
        // If the index is invalid, just ignore this.
        return;
    }
    
    if (!objectp(target))
    {
        // If the target is empty, remove the mapping
        m_delkey(attack_mapping, enemy);
        return;
    }
    
    attack_mapping[enemy] = target;
}

/* 
 * Function:      attacked_by 
 * Description:   Called when someone attacks the player. 
 * Arguments:     attacker - person doing the attacking 
 */ 
void 
attacked_by(object attacker) 
{ 
    object player;
    object * team;
        
    // We allow the lower shadows to process the attacked by first
    // before we update the mapping with the new targets.
    shadow_who->attacked_by(attacker); 

    // Update the book-keeping information in all the teammates.
    team = shadow_who->query_team_others();
    foreach (object teammate : team)
    {
        teammate->update_attack_target(attacker, shadow_who);
    }
    update_attack_target(attacker, shadow_who);        
    
    // We mark the attacker with information about when and who they
    // attacked on the Calian team
    attacker->add_prop(CALIAN_ATTACKER_LAST_ATTACK_TIME, time());
    attacker->add_prop(CALIAN_ATTACKER_LAST_TARGET, shadow_who);
}

/*
 * Function name:   attack_object
 * Description:     Start attacking, the actual attack is done in heart_beat
 * Arguments:       The object to attack
 */
public void
attack_object(object ob)
{
    object enemy_target;
    object * team;
    
    shadow_who->attack_object(ob);

    if (ob->query_attack())
    {
        enemy_target = ob->query_attack();
    }
    else
    {
        // This would only happen if the heart beat hasn't started
        // yet or something.
        enemy_target = shadow_who;
    }
    
    // We will now store the attack information
    // Update the book-keeping information in all the teammates.
    team = shadow_who->query_team_others();
    foreach (object teammate : team)
    {
        teammate->update_attack_target(ob, enemy_target);
        teammate->update_attack_target(shadow_who, ob);
    }
    update_attack_target(ob, enemy_target);        
    update_attack_target(shadow_who, ob);
    send_debug_message("opp_attack", "Attacking enemy");
}


/*
 * Function name: add_opportunity_attack_shadow_to_team
 * Description  : Every member of the team is checked to make sure they
 *                have the opportunity attack shadow
 * Arguments    : none
 * Returns      : nothing
 */
public void
add_opportunity_attack_shadow_to_team()
{
    object * team;
    
    setuid();
    seteuid(getuid()); 

    team = shadow_who->query_team_others();
    foreach (object teammate : team)
    {
        if (!teammate->has_opportunity_attack_shadow())
        {
            clone_object(MASTER_OB(this_object()))->shadow_me(teammate);
        }
    }
}

/*
 * Function name: team_join
 * Description  : This function is called when someone joins our team.
 *                We shadow this so that we add the shadow to anyone
 *                who doesn't already have it.
 * Arguments    : object m - the person joining the team
 * Returns      : int - 1/0 success/failure.
 */
public int 
team_join(object m) 
{ 
    object * team;
    
    if (!(shadow_who->team_join(m))) 
    {
        return 0; 
    }
    
    setuid();
    seteuid(getuid()); 

    if (!m->has_opportunity_attack_shadow())
    {
        clone_object(MASTER_OB(this_object()))->shadow_me(m);
    }        

    return 1; 
} 

/*
 * Function name: set_leader
 * Description  : Sets this living as a member in a team by assigning a leader.
 *                It will fail if this living is a leader of a team already.
 * Arguments    : object leader - the leader of the team.
 * Returns      : int - 1/0 success/failure.
 */
public int
set_leader(object leader)
{
    object * team, *calians;
    int result;
    
    result = shadow_who->set_leader(leader);
    if (result && objectp(leader))
    {        
        add_opportunity_attack_shadow_to_team();
    }
    
    return result;
}

/*
 * Function name: stop_fight
 * Description  : Makes this living stop fighting others.
 * Arguments    : mixed elist - the enemy or enemies to stop fighting.
 */
public void
stop_fight(mixed elist)
{
    object * team;
    
    shadow_who->stop_fight(elist);

    team = shadow_who->query_team_others();
    foreach (object teammate : team)
    {
        teammate->update_attack_target(shadow_who, 0);
    }
    update_attack_target(shadow_who, 0);
}
