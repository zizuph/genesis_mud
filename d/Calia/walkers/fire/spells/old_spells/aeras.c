
 /*
  *
  * Aeras (Flame Wind) spell for the Firewalkers Guild
  * by Jaacar   Originally: August 7th, 1996
  * recoded to new spell system: May 4th, 1998
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
#include "defs.h"
#include FIRE_HEADER

public int create_spell_aeras(object caster, object *targets,
    string argument);
private void desc_aeras_damage(object caster, object *targets, mixed *results);
private void desc_aeras_miss(object caster, object target);

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

    if (!present("_aeras_potion_object_",caster))
    {
        caster->catch_tell("You are not feeling the effects of the "+
            "aeras potion.\n");
        return ({});
    }

    if (environment(caster)->query_prop(ROOM_UNDER_WATER))
    {
        write("You cannot use the power of Aeras underwater!\n");
        return ({});
    }

    return oblist;
}

public int
create_spell_aeras(object caster, object *targets, string argument)
{
    ::create_spell_bolt(caster, targets, argument);
    set_spell_element(SS_ELEMENT_FIRE, 50);
    set_spell_form(SS_PRAYER, 50);
    set_spell_ingredients(({ }));  // Uses a potion
    set_spell_time(2);
    set_spell_mana(120);
    set_spell_task(TASK_ROUTINE);
    set_bolt_pen(502);
    set_bolt_desc("flaming");
    set_spell_offensive(1);
    set_bolt_damage_msg(desc_aeras_damage);
    set_bolt_miss_msg(desc_aeras_miss);
}

private int
try_to_hit(object caster, object target)
{
    /* Should make a better formula */
    return (target->resolve_task(TASK_ROUTINE, ({ TS_DEX, SS_DEFENSE })) > 0);
}

private void
desc_aeras_damage(object caster, object target, mixed *result)
{
    string how, wind, him, his;
    int dam = result[3];

    him = target->query_objective();
    his = target->query_possessive();

    switch (result[0])
    {
        case 0..5:
            how = "sear";
            break;
        case 6..15:
            how = "char"; 
            break;
	case 16..30:
            how = "scorch"; 
            break;
	case 31..50:
            how = "burn"; 
            break;
	case 51..90:
            how = "consume"; 
            break;
	case 91..99:
            how = "oxidize"; 
            break;
        default:
            break;
    }

    if (dam > 600)
        wind = "huge flames";
    else
        wind = ((dam > 300) ? "flames" : "small flames");

    if (!how) // Death Blow
    {
        caster->catch_tell("The ground opens around your feet.  "+
            "Molten lava bubbles to the surface, causing spontaneous "+
            "flames to erupt.  You point at "+target->query_the_name(caster)+ 
            " and " + wind + " rush toward " + him +
            ".  Large fires rise up and swallow "+ him +", leaving "+ his +
            " blackened corpse standing there as the flames slowly withdraw "+
            "into the ground.  The blackened corpse falls to the ground "+
                "with a loud 'THUD' and shatters into a cloud of "+
                "ash.\nThe ground returns to normal.\n");

        target->catch_tell("The ground opens around " + caster->query_the_name(target) +
            "'s feet.  Molten lava bubbles to the surface, causing "+
            "spontaneous flames to erupt.  Suddenly, "+
            C_HE+" points at you and " + wind + " rush towards you.  "+
            "Large fires rise up and swallow you whole, burning you beyond "+
            "recognition and leaving your blackened corpse smouldering as "+
            "the flames slowly withdraw back into the ground.  Your blackened "+
                "corpse falls to the ground with a loud 'THUD' and "+
                "shatters into a cloud of ash.\nThe ground "+
            "returns to normal.\n");

        caster->tell_watcher("The ground opens around "+
            QCTNAME(caster) + "'s feet.  Molten lava bubbles to the "+
            "surface, causing spontaneous flames to erupt.  Suddenly, "+
            QCTNAME(caster) + " points at " + QTNAME(target) +
            " and " + wind + " rush toward " + QTNAME(target) +
            ".  Large fires rise up and swallow "+ him +", leaving "+ his +
            " blackened corpse standing there as the flames slowly withdraw "+
            "into the ground.  The blackened corpse falls to the ground "+
                "with a loud 'THUD' and shatters into a cloud "+
                "of ash.\nThe ground returns to normal.\n",target);
            seteuid(getuid());
            target->add_prop(LIVE_I_NO_CORPSE,1);
            clone_object("/d/Calia/walkers/fire/objects/ash")->move(environment(target));
    }

    else // All other blows
    {
        caster->catch_tell("The ground opens around your feet.  "+
            "Molten lava bubbles to the surface, causing spontaneous "+
            "flames to erupt.  You point at "+target->query_the_name(caster)+ 
            " and " + wind + " rush toward " + him +
            " and " + how + " " + him + " with a "+
            "fiery wind.\nThe ground returns to normal.\n");

        target->catch_tell("The ground opens around " + caster->query_the_name(target) +
            "'s feet.  Molten lava bubbles to the surface, causing "+
            "spontaneous flames to erupt.  Suddenly, "+
            C_HE+" points at you and " + wind + " rush towards you and "+
            how + " you with a fiery wind.\nThe ground returns to normal.\n");
        
        caster->tell_watcher("The ground opens around "+
            QCTNAME(caster) + "'s feet.  Molten lava bubbles to the "+
            "surface, causing spontaneous flames to erupt.  Suddenly, "+
            QCTNAME(caster) + " points at " + QTNAME(target) +
            " and " + wind + " rush toward " + QTNAME(target) +
            " and " + how + " " + him +
            " with a fiery wind.\nThe ground returns to normal.\n",target); 
    }
}

private void
desc_aeras_miss(object caster, object target)
{
    string bolt = "The bolt of " + bolt_desc + " misses ";

    target->catch_tell(bolt + "you.\n");
    caster->catch_tell(bolt + target->query_the_name(caster) + ".\n");
    caster->tell_watcher(bolt + QCTNAME(target) + ".\n", target);
}
