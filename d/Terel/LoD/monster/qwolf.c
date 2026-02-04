/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * qwolf.c
 *
 * A wolf. Mortricia 920917
 * Modified by Sorgum 941029
 * Modified by Mortricia 960628
 */
#include "/d/Terel/include/Terel.h"
inherit STDCREATURE;
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/domove";
inherit "/std/act/attack";

#include <ss_types.h>
#include <wa_types.h>

#include "/d/Terel/LoD/dungeon/quest.h"

public int
my_aggressive()
{
    object coat = present(DQ_WOLF_COAT, TP);
    
    if (coat && coat->query_worn() == TP)
        return 0;
        
    return 1;   
}

public string
my_growl()
{
    int i;
    object coat, *obs;
    
    if (query_attack())
        return "growl";

    obs = filter(all_inventory(ETO) - ({ TO }), living);
    for (i=0; i<sizeof(obs); i++)
    {
        coat = present(DQ_WOLF_COAT, obs[i]);
        if (coat && coat->query_worn() == obs[i]) continue;
        
        attack_object(obs[i]);
        obs[i]->catch_msg(QCTNAME(TO) + " attacks you!\n");
        tell_room(ETO, QCTNAME(TO) + " attacks " +
                  QTNAME(obs[i]) + ".\n", ({obs[i], TO}));
        break;
    }

    return "growl";
}

public void
create_creature()
{
    ::create_creature();
    
    set_name("wolf");
    set_long("It is a huge dangerous-looking wolf.\n");
    set_adj(({"huge", "dangerous-looking"}));
    set_race_name("wolf");
    set_stats(({128, 120, 120, 89, 89, 110}));
    SET_MAX_HP;
    set_alignment(0);
    set_gender(0);
    set_aggressive("@@my_aggressive");

    set_act_time(2);
    add_act("@@my_growl");

    set_skill(SS_DEFENCE, 85);
    set_skill(SS_UNARM_COMBAT, 85);
    set_skill(SS_AWARENESS, 90);

    add_prop(LIVE_I_NEVERKNOWN,    1);
    add_prop(LIVE_I_SEE_DARK,      1);
    add_prop(CONT_I_WEIGHT,     35000);
    add_prop(CONT_I_VOLUME,     34000);
    add_prop(CONT_I_MAX_WEIGHT, 52600);
    add_prop(CONT_I_MAX_VOLUME, 50000);

    add_item(({"fur"}), "It looks very clean.\n");
    add_item(({"teeth"}), "The teeth are very sharp.\n");
    add_item(({"eyes"}), "They are yellowish.\n");
}

public int
special_attack(object victim)
{
    object necklace, collar;
    int dam;
    
    if (random(5))
        return 0;
    
    necklace = present(DQ_NECKLACE, victim);
    collar = present("collar", victim);
    if (necklace) {
        victim->catch_msg(QCTNAME(TO) + " jumps up on you and bites you " +
                      "in your throat!  Luckily, the " +
                      necklace->short() + " seems to take most of the blow.\n");
        dam = 20;
    } else if (collar && collar->query_worn() == victim) {
        victim->catch_msg(QCTNAME(TO) + " jumps up on you and bites you " +
                      "in your throat!  Luckily, the " +
                      collar->short() + " seems to take some of the blow.\n");
        dam = 50;
    } else {
        victim->catch_msg(QCTNAME(TO) + " jumps up on you and bites you " +
                      "in your throat! Ouch!\n");
        dam = 500;
    }
    tell_room(ETO, QCTNAME(TO) + " jumps up on " + QTNAME(victim) +
              " and bites " + victim->query_objective() + " in " +
              victim->query_possessive() + " throat.\n", victim);
    
    victim->reduce_hit_point(dam + random(dam));
    if (victim->query_hp() <= 0)
        victim->do_die(TO);
    
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
    if (random(3))
        return 1;
        
    tell_room(ETO, QCTNAME(TO) +
              " swiftly backs off to avoid attacks.\n", TO);
    return 0;
}

#define A_BITE  0
#define A_CLAW  1

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
cr_configure()
{
    add_attack(75, 75, W_IMPALE, 25, A_BITE);
    add_attack(40, 40, W_SLASH,  75, A_CLAW);

    add_hitloc(({30, 30, 28}), 20, "head", H_HEAD);
    add_hitloc(({57, 57, 60}), 50, "body", H_BODY);
    add_hitloc(({42, 42, 45}), 30, "legs", H_LEGS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
        case A_BITE:return "bite";
        case A_CLAW:return "claws";
    }
}
