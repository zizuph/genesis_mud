
 /*
  *
  * Saita spell for the Elemental Worshippers of Calia
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

public int create_spell_saita(object caster, object *targets,
    string argument);
private void desc_saita_damage(object caster, object *targets, mixed *results);
private void desc_saita_miss(object caster, object target);

private object *
saita_target_one_other_present_living(object caster, string str)
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

    if (!present("_saita_potion_object_",caster))
    {
        caster->catch_tell("You are not feeling the effects of the "+
            "saita potion.\n");
        return ({});
    }

    if (environment(caster)->query_prop(ROOM_UNDER_WATER))
    {
        write("You cannot use the power of Saita underwater!\n");
        return ({});
    }
    return oblist;
}

public int
create_spell_saita(object caster, object *targets, string argument)
{
    ::create_spell_bolt(caster, targets, argument);
    set_spell_element(SS_ELEMENT_FIRE, 40);
    set_spell_form(SS_PRAYER, 40);
    set_spell_ingredients(({ }));  // Uses a potion
    set_spell_time(2);
    set_spell_mana(64);
    set_spell_task(TASK_SIMPLE);
    set_bolt_pen(301);
    set_bolt_desc("fire");
    set_bolt_damage_msg(desc_saita_damage);
    set_bolt_miss_msg(desc_saita_miss);
}

private int
try_to_hit(object caster, object target)
{
    /* Should make a better formula */
    return (target->resolve_task(TASK_SIMPLE, ({ TS_DEX, SS_DEFENSE })) > 0);
}

private void
desc_saita_miss(object caster, object target)
{
    string bolt = "The bolt of " + bolt_desc + " misses ";

    target->catch_tell(bolt + "you.\n");
    caster->catch_tell(bolt + target->query_the_name(caster) + ".\n");
    caster->tell_watcher(bolt + QCTNAME(target) + ".\n", target);
}

private void
desc_saita_damage(object caster, object target, mixed *result)
{
    string how, bolt, him, his;

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
        case 91..99:
            how = "a huge area of burnt, crispy flesh";
            break;
        default:
            break;
    }

    if (!how) // Death Blow
    {
        caster->catch_tell("It speeds relentlessly towards " +
            target->query_the_name(caster) + ", striking " + him +
            " with enough force to knock " + him + " to the ground.  " +
            "The fire quickly spreads to " + his + " entire body, " +
            "burning away all of the flesh from it.  The smell of " +
            "burnt flesh and hair fills the air.  " + capitalize(his) +
            " lifeless body slowly burns up, leaving no trace of " +
            "its existance except a small pile of ashes.\n");
        target->catch_tell("It speeds relentlessly towards you and " +
            "finally strikes you with enough force to knock you to " +
            "the ground.  The fire quickly spreads over your entire " +
            "body, burning all of the flesh and hair away from it.  " +
            "The last sensation you remember is the smell of your own " +
            "flesh and hair being burned away by the flames.  They " +
            "slowly die out leaving no trace of your existance except " +
            "a small pile of ashes.\n");
        caster->tell_watcher("It speeds relentlessly towards " +
            QTNAME(target) + ", striking " + him + " with enough " +
            "force to knock " + him + " to the ground.  The fire " + 
            "quickly spreads to " + his + " entire body, burning away " +
            "all of the flesh from it.  The smell of burnt flesh and " +
            "hair fills the air.  " + capitalize(his) + " lifeless " +
            "body slowly burns up, leaving no trace of its existance " +
            "except a small pile of ashes.\n",target);
        target->add_prop(LIVE_I_NO_CORPSE,1);
        seteuid(getuid());
        clone_object("/d/Calia/walkers/fire/objects/ash")->move(environment(caster));
    }

    else // All other blows
    {
        caster->catch_tell("It speeds relentlessly towards " + 
            target->query_the_name(caster)+" and strikes "+
            him + ", leaving " + how + ".\n");

        target->catch_tell("It speeds relentlessly towards you "+
            "and strikes you, leaving " + how + ".\n");

        caster->tell_watcher("It speeds relentlessly towards "+
        QTNAME(target)+" and strikes " + him + ", leaving "+
        how + ".\n",target); 
    }
}
