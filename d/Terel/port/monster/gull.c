/*
 * crab.c
 *
 * A crab. Mortricia Dec 1994
 */

#include "/d/Terel/include/Terel.h"
inherit STDCREATURE;
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/domove";

#include <wa_types.h>
#include <ss_types.h>
#include <money.h>

#define COLS ({"white", "grey", "yellow"})

/*
 * Function name: create_creature
 * Description:   Create the seagull.
 */
public void
create_creature()
{
    string adj;
    
    if (!IS_CLONE) return;

    ::create_creature();
    
    adj = COLS[random(sizeof(COLS))];
    
    set_name("seagull");
    set_long("It's a "+adj+" seagull. It is looking for some fish to eat.\n");
    set_adj(adj);
    set_race_name("seagull");
    set_stats(({13, 16, 12, 10, 10, 15}));
    SET_MAX_HP;
    set_alignment(random(40)-20);
    set_gender(NEUTER);
    set_whimpy(30);
    set_random_move(10);

    set_act_time(10);
    add_act("@@do_scream");

    set_skill(SS_DEFENCE, 12 + random(5));

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_WEIGHT,     1500);
    add_prop(CONT_I_VOLUME,     2000);
    add_prop(CONT_I_MAX_WEIGHT, 2500);
    add_prop(CONT_I_MAX_VOLUME, 2800);

    add_item(({"legs"}),   "The legs are yellow.\n");
    add_item(({"body"}),   "The body is covered with feathers.\n");
    add_item(({"eyes"}),   "The eyes seem to watch you.\n");
    add_item(({"beak"}), "The beak is slightly open.\n");
    
    MONEY_MAKE_SC(1+random(3))->move(TO, 1);
}

#define A_BITE  0
#define A_CLAW  1
#define A_WING  2

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
#define H_WING 3
#define H_CLAW 4

public void
cr_configure()
{
    add_attack(12, 10, W_IMPALE,    40, A_BITE);
    add_attack( 9,  5, W_SLASH,     30, A_CLAW);
    add_attack( 9,  5, W_BLUDGEON,  30, A_WING);

    add_hitloc( ({ 3, 2, 3 }), 10, "head",  H_HEAD);
    add_hitloc( ({10, 9, 9 }), 50, "body",  H_BODY);
    add_hitloc( ({ 6, 4, 7 }), 20, "legs",  H_LEGS);
    add_hitloc( ({ 9, 9, 7 }), 20, "wings", H_CLAW);
}

public string
cr_attack_desc(int aid)
{
    switch(aid) {
    case A_BITE:
        return "beak";
    case A_CLAW:
        return "feet";
    case A_WING:
        return "wing";
    }
}

do_scream()
{
    tell_room(ETO, "The " + short() + " screams.\n");
    return "";
}

