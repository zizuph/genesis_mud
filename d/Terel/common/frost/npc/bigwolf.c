/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * bigwolf.c
 *
 * This white wolf is larger than the grey wolves and gets a special
 * attack.
 * 
 * Modifications by Petros, May 2009
 *  - Uses W_IMPALE instead of MAGIC_DT for special attack
 *  - Uses A_BITE instead of -1 for attack id.
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

static object my_boss;
static object *my_foes;

void help_the_boss(object boss);
void attack_someone();

/*
 * Function name: create_creature
 * Description:   Create the creature.
 */
public void
create_creature()
{
    ::create_creature();
    set_name(({"wolf", "animal", "g_wolf"}));
    set_short("enormous white wolf");
    set_pshort("enormous white wolves");
    set_long("An enormous white vicious-looking wolf, with a platinum " +
	     "collar around its neck.  It was probably left here to " +
	     "guard the place.\n");
    set_adj(({"enormous", "white", "vicious"}));
    set_race_name("wolf");
    set_alignment(-80 - random(20));
    set_aggressive(1);
    set_stats (({100, 100, 100, 100, 100, 180}));


    add_prop(LIVE_I_SEE_INVIS, 10);
    add_prop(LIVE_I_SEE_DARK, 10);

    set_attack_unarmed(A_BITE,  15, 12, W_IMPALE, 30, "jaws");
    set_attack_unarmed(A_LCLAW, 20, 10, W_SLASH,  20, "left claw");
    set_attack_unarmed(A_RCLAW, 20, 10, W_IMPALE, 20, "right claw");

    set_hitloc_unarmed(H_HEAD, ({ -15, -25, -20, -20 }), 30, "head");
    set_hitloc_unarmed(H_BODY, ({  10,  15,  30,  20 }), 20, "body");

    SET_MAX_HP;
    set_gender(NEUTER);
    set_skill(SS_UNARM_COMBAT, 90);
    set_skill(SS_DEFENCE, 80);
    add_prop (NPC_I_NO_FEAR, 1);
    add_prop (NPC_I_NO_RUN_AWAY, 1);


    set_act_time(20);
    add_act("emote growls ferociously.");
    add_act("emote bears its teeth at you.");
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

	hurt = F_PENMOD(40, 20 + random(50));
	
	hitresult = enemy->hit_me(hurt, W_IMPALE, me, A_BITE);

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

void
help_the_boss(object boss)
{
    if (!boss) return;
    my_boss = boss;
    my_foes = my_boss->query_my_enemies();
}

void
attack_someone()
{
    int i, found_foe = 0;
    object foe;

    if (!query_attack()) {
        help_the_boss(my_boss);
        for (i=0; i<sizeof(my_foes); i++) {
            foe = my_foes[i];
            if (foe && environment(TO) == environment(foe)) 
            {
                attack_object(foe);
                found_foe = 1;
                break;
            }
        }
	if (!found_foe && my_boss &&
	    environment(my_boss) != environment(TO)) {
	    tell_room(environment(TO), QCTNAME(TO) +
		      " leaves to seek his master.\n", TO);
	    move_living("M", environment(my_boss));
	    tell_room(environment(my_boss), QCTNAME(TO) +
		      " arrives.\n", TO);
            set_alarm(4.0, -1.0, attack_someone);
	    return;
	}
    }
    set_alarm(30.0, -1.0, attack_someone);
}
