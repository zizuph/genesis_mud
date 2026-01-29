inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("slave");
   set_race_name("ogre");
   set_adj("beaten");
   add_adj("whipped");
   set_long("The most wretched ogre you've ever had the misfortune of laying eyes on, as a "+
      "general rule ogres are nasty and disgusting creatures, this pitiful thing before "+
      "you makes such ogres appear as nobility, so wretched is its "+
      "existence.\n");
   set_stats(({75,60,80,15,15,80}));
   set_alignment(-100);
   set_knight_prestige(100);
   set_skill(SS_UNARM_COMBAT,40);
   set_skill(SS_DEFENCE,40);
   set_skill(SS_AWARENESS,40);
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
