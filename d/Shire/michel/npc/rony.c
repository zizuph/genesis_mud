inherit "/std/monster";
 
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/bits.h"
 
#define QUEST_NAME "pond"
#define LOG_FILE "/d/Shire/log/pond"
/* Function prototypes */
void reward_pond_quest(object player);
void pond_quest();
void return_introduce(string who);
 
create_monster()
{
    if (!IS_CLONE) return;
    set_living_name("_rony_");
    set_name("rony");
    set_title("the hard working peasant");
    set_race_name("hobbit");
    set_long("At the first sight this is an ordinary hobbit peasant:\n"+
     "big strong arms that got used to farmer labour, the hair is \n" +
     "faden under the sun, few wrinkles on his forhead.\n"+
     "But he looks grieved right now.\n");
    set_adj(({"sad-eyed","potato-nosed"}));
    set_stats(({40,60,40,30,30,30}));
    set_alignment(250);
 
    set_skill(SS_WEP_CLUB,50);
    set_skill(SS_DEFENCE,50);
 
    remove_prop(NPC_M_NO_ACCEPT_GIVE,0);
    add_prop(CONT_I_WEIGHT, 70*1000);
    add_prop(CONT_I_HEIGHT, 110);
    set_gender(G_MALE);
 
   set_chat_time(5);
   add_chat("Last night's party was great!");
   add_chat("Oh my poor head ...feels like I die soon.");
   add_chat("I think I drunk too much brandy last night.");
   add_chat("Have you seen our inn here in Michel Delving?");
   add_chat("I have always thought that Lakoshels are thieves!");
 
   trig_new("%w 'introduces' %s","react_introduce");
   add_ask(({"task","help","job"}),VBFC_ME("give_task"));
   add_ask(({"party","last night","thief"}),VBFC_ME("info"));
 
   set_alarm(1.0,0.0,"arm_me");
}
 
/*  Function arm_me equips the hobbit with money.armour and weapon */
void arm_me()
{
    object tunic;
    object flail;
    FIXEUID;
    MAKE_MONEY;
    tunic = clone_object(BREE_DIR + "arm/" + "ltunic");
    tunic->move(TO);
    command("wear all");
    flail = clone_object(MICH_DIR + "wep/h_flail");
    flail->move(TO);
    command("wield all");
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
            command("say Good day " + obj->query_cap_name() +", are you looking for a task here?");
            command("introduce me");
            command("smile " + who);
            command("shake " + who);
        }
        if (ran == 1)
        {
            command("bow to " + who);
            command("introduce me");
            command("Hi there, "+CAP(who));
            command("smile serious " + who);
        }
        if (ran == 2)
        {
            command("introduce me");
            command("say Greetings, " + CAP(who) + ".");
            command("bow tir to " + who);
        }
    }
}
 
void test_pond_quest(object player)
{
    if(player->test_bit("Shire",WESTERN_GROUP,POND_QUEST_BIT))
    {
      command("say You have done it one day and that was great.");
      command("say I don't want to bother you anymore.");
      return;
    }
    if(!player->query_prop("_me_found_chain_"))
     {
       command("emote grins suspiciously");
       command("say I see no confidence in your greedy eyes.");
       command("say I asked you to find it by yourself!.");
       command("say You have one more chance...go away!");
       return;
     }
     command("say Thank you very much!");
     command("say Those Lakoshels will pay for this one day!.");
            reward_pond_quest(player);
       return;
}
 
string give_task()
{
 if (!TP->test_bit("Shire",WESTERN_GROUP,POND_QUEST_BIT))
    {
        pond_quest();
        return "";
    }
      command("say You have done it one day and that was great.");
      command("say I don't want to bother you anymore.");
      return "";
}
 
 
void pond_quest()
{
    if(TP->query_prop("_pond_quest_"))
    {
      command("sigh");
      command("say Haven't I told you the task?");
      command("say Go and bring my chain");
      return;
    }
    command("hmm");
    command("say I lost the chain - the hierloom of our family!");
    command("moan");
    command("say I had waken up in the morning and found out my lost!");
    command("say I don't remember how I spent last night");
    command("say It was always with me! Every day");
    command("ponder returning him the hierloom");
    command("say You are able to earn some cash for this, go ahead!");
    TP->add_prop("_pond_quest_",1);
}
 
void
reward_pond_quest(object player)
{
          player->set_bit(WESTERN_GROUP,POND_QUEST_BIT);
          player->add_exp(POND_QUEST_EXP,0);
          seteuid(getuid(TO));
       log_file(LOG_FILE, extract(ctime(time()),4,15) + " " +
          CAP(player->query_real_name()) +" rewarded with "+POND_QUEST_EXP+" exp, "+
          "<"+player->query_average_stat()+"> avg stats.\n");
          tell_object(player,"You feel little more experienced!\n");
          set_alarm(9.0,0.0,"cash_reward",player);
}
 
/* Here i am rewarding the player with some cash */
cash_reward(object player)
{   command("say Are you still waiting for money?");
    command("sigh");
    command("say Ok, greedy "+ player->query_race() +", here you are!");
    MAKE_MONEY;
    command("give coins to "+ player->query_race());
}
 
/* Function enter_inv checks if the player gave us the chain we wanted */
public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (!living(from))
        return;
    if (obj->id("_elegant_chain_")) {test_pond_quest(from);}
    else
      {
        command("say This is not what I asked for.");
        command("drop " + obj->query_short());
        return;
      }
}
/* Function info give some helpfull information on quest */
string info()
{
    command("say I don't remember how I spent last night.");
    command("say There was a party...much ale, brandy and snacks.");
    command("smile dre");
    command("say I suspect the hobbit from Lakoshel family.");
    command("say He might have stolen it during last night!");
    return"";
}
do_die(object enemy)
{
  if (!enemy->query_prop("_i_kill_hobbits_"))
     {
      enemy->add_prop("_i_kill_hobbits_",1);
     }
     ::do_die();
}
