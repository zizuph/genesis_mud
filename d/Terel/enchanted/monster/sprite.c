/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * sprite.c
 *
 * A sprite. Mortricia 921018
 * modified by Sorgum 941226
 */

#include "/d/Terel/include/Terel.h"

inherit STDMONSTER;

inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/std/act/domove";

#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#define ARM_DIR         MORTRICIA_DIR + "armours/"
#define SPELL_DELAY     25

#define G_KID           0
#define G_YOUNGSTER     1
#define G_GROWN         2
#define G_OLD           3

void set_spell_prop(object ob);

int g_age;

public void
dress_me()
{
    object cloak;

    FIX_EUID;
    cloak = clone_object(ARM_DIR + "cloak");
    if(g_age == G_KID) {
        cloak->set_short("small cloak");
        cloak->set_adj(({"small", "green"}));
        cloak->set_long("It's a small green cloak of good quality.\n");
    }
    if(g_age == G_YOUNGSTER) {
        cloak->set_short("green cloak");
        cloak->set_adj(({"green"}));
        cloak->set_long("It's a green cloak of good quality.\n");
    }
    if(g_age == G_GROWN) {
        cloak->set_short("cloak");
        cloak->set_adj(({"green"}));
        cloak->set_long("It's a green cloak of good quality.\n");
    }
    if(g_age == G_OLD) {
        cloak->set_short("well-used cloak");
        cloak->set_adj(({"well-used", "green"}));
        cloak->set_long("It's a well-used green cloak of good quality.\n");
    }
    cloak->set_default_armour(4 + 2*g_age, A_ROBE, 0, 0);
    cloak->move(TO);
    MONEY_MAKE_SC(3+3*g_age)->move(TO);
    command("wear cloak");
}

public void
create_monster()
{
    int i, j, jj, align;

    if (!IS_CLONE)
        return;

    ::create_monster();
    i = random(4);           /* age */
    g_age = i;
    align = 50 - 10 * i;
    j = random(2);           /* gender */
    jj = 3*j;

    set_act_time(2 + i);
    if (i == G_KID) {
        set_name("sprite");
        set_short("small sprite");
        set_long("It's a small sprite. This tree-sprite never " +
                 "leaves this forest. When annoyed this sprite " +
                 "can make you feel tired.\n");
        set_adj("small");
        set_stats(({10 - jj, 10, 15 + jj, 10, 10, 10}));
        add_act(({"sniff"}));
    }
    if (i == G_YOUNGSTER) {
        set_name("sprite");
        set_short("young sprite");
        set_long("It's a young sprite. This tree-sprite never " +
                 "leaves this forest. You should not mess with " +
                 "it unless you are in good condition.\n");
        set_adj("young");
        set_stats(({20 - jj, 20, 20 + jj, 20, 20, 20}));
        add_act(({"smile"}));
    }
    if (i == G_GROWN) {
        set_name("sprite");
        set_short("vivid sprite");
        set_long("It's a vivid sprite. This tree-sprite never " +
                 "leaves this forest. It has some kind of magic " +
                 "touch, and you feel tired just by looking at it.\n");
        set_adj("vivid");
        set_stats(({30 - jj, 25, 30 + jj, 30, 30, 30}));
        add_act(({"frown"}));
    }
    if (i == G_OLD) {
        set_name("sprite");
        set_short("old sprite");
        set_long("It's an old sprite. This tree-sprite never " +
                 "leaves this forest. It's eyes have seen many odd " +
                 "creatures, but you is probably one of the worst ones.\n");
        set_adj("old");
        set_stats(({20 - jj, 15, 20 + jj, 40, 40, 30}));
        add_act(({"stare"}));
    }
    set_race_name("sprite");
    set_gender(j);
    add_prop(OBJ_I_WEIGHT, 10000 + i * 5000);
    add_prop(OBJ_I_VOLUME, 10000 + i * 5000);
    add_prop(LIVE_O_SPELL_ATTACK, TO);

    SET_MAX_HP;
    SET_MAX_MANA;
    set_alignment(align);

    set_all_hitloc_unarmed(2 + i * 10);
    set_all_attack_unarmed(2 + i * 10, 2 + i * 10);

    set_skill(SS_UNARM_COMBAT, 2  + i*(10-jj));
    set_skill(SS_DEFENCE,      2  + i*(10+jj));
    set_skill(SS_SPELLCRAFT,   10 + i*10);

    set_alarm(1.0, -1.0, dress_me);
}

public void
set_spell_prop(object ob)
{
    add_prop(LIVE_O_SPELL_ATTACK, ob);
}

public void
spell_attack(object me, object victim)
{
    int v_fat, v_m_fat, tired;
    int v_mana, v_m_mana, mana;
    int j, me_mana;
    string who;
    object room;

    me_mana = me->query_mana();

    if (me_mana >= 20) {
        me->add_mana(-20);

        who = victim->query_name();
        room = environment(me);

        v_fat    = victim->query_fatigue();
        v_mana   = victim->query_mana();
        v_m_fat  = victim->query_max_fatigue();
        v_m_mana = victim->query_max_mana();

        tell_room(room, "The sprite mumbles something in a strange " +
                  "language.\n");
        me->command("stare " + who);
        tired = 3 + g_age * 3;
        if (tired > v_fat) tired = v_fat;
        victim->add_fatigue(-tired);
        j = (3*(v_fat-tired))/v_m_fat;
        if (j==2) tell_object(victim, "You feel somewhat tired.\n");
        if (j==1) tell_object(victim, "You feel tired.\n");
        if (j==0) tell_object(victim, "You feel very tired.\n");

        mana = 5 + g_age * 5;
        if (mana > v_mana) mana = v_mana;
        victim->add_mana(-mana);
    }

    set_alarm(itof(10 + SPELL_DELAY), -1.0, &set_spell_prop(me));
}
