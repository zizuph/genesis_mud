/*
 * /d/Gondor/guilds/militia/jab.c
 *
 * This code is copyright (c) 2001 by Scott A. Hardy and Alyssa Hardy.
 * Genesis is a game currently run through Chalmers University.
 * Scott and Alyssa Hardy have seen the 1991 document of Genesis'
 * called 'legal', and they do not forfeit any of their intellectual
 * property rights as that document supposes they would.  They are the
 * sole and complete owners of this code, which as of April 2001 they are
 * loaning to Genesis.  Genesis does not own this code, or
 * have any right to transfer it to anyone.  By its ongoing
 * use and storage of their code, Genesis acknowledges and agrees
 * to all of the above.
 *
 * Jab special for the Thornlin Militia
 *
 * Gwyneth and Auberon, March 4, 2001
 *
 * Modification log:
 * 05/13/01 - tweaked constants used in F_PENMOD determination to
 * even out rounding errors a bit, changed break points for damage
 * messages to make damage appear less (and to reduce monotony of
 * high damage messages -- the default message was getting very
 * boring). -- Auberon
 * June 16, 2001 - Added in the check on F_DARE_ATTACK. *blush*
 * Since the layout for the code is based somewhat on the kender
 * guild's sling, and they don't use F_DARE_ATTACK, it was left
 * out by mistake. -- Gwyneth
 */

#include <cmdparse.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "militia.h"

#define RESET_TIME	(11.0)
#define PREPARE_TIME	3.0

public void reset_jab(object who);
public void jab_target(object target, object who);
public string check_ready_enemy(object who, object target);

public string
check_ready(object who)
{
    string message;
 
    if (environment(who) &&
      (message = environment(who)->query_prop(ROOM_M_NO_ATTACK)))
        return (stringp(message) ? message : "A divine presence prevents " +
            "any attack.\n");
 
    if (who->query_prop(LIVE_I_ATTACK_DELAY) ||
      who->query_prop(LIVE_I_STUNNED))
        return "You are too stunned to jab.\n";
 
    if (who->query_evade() ||
      who->query_prop(PLAYER_I_EVADE_RESET))
        return "You can't seem to concentrate on jabbing when you " +
            "are busy evading attacks.\n";
}

public string
check_ready_enemy(object who, object target)
{
    string message;
 
    if (!living(target) || target == who || target->query_ghost())
        return "Jab whom?\n";
 
    if (message = target->query_prop(OBJ_M_NO_ATTACK))
        return (stringp(message) ? message : "A strong presence prevents " +
            "your attack.\n");
 
    if (who->query_met(target) && who->query_enemy(0) != target)
    {
        if (who->query_prop(LIVE_O_LAST_KILL) != target)
        {
            who->add_prop(LIVE_O_LAST_KILL, target);
            return "Attack " + target->query_the_name(who) + "? Please " +
                "confirm by trying again.\n";
        }
    }

    if (target != who->query_attack())
    {
        if (!F_DARE_ATTACK(who, target))
            return "Umm... no, You do not have enough self-discipline to " +
                "dare!\n";
    }
}

/*
 * Function name : jab
 * Description   : Pre-attack part of jab, initial parsing, etc.
 * Arguments     : string str - target as entered by player
 * Returns       : 0 on failure, 1 on success
 */
