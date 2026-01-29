inherit "/d/Cirath/std/patrol";
#pragma strict_types
#pragma save_binary 

inherit "/d/Cirath/std/monster";
#include <wa_types.h>
#include <options.h>
#include "/d/Cirath/common/defs.h"
#include "wbt.h"
#define RNDWEP ({"axe2.c", "mace2.c"})
#define ONE_OF_LIST(array)  ((array)[random(sizeof(array))])

void
arm_me();

void
create_monster()
{
	::create_monster();
	set_race_name("adept");
	set_name("adept");
	set_adj("advanced");
 add_adj("warrior");

   set_long("This adept looks almost the same as some of the "
        +"other adepts, but from the way he moves and swings his "
        +"sword, you assume he is much more advanced than the "
        +"standard adept.\n");


	add_prop(LIVE_I_NEVERKNOWN, 1);

	set_stats(({ 60, 50, 48, 30, 30, 60}));

	set_skill(SS_DEFENCE, 40);
	set_skill(SS_PARRY, 36);
	set_skill(SS_WEP_AXE, 50);
	set_skill(SS_WEP_POLEARM, 50);
	set_skill(SS_WEP_CLUB, 50);

	set_alignment(-30);

	set_act_time(10);
	set_cact_time(5);

   add_act("Hey, fool!  You want to spar?");
   add_act("grin eagerly");


	add_cact("'Heh, what are you trying to do ? The best one trained me!");
	add_cact("shout Come on, wanna see my real fight ?");

	set_default_answer("Adept says: Go out, wretch!\n");
	start_patrol();
	set_patrol_time(30);
	set_patrol_path(({"e", "e", "w", "w","s", "n"}));
}

void
arm_me()
{
	int ran = random(2);
	clone_object(WWORK + RNDWEP[ran])->move(TO);
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
