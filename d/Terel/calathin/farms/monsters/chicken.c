/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * chicken.c
 * Tomas  -- Nov. 1999
 *
 *  Modified: 1 Aug 2003, by Bleys
 *      - added CONT_I_WEIGHT and CONT_I_VOLUME, since the OBJ_I_WEIGHT
 *          and OBJ_I_VOLUME are obtained from std creature.
 *      - fixed typo in the add_acts
 *
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
    set_name(({"chicken"}));
    add_name("livestock");
    set_short("white chicken");
    set_long(" A small white chicken.\n");
    set_adj(({"small", "white"}));
    set_race_name("chicken");
    set_stats(({4, 8, 5, 3, 3, 3}));
    PASSIVE;
    SET_MAX_HP;
    BRAVE;
    set_act_time(20 + random(20)); 
    add_act(({"emote clucks.", "emote squawks!"}));
    set_gender(random(2));
    set_skill(SS_DEFENCE, random(25));
    set_restrain_path(CALATHIN_DIR);
    set_random_move(30);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 700);
    add_prop(LIVE_I_NO_CORPSE, 1);

    add_prop(CONT_I_WEIGHT, 500);
    add_prop(CONT_I_VOLUME, 500);


        
    ADDMEAT(1);
}


#define A_BITE  0

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
cr_configure()
{
    add_attack(3, 3, W_SLASH, 100, A_BITE);

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


public void
do_die(object killer)
{
     object corpse;

     if (query_hp() > 0)
     {
         return;
     }      
         FIX_EUID;
     corpse=clone_object(CALATHIN_DIR + "farms/obj/chicken_corpse");
     corpse->move(ETO);
     
     ::do_die(killer);
}
