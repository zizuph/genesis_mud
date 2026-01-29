inherit "/d/Kalad/std/monster";
inherit "/lib/trade";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/money.h"
#define NUM sizeof(MONEY_TYPES)
/* by Korat */
create_monster()
{
   ::create_monster();
   set_name("grell");
   add_name("cook");
   set_race_name("human");
   set_adj("fat");
   set_long("This fat human is the cook here, and he looks like it! "+
      "He is paid to make the food to the hired gladiators, but he "+
      "will probably give you some too if you have the cash needed "+
      "to drop into his huge, greasy hands.\n");
   set_stats(({30,30,50,20,20,50}));
   set_alignment(100);
   set_skill(SS_UNARM_COMBAT,40);
   set_skill(SS_DEFENCE,30);
   set_skill(SS_AWARENESS,30);
   config_default_trade();
   
   add_prop(NPC_M_NO_ACCEPT_GIVE,1); /* won't accept gifts */
      add_prop(CONT_I_WEIGHT, 130000);  /* weights 130 kilo's */
   add_prop(CONT_I_HEIGHT, 175);    /* 175 cm high */
   set_hp(query_max_hp()); /* heal fully */
   set_title("the arena Cook");
   add_speak("I can sell you some soup ... just cost yah 150 coppers.\n");
   add_ask("food","Grell says: You are hungry ehh? Well, it will cost "+
      "you 150 coppers for some soup!\n");
   add_ask(({"fight","arena","games","participate"}),
      "Well, right now the arena is under construction...so no games are held.\n");
   
   set_act_time(2);
   add_act(({"emote throws some more salt into the soup and starts to stir it.",
            "say Are you hungry?",
            "smile hopefully"}));
   add_act(({"ponder more pepper? Nahh more salt!","think"}));
   add_act(({"emote tastes the soup.","shiver"}));
   add_act(({"shout WHERE ARE YOU, YOU DUMB GIANT SOB!!",
            "say its so dumb, soo extremely lazy and sooo bloody big!"}));
   add_act("emote fumes at the thought of the lazy giant.");
   set_cact_time(1);
   add_cact("say Hey...stop this or I'll make a soup out of you!");
   add_cact("say You wretch! I shall report this to Karoth.");
   add_cact("puke");
   add_cact("spit");
   add_cact(({"say More salt?","cackle"}));
   
   set_knight_prestige(-5);
   set_alarm(1.0,0.0,"arm_me");
   trig_new("%w 'attacks' %s", "react_attack");
}

void
arm_me()
{
   object wep, arm;
   seteuid(getuid(TO));
   arm = clone_object("/d/Kalad/common/central/arm/apron");
   arm -> move(TO);
   command("wear all");
   MONEY_MAKE_SC(random(10))->move(TO,1);
}

void
init_living()
{
   add_action("buy_soup","buy");
}

int
buy_soup(string str)
{
   object buy_ob;
   string what, for_c, get_c, change;
   
   int *result, m_res, price;
   if (!str) {
      notify_fail("Buy what?\n");
      return 0;
   }
   if (sscanf(str, "%s with %s and get %s", what, for_c, get_c) != 3)
      if (sscanf(str, "%s with %s", what, for_c) != 2)
      what = str;
   if (what != "soup") {
      notify_fail("All I have is soup. Buy that or nothing!\n");
      return 0;
   }
   buy_ob=clone_object("/d/Kalad/common/central/obj/soup");
   if (!buy_ob) {
      notify_fail("There is none left. Sorry for that...\n");
      return 0;
   }
   price=buy_ob->query_prop(OBJ_I_VALUE);
   result=pay(price,this_player(),for_c,0,0,get_c);
   if (sizeof(result)==1) {
      buy_ob->remove_object();
      return 0;
   }
   if (buy_ob->move(this_player())) {
      write("You drop the " + buy_ob->short() + " on the ground.\n");
      say(QCTNAME(this_player()) + " drops one " + buy_ob->short() +
         " on the ground.\n");
      buy_ob->move(environment(this_player()));
   }
   else {
      write("You get your " + buy_ob->short() + ".\n");
      say(QCTNAME(this_player()) + " buys a " + buy_ob->short() + ".\n");
   }
   write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
   if (change)
      write("You get " + change + " as change.\n");
   return 1;
}

int
react_attack(string who, string dummy){
   if(who){
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_attack",who,dummy);
      return 1;
   }
}
void
return_attack(string who,string dummy){
   object obj;
   int ran;
   if(obj = present(who, environment())){
      if (dummy=="you!\n")
         {
         command("say I'm not that easily beaten!");
         command("say Die then " + obj->query_nonmet_name() + "!");
         command("kill " + (obj->query_real_name()));
         command("smirk");
      }
      else
         {
         command("say hey! No fighting in the mess hall!");
      }
   }
}

int
special_attack(object enemy)
{
   object me;
   mixed* hitresult;
   string how;
   me = this_object();
   if(random(6))
      return 0;
   
   hitresult = enemy->hit_me(50+ random(50), W_SLASH, me, -1);
   how = " angrily";
   if (hitresult[0] > 0)
      how == " ";
   if (hitresult[0] > 10)
      how = " loudly";
   if (hitresult[0] > 20)
      how = " piercingly";
   if (hitresult[0] > 30)
      how = " terrifyingly";
   if (hitresult[0] > 40)
      how = " bonechillingly";
   me -> catch_msg("You throw salt into your enemies wounds!\n" +
      capitalize(enemy->query_pronoun()) + " screams "+ how + " when hit by the salt!.\n");
   enemy -> catch_msg(QCTNAME(me) + " throws salt into your wounds.\n" +
      "You scream"+ how+"!\n");
   tell_watcher(QCTNAME(me) + " throws salt into " + QTNAME(enemy) + "'s wounds!\n" +
      capitalize(enemy->query_pronoun()) + " screams"+
      how + "!.\n", enemy);
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
