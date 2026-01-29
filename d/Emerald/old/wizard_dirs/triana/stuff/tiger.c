inherit "/d/Avenir/inherit/monster.c";
#include "/d/Avenir/common/bazaar/bazaar.h"
#include <language.h>

void
create_monster()
{
	::create_monster();
	set_name("raja");
	set_race_name("tiger");
set_long("A gorgeous, snow-white tiger.\n");
	set_stats(({70,70,72,72,71,69}));
	set_hp(3200);

	set_act_time(4);
	add_act("lick all");
	add_act("emote licks his paws");
	add_act("snuggle all");
	add_act("purr");
	add_act("stretch");

	set_skill(SS_DEFENCE, 90);
	set_skill(SS_UNARM_COMBAT, 90);
	set_skill(SS_PARRY, 85);
	set_skill(SS_HUNTING, 55);
	set_skill(SS_TRACKING, 60);

	call_out("arm_me", 1);
}

void
arm_me()
{
object wep;

wep=clone_object("/d/Wiz/triana/belt.c");
wep->move(this_object());
	command("wear all");
}
