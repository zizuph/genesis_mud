/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * bird.c
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
    set_name(({"bird"}));
    set_short("small white bird");
    set_long("The white colour of the bird makes it difficult to " + 
	     "see. It's searching for food on the cold icy ground.\n");
    set_adj(({"white"}));
    set_race_name("bird");
    set_alignment(20 - random(5));
    set_stats(({2, 5, 2, 2, 2, 2}));
    PASSIVE;
    BRAVE;
    set_act_time(31);
    add_act(({"stare"}));
    add_prop(OBJ_I_WEIGHT, 1000 + random(1000));
    add_prop(OBJ_I_VOLUME, 1000 + random(1000));
    SET_MAX_HP;
    set_gender(random(1));
    set_random_move(random(50) + 10);
    set_skill(SS_DEFENCE, random(5) + 5);
    ADDMEAT(1);
}


#define A_PECK   0
#define A_LFCLAW 1
#define A_RFCLAW 2
#define A_WING   3

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
#define H_WING 3

public void
cr_configure()
{
    add_attack(3, 2, W_IMPALE,   15, A_PECK);
    add_attack(1, 1, W_SLASH,    30, A_LFCLAW);
    add_attack(1, 1, W_SLASH,    30, A_RFCLAW);
    add_attack(2, 2, W_BLUDGEON, 25, A_WING);

    add_hitloc( ({ 2, 2, 2 }), 10, "head", H_HEAD);
    add_hitloc( ({ 1, 1, 1 }), 20, "body", H_BODY);
    add_hitloc( ({ 2, 2, 1 }), 25, "legs", H_LEGS);
    add_hitloc( ({ 2, 2, 1 }), 45, "wings", H_WING);
}

public string
cr_attack_desc(int aid)
{
    switch(aid) {
     case A_PECK:   return "beak";
     case A_LFCLAW: return "left claw";
     case A_RFCLAW: return "right claw";
     case A_WING:   return "wing bash";
    }
}

