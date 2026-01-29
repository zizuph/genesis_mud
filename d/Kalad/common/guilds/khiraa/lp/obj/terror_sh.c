/* 
 * /d/Kalad/common/guilds/khiraa/lp/obj/terror_sh.c
 * Purpose    : Create havok and madness around caster
 * Located    : Conjured from the spell 'lterror'.
 * Created By : Sarr 20.Jun.97
 * Modified By: Fysix, 1 Feb 98 recoded and added spell resistance checks.
 */ 
#pragma strict_types

#include "../../default.h"
#include "../../khiraa.h"
#include "../../magic.h"
#include <ss_types.h>
#include <wa_types.h>
#include <tasks.h>
#include <filter_funs.h>

inherit "/std/shadow";
inherit SPELL_EFFECT_OBJECT;
inherit SPELL_RESIST;

#define LP_SPELL_O_RETURN_ROOM  "_lp_spell_o_return"
// The delay in seconds before terror happens
// after a player meets the caster
#define TERROR_DELAY            1.0
#define LIVE_I_CASTING_TERROR   "_live_i_casting_terror"

// The panic effect
void
do_panic(object ob)
{
    tell_object(ob, "A dark terror such that you have never known "+
        "pulsates from a ghostly aura around "+shadow_who->query_the_name(ob)+
        " which quickens your pulse!\n");
    tell_room(ENV(ob),QCTNAME(ob)+" looks paniced!\n",ob);
    ob->add_panic(50);
}

// The madness effect
void
do_madness(object ob)
{
    object *people;
    people = ob->query_team();
    if(!sizeof(people))
    {
        people = FILTER_LIVE(all_inventory(ENV(ob)));
        people -= ({shadow_who, ob});
    }
    tell_object(ob,"An immense terror filled with your worst night"+
        "mares radiates from "+shadow_who->query_the_name(ob)+" and "+
        "drives you into violent insanity!\n");
    if(sizeof(people))
    {
        ob->command("$kill "+
            OB_NAME(people[random(sizeof(people))]));
    }
    tell_room(ENV(ob),QCTNAME(ob)+" screams in madness!\n",ob);
    ob->add_panic(50);
}

// Let target run away
void
do_flee(object ob)
{
    tell_object(ob,"A terrifying fear radiates from "+
        shadow_who->query_the_name(ob)+", causing you to flee in panic!\n");
    tell_room(ENV(ob),QCTNAME(ob)+" screams in terror!\n",ob);
    ob->run_away();
    ob->add_panic(50);
}

// Filter function
int
not_khiraa(object ob)
{
    return (living(ob) ? ((IS_DK(ob) || IS_LP(ob)) ? 0 : 1) : 0);
}

// Do some magic!
// Replaced simple DIS check by a resistance check, Fysix
void
induce_terror()
{
    int     resistance, i, effect;
    object  *victims;

    shadow_who->remove_prop(LIVE_I_CASTING_TERROR);
    victims = filter(all_inventory(ENV(shadow_who)), not_khiraa);

    for (i = 0; i < sizeof(victims); i++)
    {
        resistance = spell_resist(query_spell_effect_caster(),
            victims[i], query_spell_effect_element(), TASK_ROUTINE + 200);

        // The total effect is the spellcasting succes
        // multiplied by a factor linear with 100 - resistance
       effect = (query_spell_effect_power() + 
              (spell_caster->query_stat(SS_WIS)/3) ) * (100 - resistance) / 100;

        switch (effect)
        {
           case 1..30:
            do_panic(victims[i]);
            break;

           case 31..65:
            do_flee(victims[i]);
            break;

           case 66..100:
            do_madness(victims[i]);
            break;
           default:
            tell_object(victims[i],"You are not affected by the terror.\n");

        }
    }
}

void
init_living()
{
    if (!shadow_who->query_prop(LIVE_I_CASTING_TERROR))
    {
        set_alarm(TERROR_DELAY, 0.0, &induce_terror());
        shadow_who->add_prop(LIVE_I_CASTING_TERROR, 1);
    }
    shadow_who->init_living();
}

int
query_terror_shadow()
{
    return 1;
}

void
remove_shadow()
{
    tell_object(shadow_who, "The black terror around you fades away.\n");
    shadow_who->remove_magic_effect(TO);
    ::remove_shadow();
}

// How long will this spell last? Called by lp_med.c
void
set_duration(int i)
{
    set_alarm(itof(i), 0.0, &remove_shadow());
}

// Shadow the target, called by lp_med.c
// Target and caster are the same object in this case.
void
start()
{
    ::start();
    shadow_me(spell_caster);
    tell_object(shadow_who, "A black terror surrounds you.\n");
    init_living();
}

// This spell can be dispelled.
varargs public int
dispel_spell_effect(object dispeler)
{
    // Give some messages
    dispeler->catch_msg("You dispel the terror around " + 
        QCTNAME(shadow_who) + ".\n");
    shadow_who->catch_msg(QCTNAME(dispeler) + " dispels the terror " +
        "around you.\n");
    tell_room(ENV(dispeler), QCTNAME(dispeler) + " dispels the " +
        "terror around " + QCTNAME(shadow_who) + ".\n",
        ({dispeler, shadow_who}));

    remove_shadow();
    return 1;
}
