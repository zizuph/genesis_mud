inherit "/std/monster";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/bits.h"

#define QUEST_NAME "revenge"

/* Function prototypes */
void reward_locket_quest(object player);
void locket_quest();
void return_introduce(string who);

int alarm_id;

create_monster()
{
    if (!IS_CLONE)
        return;	

    set_living_name("_tick_");
    set_name("tick");
    set_race_name("hobbit");
   set_long("This poor creature looks like a bag of bones. He "+
   "seems incurable by medicine, perhaps he is holding on for some news?\n");
    set_adj(({"weak","scrawny"}));
    set_stats(({30,30,40,80,100,30}));
    MAKE_MONEY;
    set_alignment(350);
    
    set_skill(SS_WEP_KNIFE,50);
    set_skill(SS_DEFENCE,50);
    
    add_prop(CONT_I_WEIGHT, 70*1000);
    add_prop(CONT_I_HEIGHT, 110);
    set_gender(G_MALE);

    set_chat_time(5);
   add_chat("Where could he be?");
   add_chat("If you ever reach my age, I hope you will feel better than I do.");
   add_chat("Medicine is no good for me, I just want to see my son before I go.");
   add_chat("I don't mind dying so much as this pain.");

   set_act_time(3);
   add_act("emote rolls over in bed.");
   add_act("cough");
   add_act("sigh sad");

    trig_new("%w 'introduces' %s","react_introduce");
    add_ask(({"son","troll","help","quest","job","task"}),VBFC_ME("ask_stuff"));
   add_ask(({"gollin"}),VBFC_ME("give_task"));
   add_ask(({"reward","for reward","for a reward"}),VBFC_ME("ask_reward"));

}


int
react_introduce(string who, string dummy)
{
    if (who)
    {
        who = lower_case(who);
        set_alarm(3.0,0.0,&return_introduce(who));
        return 1;
    }
}

void
return_introduce(string who)
{
    object obj;
    int    ran;
    
    if (obj = present(who,environment()))
    {
        ran = random(3);
        if (ran == 0)
        {
            command("say Good day " + obj->query_cap_name() +", are you looking for an adventure here?");
            command("introduce me");
            command("smile " + who);
            command("shake " + who);
        }
        if (ran == 1)
        {
            command("bow to " + who);
            command("introduce me");
            command("say Welcome " + who +", can i help you with something?");
            command("smile serious " + who);
        }
        if (ran == 2)
        {
            command("introduce me");
            command("say Greetings " + who + ".");
        }
    }
}


void test_locket_quest(object player)
{
int ix;
ix = player->test_bit("Shire",WESTERN_GROUP,TROLL_REVENGE_BIT);
    if(player->test_bit("Shire",WESTERN_GROUP,TROLL_REVENGE_BIT))
    {
      command("say Thanks for asking, but I am at peace now, thanks to you.");
      return;
    }
/*
            command("gasp");
          command("say I know just who this is! Just wait till...");
          command("blush");
          command("Oh, sorry, didn't mean to have an outburst.");
            command("say Thank you so much for aiding me.");
            command("shake " + player->query_name());
*/
            reward_locket_quest(player);

}


string give_task()
  {
    if (!TP->test_bit("Shire",WESTERN_GROUP,TROLL_REVENGE_BIT))
    {
        locket_quest();
        return "";
    }
    else 
    {
        command("say Ah, thank you, you have already helped "+
        "me find peace.");
        return "";
    }
}

string
ask_stuff()
{
  command("say So you are looking for adventure eh? You think you ");
   command("say know something about my boy, eh?");
   command("say If you do, why don't you ask me about him- by name?");
   command("say But I doubt you know him, he was such a good ");
   command("cry");
   command("say Son.");
   command("sigh");

    return "";
}

string
ask_reward()
{

   if(TP->query_prop("flooded_the_shaws_"))
   {
     command("say Well, now, you're still wet behind the ears!");
     command("say I can't tell you how much this means to me.");
     command("say Those no-good stinking trolls won't bother anyone ever again!");
     command("say I can't thank you enough, but this is what I have.");
     command("give coins to "+TP->query_real_name());
     test_locket_quest(TP);

   return "";
   }
}

void locket_quest()
{
    if(TP->query_prop("_troll_revenge_quest"))
    {
      command("glare " + TP->query_name());
      command("say Are you going to help me or not? ");
      command("say I want vengeance so I can rest easy!");
      return;
  }

    command("say As you know, I have lost my son to those...those");
    command("say stinking trolls of the Trollshaws!");
    command("sniff");
    command("say I don't care what you do, but please avenge him!");
    command("say Avenge him!");
    command("emote trembles with anger for a moment.");
    command("say I cannot rest until");
    command("emote gasps for breath.");
    command("say until they have gotten what is coming to them!");

    TP->add_prop("_troll_revenge_quest",1);
}

void
reward_locket_quest(object player)
{
          player->remove_prop("_troll_revenge_quest");
          player->set_bit(WESTERN_GROUP,TROLL_REVENGE_BIT);
          player->add_exp(TROLL_REVENGE_EXP,0);
          seteuid(getuid(TO));
          log_file(QUEST_NAME, extract(ctime(time()),4,15) + " " +
          CAP(player->query_real_name()) + " rewarded with "+TROLL_REVENGE_EXP+" exp, "+
          "<"+player->query_average_stat()+"> avg stats.\n");
          tell_object(player,"You feel much more experienced!\n");
	  say(QCTNAME(player) + " got a nice reward.\n");
}


