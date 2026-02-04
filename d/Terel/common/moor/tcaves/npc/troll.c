/*
 * troll.c
 * Troll north of Terel. Claws and regenerates, sort of.
 * Shinto:
 *
 *  Modified: 6 May 2003, by Bleys
 *      - fixed a typo in the special
 *
 *            30 June 2008 Lilith
 *      - Removed code that discriminated against people who can
 *        go invis and see or fight in the dark. They pay for
 *        these skills and abilities, why foil them? Also,
 *        lowered the evil align. They do nothing to warrant
 *        being -700 align.
 *           15 Aug 2008  Lilith
 *      - Lowered the 130 exp modifier to 110
 *      - Added logging of kills
 *           28 Sep 2008  Lilith
 *      -Made it possible for randomly larger sized npcs.
 *      -put exp factor back in, but at 125.
 *
 *  Modified May 2009 by Petros
 *      - Re-upped skills and attacks and alignment
 *      - Lowered exp_factor to 110
 *
 *  Modified May 2010 by Petros
 *      - Added check for query_not_attack_me in special_attack
 *  Cotillion - 2020-07-13
 *  - XP factor to 105
 *
 *  Lucius - Jan 2021
 *     Cleanup. Add NPC_I_NO_LOOKS.
 *     Removed the 'ogre' to disambiguate from player race/guild.
 *     Increased LIVE_I_SEE_DARK, 3->9, these trolls live in darkness
 *     it shouldn't be that easy to overcome it.
 *     Turn off logging, doesn't add anything at this point
 *     and the giant trolls don't even do it either.
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

#define KILL_FILE  (TROLL_CAVE_DIR + "npc/troll_log")

public static string *adjs = ({
    "large", "terrifying", "green-skinned", "disgusting",
    "sickly", "grotesque", "slimy", "brown-skinned",
});

void
create_creature()
{
    set_adj(one_of_list(adjs));
    set_race_name("troll");
    add_name("_terel_cave_troll");

    set_long("A horrible flesh-eating creature. It has thick skin "
      +"of putrid gray-green and mottled black. Its mouth lined "
      +"with cruel teeth, its hands with dagger-like claws. "
      +"Dirty and smelling of rot, its body covered with hides "
      +"and tattered clothing, its head draped by thick strands "
      +"of gray bestial hair. Its eyes black with yellow slits.\n");

    default_config_creature(170 + random(50));

    set_skill(SS_DEFENCE, 60);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_UNARM_COMBAT, 75);
    set_skill(SS_BLIND_COMBAT, 75);

    set_aggressive(1);
    set_exp_factor(105);
    set_alignment(-700);

    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_SEE_DARK, 9);

    set_attack_unarmed(A_BITE,   55, 50, W_IMPALE, 30, "bite");
    set_attack_unarmed(A_R_CLAW, 45, 40, W_SLASH, 35, "right claw");
    set_attack_unarmed(A_L_CLAW, 45, 40, W_SLASH, 35, "left claw");

    set_hitloc_unarmed(H_HEAD, ({ 45, 35, 40}), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 40, 35, 40}), 40, "body");
    set_hitloc_unarmed(H_R_ARM, ({35, 35, 35 }), 20, "right arm");
    set_hitloc_unarmed(H_L_ARM, ({35, 35, 35 }), 20, "left arm");
}

int
special_attack(object enemy)
{
    mixed* hitresult;
    string how;
    object wuss, me = TO;
    int hurt;

    if (random(11) > 8)
    {
	// Make sure that we can actually attack the target
	if (enemy->query_not_attack_me(me, -1))
	    return 1; // round is ended so return 1.

	hurt = F_PENMOD(50 +(random(10)), 50 + (random(20)));
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

	tell_watcher(QCTNAME(me) + " slashes at " + QTNAME(enemy)
            + ".\n", enemy);
	enemy->catch_tell(query_The_name(enemy) + " slashes at you!\n" +
            "You feel " + how + ".\n");

	if (enemy->query_hp() <= 0)
	    enemy->do_die(me);

	heal_hp(50 + random(50));
	wuss = query_smallest_enemy();
	if (wuss != query_attack())
	    command("kill " + wuss->query_real_name());

	return 1;
    }

    return 0;
}

#if 0
void
do_die(object killer)
{
    if (query_hp() > 100)
	return 0;

    if (!killer)
	killer = previous_object();

    object *enemies = query_my_enemies();
    string str = killer->query_name() + "[" + killer->query_average_stat() + "]";
    for (int i=0; i<sizeof(enemies); i++)
    {
	if (enemies[i] != killer)
	    str += ", " + enemies[i]->query_name() +
	    "[" + enemies[i]->query_average_stat() + "]";
    }

    if (file_size(KILL_FILE) > 50000)
	rename(KILL_FILE, KILL_FILE+".old");
    write_file(KILL_FILE, ctime(time()) +" by "+ str +"\n");

    ::do_die(killer);
}
#endif
