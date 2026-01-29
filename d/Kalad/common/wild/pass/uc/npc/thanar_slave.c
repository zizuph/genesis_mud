inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("slave");
   set_race_name("dwarf");
   set_adj("brutalized");
   add_adj("tortured");
   set_short("brutalized tortured dwarf");
   set_pshort("brutalized tortured dwarves");
   set_long("A once proud dwarf, this individual has, by the looks of him, been "+
      "severely beaten and tortured. Most shocking of all is the fact that "+
      "this dwarf's beard has been shaved, no doubt by his captors. He is "+
      "truly a wretched creature.\n");
   set_stats(({25,20,30,15,15,25}));
   set_alignment(250);
   set_knight_prestige(-3);
   set_skill(SS_UNARM_COMBAT,30);
   set_skill(SS_DEFENCE,30);
   set_act_time(6);
   add_act("groan");
   add_act("moan");
   add_act("sniff");
   add_act("cry");
   add_act("shiver");
   add_act("cringe");
   set_cact_time(3);
   add_cact("emote looks at you pleadingly, as if to ask you to end his life.");
   add_cact("sob");
   add_prop(LIVE_I_NEVERKNOWN,1);
}
