inherit "/d/Kalad/std/monster";
inherit "/lib/trade";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#define NUM sizeof(MONEY_TYPES)
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("baltana");
   set_race_name("drow");
   set_adj("tall");
   add_adj("sensuous");
   set_long("A tall, lithe drow female, whose beautifully sculpted and "+
      "toned body is shockingly visible to you. It seems as though the "+
      "only thing covering her sensuous body is her long shock of ivory "+
      "hair, which wraps around her in key points of interest.\n");
   set_gender(G_FEMALE);
   set_stats(({50,90,50,50,50,50}));
   set_alignment(-250);
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_DEFENCE,50);
   set_skill(SS_AWARENESS,50);
   config_default_trade();
   add_prop(NPC_M_NO_ACCEPT_GIVE,1); /* won't accept gifts */
   set_title("the Owner of the Massage Parlour of Undraeth");
   add_ask(({"massage","parlour","pass","web","covering"}),
      "For a single platinum coin, I will let you have a pass to go east "+
      "where you may get the most fabulous massage you've ever had, or will "+
      "ever have. Once there, just type 'massage me' and we'll take "+
      "care of everything. Note however, you may only be massaged once.\n");
   set_act_time(3);
   add_act("smile misc");
   add_act("wink");
   add_act("say Would you care for a massage?\n");
   add_act("say Buy a pass and enjoy the most sensual massage ever.");
   set_knight_prestige(250);
   add_speak("A single platinum coin, and the most glorious massage ever shall "+
      "be yours. Just go east, once you have a massage pass and type "+
      "'massage me' and let us take care of everything. Note however, you "+
      "may only be massaged once.\n");
   add_prop(LIVE_I_SEE_DARK,10);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   MONEY_MAKE_PC(random(1))->move(TO,1);
}

void
init_living()
{
   AA(buy_pass,buy);
   AA(speak,speak);
   AA(speak,chat);
   AA(speak,talk);
}

int
buy_pass(string str)
{
   object buy_ob;
   string what, for_c, get_c, change;
   
   int *result, m_res, price;
   if (!str) {
      NF("Buy what?\n");
      return 0;
   }
   if (sscanf(str, "%s with %s and get %s", what, for_c, get_c) != 3)
      if (sscanf(str, "%s with %s", what, for_c) != 2)
      what = str;
   if(what != "pass")
      {
      NF("I only sell passes.\n");
      return 0;
   }
   buy_ob = clone_object(CPASS(drow/obj/massage_pass));
   if (!buy_ob) {
      NF("I have no more for you to hire.\n");
      return 0;
   }
   price=1728;
   result=pay(price,this_player(),for_c,0,0,get_c);
   if (sizeof(result)==1) {
      buy_ob->remove_object();
      return 0;
   }
   if(buy_ob->move(TP))
      {
      write("You drop the " + buy_ob->short() + " on the ground.\n");
      say(QCTNAME(this_player()) + " drops one " + buy_ob->short() +
         " on the ground.\n");
      buy_ob->move(E(TP));
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