/*
 * /d/Ansalon/guild/kender_occ/taunt.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * The ability to taunt would temporarily decrease the defence 
 * skill of the opponent based on the guild stat of the kender,
 * the kender's skill and the kender's wis all vs the dis and int of 
 * the enemy. Taunts have a reset time of 90 seconds, take 5 seconds
 * to go through, and last for 90 seconds.
 * 
 * Gwyneth, July 1999
 * Modification log:
 * Gwyneth, January 2001 - General cleanup and addition of parry
 *                         and highest weapon skill as alternates.
 *                         Will lower the highest of either parry,
 *                         defence or offensive skill (weapon/unarmed).
 */
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include "guild.h"

#define AXE		0
#define CLUB		1
#define KNIFE		2
#define POLEARM		3
#define SWORD		4
#define UNARMED		5

/*
 * Function name: check_attack
 * Description  : Does some checks to see if the special is allowed
 *                to be done.
 * Arguments    : object taunter
 * Returns      : The failure message if any.
 */
public string
check_attack(object taunter)
{
    int wimpy_scale = taunter->query_whimpy();
    string message;

    if (taunter->query_skill(SS_TAUNT_SPECIAL) < 1)
        return "You don't have enough skill to taunt anyone.\n";

    if (taunter->query_wiz_level())
        return "That would be a very bad idea!\n";

    if (message = environment(this_player())->query_prop(ROOM_M_NO_ATTACK))
        return (stringp(message) ? message : "A divine presence prevents " +
            "any attack.\n");

    if (taunter->query_prop(TAUNT_RESET))
        return "You're not ready to compose a new taunt yet.\n";

    if (taunter->query_prop(TAUNT_PREPARE))
        return "You are already composing a taunt.\n";

    if (wimp_check(taunter) < wimpy_scale)
        return "You are too busy thinking about running away to " +
            "compose a decent taunt!\n";

    return "";
}

/*
 * Function name: check_attack_enemy
 * Description  : Does some checks to see if the special is allowed
 *                to be done on the enemy.
 * Arguments    : object taunter, object enemy
 * Returns      : The failure message if any.
 */
public string
check_attack_enemy(object taunter, object enemy)
{
    string message;

    if (taunter == enemy)
        return "Taunt yourself?\n";

    if (!objectp(enemy) ||
      !present(enemy, environment(taunter)))
        return (enemy->query_The_name(taunter) + " doesn't seem to be " +
            "here anymore.\n");

    if (message = enemy->query_prop(OBJ_M_NO_ATTACK))
        return (stringp(message) ? message : "You cannot attack " +
            enemy->query_the_name(taunter) + " for some reason.\n");

    if (taunter->query_met(enemy) && taunter->query_enemy(0) != enemy)
    {
        if (taunter->query_prop(LIVE_O_LAST_KILL) != enemy)
        {
            taunter->add_prop(LIVE_O_LAST_KILL, enemy);
            return("Attack " + enemy->query_the_name(taunter) +
                "?!? Please confirm by trying again.\n");
        }
    }

    return "";
}

/*
 * Function name: reset_taunt
 * Description  : Removes the reset and prepare props and
 *                gives a message that it has reset.
 * Arguments    : object taunter
 */
public void
reset_taunt(object taunter)
{
    taunter->catch_tell("\nYou feel ready to think of a brilliant " +
        "new taunt!\n\n");
    taunter->remove_prop(TAUNT_RESET);
}

/*
 * Function name: reset_skills
 * Description  : Resets the affected skill by the amount it was
 *                changed 90 seconds after the taunt, and gives
 *                messages to the victim and those around him of
 *                its reset.
 * Arguments    : object taunter - the taunter
 *                modifier - the amount that was changed
 *                skill    - the weapon skill affected
 *                target   - who to reset the skills on
 */
