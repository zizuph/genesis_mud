/* Seandlar - candler maker of MacDunn Priory
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/5/98     Created
** Tapakah        08/2021    Refactored
*/

#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "defs.h"

inherit  SR_NPC+"monkbase";
inherit  SR_NPC+"shopkeep";
 
#define  VEST (({"robe","cincture","tonsure","scapular"}))
 
void
arm_me ()
{
  vest_me(VEST);
}
 
void
create_khalakhor_human ()
{
  int     stat=(40+random(60));
  string* adj;

  setup_base_manach(stat);
  ::create_khalakhor_human();
  adj = query_adj(1); /* 1 means return list of all adjectives */
  set_long(
           "He is a "+adj[0]+" "+adj[1]+" "+(query_race_name())+", his habit "+
           "identifying him as a monastic member of the Order of Sean-Rhian. "+
           "He is the candle maker of the abbey.\n");
  add_prop(NPC_M_NO_ACCEPT_GIVE," says: I may not take gifts from ye.\n");
  set_act_time(30);
  add_act("emote wipes the shelves with a dust rag.");
  add_act("say A pure candle is the seat of the heart of the flame.");
  add_act("emote cleans wax from the candlewraught.");
  add_act("emote admires the ornate candles on the shelves.");
  add_act("emote scrapes wax off his fingers.");
  add_act("emote places some new beeswax candles on the shelf.");
  add_act("emote eyes the candlewraught proudly.");
  add_act("emote bows momentarily for a short prayer.");
  init_shopkeeper();
 
  add_ask(({"about candle","about candles","ornate candle","ornate candles",
            "about ornate candle","about ornate candles"}),
          "say We've the finest candles in MacDunn. Only those listed on the "+
          "sign are for sale.",1);
  add_ask(({"candle","candles","buy","buy candle","buy candles"}),
          "say If ye'd like a candle, just 'buy candle'.",1);
  add_ask(({"make candle","to make candle"}),
          "say I'm done makin' candles for today. Ye can make one yerself.",1);
  add_ask(({"how make candle","how to make candle","how to make a candle",
            "how to use candlewraught","how use candlewraught"}),
          "say Thar's instructions on the frame.",1);
  add_ask(({"cost","about cost","price","about price","pricelist"}),
          "say You may do askprice of an item, and perhaps I can tell you.",1);
  add_ask("candlewraught",
          "say It's a machine to make candles. Ye may use it if ye wish.",1);
  add_ask(({"color","colors","powder","scent","scents","herbal powders",
            "dye"}), "say Ye can add color and scent to the candles with "+
          "herbal powders.", 1);
  add_ask(({"for powder","for powders","for herbs","for color",
            "for colors","for dye"}),
          "say I do no' have any that I can sell ye.",1);
  add_ask(({"honeycomb","honeycombs","for honeycomb","for honeycombs",
            "wax","for wax","comb","combs","beeswax","for beeswax"}),
          "say I do no' have any honeycombs I can sell ye. Ye'll have to "+
          "rob the bees yerself",1);
  add_ask(({"wick","wicks","for wick","for wicks"}),
          "say We make wicks from wool, but I do no' have any extra for ye.",1);
  add_ask(({"task","job","quest","tour","for task","for job","for quest",
            "for tour"}),
          "say I have nothing for ye to do, but I believe Abbot Semion has "+
          "a task for someone involving candles.",1);
  add_ask(({"bees","bee","hive","sheep"}),
          "say There aren't any around here. Maybe in the countryside.",1);
  add_ask("wool","say Why it comes from sheep, of course.",1);
  add_ask(({"mortar","pestle","mortar and pestle"}),
          "say I do 'no have one.",1);
  add_ask(({"key","for key"}),
          "say I do 'no have a key to anything.",1);
}
 
void
reply_buy_not_spec (object buyer)
{
  command("say What is it you want to buy, a candle?");
}
void
reply_dont_have (object buyer, string s)
{
  command("say I do not sell "+LANG_ART(s)+" "+s+" here.");
}
void
reply_not_allowed (object buyer, string s)
{
  command("say I am afraid I am not permitted to sell that to you.");
}
void
reply_sell_fail (object buyer, string s)
{
  command("say You do not seem to be able to pay for it.");
  command("say Are you sure you have enough money?");
}
void
reply_tell_price (object buyer, string s, int price)
{
  command("say The price of "+LANG_ART(s)+" "+s+" is "+price+" coppers.");
}
 
void
do_sale_actions (string ishort, object tp)
{
  string art=LANG_ART(ishort);
  tp->catch_msg("You pay "+QTNAME(TO)+" for "+art+" "+ishort+".\n");
  tell_room(ENV(TO), QCTNAME(tp)+" pays "+QTNAME(TO)+" some money.\n", tp);
  command("emote takes "+art+" "+ishort+" from behind the counter.");
}
