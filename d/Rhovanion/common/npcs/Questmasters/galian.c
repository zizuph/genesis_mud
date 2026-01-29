/*
 * galian.c
 * This is the questmaster in Thranduil's Caverns in Rhovanion.
 * Created in november 1993 by Daneel.
 *
 * QUESTS:
 * 
 * 0 - Find the adventurer guild             50 xp
 * 1 - Find the Storeroom with barrels       50 xp
 * 2 - Find key and free prisoner           500 xp
 * 3 - Spider legs quest                   7500 xp
 */

inherit "/std/monster.c";

#include "/d/Rhovanion/defs.h"
#include "/d/Rhovanion/lib/binbit.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

#define PERSONAL_STAMP_NOTE  "_personal_stamp_note_"
#define TOURS "/d/Rhovanion/common/quest/tours"
#define NOTE "/d/Rhovanion/common/quest/tournote"
#define GROUP 0
#define LEFT_BIT 0
#define RIGHT_BIT 3
#define REWARD ({ 50,50,500,7500,3600,0,0,0,0,0,0,0,0,0,0 })

#define SPIDER_LEGS_QUEST  3
#define LEG_IS_LIVE        "_leg_is_live"
#define GOOD_LEGS_GIVEN    "_good_legs_given_"
#define LIVE_LEGS_NOTIFIED "_live_legs_notified_"

string *tours;
string *list_introduced = ({ });
string *list_of_killers = ({ });

void
set_list_of_killers()
{
  int i;
  string text;

  text = read_file("/d/Rhovanion/log/galian_killers", 1, 1);
  if(!text || strlen(text)<2) return;
  text = explode(text, "\n")[0];
  i = 2;
  while(strlen(text) > 0)
  {
    list_of_killers += ({ text });
    text = read_file("/d/Rhovanion/log/galian_killers", i, 1);
    if(!text || strlen(text)<2) return;
    text = explode(text, "\n")[0];
    i += 1;
  }
}

int
player_is_killer(string name)
{
  if(member_array(name, list_of_killers) == -1)
    return 0;
  return 1;
}

void
create_monster()
{
  seteuid(getuid());

  set_living_name("_thranduil_quest_master_");
  set_title("Advisor of Thranduil");
  set_name("galian");
  set_pname("elves");
  set_race_name("elf");
  set_adj(({"tall","wise"}));
  set_long("This is the advisor of Thranduil, King of the Silvan elves "+
           "in the northern part of Mirkwood. He might have some tasks "+
           "for you to do. \n");

  set_stats(({70+random(15), 70+random(15), 70+random(15), 
              70+random(15), 70+random(15), 70+random(15)}));

  set_skill(SS_WEP_SWORD, 80);
  set_skill(SS_2H_COMBAT, 60);
  set_skill(SS_PARRY, 80);
  set_skill(SS_DEFENCE, 70);
  set_skill(SS_AWARENESS, 80);
  set_alignment(700);
  add_prop(NPC_M_NO_ACCEPT_GIVE, 0);

  add_prop(DO_I_TELL_RUMOURS, 1);

  set_chat_time(8);
  add_chat("Hello! Would you do something for me?");
  add_chat("I have small rewards for small jobs.");
  add_chat("I have big rewards for big jobs.");
  add_chat("Do you have spare time?");

  set_cchat_time(2);
  add_cchat("Alarm!");
  add_cchat("HELP, I AM BEING ATTACKED BY A FOOL");
  add_cchat("You shall regret this severly!");
  add_cchat("I will NOT give you any job if you kill me!!!");

  set_default_answer(VBFC_ME("default_answear"));

  add_ask(({ "tour", "quest", "task", "job"}), VBFC_ME("quest_inform"));

  trig_new("%w 'introduces' %s","react_introduce");

  tours = TOURS->query_tours();
  set_list_of_killers();
}

