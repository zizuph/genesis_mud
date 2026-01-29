inherit "/d/Kalad/std/monster";
inherit "/lib/trade";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/money.h"
#define NUM sizeof(MONEY_TYPES)
void
create_monster()
{
   ::create_monster();
   set_name("brilder");
   add_name("piercer");
   set_living_name("brilder");
   set_race_name("goblin");
   set_adj("mohawk-haired");
   add_adj("repulsive");
   set_long("This is a repulsive goblin. He is holding a big needle "
	+"which he apparently wants to stick through your body.\n");
   set_stats(({50,50,75,40,40,30}));
   set_alignment(-50);
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_DEFENCE,50);
   set_skill(SS_AWARENESS,30);
   heal_hp(15000);
   config_default_trade();
   add_speak("How 'bout I poke a hole in ya?\n");
   set_knight_prestige(50);
   set_act_time(3);
   add_act("emote looks like he wants to poke a hole in your body.");
   add_act("say Let me stick a needle in you or go away!");
   add_act("say My brother is Skeever. He lives in Kabal.");
   set_title("the Body Piercing Wonder");
   add_ask(({"tattoo"}),"The mohawk-haired repulsive goblin says: Look at "+
      "the sign ya idjut!\n");
   set_default_answer("I don't know much about that crap. Get lost!\n");
   MONEY_MAKE_GC(random(3))->move(TO,1);
}
void
init_living()
{
   add_action("buy_pierce1","buy");
   add_action("buy_pierce2","buy");
   add_action("buy_pierce3","buy");
   add_action("buy_pierce4","buy");
   add_action("buy_pierce5","buy");
   add_action("buy_pierce6","buy");
   add_action("buy_pierce7","buy");
   add_action("buy_pierce8","buy");
   add_action("buy_pierce9","buy");
}
int
buy_pierce1(string str)
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
   if (what != "pierce1"){
      notify_fail("I have no such thing to sell you.\n");
      return 0;
   }
   buy_ob=clone_object("/d/Kalad/common/zhent/obj/pierce1");
   if (!buy_ob) {
      notify_fail("I'm too tired to pierce you.\n");
      return 0;
   }
   price=buy_ob->query_prop(OBJ_I_VALUE);
   result=pay(price,this_player(),for_c,0,0,get_c);
   if (sizeof(result)==1) {
      buy_ob->remove_object();
      return 0;
   }
   if (buy_ob->move(this_player())) {
      write("For some reason, the piercer messed up.\n");
      say(QCTNAME(TP) + " tried to get his body pierced done, but the piercer messed up.\n");
      buy_ob->move(environment(this_player()));
   }
   else {
      write("You get yourself pierced.\n");
      say(QCTNAME(TP) + " gets body piercing done!\n");
   }
   write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
   if (change)
      write("You get " + change + " as change.\n");
   return 1;
}
int
buy_pierce2(string str)
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
   if (what != "pierce2"){
      notify_fail("I have no such thing to sell you.\n");
      return 0;
   }
   buy_ob=clone_object("/d/Kalad/common/zhent/obj/pierce2");
   if (!buy_ob) {
      notify_fail("I'm too tired to pierce you.\n");
      return 0;
   }
   price=buy_ob->query_prop(OBJ_I_VALUE);
   result=pay(price,this_player(),for_c,0,0,get_c);
   if (sizeof(result)==1) {
      buy_ob->remove_object();
      return 0;
   }
   if (buy_ob->move(this_player())) {
      write("For some reason, the piercer messed up.\n");
      say(QCTNAME(TP) + " tried to get some body piercing, but the piercer messed up.\n");
      buy_ob->move(environment(this_player()));
   }
   else {
      write("You get your body pierced.\n");
      say(QCTNAME(TP) + " gets some body piercing done!\n");
   }
   write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
   if (change)
      write("You get " + change + " as change.\n");
   return 1;
}
int
buy_pierce3(string str)
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
   if (what != "pierce3"){
      notify_fail("I have no such thing to sell you.\n");
      return 0;
   }
   buy_ob=clone_object("/d/Kalad/common/zhent/obj/pierce3");
   if (!buy_ob) {
      notify_fail("I'm too tired to pierce you.\n");
      return 0;
   }
   price=buy_ob->query_prop(OBJ_I_VALUE);
   result=pay(price,this_player(),for_c,0,0,get_c);
   if (sizeof(result)==1) {
      buy_ob->remove_object();
      return 0;
   }
   if (buy_ob->move(this_player())) {
      write("For some reason, the piercer messed up.\n");
      say(QCTNAME(TP) + " tried to get his body pierced done, but the piercer messed up.\n");
      buy_ob->move(environment(this_player()));
   }
   else {
      write("You get yourself pierced.\n");
      say(QCTNAME(TP) + " gets body piercing done!\n");
   }
   write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
   if (change)
      write("You get " + change + " as change.\n");
   return 1;
}
int
buy_pierce4(string str)
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
   if (what != "pierce4"){
      notify_fail("I have no such thing to sell you.\n");
      return 0;
   }
   buy_ob=clone_object("/d/Kalad/common/zhent/obj/pierce4");
   if (!buy_ob) {
      notify_fail("I'm too tired to pierce you.\n");
      return 0;
   }
   price=buy_ob->query_prop(OBJ_I_VALUE);
   result=pay(price,this_player(),for_c,0,0,get_c);
   if (sizeof(result)==1) {
      buy_ob->remove_object();
      return 0;
   }
   if (buy_ob->move(this_player())) {
      write("For some reason, the piercer messed up.\n");
      say(QCTNAME(TP) + " tried to get his body pierced done, but the piercer messed up.\n");
      buy_ob->move(environment(this_player()));
   }
   else {
      write("You get yourself pierced.\n");
      say(QCTNAME(TP) + " gets body piercing done!\n");
   }
   write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
   if (change)
      write("You get " + change + " as change.\n");
   return 1;
}
int
buy_pierce5(string str)
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
   if (what != "pierce5"){
      notify_fail("I have no such thing to sell you.\n");
      return 0;
   }
   buy_ob=clone_object("/d/Kalad/common/zhent/obj/pierce5");
   if (!buy_ob) {
      notify_fail("I'm too tired to pierce you.\n");
      return 0;
   }
   price=buy_ob->query_prop(OBJ_I_VALUE);
   result=pay(price,this_player(),for_c,0,0,get_c);
   if (sizeof(result)==1) {
      buy_ob->remove_object();
      return 0;
   }
   if (buy_ob->move(this_player())) {
      write("For some reason, the piercer messed up.\n");
      say(QCTNAME(TP) + " tried to get his body pierced done, but the piercer messed up.\n");
      buy_ob->move(environment(this_player()));
   }
   else {
      write("You get yourself pierced.\n");
      say(QCTNAME(TP) + " gets body piercing done!\n");
   }
   write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
   if (change)
      write("You get " + change + " as change.\n");
   return 1;
}
int
buy_pierce6(string str)
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
   if (what != "pierce6"){
      notify_fail("I have no such thing to sell you.\n");
      return 0;
   }
   buy_ob=clone_object("/d/Kalad/common/zhent/obj/pierce6");
   if (!buy_ob) {
      notify_fail("I'm too tired to pierce you.\n");
      return 0;
   }
   price=buy_ob->query_prop(OBJ_I_VALUE);
   result=pay(price,this_player(),for_c,0,0,get_c);
   if (sizeof(result)==1) {
      buy_ob->remove_object();
      return 0;
   }
   if (buy_ob->move(this_player())) {
      write("For some reason, the piercer messed up.\n");
      say(QCTNAME(TP) + " tried to get his body pierced done, but the piercer messed up.\n");
      buy_ob->move(environment(this_player()));
   }
   else {
      write("You get yourself pierced.\n");
      say(QCTNAME(TP) + " gets body piercing done!\n");
   }
   write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
   if (change)
      write("You get " + change + " as change.\n");
   return 1;
}
int
buy_pierce7(string str)
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
   if (what != "pierce7"){
      notify_fail("I have no such thing to sell you.\n");
      return 0;
   }
   buy_ob=clone_object("/d/Kalad/common/zhent/obj/pierce7");
   if (!buy_ob) {
      notify_fail("I'm too tired to pierce you.\n");
      return 0;
   }
   price=buy_ob->query_prop(OBJ_I_VALUE);
   result=pay(price,this_player(),for_c,0,0,get_c);
   if (sizeof(result)==1) {
      buy_ob->remove_object();
      return 0;
   }
   if (buy_ob->move(this_player())) {
      write("For some reason, the piercer messed up.\n");
      say(QCTNAME(TP) + " tried to get his body pierced done, but the piercer messed up.\n");
      buy_ob->move(environment(this_player()));
   }
   else {
      write("You get yourself pierced.\n");
      say(QCTNAME(TP) + " gets body piercing done!\n");
   }
   write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
   if (change)
      write("You get " + change + " as change.\n");
   return 1;
}
int
buy_pierce8(string str)
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
   if (what != "pierce8"){
      notify_fail("I have no such thing to sell you.\n");
      return 0;
   }
   buy_ob=clone_object("/d/Kalad/common/zhent/obj/pierce8");
   if (!buy_ob) {
      notify_fail("I'm too tired to pierce you.\n");
      return 0;
   }
   price=buy_ob->query_prop(OBJ_I_VALUE);
   result=pay(price,this_player(),for_c,0,0,get_c);
   if (sizeof(result)==1) {
      buy_ob->remove_object();
      return 0;
   }
   if (buy_ob->move(this_player())) {
      write("For some reason, the piercer messed up.\n");
      say(QCTNAME(TP) + " tried to get his body pierced done, but the piercer messed up.\n");
      buy_ob->move(environment(this_player()));
   }
   else {
      write("You get yourself pierced.\n");
      say(QCTNAME(TP) + " gets body piercing done!\n");
   }
   write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
   if (change)
      write("You get " + change + " as change.\n");
   return 1;
}
int
buy_pierce9(string str)
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
   if (what != "pierce9"){
      notify_fail("I have no such thing to sell you.\n");
      return 0;
   }
   buy_ob=clone_object("/d/Kalad/common/zhent/obj/pierce9");
   if (!buy_ob) {
      notify_fail("I'm too tired to pierce you.\n");
      return 0;
   }
   price=buy_ob->query_prop(OBJ_I_VALUE);
   result=pay(price,this_player(),for_c,0,0,get_c);
   if (sizeof(result)==1) {
      buy_ob->remove_object();
      return 0;
   }
   if (buy_ob->move(this_player())) {
      write("For some reason, the piercer messed up.\n");
      say(QCTNAME(TP) + " tried to get his body pierced done, but the piercer messed up.\n");
      buy_ob->move(environment(this_player()));
   }
   else {
      write("You get yourself pierced.\n");
      say(QCTNAME(TP) + " gets body piercing done!\n");
   }
   write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
   if (change)
      write("You get " + change + " as change.\n");
   return 1;
}
