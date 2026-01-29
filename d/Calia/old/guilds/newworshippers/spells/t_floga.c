/*

  This is the Floga (fire bolt) spell for the Worshippers. 

  Coded by Bishop of Calia, June 2003

  - Modified by Petros, January 2012 to prevent team members from being
    targeted.
 */

#pragma strict_types

inherit "/d/Genesis/newmagic/spells/bolt.c";

#include <tasks.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"

/*
 * Function:    spell_target_one_other_present_living_non_team_member
 * Description: This targetting function prevents one from attacking
 *              someone on your team. This is relevant for Worshippers,
 *              since it is against the rules to attack someone on your
 *              team. Implemented as a result of a request from Syrk.
 */
public object *
spell_target_one_other_present_living_non_team_member(object actor, string str)
{
    object * target_players = spell_target_one_other_present_living(actor, str);
    if (!sizeof(target_players))
    {
        // There are no target players. An error must have occurred. We just
        // go ahead and return.
        return target_players;
    }
    
    object * other_team_members = actor->query_team_others();
    if (!sizeof(other_team_members))
    {
        // The person isn't on a team, so we don't bother preventing anything.
        return target_players;
    }
    
    foreach (object target : target_players)
    {
        if (IN_ARRAY(target, other_team_members))
        {
            actor->catch_tell("You cannot target a team member!\n");
            return ({ });
        }
    }
    return target_players;
}

/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       1/0 - spell configured/not configured (cannot be cast)
 */
public varargs int
config_spell(object caster, object *targets, string argument)
{
    ::config_spell(caster, targets, argument);

    set_spell_time(3);
    set_spell_mana(120);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_FIRE, 40);
    set_spell_form(SS_FORM_CONJURATION, 35);
    set_spell_ingredients(({"fireweed"}));
    
    set_spell_target(spell_target_one_other_present_living_non_team_member);

    set_bolt_pen(min(250 + random(caster->query_stat(SS_LAYMAN))
        + random(caster->query_stat(SS_LAYMAN)) , 450));
    set_spell_name("floga");
    set_spell_desc("Burn someone with the fires of Lord Pyros");
    
    return 0;
}

public void
concentrate_msg(object caster, object *targets, string arg)
{
    caster->catch_msg("You begin to murmur the Floga incantation, focusing" +
        " on " + QTNAME(targets[0]) + ".\n");
    say(QCTNAME(caster) + " begins to murmur a strange" +
        " incantation.\n");
}

/*
 * Function name: desc_bolt_miss
 * Description:   Write out some text describing the missed attack.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_bolt_miss(object caster, object target)
{
    string *dodge = ({"dodges feverishly", "sidesteps deftly", 
        "ducks effortlessly", "jumps wildly"});
    string *dodge2 = ({"dodge feverishly", "sidestep deftly",
        "duck effortlessly", "jump wildly"});
    int i = random(sizeof(dodge));

    caster->catch_msg("The flames stream toward " + QTNAME(target) +
        ", but " + target->query_pronoun() + " " + 
        dodge[i] + ", escaping your wrath for now.\n");
    target->catch_msg("The flames stream toward you, but you " +
        dodge2[i] + ", escaping " + LANG_POSS(QTNAME(caster)) + " wrath!\n");
    caster->tell_watcher_miss("The flames stream toward " + QTNAME(target)+
        ", but " + target->query_pronoun() + " " + 
        dodge[i] + ", escaping " + LANG_POSS(QTNAME(caster)) + " wrath.\n" ,
        target);
}

/*
 * Function name: desc_bolt_cast
 * Description:   Describe casting of the spell, not including damage messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_bolt_cast(object caster, object *targets)
{
    string desc;

    if (bolt_pen < 300)
    {
        desc = "A thin beam of fire jets";
    }
    else if (bolt_pen < 400)
    {
        desc = "A thick lance of flame streams";
    }
    else
    {
        desc = "A raging torrent of fire cascades";
    }   

    if (caster->query_wiz_level())
    {
        caster->catch_tell("Bolt penetration is: " + bolt_pen + ".\n");
    }
    
    caster->catch_msg("Finishing the incantation, your arm whips out," +
        " aiming at " + QTNAME(targets[0]) + ". " + desc + " forth from" +
        " your outstretched palm toward your hapless target!\n");
    targets[0]->catch_msg("As " + QTNAME(caster) + " finishes the" +
        " incantation, " + caster->query_possessive() + " arm whips out," +
        " aiming in your direction. " + desc + " forth from " +
        caster->query_possessive() + " outstretched palm, heading straight" +
        " toward you!\n");
    caster->tell_watcher("As " + QTNAME(caster) + " finishes the" +
        " incantation, " + caster->query_possessive() + " arm whips out," +
        " aiming at " + QTNAME(targets[0]) + ". " + desc + " forth from " +
        caster->query_possessive() + " outstretched palm, heading straight" +
        " toward " + QTNAME(targets[0]) + ".\n", targets[0]);
}


/*
 * Function name: try_to_hit
 * Description:   Test to see if the bolt hits a target.
 * Arguments:     object caster - the caster
 *                object target - the target
 * Returns:       1/0 - hit/missed
 */
