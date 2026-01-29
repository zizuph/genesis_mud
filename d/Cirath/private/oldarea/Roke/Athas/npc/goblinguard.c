inherit "/std/monster";
inherit "/std/act/action";

#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <macros.h>

void
create_monster()
{
	set_name("magron");
	add_name("slave");
	set_race_name("goblin");
	add_adj("massive");
	add_adj("hairy");
	set_short("hairy massive goblin slave");
	set_long("This looks like a mix between a bear and a "+
	   "goblin. He has big, gnashing teeth, and a smug "+
	   "look on his face that leads you to believe he "+
	   "knows something you don't.\n");

	set_stats(({ 100, 70, 100, 70, 70, 100 }));
	set_skill(SS_DEFENCE, 50);
	set_skill(SS_PARRY, 50);
	set_skill(SS_BLIND_COMBAT, 100);
	set_skill(SS_WEP_AXE, 90);

	set_alignment(-300);

	refresh_mobile();

	set_act_time(7);
	add_act("grin");
	add_act("chuckle rude");
	add_act("grin know");
	add_act("winks like he knows something you don't.");
	
	set_cchat_time(8);
	add_cchat("You'll never live to see the boss.");
	add_cchat("Nice ears. I think I'll add them to my "+
	   "collection.");

        set_cact_time(3);
	add_cact("emote gnashes his teeth menacingly.");
	add_cact("emote gnashes his teeth savagely.");
        add_cact("emote gnashes his teeth hungrily.");
	add_cact("emote gnashes his teeth playfully.");
	add_cact("cackle demon");

	set_alarm(1.0, 0.0, "arm_me");
}
arm_me()
{
	seteuid(getuid(TO));
	clone_object(A_WEP_D +"axe4")->move(TO);
	clone_object(A_ARM_D +"hugeshield")->move(TO);
	clone_object(A_ARM_D +"blackhelmet")->move(TO);
	clone_object(A_ARM_D +"blackboots")->move(TO);
	clone_object(A_ARM_D +"scalemail")->move(TO);

	command("wear all");
	command("wield all");
}

query_knight_prestige(){return 550;}
