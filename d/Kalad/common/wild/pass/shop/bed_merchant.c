inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/std/shop_list";
inherit "/d/Kalad/lib/intro";
#define STORE "/d/Kalad/common/wild/pass/shop/bed_sack"
#define SWORD "/d/Kalad/common/wild/pass/wep/bed_m_sword"
#define ABA "/d/Kalad/common/wild/pass/arm/bed_m_aba"
#include "/d/Kalad/defs.h"
/* by Antharanos */
static object store;
void
create_monster()
{
   ::create_monster();
   set_name("salamun");
   add_name("merchant");
   add_name(({"owner","shopkeeper","keeper"}));
   add_name("_wandering_merchant");
   set_race_name("human");
   set_adj("stoic");
   add_adj("weather-beaten");
   set_long("A man that is clearly past his prime, his weather-beaten "+
      "countenance is no doubt due to constant exposure to the searing "+
      "light of the Kaladian sun. It is uncertain from his appearance "+
      "wether or not he is a native of the desert, yet for all intents and "+
      "purposes he is a member of this tribe of Bedellin.\n");
   set_title("of the Iriphawa Tribe and Wealthy Merchant of the Great Kalad Waste");
   set_stats(({125,75,125,90,90,100}));
   set_alignment(500);
   set_skill(SS_WEP_SWORD,100);
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_BLIND_COMBAT,50);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_PARRY,100);
   set_skill(SS_AWARENESS,60);
   set_act_time(3);
   add_act("say I am the wealthiest member of this tribe, aside from the "+
      "sheik, of course.");
   add_act("hmm");
   add_act("ponder");
   add_act("say These warriors are here to keep me safe from hostile outlanders.");
   add_speak("Let's make a deal, outlander.\n");
   set_knight_prestige(-3);
   add_prop(LIVE_I_ALWAYSKNOWN,1);
   add_prop(OBJ_S_WIZINFO, break_string("This merchant carries a special "+
         "sack that is his store-room. Every object he buys ends up in this "+
         "sack and he sells what he has in the sack.", 75) + "\n");
   config_default_trade();
   set_money_give_max(1000);
   seteuid(getuid(TO));
   store = clone_object(STORE);
   store -> move(TO,1);
   set_store_room(STORE);
}
void
arm_shopkeeper()
{
   clone_object(SWORD)->move(TO,1);
   command("wield all");
   clone_object(ABA)->move(TO,1);
   command("wear all");
   MONEY_MAKE_PC(random(10))->move(TO,1);
   MONEY_MAKE_GC(random(50))->move(TO,1);
   MONEY_MAKE_SC(random(100))->move(TO,1);
   MONEY_MAKE_CC(random(200))->move(TO,1);
}
void
init_living()
{
   ::init_living();
   init_shop();
}
int
shop_hook_sold_items(object *item)
{
   write(break_string("You sold " + COMPOSITE_DEAD(item) + ".\n", 75));
   say(QCTNAME(this_player()) + " sold " + QCOMPDEAD + ".\n");
   tell_room(environment(), QCTNAME(this_object()) + " puts the things "+
      "in his sack.\n");
   return 1;
}
int
shop_hook_bought_items(object *arr)
{
   write(break_string("You bought " + COMPOSITE_DEAD(arr) + ".\n", 75));
   say(QCTNAME(this_player()) + " bought " + QCOMPDEAD + ".\n");
   tell_room(environment(), QCTNAME(this_object()) + " rummages around in "+
      "his sack.\n");
   return 1;
}
int
shop_hook_value_no_match(string str)
{
   notify_fail("I have no '" + str + "' in my sack.\n");
}
void
shop_hook_list_empty_store(string str)
{
   notify_fail("I have nothing to sell right now.\n");
}
int
shop_hook_list_no_match(string str)
{
   notify_fail("I have no '" + str + "' in my sack.\n");
}
int
do_read(string str)
{
   return 0;
}
do_die(object killer)
{
   string text;
   if (query_hp() > 0) return;
   
   killer->catch_msg("A large group of bedellin warriors arrives!\n");
   say("A large group of bedellin warriors arrives!\n");
   killer->catch_msg("A bedellin warrior shouts: Foul ulugarr! Now you "+
      "shall pay dearly for your treachery!!\n");
   say("A bedellin warrior shouts: Foul ulugarr! Now you shall pay "+
      "dearly for your treachery!!\n");
   killer->catch_msg("Many bedellin warriors attack you!!!\n");
   say("Many bedellin warriors attack the killer of Salamun!!\n");
   killer->set_hp(1);
   killer->catch_msg("Just as you are about to die, one bedellin warrior "+
      "declares: Let us leave the ulugarr to die in the rocky plains!\n");
   say("Just as the murderer of Salamun is about to die, one bedellin "+
      "warrior declares: Let us leave the ulugarr to die in the rocky plains!\n");
   killer->catch_msg("The other warriors agree and proceed to drag you "+
      "from their camp!!\n");
   say("The other warriors agree and proceed to drag the accused from "+
      "their camp!!\n");
   killer->catch_msg("You are dragged throughout the desert and finally "+
      "left to die in the rocky plains!\n");
   killer->move_living("the camp, dragged by dozens of bedellin warriors","/d/Kalad/common/wild/pass/desert/rock/p10");
   
   /*
   * Added by Korat: this part will send a message to
   * the watchman in centraldistrict.
   */
   
   text = "and "+capitalize(killer->query_real_name())+" has been "+
   "placed in the desert to die for crimes unspeakable.";
   call_other(CENTRAL(high-circle-south),"patrol_text",text);
   
   ::do_die(killer);
}