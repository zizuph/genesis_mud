inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
/* by mhyrkhaan */

void
create_monster()
{
   ::create_monster();
   set_name("gregor");
   add_name("owner");
   set_race_name("dwarf");
   set_adj("muscular");
   add_adj("tired");
   set_long("This is the owner of the Alliance Supply shop, he will "+
   "help you buy and seel items. He is muscular, and tired looking.\n");
   set_stats(({150,150,150,150,150,200}));
   set_title("Bloodhammer, The retired Rider of the Dark Alliance");
   set_skill(SS_WEP_SWORD,50);
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_DEFENCE,90);
   set_skill(SS_PARRY,90);
   add_prop(LIVE_I_SEE_DARK,5);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   add_prop(CONT_I_WEIGHT,100000);
   add_prop(CONT_I_VOLUME,100000);
   set_act_time(10);
   add_act("emote peers around.");
   add_act("say so how is the looting going?.");
   set_act_time(5);
   add_act("emote rubs his shoulder tiredly.");
   add_act("emote yawns, leaning against the counter.");
   add_act("emote stretches.");
}