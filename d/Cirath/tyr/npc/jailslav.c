/* Slave in the Jail of Tyr */
inherit "/d/Cirath/std/monster.c";
#include "defs.h"

#define RNDRACE ({"human", "human", "human", "half-elf", "dwarf", "dwarf", "half-giant", "mul", "elf", "elf"})
#define RNDADJ ({"starving", "scarred", "withdrawn", "angry", "pathetic", "frightened", "weary", "old", "sullen", "dirty"})

void
create_monster()
{
	add_adj("enslaved");
	set_adj(RNDADJ[random(10)]);
	set_race_name(RNDRACE[random(10)]);
	set_name("slave");
	set_gender(random(2));
	set_long("This slave looks pathetic. The slave wears dirty and "
		+"shabby clothes, probably the only thing that it could "
		+"get hold of. This poor soul don't have much to live for. "
		+"The only thing keeping it alive is the thought of not "
		+"ending up in a cell.\n");

	add_prop (LIVE_I_NEVERKNOWN, 1);

	set_stats(({20, 15, 25, 5, 5, 15}));
	set_skill(SS_UNARM_COMBAT, 30);
	set_skill(SS_DEFENCE, 20);

	set_act_time(15);
	add_act("sigh");
	add_act("emote mumbles painfully.");
	add_act("emote ponders about food.");
	add_act("' I don't like this place.");
	set_cact_time(3);
	add_cact("' Yes, end it now. Please.");
	add_cact("emote screams terrified.");
	add_cact("shout Help!");

	set_alignment(random(100)-100);

	set_speak("Leave me alone.");
}
