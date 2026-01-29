inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("adinirahc");
   add_name("owner");
   set_race_name("drow");
   set_adj("scarred");
   add_adj("leering");
   set_long("A relatively tall drow, dressed in fine black drow silk. His "+
      "otherwise perfectly-chiseled face is ruined by a vicious-looking "+
      "scar that runs from just under his left eye all the way down to "+
      "his jawline. The scar has the effect of giving him a permanent "+
      "leering look.\n");
   set_stats(({125,125,125,25,25,100}));
   set_alignment(-1000);
   set_knight_prestige(1000);
   set_skill(SS_TRADING,100);
   set_act_time(6);
   add_act("emote leers at you.");
   add_act("ponder who will win in the coming war.");
   add_act("scratch chin");
   add_act("grin");
   add_speak("The great war draws near, soon we drow shall rise up and take "+
      "all of the surface world for ourselves, noone will be spared.\n");
   set_default_answer("What was that?\n");
   add_ask(({"war","great war"}),
      "The war of races...it draws very near.\n");
   set_title("the Owner of the Bank of Undraeth");
   add_prop(OBJ_M_NO_ATTACK,"The drow owner dodges out of your reach.\n");
   add_prop(LIVE_I_SEE_DARK,10);
   add_prop(NPC_I_NO_RUN_AWAY,1);
}