public int
try_to_hit(object caster, object target)
{
    int i = caster->resolve_task(TASK_EASY, ({SKILL_WEIGHT, 60, TS_INT,
        SKILL_WEIGHT, 40, TS_WIS, SKILL_WEIGHT, 200, TS_LAYMAN }), target, 
        ({TS_DEX, SS_DEFENSE, SS_ACROBAT}));
    return (i > 0);
}


/*
 * Function name: desc_bolt_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                mixed *result - return value from do_bolt_damage() call.
 */
public void
desc_bolt_damage(object caster, object target, mixed *result)
{
    string how1, how2, how3;
            
    switch (result[0])
    {
        case 0:
            how1 = LANG_POSS(QTNAME(target)) + " " + result[1] + ". " +
                capitalize(target->query_pronoun()) + " is unscathed by the" +
                " blast and laughs at your feeble effort.\n";
            how2 = LANG_POSS(QTNAME(target)) + " " + result[1] + ". " +
                capitalize(target->query_pronoun()) + " is unscathed by the" +
                " blast and laughs at " + LANG_POSS(QTNAME(caster)) + 
                " feeble effort.\n";
            how3 = "your " + result[1] + ". You are unscathed by the blast" +
                " and laugh at " + LANG_POSS(QTNAME(caster)) + " feeble" +
                " effort.\n";
            break;
        case 1..6:
            how1 = LANG_POSS(QTNAME(target)) + " " + result[1] + ". " +
                capitalize(target->query_pronoun()) + " is singed by the" +
                " blast and grimaces in discomfort.\n";
            how2 = how1;
            how3 = "your " + result[1] + ". You are singed by the blast" +
                " and grimace in discomfort.\n";
            break;
        case 7..14:
            how1 = LANG_POSS(QTNAME(target)) + " " + result[1] + ". " +
                "The accurate blast leaves a painful and unsightly burn" +
                " wound.\n";
            how2 = how1;
            how3 = "your " + result[1] + ". The accurate blast leaves a" +
                " painful and unsightly burn wound.\n";
            break;
        case 15..23:
            how1 = LANG_POSS(QTNAME(target)) + " " + result[1] + ". " +
                capitalize(target->query_pronoun()) + " whimpers as the" +
                " withering blast strips skin from " + 
                target->query_possessive() + " body.\n";
            how2 = how1;
            how3 = "your " + result[1] + ". You whimper as the withering" +
                " blast strips skin from your body.\n";            
            break;
        case 24..40:
            how1 = LANG_POSS(QTNAME(target)) + " " + result[1] + ". " +
                capitalize(target->query_pronoun()) + " is scourged by the" +
                " fiery blast, howling in pain as the blaze shrivels flesh.\n";
            how2 = how1;
            how3 = "your " + result[1] + ". You are scourged by the fiery" +
                " blast and howl in pain as the blaze shrivels flesh.\n"; 
            break;
        default:
            how1 = LANG_POSS(QTNAME(target)) + " " + result[1] + ", lancing" +
                " almost straight through! The extremely punishing blast" +
                " leaves " + target->query_objective() + " struggling to" +
                " remain standing.\n";
            how2 = how1;
            how3 = "your " + result[1] + ", lancing almost straight through!" +
                " The extremely punishing blast leaves you struggling to" +
                " remain standing.\n";
            break;
    }
    
    if (target->query_hp() <= 0)
    {
        how1 = QTNAME(target) +
            ", almost consuming " + target->query_objective() +
            "! " + capitalize(target->query_possessive()) + 
            " shattered and blackened ruin crumples to the ground.\n";
        how2 = how1;
        how3 = "you, almost consuming" +
            " your body! The blinding pain is followed by darkness.\n";
    }
      
    caster->catch_msg("The streaming flames connect with " + how1);
    caster->tell_watcher("The streaming flames connect with " + how2, target);
    target->catch_msg("The streaming flames connect with " + how3);
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    if (environment(caster)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
    {
        caster->catch_tell("You complete the spell, but the flame you" +
            " summon is immediately doused by the surrounding water!\n");
    }
    else
    {
        ::resolve_spell(caster, targets, resist, result);
    }
}