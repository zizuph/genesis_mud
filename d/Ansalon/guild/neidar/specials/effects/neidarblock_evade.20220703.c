/*
 * Neidar Block Mastery
 *
 * Neidar gain a 20% combat aid evade ('block') bonus
 * when blocking. They get only 10% when applied on someone
 * else.
 *
 * Used Calian swarm evade by Petros as a model.
 *
 * Louie Oct 2008
 * Petros May 2009 - Cleaned up for balance approval
 * Petros September 2009 - fixed runtime when attacking defended person
 */ 

#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <filter_funs.h>
#include "/d/Ansalon/common/defs.h"
#include "../../guild.h"

inherit "/d/Genesis/specials/std/evade_obj_base";

/*
* Function     : is_neidar_block_evade
* Description  : Is this a neidar block obj
* Arguments    : none
* Returns      : 1 - always returns true
*/
public int
is_neidar_block_evade()
{
    return 1;
}

/*
* Function     : remove_neidar_block_object
* Description  : Destructor function.
* Arguments    : none
* Returns      : nothing
*/
public void
remove_neidar_block_evade()
{
    remove_object();
}

/*
 * Function:    is_active_blocker
 * Description: This is used to do some validation to see if the 
 *              Neidar who gave this block evade is actually
 *              blocking. We check the prop NEIDAR_BLOCK_TARGET
 *              to verify this.
 * Arguments:   blocker - person doing the blocking
 *              target  - person receiving the defensive block
 * Returns:     0/1 - not actively blocking/actively blocking
 */
public int
is_active_blocker(object evade_obj)
{
    object blocker, blockee, target;
            
    if (!objectp(blocker = evade_obj->query_effect_caster()))
    {
        return 0;
    }
    
    target = evade_obj->query_effect_target();    
    if (objectp(blockee = blocker->query_prop(NEIDAR_BLOCK_TARGET))
        && blockee == target)
    {
        return 1;
    }
    else if (!objectp(blockee) && blocker == target)
    {
        // Actively blocking self, and no one else.
        return 1;
    }
    
    return 0;
}


/*
* Function     : create_effect
* Description  : The create function called for objects that inherit this
* Arguments    : none
* Returns      : nothing
*/
public void
create_effect()
{
    set_name("_neidar_block_object_");
    add_name( ({"neidar_block_object" }) );
    set_short("hidden neidar block evade object");
    set_long("The object that grants blocking (evade) to "+
             "Neidars or their protected target.  This " +
             "should not be visible by players.\n");

    setuid();
    seteuid(getuid());

    set_evade_stats( TS_STR );
    set_evade_skills( SS_DEFENCE );

    set_evade_combat_aid(NEIDAR_BLOCK_AID);
}

/*
 * Function     : query_evade_valid
 * Description  : Validation function to see whether this evade object is
 *                valid in the current situation
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : 0/1 - invalid/valid
 */
public int
query_evade_valid(object player, object attacker, int attack_id)
{
    // A valid block must fulfill the following situations
    // 1. If defending someone else, the PROP must be set
    // 2. If defending self, the PROP must not be set 
    object defender, defendee;
    
    if (!objectp(defender = query_effect_caster()))
    {
        send_debug_message("neiderblock_evade", "Evade doesn't have a " +
                           "caster, therefore not valid.");
        set_alarm(0.0, 0.0, remove_object);
        return 0;
    }
    
    if (environment(defender) != environment(player))
    {
        send_debug_message("neiderblock_evade", "Defendee has moved " +
                           "out of the same room, therefore not valid.");
        return 0;
    }
    
    object* defenders_enemies = defender->query_enemy(-1);
    defendee = defender->query_prop(NEIDAR_BLOCK_TARGET);    

    // Make sure we aren't defending enemy
    foreach (object defender_enemy : defenders_enemies)
    {
        if (defender_enemy == defendee)
        {
            DEFEND_ABILITY->set_defend_target(defender);
            send_debug_message("neidarblock_evade",
                "Defendee is enemy and cannot be defended.");
            return 0;
        }
    }
    
    if (defender != player && 
        defender->query_prop(NEIDAR_BLOCK_TARGET) != player)
    {
        send_debug_message("neidarblock_evade", "Defender is not actively " +
                           "defending this player, therefore not valid.");
        set_alarm(0.0, 0.0, remove_object);
        return 0;
    }
    
    if (defender == player &&
        objectp(defendee = defender->query_prop(NEIDAR_BLOCK_TARGET)) &&
        defendee != player)
    {
        send_debug_message("neidarblock_evade", "Defender is defending " +
                           "someone else and cannot actively defend himself.");
        return 0;
    }
        
    return 1;
}

/*
 * Function     : query_evade_strength
 * Description  : Function that will be used to gauge the strength of
 *                the evade based on the situation. 
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : the modified value of the evasion percentage
 */
