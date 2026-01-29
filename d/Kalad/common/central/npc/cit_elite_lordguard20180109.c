/*
Elite Guard in the Citadel.
MADE BY: Korat
DATE: Feb 14 1995
*/

inherit "/d/Kalad/std/monster";
/* Zignur We use this to make him team properly */
inherit "/d/Kalad/std/group_cluster";
/* Zignur Add a kill logger */
inherit "/d/Kalad/common/kill_logger";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/money.h"
#include <stdproperties.h>

void
create_monster()
{
   ::create_monster();
   switch(random(3))
   {
      case 0:
      set_adj("sturdy");
      add_adj("silent");
      break;
      case 1:
      set_adj("firm");
      add_adj("righteous");
      break;
      case 2:
      set_adj("confident");
      add_adj("valiant");
      break;
      case 3:
      set_adj("courageous");
      add_adj("reliable");
      break;
   }
   set_name("lordguard");
   add_name("guard");
   add_name("_urian_npc");
   set_alignment(0);
   set_knight_prestige(0);
   set_race_name("human");
   set_long("This elite guard is paid by the Lord to protect the Citadel "+
      "from all the ruffians and assassins that roam the city of Kabal. "+
      "He is also assigned the job of stopping anyone who tries to "+
      "bother the High lord himself. "+
      "He looks quite capable of doing his job.\n");
   set_stats(({200,200,200,200,200,200}));
   set_skill(SS_DEFENCE,100);
   set_skill(SS_PARRY,90);
   set_skill(SS_BLIND_COMBAT,70);
   set_skill(SS_AWARENESS,50);
   set_skill(SS_WEP_POLEARM, 100);
   set_act_time(10);
   add_act("emote grips his weapon with steady hands.");
   add_act("emote lets his eyes sweep the room, watching for any signs of trouble.");
   add_act("emote shifts his weight over to the other foot.");
   set_cact_time(3);
   add_cact(({"close door","emote pledges: On my life, I will stop anyone "+
      "trying to disturb the Lord!"}));
   add_cact(({"say Then die! You asked for it.","close door"}));
   add_cact(({"fume","close door","say We should never have let you come this far."}));
   set_title("Elite guard of the Citadel");
   add_prop(NPC_M_NO_ACCEPT_GIVE,1);
   trig_new("'Guardb' 'shouts:' 'we' 'are' 'under' %s","assist_guards");
   trig_new("'Guardc' 'shouts:' 'we' 'are' 'under' %s","assist_guards");
   
   /* Zignur Add him to the team */
   set_prospective_cluster(({"_urian_npc"}));
   
   /* Zignur XP Adjustment */
   set_exp_factor(120);    
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
   MONEY_MAKE_GC(random(5)+2)->move(TO,1);
}

void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("kill " + lower_case(ob->query_real_name()));
   }
}   

assist_guards(string dummy)
{
   float time;
   time = itof(random(20));
   set_alarm(2.0+(time),0.0,"do_assist");
}

do_assist()
{
   switch (random(3))
   {
      case 0:
      command("shout kill them!");
      command("close door");
      break;
      case 1:
      command("emote announces: We are under attack.");
      command("close door");
      break;
      case 2:
      command("shout Do not let them enter the office!");
      command("say They are good men. They will manage to deal with the attackers.");
      command("close door");
      break;
      default:
      command("shout You can deal them alone! We will protect the High Lord.");
      command("close door");
      break;
   }
}

found_player(string who)
{
   string *dummy;
   object ob;
   who = lower_case(who);
   dummy = explode(who,".");
   if (ob = present(dummy[0], environment()))
      {
      command("shout an assassin!");
      command("reveal "+ob->query_real_name());
      command("kill "+ob->query_real_name());
   }
}


int
special_attack(object enemy)
{
   object me;
   mixed* hitresult;
   string how;
   me = this_object();
   if(random(5)>0)
      return 0;
   hitresult = enemy->hit_me(200+random(200), W_IMPALE, me, -1);
   how = " bruised";
   if (hitresult[0] > 0)
      how == "";
   if (hitresult[0] > 10)
      how = " damaged";
   if (hitresult[0] > 20)
      how = " injured";
   if (hitresult[0] > 30)
      how = " mutilated";
   if (hitresult[0] > 40)
      how = " crippled";
   
   me -> catch_msg("You move behind and"+how+" your enemy.\n");
   enemy -> catch_msg(QCTNAME(me)+" managed to get inside your defences "+
      "and"+how+" you with his weapon.\n");
   tell_watcher(QCTNAME(me)+" managed to get inside "+QTNAME(enemy)+
      "'s defences and"+how+" "+enemy->query_objective()+" with "+
      "his weapon.\n",enemy);
   if (enemy->query_hp() <= 0)
      enemy -> do_die(me);
   if (random(2)) TO->command("close door");
   return 1;
}


tell_watcher(string str,object enemy)
{
   object me,*ob;
   int i;
   me = this_object();
   ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
   ob -= ({ enemy });
   for (i=0;i<sizeof(ob);i++)
   if (ob[i]->query_see_blood())
      ob[i]->catch_msg(str);
}

