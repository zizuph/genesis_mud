inherit "/d/Kalad/std/monster";
inherit "/lib/trade";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#define NUM sizeof(MONEY_TYPES)
/* by Antharanos */
void
create_monster()
{
   ::create_monster();
   set_name("yazston");
   add_name("merchant");
   set_race_name("drow");
   set_adj("robust");
   add_adj("powerful-looking");
   set_long("A hulking and brutish drow, he stands nearly six feet in "+
      "height, a virtual giant by drow standards. His well-muscled form "+
      "and stoic facade show signs of a true warrior of Undraeth, cold, "+
      "calculating...and deadly.\n");
   set_stats(({150,125,140,25,25,100}));
   set_alignment(-300);
   set_skill(SS_WEP_AXE,100);
   set_skill(SS_WEP_CLUB,100);
   set_skill(SS_WEP_KNIFE,100);
   set_skill(SS_WEP_POLEARM,100);
   set_skill(SS_WEP_SWORD,100);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_PARRY,100);
   set_skill(SS_BLIND_COMBAT,100);
   set_skill(SS_2H_COMBAT,100);
   set_skill(SS_TRADING,100);
   set_skill(SS_AWARENESS,100);
   config_default_trade();
   set_title("the Weapons Merchant of Undraeth");
   add_speak("I sell many valueable goods.\n");
   set_knight_prestige(150);
   set_act_time(3);
   add_act("say I've got the finest weapons in all of the Dark Dominion, yours for the buying!");
   add_act("grin .");
   add_act("say Oh, let it be known to you that I do know how to use my weapons...");
   add_ask(({"goods","stuff","wares","weapons","weapon","swords","sword","knives","knife","halberds","halberd","polearms","polearm","flails","flail","clubs","club","axes","axe"}),
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"+
      "-Weapon1 - Black Adamantine Sword for 3 platinum coins\n"+
      "-Weapon2 - Black Adamantine Knife for 1 platinum coin\n"+
      "-Weapon3 - Black Adamantine Halberd for 4 platinum coins\n"+
      "-Weapon4 - Black Adamantine Flail for 2 platinum coins\n"+
      "-Weapon5 - Black Adamantine Axe for 2 platinum coins\n"+
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
   set_default_answer("What are you talking of?\n");
   MONEY_MAKE_GC(random(16))->move(TO,1);
}
void
arm_me()
{
   object wep;
   seteuid(getuid(TO));
   wep = clone_object(CPASS(drow/wep/undraeth_axe));
   wep -> move(TO);
   wep = clone_object(CPASS(drow/wep/undraeth_flail));
   wep -> move(TO);
   command("wield all");
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
   if(what == "weapon1")
      {
      buy_ob = clone_object(CPASS(drow/wep/undraeth_sword));
   }
   else
      if(what == "weapon2")
      {
      buy_ob = clone_object(CPASS(drow/wep/undraeth_knife));
   }
   else
      if(what == "weapon3")
      {
      buy_ob = clone_object(CPASS(drow/wep/undraeth_halberd));
   }
   else
      if(what == "weapon4")
      {
      buy_ob = clone_object(CPASS(drow/wep/undraeth_flail));
   }
   else
      if(what == "weapon5")
      {
      buy_ob = clone_object(CPASS(drow/wep/undraeth_axe));
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