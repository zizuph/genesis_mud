inherit "/std/monster.c";
#include "/d/Emerald/defs.h"

create_monster()
{
	set_name("boy");
	set_adj("young");
	add_adj("energetic");
	set_short("young boy");
	set_race_name("human");
	set_long("   A young boy tentaively weilding a knife. " +
	"He looks like he would be learning his trade from an elder " +
	"of his tribe.\n\n");

	set_alignment(100);
	set_skill(SS_DEFENSE, 20);
	set_skill(SS_WEP_KNIFE, 20);
	set_stats(({30, 28, 27, 27, 28, 29}));
	set_hp(query_max_hp());
	set_restrain_path("/d/Emerald/tmp/volcano/");
	set_random_move(3,4);
	call_out("arm_me", 1);
}

void
arm_me()
{
	object wep;
	wep = clone_object(VOBJ + "knife2.c");
	wep -> move(this_object());
	command("wield all");
}