public int
jab(string str)
{
    int tmp;
    mixed targets;
    object target, who = this_player();
    string ready;

    tmp = who->query_prop(PLAYER_I_JAB_PREPARE);
    if (tmp)
    {
        notify_fail("You are already preparing a jab.\n");

        if (time() > tmp + 15)
        {
            notify_fail("You are not ready to jab again.\n");
            who->remove_prop(PLAYER_I_JAB_PREPARE);
            who->add_prop(PLAYER_I_JAB_RESET, time());
            set_alarm(RESET_TIME, 0.0, &reset_jab(who));
        }
        return 0;
    }
    else
    {
        ready = check_ready(who);
        if (strlen(ready))
        {
            notify_fail(ready);
            return 0;
        }

        if (who->query_skill(SS_MILITIA) < 1)
        {
            notify_fail("You don't have the first clue how to accomplish " +
                "that technique. Perhaps you should seek training.\n");
            return 0;
        }

        if (!objectp(find_wep(who, 1)))
        {
            notify_fail("You can't seem to accomplish that without a " +
                "proper weapon.\n");
            return 0;
        }

        if (!strlen(str))
        {
            target = who->query_attack();
        }
        else
        {
            if (!parse_command(str, environment(who), "%l", targets) ||
              !sizeof(targets = NORMAL_ACCESS(targets, 0, 0)))
            {
                notify_fail("Jab whom?\n");
                return 0;
            }

            target = targets[0];
        }

        ready = check_ready_enemy(who, target);
        if (strlen(ready))
        {
            notify_fail(ready);
            return 0;
        }

        tmp = who->query_prop(PLAYER_I_JAB_RESET);
        if (tmp)
        {
            if (time() > tmp + 15)
                set_alarm(RESET_TIME, 0.0, &reset_jab(who));
            notify_fail("You aren't ready to jab again.\n");
            return 0;
        }

        who->add_prop(PLAYER_I_JAB_PREPARE, time());
        set_alarm(PREPARE_TIME, 0.0, &jab_target(target, who));
        who->reveal_me(1);

        write("You look for an opening in " + 
            target->query_the_possessive_name(who) + " defences.\n");
        return 1;
    }
}

/*
 * Function name: jab_next
 * Description  : hits the next target in line
 * Arguments    : object who
 */
public void
jab_next(object who)
{
    object target = who->query_attack();
    if (objectp(target) && present(target, environment(who)))
    {
        jab_target(target, who);
    }
    else
    {
        write("There are no enemies for you to jab.\n");
        who->remove_prop(PLAYER_I_JAB_PREPARE);
        return;
    }
}

/*
 * Function name: jab_target
 * Description  : handles the hitting, messages
 * Arguments    : object target, object who
 */
