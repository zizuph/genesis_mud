#pragma save_binary

inherit "/d/Genesis/ship/captain";
inherit "/lib/trade";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <money.h>
#include "/d/Rhovanion/defs.h"

#define	NUM	sizeof(MONEY_TYPES)

object	ship;
int alarm_intro;

void do_die(object killer)
{
  if (ship)
    ship->stop_ship("The ship stops; someone killed the captain!\n");
  ::do_die(killer);
}

void set_ship(object s)
{
  ship=s;
}

void create_monster()
{
  set_name("Captain Dingle");
  add_name("captain");
  set_title("the Ferry Sailor");
  add_name("dingle");
  set_living_name("dingle");
  set_race_name("human");
  add_adj("old");
  add_adj("stupid");

  set_stats(({ 120, 180, 120, 180, 150, 190 }));
  set_skill(SS_SWIM, 100);

  config_default_trade();

  trig_new("%w 'introduces' %s", "react_introduce");

  set_chat_time(3);
  add_chat("The sea air is good for ya'.\n");
  add_chat("I've run my little ferry for many a'year.\n");
  add_chat("I love to look out across the sea.\n");
}

void init_living()
{
  add_action("buy", "buy");
}

int buy(string str)
{
  object buy_ob;
  string what, for_c, get_c, change;
  int    *result, m_res, price;

  if (!str)
  {
    NF("Buy what?\n");
    return 0;
  }
  if (sscanf(str, "%s with %s and get %s", what, for_c, get_c) != 3)
    if (sscanf(str, "%s with %s", what, for_c) != 2)
      what = str;
  if (what != "ticket")
  {
    NF("I have no such thing for sale.\n");
    return 0;
  }
  buy_ob=clone_object(RHUN_DIR+"ltown_ne/streets/ferry_ticket");
  if (!buy_ob)
  {
    NF("I seem to be out of tickets.\n");
    return 0;
  }
  price=buy_ob->query_prop(OBJ_I_VALUE);
  result=pay(price,this_player(),for_c,0,0,get_c);
  if (sizeof(result)==1)
  {
    buy_ob->remove_object();
    return 0;
  }
  if (buy_ob->move(this_player()))
  {
    write("You drop the " + buy_ob->short() + " on the ground.\n");
    say(QCTNAME(TP) + " drops one " + buy_ob->short() + " on the ground.\n");
    buy_ob->move(environment(TP));
  }
  else
  {
    write("You get your " + buy_ob->short() + ".\n");
    say(QCTNAME(TP) + " buys a " + buy_ob->short() + ".\n");
  }
  write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
  if (change)
    write("You get " + change + " as change.\n");
  return 1;
}

void react_introduce(string person,string who)
{
  if(!alarm_intro)
    alarm_intro=set_alarm(10.0, 0.0, "introduce_me");
}

void introduce_me()
{
  command("introduce myself");
  alarm_intro=0;
}