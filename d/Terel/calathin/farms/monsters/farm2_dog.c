/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * farm2_dog.c
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

#define ARM_DIR CALATHIN_DIR + "farms/armour/"

/*
 * Function name: query_object_list
 * Description:   return list of equipment
 */
public string*
query_object_list()
{
    return ({
            ARM_DIR + "collar"
                });
}


/*
 * Function name: create_creature
 * Description:   Create the creature.
 */
public void
create_creature()
{
    ::create_creature();
/*    set_name(({"dog"})); */
    set_short("long-eared dog");
    set_long("A long-eared dog. He looks excited to have visitors.\n");
    add_name("livestock");
    set_adj(({"long-eared","excited"}));
    set_race_name("dog");
    set_stats(({20, 75, 20, 15, 15, 20}));
    PASSIVE;
    BRAVE;
    SET_MAX_HP;
    set_gender(1);
    set_act_time(100 + random(100)); 
    add_act(({"emote scratches at a flea.", "emote barks happily!"}));
    set_skill(SS_DEFENCE, random(15));
    add_prop(OBJ_I_WEIGHT, 37000);
    add_prop(OBJ_I_VOLUME, 57000);
    add_prop(CONT_I_MAX_WEIGHT, 50000);
    add_prop(CONT_I_MAX_VOLUME, 80000);
    ADDSKIN;
    ADDMEAT(4);
}


#define A_BITE  0

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
cr_configure()
{
    add_attack(25, 25, W_IMPALE, 25, A_BITE);


    add_hitloc( ({ 17, 17, 17 }), 35, "head", H_HEAD);
    add_hitloc( ({ 6, 6, 6 }), 45, "body", H_BODY);
    add_hitloc( ({ 6, 6, 6 }), 20, "legs", H_LEGS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid) {
    case A_BITE: return "teeth";
    }
}


/*
 * Function name: equip_actions
 * Description:   Initial commands (e.g. wield sword)
 */
public void
equip_actions()
{
    TO->command("wear collar");
}
