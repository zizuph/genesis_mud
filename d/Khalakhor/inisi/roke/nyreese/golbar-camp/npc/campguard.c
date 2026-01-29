/*
 * campguard.c
 *
 * Used in wild/fb.c wild/fc.c wild/fd.c wild/ff.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 *
 * Updated and moved into new camp by Treacher, Aug 2021
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <macros.h>
#include <ss_types.h>

void
create_monster()
{
    set_race_name("guard");
    set_name("guard");
    set_adj("dirty");
    set_alignment(-10);
    default_config_npc(35);

    set_short("dirty guard");
    set_long("This is a dirty guard guarding the camp of the warriors from " +
             "the evil island Golbar.\n");

    NEVERKNOWN;

    set_skill(SS_DEFENCE, 30);
    set_skill(SS_WEP_POLEARM, 60);
	set_skill(SS_AWARENESS, 30);
}

int
query_knight_prestige()
{
    return 400;
}

void
set_me_up(int act = 1)
{
    if(act)
    {
        set_chat_time(10);
        add_chat("Finally they have sent some reinforcement.");
        add_chat("After all those years in that small camp, we now have the men " +
                 "to build a larger camp. Maybe now we can keep those pesky spies " +
                 "from the mayor out!");
        set_act_time(8);
        add_act("emote performs some routine inspections of the barricade.");
        add_act("emote peers out into the vegetation.");
        add_act("emote looks at the barricade and says: Now this is what I " +
                "call a barricade, not like the one in the old small camp.");
        add_act("emote patrols back and forth outside the camp entrance.");
    }
    
    clone_object(CAMP_WEP + "halberd")->move(TO);
    clone_object(CAMP_ARM + "coat")->move(TO);
    clone_object(CAMP_ARM + "leather-bracelet")->move(TO);

    command("wear all");
    command("wield all");
}
