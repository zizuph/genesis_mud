/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ferret.c
 *
 * Janus 920701
 * modified by Sorgum 941002
 * modified by Tomas for use with the Elderwood forest.   June 2000
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
    set_short("gray ferret");
    set_long("A small grey ferret. The long sleek body seems made for " +
             "hunting small rodents and birds. \n");
    set_adj(({"small", "gray"}));
    set_race_name("ferret");
    set_stats(({5, 4, 4, 3, 3, 10}));
    set_random_move(random(80) + 20);
    PASSIVE;
    set_act_time(11);
    add_act(({"snarl", "kill rodent", "kill hare", "get corpse"}));
    SET_MAX_HP;
    set_gender(random(1));
    set_skill(SS_CLIMB, random(25)+20);
    set_skill(SS_DEFENCE,random(5)+15);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 2400);
    set_whimpy(1);
    ADDSKIN;
    ADDMEAT(1);
}


#define A_BITE  0
#define A_LPAW  1
#define A_RPAW  2

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
#define H_TAIL 3

public void
cr_configure()
{
    add_attack(8, 3, W_SLASH,    70, A_BITE);
    add_attack(5, 2, W_BLUDGEON, 15, A_RPAW);
    add_attack(5,2,W_BLUDGEON,   15, A_LPAW);

    add_hitloc( ({ 1, 1, 1 }), 10, "head", H_HEAD);
    add_hitloc( ({ 2, 2, 2 }), 50, "body", H_BODY);
    add_hitloc( ({ 2, 2, 2 }), 20, "legs", H_LEGS);
    add_hitloc( ({ 2, 2, 2 }), 30, "tail", H_TAIL);
}

public string
cr_attack_desc(int aid)
{
    switch(aid) {
    case A_BITE: return "bite";
    case A_RPAW: return "right front paw";
    case A_LPAW: return "left front paw";
    }
}