arm_me()
{
  object wep, arm;

  seteuid(getuid());

  wep = clone_object("/d/Rhovanion/common/weapons/gsword");
  wep->move(TO);
  command("wield all");

  arm = clone_object("/d/Rhovanion/common/armours/brigadine");
  arm->move(TO);
  command("wear all");
}

init_living()
{
  ::init_living();
  if(living(TP) && TP->query_ip_number() && TP->check_seen(TO))
    if (present("Thranduil_Tour_Note",TP))
      set_alarm(5.0, 0.0, "do_ask_for_note", TP);
  add_action("accept_tour","accept");
}

int
query_introduced(object who)
{
  if(member_array(who->query_real_name(), list_introduced) == -1)
    return 0;
  return 1;
}

void
do_ask_for_note(object player)
{
  if(present(player, ENV(TO)) && player->check_seen(TO) && 
     query_introduced(player))
  {
    command("whisper "+player->query_real_name()+
            " Hello again! Did you find the place? Give me the note.");
    command("smile at "+player->query_real_name());
  }
  return;
}

void
react_introduce(string who, string dummy) 
{
  who = TP->query_real_name();
  dummy = explode(dummy, " ")[0];
  if((dummy == "himself") || (dummy == "herself") || (dummy == "itself") ||
     (dummy == CAP(who)))
    if(member_array(who, list_introduced) == -1)
      list_introduced += ({ who });
  set_alarm(itof(2+random(5)), 0.0, "return_introduce");
  return;
}

void
return_introduce() {
 object *in_room;
 int i, met_me;
  in_room=FILTER_LIVE(all_inventory(environment()));
  met_me=1;
  for(i = 0; i < sizeof(in_room); i++) 
    if(!in_room[i]->query_met(TO->query_real_name())) met_me=0;
  if (!met_me) {
     command("introduce me");
     command("bow");
  }
  return;
}

string
default_answear()
{
  if(!TP->check_seen(TO))
  {
    command("say Who is here???");
    return "";
  }
  if(player_is_killer(TP->query_name()))
  {
    command("say Hey!!! I still remember you "+TP->query_name()+"!");    
    command("say You have killed me!");
    tell_room(ENV(TO),QCTNAME(TO)+" turns his back to "+QTNAME(TP)+".\n",TP);
    TP->catch_msg(QCTNAME(TO)+" turns his back to you.\n");
    return "";
  }
  if(!query_introduced(TP))
  {
    command("say I think it is nice if newcomer introduce "+HIM(TP)+
            "self, isn't it?");
    return "";
  }

  command("say No way "+TP->query_name()+
               "!!! I don't give any info on this subject!");
  return "";
}

string
quest_inform()
{
  int qno;
  string qstr;

  if(!TP->check_seen(TO))
  {
    command("say Who is here???");
    return "";
  }
  if(player_is_killer(TP->query_name()))
  {
    command("say Hey!!! I still remember you "+TP->query_name()+"!");    
    command("say You have killed me!");
    tell_room(ENV(TO),QCTNAME(TO)+" turns his back to "+QTNAME(TP)+".\n",TP);
    TP->catch_msg(QCTNAME(TO)+" turns his back to you.\n");
    return "";
  }
  if(!query_introduced(TP))
  {
    command("say I think it is nice if newcomer introduce "+HIM(TP)+
            "self, isn't it?");
    return "";
  }

  qno = query_bin_bits(GROUP, LEFT_BIT, RIGHT_BIT, TP);

  if (qno >= sizeof(tours) )
  {
    command("whisper "+TP->query_real_name()+
          " I'm sorry, there are no tasks for you to do at the moment.");
    return "";
  }

  if (qno == SPIDER_LEGS_QUEST)
  {
    command("whisper "+TP->query_real_name()+
                         " Now there is one dangerous task...");
    command("whisper "+TP->query_real_name()+
              " In the Mirkwood forest live big black spiders.");
    command("whisper "+TP->query_real_name()+
              " We hate them and kill them with our magic wherever we can.");
    command("whisper "+TP->query_real_name()+
              " Unfortunately we need their legs. Without them we can't cast");
    command("whisper "+TP->query_real_name()+
              " our best spell. So if you can bring me eight legs of spiders");
    command("whisper "+TP->query_real_name()+
              " I would be very grateful.");
    return "";
  }
  
  command("whisper "+TP->query_real_name()+" this is what you should do:");
  TP->catch_msg(tours[qno]);
  command("whisper "+TP->query_real_name()+
              " If you want to do this task, type 'accept task'");
  command("smile hopefully");
  return "";
}

