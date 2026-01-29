inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
    ::create_monster();
    set_name("slave");
    set_race_name("human");
    set_adj("tortured");
    add_adj("half-starved");
    set_long("A half-naked and clearly emaciated human. Apparently "+
      "the drow care little for the conditions of their slaves, for this man "+
      "appears as if he may die at any moment, so terrible is his health.\n");
    set_stats(({20,20,20,15,15,20}));
    set_alignment(500);
    set_knight_prestige(-1);
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
    add_prop(LIVE_I_NEVERKNOWN,1);
}
