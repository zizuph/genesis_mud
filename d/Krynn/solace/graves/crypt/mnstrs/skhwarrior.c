/* Skeletal hero by percy*/

#include "/d/Krynn/common/defs.h"

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/solace/graves/local.h"
#include <money.h>

inherit M_FILE

void
create_krynn_monster()
{
	int i;

	set_name("skeletal hero");
	set_pname("skeletal heroes");
	set_short("skeletal hero");
	set_pshort("skeletal heroes");
	add_name("hero");
	add_pname("heroes");
	set_race_name("skeleton");
	set_long("This skeleton looks more powerful than most.\n"
	 + "It now bears a hatred for all living things......\n");
	set_adj("hero");
	
	for (i = 0; i < 6; i++)
		set_base_stat(i, 20 + random(6));
	set_skill(SS_DEFENCE, random(10) + 20);
	set_skill(SS_WEP_SWORD, 55);
	set_skill(SS_PARRY, 30);
	set_skill(SS_2H_COMBAT, 30);

	set_all_attack_unarmed(10, 10);
	set_all_hitloc_unarmed(10);
	set_alignment(-300);
	set_knight_prestige(250);
	set_monster_home(TDIR+"crypt1");
	set_restrain_path(TDIR);
	add_act("emote stares at you, death in his eyes.");
	add_act("emote looks at you in disdain.");
	add_act("emote watched your every move.");
	set_act_time(15);
	set_aggressive(1);
	add_prop(NPC_I_NO_RUN_AWAY, 1);
	add_prop(LIVE_I_UNDEAD, 20);
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
	clone_object(OBJ + "skel_shield")->move(TO);

	command("wear all");
	command("wield all");
	seteuid(geteuid(TO));
	MONEY_MAKE_SC(random(20))->move(this_object());
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
