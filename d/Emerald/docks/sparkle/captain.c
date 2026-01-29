/* lake/npc/captain2.c cloned by lake/obj/ship2.c */
#pragma strict_types

inherit "/d/Genesis/ship/captain";

#include <ss_types.h>
#include "../defs.h"

//inherit INTRO_FILE;

public void
create_captain()
{
    set_name("blackeye");
    add_name("captain");
    set_living_name("blackeye");
    set_race_name("human");
    add_adj("friendly");
    add_adj("animated");

    set_stats(({ 120, 180, 120, 180, 150, 190 }));
    set_skill(SS_SWIM, 100);
    set_title("the sea navigator");
    set_ticket(DOCK_DIR + "sparkle/ticket");
    set_price(30);
    refresh_mobile();
//  enable_intro();
}
