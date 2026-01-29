
inherit "/d/Emerald/std/emerald_monster";
inherit "/d/Emerald/std/aid_npc";
#include "/d/Emerald/defs.h"
#include <wa_types.h>

create_emerald_monster()
{
	set_name("tribeswoman");
	add_name(({"tribes woman", "tribe woman", "tribewoman", "woman"}));
	set_gender(G_FEMALE);
	set_short("tribeswoman");
	set_race_name("human");
	set_long("   A small woman who carries a basket in her arms. " +
	"From her appearance, you conclude her role is to gather " +
	"food grown in the area for the tribe to eat.\n\n");
	set_alignment(340);
	set_stats(({41,42,43,45,46,47}));
	set_skill(SS_DEFENSE, 37);
	set_skill(SS_UNARM_COMBAT, 45);

	set_random_move(1,2);
	set_restrain_path(VOL);
	seteuid(getuid());
}

void
arm_me()
{
	object wep, dress;
	seteuid(getuid());
	wep = clone_object(VOBJ + "basket.c");
	wep -> move(this_object());
	wep -> fill_pouch();
	dress = clone_object(VOBJ + "dress2.c");
	dress -> move(this_object());
	command("wear all");
}

