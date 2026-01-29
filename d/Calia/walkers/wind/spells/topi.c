
 /*
  *
  * Topi (Lightning Bolt) spell for the Windwalkers
  * by Jaacar   April 29th, 1998
  *
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
#include <composite.h>
#include "defs.h"
#include WIND_HEADER

public int create_spell_topi(object caster, object *targets,
    string argument);
private void desc_topi_casting(object caster, object *targets);
private void desc_topi_damage(object caster, object *targets, mixed *results);
private void desc_topi_miss(object caster, object target);

private object *
topi_target_one_other_present_living(object caster, string str)
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

    if (!present("_topi_potion_object_",caster))
    {
        caster->catch_tell("You are not feeling the effects of the "+
            "topi potion.\n");
        return ({});
    }

    return oblist;
}

public int
create_spell_topi(object caster, object *targets, string argument)
{
    ::create_spell_bolt(caster, targets, argument);
    set_spell_element(SS_ELEMENT_AIR, 40);
    set_spell_form(SS_PRAYER, 40);
    set_spell_ingredients(({ }));  // Uses a potion
    set_spell_time(3);
    set_spell_mana(96);
    set_spell_task(TASK_ROUTINE);
    set_bolt_pen(400);
    set_bolt_desc("lightning");
    set_bolt_casting_msg(desc_topi_casting);
    set_bolt_damage_msg(desc_topi_damage);
    set_bolt_miss_msg(desc_topi_miss);
}

private int
try_to_hit(object caster, object target)
{
    /* Should make a better formula */
    return (target->resolve_task(TASK_ROUTINE, ({ TS_DEX, SS_DEFENSE })) > 0);
}

private void
desc_topi_casting(object caster, object *targets)
{
    string msg, his, he, bolt;

    his = caster->query_possessive();
    he = caster->query_pronoun();

    bolt = "A " + ((sizeof(targets) > 1) ? "bolts" : "bolt") +
        " of " + bolt_desc + ((sizeof(targets) > 1) ? " shoot" : " shoots") +
        " from %s palm.\n";

    caster->catch_tell("The air around you becomes charged with the " +
        "energies of Lady Aeria.  Minute lighting bolts dance around " +
        "your body with rapidly increasing ferocity.  As you forcefully " +
        "gesture with your hand towards " +
        FO_COMPOSITE_ALL_LIVE(targets, caster) + " the air between " +
        "you becomes alive with electricity.  " + sprintf(bolt, "your"));

    msg = "As " + he + " gestures " + his + " hand towards you, " +
        "the air between you becomes alive with electricity.  " +
        sprintf(bolt, his);
        
    targets->catch_msg("The air around " + QTNAME(caster) +
        " becomes charged with energy.  Minute lighting bolts dance " +
        "around " + his + " body rapidly with increasing ferocity.  " +
        msg);
                           
    caster->tell_watcher("The air around " + QTNAME(caster) + " suddenly " +
        "becomes charged with energy.  Minute lighting bolts dance " +
        "around " + his + " body rapidly with increasing ferocity.  " + 
        "As " + he + " gestures " + his + " hand towards " + QCOMPLIVE +
        " the air between them becomes alive with electricity.  " +
        sprintf(bolt, his), targets);
}

private void
desc_topi_damage(object caster, object target, mixed *result)
{
    string how, bolt, him, his, he;

    him = target->query_objective();
    his = target->query_possessive();
    he = target->query_pronoun();

    switch (result[0])
    {
        case 0..30:
            how = "singed";
            break;
        case 31..50:
            how = "scorched";
            break;
        case 51..80:
            how = "burnt";
            break;
        case 81..99:
            how = "nearly consumed";
            break;
        default:
            break;
    }

    if (!how) // Death Blow
    {
        caster->catch_tell("The bolt of lightning connects with " + him +
            " for a split second, immediately followed by a deafening " +
            "thunderclap.  " + capitalize(he) + " lights up like a " +
            "torch and is thrown to the ground, shuddering a couple " +
            "of times before becoming very still.  " + 
            capitalize(his) + " smouldering corpse lies on the ground " +
            "before you.\n");
        target->catch_tell("The bolt of lighting connects with you for " +
            "a split second, immediately followed by a deafening " +
            "thunderclap.  You light up like a torch before being " +
            "thrown to the ground, shuddering a couple of times before " +
            "you lose all feeling in your body.  Looking down you see " +
            "your smouldering corpse lying on the ground and you realize " +
            "you are dead.\n");
        caster->tell_watcher("The bolt of lighting connects with " + 
            QTNAME(target) + " for a split second, immediately followed " +
            "by a deafening thunderclap.  " + capitalize(he) + " lights " +
            "up like a torch and is thrown to the ground, shuddering " +
            "a couple of times before becoming very still.  " +
            capitalize(his) + " smouldering corpse lies on the ground " +
            "before you.\n",target);
    }

    else // All other blows
    {
        caster->catch_tell("The bolt of lightning connects with " + 
            target->query_the_name(caster) + " for a split second " +
            "and " + he + " is " + how + " by the discharge.\n");

        target->catch_tell("The bolt of lightning connects with you " +
            "for a split second and you are " + how +
            " by the discharge.\n");

        caster->tell_watcher("The bolt of lightning connects " +
           "with " + QTNAME(target) + " for a split second and " +
           he + " is " + how + " by the discharge.\n",target); 
    }
}

private void
desc_topi_miss(object caster, object target)
{
    string bolt = "The bolt of " + bolt_desc + " just misses ";

    target->catch_tell(bolt + "you.\n");
    caster->catch_tell(bolt + target->query_the_name(caster) + ".\n");
    caster->tell_watcher(bolt + QCTNAME(target) + ".\n", target);
}
