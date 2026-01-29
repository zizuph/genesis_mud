/*

  This is the fire bolt spell for the College of Fire Magic. It can
  be aimed at a particular hit location, which is why we need a 
  special targeting function. Otherwise, pretty standard.

  Coded by Bishop of Calia, July 2003

 */

#pragma strict_types

inherit "/d/Genesis/newmagic/spells/bolt.c";
inherit "/d/Calia/guilds/colleges/specials/common_functions";

#include <tasks.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <cmdparse.h>
#include "defs.h"
#include "/std/combat/combat.h"

int hitloc_id;

public object*
special_target_one_other_present_living(object caster, string str)
{
    object *oblist, cobj;
    string hitloc, hitloc1, hitloc2;
    int *hitloc_ids, i;
    mixed *hits;

    if (!strlen(str))
    {
        caster->catch_tell("Whom do you wish to target?\n");
        return ({});
    }

    parse_command(str, environment(caster), "[at] / [on] [the] %l %w %w", 
        oblist, hitloc1, hitloc2);
    oblist = NORMAL_ACCESS(oblist, 0, 0);
    
    if (!sizeof(oblist))
    {
        caster->catch_tell("Whom do you wish to target?\n");
        return ({});
    }

    if (sizeof(oblist) > 1)
    {
        caster->catch_tell("You will have to be more specific!  You can only "+
            "select one target.\n");
        return ({});
    }

    hitloc_id = 0;

    if (strlen(hitloc1))
    {
        if (strlen(hitloc2))
        {
            hitloc = hitloc1 + " " + hitloc2;
        }
        else
        {
            hitloc = hitloc1;
        }
        
        cobj = oblist[0]->query_combat_object();
        hitloc_ids = cobj->query_hitloc_id();
        
        for (i = 0 ; i < sizeof(hitloc_ids) ; i++)
        {
            hits = cobj->query_hitloc(hitloc_ids[i]);
            if (hits[2] == hitloc)
            {
                hitloc_id = hitloc_ids[i];
            }
        }
        
        if (!hitloc_id)
        {
            caster->catch_tell("As you are unable to find that hit" +
                " location on the target, you decide to abort casting" +
                " the spell.\n");
            return ({});
        }        
    }


    return oblist;
}


int 
bolt_pen(object ob)
{
    int stat = find_controlling_stat("fire", ob);
    
    //Penetration 300-500.
    return min(300 + random(stat) + random(stat), 500);
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
    set_spell_mana(80);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_FIRE, 45);
    set_spell_form(SS_FORM_CONJURATION, 45);
    set_spell_ingredients(({ }));
    
    set_spell_target(special_target_one_other_present_living);

    set_bolt_pen(bolt_pen(caster));
    set_spell_name("firebolt");
    set_spell_desc("Launch a flaming arrow at someone");
    
    return 0;
}


