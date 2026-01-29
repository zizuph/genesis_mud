inherit "/std/monster";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"

int alarm_id;

create_monster()
{
    if (!IS_CLONE)
        return;	

    set_living_name("sonic");
    set_name("sonic");
    set_race_name("human");
    set_long("This is one of the many humans living in Bree. He looks like "
    	    +"he is full of tears and sorrow.\n");
    set_adj(({"forlorn","hopeless"}));
    set_stats(({30,50,40,80,100,30}));
    MAKE_MONEY;
    set_alignment(100 - random(150));
    
    set_skill(SS_WEP_KNIFE,50);
    set_skill(SS_DEFENCE,50);
    
    add_prop(CONT_I_WEIGHT, 60*1000);
    add_prop(CONT_I_HEIGHT, 120);
    set_gender(G_MALE);
    
    set_chat_time(4);	    
     add_chat("Oh, I did it alright. And now I'm paying the price.");
    add_chat("Boy is it horrible what I did.");
    add_chat("I'm so alone.");
    add_chat("No one likes me.");
    add_chat("I promised to never do it again, but he said no.");
    add_chat("I knew it was wrong of me, but I did it anyway.");
    add_chat("I wish I could take it back, but no, I cannot.");
    add_chat("I thought I was too smart for them...");
    add_chat("Life is horrible.");
    add_chat("Have you been to see Ferumbras?");

    set_act_time(5);
    add_act("sniff");
    add_act("cry");
    add_act("sneeze");
    add_act("emote looks like he is thinking of food.");
    add_act("pout ");
    add_act("emote sings a long, sad song. You want to cry too..");
    add_act("emote curls up on the ground in a ball, sucking his thumb.");
    add_act("emote sobs uncontrollably.");
    add_act("emote kicks himself.");
    add_act("emote looks like he is thinking of food.");
    add_act("emote looks up in the sky with a guilty look.");
    
    set_cact_time(5);
    add_act("emote sits down on the ground and curls up into a ball.");
    add_cact(({"scream","say WHY me?? WHY, tell me, WHY??!"}));
    add_cact("say Finish me! Finish me now! End my pain!");
    add_cact("knee all");
    add_cact("emote screams: STOP IT, or i will start getting angry with you!");
     
    set_cchat_time(3);
    add_cchat("You think you are tough attacking a baby like me eh?");
    add_cchat("You stinking snob of an easterling!!");
    add_cchat("Hopefully you will run when my friends are here.");
    
    /*Triggers*/
        
    set_alarm(0.5,0.0,"arm_me");

    add_ask(({"help","task","job","quest"}), VBFC_ME("ask_help"));
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
    command("say Kill me, see if I care.");
    command("emote grips the hilt of his long-sword!");
    command("wield all");
    
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
    command("say Puh, I managed to scare those bandits away!");
    command("say I hope master Took will come soon.");
    remove_alarm(alarm_id);
}

string
ask_help()
{
   command("say Sorry, you can't help me, but try Ferumbras up on the Hill.");
   command("say He might be in need of help.");
   command("sigh");
   return "";
}
