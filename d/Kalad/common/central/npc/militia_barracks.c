/*
   Modified by Zignur 2017-09-14
   
 */
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include  "/sys/money.h"
#include "/sys/filter_funs.h"
int str;
int dex;
int con;

/* by Antharanos */
/* 2017-06-03 Malus: Removed name, added LIVE_I_NEVERKNOWN */ 
void
create_monster()
{
   add_name("militiaman");
   set_race_name("human");
   set_adj("watchful");
   set_long("This ordinary-looking man is carefully scanning his "+
      "surroundings, alert to any possible danger. The patch sewed onto his "+
      "right arm of two crossed swords indicates he is a member of the Kabal "+
      "city militia.\n");
   str = 50 + random(20);
   dex = 50 + random(20);
   con = 50 + random (10);
   /* New stats changed by Zignur 2017-09-14 */   
   set_stats(({70, 70, 70, 70, 70, 70}));
   set_alignment(250);
   set_skill(SS_WEP_SWORD,70);
   set_skill(SS_DEFENCE,50);
   set_skill(SS_PARRY,50);
   /* New skills changed by Zignur 2017-09-14 */
   set_skill(SS_BLIND_COMBAT,50);
   set_act_time(12);
   add_act(({"emote appraises you thoroughly.","say Come on then! Lets fight!!"}));
   add_act(({"say I want to taste your blood.","grin"}));
   add_act(({"fume","say Leave now or prepare to die."}));
   set_cact_time(6);
   add_cact("say You shouldn't have disturbed us. It will mean your death!");
   add_cact(({"say Wanna taste something sweet?",
      "emote licks his sword, tasting "+
      "the blood.","grin"}));
   set_title("the Militiaman");
   add_speak("You're a bit too curious for your own good.\n");
   set_knight_prestige(-3);
   set_aggressive(1);
   add_prop(LIVE_I_NEVERKNOWN, 1);
}
void
arm_me()
{
    
    /* Use Equp instead changed by Zignur 2017-09-14*/
    equip(({
    "/d/Kalad/common/caravan/arm/cmscale",
    "/d/Kalad/common/caravan/wep/cmsword",
      }));   
    command("wield all");
    command("wear all");

    MONEY_MAKE_SC(random(30))->move(this_object(),1);
}
void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("shout No fighting in the streets, " + ob->query_nonmet_name() + "!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
