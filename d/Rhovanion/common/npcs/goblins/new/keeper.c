inherit "/d/Rhovanion/common/npcs/goblins/goblin";
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "/d/Rhovanion/defs.h"

string *list_introduced = ({ });
string *list_asked_help = ({ });

void create_goblin()
{
  set_base_gob(70);
  set_ran_gob(30);
  set_ran_wep(({ "club" }));
  set_ran_arm(({ "helm" }));
  set_def_arm(({ "mail", "shield" }));
  set_c_chats(({ "I hate intruders like you!",
                 "I will have fresh flesh to feed on!",
                 "Someone go and prepare big pot!",
                 "I will sell loot from your corpse!" }));
  set_chats(({ "What do you want?",
               "I am hungry!!!",
               "You got anything nice to sell?",
               "You want to buy some nice equipment?",
               "You will not steal anything from me!",
               "You have enough money?",
               "I trade with anyone!",
               "Where can I get torches?" /* quest hint */
           }));
  set_name("grumphlin");
  set_title("Shopkeeper");
  set_long("This greedy goblin is willing to trade even with you as "+
           "long as he has some profit.\n");
  remove_prop(LIVE_I_NEVERKNOWN);
  trig_new("%w 'introduces' %s", "react_introduce");
  add_ask(({"help","task","quest","torch","light","torches"}),
            VBFC_ME("answer_help"));
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

int query_introduced(object who)
{
  if(member_array(who->query_real_name(), list_introduced) == -1)
    return 0;
  return 1;
}

string answer_help()
{
  string who_ask = TP->query_real_name();

/*
  if(TP->test_bit("Rhovanion",GROUP,BIT_SOLVED))
  {
    command("whisper "+who_ask+" Please, let the others do the quest now.");
    command("pat "+who_ask);
    return "";
  }
*/
  if(member_array(who_ask, list_introduced) == -1)
  {
    command("say Introduce yourself first! I like to know who am I talking to.");
    command("peer "+who_ask);
    return "";
  }
  if(member_array(who_ask, list_asked_help) != -1)
  {
    command("say "+capitalize(who_ask)+", are you deaf??? I have already "+
            "told you!!!");
    command("pat "+who_ask);
    return "";
  }
  list_asked_help += ({ who_ask }); /* now he has asked first time */
  command("whisper "+who_ask+" Yes, I will have task for you in future.");
  return "";
}
