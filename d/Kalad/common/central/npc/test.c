/*
Officer in the Citadel.
MADE BY: Korat
DATE: Feb 14 1995
*/

inherit "/d/Kalad/std/mon";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/money.h"
#include <stdproperties.h>
#include "/d/Kalad/sys/outlaw.h"

void
create_monster()
{
   ::create_monster();
   switch(random(10))
   {
      case 0:
      set_name("grock");
      break;
      case 1:
      set_name("cirros");
      break;
      case 2:
      set_name("karleen");
      break;
      case 3:
      set_name("hamal");
      break;
      case 4:
      set_name("pocter");
      break;
      case 5:
      set_name("saron");
      break;
      case 6:
      set_name("yrm");
      break;
      case 7:
      set_name("procter");
      break;
      case 8:
      set_name("laig");
      break;
      case 9:
      set_name("kromm");
      break;
      default:
      set_name("queinn");
      break;
   }
   add_name("citadel officer");
   set_adj("firm");
   add_adj("officer");
   set_alignment(150);
   set_knight_prestige(-2);
   set_race_name("human");
   set_long("This officer is paid by the Lord to protect the Citadel "+
      "from all the ruffains and assasins that roam the city of Kabal. "+
      "Assigned to him is also the job of commanding the citadel guards. "+
      "He looks quite capable of doing his job.\n");
   set_stats(({80,100,90,60,60,80}));
   set_skill(SS_DEFENCE,90);
   set_skill(SS_PARRY,80);
   set_skill(SS_BLIND_COMBAT,70);
   set_skill(SS_AWARENESS,60);
   set_skill(SS_WEP_POLEARM, 100);
   set_act_time(3);
   add_act(({"say Be sure to make no trouble in the Citadel!","emote "+
            "smiles confidently at you."}));
   add_act("emote grips his weapon with steady hands.");
   add_act(({"bow .","say You are welcome as long as you behave."}));
   add_act("emote looks with irritation in the direction of the bronze bell.");
   add_act("say That bell keeps me awake all the time. Even when i try to sleep!");
   set_cact_time(1);
   add_cact("say Then die! You asked for it.");
   add_cact("say Too bad I have to spill your blood on the marble!");
   add_cact(({"fume","say We should never have let you come this far."}));
   set_title("Officer of the Citadel");
   add_speak("It is a boring job, but they pay good.\n");
   set_default_answer("I don't know anything. Ask someone else.\n");
   add_ask(({"help","task","quest"}),"Maybe you should talk to the cleric. He "+
      "might be of help to you. Don't ask the Lord himself though!\n");
   add_prop(NPC_M_NO_ACCEPT_GIVE,1);
}
void
arm_me()
{
   object arm, wep;
   seteuid(getuid(TO));
   arm = clone_object("/d/Kalad/common/central/arm/cit_plate");
   arm -> move(TO);
   arm = clone_object("/d/Kalad/common/central/arm/cit_helm");
   arm -> move(TO);
   arm = clone_object("/d/Kalad/common/central/arm/cit_boots");
   arm -> move(TO);
   command("wear all");
   wep = clone_object("/d/Kalad/common/central/wep/cit_elite_weapon");
   wep -> move(TO);
   command("wield all");
   MONEY_MAKE_GC(random(5)+4)->move(TO,1);
}

init_living()
{
   if(IS_OUTLAW(TP)) react_outlaw(TP);
   ::init_living();
}
void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("fume");
      command("say You fool!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}   