inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("keldain");
   add_name("sheriff-captain");
   add_name("sheriff");
   add_name("captain");
   set_race_name("human");
   set_adj("stern");
   add_adj("unforgiving");
   set_long("This stern-visaged person is the sheriff-captain of the "+
      "city-state of Kabal. Under his stern hand, all miscreants are brought to "+
      "jail, where they stay until so released by him.\n");
   set_stats(({125,150,175,75,75,100}));
   set_skill(SS_WEP_SWORD,100);
   set_skill(SS_UNARM_COMBAT,30);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_PARRY,100);
   set_skill(SS_AWARENESS,75);
   set_skill(SS_BLIND_COMBAT,90);
   set_act_time(3);
   add_act("emote frowns unhappily at you.");
   add_act(({"poke all","say You've been a very naughty visitor."}));
   add_act("say You're going to stay here until you've payed your due "+
      "to the city.\n");
   add_act("say I am the judge and jury in Kabal.\n");
   set_cact_time(3);
   add_cact("say So! You wanna fight me! Come on then!");
   add_cact("say You will die, miscreant!!!");
   add_speak("You must pay your due to the city before I can release you.\n");
   set_knight_prestige(-5);
   set_title("the Sheriff-Captain of Kabal");
   set_default_answer("The sheriff-captain says: What?\n");
   add_ask(({"due","debt","pay","leave","exit"}),"The sheriff-captain says: In order "+
      "for you to leave this jail, you must pay me some gold...unless "+
      "of course you are trustworthy enough for me to release you without "+
    "bond. Only then you may leave before your time is up.\n");
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
}
void
enter_inv(object ob, object from)
{
    ::enter_inv();
    if(from)
    {
        if(ob->short() == "a gold coin" || ob->short() == "two gold coins" ||
        ob->short() == "three gold coins" || ob->short() == "four gold coins")
            set_alarm(2.0,0.0,"return_gold",from);
    }
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

void
return_gold(object obj)
{
   if(present(obj, environment()))
      {
      set_this_player(obj);
      write("The sheriff grins and lets you out the door.\n");
      say("The sheriff grins and lets " + QTNAME(TP) + " out the door.\n");
      obj -> move_living("out the door","/d/Kalad/common/trade/tsquare/c3");
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
   hitresult = enemy->hit_me(300 + random(300), W_SLASH, me, -1);
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
