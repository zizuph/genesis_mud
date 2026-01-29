#pragma save_binary

inherit "/std/monster";
#include "../defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Shire/common/make_money.h"

int alarm_id;
int intro_id = -1,re_intro_id = -1;
int not_intro;
void return_to_normal();
void return_to_normal_msg();
void introduce_me();
void re_intro();
 

void
create_monster()
{
  if(!IS_CLONE) return;

  set_name("targon");
  add_name("helmsman");
  set_title("Helmsman of the Flying Swan");
  set_race_name("human");
  set_adj("burly");
  add_adj("bronzed");
  set_long("This human is obviously a well-experienced sailor "+
    "and navigator, else he would never be able to serve as a helmsman. "+
    "Chances are pretty good then that he also is skilled in defending "+
    "the ship from pirates and other brigands.\n");
  default_config_npc(70+random(11,time()));
  set_base_stat(SS_DEX,90+random(11));
  set_base_stat(SS_CON,85+random(6));
  set_base_stat(SS_DIS,85+random(16));
  set_skill(SS_WEP_SWORD,70+random(11));
  set_skill(SS_DEFENCE,60+random(26,time()));
  set_skill(SS_PARRY,50+random(6));
  set_alignment(240+random(21));

  set_chat_time(9+random(4));
  add_chat("Ah, I love the tang of salt water in the breeze.");
  add_chat("There is nothing better than a stiff wind in your "+
    "face and sea mist washing over your body.");
  add_chat("It's a good thing the corsairs don't venture this "+
    "far north very often, even though we are prepared for them.");
  set_act_time(3+random(2));
  add_act("shout Tie down that line!");
  add_act("shout Get up that mast you bow-legged spawn of a monkey!");
  add_act("shout You call that hustle? I've seen rocks move faster "+
    "than that!");
  add_act("shout You, Earnil, keep awake up there, I don't care "+
    "what the inside of your eyelids look like!");
  add_act("shout If I wanted to stand around and wait all day "+
    "I'd have been a tree. Let's see some action over there!");
  add_act("shout Let's go! Hustle you lazy sons of udderless goats!");
  add_act("emote flexes his grip on the ship's wheel.");
  add_act("emote observes the movements of the crew with a keen eye.");
  add_act("emote turns the ship's wheel with the ease of long "+
    "familiarity.");
  set_cact_time(5);
  add_cact("shout All hands on deck, we are under attack!");
  add_cact("shout Beware! Beware! Those thieving scum corsairs have "+
    "snuck aboard the ship!");
  add_cact("knee all");
  add_cact("emote spits on the ground while cursing your name.");

    trig_new("%w 'introduces' %s", "react_introduce");
  MAKE_MONEY;
  set_alarm(1.0,0.0,"arm_me");
}


void arm_me()
{
  object wep,arm;
  FIXEUID;
   
  wep = clone_object(SHIP_DIR + "cutlass");
  wep->move(TO);  
  arm = clone_object(SHIP_DIR + "shield");
  arm->move(TO);
}


void attacked_by(object ob)
{
  ::attacked_by(ob);

  command("emote locks the wheel into position and releases it.");
  command("say Ok dog, you want a fight, I'll give you a fight.");
  command("wield all");
  command("wear all");
  
  alarm_id = set_alarm(10.0,20.0,"return_to_normal");
}


void return_to_normal() 
{
  if(TO->query_attack()) 
  {
    return;
  }
 
  else
  {
    return_to_normal_msg();
    return;
  }
}
 
void
return_to_normal_msg()
{
  mixed *calls = get_all_alarms();
  int i;
 
  command("remove all");
  command("unwield all");
  command("say That'll show 'em who is boss around here!");
  command("emote grasps the wheel and frees it with a quick tug.");
 
  for (i = 0; i < sizeof(calls); i++)
  {
    alarm_id = calls[i][0];
    remove_alarm(alarm_id);
  }
}

void
react_introduce(string person,string who)
{
    if (not_intro)
	return;
    if (intro_id == -1)
        intro_id = set_alarm(4.0,0.0,&introduce_me());
}

void
introduce_me()
{
    remove_alarm(intro_id);
    intro_id = -1;
    command("introduce myself");
    not_intro = 1;
    if (re_intro_id == -1)
        re_intro_id = set_alarm(15.0,0.0,&re_intro());
}

void
re_intro()
{
    not_intro = 0;
    remove_alarm(re_intro_id);
    re_intro_id = -1;
}
