#include "default.h"
inherit "/d/Kalad/std/monster";

void
create_kalad_monster()
{
    set_name("slave");
    set_race_name("hobbit");
    set_adj("pitiful");
    set_long("This must be the most pitiful hobbit you have ever seen. "+
      "Unlike most hobbits this one is quite scrawny, instead of being "+
      "plump and fat. The Knights must not feed him very often, or much.\n");
    set_stats(({15, 10, 15, 20, 20, 10}));
    set_alignment(333);
    set_skill(SS_UNARM_COMBAT, 10);
    set_act_time(6);
    add_act("groan");
    add_act("moan");
    add_act("cry");
    add_act("sob");
    add_act("sniff");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_knight_prestige(-3);
}
