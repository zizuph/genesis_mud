#include "/d/City/defs.h"
inherit GUARD;

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>

void
create_monster()
{
	set_g_follow(0);
	set_g_attack(10);

	set_name("Justin");
	set_race_name("human");
        set_long("This is one of the guardians of the Great Library.\n");
	set_gender(0);
        default_config_npc(80);
        set_base_stat(SS_CON, 100);
	set_hp(7500);
	set_skill(SS_UNARM_COMBAT,80);
	set_skill(SS_DEFENCE,70);
}

