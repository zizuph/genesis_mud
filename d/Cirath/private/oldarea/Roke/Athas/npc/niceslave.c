inherit "/std/monster";
inherit "/std/act/action";

#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <macros.h>

void
create_monster()
{
	set_name("niceguy");
	add_name("slave");
	set_race_name("human");
	add_adj("pleasant");
	set_short("pleasant man");
	set_long("He's just relaxing, trying to get away "+
	   "from that aweful sun outside.\n");

	set_stats(({ 75, 85, 60, 70, 70, 70 }));
	set_skill(SS_DEFENCE, 60);
	set_skill(SS_PARRY, 50);
	set_skill(SS_WEP_AXE, 80);

	set_alignment(650);

	refresh_mobile();

	set_act_time(7);
	add_act("smile");
	add_act("chuckle");
	add_act("emote paces the room in a bored manner.");
	
	set_cchat_time(5);
	add_cchat("This is definately not my day.");
	add_cchat("Oh well, even dying would be better than this "+
	   "place.\n");
	add_cchat("If you're going to kill me, make it quick.\n");
	add_cchat("I must say, I have always been a sucker for "+
	   "a good fight.\n");

	set_alarm(1.0, 0.0, "arm_me");
}
arm_me()
{
	seteuid(getuid(TO));
	clone_object(A_WEP_D +"axe3")->move(TO);
	clone_object(A_ARM_D +"rleather")->move(TO);
	clone_object(A_ARM_D +"hugeshield")->move(TO);
	clone_object(A_ARM_D +"blackboots")->move(TO);
	clone_object(A_ARM_D +"armbands")->move(TO);
	clone_object(A_ARM_D +"pothelm")->move(TO);
	clone_object(A_ARM_D +"dirtyrobe")->move(TO);

	command("wear all");
	command("wield all");
}

query_knight_prestige(){return -3;}