int
accept_tour(string str)
{
  object note;
  int qno;

  seteuid(getuid());

  if (!str || (str != "task"))
  {
    NF("Accept what?\n");
    return 0;
  }
  if(!TP->check_seen(TO))
  {
    command("say Who is here???");
    return 1;
  }
  if(player_is_killer(TP->query_name()))
  {
    command("say Hey!!! I still remember you "+TP->query_name()+"!");    
    command("say You have killed me!");
    tell_room(ENV(TO),QCTNAME(TO)+" turns his back to "+QTNAME(TP)+".\n",TP);
    TP->catch_msg(QCTNAME(TO)+" turns his back to you.\n");
    return 1;
  }
  if(!query_introduced(TP))
  {
    command("say I think it is nice if newcomer introduce "+HIM(TP)+
            "self, isn't it?");
    command("peer "+TP->query_real_name());
    return 1;
  }

  qno = query_bin_bits(GROUP,LEFT_BIT,RIGHT_BIT,TP);
  tell_room(ENV(TO), QCTNAME(TP) + " asks "+QTNAME(TO)+" for a task.\n",TP);
  TP->catch_msg("You ask "+QTNAME(TO)+" for a task.\n");
  if (qno >= sizeof(tours))
  {
    command("say Sorry, I have no more tasks for you, "+TP->query_name()+".");
    return 1;
  }
  if (qno == SPIDER_LEGS_QUEST)
  {
    command("whisper "+TP->query_real_name()+
          " Thank you and be carefull - spiders are very dangerous.");
    return 1;
  }

  command("whisper "+TP->query_real_name()+
            " Good! Here is a note that will show that you are ");
  command("whisper "+TP->query_real_name()+
            " solving a task for me. When you have solved it, come");
  command("whisper "+TP->query_real_name()+" back to me.");
  note = clone_object(NOTE);
  note->set_tour_no(qno);
  note->add_prop(PERSONAL_STAMP_NOTE, TP->query_real_name());
  if ((note->move(TP)))
  {
    command("whisper "+TP->query_real_name()+
         " Hmm. You couldn't carry more. Well, I'll drop drop it here.");
    note->move(environment(TO));
  }
  return 1;
}

void
do_reward(object player, int qno)
{
  set_bin_bits(GROUP,LEFT_BIT,RIGHT_BIT,player,qno);
  command("whisper "+TP->query_real_name()+
            " Congratulations! You have fulfilled the task I gave you!");
  command("shake " + player->query_real_name());
  player->add_exp(REWARD[qno-1],0);
  write_file("/d/Rhovanion/log/mini", player->query_name() +
	     " did tour " + qno + " and got " + REWARD[qno-1] + " exp. " +
	     ctime(time()) + ".\n");
  SORT_FILE("/d/Rhovanion/log/mini");
  TP->catch_msg("You feel more experienced.\n");
  TP->save_me(1);
  return;
}

void
test_reward(object player, object obj)
{
  if(obj->query_prop(PERSONAL_STAMP_NOTE) != player->query_real_name())
  {
    command("whisper "+player->query_real_name()+
              " Who gave you this??? It is not your!!!");
    obj->remove_object();
    return;
  }
  if (obj->query_tour_no() == query_bin_bits(GROUP,LEFT_BIT,RIGHT_BIT,player))
  {
    if (obj->query_tour_done())
    {
      do_reward(player, obj->query_tour_no() + 1);
      obj->remove_object();
      return;
    }
    else
    {
      command("whisper "+player->query_real_name()+
                   " But you haven't finished the task!");
      command("whisper "+player->query_real_name()+
              " Oh well - if you decide to try again, you're welcome to ask.");
      obj->remove_object();
      return;
    }
  }
  command("whisper "+player->query_real_name()+
            " You were not supposed to do that one - have you been cheating?");
  command("glare "+player->query_real_name());
  obj->remove_object();
  return;
}

