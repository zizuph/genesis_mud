#pragma strict_types

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <tasks.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit "/d/Genesis/specials/std/damage";

#define MAX_AID 40


public void
config_ability()
{
    ::config_ability();

    // set_ability_group(GUILD_NAME);
    // 45 when not evading, 20 when evading.
    set_combat_aid(MAX_AID);
    set_tohit(75);
    set_skills(SS_GUILD_ATTACK_SKILL);
    set_stats(({ SKILL_AVG, TS_STR, SKILL_END }));
    set_ability_prep_time(6);
    set_ability_cooldown_time(4);
    set_dt(W_BLUDGEON);
    set_ability_name("tattack");

    set_guild_stat_modifier(SS_LAYMAN, 20, 100);
    
    // Doesnt make sense for this ability to be hastened by dual wield.
    set_ability_dual_wield(0);
}

public void
special_did_hit(int aid,
                string hdesc,
                int hid,
                int phurt,
                object enemy,
                int dt,
                int phit,
                int dam)
{
    string* attack_message;
    string default_msg;
    string you_msg;
    object player = this_player();

    if (phurt >= 0) 
    {
        switch (phurt)
        {
            case 0:
                attack_message = ({
                "You step towards "+
                    enemy->query_the_name(player)+
                    " to swing a blow at "+ HIS(enemy)+
                    " head, but "+HE(enemy)+" anticipates your "+
                    "attack and hastily moves out of the way"+
                    ".\n",
                player->query_The_name(enemy) +
                    " steps towards you to swing a blow at your head, "+
                    "but you anticipate it and hastily move out "+
                    "of the way.\n",
                QCTNAME(player)+" steps towards "+QTNAME(enemy)+
                    " and swings a blow at "+HIS(enemy)+" head, but "+
                    HE(enemy)+" anticipates the attack and hastily "+
                    "moves out of the way.\n"
                });
                break;
            case 1..5:
                attack_message = ({
                "You swing at "+
                    enemy->query_the_name(player)+
                    " with a poorly timed blow, barely "+
                    "nicking "+HIM(enemy)+".\n",
                player->query_The_name(enemy) +
                    " swings at you with a poorly timed blow, "+
                    "barely nicking you.\n",
                QCTNAME(player)+" swings at "+QTNAME(enemy)+
                    " with a poorly timed blow, barely "+
                    "nicking "+HIM(enemy)+".\n"
                });
                break;
            case 6..20:
                attack_message = ({
                "You bring your knee up into the midsection of "+
                    enemy->query_the_name(player)+
                    ", grazing "+HIM(enemy)+".\n",
                player->query_The_name(enemy) +
                    " brings "+HIS(player)+" knee up into your midsection, "+
                    "grazing you.\n",
                QCTNAME(player)+" brings "+HIS(player)+" knee up into "+
                    "the midsection of "+QTNAME(enemy)+
                    ", grazing "+HIM(enemy)+".\n"
                });              
                break;
            case 21..35:
                attack_message = ({
                  "You allow "+enemy->query_the_name(player)+
                    " inside your defences and quickly strike "+
                    HIM(enemy)+
                    " with a painful headbutt.\n",
                player->query_The_name(enemy) +
                    " allows you inside "+HIS(player)+" defences "+
                    "and quickly strikes you a painful headbutt.\n",
                QCTNAME(player)+" allows "+QTNAME(enemy)+
                    " inside "+HIS(player)+" defences and quickly "+
                    "strikes "+HIM(enemy)+" with a painful headbutt.\n"
                });
                break;
            case 36..50:
                attack_message = ({
                "You spot an opening in "+
                    enemy->query_the_name(player)+
                    "'s defences and pummel "+
                    HIM(enemy)+
                    " with a throw "+
                    "of your elbow.\n",
                player->query_The_name(enemy) +
                    " spots an opening in your defence and pummels you "+
                    "with a throw of "+
                    HIS(player)+
                    " elbow.\n",
                QCTNAME(player)+" spots an opening in "+
                    QTNAME(enemy)+
                    "'s defences and pummels "+
                    HIM(enemy)+
                    " with a "+
                    "throw of "+
                    HIS(player)+
                    " elbow.\n"
                });
                break;
            case 51..75:
                attack_message = ({
                "You capitalize on a weakness in "
                    +enemy->query_the_name(player)+
                    "'s guard and crush "+HIM(enemy)+" with a powerful "+
                    "kick.\n",
                player->query_The_name(enemy) +
                    " capitalizes on a weakness in your guard and crushes "+
                    "you with a powerful kick.\n",
                QCTNAME(player)+" capitalizes on a weakness in "
                    +QTNAME(enemy)+
                    "'s guard and crushes "+HIM(enemy)+" with a powerful kick.\n"
                });
                break;
            case 76..99:
                attack_message = ({
                  enemy->query_The_name(player)+
                    " seems to stand perfectly still as you spin to the side "+
                    "and deliver a devastating blow on "+HIM(enemy)+".\n",
                  "You attempt to move but cannot dodge out of the way "+
                    "as "+player->query_the_name(enemy)+ " spins to the "+
                    "side and delivers a devastating blow on you.\n",
                  QCTNAME(enemy)+ " seems to stand perfectly still as "+
                    QTNAME(player)+" spins to the side and delivers "+
                    "a devastating blow on "+HIM(enemy)+".\n"
                });
                break;
            default:
                attack_message = ({
                  enemy->query_The_name(player)+
                    " seems to stand perfectly still as you spin to the side "+
                    "and deliver a devastating blow on "+HIM(enemy)+".\n",
                  "You attempt to move but cannot dodge out of the way "+
                    "as "+player->query_the_name(enemy)+ " spins to the "+
                    "side and delivers a devastating blow on you.\n",
                  QCTNAME(enemy)+ " seems to stand perfectly still as "+
                    QTNAME(player)+" spins to the side and delivers "+
                    "a devastating blow on "+HIM(enemy)+".\n"
                });
                break;
        }

        /* message to the player */
        player->catch_tell(attack_message[0]);

        /* message to the enemy */
        enemy->catch_tell(attack_message[1]);

        /* message to onlookers */
        player->tell_watcher(attack_message[2], enemy);
    
        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(player);
        }        
    }
    else
    {
        /* We get here if the attack missed */
    
        attack_message = ({
            "You step towards "+
                enemy->query_the_name(player)+
                " to swing a blow at "+ HIS(enemy)+
                " head, but "+HE(enemy)+" anticipates your "+
                "attack and hastily moves out of the way"+
                ".\n",
            player->query_The_name(enemy) +
                " steps towards you to swing a blow at your head, "+
                "but you anticipate it and hastily move out "+
                "of the way.\n",
            player->query_The_name(enemy)+" steps towards "+QTNAME(enemy)+
                " and swings a blow at "+HIS(enemy)+" head, but "+
                HE(enemy)+" anticipates the attack and hastily "+
                "moves out of the way.\n"
            });
        
        /* message to player */
        player->catch_tell(attack_message[0]);
    
        /* message to enemy */
        enemy->catch_tell(attack_message[1]);
     
        /* message to onlookers */
        player->tell_watcher(attack_message[2], enemy);
    }
}

