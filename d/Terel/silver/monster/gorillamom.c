/* File         : /d/Terel/silver_new/monster/gorillamom.c
 * Creator      : Pasqua
 * Date         : April 2006         
 * Purpose      : Gorilla Mother
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

void gorilla_mom();
void momma_escape();
void silverback();

/*
 * Function name: create_creature
 * Description:   Create the creature.
 */


public void
create_creature()
{
    ::create_creature();
    set_name("gorillamom");
	add_name("gorilla");
    set_short("friendly motherly gorilla");
    set_long("This motherly gorilla seems to be the mother of the gorilla family. She looks " +
             "really friendly as she just enjoy the life within the forest, taking care of " +
             "the gorilla babies. She got a massive set of canine teeth and powerful " +
		     "jaw muscles to back them up and a bite would be painful.\n");
    set_adj(({"friendly","motherly"}));
    set_race_name("gorilla");
    set_stats(({100 + random(20), 100 + random(20), 100 + random(20), 70 + random(10), 70 + random(10), 110 + random(20)}));
    PASSIVE;
    set_gender(FEMALE);
    set_skill(SS_UNARM_COMBAT, 60 + random(20));
    set_skill(SS_DEFENCE, 70 + random(10));
    add_prop(OBJ_I_WEIGHT, 4000000);
    add_prop(OBJ_I_VOLUME, 5000000);
    add_prop(CONT_I_MAX_WEIGHT, 6000000);
    add_prop(CONT_I_MAX_VOLUME, 6000000);
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
    add_attack(45, 50, W_SLASH,    30, A_BITE);
    add_attack(40, 45, W_BLUDGEON, 35, A_RFIST);
    add_attack(40, 45, W_BLUDGEON, 35, A_LFIST);

    add_hitloc( ({ 25, 25, 25 }), 15, "head", H_HEAD);
    add_hitloc( ({ 25, 25, 25 }), 60, "body", H_BODY);
    add_hitloc( ({ 25, 25, 25 }), 25, "legs", H_LEGS);
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
	object silver;
    attacker->catch_tell("The silverback gorilla jumps down from the trees and attacks you!\n");
	silver = clone_object(MONSTER + "silver");
	silver->move(ENV(TO));
	silver->attack_object(attacker);
	set_alarm(1.0, 0.0, &momma_escape());
    ::attacked_by(attacker);
	attacker->stop_fight(this_object());
    this_object()->stop_fight(attacker);
}

else
{
    attacker->add_prop("silverback_warning", 1);
    set_alarm(1.0, 0.0, &gorilla_mom());

    attacker->stop_fight(this_object());
    this_object()->stop_fight(attacker);
}

}

void
gorilla_mom()
{
	tell_room(ENV(TO),"The motherly gorilla starts to scream and climb around in the trees " +
		              "in attempt to defend herself and call for aid.\n");
	set_alarm(2.0, 0.0, &silverback());
}

void
silverback()
{
	tell_room(ENV(TO),"An enormous silverback gorilla reveals himself up in the trees, he " +
		              "seem ready to defend the mortherly gorilla.\n");
}

void 
momma_escape()
{
	tell_room(ENV(TO),"The motherly gorilla escaped the battle and hides behind the silverback gorilla.\n"); 
	this_object()->add_prop(OBJ_M_NO_ATTACK, "It aint possible to attack her when she hides behind the silverback gorilla.\n");
}