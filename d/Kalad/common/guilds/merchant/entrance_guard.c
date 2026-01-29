inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
set_name("erdellar");
add_name("guardsman");
add_name("guard");
   set_race_name("human");
set_adj("stoic");
add_adj("cheerless");
set_short("entrance guardsman");
set_long("He stands here with only a frown to indicate life from within, "+
"as his stern countenance belies any semblance of humanity from him.\n");
set_stats(({100,125,150,75,75,100}));
set_skill(SS_WEP_SWORD,100);
set_skill(SS_BLIND_COMBAT,100);
set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_PARRY,100);
   set_skill(SS_AWARENESS,75);
   set_act_time(6);
add_act("frown");
add_act("glare all");
add_act("peer all");
   set_cact_time(3);
add_cact("shout Filthy wretch! Die like the misbegotten son of a dog you are!!");
add_cact("shout To the foul hellhole of Thanar's realm with you!");
add_cact("shout Feel the piercing touch of my blade!");
add_cact("shout Die you pitiful excuse for a slug!");
add_speak("You cannot enter unless you are a guild member, or if you have "+
"valueable coins you are willing to give me.\n");
   set_knight_prestige(-5);
set_title("the mercenary guardsman of the Merchants Guild");
set_default_answer("The guardsman says: What?\n");
add_ask(({"enter","entrance","coins","coin"}),"The guardsman says: If you "+
"are a member of this guild, then you should know how to greet me, "+
"otherwise you'll need to give me some coins.\n");
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   trig_new("%w 'gives' 'you' 'a' 'gold' %s","react_gold");
   trig_new("%w 'gives' 'you' 'two' 'gold' %s","react_gold");
   trig_new("%w 'gives' 'you' 'three' 'gold' %s","react_gold");
   trig_new("%w 'gives' 'you' 'four' 'gold' %s","react_gold");
}
void
arm_me()
{
   object wep, arm;
   seteuid(getuid(TO));
   arm = clone_object(TRADE(arm/sc_armour));
   arm -> move(TO);
   command("wear all");
   wep = clone_object(TRADE(wep/sc_sword));
   wep -> move(TO);
   command("wield all");
   MONEY_MAKE_GC(random(10))->move(TO,1);
}
void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("gasp");
      command("say Filthy bugger!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
void init_living()
{
   ::init_living();
   add_action("exit","exit");
}
exit()
{
   if(TP->query_alignment() < 1)
      {
      write("You try to leave but are roughly pushed back by the sheriff.\n");
      write("The Sheriff obviously doesn't think you're fit to re-enter the city.\n");
      say(QCTNAME(TP) + " is stopped from leaving by the sheriff.\n");
      return "It looks like you're stuck here...\n";
   }
   write("The sheriff allows you to pass out into the city.\n");
   TP->move_living("out into the city","/d/Kalad/common/trade/tsquare/c3");
   return 1;
}
int
react_gold(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(3.0,0.0,"return_gold",who);
      return 1;
   }
}
void
return_gold(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
write("The guardsman ushers you south, deeper into the guild.\n");
say("The guardsman allows " + QCTNAME(TP) + " to go deeper into the guild.\n");
obj -> move_living("deeper into the guild","/d/Kalad/common/caravan/guild/joinroom");
   }
}
int
special_attack(object enemy)
{
   object me;
   mixed* hitresult;
   string how;
   me = TO;
   if(random(5))
      return 0;
   hitresult = enemy->hit_me(250 + random(500), W_SLASH, me, -1);
   how = " with little harm done";
   if(hitresult[0] > 0)
      how == "";
   if(hitresult[0] > 10)
      how = " slightly, blood trickling down the wound";
   if(hitresult[0] > 20)
      how = " solidly, blood flowing rapidly out the wound";
   if(hitresult[0] > 30)
      how = " deeply, blood gushing out the wound";
   if(hitresult[0] > 40)
      how = " fatally, blood exploding out the wound";
   me->catch_msg("You slash your opponent!\n" +
      capitalize(enemy->query_pronoun()) + " is slashed" + how + ".\n");
   enemy->catch_msg(QCTNAME(me) + " slashes at you viciously!\n"+
      "You are hit" + how + ".\n");
   tell_watcher(QCTNAME(me) + " slashes " + QTNAME(enemy) + " viciously!\n"+
      capitalize(enemy->query_pronoun()) + " is slashed"+
      how + ".\n", enemy);
   if(enemy->query_hp() <= 0)
      enemy->do_die(me);
   return 1;
}