#include "../local.h"

inherit GOBLIN_BASE;
inherit "/lib/trade";

string *list_introduced = ({ });

void 
create_goblin()
{
  set_base_gob(80);
  set_ran_gob(30);
  set_ran_wep(({ "club" }));
  set_ran_arm(({ "helm" }));
  set_def_arm(({ "mail", "shield" }));
  set_c_chats(({ "I hate intruders like you!",
                 "I will have fresh flesh for my rats!",
                 "I will feed my rats with your corpse!" }));
  set_chats(({ "What do you want?",
               "I am hungry!!!",
               "Do you like rats?",
               "You want to send message?",
               "You have enough money?",
               "I trade with anyone!",
           }));
  config_default_trade();  /* Set up the trading system */
  set_name("drugz");
  set_title("Ratkeeper");
  set_long("This greedy goblin is willing to trade even with you as "+
           "long as he has some profit.\n");
  remove_prop(LIVE_I_NEVERKNOWN);
  remove_prop(NPC_M_NO_ACCEPT_GIVE);
  add_ask(({"price","rat price","rat","price of rat","about price",
            "about rat price","about rat","about price of rat"}),
               VBFC_ME("answer_price"));
}

void
add_introduced(string who)
{
    if (member_array(who, list_introduced) != -1)
        return;
    list_introduced += ({who});
    ::add_introduced(who);
}

int
query_introduced(object who)
{
  if (member_array(who->query_real_name(), list_introduced) == -1)
      return 0;
  return 1;
}

string answer_price()
{
  string who_ask = TP->query_real_name();
  int price;

  if (member_array(who_ask, list_introduced) == -1)
  {
     command("say Introduce yourself first! I like to know who am I "+
	     "talking to.");
     command("peer "+who_ask);
     return "";
  }

  price = ENV(TO)->query_hire_price(TP);
  if(!price)
    command("say "+TP->query_name()+
            ", I am afraid I can't tell you right now the price.");
  else
    command("say For you, "+TP->query_name()+
            ", the price is "+text(split_values(price))+".");
  return "";
}

void init_attack() {}

void enter_inv(object obj, object from)
{
  string ooo, *arr;

  ::enter_inv(obj,from);
  if(!living(from)) return;

  if(obj->query_real_name() == "rat")
  {
    set_alarm(1.0,0.0,"command","say This one is not very fresh.");
    set_alarm(2.0,0.0,"command","drop "+OB_NAME(obj));
    return;
  }
  if (MASTER_OB(obj) == "/std/coins")
  {
    set_alarm(1.0,0.0,"command","say Ohh... How generous!");
    set_alarm(2.0,0.0,"command","grin");
    return;
  }
  set_alarm(1.0,0.0,"command","say I don't want this.");
  set_alarm(2.0,0.0,"command","drop "+OB_NAME(obj));
}

void get_rid_of(object obj){ obj->remove_object(); }
