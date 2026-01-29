inherit "/std/monster";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/bits.h"

#define QUEST_NAME "feather"
#define QUEST_NAME2 "mapping"

/* Function prototypes */
void reward_locket_quest(object player);
void locket_quest();
void test_mapping_quest(object player);
void reward_mapping_quest(object player);
void mapping_quest();
string give_task();
string give_map_task();
void give_item_back(object obj, object from);

int alarm_id;

create_monster()
{
    if (!IS_CLONE)
        return;	

    set_living_name("puddifoot");
    set_name("puddifoot");
   set_title("the Chief Shirriffe of the North Farthing");
    set_race_name("hobbit");
    set_long("This is the Chief Shirriffe of the North Farthing. "+
     "He looks as if he has a lot on his mind- perhaps you could help?\n");
    set_adj(({"troubled","weary"}));
    set_stats(({30,30,40,80,100,30}));
    MAKE_MONEY;
    set_alignment(350);
    
    set_skill(SS_WEP_KNIFE,50);
    set_skill(SS_DEFENCE,50);
    
    remove_prop(NPC_M_NO_ACCEPT_GIVE,0);
    add_prop(CONT_I_WEIGHT, 70*1000);
    add_prop(CONT_I_HEIGHT, 110);
    set_gender(G_MALE);

    set_chat_time(2);
   add_chat("The Shirriffes could use a good hand like you.");
   add_chat("I hope old Pott returns soon.");
   add_chat("If there's one thing I hate more than warm beer it's orcs.");
   add_chat("Sometimes I wish for excitement to happen.");
   add_chat("That encampment of orcs weighs heavily on my mind.");
   add_chat("If only we had a map!");
   add_chat("Hail Shire!");
   add_chat("How are you today?");

    trig_new("%w 'introduces' %s","react_introduce");
   add_ask(({"help","quest","map","orc","camp"}),VBFC_ME("give_map_task"));
   add_ask(({"old pott","pott","another problem"}),VBFC_ME("give_task"));
   add_ask(({"for reward","reward","prize","my prize"}),VBFC_ME("ask_reward"));
    set_alarm(1.0,0.0,"arm_me");    
}

arm_me()
{
    object  sword, tunic;
    
    FIXEUID;
    sword = clone_object(COMMON_DIR + "weapon/shortsword");
    sword->move(TO);
    command("wield all");
    tunic = clone_object(BREE_DIR + "arm/" + "ltunic");
    tunic->move(TO);
    command("wear all");
   
}

int
react_introduce(string who, string dummy)
{
    if (who)
    {
        who = lower_case(who);
        set_alarm(3.0,0.0,"return_introduce",who);
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
            command("say Good day " + obj->query_cap_name() +", are you new in the area?");
            command("introduce me");
            command("smile " + who);
            command("shake " + who);
        }
        if (ran == 1)
        {
            command("bow to " + who);
            command("introduce me");
            command("say Welcome " + CAP(who) +", could you help me with something?");
            command("smile serious " + who);
        }
        if (ran == 2)
        {
            command("introduce me");
            command("say Greetings " + CAP(who) + ".");
            command("bow deeply to " + who);
        }
    }
}


void test_locket_quest(object player)
{
int ix;
ix = player->test_bit("Shire",EASTERN_GROUP,FEATHER_BIT);
    if(player->test_bit("Shire",EASTERN_GROUP,FEATHER_BIT))
    {
      command("say I appreciate the thought, but you already helped me.");
      return;
    }


   if(!player->query_prop("_i_got_the_feather"))
   {
     command("say Did you kill Old Pott?");
   command("say Where did you get this? I won't accept it.");
   command("drop feather");
   return;
   }
            command("swear");
            command("say Well, I guess that is that then.");
            command("say Old Pott is dead and will never return.");
            command("sigh");
            command("say Well, thank you for helping, though it is grevious news.");
            command("congratulate " + player->query_name());
            reward_locket_quest(player);

}

void test_mapping_quest(object player)
{
int ix;
ix = player->test_bit("Shire",EASTERN_GROUP,MAPPING_BIT);
    if(player->test_bit("Shire",EASTERN_GROUP,MAPPING_BIT))
    {
      command("say Hmmfh. You've already helped me.");
      return;
    }
            command("say Nice work there!");
            command("pat "+player->query_real_name()+ " back");
            reward_mapping_quest(player);

}


