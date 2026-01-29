#include "default.h"
inherit "/d/Kalad/std/monster";

void
create_kalad_monster()
{
    set_name("slave");
    set_race_name("gnome");
    set_adj("pitiful");
    set_long("This must be the most pitiful gnome you have ever seen. "+
      "Unlike most gnomes this one is quiet and filled with despair, quite "+
      "a contrast to the annoyingly cheerful gnomes that are always "+
      "jabbering about one thing or another. It must make the Knights very "+
      "happy to see this creature unhappy.\n");
    set_stats(({15, 15, 10, 25, 10, 15}));
    set_alignment(333);
    set_skill(SS_UNARM_COMBAT, 15);
    set_act_time(6);
    add_act("groan");
    add_act("moan");
    add_act("cry");
    add_act("sob");
    add_act("sniff");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_knight_prestige(-3);
}
