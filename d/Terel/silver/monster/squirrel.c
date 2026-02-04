/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * squirrel.c
 *
 * Janus 920621
 * modified by Sorgum 941002
 * modified for use with the Elderwood Forest. Tomas  -- June 2000
 */

#include "/d/Terel/include/Terel.h"

inherit STDCREATURE;

inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

// #include "../include/creature_base.h"
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
    set_short("small squirrel");
    set_long("A small red squirrel, leaping from branch to branch " +
             "searching for edibles.\n");
    set_adj(({"small","red"}));
    set_race_name("squirrel");
    set_stats(({20, 10, 3, 1, 1, 5}));
    PASSIVE;
    SET_MAX_HP;
    set_act_time(11);
    add_act(({"sniff", "stare", "flip"}));
    set_gender(random(2));
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 2000);
    set_skill(SS_CLIMB, random(25) + 50);
    set_skill(SS_DEFENCE, random(10) + 5);
    set_whimpy(1);
    ADDSKIN;
    ADDMEAT(1);
}


#define A_BITE  0

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
#define H_TAIL 3

public void
cr_configure()
{
    add_attack(5,1,W_IMPALE,100,A_BITE);

    add_hitloc( ({ 2, 2, 2 }), 5, "head", H_HEAD);
    add_hitloc( ({ 1, 1, 1 }), 60, "body", H_BODY);
    add_hitloc( ({ 2, 2, 4 }), 35, "tail", H_TAIL);
}

public string
cr_attack_desc(int aid)
{
    switch(aid) {
    case A_BITE: return "bite";
    }
}


