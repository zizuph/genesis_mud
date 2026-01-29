#pragma strict_types

inherit "/d/Genesis/ship/captain";

#include <ss_types.h>
#include "../defs.h"

//inherit INTRO_FILE;

public void
create_captain()
{
    set_name("captain");
    set_race_name("elf");
    add_adj("silent");
    add_adj("grey-haired");

    set_long("This is the captain of the ferry.\n");

    set_stats(({ 120, 180, 120, 180, 150, 190 }));
    set_skill(SS_SWIM, 100);
    set_ticket(DOCK_DIR + "north_shore/ticket");
    set_price(0);
    refresh_mobile();
//  enable_intro();
}
