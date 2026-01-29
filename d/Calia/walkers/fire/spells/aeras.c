
 /*
  *
  * Aeras (Flame Wind) spell for the Firewalkers Guild
  * by Jaacar   Originally: August 7th, 1996
  * recoded to new spell system: May 4th, 1998
  *
  * Revamped, Bishop, June 16th, 1999.
  *
  */

#pragma strict_types

inherit "/d/Genesis/magic/spells/bolt";
inherit "/d/Genesis/magic/targeting";

#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <macros.h>
#include <cmdparse.h>
#include <language.h>
#include <filter_funs.h>
#include <wa_types.h>
#include "/std/combat/combat.h"
#include "defs.h"
#include FIRE_HEADER

public int create_spell_aeras(object caster, object *targets,
    string argument);
private void bolt_dam(object caster);
public void destroy_armours(object target);
private void desc_aeras_damage(object caster, object *targets, mixed *results);
private void desc_aeras_miss(object caster, object target);
private void desc_aeras_casting(object caster, object *targets);

private object *
aeras_target_one_other_present_living(object caster, string str)
{
    object *oblist;

    if (!strlen(str))
    {
        caster->catch_tell("Whom do you wish to target?\n");
        return ({});
    }

    oblist = PARSE_THIS(str, "[at] / [on] [the] %l");

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

    /*
    if (!present("_aeras_potion_object_",caster))
    {
        caster->catch_tell("You are not feeling the effects of the "+
            "aeras potion.\n");
        return ({});
    }
    */

    return oblist;
}

public int
create_spell_aeras(object caster, object *targets, string argument)
{
    ::create_spell_bolt(caster, targets, argument);
    set_spell_element(SS_ELEMENT_FIRE, 60);
    set_spell_form(SS_FORM_CONJURATION, 60);
    set_spell_ingredients(({ }));  // Uses a potion
    set_spell_time(3);
    set_spell_mana(200);
    set_spell_task(TASK_ROUTINE);
    set_bolt_desc("flaming");
    set_spell_offensive(1);
    set_bolt_casting_msg(desc_aeras_casting);
    set_bolt_damage_msg(desc_aeras_damage);
    set_bolt_miss_msg(desc_aeras_miss);
    bolt_dam(caster);
}


private void
bolt_dam(object caster)
{
    int pen, task;

    task = caster->resolve_task(TASK_ROUTINE, ({ SKILL_WEIGHT,
        75, TS_OCC, SKILL_END, SKILL_WEIGHT, 25, TS_WIS, SKILL_END, SKILL_AVG,
        SS_FORM_CONJURATION, SS_ELEMENT_FIRE, SKILL_END}));
    pen = 200 + 4*caster->query_stat(SS_OCCUP) + 6*min(max(task, 0), 100);
    pen = min(pen, 1200); //Ceiling of 1200 pen for this bolt.

    if (caster->query_wiz_level())
    {
        caster->catch_msg("Bolt penetration is: " + pen + ".\n");
    }

    set_bolt_pen(pen);
}

private void
desc_aeras_casting(object caster, object *targets)
{
    caster->catch_msg("You finish the Aeras incantation and a great flaming" +
        " mass appears before you. As you fix your concentration upon " +
        QTNAME(targets[0]) +", the mass shudders, then streaks with blinding" +
        " speed towards your hapless target, threatening to swallow " +
        targets[0]->query_objective() + " up.\n");
    caster->tell_watcher(QCTNAME(caster) + " finishes the spell and a great" +
        " flaming mass appears before " + caster->query_objective() + ". As " +
        caster->query_pronoun() + " fixes " + caster->query_possessive() +
        " concentration upon " + QTNAME(targets[0]) + ", the mass shudders," +
        " then streaks with blinding speed towards the hapless target," +
        " threatening to swallow " + targets[0]->query_objective() + " up.\n",
        targets[0]);
    targets[0]->catch_msg(QCTNAME(caster) + " finishes the spell and a great" +
        " flaming mass appears before " + caster->query_objective() + ". As " +
        caster->query_pronoun() + " fixes " + caster->query_possessive() +
        " concentration upon you, the mass shudders, then streaks with" +
        " blinding speed towards you, threatening to swallow you up!\n");
}

