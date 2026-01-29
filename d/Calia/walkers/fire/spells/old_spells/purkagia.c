
 /*
  *
  * Purkagia spell for the Elemental Worshippers of Calia
  * by Jaacar   August 7th, 1996
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
#include <stdproperties.h>
#include "defs.h"
#include FIRE_HEADER

public int create_spell_purkagia(object caster, object *targets,
    string argument);
private void desc_purkagia_damage(object caster, object *targets, mixed *results);
private void desc_purkagia_miss(object caster, object target);

private object *
purkagia_target_one_other_present_living(object caster, string str)
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

    if (!present("_purkagia_potion_object_",caster))
    {
        caster->catch_tell("You are not feeling the effects of the "+
            "purkagia potion.\n");
        return ({});
    }

    if (environment(caster)->query_prop(ROOM_UNDER_WATER))
    {
        write("You cannot use the power of Purkagia underwater!\n");
        return ({});
    }
    return oblist;
}

public int
create_spell_purkagia(object caster, object *targets, string argument)
{
    ::create_spell_bolt(caster, targets, argument);
    set_spell_element(SS_ELEMENT_FIRE, 40);
    set_spell_form(SS_PRAYER, 40);
    set_spell_ingredients(({ }));  // Uses a potion
    set_spell_time(1);
    set_spell_mana(96);
    set_spell_task(TASK_ROUTINE);
    set_spell_offensive(1);
    set_bolt_pen(400);
    set_bolt_desc("flames");
    set_bolt_damage_msg(desc_purkagia_damage);
    set_bolt_miss_msg(desc_purkagia_miss);
}

private int
try_to_hit(object caster, object target)
{
    /* Should make a better formula */
    return (target->resolve_task(TASK_ROUTINE, ({ TS_DEX, SS_DEFENSE })) > 0);
}

private void
desc_purkagia_damage(object caster, object target, mixed *result)
{
    string how, him, his, he;

    him = target->query_objective();
    his = target->query_possessive();
    he = target->query_pronoun();

    switch (result[0])
    {
    case 0..15:
        how = "licked";
        break;
    case 16..30:
        how = "scorched";
        break;
    case 31..45:
        how = "burned";
        break;
    case 46..75:
        how = "withered";
        break;
    case 76..90:
        how = "shriveled";
        break;
    case 91..99:
        how = "consumed";
        break;
    default:
        break;
    }

    if (!how) // Death Blow
    {
        caster->catch_tell("The fireball slams into " + his +
            " chest with such force that "+ his + " body explodes.  " +
            "The flying parts of " + his + " body are instantly " +
            "dissolved by the immense heat from the flames.\n");
        target->catch_tell("The fireball slams into your chest with " +
            "such force that your body explodes.  The flying parts of " +
            "your body are instantly dissolved by the immense heat " +
            "from the flames.\n");
        caster->tell_watcher("The fireball slams into " + QTNAME(target) +
            " with such force that " + his + " body explodes.  The flying " +
            "parts are instantly dissolved by the immense heat from the " +
            "flames.\n",target);
        seteuid(getuid());
        target->add_prop(LIVE_I_NO_CORPSE,1);
    }

    else // All other blows
    {
        caster->catch_tell("The fireball connects with " + 
            target->query_the_name(caster) + " and " + he + " is " +
            how + " by it.\n");

        target->catch_tell("The fireball connects with you " +
            "and you are " + how + " by it.\n");

        caster->tell_watcher("The fireball connects " +
           "with " + QTNAME(target) + " and " + he +
           " is " + how + " by it.\n",target); 
    }
}

private void
desc_purkagia_miss(object caster, object target)
{
    string bolt = "The fireball just misses ";

    target->catch_tell(bolt + "you.\n");
    caster->catch_tell(bolt + target->query_the_name(caster) + ".\n");
    caster->tell_watcher(bolt + QCTNAME(target) + ".\n", target);
}
