/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * rodent.c
 *
 * Janus 920621
 * modified by Sorgum 941002
 */

#include "/d/Terel/include/Terel.h"

inherit STDCREATURE;

inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include "../local.h"
#include <wa_types.h>
#include <ss_types.h>

/*
 * Function name: create_creature
 * Description:   Create the creature.
 */
public void
create_creature()
{
    ::create_creature();
    set_name(({"rodent"}));
    set_short("small furry rodent");
    set_long("A small brown rodent is running around scurrying for food. \n");
    set_adj(({"small", "furry"}));
    set_race_name("rodent");
    set_alignment(0);
    set_stats(({1, 5, 2, 2, 2, 4}));
    PASSIVE;
    SET_MAX_HP;
    set_act_time(20);
    add_act(({"stare", "sniff"}));
    set_gender(random(2));
    set_skill(SS_DEFENCE, random(5) + 5);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 500);
    set_whimpy(1);
}

#define A_BITE   0
#define A_LFCLAW 1
#define A_RFCLAW 2

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
#define H_TAIL 3

public void
cr_configure()
{
    add_attack(2, 1, W_SLASH, 40, A_BITE);
    add_attack(1, 1, W_SLASH, 30, A_LFCLAW);
    add_attack(1, 1, W_SLASH, 30, A_RFCLAW);

    add_hitloc( ({ 2, 2, 2 }), 10, "head", H_HEAD);
    add_hitloc( ({ 1, 1, 1 }), 40, "body", H_BODY);
    add_hitloc( ({ 2, 2, 1 }), 25, "legs", H_LEGS);
    add_hitloc( ({ 3, 3, 3 }), 25, "tail", H_TAIL);
}

public string
cr_attack_desc(int aid)
{
    switch(aid) {
    case A_BITE  : return "bite";
    case A_LFCLAW: return "left paw";
    case A_RFCLAW: return "right paw";
    }
}
