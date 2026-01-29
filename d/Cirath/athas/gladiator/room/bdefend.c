
#pragma strict_types
#pragma save_binary 

inherit "/d/Cirath/std/monster";
#include <wa_types.h>
#include <options.h>
#include "/d/Cirath/common/defs.h"

void
arm_me();

void
brutus_help();

void
create_monster()
{
	::create_monster();
	set_race_name("human");
	set_name("defender");
	set_adj("improved");
	set_adj("gladiator");

	set_short("improved great gladiator");
	set_long("This is an advanced gladiator, walking along the guild.\n");

	add_prop(LIVE_I_NEVERKNOWN, 1);

	set_stats(({ 160, 140, 170, 90, 85, 140}));

	set_skill(SS_DEFENCE, 80);
	set_skill(SS_PARRY, 85);
	set_skill(SS_WEP_AXE, 90);

	set_alignment(-300 + random(60));

	set_act_time(10);
	set_cact_time(5);

}

void
arm_me()
{
}

/* sets unarmed combat off, giving more weapon attacks! */

void
brutus_help()
{
	command("assist brutus");
}

int
query_option(int opt)
{
  return (opt == OPT_UNARMED_OFF);
}
