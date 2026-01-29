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
	set_long("A tall man who is garbed in the " +
	"traditional tribal clothes of a hunter.  He seems to be rather " +
	"proficient at what he does.\n");

	set_alignment(660);
	set_skill(SS_DEFENSE, 59);
	set_skill(SS_WEP_CLUB, 63);
	set_stats(({82,81,71,65,69,71}));
	set_hp(query_max_hp());

	set_restrain_path(VOL);
	set_random_move(3,4);
	seteuid(getuid());
}

void
arm_me()
{
	object wep, pants;
	wep = clone_object(VOBJ + "club1.c");
	wep -> move(this_object());
	command("wield all");
	pants = clone_object(VOBJ + "pants.c");
	pants -> move(this_object());
	command("wear all");
}