public void
reset_skills(object taunter, int modifier, int skill, object target)
{
    /* This is done to avoid two different alarms that will
       go off at the same time. */
    reset_taunt(taunter);

    if (objectp(target))
    {
        target->catch_tell("You manage to regain a bit of your " +
            "self control.\n");
        tell_room(environment(target), QCTNAME(target) + " seems to be " +
            "regaining " + target->query_possessive() + " self control.\n",
            target);
        target->set_skill_extra(skill,
            target->query_skill_extra(skill) + modifier);
        target->set_skill_extra(SS_DEFENCE,
            target->query_skill_extra(SS_DEFENCE) + modifier);
        target->set_skill_extra(SS_PARRY,
            target->query_skill_extra(SS_PARRY) + modifier);
    }
}

/* 
 * Function name : do_taunt
 * Description   : Checks to see if the taunt can still be used,
 *                 calculates if/how much the victim's defence 
 *                 is changed. Gives the appropriate message to
 *                 the victim, taunter and spectators. 
 * Arguments     : object target, object taunter, string taunt
 */
public void
do_taunt(object target, object taunter, string taunt)
{
    int *target_skill, skill, alt_skill, skill_level, maximum, task, skill_mod,
        taunter_occ, taunter_wis, taunter_skill, i, defence, parry,
        wimpy_scale = taunter->query_whimpy();
    string message;

    set_this_player(taunter);

    if (!objectp(target) ||
      (!present(target, environment(taunter))))
    {
        write("Your opponent isn't here to taunt anymore.\n");
        taunter->remove_prop(TAUNT_PREPARE);
        return;
    }

    if (wimp_check(taunter) < wimpy_scale)
    {
        write("You are too busy thinking about running away to " +
            "compose a taunt.\n");
        taunter->remove_prop(TAUNT_PREPARE);
        return;
    }

    if ((target->query_stat(SS_INT) < 10 && target->query_humanoid()) ||
      (target->query_stat(SS_INT) < 20 && !target->query_humanoid()))
    {
        if (!strlen(taunt))
        {
            taunt = TAUNT_LIST->query_all_taunt(target);
        }

        taunter->reveal_me(1);
        taunter->remove_prop(TAUNT_PREPARE);
        taunter->add_prop(TAUNT_RESET, 1);
        set_alarm(taunter->query_speed(90), 0.0, &reset_taunt(taunter));
        write("\n" + target->query_The_name(taunter) + " looks dumbly at " +
            "you as you yell out: " + taunt + " " + 
            capitalize(target->query_pronoun()) + " is obviously too " +
            "dumb to understand what you are saying.\n\n");
        target->catch_tell(taunter->query_The_name(target) + " yells " +
            "something at you, but it seems just nonsense words.\n");
        tell_room(environment(taunter), "\n" + QCTNAME(target) +
            " looks dumbly at " + QTNAME(taunter) + " as " +
            taunter->query_pronoun() + " yells out: " + taunt + "\n\n",
            ({ taunter, target }));
        return;
    }

    /* Find the highest weapon skill and keep track of which skill it is. */
    target_skill  = ({ target->query_skill(SS_WEP_AXE) });
    target_skill += ({ target->query_skill(SS_WEP_CLUB) });
    target_skill += ({ target->query_skill(SS_WEP_KNIFE) });
    target_skill += ({ target->query_skill(SS_WEP_POLEARM) });
    target_skill += ({ target->query_skill(SS_WEP_SWORD) });
    target_skill += ({ target->query_skill(SS_UNARM_COMBAT) });

    skill = 0;
    skill_level = target_skill[0];

    for (i = 1; i < 6; i++)
    {
        if (target_skill[skill] < target_skill[i])
        {
            skill = i;
            skill_level = target_skill[i];
        }
    }

    
    switch(skill)
    {
        case 0:
            skill = SS_WEP_AXE;
            break;
        case 1:
            skill = SS_WEP_CLUB;
            break;
        case 2:
            skill = SS_WEP_KNIFE;
            break;
        case 3:
            skill = SS_WEP_POLEARM;
            break;
        case 4:
            skill = SS_WEP_SWORD;
            break;
        case 5:
            skill = SS_UNARM_COMBAT;
            break;
    }

    defence = target->query_skill(SS_DEFENCE);
    parry = target->query_skill(SS_PARRY);

    taunter_occ = taunter->query_stat(SS_OCCUP);
    taunter_wis = taunter->query_stat(SS_WIS);
    taunter_skill = taunter->query_skill(SS_TAUNT_SPECIAL);
    maximum = 33;

    task = this_player()->resolve_task(TASK_ROUTINE, ({ SKILL_AVG, TS_OCC,
        TS_WIS, SKILL_END, SS_TAUNT_SPECIAL }), target, ({ SKILL_AVG, TS_DIS,
        TS_INT, SKILL_END }));

    skill_mod = (task / 3);

    /* Taunt failed. */
    if (skill_mod <= 0)
    {
        taunter->reveal_me(1);
        taunter->remove_prop(TAUNT_PREPARE);
        taunter->add_prop(TAUNT_RESET, 1);
        set_alarm(taunter->query_speed(90), 0.0, &reset_taunt(taunter));
        write("\n" + target->query_The_name(taunter) + " retains " +
            target->query_possessive() + " calm composure as you " +
            "yell a taunt at " + target->query_objective() + ".\n\n");
        target->catch_tell("\nYou retain your calm composure as " +
            taunter->query_the_name(target) + " attempts to taunt " +
            "you.\n\n");
        tell_room(environment(taunter), "\n" + QCTNAME(target) + " retains " +
            target->query_possessive() + " calm composure as " + 
            QTNAME(taunter) + " attempts to taunt " + 
            target->query_objective() + ".\n\n", ({ taunter, target }));
        return;
    }

    /* Make the results not exceed the maximum allowed */
    skill_mod = (skill_mod > maximum ? maximum : skill_mod);

    switch(skill_mod)
    {
        case 1..5:
            message = "cheeks flush slightly in annoyance";
            break;
        case 6..10:
            message = "cheeks flush in annoyance";
            break;
        case 11..15:
            message = "face flushes in anger";
            break;
        case 16..20:
            message = "face flushes darkly in anger";
            break;
        case 21..25:
            message = "face flushes in rage";
            break;
        case 26..30:
            message = "face flushes hotly in rage";
            break;
        default:
            message = "face flushes in complete rage";
            break;
    }

    if (!strlen(taunt))
    {
        taunt = TAUNT_LIST->query_all_taunt(target);
    }

    write("\n" + target->query_The_possessive_name(taunter) + 
        " " + message + " as you taunt " + target->query_objective() +
        " yelling out: " + taunt + "\n\n");
    target->catch_tell("\nYour " + message + " as you listen to " +
        taunter->query_the_name(target) + " taunting you, yelling: " +
        taunt + "\n\n");
    tell_room(environment(taunter), "\n" + QCTPNAME(target) + " " +
        message + " as " + QTNAME(taunter) + " taunts " +
        target->query_objective() + ", yelling: " + taunt + "\n\n",
        ({ taunter, target }));
    taunter->reveal_me(1);

    if (taunter != target->query_attack())
    {
        if (skill_mod > 10 &&
          CAN_SEE(target, taunter) &&
          CAN_SEE_IN_ROOM(target))
        {
            target->attack_object(taunter);
            write(target->query_The_name(taunter) + " attacks you in " +
                target->query_possessive() + " fury.\n");
            target->catch_tell("Unable to control yourself, you attack " +
                taunter->query_the_name(target) + " in fury.\n");
            tell_room(environment(taunter), QCTNAME(target) + " attacks " +
                QTNAME(taunter) + " in " + target->query_possessive() +
                " fury.\n", ({ taunter, target }));
        }
        else if (CAN_SEE(target, taunter) &&
          CAN_SEE_IN_ROOM(target) &&
          target != taunter->query_attack())
        {
            write("You take the opportunity to attack " + 
                target->query_the_name(taunter) + " while " +
                target->query_pronoun() + " is flustered.\n");
            target->catch_tell(taunter->query_The_name(target) + " takes " +
                "the opportunity to attack you while you are flustered.\n");
            tell_room(environment(taunter), QCTNAME(taunter) + " takes the " +
                "opportunity to attack " + QTNAME(target) + " while " +
                target->query_pronoun() + " is flustered.\n", 
                ({ taunter, target }));
            taunter->attack_object(target);
        }
        else if (target != taunter->query_attack())
        {
            tell_room(environment(taunter), QCTNAME(target) + " screams in " +
                "rage at not being able to find " + 
                target->query_possessive() + " taunter.\n", target);
            target->catch_tell("You scream in rage at not being able to " +
                "find your taunter.\n");
        }
    }
    else if (skill_mod > 10 &&
      CAN_SEE(target, taunter) &&
      CAN_SEE_IN_ROOM(target))
    {
        write(target->query_The_name(taunter) + " renews " +
            target->query_possessive() + " attack on you in greater fury.\n");
        target->catch_tell("You renew your attack on " + 
            taunter->query_the_name(target) + " in greater fury.\n");
        tell_room(environment(taunter), QCTNAME(target) + " renews " +
            target->query_possessive() + " attack on " + QTNAME(taunter) +
            " in greater fury.\n", ({ target, taunter }));
    }

    /* Change the extra stats for the given skills, taking */
    /* into account any non-taunt altered skills.       */
    target->set_skill_extra(skill, 
        target->query_skill_extra(skill) - skill_mod);
    target->set_skill_extra(SS_DEFENCE,
        target->query_skill_extra(SS_DEFENCE) - skill_mod);
    target->set_skill_extra(SS_PARRY,
        target->query_skill_extra(SS_PARRY) - skill_mod);

    set_alarm(taunter->query_speed(90), 0.0, &reset_skills(taunter, skill_mod, skill, target));

    taunter->add_prop(TAUNT_RESET, 1);
    taunter->remove_prop(TAUNT_PREPARE);
/*
    find_living("gwyneth")->catch_tell(taunter->query_name() +
        " taunted " + target->query_name() + " with a result of " +
        "lowering skill number " + skill + " by " + skill_mod +
        ".\nTaunter wis(" + taunter_wis + ") occup(" + taunter_occ + ") " +
        "skill(" + taunter_skill + ").\nTarget wis(" + 
        target->query_stat(SS_WIS) + ") dis(" + target->query_stat(SS_DIS) +
        ") remaining affected skill(" + target->query_skill(skill) + "." +
        ") Max: " + maximum + " remaining parry: " +
        parry + " remaining defence " + defence + ".\n");
*/
    return;
}