void
test_spider_leg_quest(object player, object obj)
{
  if(!obj->query_prop(LEG_IS_LIVE))
  {
    if(!player->query_prop(LIVE_LEGS_NOTIFIED))
    {
      player->add_prop(LIVE_LEGS_NOTIFIED, 1);
      command("sigh");
      command("whisper "+player->query_real_name()+
         " Haven't I told you that I need legs from a living spider?");
      command("whisper "+player->query_real_name()+
         " I am sorry that I forgot to tell you earlier.");
    }
    tell_room(ENV(TO), QCTNAME(TO)+" drops the "+obj->query_short()+".\n");
    obj->move(ENV(TO));
    return;
  }
  player->add_prop(GOOD_LEGS_GIVEN, 1 + player->query_prop(GOOD_LEGS_GIVEN));
  obj->remove_object();
  if(player->query_prop(GOOD_LEGS_GIVEN) == 8)
  {
    do_reward(player, SPIDER_LEGS_QUEST + 1);
    player->remove_prop(GOOD_LEGS_GIVEN);
    return;
  }
  command("whisper "+player->query_real_name()+" "+
            CAP(LANG_WNUM(player->query_prop(GOOD_LEGS_GIVEN)))+"!");
  return;
}

void
delay_enter_inv(object obj, object from)
{
  if((ENV(TO) != ENV(from)) || !from->check_seen(TO))
  {
    command("say Who gave me this???");
    tell_room(ENV(TO),
              QCTNAME(TO)+" drops the "+obj->query_short()+" on the floor.\n");
    obj->move(ENV(TO));
    return;
  }

  if(player_is_killer(from->query_name()))
  {
    command("say Hey!!! I still remember you "+from->query_name()+"!");    
    command("say You have killed me!");    
    command("say I don't want anything from you!");    
    tell_room(ENV(TO),
              QCTNAME(TO)+" drops the "+obj->query_short()+" on the floor.\n");
    obj->move(ENV(TO));
    return;
  }

  if((MASTER_OB(obj) == NOTE) && query_introduced(from))
  {
    test_reward(from, obj);
    return;
  }

    if (obj->id("mirkwood_spider_leg") &&
     query_introduced(from) &&
     (query_bin_bits(GROUP,LEFT_BIT,RIGHT_BIT,from) == SPIDER_LEGS_QUEST))
  {
    test_spider_leg_quest(from, obj);
    return;
  }

  if(query_introduced(from))
    command("say I don't think I need this now.");
  else
    command("say I don't take anything from strangers.");

  if(obj->move(from))
  {
    command("hmm");
    command("say I see that you are quite full...");
    tell_room(ENV(TO), 
              QCTNAME(TO)+" drops the "+obj->query_short()+" on the floor.\n");
    obj->move(ENV(TO));
  }
  else
  {
    from->catch_msg(QCTNAME(TO)+" gives the "+obj->query_short()+
                    " back to you.\n");
    tell_room(ENV(TO), 
              QCTNAME(TO)+" gives the "+obj->query_short()+" back to "+
              QTNAME(from)+".\n", from);
  }
  return;
}

void
enter_inv(object obj, object from)
{
  ::enter_inv(obj, from);

  if (!from) return;

  set_alarmv(5.0, 0.0, "delay_enter_inv", ({obj, from}) );
}

void
log_killer(object killer)
{
  string text, name;
  int i;

  name = killer->query_name();

  if(player_is_killer(name)) return;

  write_file("/d/Rhovanion/log/galian_killers", name+"\n");
}

void
do_die(object killer)
{
  log_killer(killer);
  ::do_die(killer);
}

