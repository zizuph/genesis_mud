/*
 *   /d/Shire/common/bree/npc/ponyrang.c
 *
 *   This file was coded by a Shire wizard (Dunstable?) 
 *   on a unknown date. It is a Ranger in the inn in Bree.
 *
 *   Copyright (C) Shire Domain
 *
 *   Revision history:
 *   Sir Boromir of Mordor  2/Sep/95  : Made the Ranger a member of
 *					the northern rangers and gave
 *					him Gilgalad ranger cloak.
 *  
 *   Non-terminating alarm problem fixed. Glaurung 3-16-96
 *
 */

inherit "/d/Gondor/common/npc/n_ranger";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"

#define RANGER_OBJ_DIR "/d/Gondor/common/guild/obj/"

void after_attack();
void after_attack_msg();
int alarm_id;

void
create_ranger()
{
    if (!IS_CLONE)
        return;	

    set_name("appledore");
    add_name(({"ranger","dunadan",}));
    set_race_name("human");
    set_adj(({"strange-looking","weather-beaten"}));
    set_long("This is one of the visitors to the Prancing Pony. He seems "+
    "to say little yet you get the feeling he is aware of all that is happening in this room.\n");
    MAKE_MONEY;
    
    set_skill(SS_WEP_SWORD,80);
    set_skill(SS_PARRY,70);
    set_skill(SS_DEFENCE,60);
    
    add_prop(CONT_I_WEIGHT, 85*1000);
    add_prop(CONT_I_HEIGHT, 185);
    set_gender(G_MALE);
    set_alignment(200 + random(300));
    
    set_chat_time(10);	    
    add_chat("The fire could use some stoking, I think.");
    add_chat("They don't make tobacco like Old Toby anymore.");
    add_chat("I'd be careful if I were you, lots of eyes and ears around.");
    add_chat("The shadow of the East has returned.");


    set_act_time(5);
    set_stats(({ 110,120,110,85,85,110}));
    add_act("emote sips slowly at his glass of wine.");
    add_act("smile sli");
    add_act("emote closes his eyes and relaxes slightly.");
    add_act("emote shifts position silently in the corner.");
    add_act("emote stares at the firelight a while.");
    add_act(({"emote takes some nice tobacco from his pouch.","emote stuffs his old pipe with it deliberately.","emote lights his pipe from the fire.","emote inhales deeply and gives a sigh of relaxation."}));
    
    set_cact_time(1);
    add_cact("emote screams: Stop it, or i will start getting angry with you!");
    add_cact("brawl");
    add_cact("brawl");
     
    set_cchat_time(3);
    add_cchat("You think you are tough attacking a tired worn-out man eh?");
    add_cchat("You stinking snob of an easterling!!");
    add_cchat("Alas! I will have to kill you now..");
    
    set_alarm(0.5,0.0,"arm_me");
    set_company("the North");
    set_incognito();
}


arm_me()
{
    object sword,cloak;
    
    FIXEUID;

    sword = clone_object(BREE_DIR + "wep/" + "rsword");
    cloak = clone_object(RANGER_OBJ_DIR + "grey_cloak");
 
    sword->move(TO);
    cloak->move(TO);
    command("wear cloak");
    command("remove brooch");
   
}

void
attacked_by(object obj)
{
    ::attacked_by(obj);
    command("say You should not mess with me, I am stronger than I look.");
    command("emote grips the hilt of his longsword!");
    command("wield all");
    command("brawl");
    command("emote shouts: For Arnor! as he throws himself in the midst of the battle!");    
    
    alarm_id = set_alarm(10.0,20.0,"after_attack");
}

void
after_attack()
{
    if(TO->query_attack())
      return;

    else
    {
      after_attack_msg();
      return;
    }
}

void
after_attack_msg()
{
  mixed *calls = get_all_alarms();
  int i;
  
  command("unwield all");
  command("say Ha!, I managed to scare those bandits away!");
  command("say I hope Mithrandir will come soon.");

  for (i = 0; i < sizeof(calls); i++)
  {
    alarm_id = calls[i][0];
    remove_alarm(alarm_id);
  }
}
