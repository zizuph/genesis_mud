/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * wolf.c
 *
 * A bat. Mortricia 920917
 * Modified by Sorgum 941029
 * Modified by Mortricia 960406
 */

#include "/d/Terel/include/Terel.h"
inherit STDCREATURE;
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/domove";

#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>

#define MAX_TEETH   3
#define NO_OF_SIZES 1
#define ADJS        ({"huge"})
#define TOOTH       (LOD_DIR + "obj/tooth")
#define SKIN        (LOD_DIR + "obj/wolf_skin")

static int size = random(NO_OF_SIZES);
static int ntooth = MAX_TEETH;

public void
create_creature()
{
    ::create_creature();
    
    set_name("wolf");
    set_long("It is a huge black wolf. It looks very hungry. It has been " +
             "kept in the dungeons below the quarters of the Legion " +
             "of Darkness since the time before the Legion took hold of " +
             "of the place. No one has " +
             "dared to release it. It is a wonder it is still alive.\n");
    set_adj(({ADJS[size], "black"}));
    set_race_name("wolf");
    set_stats(({128+size*8, 120+size*9, 120+size*8,
                 99+size*4,  99+size*4, 110+size*8}));
    SET_MAX_HP;
    set_alignment(0);
    set_gender(0);

    set_act_time(3);
    set_cact_time(3);
    add_act("@@wolf_act");
    add_cact("@@wolf_act");

    set_skill(SS_DEFENCE, 85 + size*8 + random(5));
    set_skill(SS_UNARM_COMBAT, 85 + size*8 + random(5));
    set_skill(SS_AWARENESS, 90 + random(5));

    add_prop(LIVE_I_NEVERKNOWN,    1);
    add_prop(LIVE_I_SEE_DARK,      1);
    add_prop(CONT_I_WEIGHT,     25000 + size*2000);
    add_prop(CONT_I_VOLUME,     24000 + size*1000);
    add_prop(CONT_I_MAX_WEIGHT, 32600 + size*2000);
    add_prop(CONT_I_MAX_VOLUME, 30000 + size*1000);

    add_item(({"fur"}), "It looks very shabby.\n");
    add_item(({"teeth"}), "The teeth are enormous and very sharp.\n");
    add_item(({"eyes"}), "They are yellowish.\n");
    
    set_random_move(11, 1);
    set_m_out("runs");
}

public void
lose_tooth()
{
    if (ntooth <= 0) return;
    
    seteuid(getuid());
    clone_object(TOOTH)->move(ETO);
    tell_room(ETO, QCTNAME(TO) + " lost a tooth!\n", TO);
    ntooth--;
}

public string
wolf_act()
{
    object *all, ob=0;
    int i;
    
    if (query_attack()) return "growl madly";
    
    all = all_inventory(ETO) - ({ TO });
    for (i=0; i<sizeof(all); i++) {
        if (!living(all[i])) continue;
        if (!CAN_SEE(TO, all[i])) continue;
        if (all[i]->query_prop(LIVE_I_UNDEAD)) continue;
        if (all[i]->query_race_name() == query_race_name()) continue;
        if (all[i]->query_race_name() == "bat") continue;
        if (all[i]->query_race_name() == "dog") continue;
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
        return "emote stares coldly at you with its yellowish eyes.";
    } else if (i == 1) {
        return "emote growls silently at you.";
    } else {
        return "emote stares intently at you.";
    }
}

public int
special_attack(object victim)
{
    object necklace, collar;
    int dam;
    
    if (random(7) != 0) return 0;
    
    necklace = present("zasultra_necklace", victim);
    collar = present("collar", victim);
    if (necklace) {
        victim->catch_msg(QCTNAME(TO) + " jumps up on you and bites you " +
                      "in your throat!  Luckily, the " +
                      necklace->short() + " seems to take most of the blow.\n");
        dam = 5;
        set_alarm(1.0, 1.0, lose_tooth);
    } else if (collar && collar->query_worn() == victim) {
        victim->catch_msg(QCTNAME(TO) + " jumps up on you and bites you " +
                      "in your throat!  Luckily, the " +
                      collar->short() + " seems to take some of the blow.\n");
        dam = 20;
        if (!random(3))
            set_alarm(1.0, 1.0, lose_tooth);
    } else {
        victim->catch_msg(QCTNAME(TO) + " jumps up on you and bites you " +
                      "in your throat!\n");
        dam = 200;
    }
    tell_room(ETO, QCTNAME(TO) + " jumps up on " + QTNAME(victim) +
              " and bites " + victim->query_objective() + " in " +
              victim->query_possessive() + " throat.\n", victim);
    
    victim->reduce_hit_point(dam + random(dam));
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
    add_attack(75+size*7, 75+size*7, W_IMPALE, 75, A_BITE);
    add_attack(50+size*5, 50+size*5, W_SLASH,  25, A_CLAW);

    add_hitloc(({40+size*5, 40+size*5, 38+size*5 }), 20, "head", H_HEAD);
    add_hitloc(({57+size*5, 57+size*5, 60+size*5 }), 50, "body", H_BODY);
    add_hitloc(({42+size*5, 42+size*5, 45+size*5 }), 30, "legs", H_LEGS);
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

public void
do_die(object killer)
{
    if (query_hp() > 0)
        return;
        
    seteuid(getuid());
    clone_object(SKIN)->move(TO);
    
    ::do_die(killer);
}
