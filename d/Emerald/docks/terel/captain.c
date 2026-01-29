/* lake/npc/captain.c cloned by lake/obj/ship.c */
#pragma strict_types

inherit "/d/Genesis/ship/captain";

#include <ss_types.h>
#include <stdproperties.h>
#include "../defs.h"

public void
create_captain()
{
    set_name("crunch");
    add_name("captain");
    set_race_name("human");
    add_adj("compact");
    add_adj("burly");
    set_title("the famous captain");
    add_prop(LIVE_I_NON_REMEMBER, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_ticket(DOCK_DIR + "terel/ticket");
    set_price(18);

    set_stats(({ 120, 180, 120, 180, 150, 190 }));
    set_skill(SS_SWIM, 100);
    refresh_mobile();
}
