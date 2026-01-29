inherit "/std/monster";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"

int alarm_id;
void after_attack();
void after_attack_msg();
 
create_monster()
{
    if (!IS_CLONE)
        return;	

    set_name("ferny");
    set_race_name("human");
    set_adj(({"squint-eyed","ill-favored"}));
    set_long("This is one of the visitors to the Prancing Pony. He looks like "
    	    +"he might not be all human, and he is listening intently to the talk in the room.\n");
    set_stats(({70,60,65,80,100,95}));
    MAKE_MONEY;
    set_alignment(-100);
    
    set_skill(SS_WEP_SWORD,50);
   set_skill(SS_PARRY,70);
    set_skill(SS_DEFENCE,60);
    
    add_prop(CONT_I_WEIGHT, 60*1000);
    add_prop(CONT_I_HEIGHT, 120);
    set_gender(G_MALE);
    
    set_chat_time(5);	    
    add_act(({"emote takes out his tobacco.","emote stuffs his pipe with some tobacco.",
              "emote lights his pipe.","emote gets a big smile all over his face as he inhales some smoke from his fine pipe."}));
   add_chat("The fire could use some stoking, I think.");
   add_chat("They don't make tobacco like Old Toby anymore.");
   add_chat("There are going to be more and more people coming up the Greenway, I deem.");
   add_chat("We should follow the lead of the wizard in Orthanc.");


    set_act_time(5);
    add_act("yawn");
    add_act("smile mis");
    add_act("emote paces around the room nervously.");
    add_act("glare appledore");
    add_act("emote drinks a shot of prime liquor.");
    
    set_cact_time(5);
//  add_cact("shout Barliman, call the Shiriffe, "+QCTNAME(TP)+" is trying to kill me!!!");
    add_cact("knee all");
    add_cact("emote screams: STOP IT, or i will tell the Master!");
     
    set_cchat_time(3);
    add_cchat("You think you are tough attacking a man like me eh?");
    add_cchat("You stinking snob of an Shireling!!");
    add_cchat("Alas! I will have to kill you now.");
    
    /*Triggers*/
        
    set_alarm(0.5,0.0,"arm_me");

}

arm_me()
{
    object knife,tunic,boots;
    
    FIXEUID;

    knife = clone_object(BREE_DIR + "wep/" + "rsword");
    tunic = clone_object(BREE_DIR + "arm/" + "ltunic");
/*    boots = clone_object(BREE_DIR + "arm/" + "boots");
    boots->move(TO);
*/
    knife->move(TO);
    tunic->move(TO);
    command("wear all");
   
}

void
attacked_by(object obj)
{
    ::attacked_by(obj);
    command("say You should not mess with me, I am stronger than I look.");
    command("emote grips the hilt of his longsword!");
    command("wield all");
    command("wear all");
    
    alarm_id = set_alarm(10.0, 20.0, "after_attack");
}

void
after_attack()
{
    if(TO->query_attack())
    {
        return;
    }
 
    else
    {
      after_attack_msg();
      return;
    }
}
 
void after_attack_msg()
{
  mixed *calls = get_all_alarms();
  int i;
 
  command("unwield all");
  command("say I am too good for them!!");
  command("say I hope Sharkey will come soon.");
 
  for (i = 0; i < sizeof(calls); i++)
  {
    alarm_id = calls[i][0];
    remove_alarm(alarm_id);
  }
}
