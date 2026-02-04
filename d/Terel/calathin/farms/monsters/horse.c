/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * horse.c
 * tomas -- nov. 1999
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
/*    set_name(({"horse"})); */
    set_short("draft workhorse");
    set_long("A large draft workhorse.\n");
    set_adj(({"draft","large"}));
    set_race_name("horse");
    set_stats(({75, 60, 40, 25, 20, 20}));
    PASSIVE;
    BRAVE;
    SET_MAX_HP;
    set_gender(random(1));
    set_act_time(21);
    add_act(({"emote snorts", "glare"}));
    set_skill(SS_DEFENCE, random(15));
    add_prop(OBJ_I_WEIGHT, 750000);
    add_prop(OBJ_I_VOLUME, 750000);
    add_prop(CONT_I_MAX_WEIGHT, 900000);
    add_prop(CONT_I_MAX_VOLUME, 900000);
    ADDSKIN;
    ADDMEAT(8);
}


#define A_BUTT  0
#define A_TRAM  1

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
cr_configure()
{
    add_attack(40, 50, W_IMPALE, 75, A_BUTT);
    add_attack(45, 45, W_BLUDGEON, 25, A_TRAM);

    add_hitloc( ({ 17, 17, 17 }), 35, "head", H_HEAD);
    add_hitloc( ({ 6, 6, 6 }), 45, "body", H_BODY);
    add_hitloc( ({ 6, 6, 6 }), 20, "legs", H_LEGS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid) {
    case A_BUTT: return "teeth";
    case A_TRAM: return "hooves";
    }
}
