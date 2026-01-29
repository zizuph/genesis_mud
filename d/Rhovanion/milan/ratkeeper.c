inherit "/d/Rhovanion/common/npcs/goblins/goblin";
inherit "/lib/trade";

#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "/d/Rhovanion/defs.h"

#define GAVE_RAT  "_player_gave_rhun_rat"

string *list_introduced = ({ });

void create_goblin()
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
  trig_new("%w 'introduces' %s", "react_introduce");
  add_ask(({"price","rat price","rat","price of rat","about price",
            "about rat price","about rat","about price of rat"}),
               VBFC_ME("answer_price"));
}

int react_introduce(string who, string dummy)
{
  who = TP->query_real_name();
  dummy = explode(dummy, " ")[0];
  if((dummy == "himself") || (dummy == "herself") || (dummy == "itself"))
    if(member_array(who, list_introduced) == -1)
      list_introduced += ({ who });
  set_alarm(2.0, 0.0, "return_introduce");
  return 1;
}

void return_introduce()
{
  object *in_room;
  int i, met_me;

  in_room=FILTER_LIVE(all_inventory(ENV()));
  met_me=1;
  for (i = 0; i < sizeof(in_room); i++)
    if ((in_room[i]->query_race_name() == "goblin") &&
        (!in_room[i]->query_met(TO->query_real_name()))) met_me=0;
  if (!met_me) {
     command("introduce me");
     command("bow goblins");
  }
  return;
}

int
query_introduced(object who)
{
  if(member_array(who->query_real_name(), list_introduced) == -1)
    return 0;
  return 1;
}

string answer_price()
{
  string who_ask = TP->query_real_name();
  int price;

  if(member_array(who_ask, list_introduced) == -1)
  {
    command("say Introduce yourself first! I like to know who am I talking to.");
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

void init_attack(){}

void enter_inv(object obj, object from)
{
  string ooo, *arr;

  ::enter_inv(obj,from);
  if(!living(from)) return;

  if(obj->query_prop("_is_rhun_rat"))
  {
    set_alarm(1.0,0.0,"command","say Nice rat! It will multiply beautifully!");
    set_alarm(2.0,0.0,"command","emote puts rat into the cage.");
    if (from->query_prop(GAVE_RAT) != 2)
      set_alarm(3.0, 0.0, "command", "say Now I will hire rats to you.");
    from->add_prop(GAVE_RAT,2);
    set_alarm(0.5,0.0,"get_rid_of",obj);
    return;
  }

  arr = obj->query_adjs();
  if (!arr) arr = ({ });
  ooo = LOW(obj->query_name());
  arr += ({ ooo });
  ooo = implode(arr, " ");

  if(obj->query_real_name() == "rat")
  {
    set_alarm(1.0,0.0,"command","say This one is not very fresh.");
    set_alarm(2.0,0.0,"command","drop "+ooo);
    return;
  }
  if (MASTER_OB(obj) == "/std/coins")
  {
    set_alarm(1.0,0.0,"command","say Ohh... How generous!");
    set_alarm(2.0,0.0,"command","grin");
    return;
  }
  set_alarm(1.0,0.0,"command","say I don't want this.");
  set_alarm(2.0,0.0,"command","drop "+ooo);
}

void get_rid_of(object obj){ obj->remove_object(); }

