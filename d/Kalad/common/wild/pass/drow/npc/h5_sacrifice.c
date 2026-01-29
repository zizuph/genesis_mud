inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
    ::create_monster();
    set_name("sacrifice");
    set_race_name("gnome");
    set_adj("malnourished");
    add_adj("branded");
    add_adj("deep");
    set_long("A half-starved and abused deep gnome, a nasty red scar in the shape "+
      "of a black widow has been branded onto his forehead, marking him as "+
      "a sacrifice to Lolth.\n");
    set_stats(({15,25,25,15,10,15}));
    set_alignment(800);
    set_knight_prestige(-6);
    set_skill(SS_UNARM_COMBAT,30);
    set_skill(SS_DEFENCE,30);
    set_skill(SS_AWARENESS,30);
    set_act_time(6);
    add_act("moan");
    add_act("groan");
    add_act("cough");
    set_cact_time(6);
    add_cact("scream");
    add_cact("cringe");
    add_cact("sniff");
    set_random_move(10);
    add_prop(LIVE_I_NEVERKNOWN,1);
}
