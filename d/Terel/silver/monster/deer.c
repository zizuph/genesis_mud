/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * deer.c
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
    set_short("brown spotted deer");
    set_long("The brown spotted deer looks nervously at you.\n"); 
    set_adj(({"spotted","brown","large"}));
    set_race_name("deer");
    set_stats(({40, 30, 30, 4, 4, 30}));
    PASSIVE;
    BRAVE;
    SET_MAX_HP;
    set_gender(random(2));
    set_act_time(21);
    add_act(({"sniff"}));
    set_skill(SS_DEFENCE, random(15));
    add_prop(OBJ_I_WEIGHT, 600000);
    add_prop(OBJ_I_VOLUME, 600000);
    add_prop(CONT_I_MAX_WEIGHT, 700000);
    add_prop(CONT_I_MAX_VOLUME, 700000);
    ADDSKIN;
    ADDMEAT(4);
}


#define A_BUTT  0
#define A_TRAM  1

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
cr_configure()
{
    add_attack(40, 40, W_BLUDGEON, 75, A_BUTT);
    add_attack(35, 35, W_BLUDGEON, 25, A_TRAM);

    add_hitloc( ({ 7, 7, 7 }), 35, "head", H_HEAD);
    add_hitloc( ({ 6, 6, 6 }), 45, "body", H_BODY);
    add_hitloc( ({ 6, 6, 6 }), 20, "legs", H_LEGS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid) {
    case A_BUTT: return "head butt";
    case A_TRAM: return "trample";
    }
}
