inherit "/d/Emerald/std/emerald_monster";
inherit "/d/Emerald/std/aid_npc";
#include "/d/Emerald/defs.h"
#include <wa_types.h>
#include "/d/Wiz/triana/monster.c"

void
create_my_monster()
{
	set_name("tribesman");
	add_name(({"man", "tribesman", "tribes man", "tribe man"}));
	set_short("tribesman");
	set_race_name("human");
	set_long("A large, strong member of the local tribe. He looks " +
	"like he would be very devout in his worship of the local " +
	"god. This man appears to be a hunter in his tribe.\n");

	set_alignment(550);
	set_skill(SS_DEFENSE, 50);
	set_skill(SS_WEP_KNIFE, 47);
	set_stats(({70,68,74,65,67,67}));
	set_hp(query_max_hp());
	set_restrain_path(VOL);
	set_random_move(3,4);
	seteuid(getuid());
}

void
arm_me()
{
	object wep, pants;
	wep = clone_object(VOBJ + "knife1.c");
	wep -> move(this_object());
	pants = clone_object(VOBJ + "pants.c");
	pants -> move(this_object());
	command("wear all");
	command("wield all");
}

