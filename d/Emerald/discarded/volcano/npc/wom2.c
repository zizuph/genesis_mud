
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
	set_long("   An elderly woman of the tribe. Her days of heavy " +
	"work are over, so she now weaves clothes for the other members of " +
	"her tribe.\n\n");

	set_alignment(340);
	set_stats(({38,39,39,38,23,38,38,39}));
	set_skill(SS_DEFENSE, 37);
	set_skill(SS_UNARM_COMBAT, 30);

	set_restrain_path(VOL);
	seteuid(getuid());
}

void
arm_me()
{
	object skirt, blouse;
	skirt = clone_object(VOBJ + "skirt.c");
	skirt -> move(this_object());
	blouse = clone_object(VOBJ + "shirt.c");
	blouse -> move(this_object());
	command("wear all");
}

