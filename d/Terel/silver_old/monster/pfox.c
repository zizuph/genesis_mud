/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * pfox.c
 *
 * Janus 920701
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
    if (!IS_CLONE)
	return;

    ::create_creature();
    set_name(({"fox", "pfox"}));
    set_short("red fox");
    set_long("The reddish gray pelt makes it difficult for the fox " +
	     "blend in with the surroundings.  Properly prepared the pelt " + 
	     "could be worth quite a lot.\n");
    set_adj(({"red"}));
    set_race_name("fox");
    set_alignment(0);
    set_stats(({9, 10, 9, 5, 5, 15}));
    PASSIVE;
    set_act_time(11);
    add_act(({"growl", "kill rodent", "get corpse"}));
    SET_MAX_HP;
    set_gender(random(2));
    set_skill(SS_DEFENCE, random(5) + 25);
    add_prop(OBJ_I_WEIGHT, 22000);
    add_prop(OBJ_I_VOLUME, 22400);
    BRAVE;
    ADDSKIN;
    ADDMEAT(2);
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
    add_attack(10, 5, W_SLASH,    70, A_BITE);
    add_attack(6,  3, W_BLUDGEON, 15, A_RPAW);
    add_attack(6,  3, W_BLUDGEON, 15, A_LPAW);

    add_hitloc( ({ 1, 1, 1 }), 10, "head", H_HEAD);
    add_hitloc( ({ 2, 2, 2 }), 50, "body", H_BODY);
    add_hitloc( ({ 2, 2, 2 }), 20, "legs", H_LEGS);
    add_hitloc( ({ 6, 6, 6 }), 30, "tail", H_TAIL);
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
