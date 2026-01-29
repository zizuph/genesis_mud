/* Guard in the jail of Tyr */

#pragma strict_types
 
inherit "/d/Cirath/std/monster";
#include "defs.h"

#define JWEAPON ({"hefty_axe", "steel_spear", "edged_swrd", "war_mace"})[random(4)]
#define JADJ1 ({"stern", "agile", "grim", "strong", "ugly", "angry", "cruel"})[random(7)]
#define JADJ2 ({"arrogant", "sadistic", "angry", "massive"})[random(4)]
#define JRACE ({"human", "half-giant"})[random(2)]

void
create_monster()
{
        ::create_monster();
	add_name("guard");
        set_race_name(JRACE + " guard");
        set_adj(JADJ2);
        set_adj(JADJ1);

        set_long("This guard keeps his eyes out for possible escapers from "
		+"the cells. Another assignment is also to see that noone "
		+"helps the prisoners to escape or attack the jail. This "
		+"is a rented mercenary that looks very capable to do his "
		+"job. This isn't the right person to mess with.\n");

        add_prop(LIVE_I_NEVERKNOWN, 1);

        set_stats(({ 100, 100, 100, 60, 60, 80}));

        set_skill(SS_DEFENCE, 70);
        set_skill(SS_PARRY, 70);
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
	add_act("emote eyes you up and down.");

	add_cact("say Stop this! Now I am really angry.");
	add_cact("shout Guards! More guards! We are under attack!");
	add_cact("emote grumbles loudly.");
	add_cact("say Now you are going to die!");
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
	make_cash(random(2), "gold");
	make_cash((random(5)+5), "silver");
	command("wear all");
	command("wield all");
}
