/*
Elite Guard in the Citadel.
MADE BY: Korat
DATE: Feb 14 1995
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
   set_name("guardc");
   add_name("guard");
   set_alignment(150);
   set_knight_prestige(-3);
   set_race_name("human");
   set_long("This elite guard is paid by the Lord to protect the Citadel "+
      "from all the ruffians and assassins that roam the city of Kabal. "+
      "He is also assigned the job of stopping anyone who tries to "+
      "bestow themselves upon the Lord without an invitation. "+
      "He looks quite capable of doing his job, but he is now "+
      "off duty.\n");
   set_stats(({80,90,100,50,50,80}));
   set_skill(SS_DEFENCE,90);
   set_skill(SS_PARRY,70);
   set_skill(SS_BLIND_COMBAT,70);
   set_skill(SS_AWARENESS,50);
   set_skill(SS_WEP_POLEARM, 100);
   set_act_time(6);
   add_act("emote stretches himself.");
   add_act("say what are you doing here? A new member "+
      "of the elite guard?");
   add_act("emote scratches his leg.");
   add_act("emote sits himself down on a chair.");
   add_act("yawn");
   add_act("emote burps, and apologizes with a grin.");
   set_cact_time(3);
   add_cact("emote pledges: On my life, I will stop anyone "+
      "trying to disturb the Lord!");
   add_cact("say Then die! You asked for it.");
   add_cact("say Too bad I have to spill your blood on the marble!");
   add_cact(({"fume","say We should never have let you come this far."}));
   add_cact("emote looks abit uneasy without armours.");
   add_cact("emote fumes: Now you have ruined my free time!");
   set_title("Elite guard of the Citadel");
   add_speak("It is a boring job, but they pay good.\n");
   set_default_answer("I don't know anything. Ask someone else.\n");
   add_ask(({"help","task","quest"}),"Maybe you should talk to the cleric here. "+
      "He might be of help to you. Don't even think of asking the Lord though!\n");
   add_prop(NPC_M_NO_ACCEPT_GIVE,1);
   trig_new("'You' 'find' %w","found_player");
   trig_new("'Guardb' 'shouts:' 'we' 'are' 'under' %s","assist_guards");
   trig_new("%w 'attacks' %s","react_attack");
}
void
arm_me()
{
   object arm, wep;
   seteuid(getuid(TO));
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
   time = itof(random(20));
   set_alarm(1.0+(time),0.0,"do_assist");
}

do_assist()
{
   switch (random(3))
   {
      case 0:
      command("shout I am on my way!");
      command("north");
      command("assist guard");
      break;
      case 1:
      command("shout Warn the High Lord!");
      command("north");
      command("assist guard");
      break;
      case 2:
      command("shout We are coming!");
      command("north");
      command("assist guard");
      break;
      default:
      command("shout You deal with it. Im off duty!");
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
      command("say ehhmm, why are you hiding like that?");
      command("reveal "+ob->query_real_name());
      command("poke "+ob->query_real_name());
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

