/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * badger.c
 *
 * A savage badger. Mortricia 920917 
 * modified by Sorgum 941226
 */

#include "/d/Terel/include/Terel.h"

inherit STDCREATURE;

inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/domove";
inherit "/std/act/seqaction";

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
    set_name("badger");
    set_short("savage badger");
    set_long("It's a savage badger. Don't disturb it because it " +
	     "can bite you with its teeth or give you a stroke " +
	     "with its claws.\n");
    set_adj("savage");
    set_race_name("badger");
    set_stats(({20, 20, 20, 2, 2, 2}));
    SET_MAX_HP;
    set_alignment(-20);
    set_gender(NEUTER);
    set_whimpy(20);
    set_random_move(10);

    set_skill(SS_DEFENCE, 10 + random(5));

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_QUICKNESS,  100);
    
    add_prop(OBJ_I_WEIGHT, 15000);
    add_prop(OBJ_I_VOLUME,  9000);
    
    add_prop(CONT_I_MAX_WEIGHT, 23000);
    add_prop(CONT_I_WEIGHT,     15000);
    add_prop(CONT_I_MAX_VOLUME, 15000);
    add_prop(CONT_I_VOLUME,     9000);

    add_item(({"teeth"}), "The teeth are sharp.\n");
    add_item(({"claws"}), "The claws are sharp.\n");
    ADDSKIN;
    ADDMEAT(2);
}


#define A_BITE  0
#define A_CLAW  1

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
cr_configure()
{
    add_attack(10, 10, W_IMPALE, 25, A_BITE);
    add_attack(20, 20, W_SLASH,  75, A_CLAW);

    add_hitloc( ({ 5, 5, 5 }), 15, "head", H_HEAD);
    add_hitloc( ({ 9, 9, 9 }), 50, "body", H_BODY);
    add_hitloc( ({ 7, 7, 7 }), 35, "legs", H_LEGS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
     case A_BITE:return "teeth";
     case A_CLAW:return "claws";
    }
}
