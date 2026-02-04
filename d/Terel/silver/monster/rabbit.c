/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * rabbit.c
 *
 * Janus 920692
 * modified by Sorgum 941002
 * modified by Tomas for use with the Elderwood Forest June 2000
 */

#include "/d/Terel/include/Terel.h"

inherit STDCREATURE;

inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

//#include "../include/creature_base.h"
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
    set_short("snow-white rabbit");
    set_long("the nervous looking snowy white rabbit forages for food. \n");
    set_adj(({"snow-white","snowy","white","small", "cute"}));
    set_race_name("rabbit");
    set_stats(({4, 8, 5, 3, 3, 3}));
    PASSIVE;
    SET_MAX_HP;
    BRAVE;
    set_act_time(15);
    add_act(({"sniff", "stare"}));
    set_gender(random(2));
    set_skill(SS_DEFENCE, random(25));
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, 3000);
    add_item("teeth", "Looking closer at the rabbit's teeth you see that\n"+
             "they look perfectly normal.\n");
    add_item(({"pelt","skin"}), "The pelt could be worth a few coppers " +
             "properly prepared.\n");
    ADDSKIN;
    ADDMEAT(1);
}


#define A_BITE  0

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
cr_configure()
{
    add_attack(3, 3, W_SLASH, 100, A_BITE);

    add_hitloc( ({ 1, 1, 1 }), 15, "head", H_HEAD);
    add_hitloc( ({ 1, 1, 1 }), 60, "body", H_BODY);
    add_hitloc( ({ 1, 1, 1 }), 25, "legs", H_LEGS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid) {
    case A_BITE: return "bite";
    }
}
