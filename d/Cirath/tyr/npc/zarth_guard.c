
#pragma strict_types
#pragma save_binary 

inherit "/d/Cirath/std/monster";
#include <wa_types.h>
#include <options.h>
#include "defs.h"

#define JWEAPON ({"hefty_axe", "steel_spear", "edged_swrd", "war_mace"})[random(4)]

void
arm_me();

void
zarth_help();

void
create_monster()
{
	::create_monster();
	set_race_name("guard");
	set_name("human");
	set_adj("brutal");
	set_adj("agile");

	set_long("This is a personal body guard. He looks very grim and he "
		+"would probably not hesitate kill you.\n");

	add_prop(LIVE_I_NEVERKNOWN, 1);

	set_stats(({ 120, 140, 120, 80, 80, 100}));

	set_skill(SS_DEFENCE, 50);
	set_skill(SS_PARRY, 45);
	set_skill(SS_WEP_AXE, 80);
	set_skill(SS_WEP_SWORD, 80);
	set_skill(SS_WEP_POLEARM, 80);
	set_skill(SS_BLIND_COMBAT, 30);
	set_skill(SS_WEP_CLUB, 80);

	set_alignment(-300 + random(601));

	set_act_time(10);
	set_cact_time(5);

	add_act("emote peers around menacingly.");
	add_act("emote sighs deeply.");
	add_act("' You better leave now.");
	add_act("poke all");

	add_cact("' Stop this! Now I am really angry.");
	add_cact("emote grumbles loudly.");
	add_cact("' Leave now or die!");
	add_cact("emote gasps in astonishment.");

	set_default_answer("Don't ask me. Ask someone else.");
}

void
arm_me()
{
	clone_object(TYR_ARM + "jail_body.c")->move(TO);
	clone_object(TYR_ARM + "jail_head.c")->move(TO);
	clone_object(TYR_ARM + "jail_cloak.c")->move(TO);
	clone_object(TYR_WEP + JWEAPON)->move(TO);
	command("wear all");
	command("wield all");
}

void
zarth_help()
{
	command("assist zarth");
}

/* sets unarmed combat off, giving more weapon attacks! */

int
query_option(int opt)
{
  return (opt == OPT_UNARMED_OFF);
}