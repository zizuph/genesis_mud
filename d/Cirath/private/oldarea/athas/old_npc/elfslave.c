inherit "/std/monster";
inherit "/std/act/action";

#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <macros.h>

void
create_monster()
{
	set_name("celebrin");
	add_name("slave");
	set_race_name("elf");
	add_adj("fair");
	set_short("fair elf");
	set_long("He is standing here looking pretty, "+
	   "like most elves do. Except this one is armed "+
	   "and looks like he knows how to use his "+
	   "weapon.\n");

	set_stats(({ 30, 60, 40, 40, 40, 40 }));
	set_skill(SS_DEFENCE, 30);
	set_skill(SS_PARRY, 50);
	set_skill(SS_WEP_AXE, 50);

	set_alignment(100);

	refresh_mobile();

	set_act_time(7);
	add_act("emote looks around gloomily.");
	add_act("sigh unha");
	add_act("twinkle melan");
	add_act("mumbles dreamily about trees and dandelions.");
	
	set_cact_time(5);
	add_cact("emote turns his back and goes into a huff.");
	add_cact("emote chooses to ignore you.");
	add_cact("emote drums his fingers impatiently.");
	add_cact("emote scoffs at your attack.");

	set_alarm(1.0, 0.0, "arm_me");
}
arm_me()
{
	seteuid(getuid(TO));
	clone_object(A_WEP_D +"longaxe")->move(TO);
	clone_object(A_ARM_D +"cshield")->move(TO);
	clone_object(A_ARM_D +"armbands")->move(TO);
	clone_object(A_ARM_D +"lvest")->move(TO);
	clone_object(A_ARM_D +"wlguards")->move(TO);
	clone_object(A_ARM_D +"pothelm")->move(TO);

	command("wear all");
	command("wield all");
}

query_knight_prestige(){return -1;}
