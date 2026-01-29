inherit "/d/Emerald/std/emerald_monster";
inherit "/d/Emerald/std/aid_npc";
#include "/d/Emerald/defs.h"

create_emerald_monster()
{
	set_name("tribesman");
	add_name(({"tribes man", "tribeman", "tribe man", "man", "human"}));
	set_short("tribesman");
	set_race_name("human");
	set_long("A medium sized man who is dressed in tribal clothing. " +
	"By his clothing and manner, you judge him to be a young " +
	"warrior for the tribe.\n");

	set_alignment(550);
	set_skill(SS_DEFENSE, 50);
	set_skill(SS_WEP_KNIFE, 47);
	set_stats(({70,68,74,65,67,67}));
	set_hp(query_max_hp());

	set_restrain_path(VOL);
	set_random_move(3,4);
}

void
arm_me()
{
	object wep, pants;
	wep = clone_object(VOBJ + "knife1.c");
	wep -> move(this_object());
	command("wield all");
	pants = clone_object(VOBJ + "pants.c");
	pants ->  move(this_object());
	command("wear all");
}

