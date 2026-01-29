/*
Guard in the Citadel.
MADE BY: Korat
DATE: Feb 14 1995
*/
/* 2017-06-04 Malus: Removed names and set LIVE_I_NEVERKNOWN */ 
inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/money.h"
#include <stdproperties.h>

void
create_monster()
{
   ::create_monster();
   switch(random(2))
   {
      case 0:
      set_adj("strong");
      add_adj("righteous");
      set_alignment(150);
      set_knight_prestige(-2);
      break;
      case 1:
      set_adj("strong");
      add_adj("competent");
      set_alignment(0);
      set_knight_prestige(0);
      break;
      default:
      set_adj("strong");
      add_adj("naughty");
      set_alignment(-150);
      set_knight_prestige(50);
      break;
   }
   add_name("citadel guard");
   add_name("guard");
   set_race_name("human");
   set_long("This man is paid by the Lord to protect the Citadel "+
      "from all the ruffians and assassins that roam the city of Kabal. "+
      "He looks quite capable of doing his job.\n");
   set_stats(({60,70,70,50,50,80}));
   set_skill(SS_DEFENCE,70);
   set_skill(SS_PARRY,50);
   set_skill(SS_BLIND_COMBAT,50);
   set_skill(SS_AWARENESS,50);
   set_skill(SS_WEP_POLEARM, 90);
   set_act_time(6);
   add_act(({"say Be sure to make no trouble in the Citadel!","emote "+
            "smiles confidently at you."}));
   add_act("emote grips his weapon with steady hands.");
   add_act(({"bow .","say You are welcome as long as you behave."}));
   add_act("emote looks with irritation in the direction of the bronze bell.");
   add_act("say That bell keeps me awake all the time. Even when I try to sleep!");
   set_cact_time(1);
   add_cact("say Then die! You asked for it.");
   add_cact("say Too bad I have to spill your blood on the marble!");
   add_cact(({"fume","say We should never have let you come this far."}));
   set_title("Guard of the Citadel");
   add_speak("It is a boring job, but they pay good.\n");
   set_default_answer("I don't know anything. Ask someone else.\n");
   add_ask(({"help","task","quest"}),"Maybe you should talk to the cleric here. "+
      "He might be of help to you. Don't even think of asking the Lord though!\n");
   add_prop(NPC_M_NO_ACCEPT_GIVE,1);
   add_prop(LIVE_I_NEVERKNOWN, 1);
}
void
arm_me()
{
   object arm, wep;
   seteuid(getuid(TO));
   arm = clone_object("/d/Kalad/common/central/arm/cit_chain");
   arm->move(TO);
   arm = clone_object("/d/Kalad/common/central/arm/cit_helm");
   arm->move(TO);
   command("wear all");
   wep = clone_object("/d/Kalad/common/central/wep/cit_guard_weapon");
   wep->move(TO);
   command("wield all");
   MONEY_MAKE_SC(random(30)+10)->move(TO,1);
}

void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("gasp");
      command("say How dare you!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}   
