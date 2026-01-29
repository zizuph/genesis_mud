inherit "/d/Rhovanion/common/npcs/goblins/goblin";
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "/d/Rhovanion/defs.h"

#define GROUP     0
#define BIT       11 
#define RATS      "_brought_rats"
#define LOG_FILE  "/d/Rhovanion/log/rat_task"
/* reward = number of rats * 15 (max 300) */

string *list_introduced = ({ });
string *list_asked_help = ({ });

void create_goblin()
{
  set_base_gob(40);
  set_ran_gob(20);
  set_ran_wep(({ "club" }));
  set_ran_arm(({ "helm" }));
  set_def_arm(({ "mail", "shield" }));
  set_c_chats(({ "I will smash your stupid head!",
                 "I will feed my rats with your corpse!",
                 "Dead meat!",
                 "I will sell loot from your corpse!" }));
  set_chats(({ "What do you want?",
               "I am hungry!!!",
               "Seen any rats around?",
               "I am only catching rats here.",
               "You know how to catch rats?",
               "I could use help... they are so fast for me.",
               "They are nice but hard to catch.",
               "Would you care to help me?"
           }));
  set_name("fronghum");
  set_long("This small clumsy goblin is carrying a big cage on his back.\n");
  add_item(({"cage","big cage"}),"It is a big cage for small animals.\n");
  remove_prop(NPC_M_NO_ACCEPT_GIVE);
  remove_prop(LIVE_I_NEVERKNOWN);
  trig_new("%w 'introduces' %s", "react_introduce");
  add_ask(({"help","task","quest","job"}), VBFC_ME("answer_help"));
  add_ask(({"reward","about reward","for reward"}), VBFC_ME("answ_reward"));
  add_ask(({"final reward","for final reward"}), VBFC_ME("answ_final"));
  set_alarm(10.0, 0.0, "make_action");
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

  if(TP->test_bit("Rhovanion",GROUP,BIT))
  {
    command("whisper "+who_ask+" Let the others do the job now.");
    command("pat "+who_ask);
    return "";
  }
  if(member_array(who_ask, list_introduced) == -1)
  {
    command("say Introduce yourself first!");
    command("grin at "+who_ask);
    return "";
  }
  if(member_array(who_ask, list_asked_help) != -1)
  {
    command("say "+capitalize(who_ask)+", RATS!!! Understand???");
    command("pat "+who_ask);
    return "";
  }
  list_asked_help += ({ who_ask }); /* now he has asked first time */
  command("whisper "+who_ask+" I am trying to catch some rats here.");
  set_alarm(1.0,0.0,"command","whisper "+who_ask+
                              " But they are very fast for me.");
  set_alarm(2.0,0.0,"command","whisper "+who_ask+
                              " Maybe you could catch them for me?");
  set_alarm(3.0,0.0,"command","whisper "+who_ask+
                              " Bring me the rats and you can ask for reward.");
  set_alarm(4.0,0.0,"command","whisper "+who_ask+
                         " More you bring - the bigger reward of course.");
  return "";
}

void enter_inv(object obj, object from)
{
  string ooo, *arr;

  ::enter_inv(obj, from);
  if(!living(from)) return;

  arr = obj->query_adjs();
  if (!arr) arr = ({ });
  ooo = implode(arr+({LOW(obj->query_name())}), " ");
  if(MASTER_OB(obj) == "/std/coins")
  {
    set_alarm(1.0, 0.0,"command", "say Money!!!");
    set_alarm(0.5,0.0,"get_rid_of",obj);
    return;
  }
  if (member_array(from->query_real_name(), list_asked_help) == -1)
  {
    set_alarm(1.0, 0.0, "command", "say Why do you give me this?");
    set_alarm(2.0, 0.0, "command", "drop "+ooo);
    return;
  }
  if (member_array(NPC_DIR+"rat.c", inherit_list(obj)) != -1)
  {
    set_alarm(1.0, 0.0, "command", "say Nice "+obj->short()+"!");
    set_alarm(2.0, 0.0, "command", "emote puts "+obj->short()+
                                   " into the cage.");
    from->add_prop(RATS, from->query_prop(RATS) + 1);
    set_alarm(0.5, 0.0, "get_rid_of", obj);
    return;
  }
  set_alarm(1.0, 0.0, "command", "say This is not good.");
  set_alarm(2.0, 0.0, "command", "drop "+ooo);
}

string answ_reward()
{
  int t;

  if (member_array(TP->query_real_name(), list_asked_help) == -1)
  {
    command("say Have you done anything for me?");
    return "";
  }
  t = TP->query_prop(RATS);
  command("emote counts rats in his cage.");
  if (t < 5)
  {
    set_alarm(2.0, 0.0, "command", "say You have not caught too many rats!");
  }
  else if (t < 10)
  {
    set_alarm(2.0, 0.0, "command", "say Good, but can't you catch more?");
  }
  else
  {
    set_alarm(2.0, 0.0, "command", "say I am sure you can catch more!");
  }
  set_alarm(3.0, 0.0, "command", "say But if you really want it now "+
                                 "just ask me for final reward.");
  return "";
}

string answ_final()
{
  int r, i;

  if (member_array(TP->query_real_name(), list_asked_help) == -1)
  {
    command("say Have you done anything for me?");
    return "";
  }
  if (TP->test_bit("Rhovanion", GROUP, BIT))
  {
    command("say I think I have already rewarded you!");
    return "";
  }
  i = TP->query_prop(RATS);
  r = MIN(300, 15 * i);
  if (!i)
  {
    command("say You have better bring me some rats first!");
    return "";
  }
  list_asked_help -= ({ TP->query_real_name() });
  command("say Here is your reward.");
  reset_euid();
  TP->add_exp(r, 0);
  write_file(LOG_FILE, TP->query_name() + " caught "+i+" rats and got " +
                 r + " exp. " + ctime(time()) + ".\n");
  TP->catch_msg("You feel more experienced.\n");
  TP->set_bit(GROUP, BIT);
  TP->save_me(1);
  SORT_FILE(LOG_FILE);
  return "";
}

void get_rid_of(object obj){ obj->remove_object(); }

void init_attack(){}

void make_action()
{
  object room = ENV(TO);
  string *rooms, *cmds, *exits = ({ });
  int i;

  if (present("rat", room))
  {
    command("catch rat");
    remove_prop("_know_catch_rat");
  }
  if (!sizeof(FILTER_PLAYERS(all_inventory(room))))
  {
    rooms = room->query_exit_rooms();
    cmds = room->query_exit_cmds();
    for (i=0; i<sizeof(rooms); i++)
      if (wildmatch(RHUN_DIR+"ltown_ne/*", rooms[i]))
        exits += ({ cmds[i] });
    if (sizeof(exits))
      command(ONE_OF_LIST(exits));
  }
  set_alarm(itof(10+random(10)), 0.0, "make_action");
}

