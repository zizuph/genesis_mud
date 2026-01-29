/*
Elite Guard in the Citadel.
MADE BY: Korat
DATE: Feb 14 1995
Modified by Zignur 2017-09-15
*/

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
   set_name("guardb");
   add_name("guard");
   set_alignment(150);
   set_knight_prestige(-3);
   set_race_name("human");
   set_long("This elite guard is paid by the Lord to protect the Citadel "+
      "from all the ruffians and assassins that roam the city of Kabal. "+
      "He is also assigned the job of stopping anyone who tries to "+
      "bestow themselves upon the Lord without an invitation. "+
      "He looks quite capable of doing his job.\n");
   
   /* New stats changed by Zignur 2017-09-15 */
   set_stats(({100,100,100,100,100,100}));
   /* New skills changed by Zignur 2017-09-15 */
   set_skill(SS_DEFENCE,80);
   set_skill(SS_PARRY,70);
   set_skill(SS_BLIND_COMBAT,70);
   set_skill(SS_AWARENESS,50);
   set_skill(SS_WEP_POLEARM, 80);
   set_act_time(6);
   add_act("search here");
   add_act("emote grips his weapon with steady hands.");
   add_act("emote lets his eyes sweep the room, watching for any signs of trouble.");
   add_act("emote adjusts his armour.");
   add_act("emote shifts his weight over to the other foot.");
   set_cact_time(3);
   add_cact("emote pledges: On my life, I will stop anyone "+
      "trying to disturb the Lord!");
   add_cact("shout We are under attack!!! Warn the High Lord!");
   add_cact("say Too bad I have to spill your blood on the marble!");
   add_cact(({"fume","say We should never have let you come this far."}));
   set_title("Elite guard of the Citadel");
   add_speak("It is a boring job, but they pay good.\n");
   set_default_answer("I don't know anything. Ask someone else.\n");
   add_ask(({"help","task","quest"}),"Maybe you should talk to the cleric here. "+
      "He might be of help to you. Don't even think of asking the Lord though!\n");
   add_prop(NPC_M_NO_ACCEPT_GIVE,1);
   trig_new("'You' 'find' %w","found_player");
   trig_new("'Guarda' 'shouts:' 'we' 'are' 'under' %s","assist_guards");
   trig_new("%w 'attacks' %s","react_attack");
   
   /* XP Adjustment changed by Zignur 2017-09-15 */
   set_exp_factor(120);
}
void
arm_me()
{    
    /* Use Equp instead changed by Zignur 2017-09-15*/
    equip(({
        "/d/Kalad/common/central/arm/cit_plate",
        "/d/Kalad/common/central/arm/cit_helm",
        "/d/Kalad/common/central/arm/cit_boots",
        "/d/Kalad/common/central/wep/cit_elite_weapon",
      }));   
    command("wield all");
    command("wear all");
    MONEY_MAKE_GC(random(5)+2)->move(TO,1);
}

void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("fume");
      command("say I will kill you now!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}   

react_attack(string who,string what)
{
   set_alarm(2.0,0.0,"assist_him");
}

assist_him()
{
   command("assist");
   command("assist guardc");
}

assist_guards(string dummy)
{
   float time;
   time = itof(random(6));
   set_alarm(1.0+(time),0.0,"do_assist");
}

do_assist()
{
   switch (random(3))
   {
      case 0:
      command("shout I am on my way!");
      command("east");
      command("assist guard");
      break;
      case 1:
      command("shout Warn the High Lord!");
      command("east");
      command("assist guard");
      break;
      case 2:
      command("shout We are coming!");
      command("east");
      command("assist guard");
      break;
      default:
      command("shout You can deal them alone! We will protect the High Lord.");
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
   if (random(6)>0)
      return 0;
   hitresult = enemy->hit_me(150+random(200), W_IMPALE, me , -1);
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

