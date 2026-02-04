/* This comment tells emacs to use c++-mode  -*- C++ -*- */

#include "/d/Terel/include/Terel.h"

inherit STDCREATURE;

#define ARM_DIR  ORC_CAVE_DIR + "armour/"

inherit "/std/combat/unarmed";

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <formulas.h>
#include <wa_types.h>
#include <ss_types.h>

#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1

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
    set_name(({"wolf", "animal"}));
    set_short("enormous grey wolf");
    set_pshort("enormous grey wolves");
    set_long("An enormous grey vicious-looking wolf, with a gold-collar " +
	     "around its neck.  It was probably left here to guard the " +
	     "place.\n");
    set_adj(({"enormous", "grey", "vicious"}));
    set_race_name("wolf");
    set_alignment(-40 - random(20));

    set_stats(({random(30)+50,random(30)+60, 70, 10, 13, 80}));

    set_attack_unarmed(A_BITE,  30, 30, W_IMPALE, 40, "jaws");
    set_attack_unarmed(A_LCLAW, 30, 30, W_SLASH,  30, "left claw");
    set_attack_unarmed(A_RCLAW, 30, 30, W_IMPALE, 30, "right claw");

    set_hitloc_unarmed(H_HEAD, ({ -15, -25, -20, -20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({  10,  15,  30,  20 }), 80, "body");

    AGGRESSIVE;
    SET_MAX_HP;
    set_gender(NEUTER);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_DEFENCE, 40);
    BRAVE;
    add_prop(LIVE_I_SEE_INVIS,10);
    add_prop(LIVE_I_SEE_DARK,10);

    set_act_time(20);
    add_act("growl");
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

int
special_attack(object enemy)
{
    mixed* hitresult;
    string how;
    object me;
    int hurt, intox;
    intox = enemy->query_intoxicated();
    me = TO;
    
    if(random(10) < 4) {

	hurt = F_PENMOD(30 + intox/4, 30 + intox/4);
	
	hitresult = enemy->hit_me(hurt, W_IMPALE, me, -1);

	how = "unharmed";
	if (hitresult[0] > 0)
	    how = "slightly hurt";
	if (hitresult[0] > 20)
	    how = "rather hurt";
	if (hitresult[0] > 50)
	    how = "crushed";
	if (hitresult[0] > 100)
	    how = "devastated";
	    
        tell_watcher(QCTNAME(me) + " mauls " + QTNAME(enemy) + ".\n", enemy); 
	enemy->catch_msg(QCTNAME(me) + " mauls you!\n");
	enemy->catch_msg("You feel " + how + ".\n");
	
	return 1;
    }

    return 0;
}