/* 
 * Function name : taunt_special
 * Description   : Pre-attack, initial parsing -- checks to see
 *                 if the taunter is allowed to begin the special,
 *                 and assigns the taunt.
 * Arguments     : str - the string typed in by the taunter
 * Returns       : 1 on success, 0 on failure
 */
public int
taunt_special(string str)
{
    object enemy, *oblist, taunter = this_player();
    string str1, str2, message;

    message = check_attack(taunter);

    if (strlen(message))
    {
        notify_fail(message);
        return 0;
    }

    if (strlen(str))
    {
        /* Assigns target to str2 if only one argument */
        sscanf(str, "%s", str2);

        /* Assign target to str2 Assign text to str1 */
        sscanf(str, "%s with %s", str2, str1); 
    }

    if ((str2 == "enemy") || !strlen(str))
    {
        enemy = taunter->query_attack();
        if (!objectp(enemy))
        {
            notify_fail("Taunt who?\n");
            return 0;
        }
    }
    else
    {
        oblist = parse_this(str2, "%l");

        if (!sizeof(oblist))
        {
            notify_fail("Taunt who?\n");
            return 0;
        }
        else
        {
            enemy = oblist[0];
        }
    }

    message = check_attack_enemy(taunter, enemy);

    if (strlen(message))
    {
        notify_fail(message);
        return 0;
    }

    taunter->add_prop(TAUNT_PREPARE, 1);
    write("You rack your brain for an appropriate taunt.\n");
    set_alarm(taunter->query_speed(5),0.0, &do_taunt(enemy, taunter, str1));
    return 1;
}

