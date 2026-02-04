/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * bear.c
 *
 * Janus 920620
 * modified by Sorgum 941002
 * modified by Tomas for use with the Elderwood forest.  June 2000
 */

#include "/d/Terel/include/Terel.h"

inherit STDCREATURE;

inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";


#include "../include/creature_base.h"
#include <wa_types.h>
#include <ss_types.h>
#include <options.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

/*
 * Function name: create_creature
 * Description:   Create the creature.
 */
public void
create_creature()
{
    ::create_creature();
    set_name("momma");
    set_short("dark brown bear");
    set_long("This is a large female bear. She doesn't seem to " +
             "be in a good mood. Maybe because she is worried for her " +
             "children. Pity the poor soul who harms her children in any " +
             "way.\n");
    set_adj(({"brown","furry"}));
    set_race_name("bear");
    set_stats(({100, 75, 100, 50, 50, 100}));
    PASSIVE;
    set_random_move(random(50)+10);
    set_gender(FEMALE);
    set_skill(SS_CLIMB, random(25));
    set_skill(SS_DEFENCE, random(5) + 20);
    add_prop(OBJ_I_WEIGHT, 600000);
    add_prop(OBJ_I_VOLUME, 700000);
    add_prop(CONT_I_MAX_WEIGHT, 1000000);
    add_prop(CONT_I_MAX_VOLUME, 1000000);
    BRAVE;
    set_act_time(21);
    add_act(({"growl", "snarl", "sniff", "glare"}));
    SET_MAX_HP;
    ADDSKIN;
    ADDMEAT(5);
    BRAVE;
    trig_new("%s 'attacks' 'Bearcub.\n' %s","assist_baby");

}

string
assist_baby()
{
    TO->command("roar");
    TO->command("kill " + OB_NAME(TP));
    return "";
}



#define A_BITE  0
#define A_LPAW  1
#define A_RPAW  2
#define A_BHUG  3

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
cr_configure()
{
    add_attack(45, 40, W_SLASH,    25, A_BITE);
    add_attack(55, 50, W_BLUDGEON, 30, A_RPAW);
    add_attack(55, 50, W_BLUDGEON, 30, A_LPAW);
    add_attack(55, 60, W_BLUDGEON, 15, A_BHUG);

    add_hitloc( ({ 4, 5, 5 }), 15, "head", H_HEAD);
    add_hitloc( ({ 9, 9, 9 }), 60, "body", H_BODY);
    add_hitloc( ({ 9, 9, 9 }), 25, "legs", H_LEGS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid) {
     case A_BITE: return "bite";
     case A_RPAW: return "right front paw";
     case A_LPAW: return "left front paw";
     case A_BHUG: return "bearhug";
    }
}

