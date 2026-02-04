/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cow.c
 *
 * Tomas  -- Nov. 1999
 */

#include "/d/Terel/include/Terel.h"

inherit STDCREATURE;

inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";
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
/*    set_name(({"cow"})); */
    set_short("black and white cow");
    set_long("From the color and the large utter beneath the cow you " +
       "note that this is a milking cow.\n");
    set_adj(({"black","white","milk"}));
    set_race_name("cow");
    set_stats(({40, 15, 25, 4, 4, 20}));
    PASSIVE;
    BRAVE;
    SET_MAX_HP;
    set_gender(1);
    set_act_time(21);
    add_act(({"stare", "emote goes moo!","emote swats flies with her tail."}));
    set_skill(SS_DEFENCE, random(15));
    add_prop(OBJ_I_WEIGHT, 500000);
    add_prop(OBJ_I_VOLUME, 500000);
    add_prop(CONT_I_MAX_WEIGHT, 700000);
    add_prop(CONT_I_MAX_VOLUME, 700000);
    ADDSKIN;
    ADDMEAT(6);
}


#define A_BUTT  0
#define A_TRAM  1

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
cr_configure()
{
    add_attack(20, 25, W_BLUDGEON, 45, A_BUTT);
    add_attack(20, 20, W_BLUDGEON, 25, A_TRAM);

    add_hitloc( ({ 17, 17, 17 }), 35, "head", H_HEAD);
    add_hitloc( ({ 6, 6, 6 }), 45, "body", H_BODY);
    add_hitloc( ({ 6, 6, 6 }), 20, "legs", H_LEGS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid) {
    case A_BUTT: return "flank";
    case A_TRAM: return "hooves";
    }
}
