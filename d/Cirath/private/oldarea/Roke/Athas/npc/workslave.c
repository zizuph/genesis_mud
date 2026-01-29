inherit "/std/monster";
inherit "/std/act/action";

#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <macros.h>

void
create_monster()
{
	set_name("bob");
	add_name("slave");
	set_race_name("human");
	add_adj("tired");
	set_short("tired slave");
	set_long("This must be the slave that gets worked "+
	   "most. He seems very weary and overworked. Maybe "+
	   "he could use a drink and some food.\n");

	set_stats(({ 30, 30, 30, 30, 30, 30 }));
	set_skill(SS_DEFENCE, 15);
	set_skill(SS_PARRY, 10);
	set_skill(SS_WEP_POLEARM, 20);

	set_alignment(20);

	refresh_mobile();

	remove_prop(NPC_M_NO_ACCEPT_GIVE);

	set_act_time(10);
	add_act("yawn");
	add_act("stretch");
	
	set_cchat_time(5);
	add_cchat("Now what fer ya wanna go an kill a guy "+
	   "like me?");
	add_cchat("Didn't ah clean yer room, too?");
	add_cchat("How kin ah git any work done if ahm dead?\n");

	set_alarm(1.0, 0.0, "arm_me");
}
arm_me()
{
	seteuid(getuid(TO));
	clone_object(A_WEP_D +"scythe")->move(TO);
	clone_object(A_ARM_D +"wlguards")->move(TO);
	clone_object(A_ARM_D +"lhat")->move(TO);
	clone_object(A_ARM_D +"burlap")->move(TO);

	command("wear all");
	command("wield all");
}

query_knight_prestige(){return 1;}
