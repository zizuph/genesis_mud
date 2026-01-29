inherit "/std/monster";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/bits.h"

/* Function prototypes */
void reward_locket_quest(object player);
void locket_quest();

//   Prototypes
void return_introduce(string who);

int alarm_id;

create_monster()
{
    if (!IS_CLONE)
        return;	

    set_living_name("ferumbras");
    set_name("ferumbras");
    set_title("Took, questmaster of Bree");
    set_race_name("hobbit");
    set_long("This is one of the elderly hobbits living in Bree. It looks like "
    	    +"he has been out travelling and adventuring a lot.\n");
    set_adj(({"serious","old"}));
    set_stats(({30,30,40,80,100,30}));
    MAKE_MONEY;
    set_alignment(350);
    
    set_skill(SS_WEP_KNIFE,50);
    set_skill(SS_DEFENCE,50);
    
    remove_prop(NPC_M_NO_ACCEPT_GIVE,0);
    add_prop(CONT_I_WEIGHT, 70*1000);
    add_prop(CONT_I_HEIGHT, 110);
    set_gender(G_MALE);

    trig_new("%w 'introduces' %s","react_introduce");
   add_ask(({"task","help","quest","job","orc"}),VBFC_ME("give_task"));

    set_alarm(1.0,0.0,"arm_me");    
}

arm_me()
{
    object tunic;
    
    FIXEUID;

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
            command("say Good day " + obj->query_name() +", are you looking for a task here?");
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
            command("bow deeply to " + who);
        }
    }
}


void test_locket_quest(object player)
  {
int ix;
command("say DEBUG: entered test_locket_quest with player = " + player->query_name());
command("say DEBUG: step 1 test_locket_quest with EASTERN_GROUP = " + EASTERN_GROUP + " and BREE_LOCKET_BIT = " + BREE_LOCKET_BIT);
ix = player->test_bit("Shire",EASTERN_GROUP,BREE_LOCKET_BIT);
command("say DEBUG: step 1 test_locket_quest with bit test = " + ix);
    if(player->test_bit("Shire",EASTERN_GROUP,BREE_LOCKET_BIT))
    {
command("say DEBUG: step 2 test_locket_quest with player = " + player->query_name());
      command("say I appreciate your efforts, but you already helped me.");
      return;
    }
command("say DEBUG: step 3 test_locket_quest with player = " + player->query_name());
  
            command("say Thank you so much for aiding me.");
            command("shake " + player->query_name());
            reward_locket_quest(player);

  }


string give_task()
  {
    if (!TP->test_bit("Shire",EASTERN_GROUP,BREE_LOCKET_BIT))
    {
        locket_quest();
        return "";
    }
    else 
    {
        command("say Forgive me, but I have no need of your "+
        "services at this time.");
        return "";
    }
}


void locket_quest()
{
    if(TP->query_prop("_bree_locket_quest"))
    {
      command("peer " + TP->query_name());
      command("say I've told you all I that I know about this.");
      command("say Please, go and find out what what you can!");
      return;
  }
    command("say I need to know who is behind the orcs are moving");
    command("say in around Bree. They could not avoid the Bounders");
    command("say without some sort of aid. I fear this is the beginning");
    command("say of the end for the Shire, if we cannot unite against");
    command("say such nasty creatures. Please bring me some identification");
    command("say of the spy, hobbit or human, and I will reward you well!");
    TP->add_prop("_bree_locket_quest",1);
}

void
reward_locket_quest(object player)
{
          player->remove_prop("_bree_locket_quest");
          player->set_bit(EASTERN_GROUP,BREE_LOCKET_BIT);
          player->add_exp(BREE_LOCKET_EXP,0);
          tell_object(player,"You feel much more experienced!\n");
}

public void
enter_inv(object obj, object from)
  { 
    ::enter_inv(obj, from);
command("say DEBUG: enter_inv entered with from = " + (objectp(from) ? from->query_name() : " no object ") +
    " and obj = " + (objectp(obj) ? obj->query_name() : " no object "));
    if (!living(from))
        return;
    if (obj->id("_orc_locket_")) test_locket_quest(from);
    else
      {
        command("say I have no need for such things.");
        write("The hobbit gives it back to you.\n");
        obj->move(from);
        return;
      }
  }

