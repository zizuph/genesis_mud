/* 
 *  /d/Emerald/common/guild/aod/special_attacks.c
 *
 *  The special attack code for the Army of Darkness guild in Emerald.
 *
 *  Copyright (c) January 2007, by Cooper Sherry (Gorboth)
 */

#include <language.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <time.h>

/* A global variable to hold the id for the alarm used for the special */
static private int crush_alarm = 0;

/* Prototypes */
public void     reset_crush();
public mixed    can_attack_with_occ_special(object target, string attack);
public void     ogre_crush(object target);
public void     ogre_crush2(object target);
public int      query_crush();
public void     new_crush_msg(object who);


/*
 * Function name:        reset_crush
 * Description  :        set the crush_alarm variable to 0, indicating
 *                       that a crush is no longer being prepared.
 */
public void
reset_crush()
{
    remove_alarm(crush_alarm);
    crush_alarm = 0;
} /* reset_crush */


/*
 * Function name: can_attack_with_occ_special
 * Description:   See if we are allowed to attack someone
 * Arguments:     object target - the thing we want to attack
 *                string attack - a name for the attack we want to use
 * Returns:       A string describing why we cannot attack or 0 if
 *                we can attack
 */
mixed
can_attack_with_occ_special(object target, string attack)
{
    mixed    why;
    object   who = query_shadow_who(),
            *enemies = who->query_enemy(-1);

    if (!target || !living(target) || !present(target, environment(who)))
    {
        return attack + " whom?\n";
    }

    if (who->query_prop(LIVE_I_ATTACK_DELAY) ||
        who->query_prop(LIVE_I_STUNNED))
    {
        return "You are too stunned to " + attack + ".\n";
    }
 
    if (stringp(why = target->query_prop(OBJ_M_NO_ATTACK)) ||
        stringp(why = environment(target)->query_prop(ROOM_M_NO_ATTACK)))
    {
        return why;
    }
    else if (why)
    {
        return "You sense a force protecting " + 
            target->query_the_name(who) + ".\n";
    }

    /* Someone might try defining this to block all special attacks */
    if (target->query_not_attack_me(who, -1))
    {
        /* A message should be given by query_not_attack_me(), so
         * no need to specify one here.
         */
        return "";
    }

    if ((!who->query_npc()) && (who->query_met(target)) &&
        !(who == target->query_attack()) &&
        (who->query_prop(LIVE_O_LAST_KILL) != target))
    {
        who->add_prop(LIVE_O_LAST_KILL, target);
        return "Attack " + target->query_the_name(who) + 
            "?!? Please confirm by trying again.\n";
    }
 
    if (!F_DARE_ATTACK(who, target))
    {
        /* The dis check should only be done if the player is not 
         * currently fighting the target. If they have been attacked
         * by the target, they should not be prevented from using
         * the special.
         */
        if (member_array(target, enemies) == -1)
        {
            return "Ogre or not, you don't dare to attack.\n";
        }
    }

    
    return 0;
}

/*
 * Function name: ogre_crush
 * Description:   Start the 'crush' attack.
 * Arguments:     object target - the person to attack
 */
