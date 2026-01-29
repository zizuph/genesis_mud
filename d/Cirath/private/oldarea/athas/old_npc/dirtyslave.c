inherit "/std/monster";
inherit "/std/act/action";

#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <macros.h>

void
create_monster()
{
	set_name("slave");
	set_race_name("human");
	add_adj("dirty");
	add_adj("pitiful");
	set_short("pitiful dirty slave");
	set_long("This appears to be a slave of a noble. "+
	   "He doesn't seem very useful, as he is just "+
	   "standing around being worthless.\n");

	set_stats(({ 20, 30, 20, 20, 20, 15 }));
	set_skill(SS_DEFENCE, 10);
	set_skill(SS_WEP_POLEARM, 10);
	set_skill(SS_PARRY, 20);

	set_alignment(0);

	refresh_mobile();

	set_chat_time(7);
	add_chat("Are you going to hurt me?");
	add_chat("Please don't hurt me.");
	add_chat("I'll be good this time, I promise.");
	
	set_cchat_time(5);
	add_cchat("Leave me alone! I didn't do anything to you!");
	add_cchat("I'll call the guards!");
	add_cchat("HELP! I'm being attacked! Someone! ANYONE! HELP!");

	set_alarm(1.0, 0.0, "arm_me");
}
arm_me()
{
	seteuid(getuid(TO));
	clone_object(A_WEP_D +"fork")->move(TO);
	clone_object(A_ARM_D +"dirtyrobe")->move(TO);

	command("wear all");
	command("wield all");
}

query_knight_prestige(){return -1;}

