/*
 * squid.c
 *
 * A small octopus. Mortricia Dec 1994
 */

#include "/d/Terel/include/Terel.h"
inherit STDCREATURE;
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>
#include <money.h>

#define COLS ({"black", "blue", "white", "grey"})

/*
 * Function name: create_creature
 * Description:   Create the squid.
 */
public void
create_creature()
{
    string adj;

    if (!IS_CLONE) return;

    ::create_creature();

    adj = COLS[random(sizeof(COLS))];

    set_name("squid");
    set_long("It's a small "+adj+" squid. It's an angry little rascal.\n");
    set_adj(adj);
    set_race_name("squid");
    set_stats(({14, 16, 18, 9, 9, 14}));
    SET_MAX_HP;
    set_alignment(random(40)-20);
    set_gender(NEUTER);
    set_whimpy(10);

    set_act_time(10);
    add_act("@@do_wave");

    set_skill(SS_DEFENCE, 12 + random(5));

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_WEIGHT,     1500);
    add_prop(CONT_I_VOLUME,     2000);
    add_prop(CONT_I_MAX_WEIGHT, 4000);
    add_prop(CONT_I_MAX_VOLUME, 2800);

    add_item(({"legs"}),  "It has eight legs.\n");
    add_item(({"eye"}),   "The eye is staring at you.\n");

    MONEY_MAKE_SC(1+random(2))->move(TO, 1);
}

#define A_BITE  0
#define A_STRA  1

#define H_HEAD 0
#define H_ARMS 1

public void
cr_configure()
{
    add_attack(  3, 10, W_IMPALE,    20, A_BITE);
    add_attack( 13, 10, W_BLUDGEON,  80, A_STRA);

    add_hitloc( ({ 7, 7,  9 }), 20, "head",  H_HEAD);
    add_hitloc( ({ 9, 9, 12 }), 80, "arms",  H_ARMS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid) {
    case A_BITE:
        return "mouth";
    case A_ARMS:
        return "arms";
    }
}

do_wave()
{
    tell_room(ETO, "The " + short() + " tries to grip you.\n");
    return "";
}

