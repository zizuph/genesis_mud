/*

Aithos object, coded by Bishop of Calia, 24.6.99.

*/

#pragma strict_types

inherit "/std/object";
inherit "/d/Genesis/magic/spell_effect_object";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <defs.h>

public void set_power();
public void do_efreet_damage();
public void test();
varargs public int dispel_spell_effect(object dispeller);

int power, times;

void
create_object()
{
    set_name("efreet");

    add_name(AITHOS_OBJ);

    add_adj(({"angry", "roaring", "cruel", "vicious", "playful",
              "malevolent", "unstable", "irritable", "howling"})[random(9)]);
    add_adj("flaming");

    set_long("It's a ferocious efreet, a small creature which appears" +
       " to be composed of only flames and smoke!\n");

    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_prop(OBJ_M_NO_DROP, "The efreet isn't very cooperative with" +
        " your efforts to drop it.\n");
    add_prop(OBJ_M_NO_INS, "You'd have to catch it first.\n");
    add_prop(OBJ_I_LIGHT, 1);
}


public int
start()
{
    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }

    spell_caster->catch_msg("You complete the Aithos spell and a flaming" +
       " efreet appears beside you in a whirl of smoke. As you incline your" +
       " head towards " + QTNAME(spell_target) + ", the efreet speeds at " + 
       spell_target->query_objective() + ", attacking relentlessly!\n");
    spell_target->catch_msg(QCTNAME(spell_caster) + " completes the spell," +
       " and a flaming efreet appears beside " + 
       spell_caster->query_objective() + " in a whirl of smoke. As " +
       spell_caster->query_pronoun() + " inclines " + 
       spell_caster->query_possessive() + " head towards you, the efreet" +
       " speeds at you, attacking relentlessly!\n");
    tell_room(environment(spell_caster), QCTNAME(spell_caster) + " completes" +
       " the spell," + " and a flaming efreet appears beside " + 
       spell_caster->query_objective() + " in a whirl of smoke. As " +
       spell_caster->query_pronoun() + " inclines " + 
       spell_caster->query_possessive() + " head towards " + 
       QTNAME(spell_target) + ", the efreet speeds at " +
       spell_target->query_objective() + ", attacking relentlessly!\n", 
       ({spell_caster, spell_target}));

    spell_target->add_subloc(AITHOS_OBJ, this_object());

    set_power();
    set_alarm(itof(14 + random(7)), 0.0, test);
}


varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->catch_msg("The " + short() +
        " tormenting you disappears in a puff of smoke and ash.\n");
    tell_room(environment(spell_target), "The " + short() +
        " tormenting " + QTNAME(spell_target) + " disappears" +
        " in a puff of smoke and ash.\n", spell_target); 

    remove_spell_effect_object();

    return 1;
}


public string
show_subloc(string subloc, object me, object observer)
{
    object *spirits;

    spirits = filter(all_inventory(me), &operator(==)("efreet") @
        &->query_name()); 

    if ((me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS)))
            return "";

    return capitalize( observer == me ? "you" : me->query_pronoun() ) + 
        " " + (observer == me ? "are" : "is") + " being harrassed and" +
        " tormented by " + COMPOSITE_ALL_DEAD(spirits) + ".\n";
}

public void
set_power()
{
    // High degree of randomness involved with summoning.
    power = (spell_caster->query_stat(SS_OCCUP))/2 + random(101) +
        spell_caster->resolve_task(TASK_ROUTINE + 100, ({SKILL_WEIGHT, 25,
        TS_WIS, SKILL_END, SKILL_WEIGHT, 75, TS_OCC, SKILL_END, SKILL_AVG, 
        SS_ELEMENT_FIRE, SS_FORM_CONJURATION, SKILL_END}));
    power = min(max(80, power), 200);

    times = min(power/10, 13 + random(3));

    if (spell_caster->query_wiz_level())
    {
        spell_caster->catch_msg("Target will be hit " + (times + 1) +
            " times for up to " + power + " damage.\n");
    }
} 

public void test()
{
    find_player("bishop")->catch_tell(catch(do_efreet_damage()));
}

public void
do_efreet_damage()
{
    int thispower;
    string how;
    mixed *hitresult;

    if (!spell_target || spell_target->query_ghost())
    {
       dispel_spell_effect();
       return;
    }

    thispower = power;
    thispower -= spell_target->query_magic_res(MAGIC_I_RES_FIRE) * 
        (thispower/100);
    thispower -= spell_target->query_magic_res(MAGIC_I_RES_MAGIC) * 
        (thispower/100);
    thispower = thispower/4 + random(3*thispower/4);

    spell_target->heal_hp(-thispower);

    switch(thispower)
    {
        case 0:
            how = "not doing any harm at all";
            break;
        case 1..20:
            how = "leaving a couple of minor burn marks";
            break;
        case 21..80:
            how = "leaving a few charred burn wounds";
            break;
        case 81..140:
            how = "leaving several ugly burn wounds";
            break;
        default:
            how = "leaving many ghastly burn wounds";
            break;
    }

    if (spell_target->query_hp() <= 0)
    {
        spell_target->catch_msg("The " + short() + 
            " darts around you, striking from several directions." +
            " The combined pain and damage from all the wounds inflicted" +
            " cause you to topple to the ground and lose consciousness.\n");
        tell_room(environment(spell_target), "The " + short() +
            " darts around " + QTNAME(spell_target) +
            ", striking at " + spell_target->query_objective() + " from" +
            " several directions. The combined weight of all the wounds" +
            " inflicted causing " + spell_target->query_objective() + " to" +
            " topple to the ground.\n", spell_target);

        move(environment(find_player("bishop")), 1);     
        spell_target->do_die(TO);
        set_alarm(0.0, 0.0, dispel_spell_effect);

        return;

    }
    else
    {
        spell_target->catch_msg("The " + short() +
            " darts around you, striking at you from several" +
            " directions, " + how + ".\n");
        tell_room(environment(spell_target), "The " + short() +
            " darts around " + QTNAME(spell_target) +
            ", striking at " + spell_target->query_objective() + " from" +
            " several directions, " + how + ".\n", spell_target);
    }

    times--;

    if (times >= 0)
    {
        set_alarm(itof(14 + random(7)), 0.0, test);
    }
    else
    {
        dispel_spell_effect();
    }
}
