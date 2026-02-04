/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * mbear.c
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
    set_name(({"bear", "mbear"}));
    set_short("dark brown bear");
    set_long("This is a large male bear. He appears to be " + 
	     "sleeping.  Better not wake him, those claws of his looks " + 
	     "awfully big.\n");
    set_adj(({"brown", "furry"}));
    set_race_name("bear");
    set_alignment(0);
    set_stats(({65, 25, 55, 4, 4, 80}));
    PASSIVE;
    BRAVE;
    SET_MAX_HP;
    set_gender(MALE);
    set_skill(SS_CLIMB, random(25));
    set_act_time(21);
    add_act(({"snore", "growl", "snarl", "yawn"}));
    set_skill(SS_DEFENCE, random(15) + 20);
    add_prop(OBJ_I_WEIGHT, 1200000);
    add_prop(OBJ_I_VOLUME, 1200000);
    add_prop(CONT_I_MAX_WEIGHT, 1400000);
    add_prop(CONT_I_MAX_VOLUME, 1400000);
    ADDSKIN;
    ADDMEAT(5);
}


#define A_BITE  0
#define A_LPAW  1
#define A_RPAW  2
#define A_BHUG  3

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
cr_configure()
{
    add_attack(45, 45, W_SLASH,    25, A_BITE);
    add_attack(55, 65, W_BLUDGEON, 30, A_RPAW);
    add_attack(55, 65, W_BLUDGEON, 30, A_LPAW);
    add_attack(50, 80, W_BLUDGEON, 15, A_BHUG);

    add_hitloc( ({ 7, 7, 7 }), 15, "head", H_HEAD);
    add_hitloc( ({ 10, 10, 10 }), 60, "body", H_BODY);
    add_hitloc( ({ 10, 10, 10 }), 25, "legs", H_LEGS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid) {
    case A_BITE: return "bite";
    case A_RPAW: return "right front paw";
    case A_LPAW: return "left front paw";
    case A_BHUG: return "bearhug";
    }
}