/*
 * Function name: query_combat_aid_modifier
 * Description  : Calculates the combat aid for the special attack.
 *                It is based on the whether they are focussed on defence.
 * Arguments    : player - player executing special
 * Returns      : The adapted value, 100 means 45% combat aid, 50 means 45/2%.
 */
public int 
query_combat_aid_modifier()
{
    if (TP->query_prop(GUILD_FOCUS_PROP))
    {
        // 20 caid from 40 caid would be 50%
        return 50;
    }    
    return 100;
}


public void
hook_room_no_attack_fail(mixed reason, object room)
{
    if (stringp(reason))
    {
        write(reason);
    }
    else
    {
        write("You sense a force protecting your intended target.\n");
    }
}

/*
 * Function name: check_valid_action
 * Description:   Perform ability-specific checks
 * Arguments:     1. (object) The player
 *                2. (mixed *) The targets
 *                3. (string) Arguments passed to the command
 *                4. (int) Actual spell execution
 * Returns:       (int) 1 if we can continue, 0 if failure
 */
static int
check_valid_action(object player,
                   mixed* targets, 
                   string arg,
                   int execute)
{
    if (!::check_valid_action(player,targets,arg,execute))
    {
        return 0;
    }

    /* 
     * If the player has no skill he cannot sap
     */ 
    if (!player->query_skill(SS_GUILD_ATTACK_SKILL)) 
    { 
        player->catch_tell("You are not skilled to tattack anyone!\n");
/*
        send_debug_message(VALIDATE, 
                           capitalize(player->query_real_name()) 
                         + " is not skilled in tattacking.");
*/
        return 0; 
    }

    // Goodies get penalty here!
    if (player->query_alignment() >  0)
    {
        player->catch_tell("You feel too pure to use the skills "+
                           "thought to you in the Dark Queen's service!\n");
        return 0;
    }
    return 1;
}

public void hook_special_complete()
{    
    object player = this_player();

    int delay_prop = player->query_prop(GUILD_FOCUS_DELAY_PROP);
    if(delay_prop)
    {
        // 1 = player wants to evade.
        if(delay_prop == 1)
        {
            player->add_prop(GUILD_FOCUS_PROP, 1);
            send_debug_message("tattack", "Setting state to 1.");
            player->catch_tell("You begin focusing on defending against attacks.\n");
        }
        else
        {
            // same as setting to 0
            player->remove_prop(GUILD_FOCUS_PROP);
            send_debug_message("tattack", "Setting state to 0.");
            player->catch_tell("You stop attempting to defend against attacks.\n");
       }
    }
    player->remove_prop(GUILD_FOCUS_DELAY_PROP);
    write("You feel ready to throw another attack.\n");
}

static void ability_msg(object actor, mixed* targets, string arg)
{
    write("You look for an opening to throw an attack.\n");
}

