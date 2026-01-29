inherit "/d/Emerald/std/emerald_monster";
inherit "/d/Emerald/std/aid_npc";
#include "/d/Emerald/defs.h"
#include <wa_types.h>

create_emerald_monster()
{
	set_name("tribesman");
	add_name(({"man", "tribes man", "tribeman", "tribe man", "human"}));
	set_short("tribesman");
	set_race_name("human");
	set_long("A large, well muscled man. By his clothing and " +
	"manner, you judge him to be a warrior.  He has a rather mean and " +
	"hard look to him.\n");

	set_alignment(550);
	set_skill(SS_DEFENSE, 65);
	set_skill(SS_WEP_POLEARM, 59);
	set_stats(({90,87,76,78,89,92}));
	set_hp(query_max_hp());

	set_restrain_path(VOL);
	set_random_move(3,4);
}

void
arm_me()
{
	object wep, pants;
	wep = clone_object(VOBJ + "pole1.c");
	wep -> move(this_object());
	command("wield all");
	pants = clone_object(VOBJ + "pants.c");
	pants -> move(this_object());
	command("wear all");
}

