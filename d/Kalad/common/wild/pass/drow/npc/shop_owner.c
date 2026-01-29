inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("yasraena");
   add_name("shopkeeper");
   set_race_name("drow");
   set_adj("thin");
   add_adj("gorgeous");
   set_long("A delicately thin, long-legged drow beauty. Her exquisite "+
      "features, framed by flowing white hair present a beauty that few "+
      "surface males of any race could resist. However, her dark-eyed "+
      "gaze and continual smirk are clear indications of her true nature.\n");
   set_stats(({75,100,75,25,25,75}));
   set_gender(G_FEMALE);
   set_alignment(-1200);
   set_knight_prestige(1000);
   set_skill(SS_TRADING,100);
   set_act_time(6);
   add_act("smirk");
   add_act("glare all");
   add_act("grin");
   add_speak("I am not here for idle chatter, just buy or sell here and leave.\n");
   set_default_answer("What was that?\n");
   set_title("the Shopkeeper of the General Shop of Undraeth");
   add_prop(OBJ_M_NO_ATTACK,"The drow shopkeeper dodges out of your reach.\n");
   add_prop(LIVE_I_SEE_DARK,10);
   add_prop(NPC_I_NO_RUN_AWAY,1);
}