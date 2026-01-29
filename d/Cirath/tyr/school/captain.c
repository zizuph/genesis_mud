
#pragma strict_types
#pragma save_binary 

inherit "/d/Cirath/std/monster";
#include <wa_types.h>
#include <options.h>
#include "/d/Cirath/common/defs.h"
#include "wbt.h"
		
void
create_monster()
{
	::create_monster();
   set_race_name("human");
   set_name("alteer");
   set_title("the Captain of the Guard of the Warrior School "
	+"of Tyr");
	set_adj("powerful");
	set_adj("strong");
	
	
	set_short("powerful strong guard captain");
	set_long("The captain of school's guards looks really strong. "+
			"You can't see fear in his eyes, and you know, that he "+
			"is really worthy opponent.\n");

	add_prop(LIVE_I_NEVERKNOWN, 1);

	set_stats(({ 130, 150, 140, 90, 90, 110}));

	set_skill(SS_DEFENCE, 75);
	set_skill(SS_PARRY, 80);
   set_skill(SS_WEP_CLUB,80);

	set_alignment(-400 + random(60));

	set_act_time(20);
	set_cact_time(5);

	add_act("emote smiles maniacally.");
	add_act("' What do ya want here, wretch ?");
	add_act("' Go out, yer not an adept!");

	add_cact("' Guards! This stupid one wants be slayed ground!");
	add_cact("emote smirks.");

	set_default_answer("The captain grins.\n The captain says: It's one answer - I can kill ya whenever I want!\n");
   call_out("arm_me",1);
}

void
arm_me()
{
	clone_object(WWORK+"ghelmet.c")->move(TO);
	clone_object(WWORK+"gbody.c")->move(TO);
	clone_object(WWORK+"cmace.c")->move(TO);
	command("wear all");
	command("wield all");
}

/* sets unarmed combat off, giving more weapon attacks! */

int
query_option(int opt)
{
  return (opt == OPT_UNARMED_OFF);
}
