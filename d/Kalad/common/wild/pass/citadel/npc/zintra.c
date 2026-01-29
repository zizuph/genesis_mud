inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/money.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("stranger");
   set_race_name("stranger");
   set_adj("mysterious");
   set_long("An odd-looking figure. This individual is wrapped in dark, "+
      "concealing clothes in an attempt to fade into the shadows.\n");
   set_stats(({100,150,100,60,60,75}));
   set_alignment(-1000);
   set_skill(SS_WEP_SWORD,90);
   set_skill(SS_2H_COMBAT,90);
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_DEFENCE,90);
   set_skill(SS_PARRY,90);
   set_skill(SS_BLIND_COMBAT,90);
   set_act_time(6);
   add_act("emote carefully looks around.");
   add_act("emote peers suspiciously at you.");
   add_act("emote shifts slightly in the shadows.");
   add_act("emote mumbles something about a terrible darkness in the mountains.");
   add_act("emote whispers softly: Do not venture into the darkness, you may never come back alive.");
   set_cact_time(3);
   add_cact("say Z'ress ulu Quarvalsharess!");
   add_cact("emote looks with unmitigated hatred at you.");
   add_cact("carefully looks around for a possible escape route.");
   set_knight_prestige(900);
   set_default_answer("The stranger just gazes at you balefully.\n");
   add_ask(({"drow"}),"The stranger looks directly at you and says: How "+
      "do you know of us and the atta.....\n"+
      "The stranger elapses into silence.\n");
   add_ask(({"mountains","mountain"}),"The stranger hisses: Ask me no "+
      "more such questions!\n");
   add_ask(({"darkness"}),"The stranger mumbles: A force far greater "+
      "than anything you have ever seen.\n");
   add_ask(({"force"}),"The stranger mumbles: There are rumours...of a "+
      "cave somewhere in the mountains...that is where this terrible danger "+
      "is rumoured to lie. But only a complete fool would venture there.\n");
   add_ask(({"cave"}),"The stranger says something about not everything "+
      "being what it seems.\n");
}
void
arm_me()
{
   object wep, arm;
   seteuid(getuid(TO));
   arm = clone_object("/d/Kalad/common/caravan/arm/strcloak");
   arm -> move(TO);
   arm = clone_object("/d/Kalad/common/caravan/arm/strboots");
   arm -> move(TO);
   command("wear all");
   wep = clone_object("/d/Kalad/common/caravan/wep/strsword");
   wep -> move(TO);
   wep = clone_object("/d/Kalad/common/caravan/wep/strsword");
   wep -> move(TO);
   command("wield all");
   MONEY_MAKE_GC(random(5))->move(TO,1);
}
