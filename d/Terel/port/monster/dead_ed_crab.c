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

#define COLS ({"black", "blue", "white", "grey", "brown"})

/*
 * Function name: create_creature
 * Description:   Create the crab.
 */
public void
create_creature()
{
    string adj;
    
    if (!IS_CLONE) return;

    ::create_creature();
    
    adj = COLS[random(sizeof(COLS))];
    
    set_name("crab");
    set_long("It's a small "+adj+" crab. It's a quick little rascal.\n");
    set_adj(adj);
    set_race_name("crab");
    set_stats(({9, 12, 8, 5, 5, 10}));
    SET_MAX_HP;
    set_alignment(random(40)-20);
    set_gender(NEUTER);
    set_whimpy(30);
    set_random_move(20);

    set_act_time(10);
    add_act("@@do_wave");

    set_skill(SS_DEFENCE, 7 + random(5));

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_WEIGHT,      500);
    add_prop(CONT_I_VOLUME,     1000);
    add_prop(CONT_I_MAX_WEIGHT, 2000);
    add_prop(CONT_I_MAX_VOLUME, 1800);

    add_item(({"legs"}),  "The legs are hairy.\n");
    add_item(({"body"}),  "The body is hairy.\n");
    add_item(({"eyes"}),  "The eyes seem to watch you.\n");
    
    MONEY_MAKE_CC(1+random(5))->move(TO, 1);
}

#define A_BITE  0
#define A_CLAW  1

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
#define H_CLAW 3

public void
cr_configure()
{
    add_attack( 3,  5, W_IMPALE, 70, A_BITE);
    add_attack( 3, 10, W_SLASH,  30, A_CLAW);

    add_hitloc( ({ 1, 1, 3 }), 10, "head",  H_HEAD);
    add_hitloc( ({ 9, 9, 9 }), 50, "body",  H_BODY);
    add_hitloc( ({ 4, 4, 7 }), 20, "legs",  H_LEGS);
    add_hitloc( ({ 9, 9, 7 }), 20, "claws", H_CLAW);
}

public string
cr_attack_desc(int aid)
{
    switch(aid) {
    case A_BITE:
        return "mouth";
    case A_CLAW:
        return "claws";
    }
}

do_wave()
{
    tell_room(ETO, "The " + short() + " waves with its claws.\n");
    return "";
}

