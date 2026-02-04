/* File         : /d/Terel/silver_new/monster/gorillababy.c
 * Creator      : Pasqua
 * Date         : April 2006         
 * Purpose      : Gorilla Baby
 * Related Files: 
 * Comments     : 
 * Modifications: 
 */

#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"

inherit STDCREATURE;

inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/attack";

//#include "../include/creature_base.h"
#include <wa_types.h>
#include <ss_types.h>
#include <options.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>  

/*
 * Function name: create_creature
 * Description:   Create the creature.
 */
public void
create_creature()
{
    ::create_creature();
    set_name("gorillababy");
	add_name("gorilla");
    set_short("young baby gorilla");
    set_long("This young gorilla look so innocent and friendly, but the canine teeth's on this " +
             "baby is allready growing and seems to be quite sharp allready.\n");
    set_adj(({"young","baby"}));
    set_race_name("gorilla");
    set_stats(({40 + random(20), 40 + random(20), 40 + random(20), 20 + random(10), 20 + random(10), 40 + random(20)}));
    PASSIVE;
    set_gender(MALE);
    set_skill(SS_UNARM_COMBAT, 40 + random(20));
    set_skill(SS_DEFENCE, 40 + random(10));
    add_prop(OBJ_I_WEIGHT, 1500000);
    add_prop(OBJ_I_VOLUME, 1900000);
    add_prop(CONT_I_MAX_WEIGHT, 2500000);
    add_prop(CONT_I_MAX_VOLUME, 2700000);
    BRAVE;
    SET_MAX_HP;
}




#define A_BITE  0
#define A_LFIST 1
#define A_RFIST  2

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
cr_configure()
{
    add_attack(30, 35, W_SLASH,    30, A_BITE);
    add_attack(25, 30, W_BLUDGEON, 35, A_RFIST);
    add_attack(25, 30, W_BLUDGEON, 35, A_LFIST);

    add_hitloc( ({ 10, 10, 10 }), 15, "head", H_HEAD);
    add_hitloc( ({ 10, 10, 10 }), 60, "body", H_BODY);
    add_hitloc( ({ 10, 10, 10 }), 25, "legs", H_LEGS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid) {
     case A_BITE: return "canine bite";
     case A_RFIST: return "right fist";
     case A_LFIST: return "left fist";
    }
}

public void attacked_by(object attacker)
{
if(attacker->query_prop("silverback_warning"))
{
bring_daddy();
::attacked_by(attacker);
}
else
{
attacker->add_prop("silverback_warning");
stop_fight();
}

