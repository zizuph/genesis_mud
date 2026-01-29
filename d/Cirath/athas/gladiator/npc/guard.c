
#pragma strict_types
#pragma save_binary 

inherit "/d/Cirath/std/monster";
#include <wa_types.h>
#include <options.h>
#include "/d/Cirath/common/defs.h"
#include "wbt.h"

void
arm_me();

void
create_monster()
{
	::create_monster();
	set_race_name("human");
	set_name("guard");
	set_adj("angry");
	set_adj("school");

	set_short("angry school guard");
	set_long("This is a guard.\n");

	add_prop(LIVE_I_NEVERKNOWN, 1);

	set_stats(({ 120, 140, 120, 80, 80, 100}));

	set_skill(SS_DEFENCE, 70);
	set_skill(SS_PARRY, 80);
	set_skill(SS_WEP_AXE, 80);
	set_skill(SS_WEP_SWORD, 80);
	set_skill(SS_WEP_POLEARM, 80);
	set_skill(SS_WEP_CLUB, 80);

	set_alignment(-300 + random(60));

	set_act_time(10);
	set_cact_time(5);

	add_act("emote grins.");
	add_act("' Get out of there!");
	add_act("' Yeah, I must stay here all the time...");

	add_cact("' Hey, foolish! Leave me alone!");
	add_cact("shout Guys, come on! This one has really trouble now!");
	add_cact("emote finger");

	set_speak("What are ya doing here?");
	set_default_answer("The guard looks at you and says: What do ya want? Better stop asking!\n");
}

void
arm_me()
{
	clone_object(WWORK+"ghelmet.c")->move(TO);
	clone_object(WWORK+"gbody.c")->move(TO);
	clone_object(WWORK+"gaxe.c")->move(TO);
	command("wear all");
	command("wield all");
}

/* sets unarmed combat off, giving more weapon attacks! */

int
query_option(int opt)
{
  return (opt == OPT_UNARMED_OFF);
}
