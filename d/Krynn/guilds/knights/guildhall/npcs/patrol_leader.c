/* Knight patrol leader for the battlements of the new Vingaard, */
/* by Morrigan 1/11/97. (Taken from Teth's Toede)                */

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h";
#include "../../guild.h"

inherit M_FILE
inherit NPCSTD + "vin_knight_base";
inherit AUTO_TEAM

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/d/Krynn/std/patrol";

void
create_knight_npc()
{
    set_level(3);
    set_act_time(7);
    set_pick_up_team(({"squire", "squire", "squire"}));
    set_patrol_time(50);
    set_patrol_path(({ "say Always keep an eye on the gate, it is our "+
	"main defence. If it holds, Vingaard is always safe.", "e", "e",
	"emote inspects the ladder leading downwards.", "n", "n", "emote "+
	"stares gravely towards the east, towards Dargaard.", "say The "+
	"Legend of Soth is one you should learn, and take to heart, for "+
	"his fate is a terrible one, indeed.", "n", "n", "say The mighty "+
	"Vingaard travels all the way to Kalaman. Luckily, we don't have "+
	"to be cautious of attack from there.", "w", "w", "emote stares "+
	"silently towards the High Clerist's Tower, which can barely be "+
	"seen in the distant northwest.", "say The High Clerist's Tower "+
	"has been closed since the days of the Cataclysm, only the Spur "+
	"is open. Strange bit of architecture, that Tower.", "think", "w",
	"w", "emote looks across the plains to the west, then steps to the "+
	"edge of the wall, looking down at the moat.", "say The Keep is "+
	"excellently positioned, from atop its walls, we can see for miles "+
	"and miles in every direction. Vingaard shall never be caught "+
	"by surprise.", "s", "s", "say We hold another fortress southwest "+
	"of here, Thelgaard Keep.", "s", "s", "emote nods thoughtfully"+
	", staring at the Garnet Mountains that rise up in the far "+
	"south.", "say Solanthus lies in the foothills of the Garnet "+
	"Mountains. It, too, is under our control.", "e", "e", "say Now, "+
	"one day when you are Knights, you'll be expected to lead these "+
	"patrols. It is my responsibility to show you how to properly "+
	"patrol, perhaps we'd best go over it again.", "stretch" }));


}

public void
init_living()
{
    if (interactive(TP) && TP->query_prop("_i_attacked_in_vingaard"))
	set_alarm(0.5, 0.0, "attack_func", TP);
    init_team_pickup();
    ::init_living();
}

