/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * bigwolf.c
 *
 * This white wolf is larger than the grey wolves and gets a special
 * attack.
 */

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
 * Function name: create_creature
 * Description:   Create the creature.
 */
public void
create_creature()
{
    ::create_creature();
    set_name(({"wolf", "animal"}));
    set_short("enormous white wolf");
    set_pshort("enormous white wolves");
    set_long("An enormous white vicious-looking wolf, with a platinum " +
	     "collar around its neck.  It was probably left here to " +
	     "guard the place.\n");
    set_adj(({"enormous", "white", "vicious"}));
    set_race_name("wolf");
    set_alignment(-80 - random(20));

    set_stats(({random(30)+70, random(12)+100, 140, 30, 33, 90}));

    set_attack_unarmed(A_BITE,  15, 12, W_IMPALE, 40, "jaws");
    set_attack_unarmed(A_LCLAW, 20, 10, W_SLASH,  30, "left claw");
    set_attack_unarmed(A_RCLAW, 20, 10, W_IMPALE, 30, "right claw");

    set_hitloc_unarmed(H_HEAD, ({ -15, -25, -20, -20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({  10,  15,  30,  20 }), 80, "body");

    AGGRESSIVE;
    SET_MAX_HP;
    set_gender(NEUTER);
    set_skill(SS_UNARM_COMBAT, 90);
    set_skill(SS_DEFENCE, 80);
    BRAVE;
    add_prop(LIVE_I_SEE_DARK,10);
    add_prop(LIVE_I_SEE_INVIS,10);

    set_act_time(20);
    add_act("emote growls ferociously.");
    add_act("emote bares its teeth at you.");
}

/*
 * Function name: query_object_list
 * Description:   return list of equipment
 */
public string*
query_object_list()
{
    return ({
            ARM_DIR + "pcollar"
		});
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
    int hurt;
    int fire_resist;

    me = TO;
    
    if(random(10) < 4) {

	hurt = F_PENMOD(100, 100 + random(100));
	
	hitresult = enemy->hit_me(hurt, MAGIC_DT, me, -1);

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
