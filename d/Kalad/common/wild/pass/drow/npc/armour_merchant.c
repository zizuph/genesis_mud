inherit "/d/Kalad/std/monster";
inherit "/lib/trade";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#define NUM sizeof(MONEY_TYPES)
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("dipree");
   add_name("merchant");
   set_race_name("drow");
   set_adj("frail-looking");
   add_adj("aged");
   set_long("A frail and withered-looking drow of ancient age, he must "+
      "truly be old, for drow keep their youthful appearance for many "+
      "centuries before they start showing signs of age.\n");
   set_stats(({60,100,65,25,25,50}));
   set_alignment(-250);
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_DEFENCE,50);
   set_skill(SS_TRADING,100);
   set_skill(SS_AWARENESS,100);
   config_default_trade();
   set_title("the Armour Merchant of Undraeth");
   add_speak("I sell the finest in drow armours.\n");
   set_knight_prestige(125);
   set_act_time(3);
   add_act("say For the best in armours, come trade with me.");
   add_act("grin .");
   add_act("say Surely an adventurer like yourself is in need of good armours? There is nothing better than drow armour.\n");
   add_ask(({"goods","stuff","wares","armours","armour"}),
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"+
      "-Armour1 - Black Adamantine Platemail for 4 platinum coins\n"+
      "-Armour2 - Black Adamantine Helm for 1 platinum coin\n"+
      "-Armour3 - Black Adamantine Gauntlets for 2 platinum coins\n"+
      "-Armour4 - Black Adamantine Greaves for 3 platinum coins\n"+
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
   set_default_answer("What are you talking of?\n");
   MONEY_MAKE_GC(random(15))->move(TO,1);
}
void
init_living()
{
   AA(buy_item,buy);
   AA(speak,speak);
   AA(speak,chat);
   AA(speak,talk);
}
int
buy_item(string str)
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
   if(what == "armour1")
      {
      buy_ob = clone_object(CPASS(drow/arm/undraeth_plate));
   }
   else
      if(what == "armour2")
      {
      buy_ob = clone_object(CPASS(drow/arm/undraeth_helm));
   }
   else
      if(what == "armour3")
      {
      buy_ob = clone_object(CPASS(drow/arm/undraeth_gaunt));
   }
   else
      if(what == "armour4")
      {
      buy_ob = clone_object(CPASS(drow/arm/undraeth_greaves));
   }
   else
      {
      NF("I have no such item to sell you.\n");
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