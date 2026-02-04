/*
 * gtroll.c
 * Giant troll, claws and regenerates sort of.
 * Shinto:
 *
 *  Modified: 6 May 2003, by Bleys
 *      - fixed a typo in the special attack
 *
 *  Modified: May 2009 by Petros
 *      - Re-upped the skills and stats and adjusted exp factor to 130
 *
 *  Modified May 2010 by Petros
 *      - Added check for query_not_attack_me in special_attack
 *
 *  Lucius - Jan 2021
 *     Cleanup. Add NPC_I_NO_LOOKS.
 *     Increased LIVE_I_SEE_DARK, 3->9, these trolls live in darkness
 *     it shouldn't be that easy to overcome it.
 */
#include "/d/Terel/include/Terel.h"

inherit STDCREATURE;

inherit "/std/combat/unarmed";   /* This gets us standard unarmed routines */
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <macros.h>

#define A_BITE    1
#define A_R_CLAW  2
#define A_L_CLAW  4

#define H_HEAD    1
#define H_BODY    2
#define H_R_ARM   3
#define H_L_ARM   4

void
create_creature()
{
    set_adj("giant");
    set_race_name("troll");
    set_short("giant troll");
    set_long("A horrible flesh-eating creature. It has thick skin "
      +"of putrid gray-green and mottled black. Its mouth lined "
      +"with cruel teeth, its hands with dagger like claws. "
      +"Dirty and smelling of rot, its body covered with hides "
      +"and tattered clothing, its head draped by thick strands "
      +"of gray bestial hair. Its eyes black with yellow slits.\n");

    /* str, con, dex, int, wis, dis */
    set_stats(({ 210, 170, 300, 130, 130, 150}));

    set_skill(SS_DEFENCE, 75);
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_UNARM_COMBAT, 75);
    set_skill(SS_BLIND_COMBAT, 75);
    set_exp_factor(130);
    set_alignment(-1200);
    set_aggressive(1);

    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_SEE_DARK, 9);

    set_attack_unarmed(A_BITE,   55, 50, W_IMPALE, 60, "bite");
    set_attack_unarmed(A_R_CLAW, 50, 50, W_SLASH, 20, "right claw");
    set_attack_unarmed(A_L_CLAW, 50, 50, W_SLASH, 20, "left claw");

    set_hitloc_unarmed(H_HEAD, ({ 30, 30, 20}), 15, "head");
    set_hitloc_unarmed(H_BODY, ({ 30, 30, 30}), 65, "body");
    set_hitloc_unarmed(H_R_ARM, ({25, 15, 15 }), 10, "right arm");
    set_hitloc_unarmed(H_L_ARM, ({25, 15, 15 }), 10, "left arm");
}

int
special_attack(object enemy)
{
    mixed* hitresult;
    string how;
    object wuss, me = TO;
    int hurt;

    if (random(11) > 7)
    {   // Make sure that we can actually attack the target
	if (enemy->query_not_attack_me(me, -1))
	    return 1; // round is ended so return 1.

	hurt = F_PENMOD(50, 60);
	hitresult = enemy->hit_me(hurt, W_SLASH, me, -1);

	how = "unharmed";
	if (hitresult[0] > 0)
	    how = "slightly hurt";
	if (hitresult[0] > 20)
	    how = "rather hurt";
	if (hitresult[0] > 50)
	    how = "crushed";
	if (hitresult[0] > 100)
	    how = "devastated";

	tell_watcher(QCTNAME(me) + " slashes at " +
            QTNAME(enemy) + ".\n", enemy);
	enemy->catch_tell(query_The_name(enemy) +
            " slashes at you!\nYou feel " + how + ".\n");

	if (enemy->query_hp() <= 0)
	    enemy->do_die(me);

	heal_hp(200 + random(150));

	wuss = query_smallest_enemy();
	if (wuss != query_attack())
	    command("$kill " + OB_NAME(wuss));

	return 1;
    }

    return 0;
}
