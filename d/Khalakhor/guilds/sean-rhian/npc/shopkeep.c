/*
**  Code for shop keepers of buy-only shops (see ..\room\shopbase.c)
**
**  Date       Coder      Action
** -------- -----------   -------------------------------------------
** 4/20/98   Zima         Created
** 08/2021   Tapakah      Refactored
*/

#pragma no_clone
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "shopkeeper.h"

#define TO this_object()
#define TP this_player()
#define ENV(x) environment(x)

// global vars
string arrive_msg="arrives";
 
//
// short query functions
//
string
query_arrive_msg ()
{
  return arrive_msg;
}
 
//
// short set functions
//
void
set_arrive_msg (string s)
{
  arrive_msg = s;
}
 
//
// various replies which can be masked
//
void
reply_buy_not_spec (object buyer)
{
  command("say What is it you want to buy?");
}
void
reply_dont_have (object buyer, string s)
{
  command("say I don't have "+LANG_ART(s)+" "+s+".");
}
void
reply_not_allowed (object buyer, string s)
{
  command("say I am not permitted to sell that to you.");
}
void
reply_sell_fail (object buyer, string s)
{
  command("say I am unable to sell that to you. Do you have enough money?");
}
void
reply_tell_price (object buyer, string s, int price)
{
  command("say The price of "+LANG_ART(s)+" "+s+" is "+price+" coppers.");
}
 
//
// reply - shop invokes replies in the shopkeeper.
//
varargs
void reply (int rn, string s, int num)
{
  object tp = this_player();
  switch(rn) {
  case SKR_BUY_NOT_SPEC:
    reply_buy_not_spec(TP);
    break;
  case SKR_DONT_HAVE:
    reply_dont_have(TP,s);
    break;
  case SKR_NOT_ALLOWED_TO_SELL:
    reply_not_allowed(TP,s);
    break;
  case SKR_SELL_FAIL:
    reply_sell_fail(TP,s);
    break;
  case SKR_TELL_PRICE:
    reply_tell_price(TP,s,num);
    break;
  default:
    command("emote is very confused and seems to have a bug.");
    command("emote strangely mumbles the number "+rn+".");
  }
}
 
//
// do_sale_actions - acts of the sale; mask to make more specific/interesting
//
void
do_sale_actions (string ishort, object tp)
{
  tp->catch_msg("You pay "+QTNAME(TO)+" for "+LANG_ART(ishort)+
                " "+ishort+".\n");
  tell_room(ENV(TO), QCTNAME(tp)+" pays "+QTNAME(TO)+" some money.\n", tp);
}
 
//
// complete_sale - npc completes the approved sale of an item
//
void
complete_sale (string fname, object buyer)
{
  //assumes money has already been subtracted successfully by shop
  object item   = clone_object(fname);
  string ishort = (item->query_name());
 
  item->move(TO);
  do_sale_actions(ishort,buyer);
  if (!command("$give "+ishort+" to "+lower_case(buyer->query_name())))
    command("$drop "+ishort);
}
 
//
// init_shopkeeper
//
void
init_shopkeeper ()
{
}
