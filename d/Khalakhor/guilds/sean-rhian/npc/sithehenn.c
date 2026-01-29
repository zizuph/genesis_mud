/* Sithehenn - Sacristan of MacDunn's abbey (shopkeeper)
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           4/20/98    Created
** Tapakah        08/2021    Refactored
*/

#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
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

  add_name("sacristan");
  adj = query_adj(1); /* 1 means return list of all adjectives */
  set_short(adj[0]+" "+adj[1]+" manach");
  set_long(
           "He is a "+adj[0]+" "+adj[1]+" "+(query_race_name())+", his habit "+
           "identifying him as a monastic member of the Order of Sean-Rhian. "+
           "He is the sacristan of the abbey.\n");
  add_prop(NPC_M_NO_ACCEPT_GIVE,"says: I may not accept gifts from you.");
  set_act_time(30);
  add_act("say These are holy items, sold only to saggarts.");
  add_act("say Protect the gifts from here with your life, my brathair.");
  add_act("say If you ask me the price of an item, I can tell you.");
  add_act("say A saggart must be properly vested to leave the abbey.");
  add_act("say You should know the canon laws on vestry before you vest.");
  add_act("emote shines the crystal front of a cabinet.");
  add_act("emote stacks some items in a cabinet.");
  add_act("emote hangs a vestment in a cabinet.");
  add_act("emote straightens some items on a shelf.");
  add_act("emote shines a monstrance and puts it in a cabinet.");
  add_act("emote admires the vestments in the cabinet.");
  add_act("emote takes an inventory of one of the cabinets.");
  add_act("emote prays briefly over the vestments in the cabinet.");
  add_act("emote holds his hands together prayerfully and bows.");
 
  init_shopkeeper();
 
  add_ask(({"items","vestments","tools","accessories","supplies"}),
          "say They are all available for sale to saggarts of the abbey.",1);
  add_ask(({"prices","cost","list","menu","pricelist"}),
          "say Just do askprice of an item, and perhaps I can "+
          "tell you.",1);
  add_ask(({"pendant","for pendant","shamrock pendant","aspirant pendant",
            "for shamrock pendant","for aspirant pendant"}),
          "@@ask_pendant",1);
}
 
string
title (object buyer)
{
    return buyer->query_gender() ? "sistair" : "brathair";
}
 
void
reply_buy_not_spec (object buyer)
{
  command("say What is it you want to buy, "+title(buyer)+"?");
}
void
reply_dont_have (object buyer, string s)
{
  command("say I do not have "+LANG_ART(s)+" "+s+", "+title(buyer)+".");
}
void
reply_not_allowed (object buyer, string s)
{
  command("say I am afraid I am not permitted to sell that, "+title(buyer)+
          ".");
}
void reply_sell_fail (object buyer, string s)
{
  command("say You do not seem to be able to pay for it, "+title(buyer)+
          ".");
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
  command("emote takes "+art+" "+ishort+" from a cabinet.");
  tp->catch_msg("You pay "+QTNAME(TO)+" for "+art+" "+ishort+".\n");
  tell_room(ENV(TO), QCTNAME(tp)+" pays "+QTNAME(TO)+" some money.\n", tp);
}
 
string
ask_pendant ()
{
  object pen;
  if (!(TP->is_saggart()))
    return "say Who are you to ask such of me!";
  if ((TP->query_sr_level())<SRLVL_SEARM1)
    return "say You may not invest an aspirant, "+title(TP)+". I may "+
      "not give you one.";
  pen=clone_object(SR_ARMOUR+"shampend");
  pen->move(TO);
  command("give pendant to "+(lower_case(TP->query_name())));
  command("drop pendant");
  command("say There you are, "+title(TP)+".");
  return "say Luaidh bi Ardaugh! The faith grows!";
}
