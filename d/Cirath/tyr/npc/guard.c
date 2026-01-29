
#pragma strict_types
#pragma save_binary 

inherit "/d/Cirath/std/monster";
#include <wa_types.h>
#include <options.h>
#include "defs.h"

#define JWEAPON ({"hefty_axe", "steel_spear", "edged_swrd", "war_mace"})[random(4)]

void
create_monster()
{
	::create_monster();
	set_race_name("guard");
	set_name("human");
   set_adj("strong");
   set_adj("human");
   set_short("strong human guard");
   set_long("This is a standard member of the Tyrian guard.  He "
	+"tries his best to keep order in the city without exposing "
	+"himself to any undue risk.  Physically strong, he looks "
	+"to have some experience in fighting.\n");

	add_prop(LIVE_I_NEVERKNOWN, 1);

	set_stats(({ 120, 140, 120, 80, 80, 100}));

	set_skill(SS_DEFENCE, 70);
	set_skill(SS_PARRY, 80);
	set_skill(SS_WEP_AXE, 80);
	set_skill(SS_WEP_SWORD, 80);
	set_skill(SS_WEP_POLEARM, 80);
	set_skill(SS_WEP_CLUB, 80);

	set_alignment(-300 + random(601));

	set_act_time(10);
	set_cact_time(5);

	add_act("emote peers around menacingly.");
	add_act("emote sighs deeply.");
	add_act("poke all");
	add_act("' The Captain won't be happy if we don't do our job.");
	add_act("' The payment for this job really sucks.");

	add_cact("' Stop this! Now I am really angry.");
	add_cact("shout Guards! More guards! We are under attack!");
	add_cact("emote grumbles loudly.");
	add_cact("' Leave now or die!");
	add_cact("emote gasps in astonishment.");

	set_assist_cry("Let us enslave this puny creature! I will assist you.");
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

/* sets unarmed combat off, giving more weapon attacks! */

int
query_option(int opt)
{
  return (opt == OPT_UNARMED_OFF);
}
