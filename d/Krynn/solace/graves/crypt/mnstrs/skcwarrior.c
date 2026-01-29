/* Skeletal champion by percy*/

#include <ss_types.h>
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/solace/graves/local.h"
#include <money.h>

inherit M_FILE

void
create_krynn_monster()
{
	int i;

	set_name("Skeletal champion");
	set_race_name("skeleton");
	set_long("This skeleton looks very powerful.\n"
	 + "It now bears a hatred for all living things......\n");
	add_name("champion");
        set_adj(({"champion", "undead"}));
	
	for (i = 0; i < 6; i++)
		set_base_stat(i, 50 + random(10));
	set_skill(SS_DEFENCE, random(20) + 30);
	set_skill(SS_WEP_SWORD, 75);
	set_skill(SS_PARRY, 40);
	set_skill(SS_2H_COMBAT, 50);

	set_all_attack_unarmed(20, 20);
	set_all_hitloc_unarmed(20);
	set_alignment(-500);
	set_knight_prestige(500);
	set_monster_home(TDIR+"crypt1");
	set_restrain_path(TDIR);
	add_act("emote gives you a deathly stare.");
	add_act("emote looks deadly.");
	set_act_time(20);
	add_chat("Your soul WILL be mine, mortal!");
	add_chat("There's a grave outside just waiting for you mortal.");
	set_chat_time(8);
	set_aggressive(1);
	add_prop(NPC_I_NO_RUN_AWAY, 1);
	add_prop(LIVE_I_UNDEAD, 40);
	add_prop(LIVE_I_NO_CORPSE, 1);


	if (IS_CLONE)
	  set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
	seteuid(geteuid(this_object()));

	clone_object(OBJ + "skel_arm2")->move(TO);
	clone_object(OBJ + "skel_wep2")->move(TO);
	clone_object(OBJ + "skel_wep2")->move(TO);

	command("wear armour");
	command("wield all");
	seteuid(getuid(TO));
	MONEY_MAKE_SC(random(20)+10)->move(this_object());

}

void
do_die(object killer)
{
    object ob = clone_object("/std/leftover");
    ob->leftover_init("bone","human");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("skull","human");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("bone","human");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("rib","human");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("rib","human");
    ob->move(E(TO));
    ::do_die(killer);
}