private void
desc_aeras_damage(object caster, object target, mixed *result)
{
    string how, how2;
    object skeleton;

    destroy_armours(target);
 
    switch(result[0])
    {
        case 0:
            how = "leaving " + target->query_objective() + " blackened by" +
                " soot, but otherwise unharmed.\n";
            how2 = "leaving you blackened by soot, but otherwise unharmed.\n";
            break;
        case 1..10:
            how = "burning " + target->query_objective() + " lightly.\n";
            how2 = "burning you lightly.\n";
            break;
        case 11..25:
            how = "leaving some painful blisters.\n";
            how2 = how;
            break;
        case 26..43:
            how = "causing " + target->query_objective() + " to howl with" +
                " pain as the flames leave several nasty burn wounds.\n";
            how2 = "causing you to howl with pain as the flames leave" +
                " several nasty burn wounds.\n";
            break;
        case 44..70:
            how = "disfiguring " + target->query_objective() + " as the" +
                " flames leave marks, burns wounds and blisters over " +
                target->query_possessive() + " entire body.\n";
            how2 = "disfiguring you as the flames leave marks, burn wounds" +
                " and blisters over your entire body.\n";
            break;
        default:
            how = "the incredible heat causing " + target->query_possessive() +
                " skin to melt off in" +
                " several places, leaving " + target->query_objective() +
                " a ragged, horribly disfigured copy of " + 
                target->query_possessive() + " former self.\n";
            how2 = "the incredible heat causing your skin to melt off in" +
                " several places, leaving you a ragged, horribly disfigured" +
                " copy of your former self.\n";
            break;
    }

    if (target->query_hp() <= 0)
    {
        how = "enveloping " + target->query_objective() + " and completely" +
            " obscuring " + target->query_objective() + " from view. As the" +
            " flames dissipate, only a blackened skeleton that quickly" + 
            " clatters to the ground is left of " + target->query_objective() +
            "\n";
        how2 = "enveloping you completely. Your last sensation is" +
            " unbearable pain as the flesh burns from your body.\n";
    }

    caster->catch_msg("The great flaming mass impacts with " + QTNAME(target) +
        ", " + how);
    caster->tell_watcher("The great flaming mass impacts with " + 
        QTNAME(target) + ", " + how, target);
    target->catch_msg("The great flaming mass impacts with you, " + how2);

    if (target->query_hp() <= 0)
    {
        seteuid(getuid());
        skeleton = clone_object("/d/Calia/walkers/fire/objects/skeleton_obj");
        skeleton->set_race(target->query_race_name());
        skeleton->move(environment(caster));
        target->add_prop(LIVE_I_NO_CORPSE, 1);
        target->do_die(caster);
    }     
}

private void
desc_aeras_miss(object caster, object target)
{
    caster->catch_msg(QCTNAME(target) + " quickly hits the ground, the" +
        " flaming mass passing right over " + target->query_objective() + 
        ".\n");
    caster->tell_watcher(QCTNAME(target) + " quickly hits the ground, the" +
        " flaming mass passing right over " + target->query_objective() + 
        ".\n", target);     
    target->catch_msg("You quickly hit the ground, the flaming mass passing" +
        " right over you.\n");
}

public void
destroy_armours(object target)
{
    object *armours;
    int i;

    i = 0;
    armours = target->query_clothing(-1);

    while (i < sizeof(armours))
    {
        if (armours[i]->query_ac() <= 20 && 
            !armours[i]->query_auto_load() &&
            armours[i]->query_prop(OBJ_I_RES_FIRE) < 30)
        {
            tell_room(environment(target), "The " + armours[i]->query_name() +
                " worn by " + QTNAME(target) + " is consumed by the flames!\n",
                target);
            target->catch_msg("The " + armours[i]->query_name() + " you're" +
                " wearing is consumed by the flames!\n");
            armours[i]->remove_object();
        }
        i++;
    }
}