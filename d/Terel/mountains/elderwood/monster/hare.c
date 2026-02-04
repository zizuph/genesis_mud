/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * hare.c
 *
 * Janus 920629
 * modified by Sorgum 941002
 * modified by Tomas for use with the Elderwood forest.  June 2000
 */

#include "/d/Terel/include/Terel.h"

inherit STDCREATURE;

inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include "../include/creature_base.h"
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
    set_pname("hares");
    set_short("snow-white hare");
    set_pshort("snow-white hares");
    set_long("A small snow-white hare. Properly prepared with " + 
             "the right spices it would taste great. \n");
    set_adj(({"small", "white", "snow-white"}));
    set_race_name("hare");
    set_alignment(random(20) + 5);
    set_stats(({4, 8, 5, 3, 3, 3}));
    PASSIVE;
    BRAVE;
    set_act_time(15);
    add_act(({"sniff", "stare"}));
    SET_MAX_HP;
    set_gender(random(2));
    set_skill(SS_DEFENCE, random(25));
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, 3000);
    set_whimpy(1);
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
    add_attack(4, 4, W_BLUDGEON, 100, A_BITE);

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