public void
concentrate_msg(object caster, object *targets, string arg)
{
    caster->catch_tell("You draw power from the Plane of Fire.\n");
    say(QCTNAME(caster) + " appears to focus, " + 
        caster->query_possessive() + " eyes flashing deep red.\n");
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
    caster->catch_tell("The flaming arrow zooms right past " +
        target->query_the_name(caster) + "!\n");
    target->catch_tell("The flaming arrow zooms right past " +
        " you!\n");
    caster->tell_watcher_miss("The flaming arrow zooms right past " +
        QTNAME(target) + "!\n", target);
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
    caster->catch_tell("You finish the spell and launch your flame arrow" +
        " at " + targets[0]->query_the_name(caster) + ". It screams" +
        " towards " + targets[0]->query_objective() + ", trailing smoke.\n");
    targets[0]->catch_tell(caster->query_The_name(targets[0]) + " completes" +
        " the spell and launches a flaming arrow at you! It screams" +
        " towards you, leaving a trail of smoke.\n");
    caster->tell_watcher(QCTNAME(caster) + " finishes the spell and" +
        " launches a flaming arrow at " + QTNAME(targets[0]) + ". It screams" +
        " towards " + targets[0]->query_objective() + ", trailing smoke.\n",
        targets[0]);
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
    int stat = find_controlling_stat("fire", caster);
    int taskdiff = TASK_ROUTINE - stat;
    
    //Slightly harder to hit if the bolt is aimed at a hit location.
    if (hitloc_id)
    {
        taskdiff+= 50;
    }
    
    return (caster->resolve_task(taskdiff, ({SS_INT, SKILL_WEIGHT, 70,
        SS_ELEMENT_FIRE, SKILL_WEIGHT, 30, SS_FORM_CONJURATION}), 
        target, ({TS_DEX, SKILL_WEIGHT, 70, SS_DEFENCE, SKILL_WEIGHT, 
        30, SS_ACROBAT})) > 0);
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
    string desc1, desc2, hitloc;
    object cobj;
    mixed *hits;
    
    cobj = target->query_combat_object();
    hits = cobj->query_hitloc(result[4]);
    hitloc = hits[2];
    
    switch (result[0])
    {
        case 0:
            desc1 = "The flaming arrow just grazes you, the hot air" +
                " forcing you a step backwards.\n";
            desc2 = "The flaming arrow just grazes " + QTNAME(target) +
                ", the hot air forcing " + target->query_objective() +
                " a step backwards.\n";
            break;
        case 1..7:
            desc1 = "The flaming arrow slams into your " + hitloc + ", not" +
                " penetrating, but causing a few minor burn wounds.";
            desc2 = "The flaming arrow slams into " + 
                LANG_POSS(QTNAME(target)) + " " + hitloc + ", not" +
                " penetrating, but causing a few minor burn wounds.\n";
            break;            
        case 8..16:
            desc1 = "The flaming arrow enters your " + hitloc + ", but" +
                " doesn't penetrate deeply. As the arrow disappears," +
                " you are left with a shallow burn wound.\n";
            desc2 = "The flaming errow enters " + LANG_POSS(QTNAME(target)) +
                " " + hitloc + ", but doesn't penetrate deeply. As the arrow" +
                " disappears, " + target->query_pronoun() + " is left with" +
                " a shallow burn wound.\n";
            break;
        case 17..30:
            desc1 = "The flaming arrow lodges itself squarely in your " +
                hitloc + ". As the arrow disappears, you are left with an" +
                " ugly and smouldering wound.\n";
            desc2 = "The flaming arrow lodges itself squarely in " +
                LANG_POSS(QTNAME(target)) + " " + hitloc + ". As the arrow" +
                " disappears, " + target->query_pronoun() + " is left with" +
                " an ugly and smouldering wound.\n";
            break;
        default:
            desc1 = "The flaming arrow burrows deeply into your " + hitloc +
                ". As the arrow disappears, you are left with a crippling" +
                " wound.\n";
            desc2 = "The flaming arrow burrows deeply into " +
                LANG_POSS(QTNAME(target)) + " " + hitloc + ". As the arrow" +
                " disappears, " + target->query_pronoun() + " is left with" +
                " a crippling wound.\n";
    }
    
    if (target->query_hp() <= 0)
    {
        desc1 = "The flaming arrow hits you hard, boring straight through!" +
            " It continues on, while you stare at the charred hole in your" +
            " body in stunned silence.\n";
        desc2 = "The flaming arrow hits " + QTNAME(target) + " hard," +
            " boring straight through! It continues on, while " + 
            QTNAME(target) + " stares at the charred hole in " +
            target->query_possessive() + " body in stunned silence.\n";    
    }
    
    target->catch_tell(desc1);
    caster->catch_msg(desc2);
    caster->tell_watcher(desc2, target);
}


public mixed *
do_bolt_damage(object caster, object target, int pen)
{
    int ran, i, j, hit, *hloc_ids, ac;
    object cob;
    mixed *hloc;

    cob = target->query_combat_object();
    hloc_ids = cob->query_hitloc_id();
  
    // If caster specified a hitloc, use it.    
    if (hitloc_id)
    {
        hloc = cob->query_hitloc(hitloc_id);
    
        ac = (intp(hloc[HIT_AC]) ? 
            hloc[HIT_AC] : hloc[HIT_AC][random(sizeof(hloc[HIT_AC]))]);
        pen -= random(ac / 2);

        return target->hit_me(pen, MAGIC_DT, caster, -1, hitloc_id);
    }
    
    /* Pick a hitlocation and apply armour mod to pen */
    ran = random(100);
    
    hit = -1;
    j = 0;
    
    for (i = 0; i < sizeof(hloc_ids); i++)
    {
        hloc = cob->query_hitloc(hloc_ids[i]);
    
        j += hloc[HIT_PHIT];
        if (j >= ran)
        {
            hit = hloc_ids[i];
            ac = (intp(hloc[HIT_AC]) ? 
                hloc[HIT_AC] : hloc[HIT_AC][random(sizeof(hloc[HIT_AC]))]);
            pen -= random(ac / 2);
            break;
        }
    }

    return target->hit_me(pen, MAGIC_DT, caster, hit);
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