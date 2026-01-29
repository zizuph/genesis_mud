/* Manor owner. Zayn 02-17-97. */
 
#pragma strict_types
 
inherit "/d/Cirath/std/monster.c";
#include "defs.h"
 
void
create_monster()
{
	set_name("arman");
	set_title("owner of the Manor");
	set_race_name("human");
	set_adj("rich");
	set_adj("determined");

	set_long("A rich, clean and determined noble human, who wont let anything "
		+"get in his way. He got the money to move all obstacles "
		+"that are possible to encounter. This isn't a person to mess "
		+"with if you don't want rich enemies.\n");

	set_stats(({ 30, 40, 50, 20, 20, 20}));

	add_prop(NPC_I_NO_RUN_AWAY,1);

	set_alignment(100);

	set_skill(SS_WEP_AXE, 60);
	set_skill(SS_DEFENCE, 50);
	set_skill(SS_PARRY, 40);

	set_act_time(7);
	add_act("emote starts to sort the books into an orderly fashion.");
	add_act("emote smiles proudly over his big wealth.");
	add_act("emote eyes you with a disparaging look.");
	add_act("emote pats his purse lovingly. It looks well filled.");
	add_act("emote adjusts the bedspread on the bed.");
	add_act("' If you attack me, you will get rich enemies.");
	add_act("' Do not touch my things. I want everything perfect.");
	set_cact_time(3);
	add_cact("shout GUARDS! GUARDS! HELP!");
	add_cact("emote tries to hide behind the bed.");
	add_cact("' You will regret this day!");
	add_cact("' No don't do this to me, please.");
}

void
arm_me()
{
	clone_object(TYR_ARM+"body_pad.c")->move(TO);
        clone_object(TYR_ARM+"robe_hid.c")->move(TO);
	clone_object(TYR_WEP+"implr_bn.c")->move(TO);
	make_cash((random(2)+2), "silver");
	make_cash(1, "gold");
	command("wield all");
	command("wear all");
}
