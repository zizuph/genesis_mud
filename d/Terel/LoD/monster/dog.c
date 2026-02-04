/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * dog.c
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
#define ADJS        ({"starving", "hungry", "huge"})

static int size = random(NO_OF_SIZES);

public void
create_creature()
{
    ::create_creature();
    
    set_name("dog");
    set_long("It is a shabby dog. It looks quite hungry, the legion troops" +
             " probably don't feed it too often. The teeth are big and sharp " +
             "and its fur looks very dirty.\n");
    set_adj(({"shabby", ADJS[size]}));
    set_race_name("dog");
    set_stats(({18+size*8, 20+size*9, 20+size*8,
                 9+size*4,  9+size*4, 10+size*8}));
    SET_MAX_HP;
    set_alignment(-60 - 10*size);
    set_gender(random(3));

    set_act_time(3);
    set_cact_time(3);
    add_act("@@dog_act");
    add_cact("@@dog_act");

    set_skill(SS_DEFENCE, 15 + size*8 + random(5));
    set_skill(SS_UNARM_COMBAT, 15 + size*8 + random(5));

    add_prop(LIVE_I_NEVERKNOWN,    1);
    add_prop(LIVE_I_SEE_DARK,      1);
    add_prop(CONT_I_WEIGHT,     5000 + size*2000);
    add_prop(CONT_I_VOLUME,     4000 + size*1000);
    add_prop(CONT_I_MAX_WEIGHT, 6600 + size*2000);
    add_prop(CONT_I_MAX_VOLUME, 5000 + size*1000);

    add_item(({"fur"}), "It looks shabby.\n");
    add_item(({"teeth"}), "The teeth are sharp.\n");
    
    set_random_move(11);
    set_m_out("runs");
}

public string
dog_act()
{
    object *all, ob=0;
    int i;
    
    if (query_attack()) return "growl madly";
    
    all = all_inventory(ETO);
    for (i=0; i<sizeof(all); i++) {
        if (!living(all[i])) continue;
        if (all[i]->query_prop(LIVE_I_UNDEAD)) continue;
        if (all[i]->query_race_name() == query_race_name()) continue;
        if (all[i]->query_race_name() == "bat") continue;
/* Attack only the weak or badly hurt players or NPC's */
        if (all[i]->query_hp() < query_hp()) {
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
        return ("growl madly at " + ob->query_real_name());
    }
    
    i = random(3);
    if (i == 0) {
        return "emote runs around looking for food.";
    } else if (i == 1) {
        return "emote scratches itself.";
    } else {
        return "emote looks at you with a somewhat mad look in its eyes.";
    }
}

public int
special_attack(object victim)
{
    if (random(5) != 0) return 0;
    
    victim->catch_msg(QCTNAME(TO) + " jumps up on you and bites you " +
                      "in your throat!\n");
    tell_room(ETO, QCTNAME(TO) + " jumps up on " + QTNAME(victim) +
              " and bites " + victim->query_objective() + " in " +
              victim->query_possessive() + " throat.\n", victim);
    
    victim->reduce_hit_point(17 + 5*size + random(10 + 5*size));
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
        tell_room(ETO, QCTNAME(TO) + " backs off to avoid attacks.\n", TO);
        return 0;
    }
    return 1;
}

#define A_BITE  0
#define A_CLAW  1

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
cr_configure()
{
    add_attack(15+size*7, 15+size*7, W_IMPALE, 75, A_BITE);
    add_attack(10+size*5, 10+size*5, W_SLASH,  25, A_CLAW);

    add_hitloc( ({10+size*5, 10+size*5,  8+size*5 }), 20, "head", H_HEAD);
    add_hitloc( ({17+size*5, 17+size*5, 20+size*5 }), 50, "body", H_BODY);
    add_hitloc( ({12+size*5, 12+size*5, 15+size*5 }), 30, "legs", H_LEGS);
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