public void
jab_target(object target, object who)
{
    int weaponstat, stats, hitres, total, stat;
    mixed hitresult;
    object weapon;
    string it_them, msg1, msg2, msg3, hdesc, wdesc;

    if (target->query_ghost())
    {
        jab_next(who);
        return;
    }
    else if (!present(target, environment(who)))
    {
        jab_next(who);
        return;
    }

    weapon = find_wep(who, 1);
    if (!objectp(weapon))
    {
        write("You can't jab someone without the proper weapon.\n");
        who->remove_prop(PLAYER_I_JAB_PREPARE);
        return;
    }
    else if (target->query_not_attack_me(who, -1))
    {
        who->remove_prop(PLAYER_I_JAB_PREPARE);
        who->add_prop(PLAYER_I_JAB_RESET, time());
        set_alarm(RESET_TIME, 0.0, &reset_jab(who));
        return;
    }

    if (who->query_attack() == 0)
        who->attack_object(target);

    who->reveal_me(1);

    weaponstat = (weapon->query_hit() + weapon->query_pen());
    stat = (who->query_occ_militia() ? who->query_stat(SS_OCCUP) :
        who->query_stat(SS_LAYMAN));
    stats = (((who->query_stat(SS_DEX) * 2) + stat) /10);
    total = ((weaponstat + stats + 7)/2); 
    stats = (who->query_skill(SS_MILITIA)+9);
    total += stats; total /= 2;
    hitres = F_PENMOD((total), (total + 3));
    /* F_PENMOD with 100 stats, 40/40 weapon should be 58,59 = 308 */
    /* F_PENMOD upped to 58,61=312 after weakening of impale special */
    if (who->query_combat_object()->cb_tohit(-1, 110, target) != 1)
        hitresult = target->hit_me(0, W_IMPALE, who, -1);
    else
        hitresult = target->hit_me(hitres, W_IMPALE, who, -1);

    who->add_prop(PLAYER_I_JAB_RESET, time());
    who->remove_prop(PLAYER_I_JAB_PREPARE);

    set_alarm(RESET_TIME, 0.0, &reset_jab(who));

    hdesc = hitresult[1];
    wdesc = weapon->short();

    if (target->query_hp() <= 0)
    {
        if (!(random(255) % 4))
        {
            who->catch_tell("With a look of grim determination, you throw " +
                "all your weight into a strike on " + 
                target->query_the_possessive_name(who) + " " + hdesc + 
                ", causing bones to snap and blood to spray.\n");
            target->catch_tell("With a look of grim determination, " + 
                who->query_the_name(target) + " throws all " + 
                who->query_possessive() + " weight into a strike on your " + 
                hdesc + ". As you struggle to stay conscious, you hear your " +
                "bones breaking and are nearly blinded with your own " +
                "spraying blood.\n");
            who->tell_watcher("With a look of grim determination, " + 
                QTNAME(who) + " throws all " + who->query_possessive() + 
                " weight into a " + "strike on " + QTPNAME(target) + " " + 
                hdesc + ". " + QCTNAME(target) + " turns pale as " + 
                target->query_possessive() + " bones break and blood " +
                "sprays.\n", target);
        }
        else
        {
            who->catch_tell(target->query_The_name(who) + " screams in " +
                "agony as you drive your " + wdesc + " through " + 
                target->query_possessive() + " " + hdesc + ". You withdraw " +
                "it quickly, allowing " + target->query_possessive() + 
                " body to fall.\n");
            target->catch_tell("You scream in agony as " + 
                who->query_the_name(target) + " drives " +
                who->query_possessive() + " " + wdesc + " through your " +
                hdesc + ".  As " + who->query_pronoun() + " withdraws it, " +
                "all goes dark.\n");
            who->tell_watcher(QCTNAME(target) + " screams in agony as " +
                QTNAME(who) + " drives " + who->query_possessive() + " " +
                wdesc + " completely through " + QTPNAME(target) + " " +
                hdesc + ".  As " + QTNAME(who) + " withdraws it, " +
                QTNAME(target) + " slumps to the ground, dead.\n", target);
        }

        target->do_die(who);
        return;
    }


    switch(hitresult[0])
    {
    case -2..0:
        msg1 = "You thrust your " + wdesc + " towards " + 
            target->query_the_name(who) + ", just barely missing " +
            target->query_possessive() + " " + hdesc + ".\n";
        msg2 = who->query_The_name(target) + " thrusts " +
            who->query_possessive() + " " + wdesc + " towards you, just " +
            "barely missing your " + hdesc + ".\n";
        msg3 = QCTNAME(who) + " thrusts " + who->query_possessive() + " " +
            wdesc + " towards " + QTNAME(target) + ", just barely missing " +
            target->query_possessive() + " " + hdesc + ".\n";
        break;

    case 1..4:
        msg1 = "You jab " + target->query_the_name(who) + " lightly " +
            "with your " + wdesc + ", nicking " + target->query_possessive() +
            " " + hdesc + ".\n";
        msg2 = who->query_The_name(target) + " jabs you lightly with " +
            who->query_possessive() + " " + wdesc + ", nicking your " + hdesc +
            ".\n";
        msg3 = QCTNAME(who) + " jabs " + QTNAME(target) + " lightly with " +
            who->query_possessive() + " " + wdesc + ", nicking " +
            target->query_possessive() + " " + hdesc + ".\n";
        break;

    case 5..8:
        msg1 = "You jab at " + target->query_the_possessive_name(who) +
            " " + hdesc + ", but deliver only a glancing blow.\n";
        msg2 = who->query_The_name(target) + " jabs at your " + hdesc +
            ", wounding you slightly.\n";
        msg3 = QCTNAME(who) + " jabs at " + QTPNAME(target) + " " + hdesc +
            ", causing a bit of damage.\n";
        break;

    case 9..14:
        msg1 = target->query_The_name(who) + " grimaces in pain as you jab " +
            "your " + wdesc + " into " + target->query_possessive() + " " +
            hdesc + ".\n";
        msg2 = "You grimace in pain as " + who->query_the_name(target) +
            " drives " + who->query_possessive() + " " + wdesc + " deeply " +
            "into your " + hdesc + ".\n";
        msg3 = QCTNAME(target) + " grimaces in pain as " + QTNAME(who) +
            " drives " + who->query_possessive() + " " + wdesc + " deep " +
            "into " + QTPNAME(target) + " " + hdesc + ".\n";
        break;

    case 15..20:
        msg1 = "Seeing " + target->query_the_name(who) + " off-guard, " +
            "you bring the butt of your " + wdesc + " whipping around, " +
            "battering " + target->query_objective() + " painfully in the " +
            hdesc + ".\n";
        msg2 = "Seeing you off-guard, " + who->query_the_name(target) +
            " brings the butt of " + who->query_possessive() + " " + wdesc +
            " whipping around, battering you painfully in the " + hdesc + ".\n";
        msg3 = "Seeing " + QTNAME(target) + " off-guard, " + QTNAME(who) + 
            " brings the butt of " + who->query_possessive() + " " + wdesc +
            " whipping around, battering " + QTNAME(target) + " painfully in " +
            "the " + hdesc + ".\n";
        break;

    case 21..25:
        msg1 = "You smile in grim satisfaction as you deal " +
            target->query_the_name(who) + " a serious wound to the " + hdesc +
            ".\n";
        msg2 = who->query_The_name(target) + " smiles in grim satisfaction " +
            "as " + who->query_pronoun() + " badly injures your " + hdesc + 
            ".\n";
        msg3 = QCTNAME(who) + " smiles in grim satisfaction as " +
            who->query_pronoun() + " deals a major wound to " + 
            QTPNAME(target) + " " + hdesc + ".\n";
        break;

    case 26..30:
        msg1 = "In one fluid motion, you thrust aside a clumsy blow and " +
            "lunge forward, nearly knocking " + target->query_the_name(who) +
            " down with your blow to " + target->query_possessive() + " " +
            hdesc + ".\n";
        msg2 = "In one fluid motion, " + who->query_the_name(target) +
            " thrusts aside your clumsy attack and lunges forward with " +
            who->query_possessive() + " " + wdesc + ", nearly knocking you " +
            "over with an excruciating blow to the " + hdesc + ".\n";
        msg3 = "In one fluid motion, " + QTNAME(who) + " thrusts aside " +
            QTPNAME(target) + " clumsy blow and lunges forward, nearly " +
            "knocking " + target->query_objective() + " down with a blow " +
            "to the " + hdesc + ".\n";
        break;

    case 31..35:
        msg1 = target->query_The_name(who) + " turns pale as your " + wdesc +
            " slams into " + target->query_possessive() + " " + hdesc + ".\n";
        msg2 = "You feel the blood drain from your face as " +
            who->query_the_possessive_name(target) + " " + wdesc + " slams " +
            "into your " + hdesc + ".\n";
        msg3 = QCTNAME(target) + " turns pale as " + QTPNAME(who) + " " +
            wdesc + " slams into " + target->query_possessive() + " " + hdesc + 
            ".\n";
        break;

    case 36..40:
        msg1 = "You feel more confident as your " + wdesc + " badly wounds " +
            target->query_the_name(who) + " in the " + hdesc + ".\n";
        msg2 = who->query_The_name(target) + " looks increasingly confident " +
            "as " + who->query_possessive() + " " + wdesc + " gravely " +
            "injures your " + hdesc + ".\n";
        msg3 = QCTNAME(who) + " looks more confident as " + 
            who->query_pronoun() + " gravely injures " + QTPNAME(target) +
            " " + hdesc + ".\n";
        break;

    case 41..45:
        msg1 = target->query_The_name(who) + " loses " + 
            target->query_possessive() + " concentration for a split " +
            "second, and you thrust your " + wdesc + " nearly through " +
            target->query_possessive() + " " + hdesc + ".\n";
        msg2 = "You lose your concentration for a split second, only to " +
            "receive an excruciating jab. You realize too late that " +
            who->query_the_possessive_name(target) + " " + wdesc + 
            " has horribly wounded your " + hdesc + ".\n";
        msg3 = QCTNAME(target) + " appears distracted for a split second, " +
            "only to find " + target->query_possessive() + " " + hdesc +
            " gruesomely impaled on " + QTPNAME(who) + " " + wdesc + ".\n";
        break;

    case 46..50:
        it_them = (hdesc == "legs" ? "them" : "it");
        msg1 = "Turning your back on " + target->query_the_name(who) + " for " +
            "a moment, you quickly spin, whipping your " + wdesc + " into " +
            target->query_possessive() + " " + hdesc +  ", nearly crushing " +
            it_them + ".\n";
        msg2 = who->query_The_name(target) + " turns " + 
            target->query_possessive() + " back on you for a moment, and " +
            "you close to strike. " + who->query_The_name(target) + 
            " suddenly spins, whipping " + who->query_possessive() +
            wdesc + " into your " + hdesc + " nearly crushing " + it_them +
            ".\n";
        msg3 = QCTNAME(who) + " turns " + who->query_possessive() + 
            " back on " + target->query_the_name(who) + " for a moment, " +
            "tricking " + target->query_objective() + " into advancing. " +
            QCTNAME(who) + " spins suddenly, whipping " +
            who->query_possessive() + " " + wdesc + " into " + 
            QTPNAME(target) + " " + hdesc + ", nearly crushing " +
            it_them + ".\n";
        break;

    case 51..65:
        msg1 = "You wonder what keeps " + target->query_the_name(who) +
            " fighting as you bring your " + wdesc + " crashing into " +
            "the side of " + target->query_possessive() + " " + hdesc + ".\n";
        msg2 = "You wonder what you are doing here, as " + 
            who->query_the_name(target) + " brings " + 
            who->query_possessive() + " " + wdesc + " crashing into the " +
            "side of your " + hdesc + ".\n";
        msg3 = "You begin to wonder why " + QTNAME(target) + " doesn't run " +
            "as you watch " + QTPNAME(who) + " " + wdesc + " come " +
            "crashing into the side of " + who->query_possessive() + " " +
            hdesc + ".\n";
        break;

    case 66..85:
        msg1 = "You look away briefly as you see the gruesome results " +
            "of your blow to " + target->query_the_possessive_name(who) +
            " " + hdesc + ".\n";
        msg2 = "You nearly lose consciousness as " + 
            who->query_the_possessive_name(target) + " " + wdesc + 
            "gruesomely mangles your " + hdesc + ".  You feel an urge to " +
            "run, but fear you are too weak.\n";
        msg3 = QCTNAME(target) + " nearly loses consciousness as " + 
            QTNAME(who) + " delivers a gaping wound to " + QTPNAME(target) + 
            " " + hdesc + ".\n";
        break;

    default:
        msg1 = "With a look of grim determination, you throw all your weight " +
            "into a strike on " + target->query_the_possessive_name(who) +
            " " + hdesc + ", causing bones to snap and blood to spray.\n";
        msg2 = "With a look of grim determination, " + 
            who->query_the_name(target) + " throws all " + 
            who->query_possessive() + " weight into a strike on your " + hdesc +
            ". As you struggle to stay conscious, you hear your bones " +
            "breaking and are nearly blinded with your own spraying blood.\n";
        msg3 = "With a look of grim determination, " + QTNAME(who) +
            " throws all " + who->query_possessive() + " weight into a " +
            "strike on " + QTPNAME(target) + " " + hdesc + ". " + 
            QCTNAME(target) + " turns pale as " + target->query_possessive() +
            " bones break and blood sprays.\n";
        break;

    }

    who->catch_tell(msg1);
    target->catch_tell(msg2);
    who->tell_watcher(msg3, target);

    log_file("militia_jab", extract(ctime(time()), 4, 15) +
        capitalize(who->query_real_name()) + " jabbed at: " +
        target->query_real_name() + "\nFile: " + file_name(target) + "\n" +
        "Weaponstat: " + weaponstat + ", Stats: " + stats + " Guild stat: " +
        stat + "\nHitresult: " + hitresult[0] + " Pen: " +
        hitres + " Damage: " + hitresult[3] + "\nEnemy Avg: " + 
        target->query_average_stat() + " Enemy max hps: " + 
        target->query_max_hp() + "\n\n");
    return;
}

/* Function name: reset_jab
 * Description  : Resetting the special
 * Arguments    : object who - jabber
 */
public void
reset_jab(object who)
{
    who->catch_tell("\nYou feel able to jab again.\n\n");
    who->remove_prop(PLAYER_I_JAB_RESET);
    who->remove_prop(PLAYER_I_JAB_PREPARE);
}
