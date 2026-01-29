/*
 * ogion.c
 * FIXA
 * Used in wild/ihut.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <formulas.h>
#include <macros.h>
#include <comb_mag.h>
#include <cmdparse.h>
#include <filter_funs.h>

int has_introduced = 0;

void introduce_me();
void remove_int();

void
create_monster()
{
    set_name("ogion");
    set_living_name("ogion");
    set_title("the silent");
    set_race_name("human");
    set_long("Though he looks quite weak you can feel a strong aura of " +
             "magic surrounding him.\n");
    set_adj("silent");

    set_default_answer(VBFC_ME("otherask"));
    add_ask(({"name", "about name", "real name", "about real name",
              "for real name",
              "for name", "true name", "for true name",
              "what is my true name"}), VBFC_ME("ask"));

    set_alignment(5000);

    set_stats(({50, 50, 50, 100, 100, 100}));

    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_FORM_CONJURATION, 100);
    set_skill(SS_ELEMENT_FIRE, 100);

    add_prop(LIVE_O_SPELL_ATTACK, TO);

    trig_new("%w 'introduces' %s", "react_introduce");
}

int
query_knight_prestige()
{
    return -5;
}

void
equip_me()
{
    clone_object(ROKEDIR + "arm/cloak")->move(TO);

    command("wear all");
}

string
otherask()
{
    object who;

    who = previous_object();

    command("peer " + lower_case(who->query_real_name()));
    return "";
}

string
ask(string str)
{

    string name;

    //    name = QUERY_TRUE_NAME(lower_case(TP->query_real_name()));

    TP->catch_msg(QCTNAME(TO) + " whispers to you: Your true name is " +
                  name + ".\n");
    tell_room(E(TO), QCTNAME(TO) + " whispers something to " + QTNAME(TP) +
              ".\n", TP);

    if (!QDONE(ROKEGROUP, OGIONMAZE))
    {
        TP->catch_msg("You feel more experienced.\n");
        QSET(ROKEGROUP, OGIONMAZE);
        QLOG("Ogion");
        TP->add_exp(OGIONMAZEXP);
    }
    return "";
}

void
react_introduce(string person, string who)
{
    if (!has_introduced)
    {
        set_alarm(6.0, 0.0, introduce_me);
        has_introduced = 1;
        set_alarm(30.0, 0.0, remove_int);
    }
}

void
introduce_me()
{
    command("introduce myself");
}

void
remove_int()
{
    has_introduced = 0;
}

void
add_sp(object ob)
{
    add_prop(LIVE_O_SPELL_ATTACK, ob);
    return;
}

void
spell_attack(object attacker, object target)
{
    int hurt;
    mixed *hitresult;
    string how;

    if (attacker->query_mana() < 40)
    {
        set_alarm(itof(1 + random(10)), 0.0, &add_sp(attacker));
        return;
    }

    attacker->add_mana(-40);

    hurt = target->query_max_hp() * 7 / 10;

    target->reduce_hit_point(hurt);

    tell_room(E(attacker), QCTNAME(attacker) + " stares at " +
              QTNAME(target) +
              " and does a magical gesture.\n", target);
    target->catch_msg(QCTNAME(attacker) +
                      " stares at you and does a magical gesture.\n");

    tell_room(E(attacker),
              "Suddenly a bright light strucks " + QCTNAME(target) +
              " and throws " + target->query_objective() + " out.\n",
              target);
    target->catch_msg("A bright light burns you badly, and throws you out.\n\n");

    attacker->stop_fight(target);
    target->stop_fight(attacker);

    target->move(WILDDIR + "ohut");
    target->add_prop("_enemy_of_ogion", 1);
    target->command("look");

    target->do_die(attacker);

    set_alarm(itof(1 + random(10)), 0.0, &add_sp(attacker));
}