string give_task()
  {
    if (!TP->test_bit("Shire",EASTERN_GROUP,FEATHER_BIT))
    {
        locket_quest();
        return "";
    }
    else 
    {
        command("say You've done all you could, and I thank you again.\n");
        return "";
    }
}



string give_map_task()
  {
    if (!TP->test_bit("Shire",EASTERN_GROUP,MAPPING_BIT))
    {
        mapping_quest();
        return "";
    }
    else 
    {
        command("say Say, could you help me with another problem?");
        command("say If so, remember to ask me about Old Pott.");
        return "";
    }
}

string ask_reward()
{

    if(!TP->query_prop("_i_mapped_the_orc_camp"))
     {
   command("say But your map is not complete!");
   command("say Even I have seen that much. I know you can do better!");
   command("smile");
   return "";
    }

   test_mapping_quest(TP);
   return "";

}

void locket_quest()
{
    if(TP->query_prop("_feather_quest"))
    {
      command("eyebrow " + TP->query_name());
      command("say I've told you all I that I know.");
      command("say Please, go and find old Pott!");
      return;
  }
    command("say Old Pott, a shirriffe of these parts has been missing for days.");
    command("say His last assignment was to investigate an encampment of orcs...");
    command("say We fear the worst, but if you find him prisoner, return him!");
    command("say Though we have not much hope of that.");
    TP->add_prop("_feather_quest",1);
}


void mapping_quest()
{
    if(TP->query_prop("_mapping_quest"))
    {
      command("pat " + TP->query_name());
      command("say I've told you all I that I know.");
      command("say Are you not going to map the encampment?");
      return;
  }
    command("say We have seen fires coming from the hills for weeks now.");
    command("say Finally we understand what they mean- an encampment of orcs.");
    command("say We need more information before we can even think of fighting.");
    command("say I would like you to make a map of the camp. I'll reward you well.");
    command("say Just come back and ask for your prize.");
    TP->add_prop("_mapping_quest",1 + random(2));
}


void
reward_locket_quest(object player)
{
          player->remove_prop("_feather_quest");
          player->set_bit(EASTERN_GROUP,FEATHER_BIT);
          player->add_exp(FEATHER_EXP,0);
          seteuid(getuid(TO));
          log_file(QUEST_NAME, extract(ctime(time()),4,15) + " " +
          CAP(player->query_real_name()) + " rewarded with "+FEATHER_EXP+" exp, "+
          "<"+player->query_average_stat()+"> avg stats.\n");
          tell_object(player,"You feel much more experienced!\n");
	  say(QCTNAME(player) + " got a nice reward.\n");
}

void
reward_mapping_quest(object player)
{
          player->remove_prop("_i_mapped_the_orc_camp");
          player->set_bit(EASTERN_GROUP,MAPPING_BIT);
          player->add_exp(MAPPING_EXP,0);
          seteuid(getuid(TO));
          log_file(QUEST_NAME2, extract(ctime(time()),4,15) + " " +
          CAP(player->query_real_name()) + " rewarded with "+MAPPING_EXP+" exp, "+
          "<"+player->query_average_stat()+"> avg stats.\n");
          tell_object(player,"You feel more experienced!\n");
	  say(QCTNAME(player) + " was rewarded.\n");
}

public void
enter_inv(object obj, object from)
  { 
    ::enter_inv(obj, from);
    /*command("say DEBUG: enter_inv entered with from = " + (objectp(from) ? from->query_name() : " no object ") +
    " and obj = " + (objectp(obj) ? obj->query_name() : " no object "));*/
    if (!living(from))
        return;
   if(obj->id("_pott_feather_")) test_locket_quest(from);
   if(obj->id("_mapping_quest_map_")) test_mapping_quest(from);
    else
      {
        set_alarm(1.0, 0.0, &give_item_back(obj, from));
        return;
      }
  }

void
give_item_back(object obj, object from)
{
  command("say I have no need for such things.");
  command("give "+obj->short()+" to "+from->query_real_name());
  return;
}
