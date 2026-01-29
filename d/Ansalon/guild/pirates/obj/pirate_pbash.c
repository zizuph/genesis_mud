#pragma strict_types

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <tasks.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit "/d/Genesis/specials/std/damage";

#define BLOOD_OBJ "/d/Ansalon/goodlund/nethosak/city/std/blood"
#define PIRATE_ALT_MSG "_pirate_alt_msg"


public void
config_ability()
{
    ::config_ability();
    set_combat_aid(10);
    set_tohit(75);
    set_skills(SS_SPECIAL_STAGGER);
    set_stats(({ SKILL_AVG, TS_DEX, TS_STR, SKILL_END }));
    set_ability_prep_time(6);
    set_ability_cooldown_time(9);
    set_dt(W_BLUDGEON);
    set_ability_name("pbash");
    
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
        if(!enemy->query_humanoid())
        {
            attack_message = ({"You strike "+QTNAME(enemy)+" with your bottle.\n",
                                QCTNAME(player)+" strikes you with "+HIS(player)+
                               " bottle.\n",
                               QCTNAME(player)+" strikes "+QTNAME(enemy)+" with "+
                               HIS(player)+" bottle.\n"
                             });
        }
        else
        {
            switch (phurt)
            {
                case 0:
                    attack_message = ({
                        "Raising your bottle, you charge straight at "+QTNAME(enemy)+
                            ", but still bleary from last night's debauchery, you miss "+
                            HIM(enemy)+" by a mile.\n",
                            QCTNAME(player)+" raises "+HIS(player)+" bottle as "+
                            HE(player)+" charges straight at you. Luckily, in "+
                            HIS(player)+" drunken haste "+HE(player)+
                            " misses you by a mile.\n",
                            QCTNAME(player)+" raises "+HIS(player)+" bottle as "+
                            HE(player)+" charges straight at "+QTNAME(enemy)+
                            ". But in "+HIS(player)+" drunken haste "+HE(player)+
                            " misses by a mile.\n"
                            });
                    break;
                case 1..5:
                    attack_message = ({
                        "Holding your bottle tight, you swing it at "+QTNAME(enemy)+
                            ", but in your drunken "+"haste, you land only a glancing "+
                            "blow.\n",
                            "Holding "+HIS(player)+" bottle tight, "+QTNAME(player)+
                            " swings it "+"at you, but deals only a glancing blow.\n",
                            "Holding "+HIS(player)+" bottle tight, "+QTNAME(player)+
                            " swings it at "+QTNAME(enemy)+", but deals only a glancing"+
                            " blow.\n"
                            });
                    break;
                case 6..9:
                    attack_message = ({
                        "In an effort to distract "+QTNAME(enemy)+", you toss your "+
                            "bottle up in the air.\nAs "+ QTNAME(enemy)+" follows it "+
                            "with "+HIS(enemy)+" eyes, you knee "+HIM(enemy)+" in the "+
                            "gut.\n",
                            QCTNAME(player)+" tosses "+HIS(player)+" bottle up in "+
                            "the air.\nAs you follow it with your eyes, "+HE(player)+
                            " knees you in the gut!\n",
                            "In an effort to distract "+QTNAME(enemy)+", "+
                            QTNAME(player)+" tosses "+HIS(player)+" bottle up in the "+
                            "air.\nAs "+QTNAME(enemy)+" follows it with "+HIS(enemy)+
                            " eyes, "+QTNAME(player)+" knees "+HIM(enemy)+" in the gut!\n"
                            });              
                    break;
                case 10..19:
                    attack_message = ({
                        "As "+QTNAME(enemy)+" moves in to strike you, you take a "+
                            "swig from your bottle and spit in "+HIS(enemy)+" face!\n"+
                            QCTNAME(enemy)+" rubs "+HIS(enemy)+" eyes, and you strike "+
                            HIM(enemy)+" soundly on "+HIS(enemy)+" leg.\n",
                            "As you move in to strike at "+QTNAME(player)+", "+
                            HE(player)+" takes a swig from "+HIS(player)+" bottle and "+
                            "spits in your face!\n"+QCTNAME(player)+" strikes you soundly "+
                            "on your leg, as you try to clear your eyes.\n",
                            "As "+QTNAME(enemy)+" moves in to strike at "+QTNAME(player)+
                            ", "+QTNAME(player)+" takes a swig from "+HIS(player)+
                            " bottle and spits in "+QTPNAME(enemy)+" face!\n"+
                            QCTNAME(player)+" strikes "+QTNAME(enemy)+" soundly on the "+
                            "leg, as "+HE(enemy)+" tries to clear his eyes.\n"
                            });
                    break;
                case 20..29:
                    attack_message = ({
                        "Snapping out of your drunken haze, you lunge at "+QTNAME(enemy)+
                            ", bashing "+HIM(enemy)+" on the nose with your bottle. Blood "+
                            "spurts everywhere.\n",
                            QCTNAME(player)+" snaps out of "+HIS(player)+" drunken haze, "+
                            "and lunges at you, bashing you on the nose with "+HIS(player)+
                            " bottle. Blood spurts everywhere.\n",
                            QCTNAME(player)+" snaps out of "+HIS(player)+" drunken haze "+
                            "and lunges at "+QTNAME(enemy)+", bashing "+HIM(enemy)+
                            " on the nose with "+HIS(player)+" bottle. Blood spurts "+
                            "everywhere.\n"
                            });
                    setuid();
                    seteuid(getuid());
                    clone_object(BLOOD_OBJ)->move(environment(enemy));
                    break;
                case 30..39:
                    attack_message = ({
                        "Swinging your bottle, you deliver a solid roundhouse punch to "+
                            QTNAME(enemy)+".\nWhile "+QTNAME(enemy)+
                            " is left seeing stars, you manage to sneak in another blow!\n",
                            "Swinging "+HIS(player)+" bottle, "+QTNAME(player)+
                            " delivers you a solid roundhouse punch.\n"+"While you are "+
                            "left seing stars, "+QTNAME(player)+" manages to sneak in "+
                            "another blow!\n",
                            "Swinging "+HIS(player)+" bottle, "+QTNAME(player)+
                            " delivers a solid roundhouse punch to "+QTNAME(enemy)+
                            ".\nWhile "+QTNAME(enemy)+" is left seing stars, "+
                            QTNAME(player)+" manages to sneak in another blow!\n"
                            });
                    break;
                case 40..99:
                    default_msg = "With a bloodthirsty cry of: 'No Quarter to bilge rats!'";
                    you_msg = " you";
                    
                    if(strlen(player->query_prop(PIRATE_ALT_MSG)) && player->query_prop(PIRATE_ALT_MSG)=="off")
                    {
                        attack_message = ({
                            "You bring your bottle crashing down on "+QTPNAME(enemy)+
                                " head, devastating "+HIM(enemy)+" with the blow.\n",
                                QCTNAME(player)+" brings "+HIS(player)+" bottle crashing "+
                                "down on your head, devastating you with the blow.\n",
                                QCTNAME(player)+ " brings "+HIS(player)+" bottle crashing "+
                                "down on "+QTPNAME(enemy)+" head, devastating "+HIM(enemy)+
                                " with the blow.\n"
                                });
                        break;
                    } 
                    else if(strlen(player->query_prop(PIRATE_ALT_MSG)))
                    {
                        default_msg = player->query_prop(PIRATE_ALT_MSG);
                    }
                    attack_message = ({
                        default_msg+you_msg+" "+
                            "bring your bottle crashing down on "+QTPNAME(enemy)+
                            " head, devastating "+HIM(enemy)+" with the blow.\n",
                            default_msg+" "+
                            QTNAME(player)+" brings "+HIS(player)+" bottle crashing "+
                            "down on your head, devastating you with the blow.\n",
                            default_msg+" "+
                            QTNAME(player)+ " brings "+HIS(player)+" bottle crashing "+
                            "down on "+QTPNAME(enemy)+" head, devastating "+HIM(enemy)+
                            " with the blow.\n"
                            });
                    break;
                    
                default:
                    attack_message = ({
                        "Grabbing your bottle, you hit "+QTNAME(enemy)+" hard over "+
                            "the head.\n",
                            "Grabbing "+HIS(player)+" bottle, "+QTNAME(player)+" hits you "+
                            "hard over the head.\n",
                            "Grabbing "+HIS(player)+" bottle, "+QTNAME(player)+" hits "+
                            QTNAME(enemy)+" hard over the head.\n"
                            });
                    break;
            }
        }

        /* message to the player */
        player->catch_msg(attack_message[0]);

        /* message to the enemy */
        enemy->catch_msg(attack_message[1]);

        /* message to onlookers */
        player->tell_watcher(attack_message[2], enemy);
    
        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(player);
        }
    
        return;
    }

    /* We get here if the attack missed */
    attack_message = ({
       "Raising your bottle, you charge straight at "+QTNAME(enemy)+
       ", but still bleary from last night's debauchery, you miss "+HIM(enemy)+" by a mile.\n",
       QCTNAME(player)+" raises "+HIS(player)+" bottle as "+HE(player)+
       " charges straight at you. Luckily, in "+HIS(player)+" drunken haste "+
       HE(player)+" misses you by a mile.\n",
       QCTNAME(player)+" raises "+HIS(player)+" bottle as "+HE(player)+
       " charges straight at "+QTNAME(enemy)+". But in "+HIS(player)+
       " drunken haste "+HE(player)+" misses "+QTNAME(enemy)+" by a mile.\n"
    });
    
    /* message to attacker */
    player->catch_msg(attack_message[0]);

    /* message to enemy */
    enemy->catch_msg(attack_message[1]);
 
    /* message to onlookers */
    player->tell_watcher(attack_message[2], enemy);
}

