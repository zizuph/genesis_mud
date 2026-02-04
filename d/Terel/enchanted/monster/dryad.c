/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * dryad.c
 *
 * A dryad. Mortricia 921018
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
#include <herb.h>

#define SPELL_DELAY     20

#define G_KID           0
#define G_YOUNGSTER     1
#define G_GROWN         2
#define G_OLD           3

public void set_spell_prop(object ob);

int g_age;

/*
 * Function name: init_living
 * Description:   Add the 'command items' of this object.
 */
public void
init_living()
{
    ::init_living();
    add_action("do_cut", "cut");
    add_action("do_cut", "destroy");
    add_action("do_cut", "climb");
}

/*
 * Function name: do_cut
 * Description:   Handle the cut action
 * Returns:       1/0
 */
public int
do_cut(string what)
{
    if (what != "tree") return 0;

    command("say Don't try destroy my trees.");
    attack_object(TP);
    return 1;
}

public void
dress_me()
{
    object cloak;

    FIX_EUID;
    
    cloak = clone_object(ENCHANT_DIR + "armour/cloak");
    if (g_age == G_KID) {
        cloak->set_short("small cloak");
        cloak->set_adj(({"small", "green"}));
        cloak->set_long("It's a small green cloak of good quality.\n");
    }
    if (g_age == G_YOUNGSTER) {
        cloak->set_short("green cloak");
        cloak->set_adj(({"green"}));
        cloak->set_long("It's a green cloak of good quality.\n");
    }
    if (g_age == G_GROWN) {
        cloak->set_short("cloak");
        cloak->set_adj(({"green"}));
        cloak->set_long("It's a green cloak of good quality.\n");
    }
    if (g_age == G_OLD) {
        cloak->set_short("well-used cloak");
        cloak->set_adj(({"well-used", "green"}));
        cloak->set_long("It's a well-used green cloak of good quality.\n");
    }
    cloak->set_default_armour(4 + 2*g_age, A_ROBE, 0, 0);
    cloak->move(TO);
    MONEY_MAKE_GC(2+3*g_age)->move(TO);
    command("wear cloak");
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    int i, j, jj, align;

    ::create_monster();
    
    i = random(4);           /* age */
    g_age = i;
    align = 100 - 10 * i;
    j = random(2);           /* gender */
    jj = 3*j;

    set_act_time(2 + i);
    if (i == G_KID) {
        set_name("dryad");
        set_short("tiny dryad");
        set_long("It's a tiny dryad. This cute being never " +
                 "leaves this forest. When annoyed this dryad " +
                 "can make you feel tired. Its hair is green and " +
                 "leafy, and its body has ridges resembling bark.\n");
        set_adj("small");
        set_stats(({15 - jj, 15, 20 + jj, 15, 15, 15}));
        add_act(({"cry"}));
    }
    if (i == G_YOUNGSTER) {
        set_name("dryad");
        set_short("young dryad");
        set_long("It's a young dryad. This magic being never " +
                 "leaves this forest. You should not mess with " +
                 "it unless you are in good condition. Its hair " +
                 "is green and " +
                 "leafy, and its body has ridges resembling bark.\n");
        set_adj("young");
        set_stats(({25 - jj, 25, 25 + jj, 25, 25, 25}));
        add_act(({"smile"}));
    }
    if (i == G_GROWN) {
        set_name("dryad");
        set_short("vivid dryad");
        set_long("It's a vivid dryad. This rare being never " +
                 "leaves this forest. It has some kind of magic " +
                 "touch, and you feel tired just by looking at it. " +
                 "Its hair is green and " +
                 "leafy, and its body has ridges resembling bark.\n");
        set_adj("vivid");
        set_stats(({35 - jj, 25, 35 + jj, 35, 35, 35}));
        add_act(({"frown"}));
    }
    if (i == G_OLD) {
        set_name("dryad");
        set_short("old dryad");
        set_long("It's an old dryad. This strange being never " +
                 "leaves this forest. It's eyes have seen many odd " +
                 "creatures over the years, but you are probably one " +
                 "of the worst ones. Its hair is green and " +
                 "leafy, and its body has ridges resembling bark.\n");
        set_adj("old");
        set_stats(({20 - jj, 15, 25 + jj, 40, 40, 35}));
        add_act(({"stare"}));
    }
    set_race_name("dryad");
    set_gender(j);

    add_prop(LIVE_O_SPELL_ATTACK, TO);

    add_prop(OBJ_I_WEIGHT, 10000 + i * 5000);
    add_prop(OBJ_I_VOLUME, 10000 + i * 5000);

    SET_MAX_HP;
    SET_MAX_MANA;
    set_alignment(align);

    set_all_hitloc_unarmed(5 + i * 10);
    set_all_attack_unarmed(5 + i * 10, 5 + i * 10);

    set_skill(SS_UNARM_COMBAT,  5 + i* (10-jj));
    set_skill(SS_DEFENCE,       5 + i* (10+jj));
    set_skill(SS_SPELLCRAFT,   10 + i* 10);
    set_skill(SS_ELEMENT_LIFE, 10 + i* 10);

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
    int j, v_fat, v_m_fat, tired;
    int v_mana, v_m_mana, mana;
    int me_mana;
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

        tell_room(room, "The dryad mumbles something in a strange " +
                  "language.\n");
        me->command("stare " + who);

        tired = 5 + g_age * 5;
        if (tired > v_fat) tired = v_fat;
        victim->add_fatigue(-tired);
        j = (3*(v_fat-tired))/v_m_fat;
        if (j==2) tell_object(victim, "You feel somewhat tired.\n");
        if (j==1) tell_object(victim, "You feel tired.\n");
        if (j==0) tell_object(victim, "You feel very tired.\n");

        mana = 10 + g_age * 25;
        if (mana > v_mana) mana = v_mana;
        victim->add_mana(-mana);
    }
    set_alarm(itof(10 + SPELL_DELAY), -1.0, &set_spell_prop(me));
}

/*
public void
do_die(object killer)
{
    object herb;

    if (query_hp() > 0) return;
    
    FIX_EUID;
    
    herb = clone_object(ENCHANT_DIR + "obj/herb");
    herb->set_herb_value(100 + 50 * g_age);
    herb->set_effect(HERB_HEALING, "mana", 10 + 5 * g_age);
    herb->move(TO);
    
    ::do_die(killer);
}
*/
