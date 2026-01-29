inherit "/d/Kalad/std/monster";
inherit "/lib/trade";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#define NUM sizeof(MONEY_TYPES)
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("zebeyana");
   add_name("spider trainer");
   add_name("trainer");
   set_race_name("drow");
   set_adj("tall");
   add_adj("stern");
   set_long("A tall and extremely stern-looking drow female, her features "+
      "are appropriate considering she is in charge of training Lolth's "+
      "pets, spiders.\n");
   set_gender(G_FEMALE);
   set_stats(({75,100,75,25,25,75}));
   set_alignment(-500);
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_DEFENCE,50);
   set_skill(SS_AWARENESS,50);
   set_skill(SS_ANI_HANDL,75);
   config_default_trade();
   add_prop(NPC_M_NO_ACCEPT_GIVE,1); /* won't accept gifts */
   set_title("the Spider Trainer of Undraeth");
   add_ask(({"spider","spiders"}),
      "I hire out spiders to those allied and in worship of Lolth and her "+
      "cause. Would you care to hire one? It costs but one silver.\n");
   
   set_act_time(3);
   add_act("ponder");
   add_act("think the glory of Lolth.");
   
   set_knight_prestige(500);
   add_speak("I hire out spiders to act as messengers, are you interested "+
      "in hiring out one? It costs but one silver.\n");
   add_prop(LIVE_I_SEE_DARK,10);
   add_prop(NPC_I_NO_RUN_AWAY,1);
}

void
init_living()
{
   AA(buy_spider,hire);
   AA(speak,speak);
   AA(speak,chat);
   AA(speak,talk);
}

int
buy_spider(string str)
{
   object buy_ob;
   string what, for_c, get_c, change;
    object meob;
   
   int *result, m_res, price;
   if (!str) {
      notify_fail("Hire what?\n");
      return 0;
   }
    meob = this_player();
   if (sscanf(str, "%s with %s and get %s", what, for_c, get_c) != 3)
      if (sscanf(str, "%s with %s", what, for_c) != 2)
      what = str;
   if(what != "spider")
      {
      NF("I only hire out spiders.\n");
      return 0;
   }
   buy_ob=clone_object(CPASS(drow/npc/post_spider));
   if (!buy_ob) {
      NF("I have no more for you to hire.\n");
      return 0;
   }
   price=12;
   result=pay(price,this_player(),for_c,0,0,get_c);
   if (sizeof(result)==1) {
      buy_ob->remove_object();
      return 0;
   }
    set_this_player(meob);
   if (buy_ob->move(this_player())) {
      write("You drop the " + buy_ob->short() + " on the ground.\n");
      say(QCTNAME(this_player()) + " drops one " + buy_ob->short() +
         " on the ground.\n");
      buy_ob->move(environment(this_player()));
   }
   else {
    set_this_player(meob);
      write("You get your " + buy_ob->short() + ".\n");
      say(QCTNAME(this_player()) + " buys a " + buy_ob->short() + ".\n");
   }
   write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
   if (change)
      write("You get " + change + " as change.\n");
   return 1;
}