public void
ogre_crush(object target)
{
    object  who = query_shadow_who(),
           *ogre_team,
            general;
    int     cdelay,
            i,
            kickroll;

    /* 15 second base delay plus a random 10 extra seconds with the
     * greater potiential to be lower the higher your "crush" skill
     * is. Avg is 20 seconds at max skills.
     */
    cdelay = (15 + (10 - (random(who->query_skills(
              SS_AOD_WALLOP)) / 10)));

    who->catch_msg("Your ogre mind starts trying to recall how to"
      + " manage a crushing blow.\n");

    /* Hmmm ... looks like the General might be on this Ogre's team,
     * kicking him in the butt. If so, we enact the chance for an
     * instant special! For details see tax_doc.txt
     */
    if (AOD_MASTER->get_info(who, "Buttkicked") == 1)
    {
        /* We need to make sure we are on the team of the General and
         * that the General is in the room.
         */
        ogre_team = who->query_team_others();
        kickroll = random(9);
        for (i = 0; i < sizeof(ogre_team); i++)
        {
            TELL_G("Kick check ... Kickroll is " + kickroll);
            general = ogre_team[i];
            who->remove_prop(AOD_JUST_KICKED);

            if (AOD_GENERAL(ogre_team[i]) && environment(ogre_team[i])
                == environment(who) && !kickroll)
            {
                if (who->query_prop(AOD_JUST_KICKED))
                {
                    who->catch_tell("Yikes! The General's foot just"
                      + " barely missed your butt!\n");
                    who->remove_prop(AOD_JUST_KICKED);
                }
                else
                {
                    TELL_G("general = " + general->query_real_name());
                    write_file(AOD_LOG_DIR + "buttkick_log",
                        TIME2FORMAT(time(), "mm/dd") + " ("
                      + ctime(time())[11..18] + ") "
                      + capitalize(this_player()->query_name())
                      + " got an instant special!\n");
                    who->catch_tell("OOOF!!! That buttkick helped you"
                      + " remember how to crush!\n");
                    general->catch_tell("THUMP!! You kick "
                      + capitalize(who->query_real_name())
                      + " right in the butt!\n");
                    tell_room(environment(who), "THUMP!! " + QCTNAME(general)
                      + " kicks " + QTNAME(who) + " squarely in the butt!\n",
                        ({ general, who }) );
                    cdelay = 1;
                    who->add_prop(AOD_JUST_KICKED, 1);
                }
            }
        }
    }

    crush_alarm = set_alarm(itof(cdelay), 0.0, &ogre_crush2(target));

    /* We want to determine if we are fighting a player. If so, we
     * will (in the race_soul) allow players to move between rooms
     * without interrupting the special.
     */
    if (interactive(target))
    {
        who->add_prop(AOD_I_CRUSH_STATUS, 2);
    }
    else
    {
        who->add_prop(AOD_I_CRUSH_STATUS, 1);
    }

    /* Initiate battle with the target */
    who->attack_object(target);

    /* reveal the player if he is hiding */
    who->reveal_me(0);
} /* ogre_crush */

 
/*
 * Function name: ogre_crush2
 * Description:   This is the unarmed combat attack for the Army of
 *                Darkness guild. It provides a 5% chance of knocking
 *                someone's shield to the ground in addition to the
 *                damage it causes.
 * Arguments:     object target - the target of the attack
 */
