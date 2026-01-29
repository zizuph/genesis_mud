inherit "/std/monster";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/bits.h"

#define QUEST_NAME "bracelet"

/* Function prototypes */
void reward_locket_quest(object player);
void locket_quest();
void return_introduce(string who);

int alarm_id;

create_monster()
{
    if (!IS_CLONE)
        return;	

    set_living_name("_petunia_");
    set_name("petunia");
    set_race_name("hobbit");
   set_long("This middle-aged hobbit woman seems distraught."+
   " Perhaps you can find out what the matter is?\n");
    set_adj(({"old","kindly"}));
    set_stats(({35,50,40,80,100,30}));
    MAKE_MONEY;
    set_alignment(350);
    
    set_skill(SS_WEP_KNIFE,50);
    set_skill(SS_DEFENCE,50);
    
    remove_prop(NPC_M_NO_ACCEPT_GIVE,0);
    add_prop(CONT_I_WEIGHT, 70*1000);
    add_prop(CONT_I_HEIGHT, 110);
    set_gender(G_FEMALE);

    set_chat_time(2);
   add_chat("I wish I knew when he was coming home.");
   add_chat("A Shirriffe's work is dangerous.");
   add_chat("There is more danger in this world than you know.");
   add_chat("Tonight it will only be dinner for two.");
   add_chat("My husband is dying, and he only wants one thing.");
   add_chat("Could you sing for me?");

   set_act_time(3);
   add_act("emote dusts the mantle.");
   add_act(({"west","hug tick","comfort tick","east","sigh wist"}));

   add_act("sigh");
   add_act("emote wonders if she'll bother to make dinner tonight.");
    trig_new("%w 'introduces' %s","react_introduce");
   add_ask(({"task","help","quest","son","troll"}),VBFC_ME("give_task"));

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
            command("say Good day " + obj->query_cap_name() +", are you looking for a bite to eat here?");
            command("introduce me");
            command("smile " + who);
            command("shake " + who);
        }
        if (ran == 1)
        {
            command("bow to " + who);
            command("introduce me");
            command("say Welcome " + CAP(who) +", can I help you with something?");
            command("smile grim " + who);
        }
        if (ran == 2)
        {
            command("introduce me");
            command("say Greetings " + CAP(who) + ".");
            command("bow deeply to " + who);
        }
    }
}

void
 test_locket_quest(object player)
{
int ix;
ix = player->test_bit("Shire",WESTERN_GROUP,BRACELET_BIT);
    if(player->test_bit("Shire",WESTERN_GROUP,BRACELET_BIT))
    {
      command("say I appreciate your efforts, but you already told me what you knew.");
      return;
    }

   if(TP->query_prop("_i_killed_trollshaw_trolls"))
   {
     reward_locket_quest(player);
     return;
   }
   if(TP->query_prop("i_killed_the_big_guy"))
   {
   reward_locket_quest(player);
   return;
   }
else
       command("emote examines the silver bracelet closely.");
     command("say Ah, yes, this is Gollin's.");
       command("cry");
       command("sniff");

   command("hmm");
   command("say You don't seem to have fought much for this bracelet...");
   command("say My son could take many enemies, and you don't seem to have a scratch on you.");
   command("say Who gave you this??");
   command("glare");
   return;

}


string give_task()
  {
    if (!TP->test_bit("Shire",WESTERN_GROUP,BRACELET_BIT))
    {
        locket_quest();
        return "";
    }
    else 
    {
     command("say Perhaps you should see my husband?");
        return "";
    }
}


void locket_quest()
{
    if(TP->query_prop("_lost_bracelet_quest"))
    {
     command("smile " + TP->query_name());
     command("say Please go find word of my son!");
      return;
  }
   command("say My son, the Shirriffe has been missing for nearly a week now.");
   command("sigh");
   command("say He was supposed to be back from Bree by now, but ");
   command("say It doesn't seem like he remembers the way.");
   command("say Could you please bring some sign of him?");
   command("say He wore a silver bracelet with his initial, G ");
   command("say on it. ");
   command("say He had brown curly hair and was wearing a green jacket.");
    TP->add_prop("_lost_bracelet_quest",1);
}

void
reward_locket_quest(object player)
{

   if(player->test_bit("Shire",WESTERN_GROUP,BRACELET_BIT))
   {
    return;
   }

   command("sob");
   command("say Yes, this was Gollin's.");
   command("say Thank you for braving such a dangerous mission.");
   command("say You must be a better fighter than my son was.");
   command("say Perhaps you should find my husband, he might have something for you to do.");
   command("say I only have this reward for you, though.");
          player->remove_prop("_lost_bracelet_quest");
          player->set_bit(WESTERN_GROUP,BRACELET_BIT);
          player->add_exp(BRACELET_EXP,0);
          seteuid(getuid(TO));
          log_file(QUEST_NAME, extract(ctime(time()),4,15) + " " +
          CAP(player->query_real_name()) + " rewarded with "+BRACELET_EXP+" exp, "+
          "<"+player->query_average_stat()+"> avg stats.\n");
          tell_object(player,"You feel much more experienced!\n");
	  say(QCTNAME(player) + " got a nice reward.\n");
}

failed_give(object obj,object from) 
{
  command("say I have no need for such things.");
  write(TO->query_The_name(from)+" gives it back to you.\n");
  obj->move(from);
  return;
}
public void
enter_inv(object obj, object from)
  { 
    ::enter_inv(obj, from);
    /*command("say DEBUG: enter_inv entered with from = " + (objectp(from) ? from->query_name() : " no object ") +
    " and obj = " + (objectp(obj) ? obj->query_name() : " no object "));*/
    if (!living(from))
        return;
    if (obj->id("_gollin_bracelet_"))
     {
       set_alarm(2.0,0.0,"test_locket_quest",from);
    }
    else  set_alarm(1.5,0.0,"failed_give",obj,from);
  }

