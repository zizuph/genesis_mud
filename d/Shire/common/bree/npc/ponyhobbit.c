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

    set_name("longhole");
    set_race_name("hobbit");
    set_adj(({"plump","talkative"}));
    set_long("This is one of the merry hobbits living in Bree. He looks like "
    	    +"he has something to say and wants to hear much.\n");
    set_stats(({30,50,40,58,60,30}));
    MAKE_MONEY;
    set_alignment(100);
    
    set_skill(SS_WEP_KNIFE,50);
    set_skill(SS_DEFENCE,50);
    
    add_prop(CONT_I_WEIGHT, 60*1000);
    add_prop(CONT_I_HEIGHT, 120);
    set_gender(G_MALE);
    
    set_chat_time(1);	    
    add_chat("How are you today master?");
    add_chat("My, is it not nice weather we have today?");
    add_chat("And just where are you from, stranger?");
    add_chat("I hope those birds will stay away from my garden now. I tell you master, those birds are damned!");
   add_chat("Might you know anything interesting?");
   add_chat("There's no accounting for East and West, I always say.");

    set_act_time(3);
    add_act("yawn");
    add_act("smile merri");
    add_act("sneeze");
    add_act("emote looks like he is thinking of food.");
    add_act("giggle merri ");
    add_act("emote sings a merry little tune.");
    add_act("emote drinks a mug of cold beer.");
    add_act("emote stares at the firelight a while.");
   add_act("introduce myself");
    add_act(({"emote takes out some nice tobacco.","emote stuffs his pipe with tobacco.","emote lights his pipe.","emote inhales deeply as he smokes his pipe.","emote sighs deeply, relaxing."}));
    
    set_cact_time(5);
    add_cact(({"scream","say WHY me?? WHY, tell me, WHY??!"}));
    add_cact("knee all");
    add_cact("emote screams: STOP IT, or I will start getting angry at you!");
     
    set_cchat_time(3);
    add_cchat("You think you are tough attacking a hobbit eh?");
    add_cchat("You stinking snob of an easterling!!");
    add_cchat("Hopefully you will run when my friends are here.");
    
    /*Triggers*/
        
    set_alarm(0.5,0.0,"arm_me");

}

arm_me()
{
    object knife,tunic,boots;
    
    FIXEUID;

    knife = clone_object(BREE_DIR + "wep/" + "bknife");
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
    command("say You would not mess with me, I have mighty friends.");
    command("emote grips the hilt of his long-knife!");
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
    command("say Puh, i managed to scare those bandits away!");
    command("say I hope master Took will come soon.");
    remove_alarm(alarm_id);
}

