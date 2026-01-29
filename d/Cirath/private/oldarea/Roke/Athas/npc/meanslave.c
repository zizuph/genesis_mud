inherit "/std/monster";
inherit "/std/act/action";

#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <macros.h>

void
create_monster()
{
	set_name("meanie");
	add_name("slave");
	set_race_name("human");
	add_adj("mean");
	add_adj("brutal");
	set_short("mean brutal slave");
	set_long("This is one mean guy. He even kicks around "+
	   "the rats. He doesn't look like he would mind too "+
	   "much if he kicked you around either.\n");

	set_stats(({ 70, 70, 70, 70, 70, 70 }));
	set_skill(SS_DEFENCE, 50);
	set_skill(SS_PARRY, 50);
	set_skill(SS_WEP_AXE, 70);
	set_skill(SS_2H_COMBAT, 10);

	set_alignment(-650);

	refresh_mobile();

	set_act_time(7);
	add_act("growl evil");
	add_act("snicker");
	add_act("grin");
	add_act("smirk");
	
	set_cchat_time(5);
	add_cchat("I will SEE YOU IN HELL!");
	add_cchat("Time to die.");
	add_cchat("If you destroy me, I will only get stronger!");
	add_cchat("At last, a fight against a chicken!");

	set_alarm(1.0, 0.0, "arm_me");
}
arm_me()
{
	seteuid(getuid(TO));
	clone_object(A_WEP_D +"heavyaxe")->move(TO);
	clone_object(A_WEP_D +"lightaxe")->move(TO);
	clone_object(A_ARM_D +"rleather")->move(TO);
	clone_object(A_ARM_D +"armbands")->move(TO);
	clone_object(A_ARM_D +"blackboots")->move(TO);
	clone_object(A_ARM_D +"pothelm")->move(TO);
	clone_object(A_ARM_D +"dirtyrobe")->move(TO);

	command("wear all");
	command("wield all");
}

query_knight_prestige(){return 700;}