static int
check_valid_action(object player,
                   mixed* targets,
                   string arg,
                   int execute)
{
    if(!::check_valid_action(player, targets, arg, execute))
    {
        return 0;
    }

    object* bottles = filter(all_inventory(this_player()), &->id("bottle"));
    if (sizeof(bottles)<1)
    {
      write("You do not have a bottle to use for the attack.\n");
      return 0;
    }
    return 1;
}

static mixed* 
check_required_items(object actor,
                     mixed * targets,
                     string arg,
                     int pretest)
{

    object* bottles = filter(all_inventory(actor), &->id("bottle"));
    if (sizeof(bottles)<1)
    {
      write("You suddenly realize that you have misplaced the bottle you intended to use for bashing.\n");
      return 0;
    }

    // No need to return the bottle object, so we just call the default behavior.
    return ::check_required_items(actor, targets, arg, pretest);
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
        write("You are about to bash your intended target with your bottle, " +
              "but are stopped by some magic presence.\n");
    }
}

public void hook_special_complete()
{
    write("You feel ready to hit someone with your bottle again.\n");
}

public int force_fail(object player,mixed * items,object target, int 
                        resist,int result)
{
    object* bottles = filter(all_inventory(this_player()), &->id("bottle"));
    if (sizeof(bottles)<1)
    {
      write("You do not have a bottle to use for the attack.\n");
      return 1;
    }
    return 0;
}

static void ability_msg(object actor, mixed* targets, string arg)
{
    write("You start to consider using your bottle for something other than drinking.\n");
}
 
public void
hook_special_in_cooldown()
{
    write("You do not feel ready to hit someone with your bottle again.\n");
}

/*
 * Function name: hook_targets_gone
 * Description:   Return the string that will be printed to the actor when
 *                the targets has disappeared during the prepartion of the
 *                ability.
 * Returns:       The message to print
 */
public void
hook_targets_gone(object * targets)
{
    write("The "+ (sizeof(targets)> 1 ? "targets" : "target")+ " of " +
        "your bottle " + (sizeof(targets)> 1 ? "are" : "is") + 
        " no longer here.\n");
}
