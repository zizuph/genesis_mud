#pragma strict_types

inherit "/d/Genesis/ship/captain";

#include "../defs.h"
#include <ss_types.h>

public void
create_captain()
{
    set_name("ceraint");
    add_name("captain");
    set_living_name("ceraint");
    set_race_name("sea-elf");
    add_adj("talkative");
// add_adj("sea");
    set_title("the famous captain");

    set_ticket(DOCK_DIR + "faerie/ticket");
    set_price(18);

    set_stats(({ 120, 180, 120, 180, 150, 190 }));
    set_skill(SS_SWIM, 100);
    set_skill(SS_LOC_SENSE, 100);
    refresh_mobile();
}
