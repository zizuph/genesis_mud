/*
* Created by: Luther
* Date: 11 August 2001
*
* File: /d/Cirath/tyr/npc/jailpris.c
* Comments: Slave prisoner in the Jail of Tyr 
*           edited from jailslav.c
*/

inherit "/d/Cirath/std/monster.c";
#include "defs.h"

#define RNDRACE ({"human", "human", "human", "half-elf", "dwarf", "dwarf", "half-giant", "mul", "elf", "elf"})
#define RNDADJ ({"starving", "scarred", "withdrawn", "angry", "pathetic", "frightened", "weary", "old", "sullen", "dirty"})

void
create_monster()
{
	add_adj("prisoned");
	set_adj(RNDADJ[random(10)]);
	set_race_name(RNDRACE[random(10)]);
	set_name("prisoner");
	set_gender(random(2));
	set_long("This prisoner looks pathetic. The prisoner wears dirty and "
		+"shabby clothes, probably the only thing that it had before "
		+"coming here. This poor soul doesn't have much to live for. "
		+"The only thing keeping it alive is the thought of being free "
		+"one day and leaving this god forsaken place.\n");

	add_prop (LIVE_I_NEVERKNOWN, 1);

	set_stats(({15, 10, 20, 5, 5, 10}));
	set_skill(SS_UNARM_COMBAT, 30);
	set_skill(SS_DEFENCE, 20);

	set_act_time(15);
	add_act("sigh");
	add_act("emote mumbles painfully.");
	add_act("emote ponders when the leftovers will arrive.");
	add_act("' I don't like being a prisoner.");
	add_act("' They have the wrong person, I didn't do it!");
	add_act("shout No! No! Please no more torture!");
	add_act("emote screams painfully.");
	add_act("cry");
	set_cact_time(3);
	add_cact("' Please. It wasn't me!");
	add_cact("' Please. Stop hurting me.");
	add_cact("emote screams terrified.");
	add_cact("shout Help!");

	set_alignment(random(100)-100);

	set_speak("Leave me alone, I am innocent.");
}
