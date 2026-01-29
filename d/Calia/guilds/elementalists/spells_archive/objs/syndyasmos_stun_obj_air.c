/*
 * Stun Effect Object for the Genesis Magic System Stun Spell
 * 
 * This is the stun effect object for the stun spell in the Genesis
 * Magic System. 
 *
 * Created by Petros, March 2010
 *
 */
 
#pragma strict_types

#include <macros.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/obj/stun_obj";

/*
 * Function     : create_stun_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
    set_name("_spell_stun_object");
    add_name( ({"spell_stun_object" }) );
    set_short("hidden spell stun object");    
    set_long("A spell stun object. One should not be able to see it "
           + "in their inventory.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    setuid();
    seteuid(getuid());

    set_stun_combat_aid(120);
    set_stun_tohit(95);
    set_stun_chance(95); 
    // Cycle time of 30 seconds == 15 seconds stun, 15 seconds cooldown
    // if the aid is 100%. At 25% combat aid, this equals 5 seconds
    // of stun, and 15 seconds of cooldown.
    set_stun_cycle_time(30);    
}

/*
 * Function     : attack_blocked
 * Description  : Function to display messages that the attack was
 *                blocked because the player is stunned
 * Arguments    : player    - player who is trying to attack
 * Returns      : nothing
 */
public void
attack_blocked(object player)
{
    object enemy;
    
    enemy = player->query_attack();
    if (enemy)
    {
        // There's a person that is being fought. We display messages
        // about the stun.
        player->catch_msg("You attempt to attack " + QTNAME(enemy)
                         + ", but find that the whirlwinds surrounding your "+
                         "arms "+
                         "make it impossible to do so.\n");
        enemy->catch_msg(QCTNAME(player) + " tries to attack you, but "
                           + "cannot seem to move "+player->query_possessive()+
                           " arms.\n");
        tell_room(environment(player), QCTNAME(player) + " tries to "
                + "attack " + QTNAME(enemy) + ", but cannot seem to "
                + "move "+player->query_possessive()+" arms.\n", 
                ({ player, enemy }), player);
    } 
}

public void
hook_stun_cooldown_in_effect(object player)
{
    player->catch_msg("The whirlwinds surrounding your arms dissipate.\n");
    player->tell_watcher("The whirlwinds surrounding "+QTNAME(player) +
                       " arms dissipate and "+player->query_pronoun() +
                       " seems to be able to use "+player->query_possessive()+
                       " arms again.\n", ({  }));
}

public void
hook_stun_ended(object player)
{
	object caster = query_effect_caster();
	
    player->catch_msg("You feel you have fully recovered from " +
        "the whirlwinds surrounding your arms.\n");
    player->tell_watcher(QCTNAME(player) + " seems to have " +
        "recovered from the whirlwinds surrouding "+player->query_possessive()+
        " arms.\n", ({  }));
    caster->remove_prop(LIVE_I_SYNDYASMOS_TARGETS);
}

public void
hook_stun_begin(object attacker, object target)
{
	// Set the CAID at 120 by default
	int act_caid = 120;
	
	// If racial member, set the CAID higher
	if (attacker->is_elemental_racial_cleric())
		act_caid = 150;
		
	// Find out how many targets the spell is hitting
	int num_targs = attacker->query_prop(LIVE_I_SYNDYASMOS_TARGETS);
	
    // Divide the CAID by the number of targets
	int tar_caid = act_caid / num_targs;
	
	// Set the new CAID for this target
	set_stun_combat_aid(tar_caid);
	
    target->catch_msg("Your arms are suddenly surrounded by small whirlwinds "+
        "of air, greatly restricting your ability to attack.\n");
    target->tell_watcher(QCTPNAME(target) + " arms are suddenly surrouned by "+
       "small whirlwinds of air, grealy restricting " + 
       target->query_possessive() + " arm movement.\n", ({  }) );
}
