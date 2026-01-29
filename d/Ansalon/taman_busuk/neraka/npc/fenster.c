/* Carridin, 11 jun 97 */
/* A fencer for a warehouse in the green quarter */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE

void
create_krynn_monster()
{
	set_name("fenster");
	add_name("fence");
	add_name("neraka_fenster");
	set_race_name("hobgoblin");
	set_adj("vindictive");
	add_adj("grudge-bearing");
	set_long("This smelly and generally disgusting person deals in goods of a " +
		"questionable origin. The less law-obiding elements of Neraka " +
		"often trade with him.\n");
	set_stats(({80,70,75,55,55,60}));
	set_skill(SS_DEFENCE, 60);
	set_skill(SS_AWARENESS, 60);
	set_skill(SS_UNARM_COMBAT, 60);
	set_all_hitloc_unarmed(10);
	set_act_time(9);
	add_act("grin .");
	add_act("say Do you want to buy something?");
	add_act("emote greedily eyes your purse.");
	add_act("emote looks around suspiciously.");
	add_act("say What you need, I have.");
	add_act("emote starts to search here for customers.");
	add_act("say Oi! Get a move on!");
	add_act("emote emits a foul stench.");
	set_cact_time(5);
	add_cact("say I'll flip ya. I'll flip ya for real.");
	add_cact("emote is not very happy with his current situation.");

	add_prop(LIVE_I_NEVERKNOWN, 1);
	
}