public int
query_evade_strength(object player, object attacker, int attack_id)
{
    int strength, num_blockers;
    
    strength = ::query_evade_strength(player, attacker, attack_id);
    if (query_effect_caster() == player
        && is_active_blocker(this_object()))
    {
        return strength;
    }
    
    // Each Neidar blocker contributes 10% combat aid to
    // the one that they are defending.
    // However, we need to cap the effect for large teams to 33%
    // evade (50% combat aid). That means, no matter how many team
    // mates there are that are blocking, the cap will always be
    // 50% caid. The aid starts at 10% evade up until 4 teammates.
    object * evades = player->query_evade_effects();
    evades = filter(evades, &->is_neidar_block_evade());
    evades = filter(evades, is_active_blocker);
    evades -= ({ this_object() });
    num_blockers = sizeof(evades);
    if (num_blockers > 0)
    {        
        strength = min(ftoi((1.0 - exp(log(0.67) / itof(num_blockers))) 
                       * 100.0) + 1, strength);
    }
    
    return strength;
}   

/*
* Function     : attack_blocked
* Description  : Function to display messages that the attack was
*                blocked.
* Arguments    : player    - player who is being attacked
*                attacker  - the person doing the attacking
*                attack_id - attack id location
* Returns      : nothing
*/
public void
attack_blocked(object player, object attacker, int attack_id)
{
    object defender;
    object * exclude_list;
    string defender_desc, player_desc, attacker_desc, watcher_desc;

    defender = query_effect_caster();

    exclude_list = ({ player, attacker });

    if (player == defender)
    {
        defender_desc = "";

        // The evade comes from the player himself.
        switch (random(3))
        {
            case 0:
		player_desc = "Faking an opening, you lure "+QTNAME(attacker)+
                              " to launch for an attack, but in the last " +
                              "moment you charge your shoulder into " +
                              HIM(attacker)+ " leaving " + HIM(attacker) +
                              " shaken.";

		attacker_desc = "Noticing an opening in "+QTNAME(player) +
                                "'s defenses, you launch your attack. " +
                                "Too late you realize that " +
                                QTNAME(player) + " was faking it, as " +
                                HE(player)+ " charges into you with " +
                                HIS(player) + " shoulder.";

		watcher_desc = QCTNAME(attacker) + " tries to take " + 
                               "advantage of an opening in " + QTNAME(player) +
                               "'s defences, but " + QTNAME(player) + 
                               " charges into " + HIM(attacker) + 
                               " with " + HIS(player) + " shoulder.";
		break;

            case 1:

		player_desc = "As " + QTNAME(attacker) + " strikes at you, " +
                              "you sidestep " + HIS(attacker) +
                              " swing and push " + HIM(attacker) + 
                              " out of balance.";

		attacker_desc = "As you strike at " + QTNAME(player) +
                                ", " + HE(player) + " sidesteps your swing " +
                                "and pushes you out of balance.";

		watcher_desc = "As " + QTNAME(attacker) + " strikes at " +
                               QTNAME(player) + ", " + QTNAME(player) +
                               " sidesteps " + QTNAME(attacker) +
                               "'s swing and pushes " + HIM(attacker) +
                               " out of balance.";
		break;
		
            default:

		player_desc = "Just as " + QTNAME(attacker) + 
                              " moves in for a swift attack " +
                              "against you, you let out an aggressive roar " +
                              "as you bash " + HIM(attacker) + 
                              " with your elbow causing " + HIM(attacker) +
                              " to stumble backwards.";

		attacker_desc = "As you move in for a swift attack against " +
                                QTNAME(player) + ", " + HE(player) + 
                                " lets out an aggressive roar as " + 
                                HE(player) + " bashes " + "you with " + 
                                HIS(player) + " elbow causing you to " +
                                "stumble backwards.";
		watcher_desc = "As " + QTNAME(attacker) + " moves in for " +
                               "a swift attack against " + QTNAME(player) +
                               ", " + QTNAME(player) + " lets out an " +
                               "aggressive roar as " + HE(player) + " bashes " +
                               QTNAME(attacker) + " with " + HIS(player) +
                               " elbow causing " + QTNAME(attacker) + 
                               " to stumble backwards.";
        }
    }
    else
    {
        exclude_list += ({ defender });

	//A different Neidar is doing the block
	switch(random(4))
	{
            case 0:
		player_desc = QCTNAME(attacker)+", realizing that you " +
                              "have left yourself open, closes in for " +
                              "a dangerous attack when suddenly, out " +
                              "of nowhere, " + QTNAME(defender) + 
                              " crashes into the both of you, knocking " +
                              "you aside!";

		attacker_desc = "Just as you are about to strike a " +
                                "deadly blow against " + QTNAME(player) +
                                ", "+QTNAME(defender)+ " charges "+
                                "into you from out of nowhere, " +
                                "knocking you aside!";

		watcher_desc = QCTNAME(defender) + ", realizing that " +
                               QTNAME(attacker)+" is about to " +
                               "strike a dangerous blow against " +
                               QTNAME(player)+", crashes headlong "+
                               "into the fray, knocking the two " + 
                               "surprised combatants apart!";

	        defender_desc = "Noticing that " + QTNAME(attacker) +
                                " is about to strike a dangerous blow " +
                                "against "+QTNAME(player)+", you crash " +
                                "into the fray, knocking the two " +
                                "combatants away from one another!";
  	        break;

            case 1:
	        player_desc = QCTNAME(defender)+" growls and then " +
                              "jumps right in front of " + QTNAME(attacker) +
                              ", bellowing in rage! "+QCTNAME(attacker) + 
                              " balks somewhat, and the attack that had " +
                              "been meant for you goes badly astray.";

	        attacker_desc = QCTNAME(defender) + " growls and then " +
                                "jumps right in front of you, "+
                                "bellowing in rage! Taken aback by " +
                                "this behavior, your attack against "+
                                QTNAME(player)+" goes badly astray.";

                watcher_desc = QCTNAME(defender)+" growls and then jumps " +
                               "right in front of " + QTNAME(attacker)+
                               ", bellowing in rage! " + QCTNAME(attacker) +
                               " balks somewhat, and the attack " +
                               "that had been intended for " + QTNAME(player) +
                               " goes badly astray.";

                defender_desc = "Growing irritated by the continued attacks " +
                                "of " + QTNAME(attacker) + ", you jump " +
                                "right in front of " + HIM(attacker) +
                                " and bellow in rage, causing "+ HIM(attacker) +
                                " to balk slightly and sending " + HIS(attacker)+
                                " swing against " + QTNAME(player)+" astray.";
	        break;

            case 2:

	        player_desc = "Just as "+QTNAME(attacker)+" moves in " +
                              "for a swift attack against you, "+
                              "an aggressive roar sounds out beside you " +
                              "and you are sent sprawling by " +
                              QTNAME(defender)+", who crashes into you to " +
                              "take the full brunt of the attack "+
                              HIM(defender)+"self!";

                attacker_desc = "As you move in for a swift attack against "+
                                QTNAME(player)+", an aggressive roar sounds " +
                                "away to the side as " + QTNAME(defender) + 
                                " crashes into " + HIM(player) + ", sending " +
                                QTNAME(player) + " sprawling out of the way! " +
                                "In all the motion, your attack glances " + 
                                "harmlessly off of "+QTNAME(defender)+".";

	        watcher_desc = "Just as "+QTNAME(attacker)+" moves in for a " +
                               "swift attack against " + QTNAME(player) + ", " +
                               QTNAME(defender) + " lets out an aggressive " +
                               "roar and crashes into " + QTNAME(player) +
                               ", knocking " + HIM(player) + " aside and " +
                               "taking the full brunt of the attack " +
                               HIM(defender) + "self!";

	        defender_desc = QCTNAME(attacker) + " moves in for a swift " +
                                "attack against " + QTNAME(player) + 
                                ", causing your blood to boil! With an " +
                                "aggressive roar, you storm into " +
                                QTNAME(player) + " pushing " + HIM(player) +
                                " out of the way so that the blow " +
                                "glances harmlessly off of you instead!";
                break;

            default:

                player_desc =  "Letting forth a howl of fury, " + 
                                QTNAME(defender) + " charges suddenly at " +
                               QTNAME(attacker) + " in a blind rage! " +
                               QCTNAME(attacker) + " momentarily takes " +
                               HIS(attacker) + " focus off of you to " +
                               "sidestep the assault.";

	        attacker_desc = "A howl of fury draws your attention " +
                                "away from " + QTNAME(player) + " as " +
                                QTNAME(defender) + " charges at you in " +
                                "a sudden blind rage! You quickly " +
                                "sidestep the assault.";

                watcher_desc = "Letting forth a howl of fury, " + 
                               QTNAME(defender) + " charges suddenly at " +
                               QTNAME(attacker) + " in a blind rage! " + 
                               QCTNAME(attacker) + " momentarily takes " +
                               HIS(attacker) + " focus off of " + 
                               QTNAME(player) + " to sidestep the assault!";

                defender_desc = "Hatred wells in you, and letting forth " +
                                "a howl of fury, you charge directly at " +
                                QTNAME(attacker) + ", who stops " + 
                                HIS(attacker) + " attack against " +
                                QTNAME(player) + " to sidestep your assault!";
	}
    }
    player->catch_msg(player_desc + "\n");
    attacker->catch_msg(attacker_desc + "\n");
    player->tell_watcher(watcher_desc + "\n", attacker, exclude_list);
    
    if (strlen(defender_desc))
    {
	defender->catch_msg(defender_desc + "\n");
    }
}
