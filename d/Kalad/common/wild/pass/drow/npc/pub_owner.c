inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("ryltar");
   add_name("owner");
   add_name("bartender");
   set_race_name("drow");
   set_adj("lean");
   add_adj("cruel");
   set_long("A rather plain-looking drow, distinguished only by the "+
      "perpetually cruel look plastered onto his face. He appears to be "+
      "the owner of this establishment, judging from the way he gazes at "+
      "you as though you were property.\n");
   set_stats(({100,150,100,25,25,100}));
   set_alignment(-750);
   set_knight_prestige(750);
   set_skill(SS_WEP_POLEARM,90);
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_BLIND_COMBAT,50);
   set_skill(SS_DEFENCE,90);
   set_skill(SS_PARRY,90);
   set_skill(SS_AWARENESS,60);
   set_act_time(6);
   add_act("emote sneers.");
   add_act("ponder who will win in the coming war");
   add_act("scratch chin");
   add_act("grin");
   add_act("snarl all");
   add_act("growl");
   add_speak("The time of the great war is almost at hand. When it "+
      "arrives all of the drow shall venture forth to extinguish the life from "+
      "the lands of terrible light.\n");
   set_default_answer("What was that?\n");
   add_ask(({"war","great war"}),
      "The war of races...it draws very near.\n");
   set_title("the Owner and Bartender of the Gaudy Drow drinking pit");
   add_prop(NPC_I_NO_RUN_AWAY,1);
   add_prop(LIVE_I_SEE_DARK,10);
}
arm_me()
{
   object item;
   seteuid(getuid(TO));
   item = clone_object(CPASS(wep/dw_halb));
   item -> move(TO);
   command("wield all");
   MONEY_MAKE_GC(random(10))->move(TO,1);
}