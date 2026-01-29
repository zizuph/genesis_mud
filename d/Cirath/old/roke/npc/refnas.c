/*
 * refnas.c
 * FIXA
 * Used in nyreese/cas_c7.c
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

static void tell_watch(string str, object me, object enemy);

void
create_monster()
{
    set_living_name("krfsm");
    set_name("krfsm");
    set_race_name("wizard");
    set_short("good wizard");
    set_long("This is the good wizard who rules the castle.\n");
    set_adj("good");

    set_alignment(750);

    set_cact_time(15);
    add_cact("zap wand me");

    default_config_npc(100);

    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_AWARENESS, 80);

    NEVERKNOWN;

    add_prop(LIVE_O_SPELL_ATTACK, TO);
}

int
query_knight_prestige()
{
    return -1;
}

void
equip_me()
{
    clone_object(ROKEDIR + "arm/glowingmail")->move(TO);
    clone_object(ROKEDIR + "arm/glowingshield")->move(TO);
    clone_object(ROKEDIR + "arm/glowinghelmet")->move(TO);
    clone_object(ROKEDIR + "wep/refnasstaff")->move(TO);
    clone_object(ROKEDIR + "obj/wand")->move(TO);

    command("wear all");
    command("wield all");
}

void
add_sp(object ob)
{
    add_prop(LIVE_O_SPELL_ATTACK, ob);
}

void
spell_attack(object attacker, object target)
{
    int hurt;
    mixed *hitresult;
    string how, how2;

    if (attacker->query_mana() < 40)
    {
        set_alarm(itof(1 + random(10)), 0.0, &add_sp(attacker));
        return;
    }
    if (random(10) < 3)
    {
        set_alarm(itof(1 + random(10)), 0.0, &add_sp(attacker));
        return;
    }
    attacker->add_mana(-40);

    hurt = F_PENMOD(70, 100);
    hurt -= hurt * target->query_magic_res(MAGIC_I_RES_FIRE) / 100;

    hitresult = target->hit_me(hurt, 0, attacker, 0);

    tell_watch(QCTNAME(attacker) + " throws a lightening bolt at " +
               QTNAME(target) + ".\n", attacker, target);

    how = " fumbles his spell!";
    how2 = how;

    if (hitresult[0] > 0)
    {
        how = " touches you, filling you with a cold, death-like feeling.";
        how2 = " harms" + QCTNAME(TP) + ".";
    }
    if (hitresult[0] > 20)
    {
        how = " curses you. You feel less confident.";
        how2 = " curses " + QCTNAME(TP) + ".";
    }
    if (hitresult[0] > 50)
    {
        how = " chants a spell weakening you.";
        how2 = " chants a spell, leaving " + QCTNAME(TP) + " weaker.";
    }
    if (hitresult[0] > 100)
    {
        how = " throws a large ball of green fire at you. It engulfs and burns you.";
        how2 = " throws a large ball of green fire at " + QCTNAME(TP) + ". "
                + QCTNAME(TP) + " burns before your eyes.";
    }
    target->catch_msg(QCTNAME(attacker) + how + "\n");
    tell_watch("The wizard " + how2 + "\n", attacker, target);

    if (target->query_hp() <= 0)
        target->do_die(attacker);

    set_alarm(itof(1 + random(10)), 0.0, &add_sp(attacker));
}

// finns stod for detta? FIXA
static void
tell_watch(string str, object me, object enemy)
{
    object *ob;
    int i;

    ob = FILTER_LIVE(all_inventory(environment(me))) - ({me});
    ob -= ({enemy});
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}
