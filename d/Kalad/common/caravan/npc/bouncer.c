#include "default.h"
inherit "/d/Kalad/std/monster";

void
create_kalad_monster()
{
    set_name("bouncer");
    set_race_name("human");
    set_adj("burly");
    set_long("A big, burly human that looks like he is about to kick you "+
      "right out of this room!\n");
    set_stats(({100, 75, 100, 50, 50, 100}));
    set_alignment(0);
    set_aggressive(1);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_act_time(9);
    add_act("say Get outta here!");
    set_cact_time(9);
    add_cact("say I'll teach you to peek at naked women!");
    set_knight_prestige(0);
}
