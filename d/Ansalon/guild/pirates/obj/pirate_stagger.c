/*
 * Modifications
 *  October 2009 - Fixed missing argument in tell_watcher, Petros
 * 
 */
 
#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include "/d/Genesis/specials/local.h";
inherit EVADE_OBJ_BASE;

public void
create_effect()
{
    set_name("_pirate_stagger_object_");
    setuid();
    seteuid(getuid());
    
    set_evade_stats(TS_DEX);
    set_evade_skills(SS_SPECIAL_STAGGER);
    set_evade_combat_aid(40);
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
query_evade_valid(object player,
                  object attacker,
                  int attack_id)
{
    int percent = (100 * player->query_intoxicated() + 1) /
                        (player->intoxicated_max()+1);
    if (percent < 50 || player->query_skill(SS_SPECIAL_STAGGER) < 1)
    {
        return 0;
    }
    return 1;
}

public void
attack_blocked(object player,
               object attacker,
               int attack_id)
{
    string attack_desc;
    mixed attack;
    object attack_ob = attacker->query_combat_object();
    attack = attack_ob->query_attack(attack_id);

    if (!attack)
    {
        player->catch_msg("You begin to stagger violently first to the left then " +
                          "to the right causing " +attacker->query_the_name(player) +
                          " to miss you completely with "+HIS(attacker)+" attack.\n");
        attacker->catch_msg(player->query_The_name(attacker) +
                            " staggers violently first to the left then to the right, "+
                            "causing you to miss "+HIM(player)+" completely with your "+
                            "attack.\n");
        player->tell_watcher(QCTNAME(player)+" staggers violently around, first "+
                             "to the left then to the right, causing "+QTNAME(attacker) +
                             " to miss "+HIM(player)+" completely with "+HIS(attacker) +
                             " attack.\n", attacker);
        return;
    }
    attack_desc = attack_ob->cb_attack_desc(attack_id);

    switch (random(4))
    {
        case 0:
	    player->catch_msg("You begin to stagger violently first to the " +
		              "left then to the right causing " +
                              attacker->query_the_name(player) +
                              " to miss you completely with " +HIS(attacker)+
                              " " + attack_desc+".\n");
	    attacker->catch_msg(player->query_The_name(attacker) +
                                " staggers violently first to the left " +
                                "then to the right, causing you to miss " + HIM(player)+
                                " completely with your "+attack_desc+".\n");
            player->tell_watcher(QCTNAME(player)+" staggers violently around, first to "+
                                 "left then to the right, causing "+QTNAME(attacker)+ 
                                 " to miss "+HIM(player)+" completely with "+HIS(attacker)+ 
                                 " "+ attack_desc+".\n", attacker);
            break;

        case 1:
            player->catch_msg("Your vision begins to blur as you quickly run " +
                              "forward in an attempt to keep your balance. Your sudden " +
                              "movement causes " + attacker->query_the_name(player) +
                              " to miss you with " +HIS(attacker)+ " blow.\n");
            attacker->catch_msg(player->query_The_name(attacker) +
                                " quickly runs forward in an attempt to keep "+ HIS(player)+
                                " balance. "+C(HIS(player))+
                                " sudden movement causes you to miss " +HIM(player)+ 
                                " with your blow.\n");
            player->tell_watcher(QCTNAME(player) +
                                 " quickly runs forward, in an attempt to keep "+HIS(player)+
                                 " balance. "+C(HIS(player))+" sudden movement causes "+
                                 QTNAME(attacker)+ " to miss "+HIM(player)+" with "+
                                 HIS(attacker)+ " blow.\n", attacker);
            break;

        case 2:
	    player->catch_msg("As "+attacker->query_the_name(player) +
                              " attempts to hit you with "+attack_desc+
                              ", you manage to dodge the "+
                              "attack by quickly staggering to the left.\n");
            attacker->catch_msg(player->query_The_name(attacker) +
                                " staggers quickly to the left, "+
                                "causing you to miss "+ HIM(player)+ " completely with "+
                                "your " +attack_desc+".\n");
            player->tell_watcher(QCTNAME(player) + " manages to dodge the attack by "+
                                 "quickly staggering to the left.\n", attacker);
            break;

        default:
	    player->catch_msg("As "+attacker->query_the_name(player)+
                              " attempts to hit you with " +HIS(attacker)+ " " +
                              attack_desc+ ", you manage to dodge the "+
                              "attack by quickly staggering to the right.\n");
            attacker->catch_msg(player->query_The_name(attacker) +
                                " staggers quickly to the right, "+
                                "causing you to miss "+ HIM(player)+ " completely with "+
                                "your " +attack_desc+".\n");
            player->tell_watcher(QCTNAME(player) + " manages to dodge the attack by "+
                                 "quickly staggering to the right.\n", attacker);
    }
}
