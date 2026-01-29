#pragma strict_types
 
inherit "/d/Cirath/std/monster";
#include "defs.h"

#define JWEAPON ({"hefty_axe", "steel_spear", "edged_swrd", "war_mace"})[random(4)]

void
create_monster()
{
	::create_monster();
	set_race_name("guard");
	set_adj("stern");
	set_adj("agile");

	set_long("This is a guard in the jail. He looks very grim and he "
		+"would probably not hesitate to throw you into a cell. "
		+"To guard is his job and he will for sure protect this "
		+"building.\n");

	add_prop(LIVE_I_NEVERKNOWN, 1);

	set_stats(({ 100, 120, 100, 60, 60, 80}));

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
	add_act("say You better leave now. Before we put you into a cell.");
	add_act("poke all");
	add_act("say The Captain won't be happy if we don't do our job.");
	add_act("say The payment for this job really sucks.");

	add_cact("say Stop this! Now I am really angry.");
	add_cact("shout Guards! More guards! We are under attack!");
	add_cact("emote grumbles loudly.");
	add_cact("say Leave now or die!");
	add_cact("emote gasps in astonishment.");

	set_speak("You better leave, or I'll put you in a cell for sure.");
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

