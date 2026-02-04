/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * bat2.c
 *
 * A bat. Mortricia 920917
 * Modified by Sorgum 941029
 * Modified by Mortricia 960201
 */

#include "/d/Terel/include/Terel.h"
inherit STDCREATURE;
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/domove";

#include <ss_types.h>
#include <wa_types.h>

#define NO_OF_SIZES 3
#define ADJS        ({"small", "medium-sized", "large"})

static int size = random(NO_OF_SIZES);

public void
create_creature()
{
    ::create_creature();

    set_name("bat");
    set_long("It is a hairy black bat. It looks quite hungry. " +
             "Its teeth are small but sharp.\n");
    set_adj(({ADJS[size], "black"}));
    set_race_name("bat");
    set_stats(({10+size*6, 12+size*7, 10+size*6,
                 5+size*3,  5+size*3,  8+size*4}));
    SET_MAX_HP;
    set_alignment(-40 - 6*size);
    set_gender(NEUTER);

    set_act_time(4);
    set_cact_time(4);
    add_act("@@bat_act");
    add_cact("@@bat_act");

    set_skill(SS_DEFENCE, 5 + size*5 + random(5));
    set_skill(SS_UNARM_COMBAT, 5 + size*5 + random(5));

    add_prop(LIVE_I_NEVERKNOWN,    1);
    add_prop(LIVE_I_SEE_DARK,      10);
    add_prop(CONT_I_WEIGHT,     3000 + size*500);
    add_prop(CONT_I_VOLUME,     1000 + size*100);
    add_prop(CONT_I_MAX_WEIGHT, 3600 + size*500);
    add_prop(CONT_I_MAX_VOLUME, 1300 + size*100);

    add_item(({"wings"}), "The wings are hairy.\n");
    add_item(({"teeth"}), "The teeth are sharp.\n");

    set_random_move(9, 0);
    set_m_out("flies");
}

public string
bat_act()
{
    object *all, ob=0;
    int i;

    if (query_attack()) return "scream";

    all = all_inventory(ETO);
    for (i=0; i<sizeof(all); i++) {
        if (!living(all[i]))
            continue;
        if (all[i]->query_prop(LIVE_I_UNDEAD))
            continue;
        if (all[i]->query_race_name() == query_race_name())
            continue;
        if (all[i]->query_race_name() == "dog")
            continue;
        if (all[i]->query_name() == "Busty" && all[i]->query_npc())
            continue;
        if (all[i]->query_hp() < query_hp())
        {
            ob = all[i];
            break;
        }
    }

    if (ob) {
        attack_object(ob);
        ob->catch_msg(QCTNAME(TO) + " suddenly decides to attack you!\n");
        tell_room(ETO, QCTNAME(TO) + " suddenly attacks " + QTNAME(ob)
                  + ".\n", ob);
        set_follow(ob->query_real_name());
        return "scream";
    }

    i = random(3);
    if (i == 0) {
        return "emote flies around looking for food.";
    } else if (i == 1) {
        return "emote flies silently above your head.";
    } else {
        return "emote looks at you with its large eyes.";
    }
}

public int
special_attack(object victim)
{
    if (random(5) != 0) return 0;

    victim->catch_msg(QCTNAME(TO) + " dives quickly down and bites you " +
                      "in your throat!\n");
    tell_room(ETO, QCTNAME(TO) + " dives down and bites " + QTNAME(victim) +
              " in " + victim->query_possessive() + " throat.\n", victim);

    victim->reduce_hit_point(10 + 5*size + random(10 + 5*size));
    if (victim->query_hp() <= 0) victim->do_die(TO);

    return 1;
}

/*
 * Function name: cr_try_hit
 * Description:   Decide if a certain attack fails because of something
 *                related to the attack itself.
 * Arguments:     aid:   The attack id
 * Returns:       True if hit, otherwise 0.
 */
public int
cr_try_hit(int aid)
{
    if (random(3) == 0) {
        tell_room(ETO, QCTNAME(TO) + " flies upward to avoid attacks.\n", TO);
        return 0;
    }
    return 1;
}

#define A_BITE  0
#define A_CLAW  1

#define H_HEAD 0
#define H_BODY 1
#define H_WING 2

public void
cr_configure()
{
    add_attack(10+size*5, 10+size*5, W_IMPALE, 75, A_BITE);
    add_attack( 5+size*5,  5+size*5, W_SLASH,  25, A_CLAW);

    add_hitloc( ({ 7+size*5, 7+size*5, 7+size*5 }), 20, "head",  H_HEAD);
    add_hitloc( ({ 6+size*5, 6+size*5, 6+size*5 }), 35, "body",  H_BODY);
    add_hitloc( ({ 2+size*5, 2+size*5, 2+size*5 }), 45, "wings", H_WING);
}

public string
cr_attack_desc(int aid)
{
    switch (aid)
    {
        case A_BITE: return "teeth";
        case A_CLAW: return "claws";
    }
}
