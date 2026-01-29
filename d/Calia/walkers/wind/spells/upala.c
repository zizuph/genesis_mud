
 /*
  *
  * Upala (Air Blast) spell for the Windwalkers
  * by Jaacar   April 27th, 1998
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
#include "defs.h"
#include WIND_HEADER

public int create_spell_upala(object caster, object *targets,
    string argument);
private void desc_upala_damage(object caster, object *targets, mixed *results);
private void desc_upala_miss(object caster, object target);

private object *
upala_target_one_other_present_living(object caster, string str)
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

    if (!present("_upala_potion_object_",caster))
    {
        caster->catch_tell("You are not feeling the effects of the "+
            "upala potion.\n");
        return ({});
    }

    return oblist;
}

public int
create_spell_upala(object caster, object *targets, string argument)
{
    ::create_spell_bolt(caster, targets, argument);
    set_spell_element(SS_ELEMENT_AIR, 40);
    set_spell_form(SS_PRAYER, 40);
    set_spell_ingredients(({"black feather"}));  // Uses a potion as well
    set_spell_time(2);
    set_spell_mana(64);
    set_spell_task(TASK_SIMPLE);
    set_bolt_pen(301);
    set_bolt_desc("air");
    set_bolt_damage_msg(desc_upala_damage);
    set_bolt_miss_msg(desc_upala_miss);
}

private int
try_to_hit(object caster, object target)
{
    /* Should make a better formula */
    return (target->resolve_task(TASK_SIMPLE, ({ TS_DEX, SS_DEFENSE })) > 0);
}

private void
desc_upala_damage(object caster, object target, mixed *result)
{
    string how, bolt, him, his;

    him = target->query_objective();
    his = target->query_possessive();

    switch (result[0])
    {
        case 0..30:
            how = "unbalancing %s.";
            break;
        case 31..50:
            how = "causing %s to stagger.";
            break;
        case 51..80:
            how = "knocking %s into the ground.";
            break;
        case 81..99:
            how = "nearly knocking %s out cold.";
            break;
        default:
            break;
    }

    if (!how) // Death Blow
    {
        caster->catch_tell("The blow connects with " + him +
            ", knocking " + him + " to the ground and splitting " +
            his + " head open like a ripe melon.\n");
        target->catch_tell("The blow connects with you, knocking " +
            "you to the ground and splitting your head open like " +
            "a ripe melon.\n");
        caster->tell_watcher("The blow hits " + QTNAME(target) +
            ", knocking " + him + " to the ground and splitting " +
            his + " head open like a ripe melon.\n",target);
    }

    else // All other blows
    {
        caster->catch_tell(sprintf("The blow hits " + 
            target->query_the_name(caster) + ", "+ how + "\n", him));

        target->catch_tell(sprintf("The blow hits you, " + how +
            "\n", "you"));

        caster->tell_watcher(sprintf("The blow hits " + QTNAME(target) +
            ", " + how +"\n",him),target); 
    }
}

private void
desc_upala_miss(object caster, object target)
{
    string bolt = "The bolt of " + bolt_desc + " misses ";

    target->catch_tell(bolt + "you.\n");
    caster->catch_tell(bolt + target->query_the_name(caster) + ".\n");
    caster->tell_watcher(bolt + QCTNAME(target) + ".\n", target);
}
