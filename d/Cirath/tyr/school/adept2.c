inherit "/d/Cirath/std/patrol";
#pragma strict_types
#pragma save_binary 

inherit "/d/Cirath/std/monster";
#include <wa_types.h>
#include <options.h>
#include "/d/Cirath/common/defs.h"
#include "wbt.h"

#define ADJ1 ({"little", "clumsy", "skinny"})
#define ADJ2 ({"idiotic", "feared", "skilless"})
#define RNDWEP ({"axe.c", "mace.c"})
#define ONE_OF_LIST(array)	((array)[random(sizeof(array))])

void
arm_me();

void
create_monster()
{
	::create_monster();
	set_race_name("adept");
	set_name("adept");
	set_adj(ADJ1[random(3)]);
	set_adj(ADJ2[random(3)]);

   set_long("This young human is one of the newer students in "
        +"the Warrior's School.  He looks to be barely capable "
        +"of defending himself from attack, but he would give "
        +"it a try if pushed too far.\n");

	add_prop(LIVE_I_NEVERKNOWN, 1);

	set_stats(({ 40, 30, 38, 20, 20, 35}));

	set_skill(SS_DEFENCE, 10);
	set_skill(SS_PARRY, 16);
	set_skill(SS_WEP_AXE, 20);
	set_skill(SS_WEP_POLEARM, 20);
	set_skill(SS_WEP_CLUB, 20);

	set_alignment(0);

	set_act_time(10);
	set_cact_time(5);

	add_act("emote smiles with fear in his eyes.");
   add_act("say Hi there!  Are you a new adept?");
   add_cact("say Oh, are you kidding me?  I'm not strong!");
   add_cact("shout Help me!  Help!  Teacher!");

   set_default_answer("The adept looks at you with panic plainly "
        +"in his eyes and says:\nPlease ask my teacher.\n");

	start_patrol();
	set_patrol_time(30);
	set_patrol_path(({"e", "e", "w", "w", "s", "n"}));
}

void
arm_me()
{
	int ran;
	object wep;
	ran = random(2);
	wep = clone_object(WWORK + RNDWEP[ran]);
	wep->move(TO);
	clone_object(WWORK + "body.c")->move(TO);
	command("wear all");
	command("wield all");
}
/* sets unarmed combat off, giving more weapon attacks! */

int
query_option(int opt)
{
	return (opt == OPT_UNARMED_OFF);
}
