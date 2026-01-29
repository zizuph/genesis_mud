/*
 * /d/Ansalong/guild/kender_occ/sling.c
 *
 * Copyright (c) 2001 by Alyssa Hardy (Gwyneth)
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * The Secret Society sling special - ability to fire a pebble
 * out of a hoopak to cause damage to an opponent. Hoopak and
 * ammunition required.
 *
 * Coded by Gwyneth, July 1999
 * Updated by Gwyneth, January 2001 to add magic pebbles
 *
 * 26.sep.2003 Milan
 * Fixed some stuff in do_sling (called via alarm so write() and say()
 * functions should be used only when this_player() is properly set.
 *
 * September 16th 2006, Navarre changed reset time and execution time.
 * Kenders are bounce killing a lot of big npcs for xp, I changed these
 * times to try to prevent this.
 * I also added a cap on damage.
 *
 * April 2008, Navarre: I am getting a runtime about Integer + Float is not
 *                      allowed on the line tmp + ftoi(who->query_speed(16)).
 *                      It should be two ints, but I changed a little.
 *
 * April 2008, Navarre: The kender guild is dying out. One of their biggest complaints
 *                      were the stun from using the hoopak sling.
 *                      I changed the descriptions a bit to leave out the part of putting the
 *                      hoopak in the ground, and I removed the stun that came with it.
 */

#include <cmdparse.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

public void reset_sling(object who);
public void do_sling(object target, object who, object room);
public string check_ready_enemy(object who, object target);

/*
 * Function name: check_hoopak
 * Description  : Tests to see if a hoopak is wielded or not.
 * Arguments    : object who - the wielder
 * Returns      : 1 if wielded, 0 if not
 */
public int
check_hoopak(object who)
{
    object *weapons;

    /* Find all wielded weapons. */
    weapons = who->query_weapon(-1);

    switch(sizeof(weapons))
    {
    case 1:
        if (weapons[0]->id("hoopak"))
            return 1;
        return 0;

    case 2:
        if (weapons[0]->id("hoopak") || weapons[1]->id("hoopak"))
            return 1;
        return 0;

    default:
        return 0;

    }
}

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
        return "You are too stunned to sling anything.\n";

    if (who->query_kender_dodge() ||
      who->query_prop(DODGE_RESET))
        return "How can you sling when you're dodging all over the place?\n";
}

public string
check_ready_enemy(object who, object target)
{
    string message;

    if (!living(target) || target == who || target->query_ghost())
        return "Sling a pebble at whom?\n";

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
}

/*
 * Function name : sling
 * Description   : Pre-attack part of sling, initial parsing, etc.
 * Arguments     : string str - ammunition and target
 * Returns       : 0 on failure, 1 on success
 */