public void
ogre_crush2(object target)
{
    int     hitsuc, 
            phurt,
            ogrewc,
            wielded = 0; /* 0 - unarmed,
                          * 1 - one weapon,
                          * 2 - two weapons */
    string  how, 
            how2,
            how3,
            why,
            club_name;
    object  attacker = query_shadow_who(),
           *weapons = attacker->query_weapon(-1);

    /* The player must have moved between rooms ... no bouncing! lets
     * cancel the attack.
     */
    if (!crush_alarm)
    {
        return;
    }

    crush_alarm = 0;

    if (sizeof(weapons))
    {
        if (weapons[0]->query_wt() != W_CLUB)
        {
            attacker->catch_msg(
                "ERRRRR ... ?!? What's this fancy thing? " + capitalize(
                LANG_ADDART(weapons[0]->short())) + "?? How is an ogre"
              + " supposed to crush anything using that? Find a club"
              + " or use your fists!\n");
            return;
        }

        if(sizeof(weapons) > 1)
        {
            club_name = weapons[0]->short() + " and "
                      + weapons[1]->short();
            wielded = 2;
            if (weapons[1]->query_wt() != W_CLUB)
            {
                attacker->catch_msg(
                    "ERRRRR ... ?!? What's this fancy thing? "
                  + capitalize(LANG_ADDART(weapons[1]->short()))
                  + "?? How is an ogre supposed to"
                  + " crush anything using that? Find a club or"
                  + " use your fists!\n");
                return;
            }
        }
        else
        {
            club_name = weapons[0]->short();
            wielded = 1;
        }
    }
 
    /* If the target has already died, we switch to whoever we are
     * currently attacking.
     */
    if (!target)
    {
        target = attacker->query_attack();
    }

    /* make sure the target is still in the same room as the attacker */
    if (!target)
    {
        /* If the target has already died, we switch to whoever we are
         * currently attacking.
         */
        target = attacker->cb_query_attack();

        if (!target || environment(target) != environment(attacker))
        {
            attacker->catch_msg("You suddenly realize there is no one"
              + " here to crush. They must have slipped away!\n");
            return;
        }
        else
        {
            write("Your ogre brain notices you are fighting someone else."
              + " Good enough! Crush Crush Crush!\n");
        }
    }

    /* Has target become invalid somehow? */
    if (stringp(why = can_attack_with_occ_special(target, "crush")))
    {
        set_alarm(1.0, 0.0, &new_crush_msg(attacker));
        attacker->catch_msg(why);
        return;
    }

    /* The formulae below are much the same in terms of damage
     * potential as the gladiator charge (I believe.) The difference
     * is that we do not base things on dex. Ogres rely on their
     * strength and size. Ogres aren't the fastest or most dextrous
     * beings. Therefore, we use at flat value of 65 as the to_hit
     * chance.
     */
    if ((hitsuc = attacker->query_combat_object()->cb_tohit(-1, 65,
        target)) > 0)
    {
        /* attack successful! */
        phurt = target->hit_me(3 * 
           (F_PENMOD(MIN(attacker->query_stat(SS_STR), 300) / 5,
            25 + (attacker->query_skill(SS_AOD_WALLOP) * 125 / 100))),
            W_BLUDGEON, attacker, -1)[0];
    }
    else
    {
        /* attack missed. */
        phurt = target->hit_me(hitsuc, 0, attacker, -1)[0];
    }

    /* Lets log damage versus players ... */
    if (interactive(target))
    {
        write_file(AOD_LOG_DIR + "crush_log",
            TIME2FORMAT(time(), "mm/dd") + " ("
          + ctime(time())[11..18] + ") "
          + "Damage = " + phurt + " - "
          + capitalize(attacker->query_name()) + " vs. "
          + capitalize(target->query_name()) + "\n");
    }

    /* add fatigue */
    if (attacker->query_fatigue() < 5)
    {
        attacker->heal_hp(-(5 - attacker->query_fatigue()));
        attacker->set_fatigue(0);
        attacker->catch_msg("Ooof! Your ogre limbs are feeling tired and"
          + " drained.\n");
    }
    else
    {
        attacker->add_fatigue(-5);
    }

    if (phurt >= 0) 
    {
        /* remove some of the attacker's panic */
        attacker->add_panic(-3 - phurt / 5);

        how = "!\n" + QCTNAME(target) + " seems ";
        how2 = "!\nYou feel ";

        /* Give combat descriptions based on the percent damage done.
         * Because players spend such a huge percentage of their time
         * on combat, lets add lots of variety. */
        switch (phurt)
        {
            case 0:
                how += "to have avoided any damage.";
                how2 = "!\nYou seem to have avoided any damage.";
                break;
            case 1:
                how3  = "slightly rattled.";
                how2 += how3;
                how  += how3;
                break;
            case 2:
                how3  = "somewhat rattled.";
                how2 += how3;
                how  += how3;
                break;
            case 3:
                how3  = "slightly battered.";
                how2 += how3;
                how  += how3;
                break;
            case 4:
                how3  = "somewhat battered.";
                how2 += how3;
                how  += how3;
                break;
            case 5:
                how3  = "seriously battered.";
                how2 += how3;
                how  += how3;
                break;
            case 6:
                how3  = "somewhat bashed.";
                how2 += how3;
                how  += how3;
                break;
            case 7:
                how3  = "seriously bashed.";
                how2 += how3;
                how  += how3;
                break;
            case 8:
                how3  = "thoroughly bashed.";
                how2 += how3;
                how  += how3;
                break;
            case 9:
                how3  = "clearly throttled.";
                how2 += how3;
                how  += how3;
                break;
            case 10:
                how3  = "thoroughly throttled.";
                how2 += how3;
                how  += how3;
                break;
            case 11:
                how3  = "absolutely throttled.";
                how2 += how3;
                how  += how3;
                break;
            case 12:
                how3  = "rather pulverized.";
                how2 += how3;
                how  += how3;
                break;
            case 13:
                how3  = "thoroughly pulverized.";
                how2 += how3;
                how  += how3;
                break;
            case 14:
                how3  = "horribly pulverized.";
                how2 += how3;
                how  += how3;
                break;
            case 15..20:
                how3  = "fairly devastated.";
                how2 += how3;
                how  += how3;
                break;
            case 21..33:
                how3  = "seriously devastated.";
                how2 += how3;
                how  += how3;
                break;
            case 34..49:
                how3  = "thoroughly devastated.";
                how2 += how3;
                how  += how3;
                break;
            case 50..99:
                how3  = "completely devastated.";
                how2 += how3;
                how  += how3;
                break;
            default:
                how = " like an avalanche of death and destruction! Ribs"
                    + " crack and bones snap as "
                    + target->query_possessive() + " body is mashed"
                    + " into a lifeless pulp!";
                how2 = " like an avalanche of death and destruction! The"
                     + " last thing you remember is the sound of your"
                     + " own spine splintering as hot pain washes over"
                     + " your mind!";
                break;
        }

        switch (wielded)
        {
            default:
            case 0:
                attacker->catch_msg("SLAM!!! You bring your mighty fists"
                  + " down on " + target->query_the_name(attacker)
                  + how + "\n");
                target->catch_msg("SLAM!!! "
                  + attacker->query_The_name(target) + " brings "
                  + attacker->query_possessive() + " mighty fists"
                  + " down on you" + how2 + "\n");
                attacker->tell_watcher("SLAM!!! " + QCTNAME(attacker)
                  + " brings " + attacker->query_possessive()
                  + " mighty fists down on " + QTNAME(target)
                  + how + "\n", target);
                break;
            case 1:
                attacker->catch_msg("SWAT!!! You swing your " + club_name
                  + " down into " + target->query_the_name(attacker)
                  + how + "\n");
                target->catch_msg("SWAT!!! "
                  + attacker->query_The_name(target) + " swings "
                  + attacker->query_possessive() + " " + club_name
                  + " down into you" + how2 + "\n");
                attacker->tell_watcher("SWAT!!! " + QCTNAME(attacker)
                  + " swings " + attacker->query_possessive() + " "
                  + club_name + " down into " + QTNAME(target)
                  + how + "\n", target);
                break;
            case 2:
                attacker->catch_msg("BLAM!! BLAM!! One after the other"
                  + " you bring your " + club_name + " hurtling down"
                  + " on " + target->query_the_name(attacker)
                  + how + "\n");
                target->catch_msg("BLAM!! BLAM!! One after the other "
                  + attacker->query_The_name(target) + " brings "
                  + attacker->query_possessive() + " " + club_name
                  + " hurtling down on you" + how2 + "\n");
                attacker->tell_watcher("BLAM!! BLAM!! " + QCTNAME(attacker)
                  + " brings " + attacker->query_possessive() + " "
                  + club_name + " hurtling down on " + QTNAME(target)
                  + how + "\n", target);
                break;
        }

        if (target->query_hp() <= 0)
        {
            target->do_die(attacker);
        }

        set_alarm(1.0, 0.0, &new_crush_msg(attacker));
        return;
    }
            
    /* We get here if the attack missed */

    /* add some panic to the attacker */
    attacker->add_panic(1);
    /* I originally had a stun here if the Ogre missed. Given that the
     * Ogres are designed to miss 1/3 of the time, this seems like too
     * harsh a measure. So, I'm commenting it out for now.
     *  - Gorboth, October 2008
    attacker->add_attack_delay(5);
     */

    switch (wielded)
    {
        default:
        case 0:
            attacker->catch_msg("THUD!!! Your mighty fists smash"
              + " harmlessly into the ground, completely missing "
              + target->query_the_name(attacker) + ".\n");
            target->catch_msg("THUD!!! " + attacker->query_The_name(target)
              + " brings " + attacker->query_possessive() + " mighty fists"
              + " crashing harmlessly into the ground beside you.\n");
            attacker->tell_watcher("THUD!!! " + QCTNAME(attacker)
              + " brings " + attacker->query_possessive() + " mighty fists"
              + " crashing harmlessly into the ground beside "
              + QTNAME(target) + ".\n", target);
            break;
        case 1:
            attacker->catch_msg("WHOOSH!! Your " + club_name + " sails"
              + " cleanly over " + target->query_the_name(attacker)
              + "'s head, missing " + target->query_objective()
              + " entirely.\n");
            target->catch_msg("WHOOSH!! " + attacker->query_The_name(target)
              + "'s " + club_name + " sails cleanly over your head,"
              + " missing you entirely.\n");
            attacker->tell_watcher("WHOOSH!! " + QCTNAME(attacker)
              + "'s " + club_name + " sails cleanly over "
              + QTNAME(target) + "'s head, missing "
              + target->query_objective() + " entirely.\n", target);
            break;
        case 2: 
            attacker->catch_msg("WHUMP!! WHUMP!! Your " + club_name
              + " plow into the ground on either side of "
              + target->query_the_name(attacker) + ", missing "
              + target->query_objective() + " completely.\n");
            target->catch_msg("WHUMP!! WHUMP!! "
              + attacker->query_The_name(target) + "'s " + club_name
              + " plow into the ground on either side of you, missing"
              + " you completely.\n");
            attacker->tell_watcher("WHUMP!! WHUMP!! " + QCTNAME(attacker)
              + "'s " + club_name + " plow into the ground on either side"
              + " of " + QTNAME(target) + ", missing "
              + target->query_objective() + " completely.\n", target);
            break;
    }

    set_alarm(1.0, 0.0, &new_crush_msg(attacker));
} /* ogre_crush2 */


/*
 * Function name: query_crush
 * Description:   See if we are currently preparing to perform
 *                the special attack
 * Returns:       1 / 0 - preparing / not preparing
 */
public int
query_crush()
{
    return !!crush_alarm;
} /* query_crush */


/*
 * Function name:        new_crush_msg
 * Description  :        Lets the Ogre know they can crush again.
 * Arguments    :        object who - who to send the message to
 */
public void
new_crush_msg(object who)
{
    who->catch_tell("Hmmmmmmmmmmm ...It dawns on your tiny brain that you"
      + " could probably try for another crushing blow, if you haven't"
      + " already.\n");
    return;
} /* new_crush_msg */
