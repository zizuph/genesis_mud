/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * e_dryad.c
 *
 * A dryad. Mortricia 921018
 * modified by Sorgum 941226
 * Added the teacher status, Mortricia, August 1996
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
inherit "/d/Terel/std/teacher";

#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#include <herb.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define HERE(xx)        (xx && environment(xx) == TO)
#define SPELL_DELAY     20

#define NO_OF_HERBS     4
#define MAX_NO_CALLS    3

object *herbs;

public void set_spell_prop(object ob);
public void set_duration(int t);
public void set_up_skills();

public void
dress_me()
{
    int i;
    object cloak;

    FIX_EUID;
    cloak = clone_object(ENCHANT_DIR + "armour/cloak");
    cloak->set_short("well-used green cloak");
    cloak->set_adj(({"well-used", "green"}));
    cloak->set_long("It's a well-used green cloak of good quality.\n");
    cloak->set_default_armour(14, A_ROBE, 0, 0);
    cloak->move(TO);
    MONEY_MAKE_GC(4)->move(TO);
    command("wear cloak");
    for(i=0; i<NO_OF_HERBS; i++) {
        herbs[i] = clone_object(ENCHANT_DIR + "obj/herb");
        herbs[i]->move(TO);
    }
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    
    herbs = allocate(NO_OF_HERBS);
    
    set_name("dryad");
    add_name("aldrain");
    set_living_name("aldrain");
    set_short("very old dryad");
    set_long("It's an ancient dryad. This strange being never " +
             "leaves this forest. Its eyes have seen many odd " +
             "creatures over the years, but you is probably one " +
             "of the worst ones. Its hair is green and " +
             "leafy, and its body has ridges resembling bark.\n");
    set_adj("old");
    set_stats(({50, 50, 50, 80, 80, 80}));
    
    set_act_time(2 + random(20));
    add_act(({"stare"}));
    add_chat("Revere the forest and you will be rewarded.");
    set_race_name("dryad");
    set_gender(0);
    add_prop(LIVE_O_SPELL_ATTACK, TO);
    add_prop(CONT_I_WEIGHT, 25000);
    add_prop(CONT_I_VOLUME, 25000);
    add_prop(CONT_I_HEIGHT, 120);
    add_prop(CONT_I_MAX_WEIGHT, 45000);
    add_prop(CONT_I_MAX_VOLUME, 45000);

    SET_MAX_HP;
    SET_MAX_MANA;
    set_alignment(random(200) + 100);

    set_all_hitloc_unarmed(35);
    set_all_attack_unarmed(35, 35);

    set_skill(SS_UNARM_COMBAT, 40);
    set_skill(SS_DEFENCE,      45);
    set_skill(SS_SPELLCRAFT,   40);
    set_skill(SS_ELEMENT_LIFE, 50);
    set_skill(SS_HERBALISM,    70);

    set_alarm(1.0, -1.0, dress_me);

    create_skill_raise();
    set_up_skills();
}

public void
set_up_skills()
{
   string me, ot;

   me = "how to deal with herbs"; ot = me;
   sk_add_train(SS_HERBALISM, ({me, ot}), 0, 0, MYSTIC_MAX_HERBALISM);
}

public int
sk_improve(string str)
{
   string name;

   name = lower_case(TP->query_name());
   if (!MEMBER(TP)) {
       command("say You are not worthy to be teached.");
       command("point at " + name);
       return 1;
   } else if (query_prop("summoner") != TP->query_name()) {
       command("say You did not summon me.");
       command("stare at " + name);
       return 1;
   }
   return ::sk_improve(str);
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
    if (me_mana >=20) {
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

        tired = 40;
        if (tired > v_fat) tired = v_fat;
        victim->add_fatigue(-tired);
        j = (3*(v_fat-tired))/v_m_fat;
        if(j==2) tell_object(victim, "You feel somewhat tired.\n");
        if(j==1) tell_object(victim, "You feel tired.\n");
        if(j==0) tell_object(victim, "You feel very tired.\n");

        mana = 150;
        if (mana > v_mana) mana = v_mana;
        victim->add_mana(-mana);
    }
    set_alarm(itof(10 + SPELL_DELAY), -1.0, &set_spell_prop(me));
}

public void
set_spell_prop(object ob)
{
    add_prop(LIVE_O_SPELL_ATTACK, ob);
}

public void
poof_me()
{
    tell_room(ETO, "The " + short() + " disappears between the pines.\n");
    remove_object();
}

public void
set_duration(int t)
{
    set_alarm(itof(t), 0.0, poof_me);
}

public int
give_herb(string str)
{
    int i, ii, no_times, tmp;
    string s;

    NF(capitalize(query_verb()) + " what?\n");
    if (!str) return 0;

    if (str != "the pines" && str != "pines" &&
        str != "the forest" && str != "forest") return 0;

    NF("I am not here at your call.\n");
    if (query_prop("summoner") != TP->query_name()) return 0;

    NF("I have nothing to give you.\n");
    no_times = TP->query_prop("_calls_for_dryad");
    if (no_times >= MAX_NO_CALLS) return 0;

    ii = 0;
    for(i=0; i<NO_OF_HERBS; i++) {
        if (HERE(herbs[i])) {
            ii++;
            tmp = TP->query_stat(SS_WIS);
            herbs[i]->set_herb_value(10*tmp/4);
            herbs[i]->set_effect(HERB_HEALING, "mana", tmp/4);
        }
    }
    if (ii == 0) return 0;
    s = "herb";
    if (ii > 1) s += "s";

    command("give " + s + " to " + TP->query_real_name());
    if (no_times) {
        TP->change_prop("_calls_for_dryad", (no_times + 1));
    } else {
        TP->add_prop("_calls_for_dryad", 1);
    }
    return 1;
}

/*
 * Function name: do_cut
 * Description:   Handle the cut action
 * Returns:       1/0
 */
public int
do_cut(string what)
{
    if (what != "tree" && what != "trees") return 0;

    command("say Don't try to destroy my trees.");
    attack_object(TP);
    return 1;
}

/*
 * Function name: init_living
 * Description:   Add the 'command items' of this object.
 */
public void
init_living()
{
    ::init_living();

    add_action(do_cut,    "cut");
    add_action(do_cut,    "destroy");
    add_action(do_cut,    "climb");
    add_action(give_herb, "revere");
    add_action(give_herb, "venerate");

    init_skill_raise();
}
