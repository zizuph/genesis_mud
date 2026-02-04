/*
 * lobster.c
 *
 * A lobster. Mortricia Dec 1994
 */

#include "/d/Terel/include/Terel.h"
inherit STDCREATURE;
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include <money.h>

#define COLS ({"black", "dark-blue", "dark-red"})

/*
 * Function name: create_creature
 * Description:   Create the lobster.
 */
public void
create_creature()
{
    string adj;

    if (!IS_CLONE) return;

    ::create_creature();

    adj = COLS[random(sizeof(COLS))];

    set_name("lobster");
    set_long("It's a large "+adj+" lobster. It looks hostile and dangerous.\n");
    set_adj(adj);
    set_race_name("lobster");
    set_stats(({24, 27, 23, 20, 20, 25}));
    SET_MAX_HP;
    set_alignment(random(60)-30);
    set_gender(NEUTER);
    set_whimpy(10);
    set_aggressive(1);

    set_act_time(10);
    add_act("@@do_wave");

    set_skill(SS_DEFENCE, 22 + random(5));

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_WEIGHT,     3500);
    add_prop(CONT_I_VOLUME,     4000);
    add_prop(CONT_I_MAX_WEIGHT, 5000);
    add_prop(CONT_I_MAX_VOLUME, 5800);

    add_item(({"legs"}),   "There are six of them.\n");
    add_item(({"body"}),   "The body has thick scales.\n");
    add_item(({"claws"}),  "The claws look strong.\n");

    MONEY_MAKE_GC(1+random(2))->move(TO, 1);
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
    add_attack( 3, 10, W_IMPALE, 30, A_BITE);
    add_attack(13, 32, W_SLASH,  70, A_CLAW);

    add_hitloc( ({10,10,15 }), 10, "head",  H_HEAD);
    add_hitloc( ({25,25,16 }), 50, "body",  H_BODY);
    add_hitloc( ({10,10,15 }), 10, "legs",  H_LEGS);
    add_hitloc( ({30,30,23 }), 30, "claws", H_CLAW);
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