public int
sling(string str)
{
    mixed ammo, targets;
    object target, pebble, who = this_player();
    object room = environment(who);
    string str1, str2, ready;
    int tmp, wimpy_scale = who->query_whimpy();

    if (tmp = who->query_prop(SLING_PREPARE))
    {
        if (time() > tmp + 20)
        {
            notify_fail("You are not ready to sling again.\n");
            who->remove_prop(SLING_PREPARE);
            who->add_prop(SLING_RESET, time());
            set_alarm(who->query_speed(13), 0.0, &reset_sling(who));
        }
        else
        {
            notify_fail("You are already preparing to sling.\n");
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

        if (who->query_skill(SS_CTACT_SPECIAL) < 1)
        {
            notify_fail("You don't have enough skill to do that!\n");
            return 0;
        }

        if (wimp_check(who) < wimpy_scale)
        {
            notify_fail("You're too busy thinking about running away " +
                "to sling!\n");
            return 0;
        }

        if (!check_hoopak(who))
        {
            notify_fail("Oh no! Where's your hoopak?\n");
            return 0;
        }

        if (!strlen(str))
        {
            target = who->query_attack();

            if (!objectp(pebble = present("pebble", who)))
            {
                notify_fail("You have nothing to sling!\n");
                return 0;
            }
        }
        else
        {
            /* sling goblin */
            sscanf(str, "%s", str2);

            /* sling pebble at goblin */
            sscanf(str, "%s at %s", str1, str2);

            if (!strlen(str1))
            {
                if (!objectp(pebble = present("pebble", who)))
                {
                    notify_fail("Sling what at whom?\n");
                    return 0;
                }
            }
            else
            {
                if (!parse_command(str1, all_inventory(who), "%i", ammo) ||
                    !sizeof(ammo = NORMAL_ACCESS(ammo, 0, 0)))
                {
                    notify_fail("Sling what at whom?\n");
                    return 0;
                }

                if (!ammo[0]->id("pebble"))
                {
                    notify_fail("You can't seem to sling that.\n");
                    return 0;
                }

                pebble = ammo[0];
            }

            if (!parse_command(str2, environment(who), "%l", targets) ||
               !sizeof(targets = NORMAL_ACCESS(targets, 0, 0)))
            {
                notify_fail("Sling what at whom?\n");
                return 0;
            }

            target = targets[0];
        }

        if (strlen(ready = check_ready_enemy(who, target)))
        {
            notify_fail(ready);
            return 0;
        }

        if (tmp = who->query_prop(SLING_RESET))
        {
            /* Odd run-time. Let's see if it changes shape now. */
            if ((time() - tmp) > ftoi(who->query_speed(20)))
            {
                set_alarm(who->query_speed(13), 0.0, &reset_sling(who));
            }
            notify_fail("You aren't ready to sling again.\n");
            return 0;
        }

        who->add_prop(SLING_PREPARE, time());
        set_alarm(who->query_speed(3+random(3)), 0.0, &do_sling(target, who, room));
        who->reveal_me(1);

        write("You load a pebble into the sling of your hoopak while taking careful aim at " +
              target->query_the_name(who) + ".\n");
        
        say(QCTNAME(who) + " loads a pebble into "+who->query_possessive() +
            " hoopak while taking aim.\n");

        if (pebble->query_prop(HEAP_I_IS))
        {
            pebble->restore_heap();
            pebble->set_heap_size(pebble->num_heap() - 1);
        }
        else
        {
            pebble->remove_object();
        }

        return 1;
    }
}

/*
 * Function name: do_sling
 * Description  : handles the hitting, messages
 * Arguments    : object target, object who, object room
 */
public void
do_sling(object target, object who, object room)
{
    int wimpy_scale, weaponstat, stats, total, hitres, magic = 0;
    mixed hitresult;
    object weapon;
    string dmsg1, dmsg2, dmsg3, how, hdesc;
    string khe, khis, khim, ktname, kTname, ehe, ehis, ehim, etname, eTname;

    if (!objectp(who)) return;
    if (!objectp(target))
    {
        who->catch_tell("You sling pebble out of sight.\n");
        who->remove_prop(SLING_PREPARE);
        return;
    }

    wimpy_scale = who->query_whimpy();

    if (environment(who) != room)
    {
        who->catch_tell("Your sling goes wild, as you have moved. The stone " +
            "flies out of sight.\n");
        who->remove_prop(SLING_PREPARE);
        return;
    }
    else if (wimp_check(who) < wimpy_scale)
    {
        who->catch_tell("You're too busy thinking about running away " +
            "to sling!\n");
        who->remove_prop(SLING_PREPARE);
        return;
    }
    else if (target->query_ghost())
    {
        who->catch_tell("Your pebble flies right through " +
            target->query_the_name(who) + "!\n");
        who->remove_prop(SLING_PREPARE);
        return;
    }
    else if (!present(target, room))
    {
        who->catch_tell("You pull back on the hoopak's sling and let fire, " +
            "noticing too late that your target is gone.\n");
        who->tell_watcher(QCTNAME(who) + " pulls back on " + who->query_possessive() +
            " hoopak's sling and lets fly, noticing too late that the " +
            "target is gone.\n");
        who->remove_prop(SLING_PREPARE);
        return;
    }
    else if (!check_hoopak(who))
    {
        who->catch_tell("Oh no! Where'd your hoopak go?\n");
        who->remove_prop(SLING_PREPARE);
        return;
    }

    if (target->query_not_attack_me(who, -1))
    {
        who->remove_prop(SLING_PREPARE);
        who->add_prop(SLING_RESET, 1);
        set_alarm(who->query_speed(13), 0.0, &reset_sling(who));
        return;
    }

    if (who->query_attack() == 0)
        who->attack_object(target);

    who->reveal_me(1);

    weapon = (who->query_weapon(-1))[0];

    weaponstat = ((weapon->query_hit() + weapon->query_pen()) / 2);
    weaponstat *= 10;
    weaponstat /= 8;

    stats = (((who->query_stat(SS_DEX) * 2) + who->query_stat(SS_OCCUP)) / 8);

    total = ((weaponstat + stats) / 2);

    hitres = F_PENMOD(total, who->query_skill(SS_CTACT_SPECIAL));

    if (who->query_combat_object()->cb_tohit(-1, 100, target) != 1)
        hitresult = target->hit_me(0, W_BLUDGEON, who, -1);
    else
        hitresult = target->hit_me(hitres, W_BLUDGEON, who, -1);

    who->add_prop(SLING_RESET, time());
    who->remove_prop(SLING_PREPARE);

    set_alarm(who->query_speed(13), 0.0, &reset_sling(who));

    hdesc = hitresult[1];

    /* kender info */
    khe = who->query_pronoun();
    khis = who->query_possessive();
    khim = who->query_objective();
    ktname = who->query_the_name(target);
    kTname = who->query_The_name(target);

    /* enemy info */
    ehe = target->query_pronoun();
    ehis = target->query_possessive();
    ehim = target->query_objective();
    etname = target->query_the_name(who);
    eTname = target->query_The_name(who);

    if (target->query_hp() <= 0)
    {
        if (target->query_guild_name_race() == "Red Fang Guild")
        {
            dmsg1 = (QCTNAME(who) + " sends a stone flying at " +
                QTNAME(target) + ", which strikes " + ehis +
                " heay with a loud crack. " + QCTNAME(target) + " slumps to " +
                "the ground, drooling slightly as " + QTNAME(who) +
                " scrunches up " + khis + " face in imitation of a goblin. " +
                "'Red Fang Forever!' " + khe + " yells in mockery.");
            dmsg2 = (kTname + " sends a stone flying at you, which strikes " +
                "your head with a loud crack. You slump to the ground, a bit " +
                "of drool slipping from between your slack lips. Just as " +
                "darkness overtakes your consciousness, you see " + ktname +
                " scrunch up " + khis + " face in imitation of a goblin. " +
                "'Red Fang Forever!' " + khe + " yells in mockery. The " +
                "words ring in your ears, the last you hear in this lifetime.");
            dmsg3 = ("You send a stone flying at " + etname + ", which " +
                "strikes " + ehis + " head with a loud crack. " + eTname +
                " slumps to the ground, drooling slightly. You scrunch up " +
                "your face in imitation of a goblin. 'Red Fang Forever!' you " +
                "yell in mockery.");
        }
        else
        {
            switch(random(7))
            {
            case 0:
                dmsg1 = (QCTNAME(who) + " lets a stone fly from " + khis +
                    " hoopak that lands with a sharp crack, square between " +
                    "the eyes of " + QTNAME(target) + ", who stares blankly " +
                    "into space before slumping to the ground. " +
                    QCTPNAME(who) + " concentrated expression brightens as " +
                    khe + " hugs " + khis + " hoopak, " +
                    "delighted at the wonderful shot.");
                dmsg2 = (kTname + " lets a stone fly from " + khis +
                    " hoopak that lands with a sharp crack, square between " +
                    "your eyes. You stare blankly into space before " +
                    "slumping to the ground, your last sight that of " +
                    ktname + " hugging " + khis + " hoopak, " +
                    "delighted at the wonderful shot.");
                dmsg3 = ("You let a stone fly from your hoopak, which lands " +
                    "with a sharp crack, square between the eyes of " +
                    etname + ", who stares blankly into space before " +
                    "slumping to the ground. You hug your hoopak, " +
                    "delighted at the wonderful shot.");
                break;
            case 1:
                dmsg1 = (QCTNAME(who) + " flings a stone from " + khis +
                    " hoopak at " + QTNAME(target) + " with deadly " +
                    "accuracy, and " + ehe + " staggers for a final brief " +
                    "moment. You hear some wild sounds, and are amazed to " +
                    "see " + QTNAME(who) + " dancing around with " + khis +
                    " hoopak held high, revelling in the victory.");
                dmsg2 = (kTname + " flings a stone from " + khis + " hoopak " +
                    "at you with deadly accuracy. You stagger for a brief " +
                    "moment, your final sight that of " + ktname +
                    " dancing around with " + khis + " hoopak held " +
                    "high, revelling in the victory.");
                dmsg3 = ("You fling a stone from your hoopak at " + etname +
                    " with deadly accuracy, and " + ehe + " staggers for a " +
                    "final brief moment. You hold your hoopak high " +
                    "with a mighty kender victory cry. You dance " +
                    "around with your hoopak, revelling in the " +
                    "victory.");
                break;
            case 2:
                dmsg1 = (QCTNAME(who) + " lets a stone fly from " + khis +
                    " hoopak that sends " + QTNAME(target) + " plummeting " +
                    "to the ground. With a cheer, " + QTNAME(who) + " swings " +
                    khis + " hoopak wildly" + " while running to " +
                    "inspect " + khis + " fallen foe. Placing " + khis +
                    " foot mightily on the corpse, " + khe + " remarks with " +
                    "a smug face: 'That'll teach 'em to mess with a kender!'");
                dmsg2 = (kTname + " lets a stone fly from " + khis +
                    " hoopak that sends you forcefully to the ground. With " +
                    "a cheer, " + ktname + " swings " + khis + " hoopak wildly " +
                    "while running towards you. " + khe + " places " +
                    khis + " foot on your prone form, and the last thing " +
                    "you hear is " + ktname + " remarking with a smug " +
                    "voice: 'That'll teach 'em to mess with a kender!'");
                dmsg3 = ("You let a stone fly from your hoopak that sends " +
                    etname + " plummeting to the ground. With a cheer you " +
                    "give your hoopak an expertly swing and run to inspect " +
                    "your fallen foe. Placing your foot mightily on the " +
                    "corpse, you remark in a smug voice: 'That'll teach 'em " +
                    "to mess with a kender!'");
                break;
            case 3:
                dmsg1 = ("As " + QTNAME(who) + " lets a stone fly from " +
                    khis + " hoopak, you hear a resounding thump as it " +
                    "strikes " + QTNAME(target) + " in the forehead. Hoopak " +
                    "in hand, " + khe + " creeps toward the fallen victim " +
                    "with a solemn expression, remarking mostly to " + khim +
                    "self: 'Some people have to learn the hard way.'");
                dmsg2 = ("As " + ktname + " lets a stone fly from " + khis +
                    " hoopak, you feel a burst of pain throughout your head " +
                    "as it strikes you. You slump to the ground. Your last " +
                    "sight is of " + ktname + " creeping towards you with a " +
                    "solemn expression. " + khe + " remarks mostly to " + khe +
                    "self: 'Some people have to learn the hard way.'");
                dmsg3 = ("As you let a stone fly from your hoopak, you hear " +
                    "a resounding thump as it strikes " + etname + " in the " +
                    "forehead. Hoopak in hand, you creep towards your fallen " +
                    "foe. Feeling very solemn, you remark to yourself: " +
                    "'Some people have to learn the hard way.'");
                break;
            case 4:
                dmsg1 = (QCTNAME(who) + " flings a stone from " + khis +
                    " hoopak at " + QTNAME(target) + " with " + "deadly " +
                    "accuracy, and " + QTNAME(target) + " staggers for a " +
                    "final brief moment. Looking at the fallen victim in " +
                    "shock, " + QTNAME(who) + " murmers: 'Oops!' " + khe +
                    " shrugs off the brief moment of silence and gives " +
                    khis + " hoopak a lovingly pet.");
                dmsg2 = (kTname + " flings a stone from " + khis + " hoopak " +
                    "at you with deadly accuracy, making you stagger " +
                    "briefly before collapsing to the ground. As your " +
                    "vision goes black, the last thing you hear is: 'Oops!'");
                dmsg3 = ("You fling a stone from your hoopak at " + etname +
                    " with deadly accuracy, and " + ehe + " staggers for a " +
                    "final brief moment. Looking at the fallen victim in " +
                    "shock, you murmur: 'Oops!' You shrug off a brief " +
                    "moment of silence and give your hoopak a lovingly pet.");
                break;
            case 5:
                dmsg1 = (QCTNAME(who) + " lets a stone fly from " + khis +
                    " hoopak that sends " + QTNAME(target) + " falling to " +
                    "the ground. " + QCTNAME(who) + " shows off " + khis +
                    " hoopak with a grandiose gesture, " +
                    "puffs out " + khis + " chest, and attempts to harden " +
                    khis + " childlike features into the visage of a " +
                    "fearsome warrior. You feel sure that the effort is " +
                    "in vain.");
                dmsg2 = (kTname + " lets a stone fly from " + khis +
                    " hoopak that sends you falling to the ground. As your " +
                    "lifeblood slowly drains from your body, you see " +
                    ktname + " show off " + khis + " hoopak " +
                    "with a grandiose gesture, puff up " + khis + " chest " +
                    "and attempt to harden " + khis + " childlike features " +
                    "into the visage of a fearsome warrior. Despite the " +
                    "gravity of the situation, you can't help but give off " +
                    "a small wry laugh.");
                dmsg3 = ("You let a stone fly from your hoopak that sends " +
                    etname + " falling to the ground with a mortal wound. " +
                    "You show off your hoopak with a grandiose " +
                    "gesture, puff out your chest, and harden your features " +
                    "into the visage of a fearsome warrior. Unexpectedly, " +
                    "you hear a small laugh come from the dying " +
                    target->query_art_name(who) + ". You wonder what " +
                    ehe + " was laughing about.");
                break;
            case 6:
                dmsg1 = (QCTNAME(who) + " lets a stone fly from " + khis +
                    " hoopak. You hear a resounding thump as it strikes " +
                    QTNAME(target) + " in the forehead. As " + QTNAME(target) + " falls, " + QTNAME(who) +
                    " lets out a gleeful howl of triumph.");
                dmsg2 = (kTname + " lets a stone fly from " + khis +
                    " hoopak. You hear a resounding thump and shooting pain " +
                    "as it strikes you in the forehead. You fall to the " +
                    "ground, " + who->query_the_possessive_name(target) +
                    " gleeful howls of triumph ringing in your ears.");
                dmsg3 = ("You let a stone fly from your hoopak. You hear a " +
                    "resounding thump as it strikes " + etname + " in the " +
                    "forehead. " + eTname + " falls to the ground as you " +
                    "let out a gleeful howl of triumph.");
                break;
            default:
                dmsg1 = (QCTNAME(who) + " sends a stone flying from " +
                    khis + " hoopak. It hits " + QTNAME(target) + " square " +
                    "in the forehead, killing " + ehim + ".");
                dmsg2 = (kTname + " sends a stone flying from " + khis +
                    " hoopak. It hits you square in the forehead with a " +
                    "mortal blow.");
                dmsg3 = ("You send a stone flying from your hoopak. It hits " +
                    etname + " square in the forehead, killing " + ehim + ".");
                break;
            }
        }

        /* Send death message to the slinger. */
        who->catch_tell(dmsg3 + "\n");

        /* Send death message to the watcher(s). */
        who->tell_watcher(dmsg1 + "\n", target);

        /* Send death message to the target. */
        target->catch_tell(dmsg2 + "\n");

        /* Make the target die. */
        target->do_die(who);

        return;
    }

    /* Choose hit/miss messages. */
    switch(hitresult[0])
    {
    case -1..0:
        how = "but it flies wide and misses";
        break;
    case 1..5:
        how = "leaving slight bruises";
        break;
    case 6..10:
        how = "leaving bruises";
        break;
    case 11..15:
        how = "leaving painful bruises";
        break;
    case 16..20:
        how = "leaving severe bruises";
        break;
    case 21..25:
        how = "leaving horrible bruises";
        break;
    default:
        how = "landing with a sharp crack";
        break;
    }

    /* Send hit/miss message to slinger. */
    who->catch_tell("You let the stone fly from your hoopak " +
        "towards " + target->query_the_possessive_name(who) + " " + hdesc +
        ", " + how + ".\n");

    /* Send hit/miss message to target. */
    target->catch_tell(who->query_The_name(target) + " let's a stone fly " +
        "from " + khis + " hoopak towards your " + hdesc + ", " + how + ".\n");

    /* Send hit/miss message to watcher(s). */
    who->tell_watcher(QTNAME(who) + " let's a stone fly from " + khis +
        " hoopak towards " + QTPNAME(target) + " " + hdesc + ", " +
        how + ".\n", target);

    log_file("/kender/sling", extract(ctime(time()), 4, 15) +
        " " + who->query_name() + " slung at: " + target->query_name() +
        "\nFile: " + file_name(target) + "\n" +
        " skill: " + who->query_skill(SS_CTACT_SPECIAL) + "\nDex: " +
        who->query_stat(SS_DEX) + " Guild stat: " + who->query_stat(SS_OCCUP) +
        "\nHitresult: " + hitresult[0] + " Pen: " + hitres + " Damage: " +
        hitresult[3] + "\nEnemy Avg: " + target->query_average_stat() +
        " Enemy max hps: " + target->query_max_hp() + "\n" +
        "------------------------------------------------------------\n");

    return;
}

/* Function name: reset_sling
 * Description  : Resetting the special
 * Arguments    : object who - slinger
 */
public void
reset_sling(object who)
{
    who->catch_tell("\nYou feel able to sling again.\n\n");
    who->remove_prop(SLING_RESET);
    who->remove_prop(SLING_PREPARE);
}
