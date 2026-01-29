
 /*
  *
  * Saita spell for the Elemental Worshippers of Calia
  * by Jaacar   August 7th, 1996
  *
  * Heavily modified by Bishop, June 12th, 1999.
  */

#pragma strict_types

inherit "/d/Genesis/magic/spells/bolt";
inherit "/d/Genesis/magic/targeting";

#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include <cmdparse.h>
#include <language.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/std/combat/combat.h"
#include "defs.h"
#include FIRE_HEADER

public int create_spell_saita(object caster, object *targets,
    string argument);
private void set_pen(object caster);
private void desc_saita_damage(object caster, object *targets, mixed *results);
private void desc_saita_miss(object caster, object target);
private void desc_saita_casting(object caster, object *targets);

public int hitloc;

private object *
saita_target_one_other_present_living(object caster, string str)
{
    mixed *hits;
    object *oblist, cobj;
    string *strings, hloc;
    int *hitloc_ids, i;

    hitloc = 0;
    
    if (!strlen(str))
    {
        caster->catch_tell("Whom do you wish to target?\n");
        return ({});
    }

    strings = explode(str, " ");
 
    if (sizeof(PARSE_THIS(str, "[at] / [on] [the] %l %w %w")))
    {
        oblist = PARSE_THIS(str, "[at] / [on] [the] %l %w %w");
    }
    else
    if (sizeof(PARSE_THIS(str, "[at] / [on] [the] %l %w")))
    {
        oblist = PARSE_THIS(str, "[at] / [on] [the] %l %w");
    }
    else
    {
        oblist = PARSE_THIS(str, "[at] / [on] [the] %l");
    }

    if (!sizeof(oblist))
    {
        caster->catch_tell("Whom do you wish to target?\n");
        return ({});
    }

    if (sizeof(oblist) > 1)
    {
        caster->catch_tell("You will have to be more specific!  You "+
            "can only select one target.\n");
        return ({});
    }

    cobj = oblist[0]->query_combat_object();
    hitloc_ids = cobj->query_hitloc_id();
 
    if (sizeof(PARSE_THIS(str, "[at] / [on] [the] %l %w %w")))
    {
        hloc = strings[sizeof(strings) - 2] + " " +
            strings[sizeof(strings) - 1];
    }
    else
    if (sizeof(PARSE_THIS(str, "[at] / [on] [the] %l %w")))
    {
        hloc = strings[sizeof(strings) - 1];
    }
    else
    {
        hloc = "";
    }

    if (strlen(hloc))
    {

        for (i=0 ; i < sizeof(hitloc_ids) ; i++)
        {
            hits = cobj->query_hitloc(hitloc_ids[i]);
            if (hits[2] == hloc)
            {
                hitloc = hitloc_ids[i];
            }
        }
        
        if (!hitloc)
        {
            caster->catch_tell("As you are unable to find that hit" +
                " location on the target, you decide to abort casting" +
                " the spell.\n");
            return ({});
        }
    }

    /*
    if (!present("_saita_potion_object_",caster))
    {
        caster->catch_tell("You are not feeling the effects of the "+
            "saita potion.\n");
        return ({});
    }
    */

    return oblist;
}

public int
create_spell_saita(object caster, object *targets, string argument)
{
    ::create_spell_bolt(caster, targets, argument);
    set_spell_element(SS_ELEMENT_FIRE, 40);
    set_spell_form(SS_FORM_CONJURATION, 40);
    set_spell_ingredients(({ }));  // Uses a potion
    set_spell_time(2);
    set_spell_mana(75);
    set_spell_task(TASK_SIMPLE);
    set_bolt_desc("fire");
    set_bolt_damage_msg(desc_saita_damage);
    set_bolt_casting_msg(desc_saita_casting);
    set_bolt_miss_msg(desc_saita_miss);
    set_pen(caster);
}

private void
desc_saita_miss(object caster, object target)
{
    target->catch_tell("A feverish dodging maneuver saves you from being hit" +
        " by bolt of fire.\n");
    caster->catch_tell("A feverish dodging maneuver saves " +
        target->query_the_name(caster) +
        " from being hit by the bolt of fire.\n");
    caster->tell_watcher("A feverish dodging maneuver saves " + 
        target->query_the_name(caster) +
        " from being hit by the bolt of fire.\n", target);
}

private void 
set_pen(object caster)
{
    int pen, task;

    task = caster->resolve_task(TASK_ROUTINE, ({ SKILL_WEIGHT,
        75, TS_OCC, SKILL_END, SKILL_WEIGHT, 25, TS_WIS, SKILL_END, SKILL_AVG,
        SS_FORM_CONJURATION, SS_ELEMENT_FIRE, SKILL_END}));
    pen = 100 + 2*caster->query_stat(SS_OCCUP) + 3*min(max(task, 0), 100);
    pen = min(pen, 500); //Ceiling of 500 pen for this bolt.

    if (caster->query_wiz_level())
    {
        caster->catch_msg("Bolt penetration is: " + pen + ".\n");
    }

    set_bolt_pen(pen);
}


