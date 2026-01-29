/*
 * Updated Trickster's NPC
 * Finwe, June 2002
 */

inherit "/std/monster";
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"

int alarm_id;

create_monster()
{
    if (!IS_CLONE)
        return;	

    set_name("rushlight");
    set_race_name("human");
    set_adj(({"short","rough-looking"}));
    set_long("This human looks at you strangely, wondering what you are "+
    "doing in his house. His fingers twitch at his side and you "+
    "wonder if you try anything you won't get a good beating.\n");
    set_stats(({70,60,65,80,100,95}));
    MAKE_MONEY;
    set_alignment(-163);
    
    set_skill(SS_WEP_SWORD,70);
   set_skill(SS_PARRY,70);
    set_skill(SS_DEFENCE,60);
    
    add_prop(CONT_I_WEIGHT, 60*100);
    add_prop(CONT_I_HEIGHT, 120);
    set_gender(G_MALE);
    


   add_ask(({"task","help","job","quest"}), VBFC_ME("ask_job"));
    set_chat_time(5);	    
    add_act(({"emote takes out his tobacco.","emote stuffs his pipe with some tobacco.",
              "emote lights his pipe.","emote gets a big smile all over his face as he inhales some smoke from his fine pipe."}));
   add_chat("The fire could use some stoking, I think.");
   add_chat("They don't make tobacco like Old Toby anymore.");
   add_chat("There are going to be more and more people coming up the Greenway, I deem.");
    add_chat("Get out of here, you're bothering me.");
    add_chat("What are you doing in my house?");


    set_act_time(5);
    add_act("yawn");
    add_act("glare");
    add_act("emote eyes you up carefully.");
    
    set_cact_time(5);
    add_cact("knee all");
    add_cact("emote screams: STOP IT, or I will tell the Master!");
     
    set_cchat_time(3);
    add_cchat("You think you are tough attacking a man like me, do you?");
    add_cchat("You stinking snob of an Shireling!!");
    add_cchat("Alas! I will have to kill you now.");
    
    /*Triggers*/
        
    set_alarm(0.5,0.0,"arm_me");

}

arm_me()
{
    object knife,tunic,boots;
    
    FIXEUID;

    knife = clone_object(WEP_DIR + "sword");
    tunic = clone_object(ARM_DIR + "ltunic");

    knife->move(TO);
    tunic->move(TO);
    command("wield sword");
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
    
/*  Added a little check to avoid getting more than one alarm.
 * Elessar, Nov. 7th 1995.
 */
    if (alarm_id) return;
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
    command("say I am too good for them!!");
    command("say I hope Sharkey will come soon.");
    remove_alarm(alarm_id);
}

string
ask_job()
{
   command("say Need help? Me? No.");
   command("ponder");
   command("emote looks at you carefully.");
   command("say I think you need help though.");
   command("say Get out of my house!");
   write("The short human pushes you outside with a great shove!\n");
   TP->move_living("M","/d/Shire/bree/rooms/road/broad05",1);
   command("emote pushes someone out of the house so fast, you can't see who it was.");
   command("say There, that showed 'em.");
   return "";

}
