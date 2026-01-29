inherit "/std/monster";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/bits.h"

#define QUEST_NAME "gloin"


/* Function prototypes */
void test_axe_quest(object player);
string give_task();
void axe_quest();
void reward_axe_quest(object player);

int alarm_id;

create_monster()
{
    if (!IS_CLONE)
        return;	

    set_name("gloin");
    set_race_name("dwarf");
    set_adj(({"wrinkled","white-bearded"}));
    set_long("This is one of the visitors to the Prancing Pony. He looks like "
    	    +"he wishes to appear unconcerned about other's affairs, but he is listening.\n");
    set_stats(({65,50,70,30,40,95}));
    MAKE_MONEY;
    set_alignment(100);
    
    set_skill(SS_WEP_AXE,70);
   set_skill(SS_PARRY,70);
    set_skill(SS_DEFENCE,60);
    
    add_prop(CONT_I_WEIGHT, 60*1000);
    remove_prop(NPC_M_NO_ACCEPT_GIVE,0);
    add_prop(CONT_I_HEIGHT, 120);
    set_gender(G_MALE);
    
    set_chat_time(3);	    
    add_act(({"emote takes out his tobacco.","emote stuffs his pipe with some tobacco.",
              "emote lights his pipe.","emote gets a big smile all over his face as he inhales some smoke from his fine pipe."}));
   add_chat("The fire could use some stoking, I think.");
   add_chat("Where the pick is sharp, the will is strong, and where the gold is good, the heart is warm.");
   add_chat("I'd be careful if I were you, lots of eyes and ears around.");
   add_chat("What fate has befallen the axe of Durin?");


    set_act_time(5);
    add_act("emote drinks a pint of ale.");
    add_act("smile sli");
    add_act("emote perks his ears up at the last bit of conversation.");
    add_act("emote stares at the firelight a while.");
    add_act("think Durin's axe");
    
    set_cact_time(5);
    add_cact("knee all");
    add_cact("emote screams: STOP IT, or i will start getting angry at you!");
     
    set_cchat_time(3);
    add_cchat("You think you are tough attacking a dwarf eh?");
    add_cchat("You stinking snob of an easterling!!");
    add_cchat("Alas! I will have to kill you now.");


   add_ask(({"durin's bane","axe","durin's axe"}),VBFC_ME("give_task"));
      
   set_alarm(0.5,0.0,"arm_me");

}

void
arm_me()
{
    object knife,tunic,boots;
    
    FIXEUID;

    knife = clone_object(BREE_DIR + "wep/" + "daxe.c");
    tunic = clone_object(BREE_DIR + "arm/" + "ltunic");
    knife->move(TO);
    tunic->move(TO);
    command("wear all");
   
}

void
attacked_by(object obj)
{
    ::attacked_by(obj);
    command("say You should not mess with me, I am younger than I look.");
    command("emote grips the hilt of his sharp axe!");
    command("wield all");
    command("wear all");
    
    alarm_id = set_alarm(10.0,20.0,"before_attack");
}

void
before_attack()
{
    if(TO->query_attack())
    {
        return;
    }
    command("unwield all");
    command("say Ha!, i managed to scare those scoundrels away!");
    command("say I hope Dain will come soon.");
    remove_alarm(alarm_id);
}


void test_axe_quest(object player)
{
    int ix;
    ix = player->test_bit("Shire",EASTERN_GROUP,GLOIN_BIT);
    if(player->test_bit("Shire",EASTERN_GROUP,GLOIN_BIT))
    {
      command("say Hmmfh. You've already helped me.");
      command("say But I think I'll keep this for my next adventure.");
      command("say Bye now!");
      command("e");
      command("s");
      command("w");
      remove_object();
      return;
    }
            command("cheer");
            command("say You'd better run, BALROG!!!");
            command("say 'Cause here comes Gloin!");
            command("emote wields Durin's Axe.");
            command("dance");
            reward_axe_quest(player);

}


string give_task()
  {
    if (!TP->test_bit("Shire",EASTERN_GROUP,GLOIN_BIT))
    {
        axe_quest();
        return "";
    }
    else 
    {
        command("say You've already done your part.\n");
        return "";
    }
}


void axe_quest()
{
    if(TP->query_prop("_durins_axe_quest"))
    {
      command("eyebrow " + TP->query_name());
      command("say I've told you all I that I know.");
      command("say Please, go and recover that holy weapon.");
      return;
  }
    command("say Many ages ago, the dwarves were driven from the Mines of");
    command("say Moria by Durin's Bane, which slew Durin the third and ");
    command("say took the Mines for its evil self.");
    command("say Now we dwarves are mighty again, mighty enough to");
    command("say challenge the Unspeakable Horror, but still we stand ");
    command("say no chance without the axe of Durin.  It is hidden deep ");
    command("say in the Mines and guarded well.");
    command("sigh");
    command("say I could reward you well if you were to bring that heirloom");
    command("say of all dwarves and give it to me.");
    TP->add_prop("_durins_axe_quest",1);
}



void
reward_axe_quest(object player)
{

          player->set_bit(EASTERN_GROUP,GLOIN_BIT);
          player->add_exp(GLOIN_EXP,0);
          seteuid(getuid(TO));
          log_file(QUEST_NAME, extract(ctime(time()),4,15) + " " +
          CAP(player->query_real_name()) + " rewarded with "+GLOIN_EXP+" exp, "+
          "<"+player->query_average_stat()+"> avg stats.\n");
          tell_object(player,"You feel more experienced!\n");
	       say(QCTNAME(player) + " was rewarded for generosity.\n");

         command("smile "+player->query_real_name());
         command("say Bye now- I've got a score to settle!!!");
         command("shout FOR DURIN!");
         command("e");
         command("s");
         command("w");
         remove_object();
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
   if(obj->id("_durins_axe_")) set_alarm(2.0,0.0,"test_axe_quest",from);

   else
      {
        command("say I have no need for such things.");
        command("drop "+obj->query_name());
        return;
      }
  }