private void
desc_saita_casting(object caster, object *targets)
{

    caster->catch_msg("You complete the Saita spell, and a bolt of fire" +
        " appears next to you. With a casual hand movement, you"+
        " send it towards " + QTNAME(targets[0]) + ".\n");
    caster->tell_watcher(QCTNAME(caster) + " completes the spell, and a" +
        " bolt of fire appears next to " + caster->query_objective() +
        ". With a casual hand movement" +
        ", " + caster->query_pronoun() + " sends it towards " +
        QTNAME(targets[0]) + ".\n", targets[0]);
    targets[0]->catch_msg(QCTNAME(caster) + " completes the spell, and a" +
        " bolt of fire appears next to " + caster->query_objective() +
        ". With a casual hand movement" +
        ", " + caster->query_pronoun() + " sends it towards you.\n");
}


private void
desc_saita_damage(object caster, object target, mixed *result)
{
    string how, bolt, him, his;
    mixed *loc;

    him = target->query_objective();
    his = target->query_possessive();

    switch (result[0])
    {
        case 0..5:
            how = "no marks whatsoever";
            break;
        case 6..15:
            how = "a large burn mark";
            break;
	case 16..30:
            how = "a large, blistering burn mark";
            break;
	case 31..50:
            how = "a painful, blistering burn mark";
            break;
	case 51..90:
            how = "a large area of smouldering flesh";
            break;
        default:
            how = "a huge area of burnt, crispy flesh";
            break;
    }

    if (target->query_hp() <= 0)
    {
        caster->catch_msg("The bolt speeds relentlessly towards " +
            QTNAME(target) + " and slams into " + target->query_objective() +
            " with enough force to propel " + target->query_objective() +
            " several feet backwards.\n");
        caster->tell_watcher("The bolt speeds relentlessly towards " +
            QTNAME(target) + " and slams into " + target->query_objective() +
            " with enough force to propel " + target->query_objective() +
            " several feet backwards.\n", target);
        target->catch_msg("The bolt speeds relentlessly towards " +
            " you and slams into you with enough force to propel you several" +
            " feet backwards. As you will yourself to get back up on your" +
            " feet, but nothing happens, you realize that death is not far" +
            " away.\n");
        target->do_die(caster);
    }
    else
    if (!hitloc)
    {
        caster->catch_msg("The bolt speeds relentlessly towards " +
            QTNAME(target) + " and slams into " + target->query_objective() +
            ", leaving " + how + ".\n");
        caster->tell_watcher("The bolt speeds relentlessly towards " +
            QTNAME(target) + " and slams into " + target->query_objective() +
            ", leaving " + how + ".\n", target);
        target->catch_msg("The bolt speeds relentlessly towards " +
            "you and slams into you, leaving " + how + ".\n");
    }
    else
    {
        loc = (target->query_combat_object())->query_hitloc(hitloc);   
        caster->catch_msg("The bolt speeds relentlessly towards " +
            QTNAME(target) + " and slams into " + target->query_possessive() +
            " " + loc[2] + ", leaving " + how + ".\n");
        caster->tell_watcher("The bolt speeds relentlessly towards " +
            QTNAME(target) + " and slams into " + target->query_possessive() +
            " " + loc[2] + ", leaving " + how + ".\n", target);
        target->catch_msg("The bolt speeds relentlessly towards " +
            "you and slams into your " + loc[2] + ", leaving " + how + ".\n");
    } 
}

public mixed *
do_bolt_damage(object caster, object target, int pen)
{
    int ran, i, j, hit, *hloc_ids, ac;
    object cob;
    mixed *hloc;

    /* Pick a hitlocation and apply armour mod to pen */
    ran = random(100);

    cob = target->query_combat_object();
    hloc_ids = cob->query_hitloc_id();
    hit = -1;
    j = 0;

    if (!hitloc)
    {
        for (i = 0; i < sizeof(hloc_ids); i++)
        {
            hloc = cob->query_hitloc(hloc_ids[i]);
    
            j += hloc[HIT_PHIT];
            if (j >= ran)
	    {
                hit = hloc_ids[i];
                hitloc = hit;
                ac = (intp(hloc[HIT_AC]) ? 
                    hloc[HIT_AC] : hloc[HIT_AC][random(sizeof(hloc[HIT_AC]))]);
                pen -= random(ac / 2);
                break;
	    }
        }
    }
    else
    {
        hit = hitloc;
        hloc = cob->query_hitloc(hit);
        ac = (intp(hloc[HIT_AC]) ? 
            hloc[HIT_AC] : hloc[HIT_AC][random(sizeof(hloc[HIT_AC]))]);
        pen -= random(ac / 2);
    }            

    return target->hit_me(pen, MAGIC_DT, caster, hit);
}