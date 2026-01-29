#include "default.h"
inherit "/d/Kalad/std/monster";

void
create_kalad_monster()
{
    set_name("slave");
    set_race_name("human");
    set_adj("downtrodden");
    set_long("A filthy-looking human being that looks like he has had the "+
      "very life sucked out of him. Even as you examine him, it doesn't "+
      "seem to register within him that you are here, so out of sync is he "+
      "with the world.\n");
    set_stats(({20, 15, 25, 15, 15, 15}));
    set_alignment(500);
    set_act_time(18);
    add_act("stare");
    add_act("groan");
    add_act("sniff");
    set_knight_prestige(-5);
    add_prop(LIVE_I_NEVERKNOWN, 1);
}
