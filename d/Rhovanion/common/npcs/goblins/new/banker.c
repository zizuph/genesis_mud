inherit "/d/Rhovanion/common/npcs/goblins/goblin";

#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "/d/Rhovanion/defs.h"

string *list_introduced = ({ });

void create_goblin()
{
  set_base_gob(120);
  set_ran_gob(30);
  set_ran_wep(({ "club" }));
  set_ran_arm(({ "helm" }));
  set_def_arm(({ "mail","shield" }));
  set_c_chats(({ "I hate intruders like you!",
                 "I will have fresh flesh to feed on!",
                 "Someone go and prepare big pot!",
                 "I will sell loot from your corpse!" })
  set_chats(({ "What do you want?",
               "I am hungry!!!",
               "You got lot of money?",
               "You will not steal anything from me!",
               "You have enough money?" }));

  set_name("crotch");
  set_title("Banker");
  set_long("This greedy goblin is willing to trade even with you as "+
           "long as he has some profit.\n");
  remove_prop(LIVE_I_NEVERKNOWN);
  trig_new("%w 'introduces' %s", "react_introduce");
  add_ask("instructions", VBFC_ME("answer_help"));
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
  if(!met_me)
  {
    command("introduce me");
    command("bow goblins");
  }
  return;
}

int query_introduced(object who)
{
  if(member_array(who->query_real_name(), list_introduced) == -1)
    return 0;
  return 1;
}

string answer_help()
{
  string who_ask = TP->query_real_name();

  if(member_array(who_ask, list_introduced) == -1)
  {
    command("say Introduce yourself first! I like to know who am I talking to.");
    command("peer "+who_ask);
    return "";
  }
  command("say Yes, I can relieve you of the burden of heavy coins.");
  command("smile greedily");
  command("say You can change platinum and gold for copper...");
  command("say then change 100 platinum for copper...");
  command("say maybe even change platinum for 10 silver...");
  command("hmm");
  command("scratch");
  command("say Yes...");
  command("say you can do test change 100 platinum for copper too!");
  command("poke "+who_ask);
  command("think");
  command("scratch");
  command("peer "+who_ask);
  command("say O.K. I tell you...");
  command("say You can even minimize coins!");
  command("say But I don't like to do this very much.");
  command("grin");
  command("say I think that's all...");
  command("smile "+who_ask);
  command("think");
  command("oops");
  command("say I forgot the most important part!!!");
  command("say Of course I take some small fee for my service.");
  command("giggle greedily");
  return "";
}

