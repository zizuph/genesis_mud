inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("slave");
   set_race_name("goblin");
   set_adj("beaten");
   add_adj("subjugated");
   set_long("The most wretched goblin you've ever laid eyes upon, as a "+
      "rule goblins are nasty and filthy creatures, this pitiful thing before "+
      "you makes such goblins appear as royalty, so wretched is its "+
      "existence.\n");
   set_stats(({25,30,35,5,5,20}));
   set_alignment(-100);
   set_knight_prestige(100);
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
   add_prop(LIVE_I_SEE_DARK,1);
   add_prop(LIVE_I_NEVERKNOWN,1);
}
